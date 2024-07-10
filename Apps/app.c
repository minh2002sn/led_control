/**
 * @file        app.c
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
#include "app.h"
#include "main.h"
#include "sys_btn.h"
#include "sys_data_mng.h"
#include "sys_led.h"
#include "sys_mng.h"

/* Private defines ---------------------------------------------------- */
#define PRINTF_UART_ENABLE 1      /* (1) Enable using printf() with UART */
#define PRINTF_UART_X      huart2 /* UART port used for printf() */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */
// Using printf with UART
#if PRINTF_UART_ENABLE
extern UART_HandleTypeDef PRINTF_UART_X;
#if defined(__GNUC__)
int _write(int fd, char *ptr, int len)
{
  HAL_UART_Transmit(&PRINTF_UART_X, (uint8_t *)ptr, len, 0xFFFFFFFF);
  return len;
}
#elif defined(__ICCARM__)
#include "LowLevelIOInterface.h"

size_t __write(int handle, const unsigned char *buffer, size_t size)
{
  HAL_UART_Transmit(&PRINTF_UART_X, (uint8_t *)buffer, size, 0xFFFFFFFF);
  return size;
}
#elif defined(__CC_ARM)
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&PRINTF_UART_X, (uint8_t *)&ch, 1, 0xFFFFFFFF);
  return ch;
}
#endif
#endif

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
void app_init()
{
  sys_data_mng_init();
  sys_mng_init();
  sys_btn_init();
  sys_led_init();
}

void app_loop()
{
  sys_data_mng_loop();
  sys_mng_loop();
  sys_btn_loop();
  sys_led_loop();
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
