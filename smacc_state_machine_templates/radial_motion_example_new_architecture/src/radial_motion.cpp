#include <radial_motion.h>


RadialMotionStateMachine::RadialMotionStateMachine(my_context ctx, smacc::SignalDetector *signalDetector)
    : SmaccStateMachineBase<RadialMotionStateMachine,Superstate<RadialMotionStateMachine>>(ctx, signalDetector) 
    {
    }
    
int main(int argc, char **argv) 
{
  ros::init(argc, argv, "radial_test_state_machine");
  ros::NodeHandle nh;

  ros::Duration(5).sleep();
  smacc::run<RadialMotionStateMachine>();
}