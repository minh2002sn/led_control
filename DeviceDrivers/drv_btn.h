/**
 * @file        drv_btn.h
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
#ifndef __DRV_BTN_
#define __DRV_BTN_

/* Includes ----------------------------------------------------------- */
#include "main.h"
#include <stdint.h>

/* Public defines ----------------------------------------------------- */
#define DRV_BTN_SUCCESS (0x00000000)
#define DRV_BTN_ERROR   (0xFFFFFFFF)

/* Public enumerate/structure ----------------------------------------- */

enum drv_btn_debounce_state_enum
{
  DRV_BTN_DEBOUNCE_STATE_IDLE,
  DRV_BTN_DEBOUNCE_STATE_DEBOUNCE
};

enum drv_btn_handle_state_enum
{
  DRV_BTN_HANDLE_STATE_IDLE,
  DRV_BTN_HANDLE_STATE_CHECK_ACTIVE,
  DRV_BTN_HANDLE_STATE_CHECK_NON_ACTIVE,
  DRV_BTN_HANDLE_STATE_HOLD,
  DRV_BTN_HANDLE_STATE_CHECK_RELEASE
};

typedef struct
{
  GPIO_TypeDef *gpio_x;
  uint16_t gpio_pin;
  uint32_t t_start_debounce;
  uint32_t t_start_change;
  uint32_t gpio_state;
  uint32_t active_state;
  uint32_t click_count;
  enum drv_btn_debounce_state_enum debounce_state;
  enum drv_btn_handle_state_enum handle_state;
} drv_btn_t;

typedef void (*drv_btn_cb_func_t)(drv_btn_t *);


/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Initialize button
 *
 * @param[in]       btn           Pointer to drv_btn_t structure
 * @param[in]       gpio_x        Pointer to GPIO_TypeDef structure
 *                                where x can be (A..K) to select the GPIO peripheral
 * @param[in]       btn           The port bit to be written
 *                                This parameter can be one of GPIO_PIN_x where x can be (0..15)
 * @param[in]       active_state  Active state of button (1 - HIGH, 0 - LOW)
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t drv_btn_init(drv_btn_t *btn, GPIO_TypeDef *gpio_x, uint16_t gpio_pin, uint32_t active_state);

/**
 * @brief           Register callback functions
 *
 * @param[in]       single_click_cb_func  Function pointer that point to single click event callback function
 * @param[in]       double_click_cb_func  Function pointer that point to double click event callback function
 * @param[in]       hold_cb_func          Function pointer that point to hold event callback function
 * @param[in]       release_cb_func       Function pointer that point to release event callback function
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t drv_btn_reg_cb_func(drv_btn_cb_func_t single_click_cb_func,
                             drv_btn_cb_func_t double_click_cb_func,
                             drv_btn_cb_func_t hold_cb_func,
                             drv_btn_cb_func_t release_cb_func);

/**
 * @brief           External interrupt function to handle button event
 *
 * @param[in]       btn         Pointer to drv_btn_t structure
 * @param[in]       exti_line   External interrupt line
 *
 * @attention       Call this function in external interrupt handling function
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t drv_btn_exti_handle(drv_btn_t *btn, uint16_t exti_line);

/**
 * @brief           Handle button in while(1) loop
 *
 * @param[in]       btn         Pointer to drv_btn_t structure
 *
 * @attention       Call this function in while(1) loop
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t drv_btn_handle(drv_btn_t *btn);

#endif // __DRV_BTN_

/* End of file -------------------------------------------------------- */
