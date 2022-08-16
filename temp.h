#ifdef RF_RX_PIN
#include <Arduino.h>
#include <ErriezOregonTHN128Esp32Receive.h> // Lib from https://github.com/paulgreg/ErriezOregonTHN128-esp32
#endif

struct LocalTemp {
  char temp[10];
};

#ifdef RF_RX_PIN
void printReceivedData(OregonTHN128Data_t *data) {
    bool negativeTemperature = false;
    static uint32_t rxCount = 0;
    int16_t tempAbs;
    char msg[80];

    // Convert to absolute temperature
    tempAbs = data->temperature;
    if (tempAbs < 0) {
        negativeTemperature = true;
        tempAbs *= -1;
    }
    snprintf_P(msg, sizeof(msg), 
               PSTR("RX %lu: Rol: %d, Channel %d, Temp: %s%d.%d, Low batt: %d (0x%08lx)"),
               rxCount++,
               data->rollingAddress, data->channel,
               (negativeTemperature ? "-" : ""), (tempAbs / 10), (tempAbs % 10), data->lowBattery,
               data->rawData);
    Serial.println(msg);
}

void fillLocalTempFromJson(OregonTHN128Data_t *oregonData, LocalTemp* localTemp) {
  bool negativeTemperature = false;
  int16_t tempAbs = oregonData->temperature;

  // Convert to absolute temperature
  if (tempAbs < 0) {
      negativeTemperature = true;
      tempAbs *= -1;
  }

  sprintf(localTemp->temp, "%s%d", (negativeTemperature ? "-" : ""), (tempAbs / 10)); 
}
#endif
