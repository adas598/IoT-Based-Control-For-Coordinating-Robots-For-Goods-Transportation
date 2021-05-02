#include <ArduinoHardware.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int16.h>

#define PULSES_PER_REV 210
#define pi 3.14
// -------------------------------ENCODER PINS-----------------------------
volatile unsigned int ENCODERA_MOTOR1 = 19; // Hall sensor A connected to pin 3 (external interrupt)
volatile unsigned int ENCODERA_MOTOR2 = 18;

// --------------------------------MOTOR PINS---------------------------------
const unsigned int MOTOR1_EN = 10;
const unsigned int MOTOR1A = 8;
const unsigned int MOTOR1B = 9;
const unsigned int MOTOR2_EN = 7;
const unsigned int MOTOR2A = 5;
const unsigned int MOTOR2B = 6;

// ----------------------------ENCODER TICK VARIABLES-------------------------
volatile long left_ticks = 0;
volatile long right_ticks = 0;
float left_rev_count = 0.0, right_rev_count = 0.0, l_dist_val = 0.0, r_dist_val = 0.0;


const float wheel_rad = 0.0335;
const float wheel_sep = 0.173;
const float dist_per_rev = (2*pi*wheel_rad);
float w_r, w_l, speed_ang, speed_lin;

// ******************** ROS STUFF *****************
ros::NodeHandle n;

std_msgs::Int16 l_dist_msg, r_dist_msg;

ros::Publisher l_dist("l_dist", &l_dist_msg);
ros::Publisher r_dist("r_dist", &r_dist_msg);

void cmd_vel_callback( const geometry_msgs::Twist& msg){
  speed_ang = msg.angular.z;
  speed_lin = msg.linear.x;
  w_r = (speed_lin/wheel_rad)+ ((speed_ang*wheel_sep)/(2.0*wheel_rad));    // speed_ang*2.91 -2.91
  w_l = (speed_lin/wheel_rad)- ((speed_ang*wheel_sep)/(2.0*wheel_rad));
}
ros::Subscriber<geometry_msgs::Twist> sub_cmd_vel("cmd_vel", &cmd_vel_callback );

// ********************** FUNCTION DECLARATIONS *********************
void update_right_encoder(void);
void update_left_encoder(void);

void to_odom_publisher(void);
int update_left(void);
int update_right(void);

void move_l_motor(int pwm);
void move_r_motor(int pwm);

void pinmode_setup()
{
    pinMode( MOTOR1_EN, OUTPUT);
    pinMode( MOTOR1A , OUTPUT);
    pinMode( MOTOR1B , OUTPUT);

    pinMode( MOTOR2_EN, OUTPUT);
    pinMode( MOTOR2A , OUTPUT);
    pinMode( MOTOR2B , OUTPUT);

    pinMode( ENCODERA_MOTOR1, INPUT_PULLUP);
    pinMode( ENCODERA_MOTOR2, INPUT_PULLUP);
}

void pin_init()
{
    digitalWrite(MOTOR1_EN, HIGH);
    digitalWrite(MOTOR1A, LOW);
    digitalWrite(MOTOR1B, LOW);

    digitalWrite(MOTOR2_EN, HIGH);
    digitalWrite(MOTOR2A, LOW);
    digitalWrite(MOTOR2B, LOW);
}

void test()
{
    digitalWrite(MOTOR1A, HIGH);

    digitalWrite(MOTOR2A, HIGH);
}

void setup() {

//    Serial.begin(1152/00);//Initialize the serial port

    pinmode_setup();
    EncoderInit();

    pin_init();

//    t/est();

    n.initNode();
    n.advertise(l_dist);
    n.advertise(r_dist);
    n.subscribe(sub_cmd_vel);
}

void loop() {
    
  move_l_motor(w_l*10);
  move_r_motor(w_r*10);

  to_odom_publisher();

//   left_ticks = 0;
//   right_ticks = 0;
 
  n.spinOnce();
  delay(1000);
}

void EncoderInit()
{
  attachInterrupt(digitalPinToInterrupt(ENCODERA_MOTOR1), update_left_encoder, FALLING);
  attachInterrupt(digitalPinToInterrupt(ENCODERA_MOTOR2), update_right_encoder, FALLING);
}

void update_right_encoder()
{
  right_ticks++;
}


void update_left_encoder()
{
  left_ticks++;
}

int update_left()
{
  left_rev_count = (float)left_ticks/PULSES_PER_REV;
  l_dist_val = (float)left_rev_count * dist_per_rev;
//   return l_dist_val;
    return left_ticks;
}

int update_right()
{
  right_rev_count = (float)right_ticks/PULSES_PER_REV;
  r_dist_val = (float)right_rev_count * dist_per_rev;
//   return r_dist_val;
    return right_ticks;
}

void to_odom_publisher(void)
{
  l_dist_msg.data = update_left();
  r_dist_msg.data = update_right();

  l_dist.publish(&l_dist_msg);
  r_dist.publish(&r_dist_msg);
  return;
}

void move_l_motor(int pwm){
    if (pwm > 0){
    analogWrite(MOTOR1_EN, pwm);
    digitalWrite(MOTOR1A, HIGH);
    digitalWrite(MOTOR1B, LOW);
    }
    if (pwm < 0){
    pwm=abs(pwm);
    analogWrite(MOTOR1_EN, pwm);
    digitalWrite(MOTOR1A, LOW);
    digitalWrite(MOTOR1B, HIGH);
    }
    if (pwm == 0){
    analogWrite(MOTOR1_EN, pwm);
    digitalWrite(MOTOR1A, LOW);
    digitalWrite(MOTOR1B, LOW);
    }
}

void move_r_motor(int pwm){
    if (pwm > 0){
    analogWrite(MOTOR2_EN, pwm);
    digitalWrite(MOTOR2A, HIGH);
    digitalWrite(MOTOR2B, LOW);
    }
    if (pwm < 0){
    pwm=abs(pwm);
    analogWrite(MOTOR2_EN, pwm);
    digitalWrite(MOTOR2A, LOW);
    digitalWrite(MOTOR2B, HIGH);
    }
    if (pwm == 0){
    analogWrite(MOTOR2_EN, pwm);
    digitalWrite(MOTOR2A, LOW);
    digitalWrite(MOTOR2B, LOW);
    }
}
