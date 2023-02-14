#include <smacc/client_behavior_bases/cb_subscription_callback_base.h>
#include <smacc/smacc.h>
#include <std_msgs/Empty.h>

namespace sm_atomic_early_exit {
class CbExampleSub : public smacc::CbSubscriptionCallbackBase<std_msgs::Empty> {
 public:
  void onMessageReceived(const std_msgs::Empty& msg) override {
    ROS_WARN_STREAM("Triggering crash..." << std::to_string(cl_sub_->getNum()));
  }

 private:
  ClExampleSub* cl_sub_;
};
}  // namespace sm_atomic_early_exit
