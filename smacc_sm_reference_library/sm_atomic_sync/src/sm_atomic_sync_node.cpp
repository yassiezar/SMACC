#include <sm_atomic_sync/sm_atomic_sync.h>

//--------------------------------------------------------------------
int main(int argc, char **argv)
{
    ros::init(argc, argv, "sm_atomic_sync");
    ros::NodeHandle nh;

    smacc::run<sm_atomic_sync::SmAtomicSync>();
}