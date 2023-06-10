#include <ros/ros.h>
#include <iostream>
#include <iomanip>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


class navigation {

    public:

    navigation(ros::NodeHandle* nodehandle);
    ros::NodeHandle nh_;
    void Goal();

};


navigation::navigation(ros::NodeHandle* nodehandle):nh_(*nodehandle)
{ // constructor
    ROS_INFO("in class constructor of ExampleRosClass");
}