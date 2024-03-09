#include <string>
#include <iostream>

#include "FSM.h"

void FiniteStateMachine::initialize(std::unordered_map<std::string, std::shared_ptr<State>>&& states,
                                    const std::string&                                        initialStateID)
{
   mStates = std::move(states);

   auto it = mStates.find(initialStateID);
   if (it != mStates.end())
   {
      mCurrentState    = it->second;
      mPreviousStateID = initialStateID;
      mCurrentStateID  = initialStateID;
      mCurrentState->enter();
   }
   else
   {
      std::cout << "Error - FiniteStateMachine::FiniteStateMachine - A state with the following ID does not exist: " << initialStateID << "\n";
   }
}

void FiniteStateMachine::updateCurrentState() const
{
   mCurrentState->update();
}

void FiniteStateMachine::changeState(const std::string& newStateID)
{
   auto it = mStates.find(newStateID);
   if (it != mStates.end())
   {
      mPreviousStateID = mCurrentStateID;
      mCurrentStateID  = newStateID;

      mCurrentState->exit();
      mCurrentState = it->second;
      mCurrentState->enter();
   }
   else
   {
      std::cout << "Error - FiniteStateMachine::changeState - A state with the following ID does not exist: " << newStateID << "\n";
   }
}

std::shared_ptr<State> FiniteStateMachine::getPreviousState()
{
   return mStates[mPreviousStateID];
}

std::string FiniteStateMachine::getPreviousStateID() const
{
   return mPreviousStateID;
}

std::string FiniteStateMachine::getCurrentStateID() const
{
   return mCurrentStateID;
}
