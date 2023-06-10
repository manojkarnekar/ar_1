#include "rviz_marker.hpp"



void marker_rviz::initializeSubscribers()
{
    ROS_INFO("Initializing Subscribers");
    pose_subscriber = nh_.subscribe<geometry_msgs::PoseWithCovarianceStamped>("/amcl_pose", 1, &marker_rviz::poseCallback,this);  
}

void marker_rviz::initializePublishers()
{
    ROS_INFO("Initializing Publishers");
    marker_pub = nh_.advertise<visualization_msgs::Marker>("/visualization_marker", 1);
}


void marker_rviz::poseCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& pose_message){
    pose.pose.pose.position.x = pose_message->pose.pose.position.x;
    pose.pose.pose.position.y = pose_message->pose.pose.position.y;
    pose.pose.pose.orientation.x = pose_message->pose.pose.orientation.x;
    pose.pose.pose.orientation.y = pose_message->pose.pose.orientation.y;
    pose.pose.pose.orientation.z = pose_message->pose.pose.orientation.z;
    pose.pose.pose.orientation.w = pose_message->pose.pose.orientation.w;
}

void marker_rviz::marker(){
    ros::Rate r(1);
    unique_id = 0;
    uint32_t shape = visualization_msgs::Marker::ARROW;

    while (ros::ok())
    {
        visualization_msgs::Marker marker;
        marker.header.frame_id = "/map";
        marker.header.stamp = ros::Time::now();
        marker.ns = "basic_shapes";
        marker.id = getUniqueId();
        marker.type = shape;
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = pose.pose.pose.position.x;
        marker.pose.position.y = pose.pose.pose.position.y;
        marker.pose.position.z = 0;
        marker.pose.orientation.x = pose.pose.pose.orientation.x;
        marker.pose.orientation.y = pose.pose.pose.orientation.y;
        marker.pose.orientation.z = pose.pose.pose.orientation.z;
        marker.pose.orientation.w = pose.pose.pose.orientation.w;
        marker.scale.x = 0.3;
        marker.scale.y = 0.05;
        marker.scale.z = 0.02;
        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0;
        marker.lifetime = ros::Duration();

        while (marker_pub.getNumSubscribers() < 1)
        {
        ROS_WARN_ONCE("Please create a subscriber to the marker");
        sleep(1);
        }
        marker_pub.publish(marker);
        ros::spinOnce();
        r.sleep();
  }
}

int marker_rviz::getUniqueId()
{
  int temp_id = unique_id;
  unique_id += 1;
  return temp_id;
}


int main( int argc, char** argv )
{
    ros::init(argc, argv, "marker_rviz");
    ros::NodeHandle nh; // create a node handle; need to pass this to the class constructor

    ROS_INFO("main: instantiating an object of type ExampleRosClass");
    marker_rviz marker_rviz(&nh);

    marker_rviz.marker();

    return 0;

}