#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our shape type to be a sphere
  uint32_t shape = visualization_msgs::Marker::SPHERE;


    visualization_msgs::Marker marker;
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
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    /*while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }*/
    ROS_INFO("Waiting 10 seconds so we can see the node starting...");
    sleep(10);
    ROS_INFO("Started!");
    
    // Marker on pickup location:
    ROS_INFO("Displaying marker on pickup location for 5 seconds");
    marker_pub.publish(marker);
    // Wait 5 seconds:
    sleep(5);

    // Remove marker:
    ROS_INFO("Marker removed for 5 seconds");
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    // Wait 5 seconds:
    sleep(5);

    // Marker on drop off location:
    ROS_INFO("Displaying marker on drop off location");
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.y = 0; //changing y coordinate
    marker_pub.publish(marker);
    
  // Keeping the node alive
  ros::spin();
}
