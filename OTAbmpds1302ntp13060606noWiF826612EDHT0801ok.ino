#include "DHTesp.h" // Click here to get the library: http://librarymanager/All#DHTesp
#include <ESP8266WiFi.h>  //esp32 
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <time.h>
#include <U8x8lib.h> 
#include <virtuabotixRTC.h> 
 #include <Adafruit_Sensor.h>
 #include <Adafruit_BMP280.h> 
 #include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h> 
//Wiring SCLK -> 6, I/O -> 7, CE -> 8
//Or CLK -> 6 , DAT -> 7, Reset -> 8
const int dirb = 2; //detect gpio 2
int dirfb ;//2 detect gpio 2
//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the u8x8  
virtuabotixRTC myRTC(14, 12, 13); //If you change the wiring change the pins here also
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 5, /* data=*/ 4, /* reset=*/ U8X8_PIN_NONE); 
//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the u8x8 NODEMCU USE
#define SEALEVELPRESSURE_HPA (1013.25)
const char* ssid = "TP-LINK_2394";  //jone";  方國忠 的 iPhone TP-LINK_2394           
const char* password = "A12kec00";      
const char* NTP_SERVER = "ch.pool.ntp.org";  //"ch.pool.ntp.org";
const char* TZ_INFO    = "SGT-8,M3.5.0/01:00:00,M10.5.0/02:00:00";  // enter your time zone (https://remotemonitoringsystems.ca/time-zone-abbreviations.php)
AsyncWebServer server(80);
Adafruit_BMP280 bmp; // For I2C interface
tm timeinfo;
time_t now;
DHTesp dht;
long unsigned lastNTPtime;
unsigned long lastEntryTime;
  bool getNTPtime(int sec) 
{
  {
    uint32_t start = millis();
    do
    {
      time(&now);
      localtime_r(&now, &timeinfo);
      delay(10);
    } while (((millis() - start) <= (1000 * sec)) && (timeinfo.tm_year < (2016 - 1900)));
    
    if (timeinfo.tm_year <= (2016 - 1900)) 
        return false;  // the NTP call was not successful
    
    Serial.print("Time Now: ");  
    Serial.println(now); 
  }
  return true;
}
 void setTime(tm *localTime) 
{
  //print to serial terminal
  int a1,a2,a3,a4,a5,a6,a7 ;
  Serial.print(localTime->tm_mday);
  Serial.print('/');
  Serial.print(localTime->tm_mon + 1);
  Serial.print('/');
  Serial.print(localTime->tm_year - 100);
  Serial.print('-');
  Serial.print(localTime->tm_hour);
  Serial.print(':');
  Serial.print(localTime->tm_min);
  Serial.print(':');
  Serial.print(localTime->tm_sec);
  Serial.print(" Day of Week ");
  Serial.println(localTime->tm_wday);
  Serial.println();
   // myRTC.setDS1302Time(localTime->tm_sec, localTime->tm_min, localTime->tm_hour, localTime->tm_wday, localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year - 100);
    myRTC.setDS1302Time(int(localTime->tm_sec), int(localTime->tm_min), int(localTime->tm_hour), int(localTime->tm_wday), int(localTime->tm_mday), localTime->tm_mon + 1, int(localTime->tm_year - 100) + 2000);
//    Serial.println(char(localTime->tm_sec), char(localTime->tm_min), char(localTime->tm_hour), char(localTime->tm_wday), char(localTime->tm_mday), char(localTime->tm_mon + 1), char(localTime->tm_year - 10));
}     
void setup()  {   


    Wire.begin();
   String thisBoard= ARDUINO_BOARD;
     dht.setup(16, DHTesp::DHT11); // Connect DHT sensor to GPIO 16(D2)  15(D8) 16(D0)
   u8x8.begin();
      Serial.begin(9600);
  Serial.println("\n\nNTP Time Test\n");
  WiFi.begin(ssid, password);
  Serial.print("Connecting to network");
      delay(1000); 
   
  int counter = 0;
//  WiFi.begin(ssid, password);
//      delay(2000);
//  for (i: =1 to 5) do begin {
  if (WiFi.status() != WL_CONNECTED) 
  {
 //   delay(2000);    
  WiFi.begin(ssid, password);
      delay(2000);
          Serial.print( "." );}
  if (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);    
  WiFi.begin(ssid, password);
      delay(1000);
          Serial.print( "." );}
   if (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);    
  WiFi.begin(ssid, password);
      delay(1000);
   Serial.print( "." );} 
    if (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);    
  WiFi.begin(ssid, password);
      delay(1000);
          Serial.print( "." );} 
    if (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);    
  WiFi.begin(ssid, password);
      delay(1000);
          Serial.print( "." );} 
   if (WiFi.status() == WL_CONNECTED) {
  Serial.println("\nWiFi connected\n\n");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP32.");
  });
 
  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");   
  configTime(0, 0, NTP_SERVER);
  // See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for Timezone codes for your region
  setenv("TZ", TZ_INFO, 1);  //1
  if (getNTPtime(500)) 
  {  
    setTime(&timeinfo) ;// wait up to 10sec to sync
  } 
  else 
  {
    Serial.println("Time not set");
//    ESP.restart();
  }
  lastNTPtime = time(&now);
  lastEntryTime = millis();
//  showTime(&timeinfo);
//  Serial.println(tm *localTime);
//  Serial.println(&timeinfo);
  lastNTPtime = time(&now);
  lastEntryTime = millis();
  Serial.println(lastNTPtime);
  Serial.println(TZ_INFO);
//  myRTC.setDS1302Time(00, 59, 23, 6, 10, 1, 2014);
//setTime((&timeinfo)) ;
//setTime(&timeinfo) ;
//(tm *localTime)
// seconds, minutes, hours, day of the week, day of the month, month, year
//  myRTC.setDS1302Time(00, 59, 23, 6, 10, 1, 2014);
 if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
// if (!bmp.begin()) {
     // connection error or device address wrong!
     Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
     u8x8.setCursor(34, 23);
     u8x8.print("Connection");
     u8x8.setCursor(49, 33);
     u8x8.print("Error");
//     u8x8.u8x8();        // update the u8x8
     while (1) // stay here
       delay(1000);
   }
}
}

void loop()  {      
dirfb = digitalRead(dirb); //pin2
if (dirfb == HIGH){   //Gpio 2 低電位觸發 
// This allows for the update of variables for time or accessing the individual elements.                //|
  myRTC.updateTime();                                                                                    //| 
     showTime();                                                                                                      //| 
// Start printing elements as individuals                                                                //|   
  Serial.print("Current Date / Time: ");                                                                 //| 
  Serial.print(myRTC.dayofmonth);                                                                        //| 
  Serial.print("/");                                                                                     //| 
  Serial.print(myRTC.month);                                                                             //| 
  Serial.print("/");                                                                                     //| 
  Serial.print(myRTC.year);                                                                              //| 
  Serial.print("  ");                                                                                    //| 
  Serial.print(myRTC.hours);                                                                             //| 
  Serial.print(":");                                                                                     //| 
  Serial.print(myRTC.minutes);                                                                           //| 
  Serial.print(":");                                                                                     //| 
  Serial.println(myRTC.seconds);                                                                         //| 
   delay(dht.getMinimumSamplingPeriod());
}

dirfb = digitalRead(dirb); //pin2
if (dirfb == LOW){   //Gpio 2 低電位觸發
  showbmp() ;
}
}

void showbmp() 
{
  u8x8.clear() ;
/*     u8x8.setFont(u8x8_font_8x13B_1x2_f);
   u8x8.setCursor(0, 0);
   u8x8.print("TEMPERATURE:");
     u8x8.setFont(u8x8_font_8x13B_1x2_f);
   u8x8.setCursor(0, 3);
   u8x8.print("Pressure:");
     u8x8.setFont(u8x8_font_8x13B_1x2_f);
   u8x8.setCursor(0, 5);
   u8x8.print("Altitude:");
//   u8x8.u8x8();        // update the u8x8*/
    float temp = bmp.readTemperature();    // get temperature in degree Celsius
   float pres = bmp.readPressure()/100;       // get pressure in Pa
   float alti = bmp.readAltitude(SEALEVELPRESSURE_HPA);       // get altitude in meter
 
 //  delay(1000);  // wait a second
 // print data on the LCD
   // print temperature
   Serial.print("Temperature = ");
   Serial.print(temp);
   Serial.println("*C");
     u8x8.setFont(u8x8_font_8x13B_1x2_f);
        u8x8.setCursor(0, 1); 
   u8x8.print("Temp:");
   u8x8.setCursor(6, 1);
   if (temp < 0)
     u8x8.printf("-%02u.%02u C", (int)abs(temp) % 100, (int)(abs(temp) * 100) % 100 );
   else
     u8x8.printf(" %02u.%02u C", (int)temp % 100, (int)(temp * 100) % 100 );
 // print degree symbols ( ° )
//   u8x8.drawRect(75, 10, 3, 3, WHITE);
 //print pressure
   Serial.print("Pressure = ");
   Serial.print(pres);
   Serial.println("hPa");
     u8x8.setFont(u8x8_font_8x13B_1x2_f);
   u8x8.setCursor(0, 3); 
   u8x8.print("Press:");    
   u8x8.setCursor(7, 3);
   u8x8.printf("%02u hPa", (int)(pres));
   //print Altitude
   Serial.print("Approx. Altitude = ");
   Serial.print(alti);
   Serial.println("m");
     u8x8.setFont(u8x8_font_8x13B_1x2_f);
     u8x8.setCursor(0, 5); 
   u8x8.print("Alti:");   
   u8x8.setCursor(7, 5);
   u8x8.printf("%02u meter", (int)(alti));
 // update the u8x8
//u8x8();
 delay(1000);  // wait a second
 Serial.println();
//   Blynk.virtualWrite(V1, temp); // For Temperature
//   Blynk.virtualWrite(V2, pres); // For Pressure
//   Blynk.virtualWrite(V3, alti); //For Approx. Altitude
   delay(1000);
     u8x8.clear() ;
}                                                                                                   //| 
                                                                                                      //| 
 void showTime() 
{
    float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  //u8x8 on OLED
  char time_output[30];
  
  u8x8.setFont(u8x8_font_courB18_2x3_f);
  u8x8.setCursor(0,0);
  sprintf(time_output, "%02d:%02d:%02d", myRTC.hours, myRTC.minutes, myRTC.seconds);
  u8x8.print(time_output);
  
  u8x8.setFont(u8x8_font_8x13B_1x2_f);
  u8x8.setCursor(0,4);
  sprintf(time_output, "%02d/%02d/%02d", myRTC.dayofmonth, myRTC.month, myRTC.year);
  u8x8.print(time_output);
  
  u8x8.setCursor(0,6);
  u8x8.print(getDOW(myRTC.dayofweek));

  u8x8.setCursor(12,4);
  u8x8.print(humidity, 1);
  u8x8.setCursor(12,6);
  u8x8.print(temperature, 1);
//    u8x8.clear() ;
    }

char * getDOW(uint8_t dayofweek)
{
  switch(dayofweek)
  {
    case 1:
      return "Monday";
      break;
    case 2:
      return "Tuesday";
      break;
    case 3:
      return "Wednesday";
      break;
    case 4:
      return "Thursday";
      break;
    case 5:
      return "Friday";
      break;
    case 6:
      return "Saturday";
      break;
    case 0:
      return "Sunday";
      break;
    default:
      return ""; //"Error";
      break;
}  
}   
