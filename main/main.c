#include <stdio.h>
#include "config.h"
#include "lv_conf.h"
#include "lvgl.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"

static const char *TAG = "Tamagotchi";

void app_main(void)
{
    i2c_param_config(I2C_NUM_0, &conf);
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
    esp_err_t spi_bus_initialize()
}
