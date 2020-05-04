#pragma once
namespace sm_panda_moveit
{
namespace pick_states
{
// STATE DECLARATION
struct StMovePregraspPose : smacc::SmaccState<StMovePregraspPose, SS>
{
    using SmaccState::SmaccState;

    // TRANSITION TABLE
    typedef mpl::list<

        Transition<MoveGroupMotionExecutionSucceded<ClMoveGroup, OrArm>, StGraspOpen, SUCCESS>,
        Transition<MoveGroupMotionExecutionFailed<ClMoveGroup, OrArm>, StMovePregraspPose, ABORT> /*retry on failure*/
        >
        reactions;

    // STATE FUNCTIONS
    static void staticConfigure()
    {
        configure_orthogonal<OrArm, CbMoveEndEffector>();
        // configure_orthogonal<OrGripper, CbPandaOpenGripper>();
    }

    void runtimeConfigure()
    {
        ROS_INFO("Pre grasp pose initialization.");
        ros::WallDuration(5).sleep();

        ClPerceptionSystem *perceptionSystem;
        this->requiresClient(perceptionSystem);

        auto pregraspPose = perceptionSystem->decidePegPose();

        auto moveAbsolute = this->getOrthogonal<OrArm>()
                                ->getClientBehavior<CbMoveEndEffector>();

        pregraspPose.pose.position.z += 0.2;

        tf::Quaternion q;
        q.setRPY(M_PI, 0, 0);

        tf::quaternionTFToMsg(q, pregraspPose.pose.orientation);

        moveAbsolute->targetPose = pregraspPose;
        moveAbsolute->tip_link_ = "panda_link8";
    }
};
} // namespace pick_states
} // namespace sm_panda_moveit