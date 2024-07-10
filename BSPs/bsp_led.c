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
#include "common.h"
#include "main.h"
#include <stdint.h>

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */
typedef struct
{
  GPIO_TypeDef *gpio_x;
  uint16_t      gpio_pin;
  uint32_t      active_state;
} bsp_led_data_t;

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static bsp_led_data_t bled_data[] = {
  { GPIOD, GPIO_PIN_12, 1 },
  { GPIOD, GPIO_PIN_13, 1 },
  { GPIOD, GPIO_PIN_14, 1 }
};

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t bsp_led_init()
{
  return BSP_LED_SUCCESS;
}

uint32_t bsp_led_on(bsp_led_t led)
{
  // Check input
  ASSERT((led >= 0) && (led <= (sizeof(bled_data) / sizeof(bsp_led_data_t))), BSP_LED_ERROR);

  HAL_GPIO_WritePin(bled_data[led].gpio_x, bled_data[led].gpio_pin,
                    bled_data[led].active_state);
  return BSP_LED_SUCCESS;
}

uint32_t bsp_led_off(bsp_led_t led)
{
  // Check input
  ASSERT((led >= 0) && (led <= (sizeof(bled_data) / sizeof(bsp_led_data_t))), BSP_LED_ERROR);

  HAL_GPIO_WritePin(bled_data[led].gpio_x, bled_data[led].gpio_pin,
                    !bled_data[led].active_state);
  return BSP_LED_SUCCESS;
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
