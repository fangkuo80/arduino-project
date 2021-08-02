#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>  //esp32 
#include <time.h>
//#include <U8x8lib.h>
//const int rs = 0, rw = 9, en2 = 10 , en1 = 8, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
//LiquidCrystal lcd(rs, rw, en2 , 5, 4, 3, 6); //rs, rw, en1, en2, d4, d5, d6, d7
const int rs = 0, rw = 9, en2 = 10 , en1 = 8, d4 = 6, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, rw, en2 , 5, 4, 3, 6); //rs, rw, en1, en2, d4, d5, d6, d7
//LiquidCrystal lcd(rs, rw, en2 , 5, 4, 3, 2); //rs, rw, en1, en2, d4, d5, d6, d7
const char* ssid = "TP-LINK_2394";  //jone";  方國忠 的 iPhone            
const char* password = "A12kec00";      
const char* NTP_SERVER = "ch.pool.ntp.org";  //"ch.pool.ntp.org";
const char* TZ_INFO    = "SGT-8,M3.5.0/01:00:00,M10.5.0/02:00:00";  // enter your time zone (https://remotemonitoringsystems.ca/time-zone-abbreviations.php)
tm timeinfo;
time_t now;
long unsigned lastNTPtime;
unsigned long lastEntryTime;
//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 0, /* data=*/ 2, /* reset=*/ U8X8_PIN_NONE);         
//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 2, /* data=*/ 0, /* reset=*/ U8X8_PIN_NONE);         // Digispark ATTiny85
//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display
void setup() 
{
    lcd.begin(40,4); //,LCD_5x8DOTS
  lcd.clear() ;
  // Print a message to the LCD.
  lcd.print("-----abcdefghijklmnopqrstuvwxyz----");
//  lcd.setCursor(0,1);
//  lcd.print("hello, world!");
    LiquidCrystal lcd(rs, rw, en1 , 5, 4, 3, 2); //rs, rw, en1, en2, d4, d3, d2, d1
 //       LiquidCrystal lcd(rs, rw, en1 , 5, 4, 3, 2); //rs, rw, en1, en2, d4, d3, d2, d1
      lcd.begin(40,4); //,LCD_5x8DOTS
  lcd.print("-----abcdefghijklmnopqrstuvwxyz-----");
    lcd.setCursor(0,1);
  lcd.print("hello, world!");
    Serial.begin(9600);
    
//  u8x8.begin();
  
  Serial.begin(9600);
  Serial.println("\n\nNTP Time Test\n");
  WiFi.begin(ssid, password);
  Serial.print("Connecting to network");
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(200);    
    if (++counter > 100) 
      ESP.restart();
    Serial.print( "." );
  }
  Serial.println("\nWiFi connected\n\n");
  configTime(0, 0, NTP_SERVER);
  // See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for Timezone codes for your region
  setenv("TZ", TZ_INFO, 1);  //1
  if (getNTPtime(100)) 
  {  
    // wait up to 10sec to sync
  } 
  else 
  {
    Serial.println("Time not set");
    ESP.restart();
  }
  showTime(&timeinfo);
  lastNTPtime = time(&now);
  lastEntryTime = millis();
}
void loop() 
{
  getNTPtime(10);
  showTime(&timeinfo);
  delay(1000);
}
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
void showTime(tm *localTime) 
{
  //print to serial terminal
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
  //display on OLED
  char time_output[30];
  
 // u8x8.setFont(u8x8_font_courB18_2x3_f);
 // u8x8.setCursor(0,0);
  sprintf(time_output, "%02d:%02d:%02d", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
 // u8x8.print(time_output);
      lcd.setCursor(0,1);
  lcd.print(time_output);
  //u8x8.setFont(u8x8_font_8x13B_1x2_f);
 // u8x8.setCursor(4,4);
  sprintf(time_output, "%02d/%02d/%02d", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year - 100);
 // u8x8.print(time_output);
  
 // u8x8.setCursor(4,6);
 // u8x8.print(getDOW(localTime->tm_wday));
}
char * getDOW(uint8_t tm_wday)
{
  switch(tm_wday)
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
    case 7:
      return "Sunday";
      break;
    default:
      return ""; //"Error";
      break;
  }
}
