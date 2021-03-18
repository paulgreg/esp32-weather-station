# ESP32 Weather Station

That project is a weather station (getting data from openweathermap.org) displayed on an e-ink screen.

The main advantage of using an eink screen is that display stays, even if esp32 is powered down.
So the ESP32 is waking up, fetch weather data, update screen and sleeps for one hour.
Also, refresh is stopped from around midnight to 6 a.m.

Here’s the [hackaday project page](https://hackaday.io/project/171910-esp32-weather-station) including pictures.

Hardware components are :

  * [Waveshare Universal e-Paper Raw Panel Driver Board ESP32 WiFi/Bluetooth control](https://www.ebay.fr/itm/Waveshare-2-7inch-E-Ink-Raw-Display-Panel-Three-Color-e-paper-SPI-Interface/253103850269?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2060353.m2749.l2649)
  * [2.7inch e-Paper (B) 264x176, raw display, three-color, SPI interface](https://www.ebay.fr/itm/Waveshare-Universal-e-Paper-Raw-Panel-Driver-Board-ESP32-WiFi-Bluetooth-control/254038211273?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2060353.m2749.l2649)

## Arduino env

use Board "ESP32 Dev Module" to build with Arduino IDE.

Copy `parameters.h.dist` to `parameters.h` and update it with your wifi settings and update the URL (you need to change lat/lng and set your OpenWeatherMap API token).

I’m using the nice [GxEPD2](https://github.com/ZinggJM/GxEPD2) library from [ZinggJM](https://github.com/ZinggJM). Thanks

## Weather API

  * https://openweathermap.org/api/one-call-api
  * create an account and an API KEY

## Icons

Icons are [official icons from OpenWeatherMap](https://openweathermap.org/weather-conditions#How-to-get-icon-URL).

To be able to open them correctly in GxEPD2, I convert them using [LCD Assistant](http://en.radzio.dxp.pl/bitmap_converter/) with byte orientation set to horizontal and big endian settings.
It can be opened via wine (by adding 32 bits architecture).

## Fonts

Fonts are from [Adafruit-GFX-Library-fontconvert](https://github.com/paulgreg/Adafruit-GFX-Library-fontconvert) project.

## HTTP request & JSON parsing

  * https://randomnerdtutorials.com/esp32-http-get-post-arduino/

## HTTPS request

  * https://techtutorialsx.com/2017/11/18/esp32-arduino-https-get-request/
