/**
 * @file        app.h
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
#ifndef __APP_
#define __APP_

/* Includes ----------------------------------------------------------- */
#include "sys_mng.h"
#include <stdint.h>

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Initialize application
 *
 * @return          none
 */
void app_init();

/**
 * @brief           Application loop() function
 *
 * @return          none
 */
void app_loop();

#endif // __APP_

/* End of file -------------------------------------------------------- */
