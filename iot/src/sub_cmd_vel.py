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
#database.child("Baggage_Status_Transit").update({"Luggage_A":"Ready To Move"})

import rospy
from iot.msg import custom_msg
from geometry_msgs.msg import *
from std_msgs.msg import *

vx = 0.0
az = 0.0
r_distance = 0.0
l_distance = 0.0
def subscriber():
    subcriber_cmd_vel = rospy.Subscriber('cmd_vel', Twist, callback_function)
    sub_rdist = rospy.Subscriber('r_dist', Float32, callback_function_rdist)
    sub_ldist = rospy.Subscriber('l_dist', Float32, callback_function_ldist)
    motor_status()
    
    rospy.loginfo("after motor_status")
    
    rospy.spin()

def callback_function(message):

    vx = message.linear.x; 
    vy = message.linear.y;
    vz = message.linear.z;
    
    ax = message.angular.x; 
    ay = message.angular.y;
    az = message.angular.z;
    
    rospy.loginfo("vx: %f"%vx)
    rospy.loginfo("az: %f"%az)
    return
def callback_function_rdist(message):
    rospy.loginfo("inside rdist")
    global r_distance 
    r_distance = message.data
    rospy.loginfo("right %f"%r_distance)
    return    
def callback_function_ldist(message):
    rospy.loginfo("inside ldist")
    global l_distance
    l_distance = message.data        
    rospy.loginfo("left %f"%l_distance)
    #motor_status()
    return
def motor_status():
    rospy.loginfo("inside motor_status")
    global r_distance 
    global l_distance 
    linear_x = (r_distance+l_distance)/2
    angular_z = (r_distance-l_distance)/0.173
    
    rospy.loginfo("linear_x: %f"%linear_x)
    rospy.loginfo("angular_z: %f"%angular_z)
    
    return
#    if (linear_x != vx) or (angular_z !=az):
#        return "Fault found"
#    else:
#        return "Working As Expected"                

def uploading_status():
    database.child("Faults").update({"Motor":motor_status()})
            
if __name__ == "__main__":
    rospy.init_node("sub_to_cmd_vel")
    subscriber()
