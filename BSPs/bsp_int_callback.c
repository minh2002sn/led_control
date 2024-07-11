/**
 * @file        bsp_int_callback.c
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
#include "bsp_int_callback.h"
#include "bsp_btn.h"
#include "bsp_led.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */

/* Private definitions ----------------------------------------------- */

/* Weak definitions ----------------------------------------------- */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  bsp_btn_exti_handle(GPIO_Pin);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  bsp_led_int_handle(htim);
}


/* End of file -------------------------------------------------------- */
