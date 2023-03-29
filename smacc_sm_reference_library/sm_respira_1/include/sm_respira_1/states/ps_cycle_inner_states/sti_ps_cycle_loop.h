namespace sm_respira_1
{
namespace ps_cycle_inner_states
{
// STATE DECLARATION
struct StiPSCycleLoop : smacc::SmaccState<StiPSCycleLoop, SsPSCycle>
{
public:
  using SmaccState::SmaccState;

// TRANSITION TABLE
  typedef mpl::list<

  Transition<EvLoopContinue<StiPSCycleLoop>, StiPSCycleInspire, CONTINUELOOP>

  >reactions;

// STATE FUNCTIONS
  static void staticConfigure()
  {
  }

  void runtimeConfigure()
  {
  }

  bool loopWhileCondition()
  {
    auto &superstate = this->context<SsPSCycle>();

    ROS_INFO("Loop start, current iterations: %d, total iterations: %d", superstate.iteration_count, superstate.total_iterations());
    return superstate.iteration_count++ < superstate.total_iterations();
  }

  void onEntry()
  {
    ROS_INFO("LOOP START ON ENTRY");
    checkWhileLoopConditionAndThrowEvent(&StiPSCycleLoop::loopWhileCondition);
  }
};
}
}
