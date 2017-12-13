#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Joy.h>
#include <iostream>

std_msgs::Float64 throttle;
std_msgs::Float64 steer;

const double THROTTLE_GAIN = 15; 
const double STEER_GAIN = 0.53 ;

void callBack (const sensor_msgs::Joy &msg)
{
   throttle.data = abs(msg.axes[5] - 1) * THROTTLE_GAIN;
   steer.data = msg.axes[0] * STEER_GAIN;
   if (msg.axes[2] != 1) // if it's backward drive
     throttle.data = -(abs(msg.axes[2] - 1) * THROTTLE_GAIN);
   //std::cout << "throttle: " << throttle.data << std::endl;
   //std::cout << "steer: " << steer.data << std::endl;
}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "lucky_joy_command");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/joy", 1000 , callBack);
  
  ros::Publisher  pub1 = n.advertise<std_msgs::Float64>("racecar/left_rear_wheel_velocity_controller/command", 1000);
  ros::Publisher  pub2 = n.advertise<std_msgs::Float64>("racecar/right_rear_wheel_velocity_controller/command", 1000);
  ros::Publisher  pub3 = n.advertise<std_msgs::Float64>("racecar/left_front_wheel_velocity_controller/command", 1000);
  ros::Publisher  pub4 = n.advertise<std_msgs::Float64>("racecar/right_front_wheel_velocity_controller/command", 1000);

  
  ros::Publisher  pub5 = n.advertise<std_msgs::Float64>("racecar/left_steering_hinge_position_controller/command", 1000);
  ros::Publisher  pub6 = n.advertise<std_msgs::Float64>("racecar/right_steering_hinge_position_controller/command", 1000);
  ros::Rate rate (200); 

  while (ros::ok())
  {
    //recieve data from previse topic
    ros::spinOnce();
  
    //do some calculate about the date received.
  
    //input the result to publisher msg.
    
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
