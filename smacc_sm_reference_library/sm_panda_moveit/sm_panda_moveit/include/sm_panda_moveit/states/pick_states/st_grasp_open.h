
#pragma once
namespace sm_panda_moveit
{
namespace pick_states
{
// STATE DECLARATION
struct StGraspOpen : smacc::SmaccState<StGraspOpen, SS>
{
    using SmaccState::SmaccState;

    // TRANSITION TABLE
    typedef mpl::list<
        Transition<MoveGroupMotionExecutionSucceded<ClMoveGroup, OrGripper>, StGraspApproach, SUCCESS>,
        Transition<MoveGroupMotionExecutionFailed<ClMoveGroup, OrGripper>, StGraspOpen, ABORT> /*retry on failure*/
        >
        reactions;

    // STATE FUNCTIONS
    static void staticConfigure()
    {
        configure_orthogonal<OrGripper, CbPandaOpenGripper>();
    }

    void runtimeConfigure()
    {
    }
};
} // namespace pick_states
} // namespace sm_panda_moveit