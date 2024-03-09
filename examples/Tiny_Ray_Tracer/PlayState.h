#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <LilyGo_AMOLED.h>
#include <TFT_eSPI.h>

#include "State.h"
#include "FSM.h"
#include "FileParser.h"
#include "RandomSampleGenerator.h"
#include "RayGenerator.h"
#include "SceneDescription.h"
#include "TextSpriteSettings.h"

class PlayState : public State
{
public:

   PlayState(const std::shared_ptr<FiniteStateMachine>& finiteStateMachine,
             LilyGo_Class* amoled,
             TFT_eSPI& tft,
             uint16_t screenWidth,
             uint16_t screenHeight);
   ~PlayState() = default;

   PlayState(const PlayState&) = delete;
   PlayState& operator=(const PlayState&) = delete;

   PlayState(PlayState&&) = delete;
   PlayState& operator=(PlayState&&) = delete;

   void enter() override;
   void update() override;
   void exit() override;

private:

   bool checkCancelRenderButton();
   void updateRayTracingSprite();
   void updatePercentageProgressSprite(float progress);
   void updateProgressBar(float progress);

   std::shared_ptr<FiniteStateMachine> mFSM;

   LilyGo_Class*                       mAmoled;

   const uint16_t                      mScreenWidth;
   const uint16_t                      mScreenHeight;

   TFT_eSprite                         mImageRenderingSprite;

   TFT_eSprite                         mRayTracingLabelSprite;
   TFT_eSprite                         mRayTracingLabelBackgroundSprite;
   TFT_eSprite                         mRayTracingLabelMixedSprite;

   TFT_eSprite                         mPercentageProgressLabelSprite;
   TFT_eSprite                         mPercentageProgressLabelBackgroundSprite;
   TFT_eSprite                         mPercentageProgressLabelMixedSprite;

   TFT_eSprite                         mProgressBarSprite;
   TFT_eSprite                         mProgressBarBackgroundSprite;
   TFT_eSprite                         mProgressBarMixedSprite;

   std::unique_ptr<FileParser>         mFileParser;
   std::unique_ptr<SceneDescription>   mSceneDesc;
   std::unique_ptr<Scene>              mScene;
   RandomSampleGenerator               mSampleGenerator;
   RayGenerator                        mRayGenerator;
   Sample                              mSample;
   Ray                                 mRay;
   Intersection                        mIntersection;

   TextSpriteSettings                  mRayTracingSpriteSettings;
   uint32_t                            mNumDots;
   unsigned long                       mLastTimeRayTracingSpriteWasUpdated;
   bool                                mRayTracingLabelBackgroundSpriteChanged;

   TextSpriteSettings                  mPercentageProgressSpriteSettings;

   const int32_t                       mProgressBarWidth;
   const int32_t                       mProgressBarHeight;
   const int32_t                       mProgressBarXPosition;
   const int32_t                       mProgressBarYPosition;
   const int32_t                       mProgressBarFillableWidth;
   const int32_t                       mProgressBarFillableHeight;
   int32_t                             mPrevProgressWidth;

   bool                                mDoOnce;

   const int                           mCancelRenderButtonPin;
   int                                 mCancelRenderButtonState;
   int                                 mLastCancelRenderButtonState;
   unsigned long                       mLastCancelRenderButtonDebounceTime;
   unsigned long                       mCancelRenderButtonDebounceDelay;
};

#endif
