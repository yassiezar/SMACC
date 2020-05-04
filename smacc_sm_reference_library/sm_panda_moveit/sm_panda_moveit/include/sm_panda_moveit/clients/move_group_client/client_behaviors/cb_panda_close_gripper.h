#pragma once

namespace sm_panda_moveit
{
class CbPandaCloseGripper : public moveit_z_client::CbMoveJoints
{
public:
    CbPandaCloseGripper() : CbMoveJoints({{"panda_finger_joint1", 0.0031}, {"panda_finger_joint2", 0.0031}})
    {
    }

private:
    double previousTolerance;

public:
    virtual void onEntry() override
    {
        this->requiresClient(movegroupClient_);
        auto &moveGroupInterface = movegroupClient_->moveGroupClientInterface;

        previousTolerance = moveGroupInterface.getGoalJointTolerance();

        moveGroupInterface.setGoalJointTolerance(0.0001);
        moveit_z_client::CbMoveJoints::onEntry();
    }

    virtual void onExit() override
    {

        auto &moveGroupInterface = movegroupClient_->moveGroupClientInterface;
        moveGroupInterface.setGoalJointTolerance(previousTolerance);

        moveit_z_client::CbMoveJoints::onExit();
    }
};

} // namespace sm_panda_moveit
