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
#include "cbuffer.h"
#include "common.h"
#include "sys_led.h"

/* Private defines ---------------------------------------------------- */
#define SYS_MNG_CBUFFER_SIZE (32) /* Size of circular buffer */

/* Private enumerate/structure ---------------------------------------- */
typedef enum
{
  SYS_MNG_STATE_IDLE
} sys_mng_state_t;

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static sys_mng_state_t mng_state = SYS_MNG_STATE_IDLE;
static cbuffer_t       sys_mng_msg_from_btn_cb;
static uint8_t         sys_mng_msg_from_btn_buff[SYS_MNG_CBUFFER_SIZE];

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t sys_mng_init()
{
  uint32_t ret;

  // Init circular buffer
  ret = cb_init(&sys_mng_msg_from_btn_cb, sys_mng_msg_from_btn_buff, SYS_MNG_CBUFFER_SIZE);
  ASSERT(ret == CB_SUCCESS, SYS_MNG_ERROR);

  // Register receiving
  ret = sys_prot_reg_rx(SYS_PROT_NOTE_SYS_MNG, &sys_mng_msg_from_btn_cb);
  ASSERT(ret == SYS_PROT_SUCCESS, SYS_MNG_ERROR);

  return SYS_MNG_SUCCESS;
}

uint32_t sys_mng_loop()
{
  sys_mng_msg_t msg;

  // Read message from circular buffer
  if ((cb_data_count(&sys_mng_msg_from_btn_cb) / sizeof(sys_mng_msg_t)) >= 1)
  {
    cb_read(&sys_mng_msg_from_btn_cb, &msg, sizeof(msg));

    // Check source id
    ASSERT(msg.src_id == SYS_PROT_NOTE_SYS_BTN, SYS_MNG_ERROR);
    // Process message
    switch (mng_state)
    {
    case SYS_MNG_STATE_IDLE:
      // Message process
      sys_prot_send_msg(SYS_PROT_NOTE_SYS_MNG, SYS_PROT_NOTE_SYS_LED,
                        (uint8_t *)&msg.event, sizeof(msg.event));
      break;

    default:
      break;
    }
  }

  return SYS_MNG_SUCCESS;
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
