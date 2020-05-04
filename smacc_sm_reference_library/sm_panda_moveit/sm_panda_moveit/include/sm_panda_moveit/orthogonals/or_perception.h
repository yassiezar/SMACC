#pragma once

#include <smacc/smacc_orthogonal.h>
#include <sm_panda_moveit/clients/perception_system_client/cl_perception_system.h>

// using namespace sm_moveit::cl_perception_system;

namespace sm_panda_moveit
{
class OrPerception : public smacc::Orthogonal<OrPerception>
{
public:
    virtual void onInitialize() override
    {
        ROS_INFO("Or perception initialization");
        auto perceptionClient = this->createClient<ClPerceptionSystem>();

        perceptionClient->peg0 = perceptionClient->createNamedComponent<cl_move_base_z::Pose>("peg0", "/peg0", "/world");

        perceptionClient->horizontalPegPlace0 = perceptionClient->createNamedComponent<cl_move_base_z::Pose>("horizontal_peg_place_0", "/horizontal_peg_place_0", "/world");
        perceptionClient->horizontalPegPlace1 = perceptionClient->createNamedComponent<cl_move_base_z::Pose>("horizontal_peg_place_1", "/horizontal_peg_place_1", "/world");
        perceptionClient->horizontalPegPlace2 = perceptionClient->createNamedComponent<cl_move_base_z::Pose>("horizontal_peg_place_2", "/horizontal_peg_place_2", "/world");

        perceptionClient->wallPegPlace0 = perceptionClient->createNamedComponent<cl_move_base_z::Pose>("wall_peg_place_0", "/wall_peg_place_0", "/world");
        perceptionClient->wallPegPlace1 = perceptionClient->createNamedComponent<cl_move_base_z::Pose>("wall_peg_place_1", "/wall_peg_place_1", "/world");
        perceptionClient->wallPegPlace2 = perceptionClient->createNamedComponent<cl_move_base_z::Pose>("wall_peg_place_2", "/wall_peg_place_2", "/world");
    }
};
} // namespace sm_panda_moveit