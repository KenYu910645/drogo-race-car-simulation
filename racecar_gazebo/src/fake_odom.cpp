#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf2_msgs/TFMessage.h>

ros::Time t;
double px, py, pz ,qx, qy, qz, qw = 0;
int seq = 0;

void callBack (const nav_msgs::Odometry &msg)
{
  t = msg.header.stamp;
  px = msg.pose.pose.position.x;
  py = msg.pose.pose.position.y;
  pz = msg.pose.pose.position.z;
  qx = msg.pose.pose.orientation.x;
  qy = msg.pose.pose.orientation.y;
  qz = msg.pose.pose.orientation.z;
  qw = msg.pose.pose.orientation.w;
}

int main (int argc, char** argv)
{
  ros::init(argc, argv, "fake_odom");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/vesc/odom", 1000 , callBack);
  ros::Publisher  pub = n.advertise<tf2_msgs::TFMessage>("tf", 1000);
  ros::Rate rate (20); // 10Hz

  while (ros::ok())
  {
    tf2_msgs::TFMessage msg;

    //input header information
    msg.transforms[seq].header.frame_id = "odom";
    msg.transforms[seq].child_frame_id = "base_footprint";
    msg.transforms[seq].header.stamp = t;
    //recieve data from previse topic
    ros::spinOnce();
  
    //input the result to publisher msg.
    msg.transforms[seq].transform.translation.x = px; 
    msg.transforms[seq].transform.translation.y = py; 
    msg.transforms[seq].transform.translation.z = pz; 
    msg.transforms[seq].transform.rotation.x = qx; 
    msg.transforms[seq].transform.rotation.y = qy; 
    msg.transforms[seq].transform.rotation.z = qz; 
    msg.transforms[seq].transform.rotation.w = qw; 
    
    //post-process
    pub.publish(msg);
    rate.sleep();
    //seq++;
  }
  return 0;
}
