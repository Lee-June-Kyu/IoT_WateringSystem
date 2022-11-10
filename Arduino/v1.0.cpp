// 아두이노 - PC 시리얼 통신
// 아두이노와 PC를 USB로 연결함
// 습도제어, 모터

#include <LiquidCrystal_I2C.h>
#include <Stepper.h>

int IN1 = 2; //IN1은 2번 핀에 연결
int IN2 = 3; //IN2는 3번 핀에 연결
int IN3 = 4; //IN3는 4번 핀에 연결
int IN4 = 5; //IN4는 5번 핀에 연결
Stepper step1(2048, IN1, IN3, IN2, IN4);

int lap = 2048; //2048-->360도 회전

LiquidCrystal_I2C lcd (0x27, 16, 2);
#define sensor A0
#define wet 250
#define dry 530

void setup() {
  step1.setSpeed(13); //분당 10회 회전
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
}

void loop() {
  int value = analogRead(sensor);
  Serial.println(value);
  lcd.setCursor(1,0);
  lcd.print("Soil Moisture: ");
  lcd.setCursor(3,1);
  lcd.print(value);
  lcd.print(" ");
  lcd.setCursor(7,1);
  lcd.print("--");
  int pre = map(value, wet, dry, 100, 0);
  lcd.setCursor(10, 1);
  lcd.print(pre);
  lcd.setCursor(12, 1);
  lcd.print("%");
  step1.step(lap); //오른쪽으로 한바퀴
  delay(1500); //1초 딜레이
  step1.step(-lap); //왼쪽으로 한바퀴
  delay(1500);
}