# Project 1 - Build My World

This projects consists in creating models, world and plugin for Gazebo.

## Models

The 2 models created are: a 4 wheeled robot, being a model with joints - `4wbot` of this repo; and one building model - `House` model of this repo. All models created are located in the `/model` folder of this repo.

## World

The world file is located on the `/world` folder of this repo and contains the created custom models and some standard models available on the gazebo models database. It was generated via Gazebo GUI, so it is not the best modular approach to build a world. Idealy, whe world file would import the models from the model file, and for this it is necessary to change the `GAZEBO_MODEL_PATH` variable. See the following links for more instructions on this matter:
- https://sir.upc.edu/projects/rostutorials/8-gazebo_basics_tutorial/
- https://answers.gazebosim.org//question/13391/how-to-set-gazebo_plugin_path-correctly-and-add-the-plugin-into-gazebo_ros/

## Plugin

The project also has a Gazebo Plugin located on the `/script` folder. It works together with the `CMakeLists.txt` file to run properly and was based on the ["hello world plugin" tutorial from Gazebo](http://gazebosim.org/tutorials?tut=plugins_hello_world&cat=write_plugin). To make this plugin work properly, create your own `/build` folder following the steps of the tutorial - the build files are system dependent! This means that it will only work in your own system.