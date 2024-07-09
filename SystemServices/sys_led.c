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
#include "cbuffer.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */
#define SYS_LED_CBUFFER_SIZE (32) /* Size of circular buffer */

/* Private enumerate/structure ---------------------------------------- */
typedef enum
{
  SYS_LED_STATE_ALL_OFF,
  SYS_LED_STATE_ONLY_LED1_ON,
  SYS_LED_STATE_ONLY_LED2_ON,
  SYS_LED_STATE_ONLY_LED3_ON,
} sys_led_state_t;

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static sys_led_state_t led_state = SYS_LED_STATE_ALL_OFF;
static cbuffer_t       sys_led_msg_cb;
static uint8_t         sys_led_msg_buff[SYS_LED_CBUFFER_SIZE];

/* Private function prototypes ---------------------------------------- */
/**
 * @brief           Handle led control state machine
 *
 * @param[in]       event   sys_led_event_t received
 *
 * @return          none
 */
static void state_machine_handle(sys_mng_event_t event);

/* Function definitions ----------------------------------------------- */
uint32_t sys_led_init()
{
  uint32_t ret;
  // Init BSP LED
  ret = bsp_led_init();
  ASSERT(ret == BSP_LED_SUCCESS, SYS_LED_ERROR);

  // Init circular buffer
  ret = cb_init(&sys_led_msg_cb, sys_led_msg_buff, SYS_LED_CBUFFER_SIZE);
  ASSERT(ret == CB_SUCCESS, SYS_LED_ERROR);

  // Register receiving
  ret = sys_prot_reg_rx(SYS_PROT_NOTE_SYS_LED, &sys_led_msg_cb);
  ASSERT(ret == SYS_PROT_SUCCESS, SYS_LED_ERROR);

  return SYS_LED_SUCCESS;
}

uint32_t sys_led_loop()
{
  sys_mng_msg_t msg;

  // Read message from circular buffer
  if ((cb_data_count(&sys_led_msg_cb) / sizeof(sys_mng_msg_t)) >= 1)
  {
    cb_read(&sys_led_msg_cb, &msg, sizeof(msg));
    state_machine_handle(msg.event);
  }

  return SYS_LED_SUCCESS;
}

/* Private definitions ----------------------------------------------- */
static void state_machine_handle(sys_mng_event_t event)
{
  // Change state
  switch (led_state)
  {
  case SYS_LED_STATE_ALL_OFF:
    if (event.btn_event == SYS_MNG_BTN_EVENT_SINGLE_CLICK)
      led_state = SYS_LED_STATE_ONLY_LED1_ON;
    break;

  case SYS_LED_STATE_ONLY_LED1_ON:
    if (event.btn_event == SYS_MNG_BTN_EVENT_DOUBLE_CLICK)
      led_state = SYS_LED_STATE_ONLY_LED2_ON;
    else if (event.btn_event == SYS_MNG_BTN_EVENT_HOLD)
      led_state = SYS_LED_STATE_ALL_OFF;
    break;

  case SYS_LED_STATE_ONLY_LED2_ON:
    if (event.btn_event == SYS_MNG_BTN_EVENT_DOUBLE_CLICK)
      led_state = SYS_LED_STATE_ONLY_LED3_ON;
    else if (event.btn_event == SYS_MNG_BTN_EVENT_HOLD)
      led_state = SYS_LED_STATE_ALL_OFF;
    break;

  case SYS_LED_STATE_ONLY_LED3_ON:
    if (event.btn_event == SYS_MNG_BTN_EVENT_DOUBLE_CLICK)
      led_state = SYS_LED_STATE_ONLY_LED1_ON;
    else if (event.btn_event == SYS_MNG_BTN_EVENT_HOLD)
      led_state = SYS_LED_STATE_ALL_OFF;
    break;

  default:
    break;
  }

  // Moore State machine
  switch (led_state)
  {
  case SYS_LED_STATE_ALL_OFF:
    bsp_led_off(BSP_LED_0);
    bsp_led_off(BSP_LED_1);
    bsp_led_off(BSP_LED_2);
    break;

  case SYS_LED_STATE_ONLY_LED1_ON:
    bsp_led_on(BSP_LED_0);
    bsp_led_off(BSP_LED_1);
    bsp_led_off(BSP_LED_2);
    break;

  case SYS_LED_STATE_ONLY_LED2_ON:
    bsp_led_off(BSP_LED_0);
    bsp_led_on(BSP_LED_1);
    bsp_led_off(BSP_LED_2);
    break;

  case SYS_LED_STATE_ONLY_LED3_ON:
    bsp_led_off(BSP_LED_0);
    bsp_led_off(BSP_LED_1);
    bsp_led_on(BSP_LED_2);
    break;

  default:
    break;
  }
}

/* End of file -------------------------------------------------------- */
