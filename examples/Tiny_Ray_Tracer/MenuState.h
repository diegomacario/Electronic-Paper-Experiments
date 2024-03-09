#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <vector>

#include <LilyGo_AMOLED.h>
#include <TFT_eSPI.h>

#include "State.h"
#include "FSM.h"
#include "Cell.h"

class MenuState : public State
{
public:

   MenuState(const std::shared_ptr<FiniteStateMachine>& finiteStateMachine,
             LilyGo_Class* amoled,
             TFT_eSPI& tft,
             uint16_t screenWidth,
             uint16_t screenHeight);
   ~MenuState() = default;

   MenuState(const MenuState&) = delete;
   MenuState& operator=(const MenuState&) = delete;

   MenuState(MenuState&&) = delete;
   MenuState& operator=(MenuState&&) = delete;

   void enter() override;
   void update() override;
   void exit() override;

   int32_t getCurrentCellIndex() { return mCurrentCellIndex; };

private:

   bool checkNextSceneButton();
   bool checkSelectSceneButton();

   std::shared_ptr<FiniteStateMachine> mFSM;

   LilyGo_Class*                       mAmoled;

   const uint16_t                      mScreenWidth;
   const uint16_t                      mScreenHeight;

   int32_t                             mNumRows;
   int32_t                             mNumColumns;

   int32_t                             mCellHorizontalMargin;
   int32_t                             mCellVerticalMargin;
   int32_t                             mCellHorizontalPadding;
   int32_t                             mCellVerticalPadding;

   int32_t                             mCellWidth;
   int32_t                             mCellHeight;
   int32_t                             mCellRadius;

   std::vector<Cell>                   mCells;
   std::vector<TFT_eSprite>            mCellSprites;
   int32_t                             mCurrentCellIndex;

   int32_t                             mFontSize;

   const int                           mNextSceneButtonPin;
   int                                 mNextSceneButtonState;
   int                                 mLastNextSceneButtonState;
   unsigned long                       mLastNextSceneButtonDebounceTime;
   unsigned long                       mNextSceneButtonDebounceDelay;

   const int                           mSelectSceneButtonPin;
   int                                 mSelectSceneButtonState;
   int                                 mLastSelectSceneButtonState;
   unsigned long                       mLastSelectSceneButtonDebounceTime;
   unsigned long                       mSelectSceneButtonDebounceDelay;

   TFT_eSprite                         mResetScreenSprite;
};

#endif
