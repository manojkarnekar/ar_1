#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include <sstream>
#include <time.h>
#include <memory>
#include <algorithm>
#include <vector>
#include <cstdlib>


using namespace std;


class marker_rviz {

    public:

    marker_rviz(ros::NodeHandle* nodehandle);
    ros::NodeHandle nh_;

    void resetUniqueId();
    int getUniqueId();
    void poseCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& pose_message);
    void initializeSubscribers(); // we will define some helper methods to encapsulate the gory details of initializing subscribers, publishers and services
    void initializePublishers();
    void marker();

    geometry_msgs::PoseWithCovarianceStamped pose;
    ros::Publisher marker_pub;
    ros::Subscriber pose_subscriber;
    int unique_id;
};


marker_rviz::marker_rviz(ros::NodeHandle* nodehandle):nh_(*nodehandle)
{ // constructor
    ROS_INFO("in class constructor of ExampleRosClass");
    initializeSubscribers(); // package up the messy work of creating subscribers; do this overhead in constructor
    initializePublishers();
}