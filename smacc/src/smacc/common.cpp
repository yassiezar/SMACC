/*****************************************************************************************************************
 * ReelRobotix Inc. - Software License Agreement      Copyright (c) 2018
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/
#include "smacc/common.h"
#include "smacc/client_bases/smacc_action_client_base.h"

namespace smacc
{
namespace utils
{

std::string cleanShortTypeName(const std::type_info &tinfo)
{
    auto typeinfo= TypeInfo::getFromStdTypeInfo(tinfo);
    auto nontemplatedfullclasname = typeinfo->getNonTemplatedTypeName();


    //ROS_INFO("State full classname: %s", fullclassname.c_str());

    std::vector<std::string> strs;
    boost::split(strs, nontemplatedfullclasname, boost::is_any_of("::"));
    std::string classname = strs.back();
    //ROS_INFO("State classname: %s", classname.c_str());


    return classname;
}
} // namespace utils
} // namespace smacc
