/**
 * @file        common.h
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
#ifndef __COMMON_
#define __COMMON_

/* Includes ----------------------------------------------------------- */

/* Public defines ----------------------------------------------------- */
#define UART_DEBUG_ENABLE  1      /* Enable UART debug */
#define PRINTF_UART_ENABLE 1      /* (1) Enable using printf() with UART */
#define PRINTF_UART_X      huart2 /* UART port used for printf() */

/* Public enumerate/structure ----------------------------------------- */

/* Public macros ------------------------------------------------------ */
// Assert input parameter
#define ASSERT(_expr_, _rc_) \
  do                         \
  {                          \
    if (!(_expr_))           \
      return (_rc_);         \
  } while (0)

// Check callback function and call that function
#define CALLBACK(_cb_func_, ...) \
  do                             \
  {                              \
    if (((_cb_func_) != NULL))   \
      _cb_func_(__VA_ARGS__);    \
  } while (0)

// Using printf with UART
#if PRINTF_UART_ENABLE
#if defined(__GNUC__)
int _write(int fd, char *ptr, int len)
{
  HAL_UART_Transmit(&PRINTF_UART_X, (uint8_t *)ptr, len, HAL_MAX_DELAY);
  return len;
}
#elif defined(__ICCARM__)
#include "LowLevelIOInterface.h"

size_t __write(int handle, const unsigned char *buffer, size_t size)
{
  HAL_UART_Transmit(&PRINTF_UART_X, (uint8_t *)buffer, size, HAL_MAX_DELAY);
  return size;
}
#elif defined(__CC_ARM)
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&PRINTF_UART_X, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}
#endif
#endif
/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */

/* Public function prototypes ----------------------------------------- */

#endif // __COMMON_

/* End of file -------------------------------------------------------- */
