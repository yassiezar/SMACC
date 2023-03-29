/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/

#pragma once

#include <smacc/smacc_client.h>
#include <smacc/smacc_state_machine.h>
#include <actionlib/client/simple_action_client.h>

namespace smacc
{
namespace client_bases
{
    using namespace actionlib;

    // This class interface shows the basic set of methods that
    // a SMACC "resource" or "plugin" Action Client has
    class ISmaccActionClient : public ISmaccClient
    {
    public:
        ISmaccActionClient();

        // The destructor. This is called when the object is not
        // referenced anymore by its owner
        virtual ~ISmaccActionClient();

        // Gets the ros path of the action...
        inline std::string getNamespace() const
        {
            return name_;
        }

        virtual void cancelGoal() = 0;

        virtual SimpleClientGoalState getState() = 0;

    protected:
        // The ros path where the action server is located
        std::string name_;
    };
} // namespace smacc
} // namespace smacc
