#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <TridentTD_LineNotify.h>

//#define DHTTYPE DHT11
//#define DHTPIN  0

// 修改成上述寄到登入郵箱的 Token號碼
#define LINE_TOKEN "4ypWH81DePFWyxNPbqh3OIy1YhWOjDzEcBwt61ZY0Pm"

// 設定無線基地台SSID跟密碼
const char* ssid     = "TP-LINK_2394";//TP-LINK_2394  jone
const char* password = "A12kec00";
const int dirf = 13; //detect gpio 3
int dirff ;//3 detect gpio 3
const int dirb = 4; //detect gpio 2
int dirfb ;//2 detect gpio 2
int relay1 = 5 ;
//DHT dht(DHTPIN, DHTTYPE, 11);    // 11 works fine for ESP8266
 
float humidity, temp_f;   // 從 DHT-11 讀取的值

unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor

// 用不到以下兩個變數
// const char* host = "notify-api.line.me";
// const int httpsPort = 443;
 AsyncWebServer server(80);
void setup(void)
{
    pinMode(dirf,INPUT);
    pinMode(dirb,INPUT);
    pinMode(relay1,OUTPUT);
    digitalWrite(relay1,LOW);
  Serial.begin(9600);  // 設定速率 感測器
//  dht.begin();           // 初始化

  WiFi.mode(WIFI_STA);
  // 連接無線基地台
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // 等待連線，並從 Console顯示 IP
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("DHT Weather Reading Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP8266.");
  });
 
  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
}
 
void loop(void)
{
   digitalWrite(relay1,LOW);
///    while (WiFi.status() != WL_CONNECTED) {
   delay(200);
  // 量測間等待至少 2 秒
/* unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis >= interval) {
    // 將最後讀取感測值的時間紀錄下來 
    previousMillis = currentMillis;   

    // 讀取溫度大約 250 微秒!
    humidity = dht.readHumidity();          // 讀取濕度(百分比)
    temp_f = dht.readTemperature(true);     // 讀取溫度(華氏)
    
 
    // 檢查兩個值是否為空值
    if (isnan(humidity) || isnan(temp_f)) {
       Serial.println("Failed to read from DHT sensor!");
       return;
    }
  }

  String tempe="溫度:"+String((int)(temp_f-32)*5/9)+"℃";   
  String humid="濕度:"+String((int)humidity)+"％";

  // 顯示 Line版本 */
   dirff = digitalRead(dirf); //pin3
   dirfb = digitalRead(dirb); //pin2
  if (dirff == HIGH){   //Gpio 3 低電位觸發
    Serial.println(LINE.getVersion());
 
    LINE.setToken(LINE_TOKEN);

  // 先換行再顯示
  //LINE.notify("\n" + tempe + " ；" + humid);
  String tempe="DOOR OPEN:143號 一樓test";   
    LINE.notify("\n" + tempe);
   digitalWrite(relay1,HIGH);   
  // 每4分鐘發送一次
    delay(300000);//240000
  }
   else if (dirfb == HIGH){   //Gpio 2 低電位觸發
    Serial.println(LINE.getVersion());
 
    LINE.setToken(LINE_TOKEN);

  // 先換行再顯示
  //LINE.notify("\n" + tempe + " ；" + humid);
  String tempe="SENSER DETECT:143號 一樓test";   
    LINE.notify("\n" + tempe);
   digitalWrite(relay1,HIGH);   
  // 每4分鐘發送一次
    delay(300000);//240000
  }
    digitalWrite(relay1,LOW);
    delay(200);
}
