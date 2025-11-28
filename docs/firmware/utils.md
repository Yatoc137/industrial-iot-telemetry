# **Utils Module**

------

This document provides a detailed and dedicated overview of the firmware’s **utility module (`utils.h`)**. It describes the module’s **enums**, **functions**, and **core features**, explaining how each component integrates into the broader architecture of the project.
 You will also find clarifications on the purpose of each element, common usage scenarios, and the role this module plays in supporting other parts of the firmware.

------

## **Enums**

---

### **UTIL_TEMP**

Defines the temperature units supported by the firmware: **Fahrenheit**, **Celsius**, and **Kelvin**.
 These are used by the internal temperature-conversion routines and serve as strongly typed arguments for external modules that rely on consistent and unambiguous unit handling.

### **UTIL_PRESSURE**

Defines the pressure units supported by the module: **Bar**, **PSI**, **kgf/cm²**, and **mmH₂O**.
 These values are used by the pressure-conversion routine, both internally and as argument types when other modules need to express or interpret pressure values in different engineering units.

------

## **Functions**

------

### **`static inline float util_map(float value, float in_min, float in_max, float out_min, float out_max)`**

This function performs a **linear transformation** of a numerical value from one interval to another.
 Given a value within the input range **$in_min, in_max$**, it computes the corresponding proportional value in the output range **$out_min, out_max$**.

This mapping approach is useful for:

- normalizing raw sensor measurements,
- scaling values between subsystems with different numeric domains,
- adjusting control signals,
- translating values into engineering units.

The function preserves the relative position of the value within its original range, ensuring consistency and predictable proportional behavior.

------

### **`static inline float util_smooth(float new_value, float \*state)`**

This function applies an **exponential smoothing filter** to a value, producing a softened output that reduces noise and stabilizes rapidly varying signals.

It blends the new sample (`new_value`) with the previously filtered value (`*state`) using a fixed smoothing factor:

- **90%** from the previous state
- **10%** from the new sample

This results in a low-pass–filtered signal that suppresses high-frequency noise and sudden fluctuations while still allowing the output to gradually follow long-term trends.

Because the function updates the value pointed to by `state`, it maintains a continuous history between successive calls, effectively functioning as a lightweight, real-time adaptive filter—ideal for sensor smoothing, control systems, and user-interface normalization.

------

### **`static inline float util_tempConvert(UTIL_TEMP from, float v, UTIL_TEMP to)`**

This function converts a temperature value between different units specified by the `UTIL_TEMP` enum: **Celsius**, **Fahrenheit**, and **Kelvin**.

To ensure consistency and numerical correctness, the conversion is performed in two phases using **Kelvin as the intermediate reference scale**, due to its absolute and linear nature.

#### **Conversion process**

1. **Convert input to Kelvin**
    Based on the `from` unit, the function translates the input temperature `v` into Kelvin:
   - Celsius → Kelvin
   - Fahrenheit → Kelvin
   - Kelvin → Kelvin (identity)
2. **Convert Kelvin to the target unit**
    The intermediate Kelvin value is then converted into the requested `to` unit using the appropriate formula.

This two-step approach ensures predictable and accurate conversions while eliminating redundancy and potential inconsistency between unit-specific formulas.
 If an invalid unit is encountered (which should not normally occur), the function returns the original input value.

This utility is particularly helpful when working with sensor data, inter-module communication, or any part of the firmware that requires consistent temperature representation.

------

### **`static inline float util_pressureConvert(UTIL_PRESSURE from, float v, UTIL_PRESSURE to)`**

This function performs conversions between pressure units defined in `UTIL_PRESSURE`: **Bar**, **PSI**, **kgf/cm²**, and **mmH₂O**.

The conversion follows a structured two-stage process similar to the temperature conversion routine. All values are first converted to **kilopascals (kPa)**—a widely recognized SI unit with well-defined relationships to other pressure units—before being converted to the requested output unit.

#### **Conversion process**

1. **Normalize the input to kPa**
    The `from` unit determines which coefficient is used to convert the input value to kPa:

   - Bar → kPa
   - PSI → kPa
   - kgf/cm² → kPa
   - mmH₂O → kPa

   Precise conversion constants ensure accuracy in engineering contexts.

2. **Convert from kPa to the target unit**
    The normalized kPa value is transformed into the desired unit:

   - kPa → Bar
   - kPa → PSI
   - kPa → kgf/cm²
   - kPa → mmH₂O

This approach centralizes all formulas, reduces floating-point drift, avoids duplicated logic, and simplifies future extensions—such as adding **atm**, **Torr**, **Pa**, or **MPa**.

In the unlikely event of an invalid unit, the function returns the original input value.
 This utility is essential for sensor interfaces, industrial measurement systems, calibration tools, and any part of the firmware that requires pressure values to be expressed in different engineering units.