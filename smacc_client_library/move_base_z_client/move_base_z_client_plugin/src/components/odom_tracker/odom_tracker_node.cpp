/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/
#include <move_base_z_client_plugin/components/move_base_z_plugin/components/odom_tracker/odom_tracker.h>
#include <odom_tracker/OdomTrackerAction.h>
#include <actionlib/server/simple_action_server.h>
#include <memory>

typedef actionlib::SimpleActionServer<odom_tracker::OdomTrackerAction> Server;

using namespace odom_tracker;
using namespace cl_move_base_z::odom_tracker;

class OdomTrackerActionServer
{
public:
  std::shared_ptr<Server> as_;
  OdomTracker odomTracker;

  OdomTrackerActionServer()
      : odomTracker("move_base")
  {
  }

  /**
******************************************************************************************************************
* execute()
******************************************************************************************************************
*/
  void execute(const OdomTrackerGoalConstPtr &goal) // Note: "Action" is not appended to DoDishes here
  {
    try
    {
      switch (goal->command)
      {
      case OdomTrackerGoal::RECORD_PATH:
        odomTracker.setWorkingMode(WorkingMode::RECORD_PATH);
        break;

      case OdomTrackerGoal::CLEAR_PATH:
        odomTracker.setWorkingMode(WorkingMode::CLEAR_PATH);
        break;

      case OdomTrackerGoal::IDLE:
        odomTracker.setWorkingMode(WorkingMode::IDLE);
        break;

      case OdomTrackerGoal::START_BROADCAST_PATH:
        odomTracker.setPublishMessages(true);
        break;

      case OdomTrackerGoal::STOP_BROADCAST_PATH:
        odomTracker.setPublishMessages(false);
        break;

      case OdomTrackerGoal::PUSH_PATH:
        odomTracker.pushPath();
        break;

      case OdomTrackerGoal::POP_PATH:
        odomTracker.popPath();
        break;

      default:

        ROS_ERROR("Odom Tracker Node - Action Server execute error: incorrect command - %d", goal->command);
        as_->setAborted();
      }

      // never reach succeeded because were are interested in keeping the feedback alive
      as_->setSucceeded();
    }
    catch (std::exception &ex)
    {
      ROS_ERROR("Odom Tracker Node - Action Server execute error: %s", ex.what());
      as_->setAborted();
    }
  }

  /**
******************************************************************************************************************
* run()
******************************************************************************************************************
*/
  void run()
  {
    ros::NodeHandle n;
    ROS_INFO("Creating odom tracker action server");

    as_ = std::make_shared<Server>(n, "odom_tracker", boost::bind(&OdomTrackerActionServer::execute, this, _1), false);
    ROS_INFO("Starting OdomTracker Action Server");

    as_->start();

    ros::spin();
  }
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "odom_tracker_node");
  OdomTrackerActionServer as;

  as.run();
}
