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
#include "sys_prot.h"
#include <stdint.h>

/* Public defines ----------------------------------------------------- */
#define SYS_MNG_SUCCESS (0x00000000)
#define SYS_MNG_ERROR   (0xFFFFFFFF)
#define SYS_MNG_BUFFULL (0xFFFFFFFE) /* Buffer full */

/* Public enumerate/structure ----------------------------------------- */
// Type define enum sys_mng_btn_event_t that has sizeof() = 1
typedef uint8_t sys_mng_btn_event_t;
#define SYS_MNG_BTN_EVENT_SINGLE_CLICK ((sys_mng_btn_event_t)0x00)
#define SYS_MNG_BTN_EVENT_DOUBLE_CLICK ((sys_mng_btn_event_t)0x01)
#define SYS_MNG_BTN_EVENT_HOLD         ((sys_mng_btn_event_t)0x02)
#define SYS_MNG_BTN_EVENT_RELEASE      ((sys_mng_btn_event_t)0x03)

typedef union
{
  sys_mng_btn_event_t btn_event;
} sys_mng_event_t;

typedef struct
{
  sys_prot_note_id_t src_id;
  sys_mng_event_t    event;
} sys_mng_msg_t;


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
uint32_t sys_mng_init();

/**
 * @brief           System manager loop() function
 */
uint32_t sys_mng_loop();

#endif // __SYS_MNG_

/* End of file -------------------------------------------------------- */
