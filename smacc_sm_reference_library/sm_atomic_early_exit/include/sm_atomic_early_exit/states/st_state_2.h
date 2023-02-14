#include <smacc/smacc.h>

namespace sm_atomic_early_exit {
// STATE DECLARATION

struct State2 : smacc::SmaccState<State2, SmAtomicEarlyExit> {
  using SmaccState::SmaccState;

  // TRANSITION TABLE
  typedef mpl::list<
      Transition<EvTimer<CbTimerCountdownOnce, OrTimer>, State1, SUCCESS> >
      reactions;

  // STATE FUNCTIONS
  static void staticConfigure() {
    configure_orthogonal<OrTimer, CbTimerCountdownOnce>(
        5);  // EvTimer triggers once at 10 client ticks
    configure_orthogonal<OrExample, CbExamplePub>(0.02);
    configure_orthogonal<OrExample, CbExampleSub>();
  }

  void runtimeConfigure() { ROS_INFO("Entering State2"); }

  void onEntry() { ROS_INFO("On Entry!"); }

  void onExit() { ROS_INFO("On Exit!"); }
};
}  // namespace sm_atomic_early_exit
