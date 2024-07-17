/**
 * @file        drv_btn.c
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
#include "drv_btn.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */
#define DEBOUNCING_TIME      50   /* Debouncing time in ms */
#define ACTIVE_THRESHOLD     500  /* Active threshold time in ms */
#define NON_ACTIVE_THRESHOLD 300  /* Non-active threshold time in ms */
#define HOLD_THRESHOLD       3000 /* Holding threshold time in ms */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

static drv_btn_cb_func_t drv_btn_cb_func_single_click = NULL;
static drv_btn_cb_func_t drv_btn_cb_func_double_click = NULL;
static drv_btn_cb_func_t drv_btn_cb_func_hold         = NULL;
static drv_btn_cb_func_t drv_btn_cb_func_release      = NULL;

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t drv_btn_init(drv_btn_t *btn, GPIO_TypeDef *gpio_x, uint16_t gpio_pin, uint32_t active_state)
{
  // Assert input
  ASSERT(btn != NULL, DRV_BTN_ERROR);
  ASSERT(gpio_x != NULL, DRV_BTN_ERROR);
  ASSERT((gpio_pin >= 0) && (gpio_pin <= 15), DRV_BTN_ERROR);
  ASSERT((active_state == 0) || (active_state == 1), DRV_BTN_ERROR);

  // Init button
  btn->gpio_x           = gpio_x;
  btn->gpio_pin         = gpio_pin;
  btn->t_start_debounce = 0;
  btn->t_start_change   = 0;
  btn->gpio_state       = !active_state;
  btn->active_state     = active_state;
  btn->click_count      = 0;
  btn->debounce_state   = DRV_BTN_DEBOUNCE_STATE_IDLE;
  btn->handle_state     = DRV_BTN_HANDLE_STATE_IDLE;

  return DRV_BTN_SUCCESS;
}

uint32_t drv_btn_reg_cb_func(drv_btn_cb_func_t single_click_cb_func,
                             drv_btn_cb_func_t double_click_cb_func,
                             drv_btn_cb_func_t hold_cb_func,
                             drv_btn_cb_func_t release_cb_func)
{
  drv_btn_cb_func_single_click = single_click_cb_func;
  drv_btn_cb_func_double_click = double_click_cb_func;
  drv_btn_cb_func_hold         = hold_cb_func;
  drv_btn_cb_func_release      = release_cb_func;

  return DRV_BTN_SUCCESS;
}

uint32_t drv_btn_exti_handle(drv_btn_t *btn, uint16_t exti_line)
{
  // Assert input
  ASSERT(btn != NULL, DRV_BTN_ERROR);
  ASSERT((exti_line >= 0) && (exti_line <= 15), DRV_BTN_ERROR);

  // Check external interrupt line
  if ((exti_line == btn->gpio_pin) && (btn->debounce_state == DRV_BTN_DEBOUNCE_STATE_IDLE))
  {
    btn->debounce_state   = DRV_BTN_DEBOUNCE_STATE_DEBOUNCE;
    btn->t_start_debounce = HAL_GetTick();
  }

  return DRV_BTN_SUCCESS;
}

uint32_t drv_btn_handle(drv_btn_t *btn)
{
  // Assert input
  ASSERT(btn != NULL, DRV_BTN_ERROR);

  // Debounce
  if (btn->debounce_state == DRV_BTN_DEBOUNCE_STATE_DEBOUNCE)
  {
    if (HAL_GetTick() - btn->t_start_debounce >= DEBOUNCING_TIME)
    {
      uint32_t curr_gpio_state = HAL_GPIO_ReadPin(btn->gpio_x, btn->gpio_pin);
      if (curr_gpio_state != btn->gpio_state)
      {
        btn->gpio_state = curr_gpio_state;
      }
      btn->debounce_state = DRV_BTN_DEBOUNCE_STATE_IDLE;
    }
  }

  // Handle
  switch (btn->handle_state)
  {
  case DRV_BTN_HANDLE_STATE_IDLE:
    // Check changing state condition
    if (btn->gpio_state == btn->active_state)
    {
      btn->handle_state   = DRV_BTN_HANDLE_STATE_CHECK_ACTIVE;
      btn->t_start_change = HAL_GetTick();
    }
    break;

  case DRV_BTN_HANDLE_STATE_CHECK_ACTIVE:
  {
    // Get current tick
    uint32_t curr_tick = HAL_GetTick();
    // Check changing state condition
    if (btn->gpio_state == !btn->active_state)
    {
      if (curr_tick - btn->t_start_change < ACTIVE_THRESHOLD)
      {
        btn->handle_state   = DRV_BTN_HANDLE_STATE_CHECK_NON_ACTIVE;
        btn->t_start_change = curr_tick;
      }
      else
        btn->handle_state = DRV_BTN_HANDLE_STATE_IDLE;
    }
    else if ((btn->gpio_state == btn->active_state) &&
             (curr_tick - btn->t_start_change >= HOLD_THRESHOLD))
    {
      btn->handle_state = DRV_BTN_HANDLE_STATE_HOLD;
      btn->click_count  = 0;
      CALLBACK(drv_btn_cb_func_hold, btn);
    }
    break;
  }

  case DRV_BTN_HANDLE_STATE_CHECK_NON_ACTIVE:
  {
    uint32_t curr_tick = HAL_GetTick();
    // Check next button gpio state is active or non active
    if ((btn->gpio_state == !btn->active_state) &&
        (curr_tick - btn->t_start_change >= NON_ACTIVE_THRESHOLD))
    {
      // Update next handling state
      btn->handle_state = DRV_BTN_HANDLE_STATE_IDLE;
      // Check single click or double click
      if (btn->click_count == 0)
        CALLBACK(drv_btn_cb_func_single_click, btn);
      else if (btn->click_count == 1)
      {
        btn->click_count = 0;
        CALLBACK(drv_btn_cb_func_double_click, btn);
      }
    }
    else if (btn->gpio_state == btn->active_state)
    {
      // Update next handling state
      btn->handle_state = DRV_BTN_HANDLE_STATE_CHECK_ACTIVE;
      // Check time
      if (curr_tick - btn->t_start_change < NON_ACTIVE_THRESHOLD)
      {
        // Increase click counter
        if (btn->click_count < 1)
          btn->click_count++;
      }
      else if (curr_tick - btn->t_start_change == NON_ACTIVE_THRESHOLD)
      {
        // Check single click or double click
        if (btn->click_count == 0)
          CALLBACK(drv_btn_cb_func_single_click, btn);
        else if (btn->click_count == 1)
        {
          btn->click_count = 0;
          CALLBACK(drv_btn_cb_func_double_click, btn);
        }
      }
      // Update changing time
      btn->t_start_change = curr_tick;
    }

    break;
  }

  case DRV_BTN_HANDLE_STATE_HOLD:
    if (btn->gpio_state == !btn->active_state)
    {
      btn->handle_state   = DRV_BTN_HANDLE_STATE_CHECK_RELEASE;
      btn->t_start_change = HAL_GetTick();
    }
    break;

  case DRV_BTN_HANDLE_STATE_CHECK_RELEASE:
  {
    // Get current tick
    uint32_t curr_tick = HAL_GetTick();
    // Check changing state condition
    if ((btn->gpio_state == !btn->active_state) && (curr_tick - btn->t_start_change >= 300))
    {
      btn->handle_state = DRV_BTN_HANDLE_STATE_IDLE;
      CALLBACK(drv_btn_cb_func_release, btn);
    }
    else if (btn->gpio_state == btn->active_state)
    {
      btn->handle_state   = DRV_BTN_HANDLE_STATE_CHECK_ACTIVE;
      btn->t_start_change = curr_tick;
      if (curr_tick - btn->t_start_change == 300)
        CALLBACK(drv_btn_cb_func_release, btn);
    }
    break;
  }
  }

  return DRV_BTN_SUCCESS;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
