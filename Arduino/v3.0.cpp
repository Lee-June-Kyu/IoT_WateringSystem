// v2.0 + (send server)
// 아두이노 -> 서버 HTTP통신 
// 프로토타입


#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>

#include "WiFiEsp.h"
// #include <DS1302.h>



//=======================================================================
//                    Motor setup
//=======================================================================
int IN1 = 4; //IN1은 2번 핀에 연결
int IN2 = 5; //IN2는 3번 핀에 연결
int IN3 = 6; //IN3는 4번 핀에 연결
int IN4 = 7; //IN4는 5번 핀에 연결

Stepper step1(2048, IN1, IN3, IN2, IN4);

//=======================================================================
//                    Huminity setup
//=======================================================================
#define sensor A0
#define wet 250
#define dry 530

int lap = 2048; //2048-->360도 회전

//=======================================================================
//                    wifi setup
//=======================================================================
unsigned long lastConnectionTime = 0;         // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 5000L; // delay between updates, in millisecondsunsigned long lastConnectionTime = 0;
const int WIFI_Initial_time=2000;

String rcvbuf;
boolean getIsConnected = false;

//Web/Server address to read/write from

IPAddress hostIp(192, 168, 4, 1);
int SERVER_PORT = 80;

#ifndef HAVE_HWSERIAL188
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#endif

char ssid[] = "Metacamp";            // your network SSID (name)
char pass[] = "Metacamp0501";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

char server[] = "192.168.0.72";

// Initialize the Ethernet client object
WiFiEspClient client;

//=======================================================================
//                    Power on setup
//=======================================================================
void setup()
{
  Serial.begin(9600);
  // initialize serial for ESP module
  Serial1.begin(9600);
  
  //분당 10회 회전
  step1.setSpeed(13);

  // initialize ESP module
  WiFi.init(&Serial1);
  // 와이파이 존재 유무
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }

  // 와이파이 연결 시도
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }

  // 연결 됐을때 출력문
  Serial.println("You're connected to the network");
  Serial.println();
  Serial.println("Starting connection to server...");
}
//=======================================================================
//                    Main Program Loop
//=======================================================================

char mtime;
void loop()
{
  
  get_dust("g"); // 측정 메소드
  Serial.println("===========================================");
  Serial.println();
//  delay(1000);
}

//=======================================================================
//                    get_Dust(measure)
//=======================================================================
void get_dust(char *mtime) {
  
  //=======================================================================
  Serial.print("현재 시각: ");
  // Serial.println(rtc.getTimeStr(mtime));
  //=======================================================================
  // Serial.println("iotId: " + iotId);
  dust(1, "2", "123");
}

//=======================================================================
//                    Dust
//=======================================================================
void dust(int dust, char *mtime, String iotId) {
  int value = analogRead(sensor);
  Serial.println("센서 측정값 전달 대기중...");
  int pre = map(value, wet, dry, 100, 0);
  // 연결됐을때, 밑에 명령들 실행
  if (client.connect(server, 8000)) {
    Serial.println("Connecting...");

    //POST Data Set//
    String jsondata = "";

    StaticJsonBuffer<200> jsonBuffer;  //json변환에 필요한 버퍼 생성
    JsonObject& root = jsonBuffer.createObject(); //json형식을 만들어 낼수있는 객체 생성
    root["humidity"] = pre; // key=["dust_val"], value=dust_val

    root.printTo(jsondata); // printTo => String변수로 변환
    Serial.print("jsondata: ");
    Serial.println(jsondata);

    // send the HTTP POST request
    client.print(F("POST /humidity/1"));
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
    delay(10000);
    // note the time that the connection was made
    lastConnectionTime = millis();
    getIsConnected = true;


  
  }

  else {
    // if you couldn't make a connection
    Serial.println("Connection failed");
    getIsConnected = false;
  }
  client.flush();
  client.stop(); // 클라이언트 접속 종료
}