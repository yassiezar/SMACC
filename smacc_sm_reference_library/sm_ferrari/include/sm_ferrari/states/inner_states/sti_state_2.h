namespace sm_ferrari
{
namespace inner_states
{
// STATE DECLARATION
struct StiState2 : smacc::SmaccState<StiState2, SS>
{
  using SmaccState::SmaccState;

// DECLARE CUSTOM OBJECT TAGS
  struct TIMEOUT : SUCCESS{};
  struct NEXT : SUCCESS{};
  struct PREVIOUS : ABORT{};

// TRANSITION TABLE
  typedef mpl::list<

  //Transition<EvTimer<CbTimerCountdownOnce, OrTimer>, StiState3, TIMEOUT>,
  Transition<EvKeyPressN<CbDefaultKeyboardBehavior, OrKeyboard>, StiState3, NEXT>,
  Transition<EvKeyPressP<CbDefaultKeyboardBehavior, OrKeyboard>, StiState1, PREVIOUS>,
  Transition<EvMyBehavior<CbMySubscriberBehavior, OrSubscriber>, StiState3, NEXT>

  >reactions;

  // STATE FUNCTIONS
  static void staticConfigure()
  {
    // configure_orthogonal<OrTimer, CbTimerCountdownOnce>(10);
    // configure_orthogonal<OrSubscriber, CbWatchdogSubscriberBehavior>();
    configure_orthogonal<OrSubscriber, CbMySubscriberBehavior>();
    // configure_orthogonal<OrUpdatablePublisher, CbDefaultPublishLoop>();
     configure_orthogonal<OrKeyboard, CbDefaultKeyboardBehavior>();
  }

  void runtimeConfigure()
  {
  }

  void onEntry()
  {
    ROS_INFO("On Entry!");
  }

  void onExit()
  {
    ROS_INFO("On Exit!");
  }

};
}
}
