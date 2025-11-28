#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FAHRENHEIT,
    CELSIUS,
    KELVIN
} UTIL_TEMP;

typedef enum {
    BAR,
    PSI,
    KGFCM2,
    MMH2O
} UTIL_PRESSURE;

static inline float util_map(float value, float in_min, float in_max, float out_min, float out_max) {
    if (value <= in_min) return out_min;
    if (value >= in_max) return out_max;

    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static inline float util_smooth(float new_value, float *state) {
    *state = (*state) * 0.9f + new_value * 0.1f;
    return *state;
}

static inline float util_tempConvert(UTIL_TEMP from, float v, UTIL_TEMP to) {
    float k = 0.0f;

    switch (from) {
        case CELSIUS:     k = v + 273.15f; break;
        case FAHRENHEIT:  k = (v - 32.0f) * 5.0f/9.0f + 273.15f; break;
        case KELVIN:      k = v; break;
    }

    switch (to) {
        case CELSIUS:     return k - 273.15f;
        case FAHRENHEIT:  return (k - 273.15f) * 9.0f/5.0f + 32.0f;
        case KELVIN:      return k;
    }

    return v;
}

static inline float util_pressureConvert(UTIL_PRESSURE from, float v, UTIL_PRESSURE to) {
    float kpa = 0.0f;

    switch (from) {
        case BAR:     kpa = v * 100.0f;        break;
        case PSI:     kpa = v * 6.894757f;     break;
        case KGFCM2:  kpa = v * 98.0665f;      break;
        case MMH2O:   kpa = v * 0.00980665f;   break;
    }

    switch (to) {
        case BAR:     return kpa * 0.01f;
        case PSI:     return kpa * 0.1450377f;
        case KGFCM2:  return kpa * 0.0101972f;
        case MMH2O:   return kpa * 101.9716213f;
    }

    return v;
}

#ifdef __cplusplus
}
#endif