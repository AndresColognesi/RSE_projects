# Project 3 - Where Am I?

This project consists in making our robot localize itself inside our Gazebo world using the Adaptive Monte Carlo Localization algorithm (AMCL).

## Structure

This project has 2 main folders: `/packages` contains the projects packages (`/my_robot` and `/teleop_keyboard_twist`); and `/screenshots` contains some screenshots from RViz showing that the robot is able to localize itself.

The `/my_robot` package contains the robot model, the gazebo world, as wll as the launch files and the RViz configurations for the project.

## Run the Project

To test this project, 3 terminals are needed. The first one will launch the world and the robot, the second one will launch the AMCL infrastructure and the third one (optional) launches the teleop package to control the robot with keyboard commands. The robot can also be controlled (autonomously) using the **2D nav goal** feature from RViz. Just click on it (central top icon with green arrow) and choose a point for the robot to localize itself - click, drag to show de orientation and it's done.

All the terminals must navigate to the `/catkin_ws` workspace built for the project. The run following commands on each one of them:

**Terminal 1 - World + Robot**
```
source devel/setup.bash
roslaunch my_robot world.launch
```

**Terminal 2 - AMCL + RViz**
```
source devel/setup.bash
roslaunch my_robot amcl.launch
```

**Terminal 3 (OPTIONAL) - Teleop Keyboard**
```
source devel/setup.bash
rosrun teleop_twist_keyboard teleop_twist_keyboard.launch
```