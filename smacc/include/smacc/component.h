/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/
#pragma once

#include <smacc/common.h>
#include <boost/optional.hpp>

namespace smacc
{
    
class ISmaccComponent
{
public:
    ISmaccComponent();

    virtual ~ISmaccComponent();

    // Returns a custom identifier defined by the specific plugin implementation
    virtual std::string getName() const;

protected:

    void initialize(ISmaccClient *owner);

    // Assigns the owner of this resource to the given state machine parameter object
    void setStateMachine(ISmaccStateMachine *stateMachine);

    template <typename EventType>
    void postEvent(const EventType &ev);

    template <typename EventType>
    void postEvent();

    template <typename TObjectTag, typename TDerived>
    void configureEventSourceTypes() {}

    template <typename TComponent>
    void requiresComponent(TComponent *& requiredComponentStorage);

    template <typename TClient>
    void requiresClient(TClient *& requiredClientStorage);

    virtual void onInitialize();

    // A reference to the state machine object that owns this resource
    ISmaccStateMachine *stateMachine_;

    ISmaccClient *owner_;

    friend class ISmaccOrthogonal;
    friend class ISmaccClient;
};
} // namespace smacc