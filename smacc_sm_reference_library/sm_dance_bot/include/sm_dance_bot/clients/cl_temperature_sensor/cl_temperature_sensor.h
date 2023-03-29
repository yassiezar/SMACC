#pragma once

#include <multirole_sensor_client/cl_multirole_sensor.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Temperature.h>

namespace sm_dance_bot
{
namespace cl_temperature_sensor
{
class ClTemperatureSensor : public cl_multirole_sensor::ClMultiroleSensor<sensor_msgs::Temperature>
{
public:
    ClTemperatureSensor()
    {
    }
};
} // namespace cl_temperature_sensor
} // namespace sm_dance_bot
