namespace sm_three_some
{
// STATE DECLARATION
struct StState1 : smacc::SmaccState<StState1, MsRun>
{
    using SmaccState::SmaccState;

// DECLARE CUSTOM OBJECT TAGS
    struct TIMEOUT : SUCCESS{};
    struct NEXT : SUCCESS{};
    struct PREVIOUS : ABORT{};


// TRANSITION TABLE
    typedef mpl::list<

    Transition<EvTimer<CbTimerCountdownOnce, OrTimer>, StState2, TIMEOUT>,
    // Keyboard events
    Transition<EvKeyPressP<CbDefaultKeyboardBehavior, OrKeyboard>, SS1::Ss1, PREVIOUS>,
    Transition<EvKeyPressN<CbDefaultKeyboardBehavior, OrKeyboard>, StState2, NEXT>,
    Transition<EvFail, MsRecover, smacc::ABORT>

    >reactions;

// STATE FUNCTIONS
    static void staticConfigure()
    {
        configure_orthogonal<OrTimer, CbTimerCountdownOnce>(10);
        configure_orthogonal<OrSubscriber, CbWatchdogSubscriberBehavior>();
        configure_orthogonal<OrUpdatablePublisher, CbDefaultPublishLoop>();
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
} // namespace sm_three_some
