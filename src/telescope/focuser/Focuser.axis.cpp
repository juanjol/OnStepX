//--------------------------------------------------------------------------------------------------
// telescope focuser control, axis instances

#include "Focuser.h"

#ifdef FOCUSER_PRESENT

#if AXIS4_DRIVER_MODEL != OFF
  #ifdef AXIS4_SERVO_PRESENT
    ServoControl servoControlAxis4;

    #if AXIS4_ENCODER == AB
      Quadrature encAxis4(AXIS4_ENCODER_A_PIN, AXIS4_ENCODER_B_PIN, 4);
    #elif AXIS4_ENCODER == AB_ESP32
      QuadratureEsp32 encAxis4(AXIS4_ENCODER_A_PIN, AXIS4_ENCODER_B_PIN, 4);
    #elif AXIS4_ENCODER == CW_CCW
      CwCcw encAxis4(AXIS4_ENCODER_A_PIN, AXIS4_ENCODER_B_PIN, 4);
    #elif AXIS4_ENCODER == PULSE_DIR
      PulseDir encAxis4(AXIS4_ENCODER_A_PIN, AXIS4_ENCODER_B_PIN, 4);
    #elif AXIS4_ENCODER == PULSE_ONLY
      PulseOnly encAxis4(AXIS4_ENCODER_A_PIN, &servoControlAxis4.directionHint, 4);
    #elif AXIS4_ENCODER == AS47_H49B_B
      As37h39bb encAxis4(AXIS4_ENCODER_A_PIN, AXIS4_ENCODER_B_PIN, 4);
    #elif AXIS4_ENCODER == SERIAL_BRIDGE
      SerialBridge encAxis4(4);
    #endif

    #if AXIS4_SERVO_FEEDBACK == FB_PID
      Pid pidAxis4(AXIS4_PID_P, AXIS4_PID_I, AXIS4_PID_D, AXIS4_PID_P_GOTO, AXIS4_PID_I_GOTO, AXIS4_PID_D_GOTO, AXIS4_PID_SENSITIVITY);
    #endif

    #if AXIS4_DRIVER_MODEL == SERVO_EE || AXIS4_DRIVER_MODEL == SERVO_PE
      const ServoDcPins ServoPinsAxis4 = {AXIS4_SERVO_PH1_PIN, AXIS4_SERVO_PH1_STATE, AXIS4_SERVO_PH2_PIN, AXIS4_SERVO_PH2_STATE, AXIS4_ENABLE_PIN, AXIS4_ENABLE_STATE, AXIS4_FAULT_PIN};
      const ServoDcSettings ServoSettingsAxis4 = {AXIS4_DRIVER_MODEL, AXIS4_DRIVER_STATUS, AXIS4_SERVO_VELOCITY_MAX, AXIS4_SERVO_ACCELERATION};
      ServoDc driver4(4, &ServoPinsAxis4, &ServoSettingsAxis4);
    #elif AXIS4_DRIVER_MODEL == SERVO_TMC2130_DC || AXIS4_DRIVER_MODEL == SERVO_TMC5160_DC
      const ServoDcTmcSpiPins ServoPinsAxis4 = {AXIS4_STEP_PIN, AXIS4_DIR_PIN, AXIS4_ENABLE_PIN, AXIS4_ENABLE_STATE, AXIS4_M0_PIN, AXIS4_M1_PIN, AXIS4_M2_PIN, AXIS4_M3_PIN, AXIS4_FAULT_PIN};
      const ServoDcTmcSettings ServoSettingsAxis4 = {AXIS4_DRIVER_MODEL, AXIS4_DRIVER_STATUS, AXIS4_SERVO_VELOCITY_MAX, AXIS4_SERVO_ACCELERATION, AXIS4_DRIVER_MICROSTEPS, AXIS4_DRIVER_IRUN};
      ServoDcTmcSPI driver4(4, &ServoPinsAxis4, &ServoSettingsAxis4);
    #elif AXIS4_DRIVER_MODEL == SERVO_TMC2209
      const ServoTmcPins ServoPinsAxis4 = {AXIS4_STEP_PIN, AXIS4_DIR_PIN, AXIS4_ENABLE_PIN, AXIS4_ENABLE_STATE, AXIS4_M0_PIN, AXIS4_M1_PIN, AXIS4_FAULT_PIN};
      const ServoTmcSettings ServoSettingsAxis4 = {AXIS4_DRIVER_MODEL, AXIS4_DRIVER_STATUS, AXIS4_SERVO_VELOCITY_MAX, AXIS4_SERVO_ACCELERATION, AXIS4_DRIVER_MICROSTEPS, AXIS4_DRIVER_IRUN, AXIS4_DRIVER_VELOCITY};
      ServoTmc2209 driver4(4, &ServoPinsAxis4, &ServoSettingsAxis4);
    #endif

    ServoMotor motor4(4, ((ServoDriver*)&driver4), &encAxis4, AXIS4_ENCODER_ORIGIN, AXIS4_ENCODER_REVERSE == ON, &pidAxis4, &servoControlAxis4, AXIS4_SYNC_THRESHOLD);
  #endif

  #ifdef AXIS4_STEP_DIR_PRESENT
    const StepDirDriverPins DriverPinsAxis4 = {AXIS4_M0_PIN, AXIS4_M1_PIN, AXIS4_M2_PIN, AXIS4_M2_ON_STATE, AXIS4_M3_PIN, AXIS4_DECAY_PIN, AXIS4_FAULT_PIN};
    const StepDirDriverSettings DriverSettingsAxis4 = {AXIS4_DRIVER_MODEL, AXIS4_DRIVER_MICROSTEPS, AXIS4_DRIVER_MICROSTEPS_GOTO, AXIS4_DRIVER_IHOLD, AXIS4_DRIVER_IRUN, AXIS4_DRIVER_IGOTO, AXIS4_DRIVER_INTPOL, AXIS4_DRIVER_DECAY, AXIS4_DRIVER_DECAY_GOTO, AXIS4_DRIVER_STATUS};
    #if defined(AXIS4_STEP_DIR_LEGACY)
      StepDirGeneric driver4(4, &DriverPinsAxis4, &DriverSettingsAxis4);
    #elif defined(AXIS4_STEP_DIR_TMC_SPI)
      StepDirTmcSPI driver4(4, &DriverPinsAxis4, &DriverSettingsAxis4);
    #elif defined(AXIS4_STEP_DIR_TMC_UART)
      StepDirTmcUART driver4(4, &DriverPinsAxis4, &DriverSettingsAxis4);
    #endif

    const StepDirPins StepDirPinsAxis4 = {AXIS4_STEP_PIN, AXIS4_STEP_STATE, AXIS4_DIR_PIN, AXIS4_ENABLE_PIN, AXIS4_ENABLE_STATE};
    StepDirMotor motor4(4, &StepDirPinsAxis4, ((StepDirDriver*)&driver4));
  #endif

  const AxisPins PinsAxis4 = {AXIS4_SENSE_LIMIT_MIN_PIN, AXIS4_SENSE_HOME_PIN, AXIS4_SENSE_LIMIT_MAX_PIN, {AXIS4_SENSE_HOME, AXIS4_SENSE_HOME_INIT, AXIS4_SENSE_HOME_DIST_LIMIT*1000.0F, AXIS4_SENSE_LIMIT_MIN, AXIS4_SENSE_LIMIT_MAX, AXIS4_SENSE_LIMIT_INIT}};
  const AxisSettings SettingsAxis4 = {AXIS4_STEPS_PER_MICRON, AXIS4_REVERSE, {AXIS4_LIMIT_MIN*1000.0F, AXIS4_LIMIT_MAX*1000.0F}, AXIS4_BACKLASH_RATE};
  Axis axis4(4, &PinsAxis4, &SettingsAxis4, AXIS_MEASURE_MICRONS);
#endif

#if AXIS5_DRIVER_MODEL != OFF
  #ifdef AXIS5_SERVO_PRESENT
    ServoControl servoControlAxis5;

    #if AXIS5_ENCODER == AB
      Quadrature encAxis5(AXIS5_ENCODER_A_PIN, AXIS5_ENCODER_B_PIN, 5);
    #elif AXIS5_ENCODER == AB_ESP32
      QuadratureEsp32 encAxis5(AXIS5_ENCODER_A_PIN, AXIS5_ENCODER_B_PIN, 5);
    #elif AXIS5_ENCODER == CW_CCW
      CwCcw encAxis5(AXIS5_ENCODER_A_PIN, AXIS5_ENCODER_B_PIN, 5);
    #elif AXIS5_ENCODER == PULSE_DIR
      PulseDir encAxis5(AXIS5_ENCODER_A_PIN, AXIS5_ENCODER_B_PIN, 5);
    #elif AXIS5_ENCODER == PULSE_ONLY
      PulseOnly encAxis5(AXIS5_ENCODER_A_PIN, &servoControlAxis5.directionHint, 5);
    #elif AXIS5_ENCODER == AS57_H59B_B
      As37h39bb encAxis5(AXIS5_ENCODER_A_PIN, AXIS5_ENCODER_B_PIN, 5);
    #elif AXIS5_ENCODER == SERIAL_BRIDGE
      SerialBridge encAxis5(5);
    #endif

    #if AXIS5_SERVO_FEEDBACK == FB_PID
      Pid pidAxis5(AXIS5_PID_P, AXIS5_PID_I, AXIS5_PID_D, AXIS5_PID_P_GOTO, AXIS5_PID_I_GOTO, AXIS5_PID_D_GOTO, AXIS5_PID_SENSITIVITY);
    #endif

    #if AXIS5_DRIVER_MODEL == SERVO_EE || AXIS5_DRIVER_MODEL == SERVO_PE
      const ServoDcPins ServoPinsAxis5 = {AXIS5_SERVO_PH1_PIN, AXIS5_SERVO_PH1_STATE, AXIS5_SERVO_PH2_PIN, AXIS5_SERVO_PH2_STATE, AXIS5_ENABLE_PIN, AXIS5_ENABLE_STATE, AXIS5_FAULT_PIN};
      const ServoDcSettings ServoSettingsAxis5 = {AXIS5_DRIVER_MODEL, AXIS5_DRIVER_STATUS, AXIS5_SERVO_VELOCITY_MAX, AXIS5_SERVO_ACCELERATION};
      ServoDc driver5(5, &ServoPinsAxis5, &ServoSettingsAxis5);
    #elif AXIS5_DRIVER_MODEL == SERVO_TMC2130_DC || AXIS5_DRIVER_MODEL == SERVO_TMC5160_DC
      const ServoDcTmcSpiPins ServoPinsAxis5 = {AXIS5_STEP_PIN, AXIS5_DIR_PIN, AXIS5_ENABLE_PIN, AXIS5_ENABLE_STATE, AXIS5_M0_PIN, AXIS5_M1_PIN, AXIS5_M2_PIN, AXIS5_M3_PIN, AXIS5_FAULT_PIN};
      const ServoDcTmcSettings ServoSettingsAxis5 = {AXIS5_DRIVER_MODEL, AXIS5_DRIVER_STATUS, AXIS5_SERVO_VELOCITY_MAX, AXIS5_SERVO_ACCELERATION, AXIS5_DRIVER_MICROSTEPS, AXIS5_DRIVER_IRUN};
      ServoDcTmcSPI driver5(5, &ServoPinsAxis5, &ServoSettingsAxis5);
    #elif AXIS5_DRIVER_MODEL == SERVO_TMC2209
      const ServoTmcPins ServoPinsAxis5 = {AXIS5_STEP_PIN, AXIS5_DIR_PIN, AXIS5_ENABLE_PIN, AXIS5_ENABLE_STATE, AXIS5_M0_PIN, AXIS5_M1_PIN, AXIS5_FAULT_PIN};
      const ServoTmcSettings ServoSettingsAxis5 = {AXIS5_DRIVER_MODEL, AXIS5_DRIVER_STATUS, AXIS5_SERVO_VELOCITY_MAX, AXIS5_SERVO_ACCELERATION, AXIS5_DRIVER_MICROSTEPS, AXIS5_DRIVER_IRUN, AXIS5_DRIVER_VELOCITY};
      ServoTmc2209 driver5(5, &ServoPinsAxis5, &ServoSettingsAxis5);
    #endif

    ServoMotor motor5(5, ((ServoDriver*)&driver5), &encAxis5, AXIS5_ENCODER_ORIGIN, AXIS5_ENCODER_REVERSE == ON, &pidAxis5, &servoControlAxis5, AXIS5_SYNC_THRESHOLD);
  #endif

  #ifdef AXIS5_STEP_DIR_PRESENT
    const StepDirDriverPins DriverPinsAxis5 = {AXIS5_M0_PIN, AXIS5_M1_PIN, AXIS5_M2_PIN, AXIS5_M2_ON_STATE, AXIS5_M3_PIN, AXIS5_DECAY_PIN, AXIS5_FAULT_PIN};
    const StepDirDriverSettings DriverSettingsAxis5 = {AXIS5_DRIVER_MODEL, AXIS5_DRIVER_MICROSTEPS, AXIS5_DRIVER_MICROSTEPS_GOTO, AXIS5_DRIVER_IHOLD, AXIS5_DRIVER_IRUN, AXIS5_DRIVER_IGOTO, AXIS5_DRIVER_INTPOL, AXIS5_DRIVER_DECAY, AXIS5_DRIVER_DECAY_GOTO, AXIS5_DRIVER_STATUS};
    #if defined(AXIS5_STEP_DIR_LEGACY)
      StepDirGeneric driver5(5, &DriverPinsAxis5, &DriverSettingsAxis5);
    #elif defined(AXIS5_STEP_DIR_TMC_SPI)
      StepDirTmcSPI driver5(5, &DriverPinsAxis5, &DriverSettingsAxis5);
    #elif defined(AXIS5_STEP_DIR_TMC_UART)
      StepDirTmcUART driver5(5, &DriverPinsAxis5, &DriverSettingsAxis5);
    #endif

    const StepDirPins StepDirPinsAxis5 = {AXIS5_STEP_PIN, AXIS5_STEP_STATE, AXIS5_DIR_PIN, AXIS5_ENABLE_PIN, AXIS5_ENABLE_STATE};
    StepDirMotor motor5(5, &StepDirPinsAxis5, ((StepDirDriver*)&driver5));
  #endif

  const AxisPins PinsAxis5 = {AXIS5_SENSE_LIMIT_MIN_PIN, AXIS5_SENSE_HOME_PIN, AXIS5_SENSE_LIMIT_MAX_PIN, {AXIS5_SENSE_HOME, AXIS5_SENSE_HOME_INIT, AXIS5_SENSE_HOME_DIST_LIMIT*1000.0F, AXIS5_SENSE_LIMIT_MIN, AXIS5_SENSE_LIMIT_MAX, AXIS5_SENSE_LIMIT_INIT}};
  const AxisSettings SettingsAxis5 = {AXIS5_STEPS_PER_MICRON, AXIS5_REVERSE, {AXIS5_LIMIT_MIN*1000.0F, AXIS5_LIMIT_MAX*1000.0F}, AXIS5_BACKLASH_RATE};
  Axis axis5(5, &PinsAxis5, &SettingsAxis5, AXIS_MEASURE_MICRONS);
#endif

#if AXIS6_DRIVER_MODEL != OFF
  #ifdef AXIS6_SERVO_PRESENT
    ServoControl servoControlAxis6;

    #if AXIS6_ENCODER == AB
      Quadrature encAxis6(AXIS6_ENCODER_A_PIN, AXIS6_ENCODER_B_PIN, 6);
    #elif AXIS6_ENCODER == AB_ESP32
      QuadratureEsp32 encAxis6(AXIS6_ENCODER_A_PIN, AXIS6_ENCODER_B_PIN, 6);
    #elif AXIS6_ENCODER == CW_CCW
      CwCcw encAxis6(AXIS6_ENCODER_A_PIN, AXIS6_ENCODER_B_PIN, 6);
    #elif AXIS6_ENCODER == PULSE_DIR
      PulseDir encAxis6(AXIS6_ENCODER_A_PIN, AXIS6_ENCODER_B_PIN, 6);
    #elif AXIS6_ENCODER == PULSE_ONLY
      PulseOnly encAxis6(AXIS6_ENCODER_A_PIN, &servoControlAxis6.directionHint, 6);
    #elif AXIS6_ENCODER == AS67_H69B_B
      As37h39bb encAxis6(AXIS6_ENCODER_A_PIN, AXIS6_ENCODER_B_PIN, 6);
    #elif AXIS6_ENCODER == SERIAL_BRIDGE
      SerialBridge encAxis6(6);
    #endif

    #if AXIS6_SERVO_FEEDBACK == FB_PID
      Pid pidAxis6(AXIS6_PID_P, AXIS6_PID_I, AXIS6_PID_D, AXIS6_PID_P_GOTO, AXIS6_PID_I_GOTO, AXIS6_PID_D_GOTO, AXIS6_PID_SENSITIVITY);
    #endif

    #if AXIS6_DRIVER_MODEL == SERVO_EE || AXIS6_DRIVER_MODEL == SERVO_PE
      const ServoDcPins ServoPinsAxis6 = {AXIS6_SERVO_PH1_PIN, AXIS6_SERVO_PH1_STATE, AXIS6_SERVO_PH2_PIN, AXIS6_SERVO_PH2_STATE, AXIS6_ENABLE_PIN, AXIS6_ENABLE_STATE, AXIS6_FAULT_PIN};
      const ServoDcSettings ServoSettingsAxis6 = {AXIS6_DRIVER_MODEL, AXIS6_DRIVER_STATUS, AXIS6_SERVO_VELOCITY_MAX, AXIS6_SERVO_ACCELERATION};
      ServoDc driver6(6, &ServoPinsAxis6, &ServoSettingsAxis6);
    #elif AXIS6_DRIVER_MODEL == SERVO_TMC2130_DC || AXIS6_DRIVER_MODEL == SERVO_TMC5160_DC
      const ServoDcTmcSpiPins ServoPinsAxis6 = {AXIS6_STEP_PIN, AXIS6_DIR_PIN, AXIS6_ENABLE_PIN, AXIS6_ENABLE_STATE, AXIS6_M0_PIN, AXIS6_M1_PIN, AXIS6_M2_PIN, AXIS6_M3_PIN, AXIS6_FAULT_PIN};
      const ServoDcTmcSettings ServoSettingsAxis6 = {AXIS6_DRIVER_MODEL, AXIS6_DRIVER_STATUS, AXIS6_SERVO_VELOCITY_MAX, AXIS6_SERVO_ACCELERATION, AXIS6_DRIVER_MICROSTEPS, AXIS6_DRIVER_IRUN};
      ServoTmc5160 driver6(6, &ServoPinsAxis6, &ServoSettingsAxis6);
    #elif AXIS6_DRIVER_MODEL == SERVO_TMC2209
      const ServoTmcPins ServoPinsAxis6 = {AXIS6_STEP_PIN, AXIS6_DIR_PIN, AXIS6_ENABLE_PIN, AXIS6_ENABLE_STATE, AXIS6_M0_PIN, AXIS6_M1_PIN, AXIS6_FAULT_PIN};
      const ServoTmcSettings ServoSettingsAxis6 = {AXIS6_DRIVER_MODEL, AXIS6_DRIVER_STATUS, AXIS6_SERVO_VELOCITY_MAX, AXIS6_SERVO_ACCELERATION, AXIS6_DRIVER_MICROSTEPS, AXIS6_DRIVER_IRUN, AXIS6_DRIVER_VELOCITY};
      ServoTmc2209 driver6(6, &ServoPinsAxis6, &ServoSettingsAxis6);
    #endif

    ServoMotor motor6(6, ((ServoDriver*)&driver6), &encAxis6, AXIS6_ENCODER_ORIGIN, AXIS6_ENCODER_REVERSE == ON, &pidAxis6, &servoControlAxis6, AXIS6_SYNC_THRESHOLD);
  #endif

  #ifdef AXIS6_STEP_DIR_PRESENT
    const StepDirDriverPins DriverPinsAxis6 = {AXIS6_M0_PIN, AXIS6_M1_PIN, AXIS6_M2_PIN, AXIS6_M2_ON_STATE, AXIS6_M3_PIN, AXIS6_DECAY_PIN, AXIS6_FAULT_PIN};
    const StepDirDriverSettings DriverSettingsAxis6 = {AXIS6_DRIVER_MODEL, AXIS6_DRIVER_MICROSTEPS, AXIS6_DRIVER_MICROSTEPS_GOTO, AXIS6_DRIVER_IHOLD, AXIS6_DRIVER_IRUN, AXIS6_DRIVER_IGOTO, AXIS6_DRIVER_INTPOL, AXIS6_DRIVER_DECAY, AXIS6_DRIVER_DECAY_GOTO, AXIS6_DRIVER_STATUS};
    #if defined(AXIS6_STEP_DIR_LEGACY)
      StepDirGeneric driver6(6, &DriverPinsAxis6, &DriverSettingsAxis6);
    #elif defined(AXIS6_STEP_DIR_TMC_SPI)
      StepDirTmcSPI driver6(6, &DriverPinsAxis6, &DriverSettingsAxis6);
    #elif defined(AXIS6_STEP_DIR_TMC_UART)
      StepDirTmcUART driver6(6, &DriverPinsAxis6, &DriverSettingsAxis6);
    #endif

    const StepDirPins StepDirPinsAxis6 = {AXIS6_STEP_PIN, AXIS6_STEP_STATE, AXIS6_DIR_PIN, AXIS6_ENABLE_PIN, AXIS6_ENABLE_STATE};
    StepDirMotor motor6(6, &StepDirPinsAxis6, ((StepDirDriver*)&driver6));
  #endif

  const AxisPins PinsAxis6 = {AXIS6_SENSE_LIMIT_MIN_PIN, AXIS6_SENSE_HOME_PIN, AXIS6_SENSE_LIMIT_MAX_PIN, {AXIS6_SENSE_HOME, AXIS6_SENSE_HOME_INIT, AXIS6_SENSE_HOME_DIST_LIMIT*1000.0F, AXIS6_SENSE_LIMIT_MIN, AXIS6_SENSE_LIMIT_MAX, AXIS6_SENSE_LIMIT_INIT}};
  const AxisSettings SettingsAxis6 = {AXIS6_STEPS_PER_MICRON, AXIS6_REVERSE, {AXIS6_LIMIT_MIN*1000.0F, AXIS6_LIMIT_MAX*1000.0F}, AXIS6_BACKLASH_RATE};
  Axis axis6(6, &PinsAxis6, &SettingsAxis6, AXIS_MEASURE_MICRONS);
#endif

#if AXIS7_DRIVER_MODEL != OFF
  #ifdef AXIS7_SERVO_PRESENT
    ServoControl servoControlAxis7;

    #if AXIS7_ENCODER == AB
      Quadrature encAxis7(AXIS7_ENCODER_A_PIN, AXIS7_ENCODER_B_PIN, 7);
    #elif AXIS7_ENCODER == AB_ESP32
      QuadratureEsp32 encAxis7(AXIS7_ENCODER_A_PIN, AXIS7_ENCODER_B_PIN, 7);
    #elif AXIS7_ENCODER == CW_CCW
      CwCcw encAxis7(AXIS7_ENCODER_A_PIN, AXIS7_ENCODER_B_PIN, 7);
    #elif AXIS7_ENCODER == PULSE_DIR
      PulseDir encAxis7(AXIS7_ENCODER_A_PIN, AXIS7_ENCODER_B_PIN, 7);
    #elif AXIS7_ENCODER == PULSE_ONLY
      PulseOnly encAxis7(AXIS7_ENCODER_A_PIN, &servoControlAxis7.directionHint, 7);
    #elif AXIS7_ENCODER == AS77_H79B_B
      As37h39bb encAxis7(AXIS7_ENCODER_A_PIN, AXIS7_ENCODER_B_PIN, 7);
    #elif AXIS7_ENCODER == SERIAL_BRIDGE
      SerialBridge encAxis7(7);
    #endif

    #if AXIS7_SERVO_FEEDBACK == FB_PID
      Pid pidAxis7(AXIS7_PID_P, AXIS7_PID_I, AXIS7_PID_D, AXIS7_PID_P_GOTO, AXIS7_PID_I_GOTO, AXIS7_PID_D_GOTO, AXIS7_PID_SENSITIVITY);
    #endif

    #if AXIS7_DRIVER_MODEL == SERVO_EE || AXIS7_DRIVER_MODEL == SERVO_PE
      const ServoDcPins ServoPinsAxis7 = {AXIS7_SERVO_PH1_PIN, AXIS7_SERVO_PH1_STATE, AXIS7_SERVO_PH2_PIN, AXIS7_SERVO_PH2_STATE, AXIS7_ENABLE_PIN, AXIS7_ENABLE_STATE, AXIS7_FAULT_PIN};
      const ServoDcSettings ServoSettingsAxis7 = {AXIS7_DRIVER_MODEL, AXIS7_DRIVER_STATUS, AXIS7_SERVO_VELOCITY_MAX, AXIS7_SERVO_ACCELERATION};
      ServoDc driver7(7, &ServoPinsAxis7, &ServoSettingsAxis7);
    #elif AXIS7_DRIVER_MODEL == SERVO_TMC2130_DC || AXIS7_DRIVER_MODEL == SERVO_TMC5160_DC
      const ServoDcTmcSpiPins ServoPinsAxis7 = {AXIS7_STEP_PIN, AXIS7_DIR_PIN, AXIS7_ENABLE_PIN, AXIS7_ENABLE_STATE, AXIS7_M0_PIN, AXIS7_M1_PIN, AXIS7_M2_PIN, AXIS7_M3_PIN, AXIS7_FAULT_PIN};
      const ServoDcTmcSettings ServoSettingsAxis7 = {AXIS7_DRIVER_MODEL, AXIS7_DRIVER_STATUS, AXIS7_SERVO_VELOCITY_MAX, AXIS7_SERVO_ACCELERATION, AXIS7_DRIVER_MICROSTEPS, AXIS7_DRIVER_IRUN};
      ServoDcTmcSPI driver7(7, &ServoPinsAxis7, &ServoSettingsAxis7);
    #elif AXIS7_DRIVER_MODEL == SERVO_TMC2209
      const ServoTmcPins ServoPinsAxis7 = {AXIS7_STEP_PIN, AXIS7_DIR_PIN, AXIS7_ENABLE_PIN, AXIS7_ENABLE_STATE, AXIS7_M0_PIN, AXIS7_M1_PIN, AXIS7_FAULT_PIN};
      const ServoTmcSettings ServoSettingsAxis7 = {AXIS7_DRIVER_MODEL, AXIS7_DRIVER_STATUS, AXIS7_SERVO_VELOCITY_MAX, AXIS7_SERVO_ACCELERATION, AXIS7_DRIVER_MICROSTEPS, AXIS7_DRIVER_IRUN, AXIS7_DRIVER_VELOCITY};
      ServoTmc2209 driver7(7, &ServoPinsAxis7, &ServoSettingsAxis7);
    #endif

    ServoMotor motor7(7, ((ServoDriver*)&driver7), &encAxis7, AXIS7_ENCODER_ORIGIN, AXIS7_ENCODER_REVERSE == ON, &pidAxis7, &servoControlAxis7, AXIS7_SYNC_THRESHOLD);
  #endif

  #ifdef AXIS7_STEP_DIR_PRESENT
    const StepDirDriverPins DriverPinsAxis7 = {AXIS7_M0_PIN, AXIS7_M1_PIN, AXIS7_M2_PIN, AXIS7_M2_ON_STATE, AXIS7_M3_PIN, AXIS7_DECAY_PIN, AXIS7_FAULT_PIN};
    const StepDirDriverSettings DriverSettingsAxis7 = {AXIS7_DRIVER_MODEL, AXIS7_DRIVER_MICROSTEPS, AXIS7_DRIVER_MICROSTEPS_GOTO, AXIS7_DRIVER_IHOLD, AXIS7_DRIVER_IRUN, AXIS7_DRIVER_IGOTO, AXIS7_DRIVER_INTPOL, AXIS7_DRIVER_DECAY, AXIS7_DRIVER_DECAY_GOTO, AXIS7_DRIVER_STATUS};
    #if defined(AXIS7_STEP_DIR_LEGACY)
      StepDirGeneric driver7(7, &DriverPinsAxis7, &DriverSettingsAxis7);
    #elif defined(AXIS7_STEP_DIR_TMC_SPI)
      StepDirTmcSPI driver7(7, &DriverPinsAxis7, &DriverSettingsAxis7);
    #elif defined(AXIS7_STEP_DIR_TMC_UART)
      StepDirTmcUART driver7(7, &DriverPinsAxis7, &DriverSettingsAxis7);
    #endif

    const StepDirPins StepDirPinsAxis7 = {AXIS7_STEP_PIN, AXIS7_STEP_STATE, AXIS7_DIR_PIN, AXIS7_ENABLE_PIN, AXIS7_ENABLE_STATE};
    StepDirMotor motor7(7, &StepDirPinsAxis7, ((StepDirDriver*)&driver7));
  #endif

  const AxisPins PinsAxis7 = {AXIS7_SENSE_LIMIT_MIN_PIN, AXIS7_SENSE_HOME_PIN, AXIS7_SENSE_LIMIT_MAX_PIN, {AXIS7_SENSE_HOME, AXIS7_SENSE_HOME_INIT, AXIS7_SENSE_HOME_DIST_LIMIT*1000.0F, AXIS7_SENSE_LIMIT_MIN, AXIS7_SENSE_LIMIT_MAX, AXIS7_SENSE_LIMIT_INIT}};
  const AxisSettings SettingsAxis7 = {AXIS7_STEPS_PER_MICRON, AXIS7_REVERSE, {AXIS7_LIMIT_MIN*1000.0F, AXIS7_LIMIT_MAX*1000.0F}, AXIS7_BACKLASH_RATE};
  Axis axis7(7, &PinsAxis7, &SettingsAxis7, AXIS_MEASURE_MICRONS);
#endif

#if AXIS8_DRIVER_MODEL != OFF
  #ifdef AXIS8_SERVO_PRESENT
    ServoControl servoControlAxis8;

    #if AXIS8_ENCODER == AB
      Quadrature encAxis8(AXIS8_ENCODER_A_PIN, AXIS8_ENCODER_B_PIN, 8);
    #elif AXIS8_ENCODER == AB_ESP32
      QuadratureEsp32 encAxis8(AXIS8_ENCODER_A_PIN, AXIS8_ENCODER_B_PIN, 8);
    #elif AXIS8_ENCODER == CW_CCW
      CwCcw encAxis8(AXIS8_ENCODER_A_PIN, AXIS8_ENCODER_B_PIN, 8);
    #elif AXIS8_ENCODER == PULSE_DIR
      PulseDir encAxis8(AXIS8_ENCODER_A_PIN, AXIS8_ENCODER_B_PIN, 8);
    #elif AXIS8_ENCODER == PULSE_ONLY
      PulseOnly encAxis8(AXIS8_ENCODER_A_PIN, &servoControlAxis8.directionHint, 8);
    #elif AXIS8_ENCODER == AS87_H89B_B
      As37h39bb encAxis8(AXIS8_ENCODER_A_PIN, AXIS8_ENCODER_B_PIN, 8);
    #elif AXIS8_ENCODER == SERIAL_BRIDGE
      SerialBridge encAxis8(8);
    #endif

    #if AXIS8_SERVO_FEEDBACK == FB_PID
      Pid pidAxis8(AXIS8_PID_P, AXIS8_PID_I, AXIS8_PID_D, AXIS8_PID_P_GOTO, AXIS8_PID_I_GOTO, AXIS8_PID_D_GOTO, AXIS8_PID_SENSITIVITY);
    #endif

    #if AXIS8_DRIVER_MODEL == SERVO_EE || AXIS8_DRIVER_MODEL == SERVO_PE
      const ServoDcPins ServoPinsAxis8 = {AXIS8_SERVO_PH1_PIN, AXIS8_SERVO_PH1_STATE, AXIS8_SERVO_PH2_PIN, AXIS8_SERVO_PH2_STATE, AXIS8_ENABLE_PIN, AXIS8_ENABLE_STATE, AXIS8_FAULT_PIN};
      const ServoDcSettings ServoSettingsAxis8 = {AXIS8_DRIVER_MODEL, AXIS8_DRIVER_STATUS, AXIS8_SERVO_VELOCITY_MAX, AXIS8_SERVO_ACCELERATION};
      ServoDc driver8(8, &ServoPinsAxis8, &ServoSettingsAxis8);
    #elif AXIS8_DRIVER_MODEL == SERVO_TMC2130_DC || AXIS8_DRIVER_MODEL == SERVO_TMC5160_DC
      const ServoDcTmcSpiPins ServoPinsAxis8 = {AXIS8_STEP_PIN, AXIS8_DIR_PIN, AXIS8_ENABLE_PIN, AXIS8_ENABLE_STATE, AXIS8_M0_PIN, AXIS8_M1_PIN, AXIS8_M2_PIN, AXIS8_M3_PIN, AXIS8_FAULT_PIN};
      const ServoDcTmcSettings ServoSettingsAxis8 = {AXIS8_DRIVER_MODEL, AXIS8_DRIVER_STATUS, AXIS8_SERVO_VELOCITY_MAX, AXIS8_SERVO_ACCELERATION, AXIS8_DRIVER_MICROSTEPS, AXIS8_DRIVER_IRUN};
      ServoDcTmcSPI driver8(8, &ServoPinsAxis8, &ServoSettingsAxis8);
    #elif AXIS8_DRIVER_MODEL == SERVO_TMC2209
      const ServoTmcPins ServoPinsAxis8 = {AXIS8_STEP_PIN, AXIS8_DIR_PIN, AXIS8_ENABLE_PIN, AXIS8_ENABLE_STATE, AXIS8_M0_PIN, AXIS8_M1_PIN, AXIS8_FAULT_PIN};
      const ServoTmcSettings ServoSettingsAxis8 = {AXIS8_DRIVER_MODEL, AXIS8_DRIVER_STATUS, AXIS8_SERVO_VELOCITY_MAX, AXIS8_SERVO_ACCELERATION, AXIS8_DRIVER_MICROSTEPS, AXIS8_DRIVER_IRUN, AXIS8_DRIVER_VELOCITY};
      ServoTmc2209 driver8(8, &ServoPinsAxis8, &ServoSettingsAxis8);
    #endif

    ServoMotor motor8(8, ((ServoDriver*)&driver8), &encAxis8, AXIS8_ENCODER_ORIGIN, AXIS8_ENCODER_REVERSE == ON, &pidAxis8, &servoControlAxis8, AXIS8_SYNC_THRESHOLD);
  #endif

  #ifdef AXIS8_STEP_DIR_PRESENT
    const StepDirDriverPins DriverPinsAxis8 = {AXIS8_M0_PIN, AXIS8_M1_PIN, AXIS8_M2_PIN, AXIS8_M2_ON_STATE, AXIS8_M3_PIN, AXIS8_DECAY_PIN, AXIS8_FAULT_PIN};
    const StepDirDriverSettings DriverSettingsAxis8 = {AXIS8_DRIVER_MODEL, AXIS8_DRIVER_MICROSTEPS, AXIS8_DRIVER_MICROSTEPS_GOTO, AXIS8_DRIVER_IHOLD, AXIS8_DRIVER_IRUN, AXIS8_DRIVER_IGOTO, AXIS8_DRIVER_INTPOL, AXIS8_DRIVER_DECAY, AXIS8_DRIVER_DECAY_GOTO, AXIS8_DRIVER_STATUS};
    #if defined(AXIS8_STEP_DIR_LEGACY)
      StepDirGeneric driver8(8, &DriverPinsAxis8, &DriverSettingsAxis8);
    #elif defined(AXIS8_STEP_DIR_TMC_SPI)
      StepDirTmcSPI driver8(8, &DriverPinsAxis8, &DriverSettingsAxis8);
    #elif defined(AXIS8_STEP_DIR_TMC_UART)
      StepDirTmcUART driver8(8, &DriverPinsAxis8, &DriverSettingsAxis8);
    #endif

    const StepDirPins StepDirPinsAxis8 = {AXIS8_STEP_PIN, AXIS8_STEP_STATE, AXIS8_DIR_PIN, AXIS8_ENABLE_PIN, AXIS8_ENABLE_STATE};
    StepDirMotor motor8(8, &StepDirPinsAxis8, ((StepDirDriver*)&driver8));
  #endif

  const AxisPins PinsAxis8 = {AXIS8_SENSE_LIMIT_MIN_PIN, AXIS8_SENSE_HOME_PIN, AXIS8_SENSE_LIMIT_MAX_PIN, {AXIS8_SENSE_HOME, AXIS8_SENSE_HOME_INIT, AXIS8_SENSE_HOME_DIST_LIMIT*1000.0F, AXIS8_SENSE_LIMIT_MIN, AXIS8_SENSE_LIMIT_MAX, AXIS8_SENSE_LIMIT_INIT}};
  const AxisSettings SettingsAxis8 = {AXIS8_STEPS_PER_MICRON, AXIS8_REVERSE, {AXIS8_LIMIT_MIN*1000.0F, AXIS8_LIMIT_MAX*1000.0F}, AXIS8_BACKLASH_RATE};
  Axis axis8(8, &PinsAxis8, &SettingsAxis8, AXIS_MEASURE_MICRONS);
#endif

#if AXIS9_DRIVER_MODEL != OFF
  #ifdef AXIS9_SERVO_PRESENT
    ServoControl servoControlAxis9;

    #if AXIS9_ENCODER == AB
      Quadrature encAxis9(AXIS9_ENCODER_A_PIN, AXIS9_ENCODER_B_PIN, 9);
    #elif AXIS9_ENCODER == AB_ESP32
      QuadratureEsp32 encAxis9(AXIS9_ENCODER_A_PIN, AXIS9_ENCODER_B_PIN, 9);
    #elif AXIS9_ENCODER == CW_CCW
      CwCcw encAxis9(AXIS9_ENCODER_A_PIN, AXIS9_ENCODER_B_PIN, 9);
    #elif AXIS9_ENCODER == PULSE_DIR
      PulseDir encAxis9(AXIS9_ENCODER_A_PIN, AXIS9_ENCODER_B_PIN, 9);
    #elif AXIS9_ENCODER == PULSE_ONLY
      PulseOnly encAxis9(AXIS9_ENCODER_A_PIN, &servoControlAxis9.directionHint, 9);
    #elif AXIS9_ENCODER == AS97_H99B_B
      As37h39bb encAxis9(AXIS9_ENCODER_A_PIN, AXIS9_ENCODER_B_PIN, 9);
    #elif AXIS9_ENCODER == SERIAL_BRIDGE
      SerialBridge encAxis9(9);
    #endif

    #if AXIS9_SERVO_FEEDBACK == FB_PID
      Pid pidAxis9(AXIS9_PID_P, AXIS9_PID_I, AXIS9_PID_D, AXIS9_PID_P_GOTO, AXIS9_PID_I_GOTO, AXIS9_PID_D_GOTO, AXIS9_PID_SENSITIVITY);
    #endif

    #if AXIS9_DRIVER_MODEL == SERVO_EE || AXIS9_DRIVER_MODEL == SERVO_PE
      const ServoDcPins ServoPinsAxis9 = {AXIS9_SERVO_PH1_PIN, AXIS9_SERVO_PH1_STATE, AXIS9_SERVO_PH2_PIN, AXIS9_SERVO_PH2_STATE, AXIS9_ENABLE_PIN, AXIS9_ENABLE_STATE, AXIS9_FAULT_PIN};
      const ServoDcSettings ServoSettingsAxis9 = {AXIS9_DRIVER_MODEL, AXIS9_DRIVER_STATUS, AXIS9_SERVO_VELOCITY_MAX, AXIS9_SERVO_ACCELERATION};
      ServoDc driver9(9, &ServoPinsAxis9, &ServoSettingsAxis9);
    #elif AXIS9_DRIVER_MODEL == SERVO_TMC2130_DC || AXIS9_DRIVER_MODEL == SERVO_TMC5160_DC
      const ServoDcTmcSpiPins ServoPinsAxis9 = {AXIS9_STEP_PIN, AXIS9_DIR_PIN, AXIS9_ENABLE_PIN, AXIS9_ENABLE_STATE, AXIS9_M0_PIN, AXIS9_M1_PIN, AXIS9_M2_PIN, AXIS9_M3_PIN, AXIS9_FAULT_PIN};
      const ServoDcTmcSettings ServoSettingsAxis9 = {AXIS9_DRIVER_MODEL, AXIS9_DRIVER_STATUS, AXIS9_SERVO_VELOCITY_MAX, AXIS9_SERVO_ACCELERATION, AXIS9_DRIVER_MICROSTEPS, AXIS9_DRIVER_IRUN};
      ServoDcTmcSPI driver9(9, &ServoPinsAxis9, &ServoSettingsAxis9);
    #elif AXIS9_DRIVER_MODEL == SERVO_TMC2209
      const ServoTmcPins ServoPinsAxis9 = {AXIS9_STEP_PIN, AXIS9_DIR_PIN, AXIS9_ENABLE_PIN, AXIS9_ENABLE_STATE, AXIS9_M0_PIN, AXIS9_M1_PIN, AXIS9_FAULT_PIN};
      const ServoTmcSettings ServoSettingsAxis9 = {AXIS9_DRIVER_MODEL, AXIS9_DRIVER_STATUS, AXIS9_SERVO_VELOCITY_MAX, AXIS9_SERVO_ACCELERATION, AXIS9_DRIVER_MICROSTEPS, AXIS9_DRIVER_IRUN, AXIS9_DRIVER_VELOCITY};
      ServoTmc2209 driver9(9, &ServoPinsAxis9, &ServoSettingsAxis9);
    #endif

    ServoMotor motor9(9, ((ServoDriver*)&driver9), &encAxis9, AXIS9_ENCODER_ORIGIN, AXIS9_ENCODER_REVERSE == ON, &pidAxis9, &servoControlAxis9, AXIS9_SYNC_THRESHOLD);
  #endif

  #ifdef AXIS9_STEP_DIR_PRESENT
    const StepDirDriverPins DriverPinsAxis9 = {AXIS9_M0_PIN, AXIS9_M1_PIN, AXIS9_M2_PIN, AXIS9_M2_ON_STATE, AXIS9_M3_PIN, AXIS9_DECAY_PIN, AXIS9_FAULT_PIN};
    const StepDirDriverSettings DriverSettingsAxis9 = {AXIS9_DRIVER_MODEL, AXIS9_DRIVER_MICROSTEPS, AXIS9_DRIVER_MICROSTEPS_GOTO, AXIS9_DRIVER_IHOLD, AXIS9_DRIVER_IRUN, AXIS9_DRIVER_IGOTO, AXIS9_DRIVER_INTPOL, AXIS9_DRIVER_DECAY, AXIS9_DRIVER_DECAY_GOTO, AXIS9_DRIVER_STATUS};
    #if defined(AXIS9_STEP_DIR_LEGACY)
      StepDirGeneric driver9(9, &DriverPinsAxis9, &DriverSettingsAxis9);
    #elif defined(AXIS9_STEP_DIR_TMC_SPI)
      StepDirTmcSPI driver9(9, &DriverPinsAxis9, &DriverSettingsAxis9);
    #elif defined(AXIS9_STEP_DIR_TMC_UART)
      StepDirTmcUART driver9(9, &DriverPinsAxis9, &DriverSettingsAxis9);
    #endif

    const StepDirPins StepDirPinsAxis9 = {AXIS9_STEP_PIN, AXIS9_STEP_STATE, AXIS9_DIR_PIN, AXIS9_ENABLE_PIN, AXIS9_ENABLE_STATE};
    StepDirMotor motor9(9, &StepDirPinsAxis9, ((StepDirDriver*)&driver9));
  #endif

  const AxisPins PinsAxis9 = {AXIS9_SENSE_LIMIT_MIN_PIN, AXIS9_SENSE_HOME_PIN, AXIS9_SENSE_LIMIT_MAX_PIN, {AXIS9_SENSE_HOME, AXIS9_SENSE_HOME_INIT, AXIS9_SENSE_HOME_DIST_LIMIT*1000.0F, AXIS9_SENSE_LIMIT_MIN, AXIS9_SENSE_LIMIT_MAX, AXIS9_SENSE_LIMIT_INIT}};
  const AxisSettings SettingsAxis9 = {AXIS9_STEPS_PER_MICRON, AXIS9_REVERSE, {AXIS9_LIMIT_MIN*1000.0F, AXIS9_LIMIT_MAX*1000.0F}, AXIS9_BACKLASH_RATE};
  Axis axis9(9, &PinsAxis9, &SettingsAxis9, AXIS_MEASURE_MICRONS);
#endif

#endif
