cmake_minimum_required(VERSION 2.8.3)
project(sm_atomic_sync)

## Find catkin macros and libraries
find_package(catkin REQUIRED 
  image_transport
  smacc
)

###################################
## catkin specific configuration ##
###################################
catkin_package()

###########
## Build ##
###########
# set(CMAKE_CXX_COMPILER clang++)
# set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
add_compile_options(-std=c++14) #workaround for ubuntu 16.04, to extinguish

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(${PROJECT_NAME}_node src/sm_atomic_sync_node.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############

## Mark executables for installation
install(TARGETS ${PROJECT_NAME}_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark other files for installation (e.g. launch and config files, etc.)
install(FILES
  launch/sm_atomic_sync.launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
)

install(DIRECTORY
  config/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/config
)
