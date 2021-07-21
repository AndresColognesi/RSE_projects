#!/bin/sh
# Terminal 1 - World + Robot
xterm  -e  "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find home_service)/worlds/andres.world" &
sleep 5
# Terminal 2 - SLAM package
xterm  -e  "roslaunch turtlebot_gazebo gmapping_demo.launch" & 
sleep 5
# Terminal 3 - RViz for Mapping
xterm  -e  "roslaunch turtlebot_rviz_launchers view_navigation.launch" & 
sleep 5
# Terminal 4 - Keyboard Control
xterm  -e "roslaunch turtlebot_teleop keyboard_teleop.launch"
