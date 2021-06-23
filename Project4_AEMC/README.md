# Project 4 - Map My World

This project consists in using the RTAB-Map SLAM package to perform mapping of the simulation world.

## Structure

This project has only one main folder, that is the `my_robot` package. Additionally, it is necessary to clone the [teleop keyboard package](https://github.com/ros-teleop/teleop_twist_keyboard) to drive the robot around and map the environment. The generated map is not present here because it is very heavy and was having problems to upload.

## Run the Project

To test this project, 3 terminals are needed. The first one will launch the world and the robot, the second one will launch the teleop package to control the robot with keyboard commands, and the last one launches the RTAB-Map in mapping mode. The robot will generate the map database and save it under `/root/.ros/` as `rtabmap.db`. If you want to change this, change the `mapping.launch` file.

All the terminals must navigate to the `/catkin_ws` workspace built for the project. Then run following commands on each one of them:

**Terminal 1 - World + Robot**
```
source devel/setup.bash
roslaunch my_robot world.launch
```

**Terminal 2 - Teleop Keyboard**
```
source devel/setup.bash
roslaunch my_robot teleop.launch
```

**Terminal 3 - RTAB-Map Mapping**
```
source devel/setup.bash
roslaunch my_robot mapping.launch
```

To make a good map of the environment it is best to go arround the map 3 times in similar trajectories. In this way, loop-closures are generated and the generated map will be more accurate. To visualize the resulting `rtabmap.db`, type following command:
```
```

**WARNING:** After mapping, save a copy of `rtabmap.db` in another directory. If you start another `mapping.launch` it will delete the previous `rtabmap.db` file inside `/root/.ros/` **!!!**