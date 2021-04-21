int in1 = 6;
int in2 = 7;
int ena = 5; 
int spd = 250 ;
void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena, OUTPUT);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(ena, spd);
  
}

void loop() {
  // put your main code here, to run repeatedly:
//  for (int i = 100; i<210; i++)
//  {
//    analogWrite(ena, i);
//    delay(300);
//  }
}
