#include <smacc/smacc.h>

namespace sm_atomic_sync {

template <typename TSource, typename TOrthogonal>
struct EvEvent : sc::event<EvEvent<TSource, TOrthogonal>> {};

struct State1 : smacc::SmaccState<State1, SmAtomicSync> {
  using SmaccState::SmaccState;

  // TRANSITION TABLE
  typedef mpl::list<Transition<EvEvent<ClClient1, OrOrthogonal1>, State1,
                               smacc::default_transition_tags::SUCCESS>>
      reactions;

  // STATE FUNCTIONS
  static void staticConfigure() {}

  void runtimeConfigure() {}
  void onEntry() { ROS_INFO("On Entry!"); }
  void onExit() { ROS_INFO("On Exit!"); }
};
}  // namespace sm_atomic_sync