/**
 * @file        sys_led.h
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
#ifndef __SYS_LED_
#define __SYS_LED_

/* Includes ----------------------------------------------------------- */
#include <stdint.h>

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  SYS_LED_EVENT_ALL_OFF,
  SYS_LED_EVENT_ONLY_LED1_ON,
  SYS_LED_EVENT_ONLY_LED2_ON,
  SYS_LED_EVENT_ONLY_LED3_ON,
} sys_led_event_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Initialize system manager
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_led_init();

/**
 * @brief           System led loop() function
 */
void sys_led_loop();

/**
 * @brief           Send event to system manager
 *
 * @param[in]       event   sys_led_event_t want to send
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_led_send_event(sys_led_event_t event);

#endif // __SYS_LED_

/* End of file -------------------------------------------------------- */
