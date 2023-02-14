#include <smacc/smacc.h>
#include <smacc/smacc_updatable.h>
#include <std_msgs/Empty.h>

#include <chrono>
#include <thread>

namespace sm_atomic_early_exit {
class CbExamplePub : public smacc::ISmaccClientBehavior,
                     public smacc::ISmaccUpdatable {
 public:
  CbExamplePub(const double& period)
      : smacc::ISmaccUpdatable{ros::Duration{period}} {}

  void update() override {
    std_msgs::Empty msg;
    cl_pub_->publish(msg);
  }

  void onEntry() override { this->requiresClient(cl_pub_); }

 private:
  ClExamplePub* cl_pub_;
};
}  // namespace sm_atomic_early_exit
