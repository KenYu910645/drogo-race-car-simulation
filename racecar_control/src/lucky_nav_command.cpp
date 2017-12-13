#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <cmath>

std_msgs::Float64 throttle;
std_msgs::Float64 steer;

const double THROTTLE_GAIN = 1; 
const double d2g = (M_PI)/180.0;

void callBack (const geometry_msgs::Twist &msg)
{
  throttle.data = (msg.linear.x - 1500) * THROTTLE_GAIN;
  steer.data = (msg.angular.z - 90) * d2g;
}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "lucky_nav_command");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/car/cmd_vel", 1000 , callBack);
  
  ros::Publisher  pub1 = n.advertise<std_msgs::Float64>("racecar/left_rear_wheel_velocity_controller/command", 1000);
  ros::Publisher  pub2 = n.advertise<std_msgs::Float64>("racecar/right_rear_wheel_velocity_controller/command", 1000);
  ros::Publisher  pub3 = n.advertise<std_msgs::Float64>("racecar/left_front_wheel_velocity_controller/command", 1000);
  ros::Publisher  pub4 = n.advertise<std_msgs::Float64>("racecar/right_front_wheel_velocity_controller/command", 1000);

  
  ros::Publisher  pub5 = n.advertise<std_msgs::Float64>("racecar/left_steering_hinge_position_controller/command", 1000);
  ros::Publisher  pub6 = n.advertise<std_msgs::Float64>("racecar/right_steering_hinge_position_controller/command", 1000);
  ros::Rate rate (100); 

  while (ros::ok())
  {
    //recieve data from previse topic
    ros::spinOnce();
    
    //post-process
    pub1.publish(throttle);
    pub2.publish(throttle);
    pub3.publish(throttle);
    pub4.publish(throttle);
    pub5.publish(steer);
    pub6.publish(steer);
    rate.sleep();
  }
  return 0;
}
