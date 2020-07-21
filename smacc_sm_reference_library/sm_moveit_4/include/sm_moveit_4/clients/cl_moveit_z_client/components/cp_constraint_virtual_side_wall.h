#pragma once

#include <smacc/component.h>
#include <moveit_z_client/cl_movegroup.h>
#include <geometry_msgs/Vector3.h>

namespace sm_moveit_4
{
    namespace cl_moveit_z_client
    {
        // Adds two simetric collision virtual walls for the moveit planning
        class CpConstraintVirtualSideWall : public smacc::ISmaccComponent, public smacc::ISmaccUpdatable
        {
        private:
            moveit::planning_interface::PlanningSceneInterface *planningSceneInterface_;
            moveit_z_client::ClMoveGroup *movegroupclient_;

            std::string referenceFrame_;
            geometry_msgs::Vector3 offset_;
            geometry_msgs::Vector3 size_;
            bool enabled_ = true;
            bool alreadyRemoved_ = true;

        public:
            void enable();

            void disable();

            CpConstraintVirtualSideWall(std::string referenceFrame, geometry_msgs::Vector3 size, geometry_msgs::Vector3 offset = geometry_msgs::Vector3());

            virtual void onInitialize() override;

            virtual void update();

            void createCollisionBox(float x, float y, float z, float xl, float yl, float zl, std::string id, std::string frameid, moveit_msgs::CollisionObject &collision, const ros::Time &time, int addOrRemove);

            void createVirtualCollisionWalls(std::vector<moveit_msgs::CollisionObject> &collisions, const ros::Time &time, int addOrRemove);
        };

    } // namespace cl_moveit_z_client

} // namespace sm_moveit_4