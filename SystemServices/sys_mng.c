/**
 * @file        sys_mng.c
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
#include "sys_mng.h"
#include "common.h"
#include "sys_data_mng.h"
#include "sys_data_mng_topic_define.h"
#include "sys_data_mng_msg_frame.h"
#include "sys_led.h"

/* Private defines ---------------------------------------------------- */
// Number of frame in topic button buffer
#define SYS_MNG_NUM_FRAME_TOPIC_BTN_BUFF (8)
// Number of frame in topic LED buffer
#define SYS_MNG_NUM_FRAME_TOPIC_LED_BUFF (8)

/* Private enumerate/structure ---------------------------------------- */

typedef enum
{
  SYS_MNG_STATE_ALL_OFF,
  SYS_MNG_STATE_ONLY_LED1_ON,
  SYS_MNG_STATE_ONLY_LED2_ON,
  SYS_MNG_STATE_ONLY_LED3_ON,
} sys_mng_state_t;

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static sys_mng_state_t smng_state = SYS_MNG_STATE_ALL_OFF;

/* Private function prototypes ---------------------------------------- */
static void sys_mng_topic_btn_cb_func(uint8_t *data, uint32_t size);

/* Function definitions ----------------------------------------------- */
uint32_t sys_mng_init()
{
  uint32_t ret;

  // Create system data manager's topic
  ret = sys_data_mng_create_topic(SYS_DATA_MNG_TOPIC_BTN,
                                  sizeof(sys_mng_topic_btn_msg_frame_t),
                                  SYS_MNG_NUM_FRAME_TOPIC_BTN_BUFF);
  ASSERT(ret == SYS_DATA_MNG_SUCCESS, SYS_MNG_ERROR);

  ret = sys_data_mng_create_topic(SYS_DATA_MNG_TOPIC_LED,
                                  sizeof(sys_mng_topic_led_msg_frame_t),
                                  SYS_MNG_NUM_FRAME_TOPIC_LED_BUFF);
  ASSERT(ret == SYS_DATA_MNG_SUCCESS, SYS_MNG_ERROR);

  // Subscribe for receiving data in topic button
  ret = sys_data_mng_subscribe_topic(SYS_DATA_MNG_TOPIC_BTN, sys_mng_topic_btn_cb_func);
  ASSERT(ret == SYS_DATA_MNG_SUCCESS, SYS_MNG_ERROR);

  return SYS_MNG_SUCCESS;
}

uint32_t sys_mng_loop()
{
  return SYS_MNG_SUCCESS;
}

/* Private definitions ----------------------------------------------- */
static void sys_mng_topic_btn_cb_func(uint8_t *data, uint32_t size)
{
  switch (smng_state)
  {
  case SYS_MNG_STATE_ALL_OFF:
    if ((sys_mng_btn_event_t)(*data) == SYS_MNG_BTN_EVENT_SINGLE_CLICK)
    {
      sys_mng_topic_led_msg_frame_t msg = { SYS_MNG_LED_EVENT_OFF, BSP_ALL_LED };
      sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_LED, (uint8_t *)&msg, sizeof(msg));
      msg.event = SYS_MNG_LED_EVENT_ON;
      msg.led   = BSP_LED_0;
      sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_LED, (uint8_t *)&msg, sizeof(msg));
      smng_state = SYS_MNG_STATE_ONLY_LED1_ON;
    }
    break;

  case SYS_MNG_STATE_ONLY_LED1_ON:
    if ((sys_mng_btn_event_t)(*data) == SYS_MNG_BTN_EVENT_DOUBLE_CLICK)
    {
      sys_mng_topic_led_msg_frame_t msg = { SYS_MNG_LED_EVENT_OFF, BSP_ALL_LED };
      sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_LED, (uint8_t *)&msg, sizeof(msg));
      msg.event = SYS_MNG_LED_EVENT_ON;
      msg.led   = BSP_LED_1;
      sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_LED, (uint8_t *)&msg, sizeof(msg));
      smng_state = SYS_MNG_STATE_ONLY_LED2_ON;
    }
    else if ((sys_mng_btn_event_t)(*data) == SYS_MNG_BTN_EVENT_HOLD)
    {
      smng_state = SYS_MNG_STATE_ALL_OFF;
      sys_mng_topic_led_msg_frame_t msg = { SYS_MNG_LED_EVENT_OFF, BSP_ALL_LED };
      sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_LED, (uint8_t *)&msg, sizeof(msg));
    }
    break;

  case SYS_MNG_STATE_ONLY_LED2_ON:
    if ((sys_mng_btn_event_t)(*data) == SYS_MNG_BTN_EVENT_DOUBLE_CLICK)
    {
      sys_mng_topic_led_msg_frame_t msg = { SYS_MNG_LED_EVENT_OFF, BSP_ALL_LED };
      sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_LED, (uint8_t *)&msg, sizeof(msg));
      msg.event = SYS_MNG_LED_EVENT_ON;
      msg.led   = BSP_LED_2;
      sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_LED, (uint8_t *)&msg, sizeof(msg));
      smng_state = SYS_MNG_STATE_ONLY_LED3_ON;
    }
    else if ((sys_mng_btn_event_t)(*data) == SYS_MNG_BTN_EVENT_HOLD)
    {
      smng_state = SYS_MNG_STATE_ALL_OFF;
      sys_mng_topic_led_msg_frame_t msg = { SYS_MNG_LED_EVENT_OFF, BSP_ALL_LED };
      sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_LED, (uint8_t *)&msg, sizeof(msg));
    }
    break;

  case SYS_MNG_STATE_ONLY_LED3_ON:
    if ((sys_mng_btn_event_t)(*data) == SYS_MNG_BTN_EVENT_DOUBLE_CLICK)
    {
      sys_mng_topic_led_msg_frame_t msg = { SYS_MNG_LED_EVENT_OFF, BSP_ALL_LED };
      sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_LED, (uint8_t *)&msg, sizeof(msg));
      msg.event = SYS_MNG_LED_EVENT_ON;
      msg.led   = BSP_LED_0;
      sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_LED, (uint8_t *)&msg, sizeof(msg));
      smng_state = SYS_MNG_STATE_ONLY_LED1_ON;
    }
    else if ((sys_mng_btn_event_t)(*data) == SYS_MNG_BTN_EVENT_HOLD)
    {
      smng_state = SYS_MNG_STATE_ALL_OFF;
      sys_mng_topic_led_msg_frame_t msg = { SYS_MNG_LED_EVENT_OFF, BSP_ALL_LED };
      sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_LED, (uint8_t *)&msg, sizeof(msg));
    }
    break;

  default:
    break;
  }
}

/* End of file -------------------------------------------------------- */
