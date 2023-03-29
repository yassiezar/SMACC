#pragma once
#include <smacc/component.h>
#include <controller_manager_msgs/ControllerState.h>

namespace smacc
{
namespace components
{
struct ControllerTypeInfo
{
    std::string type;
    std::string baseClass;
};

enum Strictness
{
    BEST_EFFORT = 1,
    STRICT = 2
};

class CpRosControlInterface : public smacc::ISmaccComponent
{
public:
    CpRosControlInterface();

    virtual ~CpRosControlInterface();

    virtual void onInitialize() override;

    // template <typename TOrthogonal, typename TSourceObject>
    // void onOrthogonalAllocation() {}

    std::vector<ControllerTypeInfo> listControllerTypes();

    std::vector<controller_manager_msgs::ControllerState> listControllers();

    bool loadController(std::string name);

    bool unloadController(std::string name);

    bool reloadControllerLibraries(bool forceKill);

    bool switchControllers(std::vector<std::string> start_controllers,
                           std::vector<std::string> stop_controllers,
                           Strictness strictness);

    boost::optional<std::string> serviceName_;

private:
    ros::NodeHandle nh_;

    ros::ServiceClient srvListControllers;
    ros::ServiceClient srvListControllersTypes;
    ros::ServiceClient srvLoadController;
    ros::ServiceClient srvReloadControllerLibraries;
    ros::ServiceClient srvSwitchControllers;
    ros::ServiceClient srvUnloadController;
};
}
}
