#ifndef GAME_H
#define GAME_H

#include "PlayState.h"
#include "FSM.h"

class Game
{
public:

   Game();
   ~Game() = default;

   Game(const Game&) = delete;
   Game& operator=(const Game&) = delete;

   Game(Game&&) = delete;
   Game& operator=(Game&&) = delete;

   void  initialize(uint16_t screenWidth, uint16_t screenHeight);
   void  update();

private:

   std::shared_ptr<PlayState>          mPlayState;

   std::shared_ptr<FiniteStateMachine> mFSM;
};

#endif
