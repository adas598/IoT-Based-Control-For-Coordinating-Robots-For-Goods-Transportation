#!/usr/bin/env python

import rospy
from iot.msg import custom_msg

def subscriber():
    sub = rospy.Subscriber('chatter', custom_msg, callback_function)

    rospy.spin()

def callback_function(message):
    header_received = message.header
    pick_place_received = message.pick_place
    count_received = message.count
    time_stamp_received = message.time_stamp

    rospy.loginfo("I received: %s"%header_received)
    rospy.loginfo("I received place: %s"%pick_place_received)
    rospy.loginfo("I received: %d"%count_received)
    rospy.loginfo("I received: %s"%time_stamp_received)
    rospy.loginfo("converted: %f"%float(time_stamp_received))
if __name__ == "__main__":
    rospy.init_node("simple_sub")
    subscriber()
