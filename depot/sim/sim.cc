#include "sim/sim.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_bool(print_state, true, "");

constexpr int kFruitPoints[14] = {0,    100,  300,  500,  500,  700,  700,
                                  1000, 1000, 2000, 2000, 3000, 3000, 5000};
constexpr int dr[4] = {-1, 0, 1, 0};
constexpr int dc[4] = {0, 1, 0, -1};

void Game::ParseMaze(std::istream& is) {
  CHECK(is.good());
  string line;
  int ghost_index = 0;
  total_pills_ = 0;
  while (true) {
    getline(is, line);
    if (line.empty() || !is.good()) break;
    CHECK(maze_.empty() || maze_.back().size() == line.size())
        << "Input maze format error";
    for (int i = 0; i < line.size(); ++i) {
      switch (line[i]) {
        case '\\':  // Lambda-Man
          CHECK(lman_ != nullptr);
          lman_->Initialize(maze_.size(), i, 2 /* face down */);
          break;
        case '=':  // Ghost
          CHECK(ghost_factories_.size() > 0);
          CHECK(ghost_factories_[ghost_index % ghost_factories_.size()]
                    != nullptr);
          ghosts_.emplace_back(
              ghost_factories_[ghost_index % ghost_factories_.size()]
                  ->Create());
          ghosts_.back()->Initialize(maze_.size(), i, 2 /* face down */);
          ghost_index++;
          break;
        case '%':  // Fruit
          fruit_location_ = Coordinate(maze_.size(), i);
          break;
        case '.':  // Pill
          total_pills_++;
          break;
      }
    }
    maze_.push_back(line);
  }
}

int Game::Start() {
  // constants
  const int height = maze_.size();
  const int width = maze_[0].size();
  const int end_of_lives = 127 * width * height * 16;
  const int fruit_appears[2] = {127 * 200, 127 * 400};
  const int fruit_expires[2] = {127 * 280, 127 * 480};
  const int flight_mode_duration = 127 * 20;
  const int level = (width * height - 1) / 100 + 1;
  const int fruit_points = kFruitPoints[level <= 12 ? level : 13];

  // initlal status
  tick_ = 0;
  score_ = 0;
  life_ = 3;
  bool fruit_appeared = false;
  vitality_ = 0;  // remaining ticks
  int utc_lman_next_move = 127;
  vector<int> utc_ghosts_next_moves(ghosts_.size());
  for (int i = 0; i < ghosts_.size(); ++i) {
    utc_ghosts_next_moves[i] = 130 + 2 * i;
  }
  vector<bool> ghosts_invisible_(ghosts_.size(), false);
  // True if Lambda-Man ate something since the last move
  bool eating = false;
  
  // AI init
  lman_->Init(this);
  for (int i = 0; i < ghosts_.size(); ++i) {
    ghosts_[i]->Init(this, i);
  }

  // main loop
  bool state_changed = true;
  while (tick_ < end_of_lives) {
    // *** 0. debug print
    if (FLAGS_print_state && state_changed) {
      std::stringstream ss;
      for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
          Coordinate rc(r, c);
          char symbol = GetSymbol(rc);
          if (symbol == '=' || symbol == '\\') symbol = ' ';
          if (lman_->GetRC() == rc) {
            symbol =  '\\';
          }
          for (int i = 0; i < ghosts_.size(); ++i) {
            if (ghosts_[i]->GetRC() == rc) {
              symbol = '=';
              break;
            }
          }
          if (fruit_appeared && fruit_location_ == rc) {
            symbol = '%';
            break;
          }
          ss << symbol;
        }
        ss << '\n';
      }
      LOG(INFO) << "The world state (utc=" << tick_ << ",score=" << score_ << "):\n" << ss.str();
      state_changed = false;
    }

    // *** 1. moves
    if (tick_ == utc_lman_next_move) {
      int d = lman_->Step();
      CHECK(0 <= d && d < 4) << d;
      if (lman_->CanMove(*this, d)) {
        lman_->SetDirection(d);
        CHECK(lman_->Move());
        LOG(INFO) << "Lambda-Man moved " << d;
      } else {
        LOG(WARNING) << "Lambda-Man hit a wall ('A`)";
      }
      utc_lman_next_move += eating ? 137 : 127;
      eating = false;  // Reset eating state
      state_changed = true;
    }
    for (int i = 0; i < ghosts_.size(); ++i) {
      if (tick_ == utc_ghosts_next_moves[i]) {
        // Check if the ghost has options
        int prev_d = ghosts_[i]->GetDirection();
        auto pos = ghosts_[i]->GetRC();
        int ways = 0;
        int oneway = 2;  // turn around if there is no option else
        for (int j = 3; j < 6; ++j) {
          int way = (prev_d + j) % 4;
          if (GetSymbolSafe(
                  Coordinate(pos.first + dr[way], pos.second + dc[way]),
                  '#') != '#') {
            ways++;
            oneway = way;
          }
        }
        if (ways >= 2) {  // has options
          int d = ghosts_[i]->Step();
          bool moved = false;
          if (d < 0 || 4 <= d) {
            LOG(WARNING) << "Ghost[" << i << "] returned invalid direction";
          } else if (d == (prev_d + 2) % 4) {
            LOG(WARNING) << "Ghost[" << i << "] chose the opposite direction";
          } else if (ghosts_[i]->CanMove(*this, d)) {
            ghosts_[i]->SetDirection(d);
            CHECK(ghosts_[i]->Move()); 
            LOG(INFO) << "Ghost[" << i << "] moved " << d;
            moved = true;
          } else {
            LOG(WARNING) << "Ghost[" << i
                         << "] chose a bad direction to a wall";
          }
          if (!moved) {  // auto move instead
            for (int j = 0; j < 4; ++j) {
              d = (prev_d + j) % 4;
              if (ghosts_[i]->CanMove(*this, d)) {
                ghosts_[i]->SetDirection(d);
                CHECK(ghosts_[i]->Move());
                LOG(INFO) << "Ghost[" << i << "] moved " << d;
                break;
              }
            }
          }
        } else if (
            ways == 1 ||
            GetSymbolSafe(Coordinate(pos.first + dr[oneway],
                                     pos.second + dc[oneway]), '#') != '#') {
          CHECK(ghosts_[i]->CanMove(*this, oneway))
              << i << ':' << ghosts_[i]->GetRC().first
              << ',' << ghosts_[i]->GetRC().second << "->" << oneway;
          ghosts_[i]->SetDirection(oneway);
          CHECK(ghosts_[i]->Move()) << "Ghost[" << i << "] auto move failed";
          LOG(INFO) << "Ghost[" << i << "] moved " << oneway;
        } else {
          // surrounded on all four sides by walls
        }
        utc_ghosts_next_moves[i] += (65 + i) * (vitality_ == 0 ? 2 : 3);
        state_changed = true;
      }
    }

    // *** 2. actions
    // flight mode deactivating
    if (vitality_ > 0) {
      if (--vitality_ == 0) {
        for (int i = 0; i < ghosts_.size(); ++i) {
          ghosts_invisible_[i] = false;
        }
      }
    }
    // fruit appearing/expiring
    for (int i = 0; i < 2; ++i) {
      if (tick_ == fruit_appears[i]) {
        fruit_appeared = true;
        state_changed = true;
      } else if (tick_ == fruit_expires[i]) {
        fruit_appeared = false;
        state_changed = true;
      }
    }

    // *** 3. occupying
    auto pos = lman_->GetRC();
    char symbol = GetSymbol(pos);
    if (symbol == '.') {
      // pill
      Eat(pos);
      score_ += 10;
      total_pills_--;
    } else if (symbol == 'o') {
      // check power pill
      Eat(pos);
      // Activates flight mode
      vitality_ = flight_mode_duration;
      // Gets all ghosts to turn around
      for (int i = 0; i < ghosts_.size(); ++i) {
        ghosts_[i]->SetDirection((ghosts_[i]->GetDirection() + 2) % 4);
      }
      score_ += 50;
    } else if (symbol == '%') {
      // check fruit
      if (fruit_appeared && fruit_location_ == pos) {
        fruit_appeared = false;
        score_ += fruit_points;
        break;
      }
    }

    // *** 4. life losing
    for (int i = 0; i < ghosts_.size(); ++i) {
      if (!ghosts_invisible_[i] && ghosts_[i]->GetRC() == pos) {
        if (vitality_ == 0) {
          // Ghost eats Lambda-Man
          // Loses a life
          life_--;
          // Resets Lambda-Man and all ghosts returned to starting positions and
          // directions
          lman_->ResetPositionAndDirection();
          for (int j = 0; j < ghosts_.size(); ++j) {
            ghosts_[j]->ResetPositionAndDirection();
          }
          break;
        } else {
          // Lambda-Man eats ghost
          ghosts_[i]->ResetPositionAndDirection();
          ghosts_invisible_[i] = true;
        }
      }
    }

    // *** 5. pills
    if (total_pills_ == 0) {
      LOG(INFO) << "Game over: You won!";
      break;
    }

    // *** 6. game over
    if (life_ == 0) {
      LOG(INFO) << "Game over: Lambda-Man has died";
      break;
    }

    // *** 7. tick end
    tick_++;
  }
  return score_;
}
