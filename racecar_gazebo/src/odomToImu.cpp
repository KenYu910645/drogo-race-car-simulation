#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/Imu.h>

double X,Y,Z,W = 0 ;

void callBack (const nav_msgs::Odometry &msg)
{
   X = msg.pose.pose.orientation.x;
   Y = msg.pose.pose.orientation.y;
   Z = msg.pose.pose.orientation.z;
   W = msg.pose.pose.orientation.w;
}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "odom2imu");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("fake_odom", 1000 , callBack);
  ros::Publisher  pub = n.advertise<sensor_msgs::Imu>("imu_data", 1000);
  ros::Rate rate (100); // 10Hz

  while (ros::ok())
  {
    sensor_msgs::Imu imu;
    
    //recieve data from previse topic
    ros::spinOnce();
  
    //do some calculate about the date received.
  
    //input the result to publisher msg.
    imu.orientation.x = X; 
    imu.orientation.y = Y; 
    imu.orientation.z = Z; 
    imu.orientation.w = W; 
    
    //post-process
    pub.publish(imu);
    rate.sleep();
  }

  return 0;
}




