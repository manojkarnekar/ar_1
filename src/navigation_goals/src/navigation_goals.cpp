#include "navigation_goals.hpp"




void navigation::Goal(){
    int n;
    long double d1, d2;
    vector<vector<long double>> v; 
    move_base_msgs::MoveBaseGoal goal;
    cout << "How many goal points you want to give: ";
    cin>>n;
    for(int i=0; i<n; i++){

        cout << "Enter x coordinate: ";
        cin>> d1;
        cout << "Enter y coordinate: ";
        cin>> d2;
        v.push_back({d1, d2});
        cout << "x = " << v[i][0] << " y = " << v[i][1] << endl;
    }

    int k = 0;
    while(k<n){

    MoveBaseClient ac("move_base", true);

    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }

    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = v[k][0];
    goal.target_pose.pose.position.y = v[k][1];
    goal.target_pose.pose.orientation.w = 1.0;

    ROS_INFO("Sending goal");
    ros::Duration(2).sleep();
    ac.sendGoal(goal);

    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Hooray, the base moved to the goal");
    else
        ROS_INFO("The base failed to move to the goal");
    k++;
    }

}



int main(int argc, char** argv){
  ros::init(argc, argv, "navigation");

    ros::NodeHandle nh; // create a node handle; need to pass this to the class constructor

    ROS_INFO("main: instantiating an object of type ExampleRosClass");
    navigation navigation(&nh);

    ros::Duration(2).sleep();
    navigation.Goal();

  return 0;
}