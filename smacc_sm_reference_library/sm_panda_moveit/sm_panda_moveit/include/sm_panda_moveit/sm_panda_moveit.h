#include <smacc/smacc.h>

// CLIENT BEHAVIORS
#include <moveit_z_client/client_behaviors.h>
#include <sm_panda_moveit/clients/move_group_client/client_behaviors/cb_panda_open_gripper.h>
#include <sm_panda_moveit/clients/move_group_client/client_behaviors/cb_panda_close_gripper.h>

// ORTHOGONALS
#include <sm_panda_moveit/orthogonals/or_gripper.h>
#include <sm_panda_moveit/orthogonals/or_arm.h>
#include <sm_panda_moveit/orthogonals/or_perception.h>

using namespace smacc;
using namespace moveit_z_client;

namespace sm_panda_moveit
{
class StInitialPosture;
namespace SS1
{
class SsPickObject;
}

struct SmPandaMoveIt
    : public smacc::SmaccStateMachineBase<SmPandaMoveIt, SS1::SsPickObject>
{
    using SmaccStateMachineBase::SmaccStateMachineBase;

    virtual void onInitialize() override
    {
        this->createOrthogonal<OrPerception>();
        this->createOrthogonal<OrArm>();
        this->createOrthogonal<OrGripper>();
    }
};

} // namespace sm_panda_moveit

#include <sm_panda_moveit/states/st_initial_posture.h>
#include <sm_panda_moveit/superstates/ss_pick_object.h>