#!/usr/bin/env python
import pyrebase
firebaseConfig = {
    "apiKey": "AIzaSyA89kvBNFAz8wgvS297EDB_K_eSsJBXF4I",
    "authDomain": "fir-realtime-91e53.firebaseapp.com",
    "databaseURL": "https://fir-realtime-91e53-default-rtdb.firebaseio.com",
    "projectId": "fir-realtime-91e53",
    "storageBucket": "fir-realtime-91e53.appspot.com",
    "messagingSenderId": "540756156225",
    "appId" : "1:540756156225:web:e45d9d4fe770267b820bc0",
    "measurementId" : "G-GB8BKV9R3W"
  };
firebase = pyrebase.initialize_app(firebaseConfig)
storage = firebase.storage()
database = firebase.database()
database.child("Baggage_Status_Transit").update({"Luggage_A":"Ready To Move"})

import rospy
from iot.msg import custom_msg
from geometry_msgs.msg import *
from std_msgs.msg import *
from sensor_msgs.msg import *


vx = 0.0
vy = 0.0


def subscriber():
    subcriber_cmd_vel = rospy.Subscriber('scan', LaserScan, callback_function)

    
    rospy.loginfo("after motor_status")
    
    rospy.spin()

def callback_function(message):

    vx = message.time_increment; 
    vy = message.scan_time;

    
    rospy.loginfo("time_increment: %f"%vx)
    rospy.loginfo("scan_time: %f"%vy)
    

            
if __name__ == "__main__":
    rospy.init_node("sub_to_cmd_vel")
    subscriber()
