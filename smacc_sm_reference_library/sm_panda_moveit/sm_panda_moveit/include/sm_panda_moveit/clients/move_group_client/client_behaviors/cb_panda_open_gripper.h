#pragma once

namespace sm_panda_moveit
{
class CbPandaOpenGripper : public moveit_z_client::CbMoveJoints
{
private:
    double previousTolerance;

public:
    CbPandaOpenGripper() : CbMoveJoints({{"panda_finger_joint1", 0.09999}, {"panda_finger_joint2", 0.09999}})
    {
        //setGoalTolerance
    }

    virtual void onEntry() override
    {
        this->requiresClient(movegroupClient_);
        auto &moveGroupInterface = movegroupClient_->moveGroupClientInterface;

        previousTolerance = moveGroupInterface.getGoalJointTolerance();

        moveGroupInterface.setGoalJointTolerance(0.01);
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
