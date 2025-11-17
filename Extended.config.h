/* ---------------------------------------------------------------------------------------------------------------------------------
 * Extended configuration for OnStepX INFREQUENTLY USED options
 *
 *          For more information on setting OnStep up see http://www.stellarjourney.com/index.php?r=site/equipment_onstep 
 *                      and join the OnStep Groups.io at https://groups.io/g/onstep
 * 
 *           *** Read the compiler warnings and errors, they are there to help guard against invalid configurations ***
 *
 * ---------------------------------------------------------------------------------------------------------------------------------
 * ADJUST THE FOLLOWING TO CONFIGURE YOUR CONTROLLER FEATURES ----------------------------------------------------------------------
 * <-Req'd = always must set, <-Often = usually must set, Option = optional, Adjust = adjust as req'd, Infreq = infrequently changed
*/
//      Parameter Name              Value   Default  Notes                                                                      Hint

// =================================================================================================================================
// CONTROLLER ======================================================================================================================

// DEBUG ---------------------------------------------------------------------------------------------------------------------------
// Enables additional debugging and/or status messages on the specified SERIAL_DEBUG port (be sure to disable when done!)
// Note: The SERIAL_DEBUG port is often (almost always) attached to the same SERIAL_A port so it cannot be used for normal
//       LX200 protocol communications.  If this is the case set both to the same (faster) baud rate specified below.
#define DEBUG                         OFF //    OFF, Use ON for background error messages only, use VERBOSE for all           Infreq
                                          //         error and status messages, use CONSOLE for VT100 debug console,
                                          //         or use PROFILER for VT100 task profiler.
#define DEBUG_SERVO                   OFF //    OFF, n. Where n=1 to 9 as the designated axis for logging servo activity.     Option
#define DEBUG_ECHO_COMMANDS           OFF //    OFF, Use ON or ERRORS_ONLY to log commands to the debug serial port.          Option
#define SERIAL_DEBUG               Serial // Serial, Use any available h/w serial port. Serial1 or Serial2, etc.              Option
#define SERIAL_DEBUG_BAUD          230400 // 230400, n. Where n=9600,19200,57600,115200,230400,460800 (common baud rates.)    Option

// NON-VOLATILE STORAGE ------------------------------------------------------------------------------------------------------------
#define NV_WIPE                       OFF //         OFF, Causes the defaults to be written back into NV (FLASH,EEPROM,etc.)  Infreq
                                          //              ***     IMPORTANT: ENABLE THIS OPTION THEN UPLOAD, WAIT A MINUTE    ***
// Warning --->                           //              ***     OR TWO THEN SET THIS OPTION TO OFF AND UPLOAD AGAIN.        ***
                                          //              ***     LEAVING THIS OPTION ENABLED CAN CAUSE EXCESSIVE NV          ***
                                          //              ***     WEAR AND DAMAGE THE MICROCONTROLLER NV SUBSYSTEM !!!        ***

// FRAM CONFIGURATION (I2C Non-Volatile Memory) -----------------------------------------------------------------------------------
// To use an external FRAM module instead of the default NV storage, uncomment ONE of the following:                      Option
// #define NV_DRIVER                NV_MB85RC64  //  8KB I2C FRAM (MB85RC64T/V) at address 0x50                            Option
// #define NV_DRIVER               NV_MB85RC256  // 32KB I2C FRAM (MB85RC256V) at address 0x50                             Option

// Optional: Override default I2C address if your FRAM module uses a different address (A0/A1/A2 pins)
// #define NV_ADDRESS                     0x50  // Default I2C address. Can be 0x50-0x57 depending on A0-A2 jumpers      Option

// FRAM WIRING FOR FYSETC E4 (ESP32):
// ┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │  FRAM Module Pin  │  FYSETC E4 Pin  │  ESP32 GPIO  │  Notes                                                         │
// ├───────────────────┼─────────────────┼──────────────┼────────────────────────────────────────────────────────────────┤
// │  VCC              │  3.3V           │  3.3V        │  Power supply (NOT 5V!)                                         │
// │  GND              │  GND            │  GND         │  Ground                                                         │
// │  SDA              │  I2C SDA        │  GPIO21      │  I2C Data line (has internal pullup)                            │
// │  SCL              │  I2C SCL        │  GPIO22      │  I2C Clock line (has internal pullup)                           │
// │  WP (if present)  │  GND            │  GND         │  Write Protect - connect to GND to allow writes                │
// └─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
//
// FRAM ADVANTAGES:
//   - Very high endurance: >300M write cycles (vs ~100K for ESP32 Flash)
//   - Fast write time: 3ms (vs 5000ms for ESP32 Flash)
//   - Enables MOUNT_COORDS_MEMORY feature (requires frequent writes)
//   - More reliable for long-term data retention
//
// SETUP PROCEDURE:
//   1. Wire FRAM module to I2C pins as shown above
//   2. Uncomment appropriate NV_DRIVER line above (NV_MB85RC64 or NV_MB85RC256)
//   3. Set NV_WIPE to ON, compile and upload, wait 2 minutes
//   4. Set NV_WIPE back to OFF, compile and upload again
//   5. FRAM is now active and ready to use

// ESP32 VIRTUAL SERIAL BLUETOOTH AND IP COMMAND CHANNELS --------------------------------------------------------------------------
#define SERIAL_BT_MODE                OFF //    OFF, Use SLAVE to enable the interface (ESP32 only.)                          Option
#define SERIAL_BT_NAME          "OnStepX" //         "OnStepX", Bluetooth device name.                                        Adjust
#define SERIAL_IP_MODE                OFF //    OFF, WIFI_ACCESS_POINT or WIFI_STATION enables interface (ESP32 only.)        Option
#define MDNS_NAME               "onstepx" //    "onstepx", mDNS device name.                                                  Adjust
#define WEB_SERVER                    OFF //    OFF, ON enables Webserver (for Website plugin.)                               Option

// EXTERNAL GPIO SUPPORT -----------------------------------------------------------------------------------------------------------
#define GPIO_DEVICE                   OFF //    OFF, DS2413: for 2-ch or 4-ch using 1-wire gpio's (one or two devices.)       Option
                                          //         SWS: for 8-ch Serial gpio (normally 4 unused encoder pins.)
                                          //         MCP23008: for 8-ch I2C gpio.
                                          //         MCP23017, X9555, or X8575: for 16-ch I2C gpio.
                                          //         SSR74HC595: for up to 32-ch gpio (serial shift register, output only.)
                                          //         Works w/most OnStep features, channels assigned in order pin# 512 and up.

// ---------------------------------------------------------------------------------------------------------------------------------
