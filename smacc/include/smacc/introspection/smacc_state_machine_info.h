/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/

#pragma once

#include <smacc/common.h>
#include <smacc/smacc_orthogonal.h>

// smacc_msgs
#include <smacc_msgs/SmaccState.h>
#include <smacc_msgs/SmaccTransition.h>
#include <smacc_msgs/SmaccOrthogonal.h>
#include <smacc_msgs/SmaccStateReactor.h>
#include <smacc_msgs/SmaccEventGenerator.h>

namespace smacc
{
namespace introspection
{
class SmaccStateMachineInfo : public std::enable_shared_from_this<SmaccStateMachineInfo>
{
public:
    std::map<std::string, std::shared_ptr<SmaccStateInfo>> states;

    std::vector<smacc_msgs::SmaccState> stateMsgs;

    template <typename InitialStateType>
    void buildStateMachineInfo();

    template <typename StateType>
    std::shared_ptr<SmaccStateInfo> createState(std::shared_ptr<SmaccStateInfo> parentState);

    template <typename StateType>
    bool containsState()
    {
        auto typeNameStr = typeid(StateType).name();

        return states.count(typeNameStr) > 0;
    }

    template <typename StateType>
    std::shared_ptr<SmaccStateInfo> getState()
    {
        if (this->containsState<StateType>())
        {
            return states[typeid(StateType).name()];
        }
        return nullptr;
    }

    template <typename StateType>
    void addState(std::shared_ptr<StateType> &state);

    void assembleSMStructureMessage(ISmaccStateMachine *sm);
};

//---------------------------------------------
struct AddSubState
{
    std::shared_ptr<SmaccStateInfo> &parentState_;
    AddSubState(std::shared_ptr<SmaccStateInfo> &parentState)
        : parentState_(parentState)
    {
    }

    template <typename T>
    void operator()(T);
};

//---------------------------------------------
struct AddTransition
{
    std::shared_ptr<SmaccStateInfo> &currentState_;

    AddTransition(std::shared_ptr<SmaccStateInfo> &currentState)
        : currentState_(currentState)
    {
    }

    template <template <typename, typename, typename> typename TTransition, typename TevSource, template <typename> typename EvType, typename Tag, typename DestinyState>
    void operator()(TTransition<EvType<TevSource>, DestinyState, Tag>);

    template <template <typename, typename> typename TTransition, typename TevSource, template <typename> typename EvType, typename DestinyState>
    void operator()(TTransition<EvType<TevSource>, DestinyState>);

    template <typename T>
    void operator()(T);
};

//---------------------------------------------
template <typename InitialStateType>
struct WalkStatesExecutor
{
    static void walkStates(std::shared_ptr<SmaccStateInfo> &currentState, bool rootInitialNode);
};

//---------------------------------------------
template <typename T>
void AddSubState::operator()(T)
{
    using type_t = typename T::type;
    //auto childState = this->parentState_->createChildState<type_t>()
    WalkStatesExecutor<type_t>::walkStates(parentState_, false);
}
//--------------------------------------------
template <typename T>
typename disable_if<boost::mpl::is_sequence<T>>::type
processSubState(std::shared_ptr<SmaccStateInfo> &parentState)
{
    WalkStatesExecutor<T>::walkStates(parentState, false);
}

//---------------------------------------------
template <typename T>
typename enable_if<boost::mpl::is_sequence<T>>::type
processSubState(std::shared_ptr<SmaccStateInfo> &parentState)
{
    using boost::mpl::_1;
    using wrappedList = typename boost::mpl::transform<T, add_type_wrapper<_1>>::type;
    boost::mpl::for_each<wrappedList>(AddSubState(parentState));
}

//--------------------------------------------
/*Iterate on All Transitions*/
template <typename T>
typename enable_if<boost::mpl::is_sequence<T>>::type
processTransitions(std::shared_ptr<SmaccStateInfo> &sourceState)
{

    ROS_INFO_STREAM("State %s Walker has transition list");
    using boost::mpl::_1;
    using wrappedList = typename boost::mpl::transform<T, add_type_wrapper<_1>>::type;
    boost::mpl::for_each<wrappedList>(AddTransition(sourceState));
}

template <typename Ev, typename Dst, typename Tag>
void processTransition(smacc::Transition<Ev, boost::statechart::deep_history<Dst>, Tag> *, std::shared_ptr<SmaccStateInfo> &sourceState)
{
    auto transitionTypeInfo = TypeInfo::getTypeInfoFromType<smacc::Transition<Ev, boost::statechart::deep_history<Dst>, Tag>>();
    smacc::Transition<Ev, Dst, Tag> *mock;
    processTransitionAux(mock, sourceState, true, transitionTypeInfo);
}

template <typename Ev, typename Dst, typename Tag>
void processTransition(smacc::Transition<Ev, Dst, Tag> *t, std::shared_ptr<SmaccStateInfo> &sourceState)
{
    auto transitionTypeInfo = TypeInfo::getTypeInfoFromType<smacc::Transition<Ev, Dst, Tag>>();
    processTransitionAux(t, sourceState, false, transitionTypeInfo);
}

template <typename Ev, typename Dst, typename Tag>
void processTransitionAux(smacc::Transition<Ev, Dst, Tag> *, std::shared_ptr<SmaccStateInfo> &sourceState, bool history, TypeInfo::Ptr &transitionTypeInfo)
{
    ROS_INFO("State %s Walker transition: %s", sourceState->toShortName().c_str(), demangleSymbol(typeid(Ev).name()).c_str());
    std::string transitionTag;
    std::string transitionType;

    if (typeid(Tag) != typeid(default_transition_name))
    {
        transitionTag = demangleSymbol<Tag>();
        transitionType = getTransitionType<Tag>();
        ROS_DEBUG_STREAM("TRANSITION TYPE:" << transitionType);
    }
    else
    {
        transitionTag = "";
        automaticTransitionTag<Ev>(transitionTag);
        automaticTransitionType<Ev>(transitionType);
    }

    ROS_INFO_STREAM("Transition tag: " << transitionTag);

    if (!sourceState->stateMachine_->containsState<Dst>())
    {
        auto realparentState = sourceState->stateMachine_->getState<typename Dst::TContext>();
        auto siblingnode = sourceState->stateMachine_->createState<Dst>(realparentState);

        //auto siblingnode = sourceState->stateMachine_->createState<Dst>(sourceState->parentState_);
        WalkStatesExecutor<Dst>::walkStates(siblingnode, true);
        sourceState->declareTransition<Ev>(siblingnode, transitionTag, transitionType, history, transitionTypeInfo);
    }
    else
    {
        //auto realparentState = sourceState->stateMachine_->getState<typename Dst::TContext>();
        //auto siblingnode = sourceState->stateMachine_->createState<Dst>(realparentState);

        auto siblingnode = sourceState->stateMachine_->getState<Dst>();
        sourceState->declareTransition<Ev>(siblingnode, transitionTag, transitionType, history, transitionTypeInfo);
    }
}

//---------------------------------------------
template <typename EvType>
void SmaccStateInfo::declareTransition(std::shared_ptr<SmaccStateInfo> &dstState, std::string transitionTag, std::string transitionType, bool history, TypeInfo::Ptr transitionTypeInfo)
{
    auto evtype = demangledTypeName<EvType>();

    SmaccTransitionInfo transitionInfo;
    transitionInfo.index = transitions_.size();
    transitionInfo.sourceState = shared_from_this();
    transitionInfo.destinyState = dstState;
    transitionInfo.transitionTypeInfo = transitionTypeInfo;

    if (transitionTag != "")
        transitionInfo.transitionTag = transitionTag;
    else
        transitionInfo.transitionTag = "Transition_" + std::to_string(transitionInfo.index);

    transitionInfo.transitionType = transitionType;
    transitionInfo.historyNode = history;

    transitionInfo.eventInfo = std::make_shared<SmaccEventInfo>(transitionTypeInfo->templateParameters.front());

    EventLabel<EvType>(transitionInfo.eventInfo->label);
    ROS_DEBUG_STREAM("LABEL: " << transitionInfo.eventInfo->label);

    transitions_.push_back(transitionInfo);
}
//---------------------------------------------

// template <typename TevSource, template <typename> typename EvType>
// void SmaccStateInfo::declareTransition(std::shared_ptr<SmaccStateInfo> &dstState, std::string transitionTag, std::string transitionType, bool history)
// {
//     auto evtype = demangledTypeName<EvType<TevSource>>();

//     SmaccTransitionInfo transitionInfo;
//     transitionInfo.index = transitions_.size();
//     transitionInfo.sourceState = shared_from_this();
//     transitionInfo.destinyState = dstState;

//     if (transitionTag != "")
//         transitionInfo.transitionTag = transitionTag;
//     else
//         transitionInfo.transitionTag = "Transition_" + std::to_string(transitionInfo.index);

//     transitionInfo.transitionType = transitionType;

//     transitionInfo.eventInfo = std::make_shared<SmaccEventInfo>(TypeInfo::getTypeInfoFromString(demangleSymbol(typeid(EvType<TevSource>).name())));

//     EventLabel<EvType<TevSource>>(transitionInfo.eventInfo->label);
//     ROS_ERROR_STREAM("LABEL: " << transitionInfo.eventInfo->label);

//     transitions_.push_back(transitionInfo);
// }

//---------------------------------------------
template <typename Ev, typename Dst>
void processTransition(statechart::transition<Ev, Dst> *, std::shared_ptr<SmaccStateInfo> &sourceState)
{
    //ROS_INFO_STREAM("GOTCHA");
}

template <typename Ev>
void processTransition(statechart::custom_reaction<Ev> *, std::shared_ptr<SmaccStateInfo> &sourceState)
{
    //ROS_INFO_STREAM("GOTCHA");
}

//---------------------------------------------
// only reached if it is a leaf transition in the mpl::list

template <typename T>
typename disable_if<boost::mpl::is_sequence<T>>::type
processTransitions(std::shared_ptr<SmaccStateInfo> &sourceState)
{
    //ROS_INFO_STREAM("state transition from: " << sourceState->demangledStateName << " of type: " << demangledTypeName<T>());
    T *dummy;
    processTransition(dummy, sourceState);
}

/*
// only reached if it is a leaf transition in the mpl::list
template <template <typename,typename,typename> typename TTransition, typename TevSource, template <typename> typename EvType, typename Tag, typename DestinyState >
typename disable_if<boost::mpl::is_sequence<TTransition<EvType<TevSource>,DestinyState, Tag>>>::type
processTransitions(std::shared_ptr<SmaccStateInfo> &sourceState)
{
    ROS_INFO("DETECTED COMPLEX TRANSITION **************");
    //ROS_INFO_STREAM("state transition from: " << sourceState->demangledStateName << " of type: " << demangledTypeName<T>());
    TTransition<EvType<TevSource>,DestinyState, Tag> *dummy;
    processTransition(dummy, sourceState);
}

template <template <typename,typename> typename TTransition, typename TevSource, template <typename> typename EvType, typename DestinyState >
typename disable_if<boost::mpl::is_sequence<TTransition<EvType<TevSource>,DestinyState>>>::type
processTransitions(std::shared_ptr<SmaccStateInfo> &sourceState)
{
    ROS_INFO("DETECTED COMPLEX TRANSITION **************");
    //ROS_INFO_STREAM("state transition from: " << sourceState->demangledStateName << " of type: " << demangledTypeName<T>());
    TTransition<EvType<TevSource>,DestinyState> *dummy;
    processTransition(dummy, sourceState);
}
*/

//--------------------------------------------

template <template <typename, typename, typename> typename TTransition, typename TevSource, template <typename> typename EvType, typename Tag, typename DestinyState>
void AddTransition::operator()(TTransition<EvType<TevSource>, DestinyState, Tag>)
{
    processTransitions<TTransition<EvType<TevSource>, DestinyState, Tag>>(currentState_);
}

//--------------------------------------------

template <template <typename, typename> typename TTransition, typename TevSource, template <typename> typename EvType, typename DestinyState>
void AddTransition::operator()(TTransition<EvType<TevSource>, DestinyState>)
{
    processTransitions<TTransition<EvType<TevSource>, DestinyState>>(currentState_);
}

template <typename TTrans>
void AddTransition::operator()(TTrans)
{
    using type_t = typename TTrans::type;
    processTransitions<type_t>(currentState_);
}

//------------------ staticConfigure -----------------------------

// SFINAE test
template <typename T>
class HasOnDefinition
{
private:
    typedef char YesType[1];
    typedef char NoType[2];

    template <typename C>
    static YesType &test(decltype(&C::staticConfigure));
    template <typename C>
    static NoType &test(...);

public:
    enum
    {
        value = sizeof(test<T>(0)) == sizeof(YesType)
    };
};

template <typename T>
typename std::enable_if<HasOnDefinition<T>::value, void>::type
CallOnDefinition()
{
    /* something when T has toString ... */
    ROS_INFO_STREAM("EXECUTING ONDEFINITION: " << demangleSymbol(typeid(T).name()));
    T::staticConfigure();
}

template <typename T>
typename std::enable_if<!HasOnDefinition<T>::value, void>::type
CallOnDefinition()
{
    ROS_INFO_STREAM("static OnDefinition: dont exist for " << demangleSymbol(typeid(T).name()));
    /* something when T has toString ... */
}

/*
void CallOnDefinition(...)
{

}*/

//-----------------------------------------------------------------------------------
template <typename InitialStateType>
void WalkStatesExecutor<InitialStateType>::walkStates(std::shared_ptr<SmaccStateInfo> &parentState, bool rootInitialNode)
{
    //ros::Duration(1).sleep();
    auto currentname = demangledTypeName<InitialStateType>();

    std::shared_ptr<SmaccStateInfo> targetState;

    if (!rootInitialNode)
    {
        if (parentState->stateMachine_->containsState<InitialStateType>())
        {
            // it already exist: break;
            return;
        }

        targetState = parentState->createChildState<InitialStateType>();
    }
    else
    {
        targetState = parentState;
    }

    CallOnDefinition<InitialStateType>();

    typedef typename std::remove_pointer<decltype(InitialStateType::smacc_inner_type)>::type InnerType;
    processSubState<InnerType>(targetState);

    // -------------------- REACTIONS --------------------
    typedef typename InitialStateType::reactions reactions;
    //ROS_INFO_STREAM("state machine initial state reactions: "<< demangledTypeName<reactions>());

    processTransitions<reactions>(targetState);
}

//------------------------------------------------

template <typename InitialStateType>
void SmaccStateMachineInfo::buildStateMachineInfo()
{
    auto initialState = this->createState<InitialStateType>(nullptr);
    WalkStatesExecutor<InitialStateType>::walkStates(initialState, true);
}

template <typename StateType>
std::shared_ptr<SmaccStateInfo> SmaccStateMachineInfo::createState(std::shared_ptr<SmaccStateInfo> parent)
{
    auto thisptr = this->shared_from_this();
    auto *statetid = &(typeid(StateType));

    auto demangledName = demangledTypeName<StateType>();
    ROS_INFO_STREAM("Creating State Info: " << demangledName);

    auto state = std::make_shared<SmaccStateInfo>(statetid, parent, thisptr);
    state->demangledStateName = demangledName;
    state->fullStateName = typeid(StateType).name();
    state->stateIndex_ = states.size();

    if (parent != nullptr)
    {
        parent->children_.push_back(state);
    }

    this->addState(state);

    return state;
}

template <typename StateType>
void SmaccStateMachineInfo::addState(std::shared_ptr<StateType> &state)
{
    states[state->fullStateName] = state;
}

template <typename StateType>
std::shared_ptr<SmaccStateInfo> SmaccStateInfo::createChildState()
{
    auto realparentState = this->stateMachine_->getState<typename StateType::TContext>();

    auto childState = this->stateMachine_->createState<StateType>(realparentState);

    ROS_WARN_STREAM("Real parent state> " << demangleSymbol<typename StateType::TContext>());

    /*auto contextInfo = TypeInfo::getTypeInfoFromType<InitialStateType>();
    auto parentState2= getState<InitialStateType::TContext>();
    parentState2->createChildState<InitialStateType>();*/

    //this->stateMachine_->addState(childState);
    //stateMachineInfo.addState(stateMachineInfo)
    //stateNames.push_back(currentname);
    //ROS_INFO("------------");
    //ROS_INFO_STREAM("** STATE state: "<< this->demangledStateName);

    return childState;
}
} // namespace introspection
} // namespace smacc
