# AMR Simulation

## Instructions

- clone the repository

```bash
git clone https://github.com/manojkarnekar/ar_1.git
```

```bash
cd ar_1
```

- build the project

```bash
catkin_make
```
- source the workspace

```bash
source devel/setup.bash
```

### Goal 1

- Finding the bug in robot description package. There are two bug in there. First is laser plugin <frameName>laser_1</frameName> has to be replaced by <frameName>laser_link</frameName> as /scan topic is with repect to that frame. Also laser link is roated by 90 degree, now this can be seen with you localized using standard localization packages like amcl localization or micvision. So make r p y to 0 0 0. That will work.

### Goal 2

#### Sub Goal 1

- Launch main.launch

```bash
roslaunch ar1_description main.launch
```

-Slam gmapping

```bash
sudo apt install ros-melodic-gmapping
```

```bash
rosrun gmapping slam_gmapping scan:=scan
```

- Use rqt_robot_steering for moving the bot and making the map.

```bash
rosrun rqt_robot_steering rqt_robot_steering
```

- Save the map using command

```bash
rosrun map_server map_saver -f map_name
```

#### Sub Goal 2

- Move base is used for navigation of the robot in the saved map. Here the global planner is Navfn and local planner is DWA local planner.

- To launch the navigation use

```bash
roslaunch ar1_description amcl_localization.launch
```

- This launch file contain robot_state_publisher, joint_state_publisher, world file, map_server, rviz config, local planner, and micvision. Local planner itself contains all information of global costmap, local costmap and base_local params files. Now the bot is ready to move autonomously.

- After launching this file give a minute for lidar to settle and use following command to localize the bot.

```bash
rosservice call /Startlocalization
```

#### Sub Goal 3

- Add footprint of the robot. Also frequencies of the map can be controlled.


### Goal 3

- The package navigation_goals contains navigation_goals.cpp. This cpp file can take waypoints from user and the ready to navigate to these points in order.

### Goal 4

- The package navigation_goals contains rviz_.cpp. Which records marker.

- To launch goal 3 and goal 4, follow the command.

```bash
roslaunch navigation_goals navigation.launch
```

- Enter number the number of waays you want.
- One by one enter x coordinate of wayspoint and y coordinate of y point.
- once the bot receives all points the bot navigate to these points in order.
