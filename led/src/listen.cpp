#include <ros/ros.h>
#include <std_msgs/String.h>

void buttonCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("LED is : [%s]", msg->data.c_str());
  std_msgs::String msg;
  msg.data = "LEDON";
  led_pub.publish(msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("button", 1000, buttonCallback);
  ros::Publisher led_pub = nh.advertise<std_msgs::String>("led", 1000);
  
  
  ros::spin();
  return 0;
}
