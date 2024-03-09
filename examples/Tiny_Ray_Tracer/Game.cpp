#include "Game.h"
#include "MenuState.h"
#include "PlayState.h"

Game::Game()
   : mMenuState()
   , mPlayState()
   , mFSM()
{

}

void Game::initialize(LilyGo_Class* amoled, TFT_eSPI& tft, uint16_t screenWidth, uint16_t screenHeight)
{
   // Create the FSM
   mFSM = std::make_shared<FiniteStateMachine>();

   // Initialize the states
   std::unordered_map<std::string, std::shared_ptr<State>> mStates;

   mMenuState = std::make_shared<MenuState>(mFSM, amoled, tft, screenWidth, screenHeight);
   mPlayState = std::make_shared<PlayState>(mFSM, amoled, tft, screenWidth, screenHeight);

   mStates["menu"] = mMenuState;
   mStates["play"] = mPlayState;

   // Initialize the FSM
   mFSM->initialize(std::move(mStates), "menu");
}

void Game::update()
{
   mFSM->updateCurrentState();
}
