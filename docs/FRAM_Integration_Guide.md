# FRAM Module Integration Guide for OnStepX

## Overview

This guide explains how to integrate an external FRAM (Ferroelectric RAM) module with OnStepX, providing superior non-volatile storage compared to the default ESP32 flash memory.

## Supported FRAM Modules

OnStepX supports Fujitsu MB85RC series I2C FRAM modules:

- **MB85RC64** (8KB) - Part numbers: MB85RC64T, MB85RC64V
- **MB85RC256** (32KB) - Part number: MB85RC256V

Default I2C address: `0x50` (configurable via A0/A1/A2 address pins)

## Hardware Wiring

### FYSETC E4 (ESP32) Wiring Diagram

```
FRAM Module          FYSETC E4 Board
┌─────────────┐      ┌──────────────────┐
│ VCC      ●──┼──────┤ 3.3V             │
│ GND      ●──┼──────┤ GND              │
│ SDA      ●──┼──────┤ GPIO21 (I2C SDA) │
│ SCL      ●──┼──────┤ GPIO22 (I2C SCL) │
│ WP       ●──┼──┐   │                  │
└─────────────┘  │   └──────────────────┘
                 │
                 └──→ GND (disable write protection)
```

### Pin Mapping Table

| FRAM Pin | FYSETC E4 | ESP32 GPIO | Description |
|----------|-----------|------------|-------------|
| VCC      | 3.3V      | 3.3V       | **Important:** Use 3.3V, NOT 5V! |
| GND      | GND       | GND        | Ground |
| SDA      | I2C SDA   | GPIO21     | I2C Data (has internal pullup) |
| SCL      | I2C SCL   | GPIO22     | I2C Clock (has internal pullup) |
| WP       | GND       | GND        | Write Protect (connect to GND to enable writes) |

### Notes on Wiring

1. **Voltage:** FRAM modules are typically 3.3V or 5V. For ESP32 boards like FYSETC E4, use **3.3V only** to prevent damage.

2. **Pull-up Resistors:** ESP32 has internal I2C pull-ups. External 4.7kΩ resistors (SDA/SCL to 3.3V) can be added if you experience communication issues or have long cable runs.

3. **Write Protection:** The WP pin on FRAM modules enables hardware write protection. Connect to GND to allow writes. Some modules don't have this pin.

4. **I2C Address:** The default address is 0x50. Some modules have A0, A1, A2 address selection pins allowing addresses from 0x50 to 0x57.

## Software Configuration

### Step 1: Edit Extended.config.h

Open `Extended.config.h` and locate the FRAM configuration section (around line 37). Uncomment the appropriate line for your FRAM module:

```cpp
// For 8KB FRAM module
#define NV_DRIVER NV_MB85RC64

// OR for 32KB FRAM module
#define NV_DRIVER NV_MB85RC256
```

### Step 2: Optional - Custom I2C Address

If your FRAM module uses a non-default address (via A0/A1/A2 pins), uncomment and set:

```cpp
#define NV_ADDRESS 0x51  // Example: if A0 is pulled high
```

### Step 3: Initialize FRAM (First Time Only)

**Important:** First-time setup requires wiping the existing NV storage.

1. In `Extended.config.h`, temporarily change:
   ```cpp
   #define NV_WIPE ON
   ```

2. Compile and upload the firmware
3. **Wait 2 minutes** for initialization to complete
4. Change back to:
   ```cpp
   #define NV_WIPE OFF
   ```
5. Compile and upload again

**Warning:** Never leave `NV_WIPE ON` permanently as it will continuously erase and rewrite memory, potentially damaging the FRAM module.

### Step 4: Verify Operation

After uploading, the system should:
- Boot normally
- Store all settings in FRAM instead of ESP32 flash
- Show faster save operations (3ms vs 5000ms)

## Advantages of FRAM over ESP32 Flash

| Feature | ESP32 Flash | FRAM MB85RC |
|---------|-------------|-------------|
| Capacity | 4KB | 8KB or 32KB |
| Write Endurance | ~100,000 cycles | **>300,000,000 cycles** |
| Write Time | 5000ms | **3ms** |
| Reliability | Medium | Very High |
| Data Retention | 20 years | 10+ years |
| Cache Support | No | Yes |

## Advanced Features Enabled by FRAM

### Mount Coordinates Memory

With FRAM installed, you can enable a feature that frequently saves mount position. This would quickly wear out EEPROM or flash storage.

In `Config.h`, set:
```cpp
#define MOUNT_COORDS_MEMORY ON
```

This feature:
- Remembers approximate mount coordinates
- Enables faster startup alignment
- **Requires FRAM** due to frequent write operations
- Mount must remain stationary when powered down

## Troubleshooting

### FRAM Not Detected

1. **Check wiring:** Verify all connections, especially SDA/SCL
2. **Check voltage:** Ensure FRAM receives 3.3V (measure with multimeter)
3. **Check address:** Verify I2C address matches configuration (use I2C scanner sketch)
4. **Add pull-ups:** Try external 4.7kΩ resistors on SDA and SCL

### Data Not Persisting

1. **Check WP pin:** Ensure write protection is disabled (WP connected to GND)
2. **Verify NV_WIPE:** Ensure it's set to OFF after initial setup
3. **Check initialization:** Confirm you waited 2 minutes during first setup with NV_WIPE ON

### System Unstable

1. **Power supply:** FRAM may require stable power; check 3.3V rail stability
2. **I2C interference:** Keep I2C wires short and away from stepper motor cables
3. **Pull-up resistors:** May need external pull-ups if wire length >6 inches

## I2C Scanner Tool

If experiencing issues, use this Arduino sketch to scan for I2C devices:

```cpp
#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // SDA=21, SCL=22 for FYSETC E4
  Serial.println("I2C Scanner");
}

void loop() {
  byte error, address;
  int nDevices = 0;

  for(address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    }
  }

  if (nDevices == 0) Serial.println("No I2C devices found");
  delay(5000);
}
```

Expected output with FRAM connected: `I2C device found at address 0x50`

## Technical Implementation Details

OnStepX FRAM support is implemented in:
- `src/lib/nv/NV_MB85RC.h` - FRAM driver header
- `src/lib/nv/NV_MB85RC.cpp` - FRAM driver implementation
- `src/HAL/HAL_ESP32.h` - ESP32 HAL configuration

The implementation provides:
- Automatic caching with 3ms write delay
- Checksum error detection
- Seamless integration with OnStepX NV abstraction layer
- Support for multiple FRAM sizes

## Other Compatible Boards

While this guide focuses on FYSETC E4, FRAM can be used with any OnStepX-compatible board that has I2C capability. Check your board's pinmap file in `src/pinmaps/` for I2C pin assignments.

Common boards with I2C support:
- Most ESP32 boards
- Teensy 3.x/4.x
- Arduino Mega with ATmega2560
- STM32 boards

## References

- [Fujitsu FRAM MB85RC Series Datasheet](https://www.fujitsu.com/jp/group/fsm/en/products/fram/)
- [OnStepX Documentation](http://www.stellarjourney.com/index.php?r=site/equipment_onstep)
- [OnStepX Groups.io](https://groups.io/g/onstep)

## License

This documentation is part of the OnStepX project.
