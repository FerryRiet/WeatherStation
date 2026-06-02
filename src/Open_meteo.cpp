// Open-Meteo implementation file
// Implementation of getWeatherInfo function

#include "Open_meteo.h"
#include "WeatherDescription.h"
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

strWeatherInfo getWeatherInfo()
{
  strWeatherInfo info;
  
  // Set default values
  info.valid = false;
  info.temperature = 0.0;
  info.surface_pressure = 0.0;
  info.weather_code = 0;
  info.relative_humidity_2m = 0;
  info.precipitation = 0.0;
  info.wind_speed_10m = 0.0;
  info.wind_direction_10m = 0;
  
  HTTPClient http;

  http.begin(WeatherURL);
  http.setTimeout(10000);
  
  int httpCode = http.GET();
  
  if (httpCode == 200) {
    String payload = http.getString();
    
	  JsonDocument doc;
	
    DeserializationError error = deserializeJson(doc, payload);
    
    if (!error) {
      info.temperature = doc["current"]["temperature_2m"] | 0.0f;
      info.surface_pressure = doc["current"]["pressure"] | 0.0f;
      info.weather_code = doc["current"]["weather_code"] | 0;
      info.relative_humidity_2m = doc["current"]["relative_humidity_2m"] | 0;
      info.precipitation = doc["current"]["precipitation"] | 0.0f;
      info.wind_speed_10m = doc["current"]["wind_speed_10m"] | 0.0f;
      info.wind_direction_10m = doc["current"]["wind_direction_10m"] | 0;

      info.valid = true ;
    }
  }
  
  http.end();
  
  return info;
}
int windSpeedToBeaufort(float speed_ms) {
  if (speed_ms < 0.3f) return 0;
  if (speed_ms < 1.6f) return 1;
  if (speed_ms < 3.4f) return 2;
  if (speed_ms < 5.5f) return 3;
  if (speed_ms < 8.0f) return 4;
  if (speed_ms < 10.8f) return 5;
  if (speed_ms < 13.9f) return 6;
  if (speed_ms < 17.2f) return 7;
  if (speed_ms < 20.8f) return 8;
  if (speed_ms < 24.5f) return 9;
  if (speed_ms < 28.5f) return 10;
  if (speed_ms < 32.7f) return 11;
  return 12;
}

const char* beaufortDescription(int beaufort) {
  static const char* desc[] = {
    "Calm", "Light air", "Light breeze", "Gentle breeze",
    "Moderate breeze", "Fresh breeze", "Strong breeze",
    "Near gale", "Gale", "Severe gale", "Storm",
    "Violent storm", "Hurricane"
  };
  if (beaufort < 0 || beaufort > 12) return "";
  return desc[beaufort];
}

const char* windDirectionToString(int degrees) {
  const char* directions[] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};
  int index = (int)((degrees + 22.5) / 45.0) % 8;
  return directions[index];
}

void printWeatherInfo(const strWeatherInfo &str) {
  if (!str.valid) {
    Serial.println("Invalid weather data");
    return;
  }
  Serial.println(String("Temperature: ") + str.temperature) ;
  int bft = windSpeedToBeaufort(str.wind_speed_10m);
  Serial.println(String("Wind: ") + str.wind_speed_10m + " m/s " + windDirectionToString(str.wind_direction_10m) + " B" + bft + " " + beaufortDescription(bft)) ;
  Serial.print(String("Weather: ") + str.weather_code) ;
  Serial.println(String(" ") + getWeatherDescription(str.weather_code,1)) ;
  Serial.println(String("Precipitation: ") + str.precipitation) ;
  Serial.println(String("Relative Humidity: ") + str.relative_humidity_2m) ;
}