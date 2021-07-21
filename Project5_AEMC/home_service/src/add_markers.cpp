#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "home_service/EditMarker.h"

#include <std_msgs/String.h>

//--- Defining our Virtual Object Marker Class ---//

class VO_Marker {
  private: // Class attributes
    // shape type for our virtual object
    uint32_t shape;
    // marker message
    visualization_msgs::Marker marker;
    // publishers:
    ros::Publisher marker_pub;
    // service:
    ros::ServiceServer service;
    // node handle:
    ros::NodeHandle n;
 
  public: // Constructor and methods
    // Constructor:
    VO_Marker(){

      //-- Populating Attributes --//

      // Set our shape type to be a sphere
      shape = visualization_msgs::Marker::SPHERE;
      // Set the frame ID and timestamp.  See the TF tutorials for information on these.
      marker.header.frame_id = "map";
      marker.header.stamp = ros::Time::now();
      
      // Set the namespace and id for this marker.  This serves to create a unique ID
      // Any marker sent with the same namespace and id will overwrite the old one
      marker.ns = "basic_shapes";
      marker.id = 0;
      
      // Set the marker type.  It is allways a SPHERE
      marker.type = shape;
      
      // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
      marker.action = visualization_msgs::Marker::ADD;
      
      // Set the pose of the marker as the pickup position.  This is a full 6DOF pose relative to the frame/time specified in the header
      marker.pose.position.x = 1.0;
      marker.pose.position.y = 1.0;
      marker.pose.position.z = 0;
      marker.pose.orientation.x = 0.0;
      marker.pose.orientation.y = 0.0;
      marker.pose.orientation.z = 0.0;
      marker.pose.orientation.w = 1.0;
      
      // Set the scale of the marker -- 1x1x1 here means 1m on a side
      marker.scale.x = 1.0;
      marker.scale.y = 1.0;
      marker.scale.z = 1.0;
      
      // Set the color -- be sure to set alpha to something non-zero!
      marker.color.r = 1.0f;
      marker.color.g = 0.0f;
      marker.color.b = 0.0f;
      marker.color.a = 1.0;
      
      marker.lifetime = ros::Duration();

      //-- Set publisher, server and publish marker --//
      marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
      service = n.advertiseService("edit_markers", &VO_Marker::editMarker, this);
      ROS_INFO("Ready to edit markers.");
    }
  

    // Methods

    //--- Service callback function ---//
    bool editMarker(home_service::EditMarker::Request  &req,
                    home_service::EditMarker::Response &res)
    {
      if (req.adding){ // Display virtual object
        // Marker will be added:
        marker.action = visualization_msgs::Marker::ADD;
        // Change position:
        marker.pose.position.x = req.x;
        marker.pose.position.y = req.y;
        // Publish marker:
        marker_pub.publish(marker);
        // Log information:
        ROS_INFO("Displaying virtual object.");
      }
      else { // Hide virtual object
        // Marker will be hidden:
        marker.action = visualization_msgs::Marker::DELETE;
        // Publish marker:
        marker_pub.publish(marker);
        // Log information:
        ROS_INFO("Virtual object was picked up!");
      }
      return true;
    }
  
}; //end of class



int main( int argc, char** argv )
{
  // Initialize node
  ros::init(argc, argv, "add_markers_server");

  // Create marker object that will start the marker server node
  VO_Marker my_marker = VO_Marker();

  // Keeping the node alive
  ros::spin();
}