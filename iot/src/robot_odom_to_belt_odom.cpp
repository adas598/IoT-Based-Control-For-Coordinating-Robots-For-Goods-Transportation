#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "robot_belt_tf_publisher");
    ros::NodeHandle n;
    ros::Rate r(100);

    tf::TransformBroadcaster broadcaster;

    while(n.ok())
    {
        broadcaster.sendTransform(
            tf::StampedTransform(
                tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.0, -0.2, 0.0)),
                ros::Time::now(), 
                "belt/odom", 
                "odom"
            )
        );
		broadcaster.sendTransform(
            tf::StampedTransform(
                tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.25, 0.05, 0.0)),
                ros::Time::now(), 
                "belt/odom", 
                "belt/a"
            )
        );
        broadcaster.sendTransform(
            tf::StampedTransform(
                tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.25, -0.05, 0.0)),
                ros::Time::now(), 
                "belt/odom", 
                "belt/b"
            )
        );
        r.sleep();
    }
    return 0;
}
