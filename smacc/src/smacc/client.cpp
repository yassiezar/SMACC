
/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/

#include <smacc/smacc_client.h>
#include <smacc/impl/smacc_client_impl.h>

namespace smacc
{
ISmaccClient::ISmaccClient()
{
}

ISmaccClient::~ISmaccClient()
{
}

void ISmaccClient::initialize()
{

}

void ISmaccClient::getComponents(std::vector<std::shared_ptr<ISmaccComponent>> &components)
{
    for (auto &ce : components_)
    {
        components.push_back(ce.second);
    }
}

std::string ISmaccClient::getName() const
{
    std::string keyname = demangleSymbol(typeid(*this).name());
    return keyname;
}

void ISmaccClient::setStateMachine(ISmaccStateMachine *stateMachine)
{
    stateMachine_ = stateMachine;
}

void ISmaccClient::setOrthogonal(ISmaccOrthogonal* orthogonal)
{
    orthogonal_ = orthogonal;
}

smacc::introspection::TypeInfo::Ptr ISmaccClient::getType()
{
    return smacc::introspection::TypeInfo::getFromStdTypeInfo(typeid(*this));
}

} // namespace smacc
