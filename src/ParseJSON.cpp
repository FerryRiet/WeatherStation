#include <ArduinoJson.h>

// Assuming the JSON string is stored in a variable (e.g., `jsonStr`)
// and you want to extract weather_code into a fixed-size array.

// Max number of hours in a day = 24
const size_t MAX_HOURS = 24;

void extractWeatherCodes(const char* json, uint8_t* weatherCodes, size_t& count) {
  // Use StaticJsonDocument with sufficient capacity.
  // Estimate: ~2000 bytes for ~24 hourly entries (conservative)
  JsonDocument doc;

  DeserializationError error = deserializeJson(doc, json);
  if (error) {
    // Handle deserialization error
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    count = 0;
    return;
  }

  // Navigate to "hourly" -> "weather_code"
  const JsonArray weatherCodeArray = doc["hourly"]["weather_code"];

  // Copy up to MAX_HOURS values
  count = std::min(weatherCodeArray.size(), MAX_HOURS);
  for (size_t i = 0; i < count; ++i) {
    weatherCodes[i] = static_cast<uint8_t>(weatherCodeArray[i]);
  }
}
