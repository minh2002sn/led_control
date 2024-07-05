/**
 * @file        bsp_led.c
 * @copyright
 * @license
 * @version     0.0.0
 * @date
 * @author      Minh Phung Nhat
 *              Hung Pham Duc
 *              Khoi Nguyen Thanh
 * @brief       none
 *
 * @note        none
 *
 * @example     none
 *
 */
/* Define to prevent recursive inclusion ------------------------------ */
#include "bsp_led.h"
#include "main.h"
#include <stdint.h>

/* Private defines ---------------------------------------------------- */

#define ON_STATE  1
#define OFF_STATE 0

/* Private enumerate/structure ---------------------------------------- */
typedef struct
{
  GPIO_TypeDef *gpio_x;
  uint16_t gpio_pin;
} bsp_led_data_t;

static bsp_led_data_t leds_data[] = {
  { GPIOD, GPIO_PIN_12 },
  { GPIOD, GPIO_PIN_13 },
  { GPIOD, GPIO_PIN_14 }
};

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t bsp_led_on(bsp_led_t led)
{
  HAL_GPIO_WritePin(leds_data[led].gpio_x, leds_data[led].gpio_pin, ON_STATE);
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
