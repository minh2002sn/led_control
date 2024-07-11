/**
 * @file        sys_data_mng_msg_frame.h
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
#ifndef __SYS_DATA_MNG_MSG_FRAME_
#define __SYS_DATA_MNG_MSG_FRAME_

/* Includes ----------------------------------------------------------- */
#include "bsp_led.h"
#include <stdint.h>

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
// Type define enum sys_mng_btn_event_t that has sizeof() = 1
typedef uint8_t sys_mng_btn_event_t;
#define SYS_MNG_BTN_EVENT_SINGLE_CLICK ((sys_mng_btn_event_t)0x00)
#define SYS_MNG_BTN_EVENT_DOUBLE_CLICK ((sys_mng_btn_event_t)0x01)
#define SYS_MNG_BTN_EVENT_HOLD         ((sys_mng_btn_event_t)0x02)
#define SYS_MNG_BTN_EVENT_RELEASE      ((sys_mng_btn_event_t)0x03)

// Type define enum sys_mng_led_event_t that has sizeof() = 1
typedef uint8_t sys_mng_led_event_t;
#define SYS_MNG_LED_EVENT_ON          ((sys_mng_led_event_t)0x00)
#define SYS_MNG_LED_EVENT_OFF         ((sys_mng_led_event_t)0x01)
#define SYS_MNG_LED_EVENT_START_BLINK ((sys_mng_led_event_t)0x02)
#define SYS_MNG_LED_EVENT_STOP_BLINK  ((sys_mng_led_event_t)0x03)

// Message frame for topic button
typedef struct __attribute__((packed))
{
  sys_mng_btn_event_t event;
} sys_mng_topic_btn_msg_frame_t;

// Message frame for topic button
typedef struct __attribute__((packed))
{
  sys_mng_led_event_t event;
  bsp_led_t           led;
} sys_mng_topic_led_msg_frame_t;

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

#endif // __SYS_DATA_MNG_MSG_FRAME_

/* End of file -------------------------------------------------------- */
