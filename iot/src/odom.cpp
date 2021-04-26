#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float32.h>

int main(int argc, char **argv){

    ros::init(argc, argv, "belt_odom_pub");
    ros::NodeHandle n;
    ros::Time current_time, previous_time;

    // ros variables used by logic
    tf::TransformBroadcaster odom_broadcaster;      //used to update odom tf
    nav_msgs::Odometry odom;                        //used to update odom values
    //Encoder_Values encoder_values;                  //class instance used to retrieve encoder distance
    geometry_msgs::Quaternion odom_quat;            //used to get the quarternion/orientation for odom tf and odom
    geometry_msgs::TransformStamped odom_trans;     //used to send the updated geometry messages to update odom tf

    //ros::Subscriber l_sub = n.subscribe("l_dist", 1000, &Encoder_Values::left_enc_cb, &encoder_values);
    //ros::Subscriber r_sub = n.subscribe("r_dist", 1000, &Encoder_Values::right_enc_cb, &encoder_values);
    ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("belt/odom", 1000);
    ros::Rate loop_rate(30);

    while(ros::ok()){
        ros::spinOnce();

        current_time = ros::Time::now();

        odom_quat = tf::createQuaternionMsgFromYaw(0.0);
        // ROS_INFO("vy is: %f", vy);

        odom_trans.header.stamp = current_time;
        odom_trans.header.frame_id = "belt/odom";
        odom_trans.child_frame_id = "belt/base_link";
        odom_trans.transform.translation.x = 0.0;
        odom_trans.transform.translation.y = 0.0;
        odom_trans.transform.translation.z = 0.0;
        odom_trans.transform.rotation = odom_quat;

        odom_broadcaster.sendTransform(odom_trans);

        odom.header.stamp = current_time;
        odom.header.frame_id = "belt/odom";
        odom.pose.pose.position.x = 0.0;
        odom.pose.pose.position.y = 0.0;
        odom.pose.pose.position.z = 0.0;
        odom.pose.pose.orientation = tf::createQuarternionMsgRollPitchYaw(0,0,0);
        odom.twist.twist.linear.x = 0.0;
        odom.twist.twist.linear.y = 0.0;
        odom.twist.twist.linear.z = 0.0;
        odom.twist.twist.angular.x = 0.0;
        odom.twist.twist.angular.y = 0.0;
        odom.twist.twist.angular.z = 0.0;

        previous_time = current_time;

        odom_pub.publish(odom);
        loop_rate.sleep();
    }
    return 0;
}
