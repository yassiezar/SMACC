#include <smacc/smacc.h>

// CLIENTS
#include <sm_atomic_sync/clients/cl_client_1.h>
#include <sm_atomic_sync/clients/cl_client_2.h>
#include <sm_atomic_sync/clients/cl_sync.h>

// ORTHOGONALS
#include <sm_atomic_sync/orthogonals/or_orthogonal_1.h>

using namespace boost;
using namespace smacc;

namespace sm_atomic_sync {

// STATE
class State1;

//--------------------------------------------------------------------
// STATE_MACHINE
struct SmAtomicSync
    : public smacc::SmaccStateMachineBase<SmAtomicSync, State1> {
  using SmaccStateMachineBase::SmaccStateMachineBase;

  void onInitialize() override { this->createOrthogonal<OrOrthogonal1>(); }
};

}  // namespace sm_atomic_sync

#include <sm_atomic_sync/states/st_state_1.h>