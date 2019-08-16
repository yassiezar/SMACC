#pragma once
#pragma once

#include <state_machine.h>

#include <boost/thread.hpp>

#include <states/navigate_superstate.h>
#include <states/navigate_to_radial_start.h>
#include <states/navigate_to_end_point.h>
#include <states/return_to_radial_start.h>
#include <states/rotate_degrees.h>

//--------------------------------------------
template<typename Container>
struct Superstate: public smacc::SmaccState<Superstate<Container>, Container, NavigateToRadialStart<Container>>
{
    using SmaccState<Superstate<Container>, Container, NavigateToRadialStart<Container>>::SmaccState;
};

