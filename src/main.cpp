#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define LEFT_WIRE 13 // Dark Blue - 1
#define RIGHT_WIRE 12 // Turquoise - 2
#define UP_WIRE 14 // Red - 3, yellow  25
#define DOWN_WIRE 27 // Black - 4, black
#define TRIG1 15
#define ECHO1 2
#define TRIG2 16
#define ECHO2 4
#define TRIG3 17
#define ECHO3 5
typedef struct test_struct {
  int x;
  int y;
} test_struct;

test_struct myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("x: ");
  Serial.println(myData.x);
  Serial.print("y: ");
  Serial.println(myData.y);
  Serial.println();
}

const int pwmFrequency = 200; // PWM frequency in Hz
const int pwmResolution = 8;   // PWM resolution in bits (8-bit resolution for ESP32)

int xJoystick = 0; // from -1800 to 1800
int yJoystick = 0; // from -1800 to 1800

// deadzone from -20 to 20 is all 0


void setup(){
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);

  pinMode(LEFT_WIRE, OUTPUT);
  pinMode(RIGHT_WIRE, OUTPUT);
  pinMode(UP_WIRE, OUTPUT);
  pinMode(DOWN_WIRE, OUTPUT);
  Serial.println(WiFi.macAddress());

  
  pinMode(TRIG1, OUTPUT); // set up distance1 sensor pins
  pinMode(ECHO1, INPUT);
  digitalWrite(TRIG1, LOW);
  pinMode(TRIG2, OUTPUT); // set up distance2 sensor pins
  pinMode(ECHO2, INPUT);
  digitalWrite(TRIG2, LOW);
  pinMode(TRIG3, OUTPUT); // set up distance3 sensor pins
  pinMode(ECHO3, INPUT);
  digitalWrite(TRIG3, LOW);

  // ledcSetup(0, pwmFrequency, pwmResolution);
  // ledcAttachPin(UP_WIRE, 0);
}

// read distance sensor, return centimeters
float readDistance(int TRIG, int ECHO) {
  digitalWrite(TRIG, LOW); delayMicroseconds(3);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  unsigned long timeout = micros() + 26233L;
  while((digitalRead(ECHO) == LOW) && (micros() < timeout));
  unsigned long start_time = micros();
  timeout = start_time + 26233L;
  while((digitalRead(ECHO) == HIGH) && (micros() < timeout));
  unsigned long lapse = micros() - start_time;
  return lapse * 0.01716f;
}

// calls readDistance a certain amount of time 
float averageDistance(int TRIG, int ECHO){
  unsigned long totalLapse = 0;
  for (int i = 0; i < 5; i++) {
    totalLapse += readDistance(TRIG, ECHO);
  }
  return totalLapse / 5;
}


void loop(){
  float dist1 = averageDistance(TRIG1, ECHO1);
  delay(50);
  float dist2 = averageDistance(TRIG2, ECHO2);
  delay(50);
  float dist3 = averageDistance(TRIG3, ECHO3);

  Serial.print("1: ");
  Serial.println(dist1);
  Serial.print("2: ");
  Serial.println(dist2);
  Serial.print("3: ");
  Serial.println(dist3);
  
  // digitalWrite(UP_WIRE, HIGH);
  // if (dist1 < 20 || dist2 < 20 || dist3 < 20){
  //   digitalWrite(UP_WIRE, LOW);
  // }

//  digitalWrite(LEFT_WIRE, HIGH);
//  delay(1000);
//  digitalWrite(LEFT_WIRE, LOW);
//  digitalWrite(RIGHT_WIRE, HIGH);
//  delay(1000);
//  digitalWrite(RIGHT_WIRE, LOW);
//  delay(5000);

 
//  digitalWrite(DOWN_WIRE, HIGH);
//  delay(1000);
//  digitalWrite(DOWN_WIRE, LOW);
//  delay(2000);

//  digitalWrite(UP_WIRE, HIGH);
//  delay(1000);
//  digitalWrite(UP_WIRE, LOW);
//  delay(2000); 


}