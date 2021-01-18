#include <ros/ros.h>
#include <std_msgs/String.h>

void buttonCallback(const std_msgs::String::ConstPtr& msg);

ros::NodeHandle nh;
ros::Publisher led_pub = nh.advertise<std_msgs::String>("led", 1000);

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::Subscriber sub = nh.subscribe("button", 1000, buttonCallback);
  
  ros::spin();
  return 0;
}

void buttonCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("LED is : [%s]", msg->data.c_str());
  std_msgs::String msg_;
  msg_.data = "LEDON";
  led_pub.publish(msg_);
}
