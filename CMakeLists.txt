cmake_minimum_required(VERSION 2.8.3)
project(proc_imagen_mj)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  tf
  cv_bridge
  image_transport
  pcl_conversions
  pcl_ros
)

catkin_package(
   INCLUDE_DIRS include
   LIBRARIES proc_imagen_mj
   CATKIN_DEPENDS
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
)

link_directories(
	${PCL_LIBRARY_DIRS}

)
add_definitions(${PCL_DEFINITIONS})

include_directories(
 include
 ${catkin_INCLUDE_DIRS}
)
add_executable(nodo_hsv_tuner src/nodo_hsv_tuner_2d.cpp)
target_link_libraries(nodo_hsv_tuner
 ${catkin_LIBRARIES}
)

add_executable(tracking_node src/tracking_node.cpp)
target_link_libraries(tracking_node
 ${catkin_LIBRARIES}
)
