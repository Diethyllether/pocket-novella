#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "esp_lcd_st7789.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_types.h"
#include "esp_err.h"
#include "bmi160.h"
#include "bmp280.h"
#include "aht.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "sprites.h"

#define BTN1_PIN GPIO_NUM_1
#define BTN2_PIN GPIO_NUM_2
#define BTN3_PIN GPIO_NUM_3

#define SDA_PIN GPIO_NUM_5
#define SCL_PIN GPIO_NUM_6

#define TFT_SCL GPIO_NUM_7
#define TFT_SDA GPIO_NUM_9
#define TFT_RES GPIO_NUM_8
#define TFT_DC GPIO_NUM_44
#define TFT_CS GPIO_NUM_43
#define LCD_HOST SPI2_HOST

#define BME_ADDR 0x77
#define AHT_ADDR 0x38
#define BMI_ADDR 0x68

typedef struct pet_stats
{
    uint8_t life;
    uint8_t hunger;
    uint8_t happiness;
} pet_stats_t;

static const char *TAG = "Tamagotchi";

void app_main(void)
{
    /*
    // --- BMI160 ---
    bmi160_t bmi160_dev;
    bmi160_conf_t bmi_conf = {
        .accRange = BMI160_ACC_RANGE_4G,
        .accOdr = BMI160_ACC_ODR_100HZ,
        .accMode = BMI160_PMU_ACC_NORMAL,
        .accAvg = BMI160_ACC_LP_AVG_4,
        .accUs = BMI160_ACC_US_OFF,

        .gyrRange = BMI160_GYR_RANGE_250DPS,
        .gyrOdr = BMI160_GYR_ODR_100HZ,
        .gyrMode = BMI160_PMU_GYR_NORMAL,
    };

    bmp280_t bme280_dev;
    bmp280_params_t bme280_conf;
    aht_t aht20_dev;

    ESP_ERROR_CHECK(bmi160_init(&bmi160_dev, BMI_ADDR, I2C_NUM_0, SDA_PIN, SCL_PIN));
    bmp280_init_default_params(&bme280_conf);
    ESP_ERROR_CHECK(bmp280_init_desc(&bme280_dev, BME_ADDR, I2C_NUM_0, SDA_PIN, SCL_PIN));
    ESP_ERROR_CHECK(bmp280_init(&bme280_dev, &bme280_conf));
    ESP_ERROR_CHECK(aht_init_desc(&aht20_dev, AHT_ADDR, I2C_NUM_0, SDA_PIN, SCL_PIN));
    ESP_ERROR_CHECK(aht_init(&aht20_dev));*/

    spi_bus_config_t buscfg = {
        .sclk_io_num = TFT_SCL,
        .mosi_io_num = TFT_SDA,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 240 * 280 * 2,
    };
    spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO);

    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_spi_config_t io_config = ST7789_PANEL_IO_SPI_CONFIG(TFT_CS, TFT_DC, NULL, NULL);
    io_config.lcd_cmd_bits = 8;
    io_config.lcd_param_bits = 8;
    esp_lcd_panel_handle_t panel_handle = NULL;
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = TFT_RES,
        .bits_per_pixel = 16,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
    };
    esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle);
    esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle);
    esp_lcd_panel_reset(panel_handle);
    esp_lcd_panel_invert_color(panel_handle, true);
    esp_lcd_panel_set_gap(panel_handle, 20, 0);
    esp_lcd_panel_init(panel_handle);
    esp_lcd_panel_swap_xy(panel_handle, 1);
    esp_lcd_panel_mirror(panel_handle, 1, 0);
    esp_lcd_panel_disp_on_off(panel_handle, true);
    esp_lcd_panel_draw_bitmap(panel_handle, 0, 0, 280, 240, &yoru_bin );
}