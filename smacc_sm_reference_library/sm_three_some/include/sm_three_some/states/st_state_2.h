namespace sm_three_some
{
struct StState2 : smacc::SmaccState<StState2, SmThreeSome>
{
    using SmaccState::SmaccState;

    typedef mpl::list<
        smacc::transition<smacc::EvActionSucceeded<Client2>, SS1::Ss1>,
        smacc::transition<EvAll<LuAllEventsGo>, StState1>>
        reactions;

    static void onDefinition()
    {
        static_configure<Orthogonal1, SbBehavior1b>();
        static_configure<Orthogonal2, SbBehavior2b>();
        static_configure<KeyboardOrthogonal, SbKeyboard>();

        static_createLogicUnit<LuAllEventsGo, EvAll<LuAllEventsGo>, mpl::list<EvTopicMessage<SbBehavior1b>, EvTopicMessage<Client1>>>();
    }

    void onInitialize()
    {
    }
};
} // namespace sm_three_some