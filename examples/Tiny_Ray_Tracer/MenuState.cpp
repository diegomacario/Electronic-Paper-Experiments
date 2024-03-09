#include <algorithm>

#include "MenuState.h"

MenuState::MenuState(const std::shared_ptr<FiniteStateMachine>& finiteStateMachine,
                     LilyGo_Class* amoled,
                     TFT_eSPI& tft,
                     uint16_t screenWidth,
                     uint16_t screenHeight)
   : mFSM(finiteStateMachine)
   , mAmoled(amoled)
   , mScreenWidth(screenWidth)
   , mScreenHeight(screenHeight)
   , mNumRows(4)
   , mNumColumns(2)
   , mCellHorizontalMargin(10)
   , mCellVerticalMargin(10)
   , mCellHorizontalPadding(10)
   , mCellVerticalPadding(2)
   , mCellWidth((mScreenWidth - (mCellHorizontalMargin * (mNumColumns + 1))) * (1.0f / mNumColumns))
   , mCellHeight((mScreenHeight - (mCellVerticalMargin * (mNumRows + 1))) * (1.0f / mNumRows))
   , mCellRadius(20)
   , mCurrentCellIndex(0)
   , mNextSceneButtonPin(2)
   , mNextSceneButtonState(LOW)
   , mLastNextSceneButtonState(LOW)
   , mLastNextSceneButtonDebounceTime(0)
   , mNextSceneButtonDebounceDelay(50)
   , mSelectSceneButtonPin(1)
   , mSelectSceneButtonState(LOW)
   , mLastSelectSceneButtonState(LOW)
   , mLastSelectSceneButtonDebounceTime(0)
   , mSelectSceneButtonDebounceDelay(50)
   , mResetScreenSprite(&tft)
{
   std::vector<std::string> cellLabels = {"Sword", "Rupee", "Castle", "Planet", "Ice Cream", "Pyramid", "Spheres", "Cake"};

   std::vector<std::string>::iterator longestLabel = std::max_element(cellLabels.begin(), cellLabels.end(), [](const std::string& a, const std::string& b) {
    return a.size() < b.size();
   });

   int32_t longestLabelLength = (*longestLabel).length();

   int32_t fontWidth = 6;
   // The font has a height of 8 pixels, but the last pixel corresponds to an empty line to separate letters vertically
   // We ignore that last empty line to center the text correctly
   int32_t fontHeight = 8 - 1;
   mFontSize = 1;
   int32_t longestLabelWidth = fontWidth * mFontSize * longestLabelLength;
   int32_t longestLabelHeight = fontHeight * mFontSize;

   int32_t maxTextWidth = mCellWidth - (mCellHorizontalPadding * 2);
   int32_t maxTextHeight = mCellHeight - (mCellVerticalPadding * 2);

   while (longestLabelWidth < maxTextWidth && longestLabelHeight < maxTextHeight && mFontSize < 7) {
      mFontSize++;
      longestLabelWidth = fontWidth * mFontSize * longestLabelLength;
      longestLabelHeight = fontHeight * mFontSize;

      // If the new dimensions exceed the cell size, revert mFontSize and calculate the dimensions again
      if (longestLabelWidth > maxTextWidth || longestLabelHeight > maxTextHeight) {
         mFontSize--;
         longestLabelWidth = fontWidth * mFontSize * longestLabelLength;
         longestLabelHeight = fontHeight * mFontSize;
         break;
      }
   }

   int32_t cellIndex = 0;
   for (int32_t columnIndex = 0; columnIndex < mNumColumns; ++columnIndex) {
      for (int32_t rowIndex = 0; rowIndex < mNumRows; ++rowIndex) {
         int32_t xPos = mCellHorizontalMargin + ((mCellWidth + mCellHorizontalMargin) * columnIndex);
         int32_t yPos = mCellVerticalMargin + ((mCellHeight + mCellVerticalMargin) * rowIndex);

         int32_t textXPos = mCellHorizontalPadding;
         int32_t textYPos = mCellVerticalPadding;
         int32_t gap = (maxTextHeight - longestLabelHeight) * 0.5f;
         textYPos += gap;

         mCells.push_back(Cell(xPos, yPos, cellLabels[cellIndex], textXPos, textYPos));
         mCellSprites.emplace_back(&tft);
         cellIndex += 1;
      }
   }
}

void MenuState::enter()
{
   mResetScreenSprite.createSprite(mScreenWidth, mScreenHeight);
   mResetScreenSprite.fillSprite(TFT_BLACK);
   mAmoled->pushColors(0, 0, mScreenWidth, mScreenHeight, (uint16_t *)mResetScreenSprite.getPointer());
   mResetScreenSprite.deleteSprite();

   for (int32_t cellIndex = 0; cellIndex < mCells.size(); ++cellIndex) {
      mCellSprites[cellIndex].createSprite(static_cast<uint16_t>(mCellWidth), static_cast<uint16_t>(mCellHeight));

      if (cellIndex == mCurrentCellIndex) {
         mCellSprites[cellIndex].fillSprite(TFT_WHITE);
         mCellSprites[cellIndex].setTextColor(TFT_BLACK);
      } else {
         mCellSprites[cellIndex].fillSprite(TFT_BLACK);
         mCellSprites[cellIndex].setTextColor(TFT_WHITE);
      }

      mCellSprites[cellIndex].setTextSize(mFontSize);
      mCellSprites[cellIndex].setTextFont(1);

      //mCellSprites[cellIndex].drawRoundRect(0, 0, static_cast<int32_t>(mCellWidth), static_cast<int32_t>(mCellHeight), mCellRadius, TFT_WHITE);
      mCellSprites[cellIndex].drawRect(0, 0, static_cast<int32_t>(mCellWidth), static_cast<int32_t>(mCellHeight), TFT_WHITE);
      mCellSprites[cellIndex].drawString(mCells[cellIndex].mText.c_str(), mCells[cellIndex].mTextXPos, mCells[cellIndex].mTextYPos);
      mAmoled->pushColors(mCells[cellIndex].mXPos, mCells[cellIndex].mYPos, static_cast<uint16_t>(mCellWidth), static_cast<uint16_t>(mCellHeight), (uint16_t *)mCellSprites[cellIndex].getPointer());
   }

   pinMode(mNextSceneButtonPin, INPUT_PULLDOWN);
   pinMode(mSelectSceneButtonPin, INPUT_PULLDOWN);
}

void MenuState::update()
{
   bool nextSceneButtonIsPressed = checkNextSceneButton();
   if (nextSceneButtonIsPressed) {
      // Make the current cell black with white text
      mCellSprites[mCurrentCellIndex].fillSprite(TFT_BLACK);
      mCellSprites[mCurrentCellIndex].setTextColor(TFT_WHITE);
      mCellSprites[mCurrentCellIndex].drawRect(0, 0, static_cast<int32_t>(mCellWidth), static_cast<int32_t>(mCellHeight), TFT_WHITE);
      mCellSprites[mCurrentCellIndex].drawString(mCells[mCurrentCellIndex].mText.c_str(), mCells[mCurrentCellIndex].mTextXPos, mCells[mCurrentCellIndex].mTextYPos);

      mAmoled->pushColors(mCells[mCurrentCellIndex].mXPos, mCells[mCurrentCellIndex].mYPos, static_cast<uint16_t>(mCellWidth), static_cast<uint16_t>(mCellHeight), (uint16_t *)mCellSprites[mCurrentCellIndex].getPointer());

      ++mCurrentCellIndex;
      mCurrentCellIndex %= mCells.size();

      // Make the selected cell white with black text
      mCellSprites[mCurrentCellIndex].fillSprite(TFT_WHITE);
      mCellSprites[mCurrentCellIndex].setTextColor(TFT_BLACK);
      mCellSprites[mCurrentCellIndex].drawRect(0, 0, static_cast<int32_t>(mCellWidth), static_cast<int32_t>(mCellHeight), TFT_WHITE);
      mCellSprites[mCurrentCellIndex].drawString(mCells[mCurrentCellIndex].mText.c_str(), mCells[mCurrentCellIndex].mTextXPos, mCells[mCurrentCellIndex].mTextYPos);

      mAmoled->pushColors(mCells[mCurrentCellIndex].mXPos, mCells[mCurrentCellIndex].mYPos, static_cast<uint16_t>(mCellWidth), static_cast<uint16_t>(mCellHeight), (uint16_t *)mCellSprites[mCurrentCellIndex].getPointer());
   }

   bool selectSceneButtonIsPressed = checkSelectSceneButton();
   if (selectSceneButtonIsPressed) {
      // Make the selected cell green with white text
      mCellSprites[mCurrentCellIndex].fillSprite(TFT_GREEN);
      mCellSprites[mCurrentCellIndex].setTextColor(TFT_WHITE);
      mCellSprites[mCurrentCellIndex].drawRect(0, 0, static_cast<int32_t>(mCellWidth), static_cast<int32_t>(mCellHeight), TFT_WHITE);
      mCellSprites[mCurrentCellIndex].drawString(mCells[mCurrentCellIndex].mText.c_str(), mCells[mCurrentCellIndex].mTextXPos, mCells[mCurrentCellIndex].mTextYPos);

      mAmoled->pushColors(mCells[mCurrentCellIndex].mXPos, mCells[mCurrentCellIndex].mYPos, static_cast<uint16_t>(mCellWidth), static_cast<uint16_t>(mCellHeight), (uint16_t *)mCellSprites[mCurrentCellIndex].getPointer());

      delay(500);

      mFSM->changeState("play");
      return;
   }
}

void MenuState::exit()
{
   for (int32_t cellIndex = 0; cellIndex < mCells.size(); ++cellIndex) {
      mCellSprites[cellIndex].deleteSprite();
   }
}

bool MenuState::checkNextSceneButton()
{
   bool nextSceneButtonIsPressed = false;

   int reading = digitalRead(mNextSceneButtonPin);

   if (reading != mLastNextSceneButtonState) {
      // Reset the debouncing timer
      mLastNextSceneButtonDebounceTime = millis();
   }

   if ((millis() - mLastNextSceneButtonDebounceTime) > mNextSceneButtonDebounceDelay) {
      // Whatever the reading is at, it's been there for longer than the debounce delay,
      // so take it as the actual current state

      // If the button state has changed
      if (reading != mNextSceneButtonState) {
         mNextSceneButtonState = reading;

         // If the new state of the button is HIGH
         if (mNextSceneButtonState == HIGH) {
            nextSceneButtonIsPressed = true;
         }
      }
   }

   mLastNextSceneButtonState = reading;

   return nextSceneButtonIsPressed;
}

bool MenuState::checkSelectSceneButton()
{
   bool selectSceneButtonIsPressed = false;

   int reading = digitalRead(mSelectSceneButtonPin);

   if (reading != mLastSelectSceneButtonState) {
      // Reset the debouncing timer
      mLastSelectSceneButtonDebounceTime = millis();
   }

   if ((millis() - mLastSelectSceneButtonDebounceTime) > mSelectSceneButtonDebounceDelay) {
      // Whatever the reading is at, it's been there for longer than the debounce delay,
      // so take it as the actual current state

      // If the button state has changed
      if (reading != mSelectSceneButtonState) {
         mSelectSceneButtonState = reading;

         // If the new state of the button is HIGH
         if (mSelectSceneButtonState == HIGH) {
            selectSceneButtonIsPressed = true;
         }
      }
   }

   mLastSelectSceneButtonState = reading;

   return selectSceneButtonIsPressed;
}
