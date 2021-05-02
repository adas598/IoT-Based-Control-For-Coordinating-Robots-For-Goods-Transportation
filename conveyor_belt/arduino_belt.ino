
#include <ros.h>
#include <std_msgs/String.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

//tag A:  4A 41 4B 19 
//tag B:  7B 64 A1 D5

//************************************************************
//RFID PINS
Servo servo1, servo2;
int servoPin1 = 8;
int servoPin2 = 4;

int a_status = 1;
int b_status = 0;

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


//MOTOR PINS
int in1 = 6;
int in2 = 7;
int ena = 5; 
int spd = 105 ;

//ROS STUFF
ros::NodeHandle n;

std_msgs::String arduino_msg;

ros::Publisher container_status("container_status", &arduino_msg);
//***********************************************************


void rfid_setup()
{
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  servo1.attach(servoPin1);
  servo1.write(0);
  servo2.attach(servoPin2);
  servo2.write(0);
}

void motor_setup()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena, OUTPUT);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(ena, spd);
}

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication

  rfid_setup();

  motor_setup();

  n.getHardware()->setBaud(9600);
  n.initNode();
  n.advertise(container_status);
}

void loop() 
{
  n.spinOnce();
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }  
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "4A 41 4B 19") //change here the UID of the card/cards that you want to give access
  {
    arduino_msg.data = "a";
    container_status.publish(&arduino_msg);
    servo1.write(135);
    delay(1000);
    servo1.write(45);
    delay(1000);
    servo1.write(135);
    delay(1000);
  }
  if (content.substring(1) == "7B 64 A1 D5") //change here the UID of the card/cards that you want to give access
  {
    arduino_msg.data = "b";
    container_status.publish(&arduino_msg);
    servo2.write(135);
    delay(1000);
    servo2.write(45);
    delay(1000);
    servo2.write(135);
    delay(1000);
  }
  else   
  {
    delay(500);
  }

  
}
