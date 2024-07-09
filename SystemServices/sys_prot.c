/**
 * @file        sys_prot.c
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
#include "sys_prot.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static cbuffer_t *note_cb_ptrs[] = { NULL, NULL };

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t sys_prot_reg_rx(sys_prot_note_id_t note, cbuffer_t *cb)
{
  // Assert input
  ASSERT(note < sizeof(note_cb_ptrs), SYS_PROT_ERROR);
  ASSERT(cb != NULL, SYS_PROT_ERROR);

  // Store circular buffer pointer
  note_cb_ptrs[note] = cb;

  return SYS_PROT_SUCCESS;
}

uint32_t sys_prot_send_msg(sys_prot_note_id_t src, sys_prot_note_id_t des, uint8_t *data, uint8_t size)
{
  // Assert input
  ASSERT(src < sizeof(note_cb_ptrs), SYS_PROT_ERROR);
  ASSERT(des < sizeof(note_cb_ptrs), SYS_PROT_ERROR);
  ASSERT(data != NULL, SYS_PROT_ERROR);
  ASSERT(note_cb_ptrs[des] != NULL, SYS_PROT_ERROR);

  // Check buffer size
  if (cb_space_count(note_cb_ptrs[des]) < sizeof(src) + size)
  {
    return SYS_PROT_BUFFULL;
  }

  // Write date
  cb_write(note_cb_ptrs[des], &src, sizeof(src));
  cb_write(note_cb_ptrs[des], data, size);

  return SYS_PROT_SUCCESS;
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
