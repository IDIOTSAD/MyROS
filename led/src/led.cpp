#include <ros/ros.h>
#include <std_msgs/String.h>
#include <wiringPi.h>

#define LED_PIN 5 // LED Pin
#define SW_PIN 6  // Switch Pin

int main(int argc, char **argv)
{
    ros::init(argc, argv, "led");
    ros::NodeHandle nh;
    ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("Message", 1000);
    
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
