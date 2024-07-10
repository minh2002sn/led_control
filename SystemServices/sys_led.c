/**
 * @file        sys_led.c
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
#include "sys_led.h"
#include "bsp_led.h"
#include "common.h"
#include "sys_data_mng.h"
#include "sys_mng.h"
#include "sys_data_mng_msg_frame.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
static void sys_led_topic_led_cb_func(uint8_t *data, uint32_t size);

/* Function definitions ----------------------------------------------- */
uint32_t sys_led_init()
{
  uint32_t ret;
  // Init BSP LED
  ret = bsp_led_init();
  ASSERT(ret == BSP_LED_SUCCESS, SYS_LED_ERROR);

  // Subscribe for receiving data from topic LED
  ret = sys_data_mng_subscribe_topic(SYS_DATA_MNG_TOPIC_LED, sys_led_topic_led_cb_func);
  ASSERT(ret == SYS_DATA_MNG_SUCCESS, SYS_LED_ERROR);

  return SYS_LED_SUCCESS;
}

uint32_t sys_led_loop()
{
  return SYS_LED_SUCCESS;
}

/* Private definitions ----------------------------------------------- */
static void sys_led_topic_led_cb_func(uint8_t *data, uint32_t size)
{
  // Change state
  sys_mng_topic_led_msg_frame_t *msg = (sys_mng_topic_led_msg_frame_t *)data;
  // sys_mng_led_event_t           event =
  // (sys_mng_led_event_t)((sys_mng_topic_led_msg_frame_t *)data)->event;
  // bsp_led_t led = (bsp_led_t)(((sys_mng_topic_led_msg_frame_t *)data)->led);
  // sys_mng_led_event_t event = (sys_mng_event_t)msg->event;

  // Process data
  if (msg->event == SYS_MNG_LED_EVENT_ON)
  {
    if (msg->led == BSP_ALL_LED)
    {
      bsp_led_on(BSP_LED_0);
      bsp_led_on(BSP_LED_1);
      bsp_led_on(BSP_LED_2);
    }
    else
    {
      bsp_led_on((bsp_led_t)(((sys_mng_topic_led_msg_frame_t *)data)->led));
    }
  }
  else if (msg->event == SYS_MNG_LED_EVENT_OFF)
  {
    if (msg->led == BSP_ALL_LED)
    {
      bsp_led_off(BSP_LED_0);
      bsp_led_off(BSP_LED_1);
      bsp_led_off(BSP_LED_2);
    }
    else
    {
      bsp_led_off((bsp_led_t)(((sys_mng_topic_led_msg_frame_t *)data)->led));
    }
  }
}

/* End of file -------------------------------------------------------- */
