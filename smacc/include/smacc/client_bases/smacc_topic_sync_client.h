#pragma once

#include <ros/node_handle.h>
#include <smacc/smacc_state_machine.h>
#include <boost/signals2/connection.hpp>
#include <smacc/smacc_client.h>
#include <image_transport/camera_subscriber.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>

namespace smacc {
  namespace client_bases {
    class SmaccTopicSyncClient : public smacc::ISmaccClient {

      using CameraInfo = sensor_msgs::CameraInfo;
      using Image = sensor_msgs::Image;

    public:
      SmaccTopicSyncClient(const std::string& base_image_topic) : base_image_topic_{base_image_topic} {
      }

      virtual ~SmaccTopicSyncClient() {
        sub_.shutdown();
      }

      template<typename T>
      boost::signals2::connection onMessageReceived(void (T::*callback)(const sensor_msgs::ImageConstPtr&, const sensor_msgs::CameraInfoConstPtr&), T* object) {
        return this->getStateMachine()->createSignalConnection(onMessageReceived_, callback, object);
      }

      virtual void initialize() {
        if (!initialized_)
        {
          if (!queue_size_) {
            queue_size_ = 1;
          }

          if (!base_image_topic_)
          {
            ROS_ERROR("Image topics not set, skipping subscription");
          }
          else
          {
            ROS_INFO_STREAM("[" << this->getName() << "] Subscribing to topic: " << base_image_topic_);

            // sub_ = nh_.subscribe(*topicName, *queueSize, &SmaccSubscriberClient<MessageType>::messageCallback, this);
            sub_ = it_.subscribeCamera(*base_image_topic_, *queue_size_, &SmaccTopicSyncClient::cameraTopicCallback, this);
            initialized_ = true;
          }
        }
      }

    protected:
      ros::NodeHandle nh_;

    private:
      void cameraTopicCallback(const sensor_msgs::ImageConstPtr& img_data, const sensor_msgs::CameraInfoConstPtr& cam_info) {
        onMessageReceived_(img_data, cam_info);
      }

      smacc::SmaccSignal<void(const sensor_msgs::ImageConstPtr&, const sensor_msgs::CameraInfoConstPtr&)> onMessageReceived_;

      image_transport::ImageTransport it_{nh_};
      image_transport::CameraSubscriber sub_;

      bool initialized_{false};
      boost::optional<std::string> base_image_topic_;
      boost::optional<int> queue_size_;
    };
  }
}
