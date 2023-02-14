#include <smacc/smacc.h>

namespace sm_atomic_early_exit {
class OrExample : public smacc::Orthogonal<OrExample> {
 public:
  virtual void onInitialize() override {
    auto sub_client = this->createClient<ClExampleSub>("example");
    sub_client->initialize();

    auto pub_client = this->createClient<ClExamplePub>("example");
    pub_client->initialize();
  }
};
}  // namespace sm_atomic_early_exit
