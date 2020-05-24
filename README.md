# ESP32 Weather Station

That project is a weather station (getting data from openweathermap.org) displayed on an e-ink screen.

Here’s the [hackaday project page](https://hackaday.io/project/171910-esp32-weather-station) including pictures.

Hardware components are :

  * [Waveshare Universal e-Paper Raw Panel Driver Board ESP32 WiFi/Bluetooth control](https://www.ebay.fr/itm/Waveshare-2-7inch-E-Ink-Raw-Display-Panel-Three-Color-e-paper-SPI-Interface/253103850269?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2060353.m2749.l2649)
  * [2.7inch e-Paper (B) 264x176, raw display, three-color, SPI interface](https://www.ebay.fr/itm/Waveshare-Universal-e-Paper-Raw-Panel-Driver-Board-ESP32-WiFi-Bluetooth-control/254038211273?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2060353.m2749.l2649)

## Arduino env

use Board "ESP32 Dev Module" to build with Arduino IDE.

Copy `parameters.h.dist` to `parameters.h` and update it with your wifi settings and update the URL.

I’m using the nice [GxEPD2](https://github.com/ZinggJM/GxEPD2) library from [ZinggJM](https://github.com/ZinggJM). Thanks

## Weather API

  * https://openweathermap.org/api/one-call-api
  * create an account and an API KEY

## HTTP request & JSON parsing

  * https://randomnerdtutorials.com/esp32-http-get-post-arduino/

## HTTPS request

  * https://techtutorialsx.com/2017/11/18/esp32-arduino-https-get-request/