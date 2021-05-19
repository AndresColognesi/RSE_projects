#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ROS_INFO_STREAM("Moving the robot");

    // Request velocity commands
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the drive_bot service and pass the requested velocities
    if (!client.call(srv))
        ROS_ERROR("Failed to call service drive_bot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    
    // Defining Constants and Variables //
    int treshold = img.width/3; //obtain the width of each decision block
  
    // Just for debug:
    //ROS_INFO_STREAM("width = " + std::to_string(img.width));
    //ROS_INFO_STREAM("treshold = " + std::to_string(treshold));
    //ROS_INFO_STREAM("step = " + std::to_string(img.step));
    
    float lin_x = 0; //desired linear x velocity
    float ang_z = 0; //desired angular z velocity

    float vx = 0.5; //adopted linear velocity (positive = foward)
    float vz = 0.5; //adopted angular velocity (positive = turn left)

    bool no_ball = true;

    // Loop over pixels and channels (3 channels)//
    for (int i = 0; i < img.height * img.step; i+=3) {
        if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel) { //R, G, B channels of pixel

            //Calculate horizontal pixel position:
            int j = int(i % img.step / 3); //there are 3 channels for each pixel

            //Check pixel position
            if (j < treshold) { //pixel on the left side
                //Go left:
                lin_x = vx;
                ang_z = vz;

                no_ball = false; //ball was found
            }
            else if (j >= treshold && j <= 2*treshold) { //pixel is in the middle
                //Go foward:
                lin_x = vx;
                ang_z = 0;

                no_ball = false; //ball was found
            }
            else if (j > 2*treshold) { //pixel on the right side
                //Go right:
                lin_x = vx;
                ang_z = -vz;

                no_ball = false; //ball was found
            }

            break; //end loop
        }
    //finished loop:    
    //no_ball will still be true if white ball is not present in the image!
    }

    if (no_ball) { //no white ball in sight
        //Stop:
        lin_x = 0;
        ang_z = 0;
    }

    //Send desired velocity to drive_robot:
    drive_robot(lin_x, ang_z);  
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}