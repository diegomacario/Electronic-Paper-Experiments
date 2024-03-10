#ifndef PLAY_STATE_H
#define PLAY_STATE_H

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

   void generateNoise(int quadrantIndex);

   std::shared_ptr<FiniteStateMachine> mFSM;

   const uint16_t                      mScreenWidth;
   const uint16_t                      mScreenHeight;

   uint8_t*                            mImageRenderingFramebuffer;
   uint8_t*                            mNoiseFramebuffer;

   std::unique_ptr<FileParser>         mFileParser;
   std::unique_ptr<SceneDescription>   mSceneDesc;
   std::unique_ptr<Scene>              mScene;
   RandomSampleGenerator               mSampleGenerator;
   RayGenerator                        mRayGenerator;
   Sample                              mSample;
   Ray                                 mRay;
   Intersection                        mIntersection;

   int                                 mQuadrantIndex;

   bool                                mGenerateCoordinatesOfQuadrants;
   bool                                mGenerateNoiseOfQuadrants;
};

#endif
