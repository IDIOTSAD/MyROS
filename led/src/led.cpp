#include <ros/ros.h>
#include <std_msgs/String.h>
#include <wiringPi.h>

#define LED_PIN 5 // LED Pin
#define SW_PIN 6  // Switch Pin

void ledCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("LED is : [%s]", msg->data.c_str());
  if(msg->data.c_str() == "LEDON")
      digitalWrite(LED_PIN, HIGH);
  else
      digitalWrite(LED_PIN, LOW);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "led");
    ros::NodeHandle nh;
    ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("button", 1000);
    ros::Subscriber sub = nh.subscribe("led", 1000, ledCallback);
    std_msgs::String msg;

    wiringPiSetupGpio();
    pinMode(LED_PIN, OUTPUT);
    pinMode(SW_PIN, INPUT);
    ROS_INFO("GPIO has been set as OUTPUT.");

    while (ros::ok())
    {
        if (digitalRead(SW_PIN))
        {
            msg.data = "ON";
            /*
            digitalWrite(LED_PIN, HIGH);
            ROS_INFO("Set GPIO HIGH");
            */
            ros::Duration(1.0).sleep();
            chatter_pub.publish(msg);
        }
        else
        {
            msg.data = "OFF";
            /*
            digitalWrite(LED_PIN, LOW);
            ROS_INFO("Set GPIO LOW");
            */
            ros::Duration(1.0).sleep();
            chatter_pub.publish(msg);
        }
        ros::spinOnce();
    }
}
