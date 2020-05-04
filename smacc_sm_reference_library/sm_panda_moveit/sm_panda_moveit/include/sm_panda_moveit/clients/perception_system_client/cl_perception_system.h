#include <ros/ros.h>
#include <gazebo_msgs/LinkStates.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include <move_base_z_client_plugin/components/pose/cp_pose.h>

namespace sm_panda_moveit
{
class ClPerceptionSystem : public smacc::ISmaccClient, public smacc::ISmaccUpdatable
{
private:
    ros::Subscriber linkStatesSub_;
    tf::TransformBroadcaster tfBroadcaster_;

public:
    cl_move_base_z::Pose *peg0;

    cl_move_base_z::Pose *horizontalPegPlace0;
    cl_move_base_z::Pose *horizontalPegPlace1;
    cl_move_base_z::Pose *horizontalPegPlace2;

    cl_move_base_z::Pose *wallPegPlace0;
    cl_move_base_z::Pose *wallPegPlace1;
    cl_move_base_z::Pose *wallPegPlace2;

    ClPerceptionSystem()
    {
        ros::NodeHandle nh;
        linkStatesSub_ = nh.subscribe("/gazebo/link_states", 1, &ClPerceptionSystem::onLinkStatesCallback, this);
    }

    void onLinkStatesCallback(const gazebo_msgs::LinkStates &linksmsg)
    {
        //std::vector<tf::Transform> pegTransforms;
        this->propagateLinkStatesToTf(linksmsg, "peg", "peg", "world", true);
        this->propagateLinkStatesToTf(linksmsg, "panda::panda_pose", "panda_pose", "world", false);

        this->propagateLinkStatesToTf(linksmsg, "horizontal_peg_holder::", "horizontal_peg_place_", "world", true);
        this->propagateLinkStatesToTf(linksmsg, "wall_peg_holder::", "wall_peg_place_", "world", true);
    }

    geometry_msgs::PoseStamped decidePegPose()
    {
        peg0->waitTransformUpdate();
        return peg0->toPoseStampedMsg();
    }

    void propagateLinkStatesToTf(const gazebo_msgs::LinkStates &linksmsg, std::string link_name_filter, std::string object_prefix, std::string global_frame, bool indexpostfix)
    {
        int count = 0;
        for (int i = 0; i < linksmsg.name.size(); i++)
        {
            auto &name = linksmsg.name[i];
            auto &pose = linksmsg.pose[i];

            if (name.find(link_name_filter) == 0)
            {
                tf::Transform transf;
                tf::poseMsgToTF(pose, transf);

                std::string framename = object_prefix;
                if (indexpostfix)
                {
                    framename += std::to_string(count);
                }

                this->tfBroadcaster_.sendTransform(tf::StampedTransform(transf, ros::Time::now(), global_frame, framename));
                count++;
            }
        }
    }

    virtual void update() override
    {
    }
};
} // namespace sm_panda_moveit