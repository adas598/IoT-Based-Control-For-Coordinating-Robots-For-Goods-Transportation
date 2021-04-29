#! /usr/bin/env python

import rospy
import actionlib
from save_dest_a.msg import move_goalAction, move_goalGoal, move_goalResult
import geometry_msgs.msg
from std_msgs.msg import String
from queue import Queue
from firebase_data import *
import tf 

queue = Queue(maxsize = 50)

def goal_client():
	global queue
	client = actionlib.SimpleActionClient('send_goal',move_goalAction)
	# Waits until the action server has started up and started
	client.wait_for_server()
	#listening for goals.
	listener = tf.TransformListener()
	goal = move_goalGoal()
	goal.goal_pose.header.frame_id = "map"
	
# 	Gets goal from the queue
	if queue.empty:
		arduino_msg = ""
	else:
		arduino_msg = queue.get()
	
# 	************************************* Start of logic ***************************************
# 	********************************************************************************************
	if arduino_msg == "":
		return 
	else:
## ****************************************** FOR A ************************************************	
		if arduino_msg == "a":
			upload_to_firebase("Luggage_A","Ready To Move")
			now = rospy.Time.now()
			listener.waitForTransform("map", "belt/a", now, rospy.Duration(4.0))
			(trans,rot) = listener.lookupTransform("map", "belt/a", now)
			goal.goal_pose.pose.position = trans
			goal.goal_pose.pose.orientation = rot
			# Sends the goal to the action server.
			client.send_goal(goal)
			
			# Waits for the server to finish performing the action.
			client.wait_for_result()
			with open("/home/ayush-pi4/fyp_belt_ws/src/save_dest_a/src/dest_a.txt",'r') as dest_a: 
				lines = dest_a.readlines()
				goal.goal_pose.pose.position.x = float(lines[0])
				goal.goal_pose.pose.position.y = float(lines[1])
				goal.goal_pose.pose.position.z = float(lines[2])
				goal.goal_pose.pose.orientation.x = float(lines[3])
				goal.goal_pose.pose.orientation.y = float(lines[4])
				goal.goal_pose.pose.orientation.z = float(lines[5])
				goal.goal_pose.pose.orientation.w = float(lines[6])
	
			# creating the goal that has the info on the destination 
			#goal = save_dest_a.msg.move_goalGoal(goal_pose)
			
			# Sends the goal to the action server.
			client.send_goal(goal)
			# Waits for the server to finish performing the action.
			status = client.wait_for_result(rospy.Duration(600.0))
			
			if status:
				rospy.loginfo("ACTION STATUS: Success - Robot reached goal before timeout")
			else:
				rospy.info("ACTION TIMEOUT: Action did not finish within 10 mins")
				# Prints out the result of executing the action
			return 
## ****************************************** FOR B ************************************************
		if arduino_msg == "b":
			upload_to_firebase("Luggage_B","Ready To Move")
			now = rospy.Time.now()
			listener.waitForTransform("map", "belt/b", now, rospy.Duration(4.0))
			(trans,rot) = listener.lookupTransform("map", "belt/b", now)
			goal.goal_pose.pose.position = trans
			goal.goal_pose.pose.orientation = rot
			# Sends the goal to the action server.
			client.send_goal(goal)
			
			# Waits for the server to finish performing the action.
			client.wait_for_result()
			with open("/home/ayush-pi4/fyp_belt_ws/src/save_dest_b/src/dest_b.txt",'r') as dest_b: 
				lines = dest_b.readlines()
				goal.goal_pose.pose.position.x = float(lines[0])
				goal.goal_pose.pose.position.y = float(lines[1])
				goal.goal_pose.pose.position.z = float(lines[2])
				goal.goal_pose.pose.orientation.x = float(lines[3])
				goal.goal_pose.pose.orientation.y = float(lines[4])
				goal.goal_pose.pose.orientation.z = float(lines[5])
				goal.goal_pose.pose.orientation.w = float(lines[6])

			# Sends the goal to the action server.
			client.send_goal(goal)
			# Waits for the server to finish performing the action.
			status = client.wait_for_result(rospy.Duration(600.0))
			
			if status:
				rospy.loginfo("ACTION STATUS: Success - Robot reached goal before timeout")
			else:
				rospy.info("ACTION TIMEOUT: Action did not finish within 10 mins")
				# Prints out the result of executing the action
			return 

def subscribe_container_belt():
	sub = rospy.Subscriber('container_status', String, container_callback_function)
	try:
		while True:
			goal_client()
	except rospy.ROSInterruptException:
		rospy.loginfo("Error Occurred")
		pass	
	rospy.spin()
	
def container_callback_function(msg):
	global queue
	queue.put(msg.data)
	rospy.loginfo("Received: %s"%msg.data)

def upload_to_firebase(luggage_name,message):
	database.child("Baggage_Status_Transit").update({luggage_name:message})
if __name__ == '__main__':
	try:
		# Initializes a rospy node so that the SimpleActionClient can
		# publish and subscribe over ROS.
		rospy.init_node('action_client_goal_py')
		subscribe_container_belt()
	except rospy.ROSInterruptException:
		pass
