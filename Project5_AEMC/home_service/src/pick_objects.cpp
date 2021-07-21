#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "home_service/EditMarker.h"

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the spick_objects node
  ros::init(argc, argv, "pick_objects_client");
  
  // Create node handler:
  ros::NodeHandle n;
  // Create client for edit_markers service of the add_markers.cpp file
  ros::ServiceClient client = n.serviceClient<home_service::EditMarker>("edit_markers");
  // Create service object:
  home_service::EditMarker srv;

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();


  // Goal 1 - Pickup //
  
  // Define the first position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 1.0;
  goal.target_pose.pose.position.y = 1.0;
  goal.target_pose.pose.orientation.w = 2.0;

   // Send the first goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("The robot reached the pickup position.");
  else
    ROS_INFO("The robot failed to reach the pickup configuration!");
  
  // Set data for service request and call service to hide object:
  srv.request.adding = false;
  client.call(srv);

  // Wait for 5 seconds
  ROS_INFO("Waiting for 5 seconds...");
  ros::Duration(5.0).sleep();


  // Goal 2 - Drop off //
  
  // Define the second position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 1.0;
  goal.target_pose.pose.position.y = 0.0;
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the second goal position and orientation for the robot to reach
  ROS_INFO("Sending drop off goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("The robot reached the drop off position.");
  else
    ROS_INFO("The robot failed to reach the drop off configuration!");
  
  // Set data for service request and call service to display object:
  srv.request.adding = true;
  srv.request.x = goal.target_pose.pose.position.x;
  srv.request.y = goal.target_pose.pose.position.y;
  client.call(srv);


  // Wait for 10 seconds only to display message on terminal
  ROS_INFO("Mission Complete! Congratulations!");
  ros::Duration(10.0).sleep();

  return 0;
}
