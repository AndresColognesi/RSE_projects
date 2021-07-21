#!/bin/sh
# Terminal 1 - World + Robot
xterm  -e  "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find home_service)/worlds/andres.world" &
sleep 5
# Terminal 2 - Localization using AMCL
xterm  -e  "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find home_service)/maps/map.yaml" & 
sleep 5
# Terminal 3 - RViz for Localization
xterm  -e  "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
# Terminal 4 - Pick Objects Node
xterm  -e  "rosrun pick_objects pick_objects_node"
