#!/usr/bin/env python

import rospy
from iot.msg import custom_msg
from geometry_msgs import *
def publisher():

    pub     = rospy.Publisher('chatter', custom_msg, queue_size=10)

    rate    = rospy.Rate(1)

    msg_to_publish  = custom_msg()

    counter = 0
    while not rospy.is_shutdown():
#        msg_to_publish.header = "its ok"
#        msg_to_publish.pick_place = "A"
#        msg_to_publish.count = counter        
#        msg_to_publish.time_stamp =  str(rospy.get_time())
        msg_to_publish.Base.linear.x = 1.21
        msg_to_publish.Base.linear.y = 1.22
        msg_to_publish.Base.linear.z = 1.23
        msg_to_publish.Base.angular.x = 2.21
        msg_to_publish.Base.angular.y = 2.22
        msg_to_publish.Base.angular.z = 2.23
        pub.publish(msg_to_publish)
        rospy.loginfo(msg_to_publish)
        counter += 1
        rate.sleep()


if __name__ == "__main__":
    rospy.init_node("simple_pub")
    publisher()
