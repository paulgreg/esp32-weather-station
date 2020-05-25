#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

GxEPD2_3C<GxEPD2_270c, GxEPD2_270c::HEIGHT> display(GxEPD2_270c(/*CS=*/ 15, /*DC=*/ 27, /*RST=*/ 26, /*BUSY=*/ 25));

// Screen used
#include "bitmaps/Bitmaps3c176x264.h" // 2.7"  b/w/r

// Icons
#include "icons/01d.h"
#include "icons/03d.h"

#include <TimeLib.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include "parameters.h"

#include <Arduino_JSON.h>

JSONVar json;

const uint64_t SECOND = 1000;
const uint64_t MINUTE = 60 * SECOND;
const uint64_t HOUR = 60 * MINUTE;
const uint64_t MICRO_SEC_TO_MILLI_SEC_FACTOR = 1000;

struct Weather {
  char temp[7];
  char feelslike[7];
  char humidity[5];
  char updated[6];
  char main[32];
  char description[128];
  char icon[10];
};

// use Board "ESP32 Dev Module" to build with Arduino IDE
void setup() {
  Serial.begin(115200);
  display.init(115200);
  // *** special handling for Waveshare ESP32 Driver board *** //
  SPI.end(); // release standard SPI pins, e.g. SCK(18), MISO(19), MOSI(23), SS(5)
  //SPI: void begin(int8_t sck=-1, int8_t miso=-1, int8_t mosi=-1, int8_t ss=-1);
  SPI.begin(13, 12, 14, 15); // map and init SPI pins SCK(13), MISO(12), MOSI(14), SS(15)
  // *** end of special handling for Waveshare ESP32 Driver board *** //

  print_wakeup_reason();
  
  display.setRotation(1);

  uint64_t sleepTime = HOUR;
  
  if (connectToWifi()) {
    boolean jsonParsed = getJSON(URL);
    if (!jsonParsed) {
      displayCenteredText("Error getting JSON");
    } else {
      Weather weather;
      fillWeatherFromJson(&weather);
      displayWeather(&weather);
      if (weather.updated[0] == '0' && weather.updated[1] == '0') sleepTime = HOUR * 6; // sleep for the night
    }
  } else {
    displayCenteredText("Can’t connect to wifi");
  }

  sleep(sleepTime);
}


void loop() {
  Serial.println("loop should never be called because it should sleep");
  delay(MINUTE);
}

void displayWeather(Weather* weather) {
  display.fillScreen(GxEPD_WHITE);

  display.firstPage();
  do
  {  
    //display.drawBitmap(0, 0, icon_03d_bits, icon_03d_width, icon_03d_height, GxEPD_BLACK);
    display.drawBitmap(0, 0, icon_01d_bits, icon_01d_width, icon_01d_height, GxEPD_RED);
    
    // Temp (feels like)
    display.setFont(&FreeMonoBold24pt7b);
    display.setTextColor(GxEPD_RED);
    display.setCursor(80, 40);
    display.println(weather->feelslike);

    // Humidity
    display.setFont(&FreeMonoBold18pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(170, 80);
    display.println(weather->humidity);

    // Description
    display.setFont(&FreeMonoBold18pt7b);
    display.setTextColor(GxEPD_RED);
    int16_t tbx, tby; uint16_t tbw, tbh;
    display.getTextBounds(weather->description, 0, 0, &tbx, &tby, &tbw, &tbh);
    uint16_t x = ((display.width() - tbw) / 2) - tbx;
    display.setCursor(x, 120);
    display.println(weather->description);

    // Updated time
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(200, 170);
    display.println(weather->updated);

  } while (display.nextPage());
}

void fillWeatherFromJson(Weather* weather) {
  int timezone_offset = (int) json["timezone_offset"];
  int dt = (int) json["current"]["dt"];
  int t = dt + timezone_offset;
  sprintf(weather->updated, "%02d:%02d", hour(t), minute(t));
  sprintf(weather->temp, "%.1f C", (double) json["current"]["temp"]);
  sprintf(weather->feelslike, "%.1f C", (double) json["current"]["feels_like"]);
  sprintf(weather->humidity, "%i %%", (int) json["current"]["humidity"]);
  sprintf(weather->main, "%s", (const char*) json["current"]["weather"][0]["main"]);
  sprintf(weather->description, "%s", (const char*) json["current"]["weather"][0]["description"]);
  sprintf(weather->icon, "%s", (const char*) json["current"]["weather"][0]["icon"]);

  char buf[256];
  sprintf(buf, "debug: %s / %s / %s / %s / %s / %s", weather->feelslike, weather->humidity, weather->updated, weather->main, weather->icon, weather->description);
  Serial.println(buf);
}

void displayCenteredText(char* text) {
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh; // boundary box window
  display.getTextBounds(text, 0, 0, &tbx, &tby, &tbw, &tbh); // it works for origin 0, 0, fortunately (negative tby!)
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  // full window mode is the initial mode, set it anyway
  display.setFullWindow();
  // here we use paged drawing, even if the processor has enough RAM for full buffer
  // so this can be used with any supported processor board.
  // the cost in code overhead and execution time penalty is marginal
  // tell the graphics class to use paged drawing mode
  display.firstPage();
  do
  {
    // this part of code is executed multiple times, as many as needed,
    // in case of full buffer it is executed once
    // IMPORTANT: each iteration needs to draw the same, to avoid strange effects
    // use a copy of values that might change, don't read e.g. from analog or pins in the loop!
    display.fillScreen(GxEPD_WHITE); // set the background to white (fill the buffer with value for white)
    display.setCursor(x, y); // set the postition to start printing text
    display.print(text); // print some text
    // end of part executed multiple times
  }
  // tell the graphics class to transfer the buffer content (page) to the controller buffer
  // the graphics class will command the controller to refresh to the screen when the last page has been transferred
  // returns true if more pages need be drawn and transferred
  // returns false if the last page has been transferred and the screen refreshed for panels without fast partial update
  // returns false for panels with fast partial update when the controller buffer has been written once more, to make the differential buffers equal
  // (for full buffered with fast partial update the (full) buffer is just transferred again, and false returned)
  while (display.nextPage());
}

boolean connectToWifi() {
  Serial.print("\nconnecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  unsigned int retries = 100;
  while (WiFi.status() != WL_CONNECTED && (retries-- > 0)) {
    Serial.print(".");
    delay(500);
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nWifi connection failed");
    return false;
  }
  Serial.println("");
  Serial.println("wifi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
  return true;
}

boolean getJSON(const char* url) {
  boolean success = false;
   
  if ((WiFi.status() == WL_CONNECTED)) {

    Serial.print("Connecting to ");
    Serial.println(url);
    
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
     Serial.print("HTTP code : ");
     Serial.println(httpCode);
    if (httpCode <= 0) {
      Serial.print("Error on HTTP request : ");
      Serial.println(httpCode);
    } else {
      json = JSON.parse(http.getString());
      
      if (JSON.typeof(json) == "undefined") {
        Serial.println("Parsing input failed!");
      } else {
        success = true;
      }
    }
    http.end();
  }  
  return success;
}

void sleep(uint64_t sleepTime) {
//  esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TOUCHPAD); // disable wake up from touch pad
  Serial.flush();
  display.powerOff();
  esp_sleep_enable_timer_wakeup((uint64_t) sleepTime * MICRO_SEC_TO_MILLI_SEC_FACTOR);
  esp_deep_sleep_start();
  delay(MINUTE);
}

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause();
  switch(wakeup_reason)
  {
    case 1  : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case 2  : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case 3  : Serial.println("Wakeup caused by timer"); break;
    case 4  : {
      Serial.print("Wakeup caused by touchpad pin "); 
      Serial.println(esp_sleep_get_touchpad_wakeup_status());
      break;
    }
    case 5  : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.println("Wakeup was not caused by deep sleep"); break;
  }
}
