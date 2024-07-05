/**
 * @file        bsp_led.h
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
#ifndef __BSP_LED_
#define __BSP_LED_

/* Includes ----------------------------------------------------------- */
#include <stdint.h>
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

typedef enum
{
  BSP_LED_0,
  BSP_LED_1,
  BSP_LED_2
} bsp_led_t;

enum bsp_led_msg_enum
{
  BSP_LED_ERROR = -1,
  BSP_LED_SUCCESS
};

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Init LEDs
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t bsp_led_init();

/**
 * @brief           Initialize circular buffer
 *
 * @param[in]       led     bsp_led_t want to turn on
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t bsp_led_on(bsp_led_t led);

/**
 * @brief           Initialize circular buffer
 *
 * @param[in]       led     bsp_led_t want to turn off
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t bsp_led_off(bsp_led_t led);

/**
 * @brief           Initialize circular buffer
 *
 * @param[in]       led     bsp_led_t want to turn toggle
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t bsp_led_toggle(bsp_led_t led);

#endif // __BSP_LED_

/* End of file -------------------------------------------------------- */
