#!/bin/bash
echo "build docker image with github user: $1"
echo "build docker image with packagecloud user: $3"
sudo docker build --build-arg ROS_DOCKER_BASE="ros:kinetic-robot" --build-arg ROS_VERSION_NAME="kinetic" --build-arg UBUNTU_VERSION="xenial" --build-arg GITHUB_USER="$1" --build-arg GITHUB_TOKEN="$2" --build-arg PACKAGE_CLOUD_USER="$3" --build-arg PACKAGE_CLOUD_TOKEN="$4" -t package_cloud_tool_docker .
