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
#include "cbuffer.h"
#include "common.h"
#include "sys_mng.h"
#include "sys_prot.h"

/* Private defines ---------------------------------------------------- */
#define SYS_BTN_MSG_BUFF_SIZE (32) /* Size of mMessage circular buffer  */

/* Private enumerate/structure ---------------------------------------- */
typedef struct __attribute__((packed))
{
  sys_prot_note_id_t src_id;
  sys_btn_id_t       btn_id;
  sys_btn_event_t    event;
} sys_btn_msg_t;

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static cbuffer_t sys_btn_msg_cb;
static uint8_t   sys_btn_msg_buff[SYS_BTN_MSG_BUFF_SIZE];

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t sys_btn_init()
{
  uint32_t ret;

  // Init bsp button
  ret = bsp_btn_init();
  ASSERT(ret == BSP_BTN_SUCCESS, SYS_BTN_ERROR);

  // Init circular buffer
  ret = cb_init(&sys_btn_msg_cb, sys_btn_msg_buff, SYS_BTN_MSG_BUFF_SIZE);
  ASSERT(ret == CB_SUCCESS, SYS_BTN_ERROR);

  // Register receiving
  ret = sys_prot_reg_rx(SYS_PROT_NOTE_SYS_BTN, &sys_btn_msg_cb);
  ASSERT(ret == SYS_PROT_SUCCESS, SYS_BTN_ERROR);

  return SYS_BTN_SUCCESS;
}

uint32_t sys_btn_loop()
{
  sys_btn_msg_t msg;

  // BSP loop function
  bsp_btn_loop();

  // Read message from circular buffer
  if ((cb_data_count(&sys_btn_msg_cb) / sizeof(sys_btn_msg_t)) >= 1)
  {
    cb_read(&sys_btn_msg_cb, &msg, sizeof(msg));

    // Check source id
    ASSERT(msg.src_id == SYS_PROT_NOTE_BSP_BTN, SYS_BTN_ERROR);
    // Check button id
    ASSERT(msg.btn_id == SYS_BTN_BTN0, SYS_BTN_ERROR);
    // Process message
    sys_mng_event_t data;
    switch (msg.event)
    {
    case SYS_BTN_EVENT_SINGLE_CLICK:
      data = (sys_mng_event_t)SYS_MNG_BTN_EVENT_SINGLE_CLICK;
      sys_prot_send_msg(SYS_PROT_NOTE_SYS_BTN, SYS_PROT_NOTE_SYS_MNG,
                        (uint8_t *)&data, sizeof(data));
      break;

    case SYS_BTN_EVENT_DOUBLE_CLICK:
      data = (sys_mng_event_t)SYS_MNG_BTN_EVENT_DOUBLE_CLICK;
      sys_prot_send_msg(SYS_PROT_NOTE_SYS_BTN, SYS_PROT_NOTE_SYS_MNG,
                        (uint8_t *)&data, sizeof(data));
      break;

    case SYS_BTN_EVENT_HOLD:
      data = (sys_mng_event_t)SYS_MNG_BTN_EVENT_HOLD;
      sys_prot_send_msg(SYS_PROT_NOTE_SYS_BTN, SYS_PROT_NOTE_SYS_MNG,
                        (uint8_t *)&data, sizeof(data));
      break;

    case SYS_BTN_EVENT_RELEASE:
      data = (sys_mng_event_t)SYS_MNG_BTN_EVENT_RELEASE;
      sys_prot_send_msg(SYS_PROT_NOTE_SYS_BTN, SYS_PROT_NOTE_SYS_MNG,
                        (uint8_t *)&data, sizeof(data));
      break;

    default:
      break;
    }
  }

  return SYS_BTN_SUCCESS;
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
