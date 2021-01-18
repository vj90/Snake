#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include <string>

#include "SDL.h"
#include "controller.h"
#include "food.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::unique_ptr<Renderer>& renderer,
       std::unique_ptr<Controller>& controller);
  void Run(std::size_t target_frame_duration);
  const int GetScore() const;
  const int GetSize() const;
  void Menu(Controller::ControllerOutput& game_state);
  void ShowMenuOptions(bool saved_game_available) const;
  void Reset();

 private:
  Snake _snake;
  Food _food;
  std::unique_ptr<Renderer> _renderer{nullptr};
  std::unique_ptr<Controller> _controller{nullptr};

  int _score{0};
  int _last_high_score{0};

  void PlaceFood();
  void Update();
  void Save();
  void ReadHighScore();
  void LoadSavedGame();
  std::string _game_file{"saved_game.txt"};
  std::string _high_score_file{"high_score.txt"};
};

#endif