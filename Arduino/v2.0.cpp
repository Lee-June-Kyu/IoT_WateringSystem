// v1.0 + wifi
// 아두이노 -> 모터장치 + 습도센서 + wifi (esp01)


#include <SoftwareSerial.h> 
#include <Stepper.h>

#define rxPin 3 
#define txPin 2 

#define sensor A0
#define wet 250
#define dry 530

SoftwareSerial esp01(txPin, rxPin); // SoftwareSerial NAME(TX, RX);

int IN1 = 2; //IN1은 2번 핀에 연결
int IN2 = 3; //IN2는 3번 핀에 연결
int IN3 = 4; //IN3는 4번 핀에 연결
int IN4 = 5; //IN4는 5번 핀에 연결
Stepper step1(2048, IN1, IN3, IN2, IN4);
int lap = 2048; // 2048-->360도 회전

void setup() {
  step1.setSpeed(10); // 분당 10회 회전
  Serial.begin(9600);   // 시리얼 모니터
  esp01.begin(9600);  // 와이파이 시리얼
}

void loop() {
  int value = analogRead(sensor);
  int pre = map(value, wet, dry, 100, 0);
  Serial.print("Soil Moisture:  ");
  Serial.print(value);
  Serial.print(" ");
  Serial.print("--");
  Serial.print(" ");
  Serial.print(pre);
  Serial.print(" %");
  Serial.print("\n\n");
  delay(10000);
  if (esp01.available()) {       
    Serial.write(esp01.read());  // 블루투스 측 내용을 시리얼 모니터에 출력
  }  
  if (Serial.available()) {         
    esp01.write(Serial.read());  // 시리얼 모니터 내용을 블루투스 측에 쓰기
  }
  step1.step(lap); // 오른쪽으로 한바퀴
  delay(1500); // 1초 딜레이
  step1.step(-lap); // 왼쪽으로 한바퀴
  delay(1500);
}