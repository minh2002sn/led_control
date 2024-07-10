/**
 * @file        sys_data_mng.c
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
#include "sys_data_mng.h"
#include "cbuffer.h"
#include "common.h"

/* Private defines ---------------------------------------------------- */
#define SYS_DATA_MNG_BUFF_SIZE          255 /* Buffer size */
#define SYS_DATA_MNG_MAX_NUM_TOPIC      32  /* Maximum number of topic */
#define SYS_DATA_MNG_MAX_NUM_SUBSCRIBER 4   /* Maximum number of subscribers */

/* Private enumerate/structure ---------------------------------------- */
typedef struct
{
  sys_data_mng_topic_id_t topic_id;
  uint32_t                frame_size;
  cbuffer_t               cir_buff;
  uint32_t                num_subscriber;
  sys_data_mng_cb_func_t  cb_funcs[SYS_DATA_MNG_MAX_NUM_SUBSCRIBER];
} sys_data_mng_topic_data_t;

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static uint8_t                   sdatamng_buff[SYS_DATA_MNG_BUFF_SIZE];
static uint32_t                  sdatamng_buff_top;
static sys_data_mng_topic_data_t sdatamng_topics[SYS_DATA_MNG_MAX_NUM_TOPIC];
static uint32_t                  sdatamng_num_topic;
// Buffer to store data from circular buffer
static uint8_t sdatamng_rx_buff[SYS_DATA_MNG_BUFF_SIZE];
// Buffer has data copied from sdatamng_rx_buff, use as parameter for callback function
static uint8_t sdatamng_param_buff[SYS_DATA_MNG_BUFF_SIZE];
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
uint32_t sys_data_mng_init()
{
  return SYS_DATA_MNG_SUCCESS;
}

uint32_t sys_data_mng_loop()
{
  for (int i = 0; i < sdatamng_num_topic; i++)
  {
    // Check number of data in buffer
    if ((cb_data_count(&sdatamng_topics[i].cir_buff) / sdatamng_topics[i].frame_size) >= 1)
    {
      cb_read(&sdatamng_topics[i].cir_buff, sdatamng_rx_buff, sdatamng_topics[i].frame_size);
      for (int j = 0; j < sdatamng_topics[i].num_subscriber; j++)
      {
        // Copy sdatamng_rx_buff data to sdatamng_param_buff
        memcpy(sdatamng_param_buff, sdatamng_rx_buff, sdatamng_topics[i].frame_size);
        // Call callback function
        sdatamng_topics[i].cb_funcs[j](sdatamng_param_buff, sdatamng_topics[i].frame_size);
      }
    }
  }

  return SYS_DATA_MNG_SUCCESS;
}

uint32_t sys_data_mng_create_topic(sys_data_mng_topic_id_t topic_id,
                                   uint32_t                size_of_frame,
                                   uint32_t                num_of_frame)
{
  uint32_t ret;
  // Assert input
  // Check full topics by checking active field of the last element of sdatamng_topics
  ASSERT(sdatamng_num_topic < SYS_DATA_MNG_MAX_NUM_TOPIC, SYS_DATA_MNG_ERROR);
  // Check whether topic has existed
  for (int i = 0; i < sdatamng_num_topic; i++)
  {
    ASSERT(topic_id != sdatamng_topics[i].topic_id, SYS_DATA_MNG_ERROR);
  }
  // Check available size of buffer
  ASSERT((size_of_frame * num_of_frame) <= (SYS_DATA_MNG_BUFF_SIZE - sdatamng_buff_top),
         SYS_DATA_MNG_ERROR);

  // Init circular buffer
  ret = cb_init(&sdatamng_topics[sdatamng_num_topic].cir_buff,
                (sdatamng_buff + sdatamng_buff_top), size_of_frame * num_of_frame);
  ASSERT(ret == CB_SUCCESS, SYS_DATA_MNG_ERROR);

  // Store topic data
  sdatamng_topics[sdatamng_num_topic].topic_id   = topic_id;
  sdatamng_topics[sdatamng_num_topic].frame_size = size_of_frame;

  // Update sdatamng_num_topic
  sdatamng_num_topic++;
  // Update sdatamng_buff_top
  sdatamng_buff_top += size_of_frame * num_of_frame;

  return SYS_DATA_MNG_SUCCESS;
}

uint32_t sys_data_mng_subscribe_topic(sys_data_mng_topic_id_t topic_id,
                                      sys_data_mng_cb_func_t  cb_func)
{
  uint32_t topic_index;

  // Check whether the topic has existed
  for (topic_index = 0; topic_index < sdatamng_num_topic; topic_index++)
  {
    if (topic_id == sdatamng_topics[topic_index].topic_id)
    {
      break;
    }
  }
  ASSERT(topic_index < sdatamng_num_topic, SYS_DATA_MNG_ERROR);

  // Check max number of subscribers
  ASSERT(sdatamng_topics[topic_index].num_subscriber < SYS_DATA_MNG_MAX_NUM_SUBSCRIBER,
         SYS_DATA_MNG_ERROR);

  // Check whether callback function has existed
  for (int i = 0; i < sdatamng_topics[topic_index].num_subscriber; i++)
  {
    ASSERT(sdatamng_topics[topic_index].cb_funcs[i] != cb_func, SYS_DATA_MNG_ERROR);
  }

  // Store callback function
  sdatamng_topics[topic_index].cb_funcs[sdatamng_topics[topic_index].num_subscriber] = cb_func;

  // Update number of subscriber
  sdatamng_topics[topic_index].num_subscriber++;

  return SYS_DATA_MNG_SUCCESS;
}

uint32_t sys_data_mng_publish_topic(sys_data_mng_topic_id_t topic_id, uint8_t *data, uint32_t size)
{
  uint32_t topic_index;
  // Check data parameter
  ASSERT(data != NULL, SYS_DATA_MNG_ERROR);

  // Check whether the topic has existed
  for (topic_index = 0; topic_index < sdatamng_num_topic; topic_index++)
  {
    if (topic_id == sdatamng_topics[topic_index].topic_id)
    {
      break;
    }
  }
  ASSERT(topic_index < sdatamng_num_topic, SYS_DATA_MNG_ERROR);

  // Check size of data buffer
  ASSERT(size <= sdatamng_topics[topic_index].frame_size, SYS_DATA_MNG_ERROR);

  // Check available space in circular buffer
  ASSERT(sdatamng_topics[topic_index].frame_size <=
         cb_space_count(&sdatamng_topics[topic_index].cir_buff),
         SYS_DATA_MNG_ERROR);

  if (cb_space_count(&sdatamng_topics[topic_index].cir_buff) <=
      sdatamng_topics[topic_index].frame_size)
  {
    cb_read(&sdatamng_topics[topic_index].cir_buff, sdatamng_rx_buff,
            sdatamng_topics[topic_index].frame_size);
  }

  // Write data to circular buffer
  cb_write(&sdatamng_topics[topic_index].cir_buff, data, size);
  // Write 0x00 if size < size of frame
  for (int i = 0; i < sdatamng_topics[topic_index].frame_size - size; i++)
  {
    uint8_t temp = 0;
    cb_write(&sdatamng_topics[topic_index].cir_buff, &temp, sizeof(temp));
  }

  return SYS_DATA_MNG_SUCCESS;
}

/* Private definitions ------------------------------------------------ */

/* End of file -------------------------------------------------------- */
