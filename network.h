boolean connectToWifi() {
  Serial.print("\nconnecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  unsigned int retries = 50;
  while (WiFi.status() != WL_CONNECTED && (retries-- > 0)) {
    Serial.print(".");
    delay(1000);
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nWifi connection failed");
    return false;
  }
  Serial.println("");
  Serial.println("wifi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("DNS: ");
  Serial.println(WiFi.dnsIP(0));
  Serial.println("");
  return true;
}

boolean disconnectFromWifi() {
  WiFi.disconnect();
}

boolean getWeatherJSON(const char* url) {
  boolean success = false;
   
  if ((WiFi.status() == WL_CONNECTED)) {

    Serial.print("Connecting to ");
    Serial.println(url);
    
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();
    Serial.print("HTTP code : ");
    Serial.println(httpCode);
    if (httpCode > 0) {
      weatherJson = JSON.parse(http.getString());
      
      if (JSON.typeof(weatherJson) == "undefined") {
        Serial.println("Parsing weatherJson input failed!");
      } else {
        success = true;
      }
    }
    http.end();
  }  
  return success;
}


boolean getLocalJSON(const char* url, const char* authorization) {
  boolean success = false;

  WiFiClientSecure secureClient;
  secureClient.setTimeout(20000);
  secureClient.setInsecure();
   
  if ((WiFi.status() == WL_CONNECTED)) {

    Serial.print("Connecting to ");
    Serial.println(url);
    
    HTTPClient http;
    http.begin(url);
    http.addHeader("Authorization", authorization);
    int httpCode = http.GET();
    Serial.print("HTTP code : ");
    Serial.println(httpCode);
    if (httpCode > 0) {
      localJson = JSON.parse(http.getString());
      
      if (JSON.typeof(localJson) == "undefined") {
        Serial.println("Parsing localJson input failed!");
      } else {
        success = true;
      }
    }
    http.end();
  }  
  return success;
}
