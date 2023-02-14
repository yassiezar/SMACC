#include <smacc/smacc.h>

// CLIENTS
#include <ros_timer_client/cl_ros_timer.h>

#include "sm_atomic_early_exit/clients/cl_example_sub.h"
#include "sm_atomic_early_exit/clients/cl_example_pub.h"

// ORTHOGONALS
#include "sm_atomic_early_exit/orthogonals/or_example.h"
#include "sm_atomic_early_exit/orthogonals/or_timer.h"

// CLIENT BEHAVIORS
#include <ros_timer_client/client_behaviors/cb_timer_countdown_loop.h>
#include <ros_timer_client/client_behaviors/cb_timer_countdown_once.h>

#include "sm_atomic_early_exit/clients/client_behaviors/cb_example_sub.h"
#include "sm_atomic_early_exit/clients/client_behaviors/cb_example_pub.h"

using namespace boost;
using namespace smacc;

namespace sm_atomic_early_exit {

// STATE
class State1;
class State2;

//--------------------------------------------------------------------
// STATE_MACHINE
struct SmAtomicEarlyExit
    : public smacc::SmaccStateMachineBase<SmAtomicEarlyExit, State1> {
  using SmaccStateMachineBase::SmaccStateMachineBase;

  virtual void onInitialize() override {
    this->createOrthogonal<OrTimer>();
    this->createOrthogonal<OrExample>();
  }
};

}  // namespace sm_atomic_early_exit

#include <sm_atomic_early_exit/states/st_state_1.h>
#include <sm_atomic_early_exit/states/st_state_2.h>
