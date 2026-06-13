#ifndef OPEN_METEO_H
#define OPEN_METEO_H

#include <Arduino.h>


// Open-Meteo header file
// Empty header - add declarations as needed
struct strWeatherInfo
{
  float temperature ;
  float surface_pressure ;
  int   weather_code ;
  int   relative_humidity_2m;
  float precipitation ;
  float wind_speed_10m;
  int   wind_direction_10m;
  boolean valid;
};

// OpenWeatherMap API Info

const String WeatherURL = "https://api.open-meteo.com/v1/forecast?latitude=52.35&longitude=4.80&current=wind_direction_10m,temperature_2m,precipitation,weather_code,wind_speed_10m,relative_humidity_2m,rain&wind_speed_unit=ms&models=knmi_seamless";


strWeatherInfo getWeatherInfo() ;
void printWeatherInfo(const strWeatherInfo &str) ;
const char* windDirectionToString(int degrees) ;
int windSpeedToBeaufort(float speed_ms) ;
const char* beaufortDescription(int beaufort, int language) ;


#endif // OPEN_METEO_H