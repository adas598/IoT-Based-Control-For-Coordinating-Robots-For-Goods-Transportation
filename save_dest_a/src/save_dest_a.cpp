#include <iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>

#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <tf/transform_listener.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseStamped.h>

using namespace std;

geometry_msgs::PoseStamped pose_odom, pose_map;
//pose_odom.header.frame_id="odom";
//pose_odom.header.frame_id="map";

void get_pose()
{
    tf::TransformListener listener;    
    try
    {
        listener.transformPose("map", pose_odom, pose_map);
    }
    catch(tf::TransformException &exception)
    {
        ROS_ERROR("%s", exception.what());
    }
}

void pose_callback(const nav_msgs::Odometry::ConstPtr& msg)
{
    pose_odom.header.stamp = ros::Time();
    pose_odom.pose.position.x = msg->pose.pose.position.x;
    pose_odom.pose.position.y = msg->pose.pose.position.y;
    pose_odom.pose.position.z = msg->pose.pose.position.z;
    pose_odom.pose.orientation.x = msg->pose.pose.orientation.x;
    pose_odom.pose.orientation.y = msg->pose.pose.orientation.y;
    pose_odom.pose.orientation.z = msg->pose.pose.orientation.z;
    pose_odom.pose.orientation.w = msg->pose.pose.orientation.w;
    return;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "save_dest_a");
    ros::NodeHandle n;
    ros::Subscriber sub_odom = n.subscribe("odom", 1000, pose_callback);
    if (n.ok())
    {
        fstream file;
        file.open("dest_a.txt", ios::app);
        
        get_pose();
        
        file<<pose_map.pose.position.x<<endl
            <<pose_map.pose.position.y<<endl
            <<pose_map.pose.position.z<<endl
            <<pose_map.pose.orientation.x<<endl
            <<pose_map.pose.orientation.y<<endl
            <<pose_map.pose.orientation.z<<endl
            <<pose_map.pose.orientation.w;
        
        file.close();   
    }
    
    ros::spinOnce();
    return 0;
}
