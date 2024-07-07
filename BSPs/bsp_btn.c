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
#include "sys_btn.h"

/* Private defines ---------------------------------------------------- */
#define BTN_ACTIVE_STATE 1 /* Active state of buttons */

/* Private enumerate/structure ---------------------------------------- */
typedef struct
{
  GPIO_TypeDef *gpio_x;
  uint16_t gpio_pin;
  drv_btn_t btn;
} bsp_led_data_t;

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
static bsp_led_data_t btns_data[] =
{
  { GPIOA, GPIO_PIN_0 }
};

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */
void bsp_btn_cb_func_single_click(drv_btn_t *btn);
void bsp_btn_cb_func_double_click(drv_btn_t *btn);
void bsp_btn_cb_func_hold(drv_btn_t *btn);
void bsp_btn_cb_func_release(drv_btn_t *btn);

/* Function definitions ----------------------------------------------- */
uint32_t bsp_btn_init()
{
  uint32_t ret;
  ret = drv_btn_init(&btns_data[0].btn, btns_data[0].gpio_x,
                     btns_data[0].gpio_pin, BTN_ACTIVE_STATE);
  ASSERT(ret == DRV_BTN_SUCCESS, BSP_BTN_ERROR);

  ret = drv_btn_reg_cb_func(bsp_btn_cb_func_single_click, bsp_btn_cb_func_double_click,
                            bsp_btn_cb_func_hold, bsp_btn_cb_func_release);
  ASSERT(ret == DRV_BTN_SUCCESS, BSP_BTN_ERROR);

  return BSP_BTN_SUCCESS;
}

uint32_t bsp_btn_loop()
{
  uint32_t ret;
  ret = drv_btn_handle(&btns_data[0].btn);
  ASSERT(ret == DRV_BTN_SUCCESS, BSP_BTN_ERROR);

  return BSP_BTN_SUCCESS;
}

uint32_t bsp_btn_exti_handle(uint16_t exti_line)
{
  uint32_t ret;
  ret = drv_btn_exti_handle(&btns_data[0].btn, exti_line);

  ASSERT(ret == DRV_BTN_SUCCESS, BSP_BTN_ERROR);

  return BSP_BTN_SUCCESS;
}

/* Private definitions ----------------------------------------------- */
void bsp_btn_cb_func_single_click(drv_btn_t *btn)
{
  sys_btn_send_msg(0, SYS_BTN_EVENT_SINGLE_CLICK);
}

void bsp_btn_cb_func_double_click(drv_btn_t *btn)
{
  sys_btn_send_msg(0, SYS_BTN_EVENT_DOUBLE_CLICK);
}

void bsp_btn_cb_func_hold(drv_btn_t *btn)
{
  sys_btn_send_msg(0, SYS_BTN_EVENT_HOLD);
}

void bsp_btn_cb_func_release(drv_btn_t *btn)
{
  sys_btn_send_msg(0, SYS_BTN_EVENT_RELEASE);
}

/* End of file -------------------------------------------------------- */
