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


import rospy
from iot.msg import custom_msg
from geometry_msgs.msg import *
from std_msgs.msg import *
from sensor_msgs.msg import *

unexpected_time_increment = 0.0
unexpected_scan_time = 0.2

def subscriber():
    subcriber_cmd_vel = rospy.Subscriber('scan', LaserScan, callback_function)

    
    rospy.loginfo("after motor_status")
    
    rospy.spin()

def callback_function(message):
    global unexpected_time_increment
    global unexpected_scan_time
    
    vx = message.time_increment; 
    vy = message.scan_time;

    if (vx == unexpected_time_increment) or (unexpected_scan_time < vy):
        upload_to_firebase("Fault Detected")
    else:
        upload_to_firebase("Working As Expected")
    rospy.loginfo("time_increment: %f"%vx)
    rospy.loginfo("scan_time: %f"%vy)
    
def upload_to_firebase(message):
    database.child("Faults").update({"LIdar":message})
            
if __name__ == "__main__":
    rospy.init_node("sub_to_cmd_vel")
    subscriber()
