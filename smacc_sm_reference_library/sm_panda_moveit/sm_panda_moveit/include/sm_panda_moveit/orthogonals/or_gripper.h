#pragma once

#include <smacc/smacc_orthogonal.h>

namespace sm_panda_moveit
{
using namespace moveit_z_client;
class OrGripper : public smacc::Orthogonal<OrGripper>
{
public:
    virtual void onInitialize() override
    {
        auto moveGroupClient = this->createClient<ClMoveGroup>("hand");
        moveGroupClient->initialize();
    }
};
} // namespace sm_panda_moveit
