#pragma once

#include <radial_motion.h>
#include <orthogonals/navigation_orthogonal.h>
#include <orthogonals/tool_orthogonal.h>

#include <substates_behaviors/navigation/navigate_forward.h>
#include <substates_behaviors/tool/tool_start.h>

//--------------------------------------------
/// NavigateToEndPoint State
template<typename Container>
struct NavigateToEndPoint: SmaccState<NavigateToEndPoint<Container>, Superstate<Container>>
{
  // when this state is finished move to the ReturnToRadialStart state
  typedef sc::transition<EvActionSucceded<smacc::SmaccMoveBaseActionClient::Result>, ReturnToRadialStart<Container>> reactions; 

public:
  using SmaccState<NavigateToEndPoint<Container>, Superstate<Container>>::SmaccState;

  void onInitialize()
  {
    //this->configure<NavigationOrthogonal>(new NavigateForward(3));
    
    // OPTIONAL SYNTAX
    // auto fw = new NavigateForward();
    // fw->forwardDistance = 3;
    // fw->forwardSpeed = 1;
    // this->configure<NavigationOrthogonal>(fw);
    

    //this->configure<ToolOrthogonal>(new ToolStart());
  }

  void onEntry()
  {
  }

  void onExit()
  {
  }
};
