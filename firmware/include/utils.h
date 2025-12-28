#pragma once

// temperature Units
typedef enum{
    FAHRENHEIT, // Fahrenheit
    CELSIUS,    // Celsius
    KELVIN      // Kelvin
}UTIL_TEMP;

// pressure units
typedef enum{
    BAR,     // Bar
    PSI,     // PSI
    KGFCM2,  // KgF/CM2
    MMH2O    // mmH2O
}UTIL_PRESSURE;

// mapping function
static inline float utilMap(float value, float in_min, float in_max, float out_min, float out_max){
    // clamping
    if (value <= in_min) return out_min;
    if (value >= in_max) return out_max;

    // mapping
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// smoothing function
static inline float utilSmooth(float* state, float newValue){
    *state = (*state) * 0.8f + newValue * 0.2f; // 80% old value, 20% new value
    return *state;
}

// temperature unit conversion function 
static inline float utilTempConvert(UTIL_TEMP from, float v, UTIL_TEMP to){
    float k = 0.0f;

    // converts value to kelvin
    switch (from){
        case CELSIUS:     k = v + 273.15f; break;
        case FAHRENHEIT:  k = (v - 32.0f) * 5.0f/9.0f + 273.15f; break;
        case KELVIN:      k = v; break;
    }

    // converts value (in kelvin) to requested unit
    switch (to){
        case CELSIUS:     return k - 273.15f;
        case FAHRENHEIT:  return (k - 273.15f) * 9.0f/5.0f + 32.0f;
        case KELVIN:      return k;
    }

    return v;
}

// pressure conversion function
static inline float utilPressureConvert(UTIL_PRESSURE from, float v, UTIL_PRESSURE to){
    float kpa = 0.0f;

    // converts value to kPa
    switch (from){
        case BAR:     kpa = v * 100.0f;        break;
        case PSI:     kpa = v * 6.894757f;     break;
        case KGFCM2:  kpa = v * 98.0665f;      break;
        case MMH2O:   kpa = v * 0.00980665f;   break;
    }

    // converts value (in kPa) to requested unit
    switch (to){
        case BAR:     return kpa * 0.01f;
        case PSI:     return kpa * 0.1450377f;
        case KGFCM2:  return kpa * 0.0101972f;
        case MMH2O:   return kpa * 101.9716213f;
    }

    return v;
}