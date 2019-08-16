#pragma once

#include <smacc/smacc.h>

template <typename Container>
class NavigateToRadialStart;

template <typename Container>
class RotateDegress;

template <typename Container>
class NavigateToEndPoint;

template <typename Container>
class ReturnToRadialStart;

template <typename Container>
class Superstate;

#include <states/navigate_superstate.h>
// ----- Radial Motion State Machine --------------

// create the RadialMotion State Machine example class that inherits from the 
// SmaccStateMachineBase. You only have to declare it, the most of the funcionality is inhterited.
struct RadialMotionStateMachine
    : public smacc::SmaccStateMachineBase<RadialMotionStateMachine,Superstate<RadialMotionStateMachine>> 
{
    RadialMotionStateMachine(my_context ctx, smacc::SignalDetector *signalDetector);
};

