#include "icons/01d-sun.h"
#include "icons/02d-sun.h"
#include "icons/02d-cloud.h"
#include "icons/03d-cloud.h"
#include "icons/04d-cloud.h"
#include "icons/04d-cloud-back.h"
#include "icons/09d-cloud.h"
#include "icons/09d-rain.h"
#include "icons/10d-cloud.h"
#include "icons/10d-sun.h"
#include "icons/11d-cloud.h"
#include "icons/11d-lightning.h"
#include "icons/13d-snow.h"
#include "icons/50d-fog.h"

void drawText(int x, int y, char* text, int color) {
  display.setFont(&FreeMonoBold12pt7b);
  display.setTextColor(color);
  display.setCursor(x, y);
  display.println(text);
}

void drawSmallText(int x, int y, char* text, int color) {
  // Updated time
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(color);
  display.setCursor(x, y);
  display.println(text);
}

void drawBigText(int x, int y, char* text) {
  display.setFont(&FreeMonoBold18pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setCursor(x, y);
  display.println(text);
}

void drawIcon(int x, int y, char* icon) {
  if (strcmp(icon, "01d") == 0) {
    // 01d - Sun
    display.drawBitmap(x, y, icon_01d_sun_bits, icon_01d_sun_width, icon_01d_sun_height, GxEPD_RED);
  } else if (strcmp(icon, "01n") == 0) {
    // 01d - Sun - night
    display.drawBitmap(x, y, icon_01d_sun_bits, icon_01d_sun_width, icon_01d_sun_height, GxEPD_BLACK);
  } else if (strcmp(icon, "02d") == 0) {
    // 02d - Cloud, sun
    display.drawBitmap(x, y, icon_02d_sun_bits, icon_02d_sun_width, icon_02d_sun_height, GxEPD_RED);
    display.drawBitmap(x, y, icon_02d_cloud_bits, icon_02d_cloud_width, icon_02d_cloud_height, GxEPD_BLACK);
  } else if (strcmp(icon, "02n") == 0) {
    // 02d - Cloud, sun - night
    display.drawBitmap(x, y, icon_02d_sun_bits, icon_02d_sun_width, icon_02d_sun_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_02d_cloud_bits, icon_02d_cloud_width, icon_02d_cloud_height, GxEPD_BLACK);
  } else if (strcmp(icon, "03d") == 0 || strcmp(icon, "03n") == 0) {
    // 03d - Cloud
    display.drawBitmap(x, y, icon_03d_cloud_bits, icon_03d_cloud_width, icon_03d_cloud_height, GxEPD_BLACK);
  } else if (strcmp(icon, "04d") == 0) {
    // 04d - Cloud, second cloud
    display.drawBitmap(x, y, icon_04d_cloud_bits, icon_04d_cloud_width, icon_04d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_04d_cloud_back_bits, icon_04d_cloud_back_width, icon_04d_cloud_back_height, GxEPD_RED);
  } else if (strcmp(icon, "04n") == 0) {
    // 04d - Cloud, second cloud - night
    display.drawBitmap(x, y, icon_04d_cloud_bits, icon_04d_cloud_width, icon_04d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_04d_cloud_back_bits, icon_04d_cloud_back_width, icon_04d_cloud_back_height, GxEPD_BLACK);
  } else if (strcmp(icon, "09d") == 0) {
    // 09d - Clouds, rain
    display.drawBitmap(x, y, icon_09d_cloud_bits, icon_09d_cloud_width, icon_09d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_09d_rain_bits, icon_09d_rain_width, icon_09d_rain_height, GxEPD_RED);
  } else if (strcmp(icon, "09n") == 0) {
    // 09d - Clouds, rain - night
    display.drawBitmap(x, y, icon_09d_cloud_bits, icon_09d_cloud_width, icon_09d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_09d_rain_bits, icon_09d_rain_width, icon_09d_rain_height, GxEPD_BLACK);
  } else if (strcmp(icon, "10d") == 0) {
    // 10d - Clouds, sun, rain
    display.drawBitmap(x, y, icon_10d_cloud_bits, icon_10d_cloud_width, icon_10d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_10d_sun_bits, icon_10d_sun_width, icon_10d_sun_height, GxEPD_RED);
  } else if (strcmp(icon, "10n") == 0) {
    // 10d - Clouds, sun, rain - night
    display.drawBitmap(x, y, icon_10d_cloud_bits, icon_10d_cloud_width, icon_10d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_10d_sun_bits, icon_10d_sun_width, icon_10d_sun_height, GxEPD_BLACK);
  } else if (strcmp(icon, "11d") == 0) {
    // 11d - Clouds, lightning
    display.drawBitmap(x, y, icon_11d_cloud_bits, icon_11d_cloud_width, icon_11d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_11d_ligthning_bits, icon_11d_ligthning_width, icon_11d_ligthning_height, GxEPD_RED);
  } else if (strcmp(icon, "11n") == 0) {
    // 11d - Clouds, lightning - night
    display.drawBitmap(x, y, icon_11d_cloud_bits, icon_11d_cloud_width, icon_11d_cloud_height, GxEPD_BLACK);
    display.drawBitmap(x, y, icon_11d_ligthning_bits, icon_11d_ligthning_width, icon_11d_ligthning_height, GxEPD_BLACK);
  } else if (strcmp(icon, "13d") == 0 || strcmp(icon, "13n") == 0) {
    // 13d - Snow
    display.drawBitmap(x, y, icon_13d_snow_bits, icon_13d_snow_width, icon_13d_snow_height, GxEPD_BLACK);
  } else if (strcmp(icon, "50d") == 0 ||strcmp(icon, "50n") == 0) {
    // 50d - Fog
    display.drawBitmap(x, y, icon_50d_fog_bits, icon_50d_fog_width, icon_50d_fog_height, GxEPD_BLACK);
  }
}

void displayDayMinMax(int x, char* title, char* icon, char* temp1, char* temp2, char* humidity) {
  int offsetTitle = strlen(title) == 1 ? 32 : 10;
  drawBigText(x + offsetTitle, 28, title);
  drawIcon(x, 28, icon);
  drawText(x + 10, 114, temp1, GxEPD_BLACK);
  drawText(x + 10, 136, temp2, GxEPD_BLACK);
  drawSmallText(x + 16, 155, humidity, GxEPD_BLACK);
}

void displayWeather(Weather* weather) {
  display.fillScreen(GxEPD_WHITE);
  display.firstPage();
  do
  {
    displayDayMinMax(5, "H+1", weather->iconH1, weather->feelsLikeH1, weather->tempH1, weather->humidityH1);
    displayDayMinMax(95, "J", weather->iconD, weather->tempMinD, weather->tempMaxD, weather->humidityD);
    displayDayMinMax(185, "J+1", weather->iconD1, weather->tempMinD1, weather->tempMaxD1, weather->humidityD1);
    drawSmallText(35, 174, weather->updated, GxEPD_RED);
  } while (display.nextPage());
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
