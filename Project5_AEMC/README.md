# Project 5 - Home Service Robot

This is the last project of the course. It consists in developing a home service robot application that autonomously picks up and delivers an object (the object actually only disappears, the robot makes the autonomous navigation part only). This project uses turtlebot as the autonomous robot.


## Running the project

There are different steps to be tested for this project and it's navigation stack. Each launch is explained below. First we will show the final launch, and next are explained all test launches.

### Home Service Robot Launch

So that the project is cleaner and the final version doesn't interfeere in the test versions, all nodes needed for the home service robot are placed inside the `/home_service` package. The files and nodes preserve the same names, but they have some substantial communication changes since they interact via client/server with each other. The logic is very simple: the `pick_objects_node` will command the autonomous navigation of the robot, sending the goals. When certain events are held, the `pick_objects_node` calls a service from `add_marker_node`, that will properly handle the spawning of the virtual object in RViz.

To launch all this application it is only necessary to navigate to the `/catkin_ws` of the project, source it, then navigate to the `/scripts` folder and run the `home_service.sh` by typing `./home_service.sh`. This will automatically run following commands and terminals. If everything runs properly, the robot will navigate to the pickup position, where a marker will be displayed in RViz. Reaching this position, the marker will disapear and the robot will wait for 5 seconds to simulate a pickup. Then, the robot will navigate to the dropoff position. Finally, after reaching this position, the marker will be displayed on the dropoff position.

**Terminal 1 - World + Robot**
```
roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find home_service)/worlds/andres.world
```

**Terminal 2 - Localization using AMCL**
```
roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find home_service)/maps/map.yaml
```

**Terminal 3 - RViz for Localization**
```
roslaunch home_service view_navigation.launch
```

**Terminal 4 - Autonomous navigation to 2 goals**
```
rosrun home_service pick_objects_home
```

**Terminal 5 - Adding Markers on RViz**
```
rosrun home_service add_markers_home
```

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! REVIEW COMMANDS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

### Test Launches

the following sections explain some test launches developed to later on create the final launch that is explained on the above section

#### 1 - SLAM Test

To test the SLAM feature of the project, navigate to the `/catkin_ws` of the project, source it, then navigate to the `/scripts` folder and run the `test_slam.sh` by typing `./test_slam.sh`. This will automatically run following commands:

**Terminal 1 - World + Robot**
```
roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find home_service)/worlds/andres.world
```

**Terminal 2 - SLAM package**
```
roslaunch turtlebot_gazebo gmapping_demo.launch
```

**Terminal 3 - RViz for Mapping**
```
roslaunch turtlebot_rviz_launchers view_navigation.launch
```

**Terminal 4 - Keyboard Control**
```
roslaunch turtlebot_teleop keyboard_teleop.launch
```

Now you can navigate and map the environment with terminal 4. To save the generated 2D map, run on a new terminal: `rosrun map_server map_saver -f <mapname> map:=/your/costmap/topic`. See [this link](http://wiki.ros.org/map_server#map_saver) for further reference on saving.


#### 2 - Localization and Navigation Test

First, it is necessary to generate a 2D map of the world, so that the robot can localize itself in it. Using the SLAM approach above, with the gmapping package, it is possible to generate a 2D map (`.pgm`and `.yaml` files). But we already mapped our world in **Project 4 - Map My World** using RTAB-Map. The output of this project was a `.db` file with lots of information of the mapping activity. We want to extract a 2D map from this output. For this, following steps were made:

**NOTE:** You won't need to do these steps if you run this project as is. This is here for guideline on how to do the procedure for other maps. See [this link](https://answers.ros.org/question/217097/export-2d-map-from-rviz-andor-rtab-map/) for further reference.

**Terminal 1 - Roscore**
```
roscore
```

**Terminal 2 - Load Database**
```
rosrun rtabmap_ros rtabmap _database_path:=<PATH TO YOUR FILE>/<FILE NAME>.db
```

**Terminal 3 - Create Map from Database**
```
rosrun map_server map_saver map:=proj_map
```

**Terminal 4 - Publish map**
```
rosservice call /publish_map 1 1 0
```

This will create a `map.pgm` and a `map.yaml` file in the folder that you are at in terminal 3. Cut these files and move them to the desired location of the current project. In our case here, this was already done! With those 2 files placed inside the `/map` package of this repo, navigate to the `/catkin_ws` directory, source it, go to the `/scripts` folder and run the `test_navigation.sh` by typing `./test_navigation.sh`. This will automatically run following commands to localize the robot inside the world:

**Terminal 1 - World + Robot**
```
roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find home_service)/worlds/andres.world
```

**Terminal 2 - Localization using AMCL**
```
roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find home_service)/maps/map.yaml
```

**Terminal 3 - RViz for Localization**
```
roslaunch turtlebot_rviz_launchers view_navigation.launch
```

#### 3 - Pick Object (Autonomous Navigation)

For this test, 2 goal locations are sent to the robot, one for pickup and one for drop off. The robot navigates to the first goal then to the second one. This is done via the `pick_object_node`. To run this test, simply navigate to the `/catkin_ws` directory, source it, go to the `/scripts` folder and run the `pick_objects.sh` by typing `./pick_objects.sh`. This will launch following terminals and commands:

**Terminal 1 - World + Robot**
```
roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find home_service)/worlds/andres.world
```

**Terminal 2 - Localization using AMCL**
```
roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find home_service)/maps/map.yaml
```

**Terminal 3 - RViz for Localization**
```
roslaunch turtlebot_rviz_launchers view_navigation.launch
```

**Terminal 4 - Autonomous navigation to 2 goals**
```
rosrun pick_objects pick_objects_node
```

#### 4 - Add Markers (Visualization on RViz)

This will later be combined with the PickUp node, making the virtual object visualization more realistic for this pickup and drop off problem. This test will display a marker in RViz for 5 seconds on the pickup location. Then the marker will disappear for 5 seconds and appear again on the drop off location. To run this test, simply navigate to the `/catkin_ws` directory, source it, go to the `/scripts` folder and run the `add_markers.sh` by typing `./add_markers.sh`. This will launch following terminals and commands:

**NOTE:** The RViz file was altered for this test, adding a Marker in RViz so that the virtual object can be seen.

**Terminal 1 - World + Robot**
```
roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find home_service)/worlds/andres.world
```

**Terminal 2 - Localization using AMCL**
```
roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find home_service)/maps/map.yaml
```

**Terminal 3 - RViz for Localization**
```
roslaunch home_service view_navigation.launch
```

**Terminal 4 - Adding Markers on RViz**
```
rosrun add_markers add_markers_node
```