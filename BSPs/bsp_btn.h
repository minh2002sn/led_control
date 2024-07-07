/**
 * @file        bsp_btn.h
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
#ifndef __BSP_BTN_
#define __BSP_BTN_

/* Includes ----------------------------------------------------------- */
#include <stdint.h>

/* Public defines ----------------------------------------------------- */
#define BSP_BTN_SUCCESS (0x00000000)
#define BSP_BTN_ERROR   (0xFFFFFFFF)

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Init buttons
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t bsp_btn_init();

/**
 * @brief           Button handling function in while(1) loop
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t bsp_btn_loop();

/**
 * @brief           External interrupt function to handle button event
 *
 * @param[in]       exti_line   External interrupt line
 *
 * @attention       Call this function in external interrupt handling function (in bsp_exti)
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t bsp_btn_exti_handle(uint16_t exti_line);

#endif // __BSP_BTN_

/* End of file -------------------------------------------------------- */
