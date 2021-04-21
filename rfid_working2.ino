#include <SPI.h>
#include <MFRC522.h>
//tag 1:  4A 41 4B 19 
//tag 2:  7B 64 A1 D5

#include <Servo.h>
Servo servo1, servo2;
int servoPin1 = 8;
int servoPin2 = 4;

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  servo1.attach(servoPin1);
  servo1.write(0);
  servo2.attach(servoPin2);
  servo2.write(0);
}
void loop() 
{
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
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "4A 41 4B 19") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    servo1.write(135);
    delay(1000);
    servo1.write(45);
    delay(1000);
    servo1.write(135);
    delay(1000);
    //delay(3000);
  }
 if (content.substring(1) == "7B 64 A1 D5") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    servo2.write(135);
    delay(1000);
    servo2.write(45);
    delay(1000);
    servo2.write(135);
    delay(1000);
    //delay(3000);
  }
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
}
