#include <sm_atomic_early_exit/sm_atomic_early_exit.h>

//--------------------------------------------------------------------
int main(int argc, char **argv) {
  ros::init(argc, argv, "sm_atomic_early_exit");
  ros::NodeHandle nh;

  smacc::run<sm_atomic_early_exit::SmAtomicEarlyExit>();
}
