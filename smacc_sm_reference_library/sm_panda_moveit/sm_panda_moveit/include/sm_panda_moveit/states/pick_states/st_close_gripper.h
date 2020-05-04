#pragma once

namespace sm_panda_moveit
{
namespace pick_states
{
// STATE DECLARATION
struct StCloseGripper : smacc::SmaccState<StCloseGripper, SS>
{
   using SmaccState::SmaccState;

   // TRANSITION TABLE
   typedef mpl::list<
           Transition<MoveGroupMotionExecutionSucceded<ClMoveGroup, OrGripper>, StGraspRetreat, SUCCESS>,
           Transition<MoveGroupMotionExecutionFailed<ClMoveGroup, OrGripper>, StCloseGripper, ABORT> /*retry on failure*/>
       reactions;

   // STATE FUNCTIONS
   static void staticConfigure()
   {
      configure_orthogonal<OrGripper, CbPandaCloseGripper>();
   }

   void onExit()
   {
      ClMoveGroup *moveGroupClient;
      this->requiresClient(moveGroupClient);

      ros::Duration(0.5).sleep();
   }
};
} // namespace pick_states
} // namespace sm_panda_moveit