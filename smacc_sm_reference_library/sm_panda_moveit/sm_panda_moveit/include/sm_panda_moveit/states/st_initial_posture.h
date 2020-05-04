#include <smacc/smacc.h>
namespace sm_panda_moveit
{
// STATE DECLARATION
struct StInitialPosture : smacc::SmaccState<StInitialPosture, SmPandaMoveIt>
{
    using SmaccState::SmaccState;

    // TRANSITION TABLE
    typedef mpl::list<>
        reactions;

    // STATE FUNCTIONS
    static void staticConfigure()
    {
    }

    void runtimeConfigure()
    {
    }
};
} // namespace sm_panda_moveit