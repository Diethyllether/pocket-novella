#pragma once

#include "driver/gpio.h"

#define BTN1_PIN GPIO_NUM_1
#define BTN2_PIN GPIO_NUM_2
#define BTN3_PIN GPIO_NUM_3
#define BTN4_PIN GPIO_NUM_4

#define SDA_PIN GPIO_NUM_5
#define SCL_PIN GPIO_NUM_6

#define TFT_SCL GPIO_NUM_7
#define TFT_SDA GPIO_NUM_9
#define TFT_RES GPIO_NUM_8
#define TFT_DC GPIO_NUM_44

#define BMI_INT GPIO_NUM_43

#define BME_ADDR 0x76
#define BMI_ADDR 0x68

typedef struct pet_stats
{
    uint8_t life;
    uint8_t hunger;
    uint8_t happiness;
} pet_stats_t;

i2c_config_t conf = {
	.mode = I2C_MODE_MASTER,
	.sda_io_num = SDA_PIN,
	.scl_io_num = SCL_PIN,
	.sda_pullup_en = GPIO_PULLUP_ENABLE,
	.scl_pullup_en = GPIO_PULLUP_ENABLE,
	.master.clk_speed = 400000,
};