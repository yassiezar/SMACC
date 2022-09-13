#include <smacc/smacc.h>

namespace sm_atomic_sync {
class OrOrthogonal1 : public smacc::Orthogonal<OrOrthogonal1> {
 public:
  void onInitialize() override {
    auto sync_client =
        this->createClient<ClSync>("/camera_topic");
    sync_client->initialize();
  }
};
}  // namespace sm_atomic_sync
