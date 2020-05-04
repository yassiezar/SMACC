#pragma once

#include <smacc/smacc_orthogonal.h>
#include <moveit_z_client/cl_movegroup.h>

namespace sm_panda_moveit
{
using namespace moveit_z_client;
class OrArm : public smacc::Orthogonal<OrArm>
{
public:
    virtual void onInitialize() override
    {
        auto moveGroupClient = this->createClient<ClMoveGroup>("panda_arm");
        //auto moveGroupClient = this->createClient<ClMoveGroup>("panda_arm_hand");
        moveGroupClient->initialize();
    }
};
} // namespace sm_panda_moveit