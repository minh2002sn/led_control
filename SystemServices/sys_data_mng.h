/**
 * @file        sys_data_mng.h
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
#ifndef __SYS_DATA_MNG_
#define __SYS_DATA_MNG_

/* Includes ----------------------------------------------------------- */
#include "sys_data_mng_common.h"
#include <stdint.h>


/* Public defines ----------------------------------------------------- */
#define SYS_DATA_MNG_SUCCESS (0x00000000)
#define SYS_DATA_MNG_ERROR   (0xFFFFFFFF)
#define SYS_DATA_MNG_BUFFULL (0xFFFFFFFE) /* Buffer full */

/* Public enumerate/structure ----------------------------------------- */
typedef void (*sys_data_mng_cb_func_t)(uint8_t *, uint32_t);

/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Initialize system data manager
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_data_mng_init();

/**
 * @brief           System data manager loop function
 *                  Check topic and call callback function
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_data_mng_loop();

/**
 * @brief           Initialize system data manager
 *
 * @param[in]       topic_id      Topic ID, specified in sys_data_mng_common
 * @param[in]       size_of_frame Size of 1 data frame
 * @param[in]       num_of_frame  Number of frame in buffer
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_data_mng_create_topic(sys_data_mng_topic_id_t topic_id,
                                   uint32_t                size_of_frame,
                                   uint32_t                num_of_frame);

/**
 * @brief           Create a new topic
 *
 * @param[in]       topic_id      Topic ID, specified in sys_data_mng_common
 * @param[in]       cb_func       Callback function for a topic
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_data_mng_subscribe_topic(sys_data_mng_topic_id_t topic_id,
                                      sys_data_mng_cb_func_t  cb_func);

/**
 * @brief           Subscribe to a topic to receive data
 *
 * @param[in]       topic_id      Topic ID, specified in sys_data_mng_common
 * @param[in]       data          Pointer to data buffer
 * @param[in]       size          Size of data buffer
 *
 * @return
 *  - (0) : Success
 *  - (-1): Error
 */
uint32_t sys_data_mng_publish_topic(sys_data_mng_topic_id_t topic_id, uint8_t *data, uint32_t size);

#endif // __SYS_DATA_MNG_

/* End of file -------------------------------------------------------- */
