# **Firmware Overview**

------

This document provides a high-level overview of the project's firmware structure. It introduces the main files and modules, summarizing their roles, data types, enums, and functions.
 Its goal is to give the reader a broad understanding of how the firmware is organized and how its components interact.
 For more in-depth information on a specific file or subsystem, refer to the corresponding dedicated documentation.

------

### **utils.h**

- **2 enums**
- **4 functions**

The `utils.h` file acts as a foundational support module for the entire firmware. It centralizes commonly used utility routines, helping maintain consistency and reducing code duplication across the project.
 Among its responsibilities are unit conversions, value mapping, and smoothing functions—operations frequently required by various modules throughout the system.