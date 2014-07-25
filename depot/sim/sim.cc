#include "sim/sim.h"
#include <algorithm>
#include <iostream>
#include <glog/logging.h>

using namespace std;

constexpr int kFruits = 2;
constexpr int kFruitPoints[14] = {0,    100,  300,  500,  500,  700,  700,
                                  1000, 1000, 2000, 2000, 3000, 3000, 5000};

void Game::ParseMaze(std::istream& is) {
  string line;
  int ghost_index = 0;
  total_pills_ = 0;
  while (true) {
    getline(is, line);
    if (line.empty() || !is.good()) break;
    CHECK(maze_.empty() || maze_.back().size() != line.size())
        << "Input maze format error";
    for (int i = 0; i < line.size(); ++i) {
      switch (line[i]) {
        case '\\':  // Lambda-Man
          lman_->Initialize(maze_.size(), i, 0);
          break;
        case '=':  // Ghost
          ghosts_.emplace_back(
              ghost_factories_[ghost_index % ghost_factories_.size()]
                  ->Create());
          ghosts_.back()->Initialize(maze_.size(), i, 0);
          ghost_index++;
          break;
        case '%':  // Fruit
          fruit_locations_.emplace_back(maze_.size(), i);
          break;
        case '.':  // Pill
          total_pills_++;
          break;
      }
    }
    maze_.push_back(line);
  }
  LOG_IF(FATAL, fruit_locations_.size() > kFruits) << "# of fruits must be "
                                                   << kFruits;
  LOG_IF(WARNING, fruit_locations_.size() < kFruits) << "# of fruits must be "
                                                     << kFruits;
}

int Game::Start() {
  // constants
  const int height = maze_.size();
  const int width = maze_[0].size();
  const int end_of_lives = 127 * width * height * 16;
  const int fruit_appears[2] = {127 * 200, 127 * 400};
  const int flight_mode_duration = 127 * 20;
  const int level = (width * height - 1) / 100 + 1;
  const int fruit_points = kFruitPoints[level <= 12 ? level : 13];

  // initlal status
  tick_ = 0;
  score_ = 0;
  life_ = 3;
  vector<bool> fruit_appeared(fruit_locations_.size(), false);
  int flight_mode = 0;  // remaining ticks
  int utc_lman_next_move = 127;
  vector<int> utc_ghosts_next_moves(ghosts_.size());
  for (int i = 0; i < ghosts_.size(); ++i)
    utc_ghosts_next_moves[i] = 130 + 2 * i;
  vector<bool> ghosts_invisible_(ghosts_.size(), false);
  // True if Lambda-Man ate something since the last move
  bool eating = false;

  // main loop
  while (tick_ < end_of_lives) {
    // *** 1. moves
    if (tick_ == utc_lman_next_move) {
      lman_->Step();
      utc_lman_next_move += eating ? 137 : 127;
      eating = false;  // Reset eating state
    }
    for (int i = 0; i < ghosts_.size(); ++i) {
      if (tick_ == utc_ghosts_next_moves[i]) {
        ghosts_[i]->Step();
        utc_ghosts_next_moves[i] += (65 + i) * (flight_mode == 0 ? 2 : 3);
      }
    }

    // *** 2. actions
    // flight mode deactivating
    if (flight_mode > 0) {
      if (--flight_mode == 0) {
        for (int i = 0; i < ghosts_.size(); ++i) {
          ghosts_invisible_[i] = false;
        }
      }
    }
    // fruit appearing
    for (int i = 0; i < kFruits; ++i) {
      if (tick_ == fruit_appears[i]) {
        fruit_appeared[i] = true;
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
      flight_mode = flight_mode_duration;
      // Gets all ghosts to turn around
      for (int i = 0; i < ghosts_.size(); ++i) {
        ghosts_[i]->SetDirection((ghosts_[i]->GetDirection() + 2) % 4);
      }
      score_ += 50;
    } else if (symbol == '%') {
      // check fruit
      for (int i = 0; i < kFruits; ++i) {
        if (fruit_appeared[i] && fruit_locations_[i] == pos) {
          fruit_appeared[i] = false;
          score_ += fruit_points;
          break;
        }
      }
    }

    // *** 4. life losing
    for (int i = 0; i < ghosts_.size(); ++i) {
      if (!ghosts_invisible_[i] && ghosts_[i]->GetRC() == pos) {
        if (flight_mode == 0) {
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
      LOG(INFO) << "Game is over: All pills have been eaten";
      break;
    }

    // *** 6. game over
    if (life_ == 0) {
      LOG(INFO) << "Game is over: Lambda-Man has died";
      break;
    }

    // *** 7. tick end
    tick_++;
  }
  return score_;
}
