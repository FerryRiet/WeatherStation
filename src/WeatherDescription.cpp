#include "WeatherDescription.h"

static const char* const en[] = {
  "Clear sky",                    // 0
  "Mainly clear",                 // 1
  "Partly cloudy",                // 2
  "Overcast",                     // 3
  "Fog",                          // 45
  "Depositing rime fog",          // 48
  "Light drizzle",                // 51
  "Moderate drizzle",             // 53
  "Dense drizzle",                // 55
  "Light freezing drizzle",       // 56
  "Dense freezing drizzle",       // 57
  "Slight rain",                  // 61
  "Moderate rain",                // 63
  "Heavy rain",                   // 65
  "Light freezing rain",          // 66
  "Heavy freezing rain",          // 67
  "Slight snow",                  // 71
  "Moderate snow",                // 73
  "Heavy snow",                   // 75
  "Snow grains",                  // 77
  "Slight rain showers",          // 80
  "Moderate rain showers",        // 81
  "Violent rain showers",         // 82
  "Slight snow showers",          // 85
  "Heavy snow showers",           // 86
  "Thunderstorm",                 // 95
  "Thunderstorm with hail",       // 96
  "Thunderstorm with heavy hail"  // 99
};

static const char* const nl[] = {
  "Helder",                       // 0
  "Hoofdzakelijk helder",         // 1
  "Gedeeltelijk bewolkt",         // 2
  "Bewolkt",                      // 3
  "Mist",                         // 45
  "Cirkelmist",                   // 48
  "Lichte motregen",              // 51
  "Matige motregen",              // 53
  "Dichte motregen",              // 55
  "Lichte bevriezende motregen",  // 56
  "Dichte bevriezende motregen",  // 57
  "Lichte regen",                 // 61
  "Matige regen",                 // 63
  "Zware regen",                  // 65
  "Lichte bevriezende regen",     // 66
  "Zware bevriezende regen",      // 67
  "Lichte sneeuw",                // 71
  "Matige sneeuw",                // 73
  "Zware sneeuw",                 // 75
  "Sneeuwgraan",                  // 77
  "Lichte regenbui",              // 80
  "Matige regenbui",              // 81
  "Hevige regenbui",              // 82
  "Lichte sneeuwbui",             // 85
  "Zware sneeuwbui",              // 86
  "Onweer",                       // 95
  "Onweer met hagel",             // 96
  "Onweer met zware hagel"        // 99
};

static const char* const de[] = {
  "Heiter",                       // 0
  "Hauptsächlich klar",           // 1
  "Teilweise bewölkt",            // 2
  "Überwiegend bewölkt",          // 3
  "Nebel",                        // 45
  "Ablagerung von Rauhreifnebel", // 48
  "Leichter Nieselregen",         // 51
  "Mäßiger Nieselregen",          // 53
  "Dicker Nieselregen",           // 55
  "Leichter gefrierender Niesel", // 56
  "Dicker gefrierender Niesel",   // 57
  "Leichter Regen",               // 61
  "Mäßiger Regen",                // 63
  "Starker Regen",                // 65
  "Leichter Gefrierregen",        // 66
  "Starker Gefrierregen",         // 67
  "Leichter Schnee",              // 71
  "Mäßiger Schnee",               // 73
  "Starker Schnee",               // 75
  "Schneegriesel",                // 77
  "Leichte Schauer",              // 80
  "Mäßige Schauer",               // 81
  "Heftige Schauer",              // 82
  "Leichte Schneeschauer",        // 85
  "Stark Schneeschauer",          // 86
  "Gewitter",                     // 95
  "Gewitter mit Hagel",           // 96
  "Gewitter mit schwerem Hagel"   // 99
};

static const int8_t code_to_index[] = {
   0,  1,  2,  3, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1,  4, -1, -1,  5, -1,
  -1,  6, -1,  7, -1,  8,  9, 10, -1, -1,
  -1, 11, -1, 12, -1, 13, 14, 15, -1, -1,
  -1, 16, -1, 17, -1, 18, -1, 19, -1, -1,
  20, 21, 22, -1, -1, 23, 24, -1, -1, -1,
  -1, -1, -1, -1, -1, 25, 26, -1, -1, 27
};

const char* getWeatherDescription(int weather_code, int language) {
  if (weather_code < 0 || weather_code > 99)
    return "Unknown";

  int idx = code_to_index[weather_code];
  if (idx < 0)
    return "Unknown";

  switch (language) {
    case LANGUAGE_NL: return nl[idx];
    case LANGUAGE_DE: return de[idx];
    default:          return en[idx];
  }
}
