#include <smacc/client_behavior_bases/cb_subscription_callback_base.h>
#include <smacc/smacc.h>
#include <std_msgs/Empty.h>

namespace sm_atomic_early_exit {
class CbExampleSub : public smacc::CbSubscriptionCallbackBase<std_msgs::Empty> {
 public:
  void onEntry() override {
    this->requiresClient(cl_pub_);
    this->requiresClient(cl_sub_);
    cl_sub_->onMessageReceived(&CbExampleSub::onMessageReceived, this);
  }

  void onMessageReceived(const std_msgs::Empty& msg) override {
    auto tmp = cl_pub_->getNum();
    tmp = cl_sub_->getNum();
  }

 private:
  ClExampleSub* cl_sub_;
  ClExamplePub* cl_pub_;
};
}  // namespace sm_atomic_early_exit
