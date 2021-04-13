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
    if (httpCode > 0) {
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
