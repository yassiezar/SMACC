#include <smacc/smacc.h>

namespace sm_dance_bot_strikes_back {
namespace SS1 {
namespace sm_dance_bot_strikes_back {
namespace radial_motion_states {

// FORWARD DECLARATION OF INNER STATES
class StiRadialRotate;
class StiRadialReturn;
class StiRadialEndPoint;
class StiRadialLoopStart;
} // namespace radial_motion_states
} // namespace sm_dance_bot_strikes_back
using namespace sm_dance_bot_strikes_back::radial_motion_states;

// STATE DECLARATION
struct SsRadialPattern1 : smacc::SmaccState<SsRadialPattern1, MsDanceBotRunMode, StiRadialLoopStart>
{
public:
    using SmaccState::SmaccState;

// TRANSITION TABLE
    typedef mpl::list<

    Transition<EvLoopEnd<StiRadialLoopStart>, StNavigateToWaypointsX, ENDLOOP>

    >reactions;

    static constexpr int total_iterations() { return 32; }
    static constexpr float ray_angle_increment_degree() { return 360.0 / total_iterations(); }
    static constexpr float ray_length_meters() { return 4; }

    int iteration_count = 0;

// STATE FUNCTIONS
    static void staticConfigure()
    {
        //configure_orthogonal<OrObstaclePerception, CbLidarSensor>();
    }

    void runtimeConfigure()
    {
    }
};

// FORWARD DECLARATION FOR THE SUPERSTATE
using SS = SsRadialPattern1;

#include <sm_dance_bot_strikes_back/states/radial_motion_states/sti_radial_end_point.h>
#include <sm_dance_bot_strikes_back/states/radial_motion_states/sti_radial_return.h>
#include <sm_dance_bot_strikes_back/states/radial_motion_states/sti_radial_rotate.h>
#include <sm_dance_bot_strikes_back/states/radial_motion_states/sti_radial_loop_start.h>
} // namespace SS1
} // namespace sm_dance_bot_strikes_back
