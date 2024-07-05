/**
 * @file        sys_mng.c
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
#include "sys_mng.h"

/* Private defines ---------------------------------------------------- */
#define SYS_MNG_CBUFFER_SIZE (16) /* Size of circular buffer */

/* Private enumerate/structure ---------------------------------------- */
typedef enum
{
  SYS_MNG_STATE_ALL_OFF,
  SYS_MNG_STATE_ONLY_LED1_ON,
  SYS_MNG_STATE_ONLY_LED2_ON,
  SYS_MNG_STATE_ONLY_LED3_ON
} sys_mng_state_t;

static sys_mng_state_t state = 0;

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
