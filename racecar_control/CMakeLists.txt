cmake_minimum_required(VERSION 2.8.3)
project(racecar_control)

find_package(catkin REQUIRED COMPONENTS
  gazebo_ros
  )

catkin_package(
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  ${catkin_INCLUDE_DIRS}
  )

add_executable(lucky_joy_command src/lucky_joy_command.cpp)
target_link_libraries(lucky_joy_command
  ${catkin_LIBRARIES}
  )

add_executable(lucky_nav_command src/lucky_nav_command.cpp)
target_link_libraries(lucky_nav_command
  ${catkin_LIBRARIES}
  )

