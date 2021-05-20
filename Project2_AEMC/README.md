# Project 2 - Go Chase It!

This projects consists in creating a wheeled robot that follows a white ball inside a simulation world based on it's camera image processing.

## Structure

The project consists of 2 packages: `/my_robot` and `/ball_chaser`. The first one constains all files needed for the dynamic simulation of the robot inside a test world, as well as all robot assets and the robot itself (`/meshes` and `/urdf`). Additionally to what is minimally required by the course, the robot was modeled using the Onshape CAD tool, and therefore the model can be accessed [here](https://cad.onshape.com/documents/2b220a0837bb66d113323dec/w/9a0097a8bb1ea4ca324e3bce/e/adca8ea51954d0e551172b3f "SimpleBot CAD") . Also, the `/my_robot/rviz` folder was created to host the `.rviz` file that configures the robot, camera and lidar on RViz. This file is automatically loaded in the `/my_robot/launch/world.launch` file to make things easier.

**NOTE:** The world file in this project is different from the one of Project 1. Some improvements were made based on the Udacity review comments on Project 1.

## How to Run

Create a catkin workspace and place both packages (`/my_robot` and `/ball_chaser`) inside the `catkin_ws/src` directory. Then build everithing and it should work. Just to explicitly put the commands for these base configurations:
```
mkdir -p catkin_ws/src
cd catkin_ws/src

# now copy the packages of this repo to this directory!!! #

catkin_init_workspace
cd ..
catkin make
```

With this made, 2 terminals will run the whole project. Go to the `/catkin_ws` directory in both terminals and run:

- Terminal 1
```
source devel/setup.bash
roslaunch my_robot world.launch
```

- Terminal 2
```
source devel/setup.bash
roslaunch ball_chaser ball_chaser.launch
```

Now just put the ball in the robot sight and it will mowe towards it! If the white ball can't be seen by the robot, it will stop moving.