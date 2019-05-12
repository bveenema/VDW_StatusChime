#ifndef PINS_H
#define PINS_H

// Photon Pins
// #define SDA D0
// #define SCL D1
#define CHIME_VOLUME_PIN D2
#define BLUE_INPUT_STEP_PIN D3
#define BLUE_INPUT_DIR_PIN D4
#define RED_INPUT_DIR_PIN D5
#define RED_INPUT_STEP_PIN D6
#define I2C_RESET_PIN D7

#define THERM_RED_PIN A0
#define THERM_BLUE_PIN A1
#define PRESS_SNS_PIN A2
// #define SCK A3
// #define MISO A4
// #define MOSI A5
#define PAIL_SNS_PIN A6
#define BATTERY_VOLTAGE_PIN A7
#define POWER_PIN RX
#define IO_INT_PIN TX

// I/O Expander 1 Pins
#define IO1_IO3_INT GPA0
#define IO1_IO2_INT GPA1
#define IO1_TRANSDUCER_BLUE GPA2
#define IO1_CAM_BLUE_INT GPA3
#define IO1_LIQUID_SNS_RED GPA4
#define IO1_RED_HLFB GPA5
#define IO1_BLUE_SOLENOID_4 GPA6
#define IO1_RED_SOLENOID_3 GPA7

#define IO1_BLUE_HLFB GPB0
#define IO1_RADIO_IN GPB1
#define IO1_USER_REMOTE GPB2
#define IO1_LIQUID_SNS_BLUE GPB3
#define IO1_CAM_RED_INT GPB4
#define IO1_RADIO_SS GPB5
#define IO1_PRESENCE_INT GPB6
#define IO1_USER_BUTTON GPB7

// I/O Expander 2 Pins
#define IO2_POWER_LED_RED GPA0
#define IO2_POWER_LED_GREEN GPA1
#define IO2_POWER_LED_BLUE GPA2
#define IO2_LED_RIGHT_BLUE GPA3
#define IO2_LED_RIGHT_GREEN GPA4
#define IO2_LED_RIGHT_RED GPA5
#define IO2_PUMP_EN GPA6
#define IO2_TRANSDUCER_RED GPA7

#define IO2_LED_LEFT_BLUE GPB0
#define IO2_LED_LEFT_GREEN GPB1
#define IO2_LED_LEFT_RED GPB2
#define IO2_USER_LED_BLUE_BACKUP GPB3
#define IO2_USER_LED_GREEN_BACKUP GPB4
#define IO2_USER_LED_RED_BACKUP GPB5
#define IO2_BLUE_ENABLE GPB6
#define IO2_RED_ENABLE GPB7

// I/O Expander 3 Pins
#define IO3_IOEXP3_10 GPA0
#define IO3_IOEXP3_9 GPA1
#define IO3_IOEXP3_8 GPA2
#define IO3_IOEXP3_7 GPA3
#define IO3_IOEXP3_6 GPA4
#define IO3_IOEXP3_5 GPA5
#define IO3_IOEXP3_4 GPA6
#define IO3_IOEXP3_3 GPA7

#define IO3_ROTARY_4 GPB0
#define IO3_ROTARY_3 GPB1
#define IO3_ROTARY_2 GPB2
#define IO3_ROTARY_1 GPB3
#define IO3_IOEXP2_6 GPB4
#define IO3_IOEXP2_5 GPB5
#define IO3_IOEXP2_4 GPB6
#define IO3_IOEXP2_3 GPB7

// Analog Expander Pins
#define ADC_CH0 0
#define ADC_CH1 1
#define ADC_CH2 2
#define ADC_CH3 3
#define ADC_CH4 4
#define ADC_CH5 5
#define ADC_BLUE_TRANSDUCER 6
#define ADC_RED_TRANSDUCER 7


#endif
