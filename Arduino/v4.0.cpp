// v4.0
// 아두이노 -> 서버 HTTP통신 
// 습도값 측정 후 http통신
// 모터 동작 제어 http 통신


// include 라이브러리
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>
#include "WiFiEsp.h"

//=======================================================================
//                    모터 초기 설정
//=======================================================================
int IN1 = 4; //IN1은 4번 핀에 연결
int IN2 = 5; //IN2는 5번 핀에 연결
int IN3 = 6; //IN3는 6번 핀에 연결
int IN4 = 7; //IN4는 7번 핀에 연결

Stepper step1(2048, IN1, IN3, IN2, IN4);

int lap = 2048; //2048-->360도 회전

//=======================================================================
//                    습도 센서 초기 설정
//=======================================================================
#define sensor A0
#define wet 250     // 건조 최소 값
#define dry 530     // 습함 최대 값

//=======================================================================
//                    wifi 초기 설정
//=======================================================================
unsigned long lastConnectionTime = 0;         // 서버에 마지막으로 접근한 시간 (milliseconds)
const unsigned long postingInterval = 5000L;  // 지연시간
const int WIFI_Initial_time=2000;

String rcvbuf;
boolean getIsConnected = false;

// 읽고 쓸 주소 Web/Server
IPAddress hostIp(192, 168, 4, 1);
int SERVER_PORT = 80;

#ifndef HAVE_HWSERIAL188
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#endif

char ssid[] = "Metacamp";            // 네트워크 이름 : SSID (name)
char pass[] = "Metacamp0501";        // 네트워크 비밀번호 : password
int status = WL_IDLE_STATUS;     

char server[] = "192.168.0.72";   // 백 서버 설정

// client 객체 초기화
WiFiEspClient client;

//=======================================================================
//                    setup 설정
//=======================================================================
void setup()
{
  // baud 맞추기
  Serial.begin(9600);
  // ESP module 시리얼 맞추기
  Serial1.begin(9600);
  
  // 분당 10회 회전
  step1.setSpeed(13);

  // ESP module 초기화
  WiFi.init(&Serial1);
  // 와이파이 존재 유무
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");

    while (true);
  }

  // 와이파이 연결 시도
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // 네트워크 연결하기
    status = WiFi.begin(ssid, pass);
  }

  // 연결 됐을때 출력문
  Serial.println("You're connected to the network");
  Serial.println();
  Serial.println("Starting connection to server...");
}

//=======================================================================
//                     Loop
//=======================================================================
void loop()
{
 
  //=======================================================================
  //                    습도 정보 보내기 ( http 통신 )
  //=======================================================================

  // 센서로부터 값 받기
  int value = analogRead(sensor);
  Serial.println("Waiting...");
  // 예측값 => 습도를 %로 표시한다.
  int pre = map(value, wet, dry, 100, 0);
  // 연결됐을때, 밑에 명령들 실행
  if (client.connect(server, 3001)) {
    Serial.println("Connecting...");
    // POST 데이터 설정
    String jsondata = "";
    StaticJsonBuffer<200> jsonBuffer;  //json변환에 필요한 버퍼 생성
    JsonObject& root = jsonBuffer.createObject(); //json형식을 만들어 낼수있는 객체 생성
    root["humidity"] = pre; // key : humidity , value : pre  

    root.printTo(jsondata); // printTo => String변수로 변환
    Serial.print("jsondata: ");
    Serial.println(jsondata);

    // HTTP POST request 보내기
    client.print(F("POST /arduino/humidity/1"));
    client.print(F(" HTTP/1.1\r\n"));
    client.print(F("Cache-Control: no-cache\r\n"));
    client.print(F("Host: 192.168.4.1:80\r\n"));
    client.print(F("User-Agent: Arduino\r\n"));
    client.print(F("Content-Type: text/json;charset=UTF-8\r\n"));
    client.print(F("Content-Length: "));
    client.println(jsondata.length());
    client.print(F("value: "));
    client.println(jsondata);
    Serial.println(jsondata);
    client.print(F("\r\n\r\n"));
    delay(1000);
    
    lastConnectionTime = millis();
    getIsConnected = true;

    // 습도 제어 결과
    String b = client.readStringUntil('\r');

    Serial.print("humidity http result : ");
    Serial.println(b);

  }
  else {
    // 연결이 되어 있지 않은 경우
    Serial.println("Connection failed");
    getIsConnected = false;
  }
  client.flush();
  client.stop(); // 클라이언트 접속 종료

  Serial.println("===========================================");
  Serial.println();

  //=======================================================================
  //                    모터 상태 확인하기 ( http 통신 )
  //=======================================================================

  // 연결됐을때, 밑에 명령들 실행
  if (client.connect(server, 3001)) {
    Serial.println("Connecting...");
 
    // HTTP GET request 보내기
    client.print(F("GET /arduino/motor/1"));
    client.print(F(" HTTP/1.1\r\n"));
    client.print(F("Cache-Control: no-cache\r\n"));
    client.print(F("Host: 192.168.4.1:80\r\n"));
    client.print(F("User-Agent: Arduino\r\n"));
    client.print(F("\r\n\r\n"));
    delay(1000);
 
    lastConnectionTime = millis();
    getIsConnected = true;

    // 모터 제어 결과
    String c = client.readStringUntil('\r');

    Serial.print("motor get http result : ");
    Serial.println(c);

    String motorStatus = c.substring(9,12);
    Serial.print("status result : ");
    Serial.println(motorStatus);

    if (motorStatus == "200"){
      step1.step(lap); // 오른쪽으로 한바퀴
      delay(1000); // 1초 딜레이
      step1.step(-lap); // 왼쪽으로 한바퀴
      delay(1000);
    }
   
  }
  else {
    Serial.println("Connection failed");
    getIsConnected = false;
  }
  client.flush();
  client.stop(); // 클라이언트 접속 종료

  Serial.println("===========================================");
  Serial.println();
 delay(10000);
}

