cmake_minimum_required(VERSION 2.8.3)
project(racecar_gazebo)

find_package(catkin REQUIRED COMPONENTS
  gazebo_ros
)

add_compile_options(-std=c++11)

catkin_package()

###########
## Build ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(odomToImu src/odomToImu.cpp)
target_link_libraries(odomToImu
    ${catkin_LIBRARIES}
  )
add_executable(fake_odom src/fake_odom.cpp)
target_link_libraries(fake_odom
    ${catkin_LIBRARIES}
  )
