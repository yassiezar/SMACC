#include <smacc/client_bases/smacc_publisher_client.h>
#include <smacc/smacc.h>
#include <std_msgs/Empty.h>

namespace sm_atomic_early_exit {
class ClExamplePub : public smacc::client_bases::SmaccPublisherClient {
 public:
  ClExamplePub(const std::string& topic) {
    this->configure<std_msgs::Empty>(topic);
  }
};
}  // namespace sm_atomic_early_exit
