#pragma once

// temperature units
typedef enum{
    FAHRENHEIT, // Fahrenheit
    CELSIUS,    // Celsius
    KELVIN      // Kelvin
}UTIL_TEMP;

// pressure units
typedef enum{
    BAR,    // Bar
    PSI,    // PSI
    KGFCM2, // KgF/CM2
    MMH2O   // mmH2O
}UTIL_PRESSURE;

typedef enum{
    RPM, // RPM
    RPS, // RPS
    Hz,  // Hz
    RadS // Rad/s
}UTIL_ROTATION;

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
        default: return 0.0f;
    }

    // converts value (in kelvin) to requested unit
    switch (to){
        case CELSIUS:     return k - 273.15f;
        case FAHRENHEIT:  return (k - 273.15f) * 9.0f/5.0f + 32.0f;
        case KELVIN:      return k;
        default: return 0.0f;
    }
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
        default: return 0.0f;
    }

    // converts value (in kPa) to requested unit
    switch (to){
        case BAR:     return kpa * 0.01f;
        case PSI:     return kpa * 0.1450377f;
        case KGFCM2:  return kpa * 0.0101972f;
        case MMH2O:   return kpa * 101.9716213f;
        default: return 0.0f;
    }
}

static inline float utilRotationConvert(UTIL_ROTATION from, float v, UTIL_ROTATION to){
    float rpm = 0.0f;

    switch (from){
        case RPM:  rpm = v;               break;
        case RPS:  rpm = v * 60.0f;       break;
        case Hz:   rpm = v * 60.0f;       break;
        case RadS: rpm = v * 9.54929658f; break;
        default: return 0.0f;
    }

    switch (to){
        case RPM:  return rpm;
        case RPS:  return rpm / 60.0f;
        case Hz:   return rpm / 60.0f;
        case RadS: return rpm * 0.10471976f;
        default: return 0.0f;
    }
}