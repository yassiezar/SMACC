#include <smacc/smacc.h>

namespace sm_panda_moveit
{
namespace SS1
{
namespace sm_panda_moveit
{
namespace pick_states
{

//FORWARD DECLARATION OF INNER STATES
class StCloseGripper;
class StGraspApproach;
class StGraspRetreat;
class StMovePregraspPose;
} // namespace pick_states
} // namespace sm_panda_moveit

using namespace sm_panda_moveit::pick_states;

// STATE DECLARATION
struct SsPickObject : smacc::SmaccState<SsPickObject, SmPandaMoveIt, StMovePregraspPose>
{
public:
    using SmaccState::SmaccState;

    // TRANSITION TABLE
    typedef mpl::list<>
        reactions;

    // STATE FUNCTIONS
    static void staticConfigure()
    {
        //configure_orthogonal<OrObstaclePerception, CbLidarSensor>();
    }

    void runtimeConfigure()
    {
        ROS_INFO("picking object superstate");
        ClMoveGroup *movegroupClient;
        this->requiresClient(movegroupClient);
    }
};

// FORWARD DECLARATION FOR THE SUPERSTATE
using SS = SsPickObject;
#include <sm_panda_moveit/states/pick_states/st_close_gripper.h>
#include <sm_panda_moveit/states/pick_states/st_grasp_open.h>

#include <sm_panda_moveit/states/pick_states/st_grasp_approach.h>
#include <sm_panda_moveit/states/pick_states/st_grasp_retreat.h>
#include <sm_panda_moveit/states/pick_states/st_move_pregrasp_pose.h>
} // namespace SS1
} // namespace sm_panda_moveit