/**
 * @file        sys_prot.h
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
#ifndef __SYS_PROT_
#define __SYS_PROT_

/* Includes ----------------------------------------------------------- */
#include "cbuffer.h"
#include <stdint.h>

/* Public defines ----------------------------------------------------- */
#define SYS_PROT_SUCCESS (0x00000000)
#define SYS_PROT_ERROR   (0xFFFFFFFF)
#define SYS_PROT_BUFFULL (0xFFFFFFFE) /* Buffer full */

/* Public enumerate/structure ----------------------------------------- */
// Type define enum sys_btn_id_t that has sizeof() = 1
typedef uint8_t sys_prot_note_id_t;
#define SYS_PROT_NOTE_SYS_MNG ((sys_prot_note_id_t)0x00)
#define SYS_PROT_NOTE_SYS_BTN ((sys_prot_note_id_t)0x01)
#define SYS_PROT_NOTE_SYS_LED ((sys_prot_note_id_t)0x02)
#define SYS_PROT_NOTE_BSP_BTN ((sys_prot_note_id_t)0x03)

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Register receiving message
 *
 * @param[in]       note    Size of buffer
 * @param[in]       cb      Pointer to a cbuffer_t structure
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_prot_reg_rx(sys_prot_note_id_t note, cbuffer_t *cb);

/**
 * @brief           Send a message to des
 *
 * @param[in]       src     Source ID
 * @param[in]       des     Destination ID
 * @param[in]       data    Pointer to data buffer
 * @param[in]       size    Size of data buffer
 *
 * @note            Message structure is {src_id - 1byte, data}
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t
sys_prot_send_msg(sys_prot_note_id_t src, sys_prot_note_id_t des, uint8_t *data, uint8_t size);

#endif // __SYS_PROT_

/* End of file -------------------------------------------------------- */
