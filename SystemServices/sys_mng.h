/**
 * @file        sys_mng.h
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
#ifndef __SYS_MNG_
#define __SYS_MNG_

/* Includes ----------------------------------------------------------- */
#include <stdint.h>

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Initialize system manager
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_mng_int();

/**
 * @brief           Send event to system manager
 *
 * @param[in]       event   Pointer to event data
 * @param[in]       size    Size of event data
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_mng_send_event(uint8_t *event, uint32_t size);

/**
 * @brief           System manager loop() function
 */
void sys_mng_loop();

#endif // __SYS_MNG_

/* End of file -------------------------------------------------------- */
