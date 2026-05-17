#ifndef WEATHER_DESCRIPTION_H
#define WEATHER_DESCRIPTION_H

#include <Arduino.h>

#define LANGUAGE_EN 0
#define LANGUAGE_NL 1
#define LANGUAGE_DE 2

const char* getWeatherDescription(int weather_code, int language);

#endif
