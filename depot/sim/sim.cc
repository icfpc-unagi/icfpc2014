#include "sim/sim.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include "util/colors.h"

DEFINE_bool(print_state, true, "");
DEFINE_bool(print_color, true, "");
DEFINE_bool(print_ghost_move, false, "");
DEFINE_int32(max_print_height, 40, "");
DEFINE_int32(max_print_width, 80, "");

constexpr int kFruitPoints[14] = {0,    100,  300,  500,  500,  700,  700,
                                  1000, 1000, 2000, 2000, 3000, 3000, 5000};
constexpr int kGhostPoints[4] = {200, 400, 800, 1600};
constexpr int dr[4] = {-1, 0, 1, 0};
constexpr int dc[4] = {0, 1, 0, -1};

void Game::ParseMaze(std::istream& is) {
  CHECK(is.good());
  string line;
  int ghost_index = 0;
  int lambda_man_index = 0;
  total_pills_ = 0;
  while (true) {
    getline(is, line);
    if (line.empty() || !is.good()) break;
    CHECK(maze_.empty() || maze_.back().size() == line.size())
        << "Input maze format error";
    for (int i = 0; i < line.size(); ++i) {
      switch (line[i]) {
        case '\\':  // Lambda-Man
          CHECK(lambda_man_factories_.size() > 0);
          CHECK(lambda_man_factories_[lambda_man_index %
                                      lambda_man_factories_.size()]
                    != nullptr);
          lman_.emplace_back(
              lambda_man_factories_[lambda_man_index %
                                    lambda_man_factories_.size()]
                  ->Create());
          lman_.back()->Initialize(maze_.size(), i, 2 /* face down */);
          lambda_man_index++;
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
  if (FLAGS_print_state && FLAGS_print_color) std::cout << CLEARSCREEN;
  
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
  vitality_ = 0;  // remaining ticks
  bool fruit_appeared = false;
  int utc_lman_next_move = 127;
  vector<int> utc_ghosts_next_moves(ghosts_.size());
  for (int i = 0; i < ghosts_.size(); ++i) {
    utc_ghosts_next_moves[i] = 130 + 2 * i;
  }
  int ghost_eaten = 0;
  // True if Lambda-Man ate something since the last move
  bool eating = false;

  // AI init
  for (int i = 0; i < lman_.size(); ++i) {
    lman_[i]->Init(this);
  }
  for (int i = 0; i < ghosts_.size(); ++i) {
    ghosts_[i]->Init(this, i);
  }

  CHECK(lman_.size() > 0);

  // main loop
  bool state_changed = true;
  while (tick_ < end_of_lives) {
    // *** 0. debug print
    if (FLAGS_print_state && state_changed) {
      std::stringstream ss;
      if (FLAGS_print_color) ss << RESETCURSOR;
      ss << "The world state (utc=" << tick_
         << ",lives=" << life_ << ",score=" << score_ << "):\n";
      auto lmanrc = lman_[0]->GetRC();
      int min_r = max(0, lmanrc.first - FLAGS_max_print_height / 2);
      int max_r = min(height, min_r + FLAGS_max_print_height);
      min_r = max(0, max_r - FLAGS_max_print_height);
      int min_c = max(0, lmanrc.second - FLAGS_max_print_width / 2);
      int max_c = min(width, min_c + FLAGS_max_print_width);
      min_c = max(0, max_c - FLAGS_max_print_width);
      for (int r = min_r; r < max_r; ++r) {
        for (int c = min_c; c < max_c; ++c) {
          Coordinate rc(r, c);
          const char* color = "";
          char symbol = GetSymbol(rc);
          if (symbol == '=' || symbol == '\\' || symbol == '%') symbol = ' ';
          if (symbol == '#') color = BLUE;
          if (symbol == 'o') color = YELLOW;
          if (lman_[0]->GetRC() == rc) {
            symbol =  vitality_ > 0 ? 'X' : '\\';
            color = BOLDYELLOW;
          }
          if (fruit_appeared && fruit_location_ == rc) {
            symbol = '%';
            color = BOLDRED;
          }
          for (int i = 0; i < ghosts_.size(); ++i) {
            if (ghosts_[i]->GetRC() == rc) {
              symbol = '=';
              static const char* kGhostColors[] = {BOLDRED, BOLDMAGENTA, BOLDCYAN, BOLDGREEN};
              color = kGhostColors[i % 4];
              break;
            }
          }
          ss << ' ';
          if (FLAGS_print_color) ss << color;
          ss << symbol;
          if (FLAGS_print_color) ss << RESET;
        }
        ss << '\n';
      }
      std::cerr << ss.str();
      state_changed = false;
    }

    // *** 1. moves
    if (tick_ == utc_lman_next_move) {
      int d = lman_[0]->Step();
      if (d < 0 && 4 <= d) {
        LOG(WARNING) << "Lambda-Man responded wrong direction " << d;
      } else if (lman_[0]->CanMove(*this, d)) {
        lman_[0]->SetDirection(d);
        CHECK(lman_[0]->Move());
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
        DCHECK(0 <= prev_d && prev_d < 4);
        int oppo_d = (prev_d + 2) % 4;
        auto pos = ghosts_[i]->GetRC();
        int ways = 0;
        int oneway = 2;  // turn around if there is no option else
        for (int j = 3; j < 6; ++j) {
          int way = (prev_d + j) % 4;
          if (ghosts_[i]->CanMove(*this, way)) {
            ways++;
            oneway = way;
          }
        }
        if (ways >= 2) {  // has options
          int d = ghosts_[i]->Step();
          bool moved = false;
          if (d < 0 || 4 <= d) {
            LOG(WARNING) << "Ghost[" << i << "] returned invalid direction";
          } else if (d == oppo_d) {
            LOG(WARNING) << "Ghost[" << i << "] chose the opposite direction";
          } else if (ghosts_[i]->CanMove(*this, d)) {
            ghosts_[i]->SetDirection(d);
            CHECK(ghosts_[i]->Move()); 
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
                break;
              }
            }
          }
        } else if (ways == 1) {
          CHECK(ghosts_[i]->CanMove(*this, oneway));
          ghosts_[i]->SetDirection(oneway);
          CHECK(ghosts_[i]->Move()) << "Ghost[" << i << "] auto move failed";
        } else if (ghosts_[i]->CanMove(*this, oppo_d)) {
          ghosts_[i]->SetDirection(oppo_d);
          CHECK(ghosts_[i]->Move());
        } else {
          // surrounded on all four sides by walls
        }
        utc_ghosts_next_moves[i] += (65 + i) * (vitality_ == 0 ? 2 : 3);
        if (FLAGS_print_ghost_move) {
	  state_changed = true;
	}
      }
    }

    // *** 2. actions
    // flight mode deactivating
    if (vitality_ > 0) {
      if (--vitality_ == 0) {
        ghost_eaten = 0;
        for (int i = 0; i < ghosts_.size(); ++i) {
          ghosts_[i]->SetVitality(0 /* standard */);
        }
      }
    }
    // fruit appearing/expiring
    for (int i = 0; i < 2; ++i) {
      if (tick_ == fruit_appears[i]) {
        fruit_appeared = true;
        fruit_remaining_ = fruit_expires[i] - tick_;
        state_changed = true;
      } else if (tick_ == fruit_expires[i]) {
        fruit_appeared = false;
        state_changed = true;
      }
    }
    if (fruit_remaining_ > 0) fruit_remaining_--;

    // *** 3. occupying
    auto pos = lman_[0]->GetRC();
    char symbol = GetSymbol(pos);
    if (symbol == '.') {
      // pill
      Eat(pos);
      score_ += 10;
      VLOG(2) << 10 << "pt by taking a pill";
      total_pills_--;
    } else if (symbol == 'o') {
      // check power pill
      Eat(pos);
      // Activates flight mode
      vitality_ = flight_mode_duration;
      // Gets all ghosts to turn around
      for (int i = 0; i < ghosts_.size(); ++i) {
        ghosts_[i]->SetVitality(1);
        ghosts_[i]->SetDirection((ghosts_[i]->GetDirection() + 2) % 4);
      }
      score_ += 50;
      VLOG(2) << 50 << "pt by taking a power pill";
    } else if (symbol == '%') {
      // check fruit
      if (fruit_appeared && fruit_location_ == pos) {
        fruit_appeared = false;
        score_ += fruit_points;
        VLOG(2) << fruit_points << "pt by taking a fruit";
      }
    }

    // *** 4. life losing
    for (int i = 0; i < ghosts_.size(); ++i) {
      if (ghosts_[i]->GetVitality() != 2 /* invisible */ && ghosts_[i]->GetRC() == pos) {
        if (vitality_ == 0) {
          // Ghost eats Lambda-Man
          // Loses a life
          life_--;
          // Resets Lambda-Man and all ghosts returned to starting positions and
          // directions
          lman_[0]->ResetPositionAndDirection();
          for (int j = 0; j < ghosts_.size(); ++j) {
            ghosts_[j]->ResetPositionAndDirection();
          }
          break;
        } else {
          // Lambda-Man eats ghost
          ghosts_[i]->ResetPositionAndDirection();
          ghosts_[i]->SetVitality(2 /* invisible */);
          score_ += kGhostPoints[ghost_eaten];
          VLOG(2) << kGhostPoints[ghost_eaten] << "pt by eating ghost" << i;
          if (ghost_eaten < 3) ghost_eaten++;
        }
      }
    }

    // *** 5. pills
    if (total_pills_ == 0) {
      VLOG(2) << "Bonus factor = " << (life_ + 1);
      score_ *= (life_ + 1);
      LOG(INFO) << "Game over: You won! (utc=" << tick_ << ")";
      break;
    }

    // *** 6. game over
    if (life_ == 0) {
      LOG(INFO) << "Game over: Lambda-Man has died (utc=" << tick_ << ")";
      break;
    }

    // *** 7. tick end
    tick_++;
  }
  LOG_IF(INFO, tick_ == end_of_lives) << "Game over: End of lives (utc=" << tick_ << ")";
  return score_;
}
