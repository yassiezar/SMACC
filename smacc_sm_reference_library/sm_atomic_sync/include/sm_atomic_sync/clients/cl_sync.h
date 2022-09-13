#pragma once

#include <message_filters/sync_policies/approximate_time.h>
#include <smacc/client_bases/smacc_topic_sync_client.h>
#include <std_msgs/Bool.h>

class ClSync
    : public smacc::client_bases::SmaccTopicSyncClient {
 public:
  ClSync(const std::string& image_topic)
      : smacc::client_bases::SmaccTopicSyncClient{image_topic} {}
};
