#include <smacc/smacc.h>
namespace sm_dance_bot_2
{
// STATE DECLARATION
struct StRotateDegrees6 : smacc::SmaccState<StRotateDegrees6, MsDanceBotRunMode>
{
  using SmaccState::SmaccState;

// TRANSITION TABLE
  typedef mpl::list<

  Transition<EvCbSuccess<CbRotate, OrNavigation>, StNavigateReverse3>,
  Transition<EvCbFailure<CbRotate, OrNavigation>, StNavigateToWaypointsX>

  >reactions;

// STATE FUNCTIONS
  static void staticConfigure()
  {
    configure_orthogonal<OrNavigation, CbRotate>(/*30*/ -180);
    configure_orthogonal<OrLED, CbLEDOff>();
    configure_orthogonal<OrObstaclePerception, CbLidarSensor>();
  }
};
}
