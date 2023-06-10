cmake_minimum_required(VERSION 3.0.2)
project(navigation_goals)


find_package(catkin REQUIRED COMPONENTS
  actionlib
  move_base_msgs
  roscpp
  visualization_msgs
  geometry_msgs
)

generate_messages(
  DEPENDENCIES
  move_base_msgs
)

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES navigation_goals
 CATKIN_DEPENDS actionlib move_base_msgs roscpp
 DEPENDS system_lib
)

include_directories(
include
  ${catkin_INCLUDE_DIRS}
)

add_executable(navigation src/navigation_goals.cpp)
target_link_libraries(navigation
  ${catkin_LIBRARIES}
)

add_executable(marker_rviz src/rviz_marker.cpp)
target_link_libraries(marker_rviz
  ${catkin_LIBRARIES}
)

