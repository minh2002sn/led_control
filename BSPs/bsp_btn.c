/**
 * @file        bsp_btn.c
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

/* Includes ----------------------------------------------------------- */
#include "bsp_btn.h"
#include "common.h"
#include "drv_btn.h"
#include "main.h"
#include "sys_data_mng.h"
#include "sys_mng.h"
#include "sys_data_mng_msg_frame.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */
typedef struct
{
  GPIO_TypeDef *gpio_x;
  uint16_t      gpio_pin;
  uint32_t      active_state;
  drv_btn_t     btn;
} bsp_led_data_t;

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
static bsp_led_data_t bbtn_data[] = {
  { GPIOA, GPIO_PIN_0, 1 }
};

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
/**
 * @brief           Callback function of single click event
 */
static void bsp_btn_cb_func_single_click(drv_btn_t *btn);

/**
 * @brief           Callback function of double click event
 */
static void bsp_btn_cb_func_double_click(drv_btn_t *btn);

/**
 * @brief           Callback function of hold event
 */
static void bsp_btn_cb_func_hold(drv_btn_t *btn);

/**
 * @brief           Callback function of release event
 */
static void bsp_btn_cb_func_release(drv_btn_t *btn);

/* Function definitions ----------------------------------------------- */
uint32_t bsp_btn_init()
{
  uint32_t ret;

  // Initialize button GPIO pin, active state
  ret = drv_btn_init(&bbtn_data[0].btn, bbtn_data[0].gpio_x,
                     bbtn_data[0].gpio_pin, bbtn_data[0].active_state);
  ASSERT(ret == DRV_BTN_SUCCESS, BSP_BTN_ERROR);

  // Register callback function for each button events
  ret = drv_btn_reg_cb_func(bsp_btn_cb_func_single_click, bsp_btn_cb_func_double_click,
                            bsp_btn_cb_func_hold, bsp_btn_cb_func_release);
  ASSERT(ret == DRV_BTN_SUCCESS, BSP_BTN_ERROR);

  return BSP_BTN_SUCCESS;
}

uint32_t bsp_btn_loop()
{
  uint32_t ret;
  ret = drv_btn_handle(&bbtn_data[0].btn);
  ASSERT(ret == DRV_BTN_SUCCESS, BSP_BTN_ERROR);

  return BSP_BTN_SUCCESS;
}

uint32_t bsp_btn_exti_handle(uint16_t exti_line)
{
  uint32_t ret;
  ret = drv_btn_exti_handle(&bbtn_data[0].btn, exti_line);

  ASSERT(ret == DRV_BTN_SUCCESS, BSP_BTN_ERROR);

  return BSP_BTN_SUCCESS;
}

/* Private definitions ----------------------------------------------- */
void bsp_btn_cb_func_single_click(drv_btn_t *btn)
{
  sys_mng_topic_btn_msg_frame_t msg = { SYS_MNG_BTN_EVENT_SINGLE_CLICK };
  sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_BTN, (uint8_t *)&msg, sizeof(msg));
}

void bsp_btn_cb_func_double_click(drv_btn_t *btn)
{
  uint8_t msg = { SYS_MNG_BTN_EVENT_DOUBLE_CLICK };
  sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_BTN, (uint8_t *)&msg, sizeof(msg));
}

void bsp_btn_cb_func_hold(drv_btn_t *btn)
{
  uint8_t msg = { SYS_MNG_BTN_EVENT_HOLD };
  sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_BTN, (uint8_t *)&msg, sizeof(msg));
}

void bsp_btn_cb_func_release(drv_btn_t *btn)
{
  uint8_t msg = { SYS_MNG_BTN_EVENT_RELEASE };
  sys_data_mng_publish_topic(SYS_DATA_MNG_TOPIC_BTN, (uint8_t *)&msg, sizeof(msg));
}

/* End of file -------------------------------------------------------- */
