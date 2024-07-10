/**
 * @file        sys_btn.c
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
#include "sys_btn.h"
#include "bsp_btn.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t sys_btn_init()
{
  uint32_t ret;

  // Init bsp button
  ret = bsp_btn_init();
  ASSERT(ret == BSP_BTN_SUCCESS, SYS_BTN_ERROR);

  return SYS_BTN_SUCCESS;
}

uint32_t sys_btn_loop()
{
  // BSP loop function
  bsp_btn_loop();

  return SYS_BTN_SUCCESS;
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
