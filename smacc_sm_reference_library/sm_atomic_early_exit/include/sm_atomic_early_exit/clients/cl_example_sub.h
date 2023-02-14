#include <smacc/client_bases/smacc_subscriber_client.h>
#include <smacc/smacc.h>
#include <std_msgs/Empty.h>

namespace sm_atomic_early_exit {
class ClExampleSub
    : public smacc::client_bases::SmaccSubscriberClient<std_msgs::Empty> {
 public:
  ClExampleSub(const std::string& topic)
      : smacc::client_bases::SmaccSubscriberClient<std_msgs::Empty>{topic} {}

  inline int getNum() const { return num_; }

 private:
  const int num_{69};
};
}  // namespace sm_atomic_early_exit
