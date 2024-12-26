/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */






// TFT LCD -- Driver



///// FONTE PARA TFT /////
const char Font[] = {
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x5F, 0x00, 0x00,
	0x00, 0x07, 0x00, 0x07, 0x00,
	0x14, 0x7F, 0x14, 0x7F, 0x14,
	0x24, 0x2A, 0x7F, 0x2A, 0x12,
	0x23, 0x13, 0x08, 0x64, 0x62,
	0x36, 0x49, 0x56, 0x20, 0x50,
	0x00, 0x08, 0x07, 0x03, 0x00,
	0x00, 0x1C, 0x22, 0x41, 0x00,
	0x00, 0x41, 0x22, 0x1C, 0x00,
	0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
	0x08, 0x08, 0x3E, 0x08, 0x08,
	0x00, 0x80, 0x70, 0x30, 0x00,
	0x08, 0x08, 0x08, 0x08, 0x08,
	0x00, 0x00, 0x60, 0x60, 0x00,
	0x20, 0x10, 0x08, 0x04, 0x02,
	0x3E, 0x51, 0x49, 0x45, 0x3E,
	0x00, 0x42, 0x7F, 0x40, 0x00,
	0x72, 0x49, 0x49, 0x49, 0x46,
	0x21, 0x41, 0x49, 0x4D, 0x33,
	0x18, 0x14, 0x12, 0x7F, 0x10,
	0x27, 0x45, 0x45, 0x45, 0x39,
	0x3C, 0x4A, 0x49, 0x49, 0x31,
	0x41, 0x21, 0x11, 0x09, 0x07,
	0x36, 0x49, 0x49, 0x49, 0x36,
	0x46, 0x49, 0x49, 0x29, 0x1E,
	0x00, 0x00, 0x14, 0x00, 0x00,
	0x00, 0x40, 0x34, 0x00, 0x00,
	0x00, 0x08, 0x14, 0x22, 0x41,
	0x14, 0x14, 0x14, 0x14, 0x14,
	0x00, 0x41, 0x22, 0x14, 0x08,
	0x02, 0x01, 0x59, 0x09, 0x06,
	0x3E, 0x41, 0x5D, 0x59, 0x4E,
	0x7C, 0x12, 0x11, 0x12, 0x7C,
	0x7F, 0x49, 0x49, 0x49, 0x36,
	0x3E, 0x41, 0x41, 0x41, 0x22,
	0x7F, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x49, 0x49, 0x49, 0x41,
	0x7F, 0x09, 0x09, 0x09, 0x01,
	0x3E, 0x41, 0x41, 0x51, 0x73,
	0x7F, 0x08, 0x08, 0x08, 0x7F,
	0x00, 0x41, 0x7F, 0x41, 0x00,
	0x20, 0x40, 0x41, 0x3F, 0x01,
	0x7F, 0x08, 0x14, 0x22, 0x41,
	0x7F, 0x40, 0x40, 0x40, 0x40,
	0x7F, 0x02, 0x1C, 0x02, 0x7F,
	0x7F, 0x04, 0x08, 0x10, 0x7F,
	0x3E, 0x41, 0x41, 0x41, 0x3E,
	0x7F, 0x09, 0x09, 0x09, 0x06,
	0x3E, 0x41, 0x51, 0x21, 0x5E,
	0x7F, 0x09, 0x19, 0x29, 0x46,  // R
	0x26, 0x49, 0x49, 0x49, 0x32, // S
	0x03, 0x01, 0x7F, 0x01, 0x03,
	0x3F, 0x40, 0x40, 0x40, 0x3F,
	0x1F, 0x20, 0x40, 0x20, 0x1F,
	0x3F, 0x40, 0x38, 0x40, 0x3F,
	0x63, 0x14, 0x08, 0x14, 0x63,
	0x03, 0x04, 0x78, 0x04, 0x03,
	0x61, 0x59, 0x49, 0x4D, 0x43,
	0x00, 0x7F, 0x41, 0x41, 0x41,
	0x02, 0x04, 0x08, 0x10, 0x20,
	0x00, 0x41, 0x41, 0x41, 0x7F,
	0x04, 0x02, 0x01, 0x02, 0x04,
	0x40, 0x40, 0x40, 0x40, 0x40,
	0x00, 0x03, 0x07, 0x08, 0x00,
	0x20, 0x54, 0x54, 0x78, 0x40,
	0x7F, 0x28, 0x44, 0x44, 0x38,
	0x38, 0x44, 0x44, 0x44, 0x28,
	0x38, 0x44, 0x44, 0x28, 0x7F,
	0x38, 0x54, 0x54, 0x54, 0x18,
	0x00, 0x08, 0x7E, 0x09, 0x02,
	0x18, 0xA4, 0xA4, 0x9C, 0x78,
	0x7F, 0x08, 0x04, 0x04, 0x78,
	0x00, 0x44, 0x7D, 0x40, 0x00,
	0x20, 0x40, 0x40, 0x3D, 0x00,
	0x7F, 0x10, 0x28, 0x44, 0x00,
	0x00, 0x41, 0x7F, 0x40, 0x00,
	0x7C, 0x04, 0x78, 0x04, 0x78,
	0x7C, 0x08, 0x04, 0x04, 0x78,
	0x38, 0x44, 0x44, 0x44, 0x38,
	0xFC, 0x18, 0x24, 0x24, 0x18,
	0x18, 0x24, 0x24, 0x18, 0xFC,
	0x7C, 0x08, 0x04, 0x04, 0x08,
	0x48, 0x54, 0x54, 0x54, 0x24,
	0x04, 0x04, 0x3F, 0x44, 0x24,
	0x3C, 0x40, 0x40, 0x20, 0x7C,
	0x1C, 0x20, 0x40, 0x20, 0x1C,
	0x3C, 0x40, 0x30, 0x40, 0x3C,
	0x44, 0x28, 0x10, 0x28, 0x44,
	0x4C, 0x90, 0x90, 0x90, 0x7C,
	0x44, 0x64, 0x54, 0x4C, 0x44,
	0x00, 0x08, 0x36, 0x41, 0x00,
	0x00, 0x00, 0x77, 0x00, 0x00,
	0x00, 0x41, 0x36, 0x08, 0x00,
	0x02, 0x01, 0x02, 0x04, 0x02
};
///// FIM FONTE /////








#ifndef _swap_int16_t
#define _swap_int16_t(a, b)                                                    \
  {                                                                            \
    int16_t t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  }
#endif




void tft_cmd( unsigned char data ){
    HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
    //NOP();
    HAL_SPI_Transmit(&hspi1, (uint8_t[]){data}, 1, 1000);
}


void tft_data( unsigned char data ){
    HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
    // NOP();

    HAL_SPI_Transmit(&hspi1, (uint8_t[]){data}, 1, 1000);

}


void tft_data16( unsigned char msb, unsigned char lsb ){
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
    // NOP();
    HAL_SPI_Transmit(&hspi1, (uint8_t[]){msb, lsb}, 2, 1000);
}


void tft_init(){

    //************* Reset LCD Driver ****************//
    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
    HAL_Delay(120);

    /* INIT */

    // Software Reset
    tft_cmd(0x01);
    HAL_Delay(150);

    // Sleep out
    tft_cmd(0x11);
    HAL_Delay(500);

    // Interface pixel format
    tft_cmd(0x3A);
    tft_data(0x55);
    HAL_Delay(10);

    // Memory data access control
    tft_cmd(0x36);
    //tft_data(0x08);
	tft_data(0x00);

    // CASET
    tft_cmd(0x2A);
    tft_data(0x00);
    tft_data(0);
    tft_data(0);
    tft_data(240);

    // RASET
    tft_cmd(0x2B);
    tft_data(0x00);
    tft_data(0);
    tft_data(0);
    tft_data(240);

    // Display inversion - on
    tft_cmd(0x21);
    HAL_Delay(10);

    // Partial off (Normal)
    tft_cmd(0x13);
    HAL_Delay(10);

    // Display on
    tft_cmd(0x29);
    HAL_Delay(500);



    //tft_cmd(0x2c); //memory write
    //__delay_ms(200);

}


void tft_setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
	uint16_t x_start = x0 + 0, x_end = x1 + 0;
	uint16_t y_start = y0 + 0, y_end = y1 + 0;

	tft_cmd(0x2A); // Column addr set
	tft_data(x_start >> 8);
	tft_data(x_start & 0xFF);     // XSTART
	tft_data(x_end >> 8);
	tft_data(x_end & 0xFF);     // XEND

	tft_cmd(0x2B); // Row addr set
	tft_data(y_start >> 8);
	tft_data(y_start & 0xFF);     // YSTART
	tft_data(y_end >> 8);
	tft_data(y_end & 0xFF);     // YEND

	tft_cmd(0x2c); // write to RAM

}


void tft_pixel(int16_t x, int16_t y, uint16_t color){
	if((x < 0) ||(x >= 240) || (y < 0) || (y >= 240)) return;
	tft_setAddrWindow(x,y,x+1,y+1);
	tft_data16(color >> 8, color);
}


void tft_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
	// rudimentary clipping (drawChar w/big text requires this)
	if((x >= 240) || (y >= 240)) return;
	if((x + w - 1) >= 240)  w = 240  - x;
	if((y + h - 1) >= 240) h = 240 - y;

	tft_setAddrWindow(x, y, x+w-1, y+h-1);

	uint8_t hi = color >> 8, lo = color;

	for(y=h; y>0; y--) {
	  for(x=w; x>0; x--) {
		  tft_data16(hi, lo);
	  }
	}



}


uint16_t tft_color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


void tft_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {

  // Rudimentary clipping
  if((x >= 240) || (y >= 240)) return;
  if((y+h-1) >= 240) h = 240-y;
  tft_setAddrWindow(x, y, x, y+h-1);

  uint8_t hi = color >> 8, lo = color;

  while (h--) {
	  tft_data16(hi, lo);
  }

}


void tft_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {

  // Rudimentary clipping
  if((x >= 240) || (y >= 240)) return;
  if((x+w-1) >= 240)  w = 240-x;
  tft_setAddrWindow(x, y, x+w-1, y);

  uint8_t hi = color >> 8, lo = color;

  while (w--) {
    tft_data16(hi, lo);
  }

}


void tft_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  tft_drawFastHLine(x, y, w, color);
  tft_drawFastHLine(x, y + h - 1, w, color);
  tft_drawFastVLine(x, y, h, color);
  tft_drawFastVLine(x + w - 1, y, h, color);
}


void tft_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {

  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  tft_pixel(x0, y0 + r, color);
  tft_pixel(x0, y0 - r, color);
  tft_pixel(x0 + r, y0, color);
  tft_pixel(x0 - r, y0, color);

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    tft_pixel(x0 + x, y0 + y, color);
    tft_pixel(x0 - x, y0 + y, color);
    tft_pixel(x0 + x, y0 - y, color);
    tft_pixel(x0 - x, y0 - y, color);
    tft_pixel(x0 + y, y0 + x, color);
    tft_pixel(x0 - y, y0 + x, color);
    tft_pixel(x0 + y, y0 - x, color);
    tft_pixel(x0 - y, y0 - x, color);
  }

}


void tft_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corners, int16_t delta, uint16_t color) {

  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;
  int16_t px = x;
  int16_t py = y;

  delta++; // Avoid some +1's in the loop

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    // These checks avoid double-drawing certain lines, important
    // for the SSD1306 library which has an INVERT drawing mode.
    if (x < (y + 1)) {
      if (corners & 1)
        tft_drawFastVLine(x0 + x, y0 - y, 2 * y + delta, color);
      if (corners & 2)
        tft_drawFastVLine(x0 - x, y0 - y, 2 * y + delta, color);
    }
    if (y != py) {
      if (corners & 1)
        tft_drawFastVLine(x0 + py, y0 - px, 2 * px + delta, color);
      if (corners & 2)
        tft_drawFastVLine(x0 - py, y0 - px, 2 * px + delta, color);
      py = y;
    }
    px = x;
  }
}


void tft_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {

  tft_drawFastVLine(x0, y0 - r, 2 * r + 1, color);
  tft_fillCircleHelper(x0, y0, r, 3, 0, color);

}


void tft_writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {

  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    _swap_int16_t(x0, y0);
    _swap_int16_t(x1, y1);
  }

  if (x0 > x1) {
    _swap_int16_t(x0, x1);
    _swap_int16_t(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0 <= x1; x0++) {
    if (steep) {
      tft_pixel(y0, x0, color);
    } else {
      tft_pixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}


void tft_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
  // Update in subclasses if desired!
  if (x0 == x1) {
    if (y0 > y1)
      _swap_int16_t(y0, y1);
    tft_drawFastVLine(x0, y0, y1 - y0 + 1, color);
  } else if (y0 == y1) {
    if (x0 > x1)
      _swap_int16_t(x0, x1);
    tft_drawFastHLine(x0, y0, x1 - x0 + 1, color);
  } else {

    tft_writeLine(x0, y0, x1, y1, color);

  }
}



void tft_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
 tft_drawLine(x0, y0, x1, y1, color);
 tft_drawLine(x1, y1, x2, y2, color);
 tft_drawLine(x2, y2, x0, y0, color);
}


void tft_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {

  int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    _swap_int16_t(y0, y1);
    _swap_int16_t(x0, x1);
  }
  if (y1 > y2) {
    _swap_int16_t(y2, y1);
    _swap_int16_t(x2, x1);
  }
  if (y0 > y1) {
    _swap_int16_t(y0, y1);
    _swap_int16_t(x0, x1);
  }


  if (y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if (x1 < a)
      a = x1;
    else if (x1 > b)
      b = x1;
    if (x2 < a)
      a = x2;
    else if (x2 > b)
      b = x2;
    tft_drawFastHLine(a, y0, b - a + 1, color);

    return;
  }

  int16_t dx01 = x1 - x0, dy01 = y1 - y0, dx02 = x2 - x0, dy02 = y2 - y0,
          dx12 = x2 - x1, dy12 = y2 - y1;
  int32_t sa = 0, sb = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if (y1 == y2)
    last = y1; // Include y1 scanline
  else
    last = y1 - 1; // Skip it

  for (y = y0; y <= last; y++) {
    a = x0 + sa / dy01;
    b = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if (a > b)
      _swap_int16_t(a, b);
    tft_drawFastHLine(a, y, b - a + 1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = (int32_t)dx12 * (y - y1);
  sb = (int32_t)dx02 * (y - y0);
  for (; y <= y2; y++) {
    a = x1 + sa / dy12;
    b = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if (a > b)
      _swap_int16_t(a, b);
    tft_drawFastHLine(a, y, b - a + 1, color);
  }
}







void tft_drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size){
  if((x >= 240)		|| // Clip right
     (y >= 240)		|| // Clip bottom
     ((x + 6 * size - 1) < 0)	|| // Clip left
     ((y + 8 * size - 1) < 0))     // Clip top
    return;

  for (int8_t i=0; i<6; i++ ) {
    uint8_t line;
    if (i == 5)
      line = 0x0;
    else
      line = Font[(c - 0x20)*5 + i];
    for (int8_t j = 0; j<8; j++) {
      if (line & 0x1) {
        if (size == 1) // default size
          tft_pixel(x+i, y+j, color);

        else {  // big size
          tft_fillRect(x+(i*size), y+(j*size), size, size, color);
        }
      } else if (bg != color) {
        if (size == 1) // default size
          tft_pixel(x+i, y+j, bg);
        else {  // big size
          tft_fillRect(x+i*size, y+j*size, size, size, bg);
        }
      }
      line >>= 1;
    }
  }
}

char _wrap = 0;
void tft_setTextWrap(char s){
	_wrap = s;
}

void tft_drawText(uint8_t x, uint8_t y, const char *_text, uint16_t color, uint16_t bg, uint8_t size) {
  uint8_t cursor_x, cursor_y;
  uint16_t textsize, i;
  cursor_x = x, cursor_y = y;
  textsize = strlen(_text);
  for(i = 0; i < textsize; i++){
    if(_wrap && ((cursor_x + size * 5) > 240)) {
      cursor_x = 0;
      cursor_y = cursor_y + size * 7 + 3 ;
      if(cursor_y > 240) cursor_y = 240;
      if(_text[i] == 0x20) {
        continue;
      }
    }
    tft_drawChar(cursor_x, cursor_y, _text[i], color, bg, size);
    cursor_x = cursor_x + size * 6;
    if(cursor_x > 240) {
      cursor_x = 240;
    }
  }
}






















































void renderBitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *bitmap){
	if((x >= 240)		|| // Clip right
		 (y >= 240)		|| // Clip bottom
		 ((x + w - 1) < 0)	|| // Clip left
		 ((y + h - 1) < 0))     // Clip top
		return;

	for (uint16_t moveY = 0; moveY < h; moveY++){
		for (uint16_t moveX = 0; moveX < w; moveX++){
			tft_setAddrWindow(x+moveX,y+moveY,x+moveX+1,y+moveY+1);
			HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
			HAL_SPI_Transmit(&hspi1, (uint8_t[]){(*bitmap) >> 8, *bitmap}, 2, 1000);
			*bitmap++;
		}
	}
}








// SPRITE LIST
// 0 -- brick
// 1 -- back
// 2 -- back w/ dot
// 3 -- box
// 4 -- box dark
// 5 -- player


uint16_t spriteList[6][400] = {
	{
		0x5265, 0x6B27, 0x6B27, 0x6B27, 0x6B27, 0x6B27, 0x6B27, 0x6B27, 0x6B27, 0x6306, 0x5285, 0x6B27, 0x6B27, 0x6B27, 0x6B27, 0x6B27,   // 0x0010 (16) pixels
		0x6B27, 0x6B27, 0x6B27, 0x6B27, 0x6B27, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA,   // 0x0020 (32) pixels
		0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x6B27, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA,   // 0x0030 (48) pixels
		0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x6B27, 0xA4AA, 0xA4AA, 0xA4AA,   // 0x0040 (64) pixels
		0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA,   // 0x0050 (80) pixels
		0x62E6, 0x9449, 0x9449, 0x9449, 0x9449, 0x946A, 0x9449, 0x9449, 0x9449, 0x8C09, 0x6B07, 0x9449, 0x9449, 0x9449, 0x9449, 0x946A,   // 0x0060 (96) pixels
		0x9449, 0x9449, 0x9449, 0x9449, 0x6B27, 0x7347, 0x7347, 0x7347, 0x6B27, 0x5AC6, 0x7347, 0x7347, 0x7347, 0x7347, 0x6B27, 0x7347,   // 0x0070 (112) pixels
		0x7347, 0x7347, 0x6B27, 0x5AC6, 0x7347, 0x7347, 0x7347, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA,   // 0x0080 (128) pixels
		0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA,   // 0x0090 (144) pixels
		0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA,   // 0x00A0 (160) pixels
		0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347,   // 0x00B0 (176) pixels
		0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x946A, 0x9449, 0x9449, 0x9449, 0x8C09, 0x6B07, 0x9449, 0x9449, 0x9449, 0x9449, 0x946A, 0x9449,   // 0x00C0 (192) pixels
		0x9449, 0x9449, 0x8C09, 0x6B07, 0x9449, 0x9449, 0x9449, 0x9449, 0x5AA6, 0x7347, 0x7347, 0x7347, 0x7347, 0x6B27, 0x7347, 0x7347,   // 0x00D0 (208) pixels
		0x7347, 0x6B27, 0x5AC6, 0x7347, 0x7347, 0x7347, 0x7347, 0x6B27, 0x7347, 0x7347, 0x7347, 0x7347, 0x6B27, 0xA4AA, 0xA4AA, 0xA4AA,   // 0x00E0 (224) pixels
		0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA,   // 0x00F0 (240) pixels
		0x6B27, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA,   // 0x0100 (256) pixels
		0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x6B27, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA,   // 0x0110 (272) pixels
		0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x62E6, 0x9449, 0x9449, 0x9449, 0x9449, 0x946A, 0x9449, 0x9449,   // 0x0120 (288) pixels
		0x9449, 0x8C09, 0x6B07, 0x9449, 0x9449, 0x9449, 0x9449, 0x946A, 0x9449, 0x9449, 0x9449, 0x9449, 0x6B27, 0x7347, 0x7347, 0x7347,   // 0x0130 (304) pixels
		0x6B27, 0x5AC6, 0x7347, 0x7347, 0x7347, 0x7347, 0x6B27, 0x7347, 0x7347, 0x7347, 0x6B27, 0x5AC6, 0x7347, 0x7347, 0x7347, 0x7347,   // 0x0140 (320) pixels
		0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347,   // 0x0150 (336) pixels
		0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA,   // 0x0160 (352) pixels
		0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA,   // 0x0170 (368) pixels
		0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA,   // 0x0180 (384) pixels
		0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA, 0x9449, 0x7347, 0xA4AA, 0xA4AA, 0xA4AA, 0xA4AA,   // 0x0190 (400) pixels
	},
	{
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD653, 0xD654, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD653,   // 0x0010 (16) pixels
		0xD654, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDE95, 0xD654,   // 0x0020 (32) pixels
		0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD654, 0xD674, 0xDEB5, 0xDEB5, 0xD674, 0xD654,   // 0x0030 (48) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDE95,   // 0x0040 (64) pixels
		0xD674, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xDE95, 0xDEB5, 0xDEB5, 0xDE95, 0xD654, 0xD654, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0050 (80) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0060 (96) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0070 (112) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xD674, 0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xD654, 0xD654, 0xDE95, 0xDEB5,   // 0x0080 (128) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD654, 0xDE95, 0xDE95, 0xD674, 0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0090 (144) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xD654, 0xD654, 0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x00A0 (160) pixels
		0xD674, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x00B0 (176) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD674, 0xDEB5, 0xD674, 0xD654, 0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x00C0 (192) pixels
		0xDE95, 0xD654, 0xD654, 0xDEB5, 0xDEB5, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x00D0 (208) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xD654, 0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x00E0 (224) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x00F0 (240) pixels
		0xDEB5, 0xD674, 0xD654, 0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xD654, 0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xD654, 0xD654, 0xDE95, 0xDEB5,   // 0x0100 (256) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0110 (272) pixels
		0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDE95,   // 0x0120 (288) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xD654, 0xD654, 0xDE95, 0xDEB5,   // 0x0130 (304) pixels
		0xDEB5, 0xD654, 0xD654, 0xD654, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD654, 0xD654, 0xDE95, 0xDEB5, 0xDEB5,   // 0x0140 (320) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD654, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0150 (336) pixels
		0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xD654, 0xD654, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0160 (352) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD674, 0xDEB5, 0xD674, 0xD654, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0170 (368) pixels
		0xDE95, 0xD654, 0xD654, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0180 (384) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0190 (400) pixels
	},
	{
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD653, 0xD654, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD653,   // 0x0010 (16) pixels
		0xD654, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDE95, 0xD654,   // 0x0020 (32) pixels
		0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD654, 0xD674, 0xDEB5, 0xDEB5, 0xD674, 0xD654,   // 0x0030 (48) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDE95,   // 0x0040 (64) pixels
		0xD674, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xDE95, 0xDEB5, 0xDEB5, 0xDE95, 0xD654, 0xD654, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0050 (80) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0060 (96) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0070 (112) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xD674, 0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xD654, 0xD654, 0xDE95, 0xDEB5,   // 0x0080 (128) pixels
		0xDE34, 0xDD72, 0xDD32, 0xDDB3, 0xDE95, 0xDEB5, 0xD674, 0xD654, 0xDE95, 0xDE95, 0xD674, 0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0090 (144) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDE34, 0xD4F1, 0xD4B0, 0xD4B0, 0xD4B0, 0xDD52, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x00A0 (160) pixels
		0xD674, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE75, 0xDD12, 0xD4B0, 0xD4B0, 0xD4B0, 0xD4B0, 0xD4B0, 0xDDB3, 0xDEB5, 0xDEB5,   // 0x00B0 (176) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD674, 0xDEB5, 0xD674, 0xD654, 0xD674, 0xDE54, 0xD4B0, 0xD4B0, 0xD4B0, 0xD4B0, 0xD4B0,   // 0x00C0 (192) pixels
		0xD4B0, 0xD511, 0xD654, 0xDEB5, 0xDEB5, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDEB5, 0xDE75, 0xDCF1,   // 0x00D0 (208) pixels
		0xD4B0, 0xD4B0, 0xD4B0, 0xD4B0, 0xD4B0, 0xDD52, 0xDE95, 0xDEB5, 0xDEB5, 0xD654, 0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x00E0 (224) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xD592, 0xD4B0, 0xD4B0, 0xD4B0, 0xD4B0, 0xD4F1, 0xDE34, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x00F0 (240) pixels
		0xDEB5, 0xD674, 0xD654, 0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xD654, 0xDDB3, 0xDCF1, 0xD4B0, 0xD511, 0xD5D3, 0xD654, 0xDE95, 0xDEB5,   // 0x0100 (256) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE75, 0xDE54, 0xDE75,   // 0x0110 (272) pixels
		0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDE95,   // 0x0120 (288) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xD654, 0xD654, 0xDE95, 0xDEB5,   // 0x0130 (304) pixels
		0xDEB5, 0xD654, 0xD654, 0xD654, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD654, 0xD654, 0xDE95, 0xDEB5, 0xDEB5,   // 0x0140 (320) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD654, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0150 (336) pixels
		0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xD654, 0xD654, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0160 (352) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD674, 0xDEB5, 0xD674, 0xD654, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0170 (368) pixels
		0xDE95, 0xD654, 0xD654, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0180 (384) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0190 (400) pixels
	},
	{
		0xB571, 0x83CC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC,   // 0x0010 (16) pixels
		0x83EC, 0x83EC, 0x83EC, 0xB571, 0x83CC, 0x836A, 0xBCCD, 0xB4AD, 0xB4AD, 0xB4AD, 0xB4AD, 0xB4AD, 0xB4AD, 0xB4AD, 0xB4AD, 0xB4AD,   // 0x0020 (32) pixels
		0xB4AD, 0xB4AD, 0xB4AD, 0xB4AD, 0xB4AD, 0xBCAD, 0x7AC5, 0x83CC, 0x83EC, 0xBCCD, 0xFE0B, 0xFDCA, 0xFDEA, 0xFDEA, 0xFDEA, 0xFDEA,   // 0x0030 (48) pixels
		0xFDEA, 0xFDEA, 0xFDEA, 0xFDEA, 0xFDEA, 0xFDEA, 0xFDEA, 0xFDEA, 0xFDCA, 0xFDEA, 0xA322, 0x83CC, 0x83EC, 0xB4AD, 0xFDCA, 0xD423,   // 0x0040 (64) pixels
		0xA301, 0xA301, 0xA321, 0xA301, 0xA301, 0xA301, 0xA301, 0xA301, 0xA301, 0xA321, 0xA301, 0xA321, 0xE529, 0xFDCA, 0xA301, 0x83CC,   // 0x0050 (80) pixels
		0x83EC, 0xB4AD, 0xFDEA, 0xA301, 0x5180, 0x61E1, 0x59A0, 0x8A60, 0x8260, 0x8260, 0x8260, 0x8260, 0x8A60, 0x59A0, 0x61E1, 0x5980,   // 0x0060 (96) pixels
		0xB4AD, 0xFDEA, 0xA301, 0x83CC, 0x83EC, 0xB4AD, 0xFDEA, 0xA301, 0x8AA0, 0xFD8A, 0x9BA8, 0xB320, 0xEC83, 0xECA3, 0xECA3, 0xF4C3,   // 0x0070 (112) pixels
		0xBB82, 0x9BA8, 0xFD8A, 0x8AA1, 0xB4AD, 0xFDEA, 0xA301, 0x83CC, 0x83EC, 0xB4AD, 0xFDEA, 0xA301, 0x7220, 0xFD68, 0xF5CC, 0x9388,   // 0x0080 (128) pixels
		0xBBE4, 0xFDCA, 0xFDCA, 0xCC88, 0x9BEA, 0xF5CC, 0xCC24, 0x4140, 0xB4AD, 0xFDEA, 0xA301, 0x83CC, 0x83EC, 0xB4AD, 0xFDEA, 0xA321,   // 0x0090 (144) pixels
		0x4140, 0xA322, 0xFD68, 0xF5CC, 0x9BC9, 0xCC88, 0xCC88, 0x9BCA, 0xFDCC, 0xCC24, 0x8260, 0x7220, 0xB4AD, 0xFDEA, 0xA301, 0x83CC,   // 0x00A0 (160) pixels
		0x83EC, 0xB4AD, 0xFDEA, 0xA301, 0x8260, 0x9AC0, 0x9B02, 0xFD68, 0xF5CC, 0x8B89, 0x6AA6, 0xF5CC, 0xCC24, 0x8260, 0xE4A5, 0x8AA1,   // 0x00B0 (176) pixels
		0xB4AD, 0xFDEA, 0xA301, 0x83CC, 0x83EC, 0xB4AD, 0xFDEA, 0xA301, 0x8260, 0xEC62, 0x9B02, 0xA322, 0xFD68, 0xF5CC, 0x9BCA, 0xA343,   // 0x00C0 (192) pixels
		0x8260, 0xE4C6, 0xFDA9, 0x8AA1, 0xB4AD, 0xFDEA, 0xA301, 0x83CC, 0x83EC, 0xB4AD, 0xFDEA, 0xA301, 0x8260, 0xECA3, 0xFDA9, 0x7AA4,   // 0x00D0 (208) pixels
		0x8AA1, 0xFD68, 0xF5CC, 0x8B68, 0xB3A4, 0xFDCA, 0xFD89, 0x8AA1, 0xB4AD, 0xFDEA, 0xA301, 0x83CC, 0x83EC, 0xB4AD, 0xFDEA, 0xA301,   // 0x00E0 (224) pixels
		0x8260, 0xF4C3, 0xCC88, 0x9BC9, 0x9303, 0xA302, 0xFD68, 0xF5CC, 0x9BEA, 0xCC88, 0xFDA9, 0x8AA1, 0xB4AD, 0xFDEA, 0xA301, 0x83CC,   // 0x00F0 (240) pixels
		0x83EC, 0xB4AD, 0xFDEA, 0xA301, 0x8A60, 0xBB82, 0x9BEA, 0xFDCC, 0xCC04, 0x69E0, 0xA322, 0xFD68, 0xF5CC, 0x9BCA, 0xCC67, 0x8AA1,   // 0x0100 (256) pixels
		0xB4AD, 0xFDEA, 0xA301, 0x83CC, 0x83EC, 0xB4AD, 0xFDEA, 0xA321, 0x59A0, 0x9BA8, 0xF5CC, 0xCC24, 0x8260, 0xDCA6, 0xABC6, 0xA322,   // 0x0110 (272) pixels
		0xFD68, 0xF5CC, 0x9BA7, 0x59A0, 0xB4AD, 0xFDEA, 0xA301, 0x83CC, 0x83EC, 0xB4AD, 0xFDEA, 0xA301, 0x61E1, 0xFD8A, 0xCC24, 0x8260,   // 0x0120 (288) pixels
		0xE4A5, 0xFDA9, 0xFDA9, 0xABA5, 0xA322, 0xFD68, 0xFD48, 0x61E1, 0xB4AD, 0xFDEA, 0xA301, 0x83CC, 0x83EC, 0xB4AD, 0xFDEA, 0xA321,   // 0x0130 (304) pixels
		0x5980, 0x8AA1, 0x4140, 0x7220, 0x8AA1, 0x8AA1, 0x8AA1, 0x8AA1, 0x4940, 0x7221, 0x92A1, 0x59A0, 0xBCAD, 0xFDEA, 0xA301, 0x83CC,   // 0x0140 (320) pixels
		0x83EC, 0xB4AD, 0xFDCA, 0xE529, 0xB4AD, 0xB4AD, 0xB4AD, 0xB4AD, 0xB4AD, 0xB4AD, 0xB4AD, 0xB4AD, 0xBCAD, 0xB4AD, 0xB4AD, 0xBCAD,   // 0x0150 (336) pixels
		0xEDF0, 0xFDCA, 0xA301, 0x83CC, 0x83EC, 0xBCAD, 0xFDEA, 0xFDCA, 0xFDEA, 0xFDEA, 0xFDEA, 0xFDEA, 0xFDEA, 0xFDEA, 0xFDEA, 0xFDEA,   // 0x0160 (352) pixels
		0xFDEA, 0xFDEA, 0xFDEA, 0xFDEA, 0xFDCA, 0xFDA9, 0xA321, 0x83CC, 0x83EC, 0x7AC5, 0xA322, 0xA301, 0xA301, 0xA301, 0xA301, 0xA301,   // 0x0170 (368) pixels
		0xA301, 0xA301, 0xA301, 0xA301, 0xA301, 0xA301, 0xA301, 0xA301, 0xA301, 0xA321, 0x7200, 0x83CC, 0xB571, 0x83CC, 0x83CC, 0x83CC,   // 0x0180 (384) pixels
		0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0xB571,   // 0x0190 (400) pixels
	},
	{
		0xB571, 0x83CC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC, 0x83EC,   // 0x0010 (16) pixels
		0x83EC, 0x83EC, 0x83CC, 0xB571, 0x83CC, 0x5A24, 0x82E6, 0x82E5, 0x82E5, 0x82E5, 0x82E5, 0x82E5, 0x82E5, 0x82E5, 0x82E5, 0x82E5,   // 0x0020 (32) pixels
		0x82E5, 0x82E5, 0x82E5, 0x82E5, 0x82E5, 0x82E5, 0x5981, 0x7BCC, 0x83EC, 0x82E6, 0xC362, 0xBB42, 0xBB42, 0xBB42, 0xBB42, 0xBB42,   // 0x0030 (48) pixels
		0xBB42, 0xBB42, 0xBB42, 0xBB42, 0xBB42, 0xBB42, 0xBB42, 0xBB42, 0xBB42, 0xBB42, 0x7140, 0x83CC, 0x83EC, 0x82E5, 0xBB42, 0x91C0,   // 0x0040 (64) pixels
		0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0xA2C2, 0xBB21, 0x6940, 0x83CC,   // 0x0050 (80) pixels
		0x83EC, 0x82E5, 0xBB42, 0x6940, 0x3880, 0x40C0, 0x3880, 0x58C0, 0x50C0, 0x50C0, 0x50C0, 0x50C0, 0x58C0, 0x3880, 0x40C0, 0x3880,   // 0x0060 (96) pixels
		0x82E6, 0xBB42, 0x6940, 0x83CC, 0x83EC, 0x82E5, 0xBB42, 0x6940, 0x5900, 0xB303, 0x6A24, 0x7120, 0xA1E0, 0xA200, 0xA200, 0xA220,   // 0x0070 (112) pixels
		0x7960, 0x6A24, 0xB303, 0x5900, 0x82E6, 0xBB42, 0x6940, 0x83CC, 0x83EC, 0x82E5, 0xBB42, 0x6940, 0x48C0, 0xB2C1, 0xB363, 0x6A04,   // 0x0080 (128) pixels
		0x81E0, 0xBB21, 0xBB21, 0x9281, 0x7264, 0xB343, 0x8A00, 0x2880, 0x82E6, 0xBB42, 0x6940, 0x83CC, 0x83EC, 0x82E5, 0xBB42, 0x6940,   // 0x0090 (144) pixels
		0x2860, 0x6940, 0xB2E1, 0xB363, 0x6A44, 0x9281, 0x9281, 0x7264, 0xB363, 0x89E0, 0x50C0, 0x48C0, 0x82E6, 0xBB42, 0x6940, 0x83CC,   // 0x00A0 (160) pixels
		0x83EC, 0x82E5, 0xBB42, 0x6940, 0x50C0, 0x60E0, 0x6940, 0xB2E1, 0xB363, 0x6224, 0x51A2, 0xB343, 0x89E0, 0x50E0, 0x9A40, 0x5900,   // 0x00B0 (176) pixels
		0x82E6, 0xBB42, 0x6940, 0x83CC, 0x83EC, 0x82E5, 0xBB42, 0x6940, 0x50C0, 0x99C0, 0x6960, 0x6960, 0xB2E1, 0xB363, 0x7264, 0x7180,   // 0x00C0 (192) pixels
		0x58E0, 0x9A61, 0xBB01, 0x5900, 0x82E6, 0xBB42, 0x6940, 0x83CC, 0x83EC, 0x82E5, 0xBB42, 0x6940, 0x50C0, 0xA200, 0xBB21, 0x5960,   // 0x00D0 (208) pixels
		0x5920, 0xB2E1, 0xB363, 0x6203, 0x79C0, 0xBB21, 0xBB01, 0x5900, 0x82E6, 0xBB42, 0x6940, 0x83CC, 0x83EC, 0x82E5, 0xBB42, 0x6940,   // 0x00E0 (224) pixels
		0x50C0, 0xA220, 0x9281, 0x6A44, 0x6161, 0x6940, 0xB2E1, 0xB363, 0x7264, 0x9281, 0xBB01, 0x5900, 0x82E6, 0xBB42, 0x6940, 0x83CC,   // 0x00F0 (240) pixels
		0x83EC, 0x82E5, 0xBB42, 0x6940, 0x58C0, 0x7960, 0x7264, 0xB363, 0x89E0, 0x40A0, 0x6940, 0xB2E1, 0xB363, 0x7264, 0x9261, 0x5900,   // 0x0100 (256) pixels
		0x82E6, 0xBB42, 0x6940, 0x83CC, 0x83EC, 0x82E5, 0xBB42, 0x6940, 0x3880, 0x6A24, 0xB343, 0x89E0, 0x50E0, 0x9A61, 0x7A00, 0x6960,   // 0x0110 (272) pixels
		0xB2E1, 0xB363, 0x7202, 0x38A0, 0x82E6, 0xBB42, 0x6940, 0x83CC, 0x83EC, 0x82E5, 0xBB42, 0x6940, 0x40C0, 0xB303, 0x8A00, 0x50C0,   // 0x0120 (288) pixels
		0x9A40, 0xBB01, 0xBB01, 0x79E0, 0x6960, 0xB2E1, 0xB2C1, 0x40C0, 0x82E6, 0xBB42, 0x6940, 0x83CC, 0x83EC, 0x82E5, 0xBB42, 0x6940,   // 0x0130 (304) pixels
		0x3880, 0x5900, 0x2880, 0x48C0, 0x5900, 0x5900, 0x5900, 0x5900, 0x2860, 0x48E0, 0x5900, 0x38A0, 0x82E6, 0xBB42, 0x6940, 0x83CC,   // 0x0140 (320) pixels
		0x83EC, 0x82E5, 0xBB42, 0xA2C2, 0x82E6, 0x82E6, 0x82E6, 0x82E6, 0x82E6, 0x82E6, 0x82E6, 0x82E6, 0x82E6, 0x82E6, 0x82E6, 0x82E6,   // 0x0150 (336) pixels
		0xABA6, 0xBB21, 0x6940, 0x83CC, 0x83EC, 0x82E5, 0xBB42, 0xBB21, 0xBB42, 0xBB42, 0xBB42, 0xBB42, 0xBB42, 0xBB42, 0xBB42, 0xBB42,   // 0x0160 (352) pixels
		0xBB42, 0xBB42, 0xBB42, 0xBB42, 0xBB21, 0xBB01, 0x6940, 0x83CC, 0x83CC, 0x5981, 0x7140, 0x6940, 0x6940, 0x6940, 0x6940, 0x6940,   // 0x0170 (368) pixels
		0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0x6940, 0x48A0, 0x7BCC, 0xB571, 0x7BCC, 0x83CC, 0x83CC,   // 0x0180 (384) pixels
		0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x83CC, 0x7BCC, 0xB571,   // 0x0190 (400) pixels
	},
	{
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD654, 0x83EC, 0x18C2, 0x0000, 0x0000, 0x0000, 0x0000, 0x18C2, 0x8C4D, 0xD674, 0xD653,   // 0x0010 (16) pixels
		0xD654, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xE6D6, 0xB571, 0x18C2, 0x0000, 0x2122, 0x39E4, 0x0000, 0x0000,   // 0x0020 (32) pixels
		0x0000, 0x18C2, 0xB571, 0xE6D6, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD674, 0xD654, 0xD674, 0xE6D6, 0x8C2D, 0x0000, 0x0000,   // 0x0030 (48) pixels
		0x7BC8, 0xB58B, 0x2962, 0x0840, 0x0020, 0x0000, 0x8C2D, 0xE6D6, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDE95,   // 0x0040 (64) pixels
		0xDEB5, 0x83EC, 0x18C1, 0x73C8, 0xEF6F, 0xFFD0, 0xE70E, 0xD68E, 0x9CCA, 0x2101, 0x7BCC, 0xD674, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0050 (80) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0x8C2D, 0x6346, 0xBDCC, 0x7387, 0xCE6D, 0xCE4D, 0x7388, 0x9CEB, 0x5B06, 0x944E, 0xE6D6,   // 0x0060 (96) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xD654, 0x6328, 0xD6CE, 0xC60F, 0xEF50, 0xDEEE, 0xC5EF,   // 0x0070 (112) pixels
		0xC60D, 0x62E7, 0xD654, 0xDEB5, 0xDEB5, 0xDE95, 0xD674, 0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xDE95, 0xD654, 0xD654, 0x5AA8, 0x73A7,   // 0x0080 (128) pixels
		0xF78F, 0xF7B0, 0xF7B0, 0xEF50, 0x7387, 0x5AC8, 0xD674, 0xD654, 0xDE95, 0xDE95, 0xD674, 0xD674, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x0090 (144) pixels
		0xDE95, 0xAD30, 0x6B4B, 0x5AEB, 0x6B68, 0x7387, 0x6B87, 0x6B48, 0x4A69, 0x6B2A, 0xAD31, 0xDE95, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5,   // 0x00A0 (160) pixels
		0xD674, 0xDE95, 0xE6D5, 0xCE34, 0x738C, 0x7BCE, 0xB5B6, 0xD69A, 0xB5B6, 0xA534, 0x8431, 0x8C51, 0xB596, 0xAD55, 0x7BCE, 0x738C,   // 0x00B0 (176) pixels
		0xCE34, 0xE6D6, 0xDEB5, 0xDEB5, 0xD674, 0xD674, 0xCE34, 0x7BCD, 0xAD75, 0xDEDB, 0xDEDB, 0xD6BA, 0xDEFB, 0xC638, 0xBDF7, 0xD6BA,   // 0x00C0 (192) pixels
		0xD69A, 0xDEFB, 0xDEDB, 0xAD75, 0x7BAD, 0xCE34, 0xDEB5, 0xDEB5, 0xDEB5, 0xE6D6, 0x7BCC, 0x8C51, 0xDEDB, 0xD6BA, 0xA514, 0xCE79,   // 0x00D0 (208) pixels
		0xDEFB, 0xC638, 0xC638, 0xDEDB, 0xCE59, 0xAD55, 0xD6BA, 0xD6BA, 0x8C51, 0x738B, 0xDE95, 0xDEB5, 0xDEB5, 0xDE95, 0x7BAB, 0xCE4F,   // 0x00E0 (224) pixels
		0xE716, 0x9492, 0x632C, 0xADF9, 0xCE38, 0xC5D6, 0xC5D6, 0xCE38, 0xA5B8, 0x630C, 0x9CD3, 0xE737, 0xCE4F, 0x73AA, 0xDE95, 0xDEB5,   // 0x00F0 (240) pixels
		0xE6D6, 0xAD51, 0x8429, 0xFFF0, 0xD6AE, 0x4A47, 0x426A, 0x23FA, 0x6B4D, 0x8349, 0x8329, 0x6B4D, 0x23FA, 0x424A, 0x4A27, 0xEF50,   // 0x0100 (256) pixels
		0xFFD0, 0x7387, 0xB572, 0xE6D6, 0xDEB5, 0xD674, 0x946D, 0x9489, 0x842A, 0x6309, 0x1291, 0x13DB, 0x1B97, 0x1335, 0x1B76, 0x1B97,   // 0x0110 (272) pixels
		0x13DB, 0x1291, 0x2123, 0x7BC9, 0x9489, 0x946D, 0xDE95, 0xDEB5, 0xDE95, 0xDEB5, 0xDE95, 0x948E, 0xC5D2, 0x8C2D, 0x1B56, 0x2CBF,   // 0x0120 (288) pixels
		0x24BF, 0x13DB, 0x247E, 0x24BF, 0x2CBF, 0x1B56, 0x8C2D, 0xBDB2, 0x946E, 0xDE95, 0xDEB5, 0xDEB5, 0xD654, 0xD654, 0xDE95, 0xE6D6,   // 0x0130 (304) pixels
		0xE6D6, 0x83EC, 0x1B57, 0x2CDF, 0x2CBF, 0x0AF4, 0x12F5, 0x2CBF, 0x2CDF, 0x1B57, 0x8C0D, 0xDE95, 0xD674, 0xDE95, 0xDEB5, 0xDEB5,   // 0x0140 (320) pixels
		0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xE6F6, 0x8C2D, 0x1315, 0x1C9F, 0x1378, 0x6B8D, 0x6B8D, 0x1378, 0x1C9F, 0x1315, 0x8C2D, 0xE6F6,   // 0x0150 (336) pixels
		0xDEB5, 0xDEB5, 0xDE95, 0xDE95, 0xDEB5, 0xDEB5, 0xD654, 0xD674, 0xCE33, 0x736B, 0x530D, 0x4B50, 0x2A0B, 0x944D, 0x944E, 0x3ACE,   // 0x0160 (352) pixels
		0x5370, 0x42AC, 0x62E9, 0xC5F3, 0xD674, 0xDEB5, 0xD674, 0xD654, 0xDEB5, 0xDEB5, 0xDE95, 0xCE13, 0x734A, 0x8B8A, 0xA388, 0x9B68,   // 0x0170 (368) pixels
		0x5206, 0x840C, 0x840D, 0x7B29, 0xA388, 0x9B68, 0x7AC6, 0x7309, 0xCE13, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xDEB5, 0xE6D6, 0xA4CF,   // 0x0180 (384) pixels
		0x28E2, 0x4183, 0x4163, 0x4163, 0x20C2, 0x8C4D, 0x8C4D, 0x28E2, 0x4163, 0x4163, 0x4183, 0x28E2, 0xA4CF, 0xE6D6, 0xDEB5, 0xDEB5,   // 0x0190 (400) pixels
	}
};









typedef struct{
    uint8_t x;
    uint8_t y;
    uint8_t active;
} Box;


Box boxList[5];
uint8_t gameBoxAmount;

uint8_t currentLevelIndex;
uint8_t currentLevelWidth;
uint8_t currentLevelHeight;

uint8_t offsetMap[2] = {0, 0};

uint16_t currentMovementCount;

uint8_t playerX, playerY;


uint8_t movementDirection = 0;
uint8_t keyPressed = 0;
uint8_t keyLocked = 0;
uint8_t isMenuMode = 1;

// 0 -- void
// 1 -- brick
// 2 -- back
// 3 -- back w/ dot
// 4 -- box
// 5 -- box dark
// 6 -- player

uint8_t level19[8][9] = {
	{1,1,1,1,1,1,1,0,0},
	{1,2,2,2,2,2,1,1,1},
	{1,2,2,6,4,4,3,3,1},
	{1,1,1,1,2,1,1,2,1},
	{0,0,1,2,2,2,2,2,1},
	{0,0,1,2,2,1,1,1,1},
	{0,0,1,2,2,1,0,0,0},
	{0,0,1,1,1,1,0,0,0}
};

uint8_t level18[8][8] = {
	{1,1,1,1,1,1,1,1},
	{1,2,2,2,3,3,2,1},
	{1,2,2,6,4,4,2,1},
	{1,1,1,1,1,2,1,1},
	{0,0,0,1,2,2,1,0},
	{0,0,0,1,2,2,1,0},
	{0,0,0,1,2,2,1,0},
	{0,0,0,1,1,1,1,0}
};

uint8_t level17[9][7] = {
	{1,1,1,1,1,1,1},
	{1,2,2,2,2,2,1},
	{1,3,2,3,2,2,1},
	{1,2,1,1,2,1,1},
	{1,2,2,4,2,1,0},
	{1,1,1,4,2,1,0},
	{0,0,1,6,2,1,0},
	{0,0,1,2,2,1,0},
	{0,0,1,1,1,1,0}
};

uint8_t level16[7][6] = {
	{1,1,1,1,1,0},
	{1,2,6,2,1,0},
	{1,3,3,3,1,0},
	{1,4,4,4,1,1},
	{1,2,2,2,2,1},
	{1,2,2,2,2,1},
	{1,1,1,1,1,1}
};


uint8_t level15[8][10] = {
	{0,1,1,1,1,0,0,0,0,0},
	{0,1,2,2,1,1,1,1,0,0},
	{0,1,2,2,2,2,2,1,1,0},
	{1,1,2,1,1,2,2,2,1,0},
	{1,3,2,3,1,2,6,4,1,1},
	{1,2,2,2,1,2,4,4,2,1},
	{1,2,2,3,1,2,2,2,2,1},
	{1,1,1,1,1,1,1,1,1,1}
};


uint8_t level14[7][9] = {
	{0,0,0,0,0,1,1,1,0},
	{1,1,1,1,1,1,6,1,1},
	{1,2,2,2,2,3,5,2,1},
	{1,2,2,2,1,2,2,2,1},
	{1,1,1,1,1,4,1,2,1},
	{0,0,0,0,1,2,2,2,1},
	{0,0,0,0,1,1,1,1,1}
};

uint8_t level13[6][7] = {
	{1,1,1,1,1,1,1},
	{1,2,2,2,2,2,1},
	{1,2,1,2,1,2,1},
	{1,3,2,4,5,6,1},
	{1,2,2,2,1,1,1},
	{1,1,1,1,1,0,0}
};


uint8_t level12[9][7] = {
	{1,1,1,1,0,0,0},
	{1,3,2,1,1,0,0},
	{1,3,6,2,1,0,0},
	{1,3,2,4,1,0,0},
	{1,1,4,2,1,1,1},
	{0,1,2,4,2,2,1},
	{0,1,2,2,2,2,1},
	{0,1,2,2,1,1,1},
	{0,1,1,1,1,0,0}
};


uint8_t level11[8][9] = {
	{1,1,1,1,1,0,0,0,0},
	{1,2,2,2,1,1,0,0,0},
	{1,2,4,2,2,1,0,0,0},
	{1,1,2,4,2,1,1,1,1},
	{0,1,1,1,6,3,2,2,1},
	{0,0,1,2,2,3,1,2,1},
	{0,0,1,2,2,2,2,2,1},
	{0,0,1,1,1,1,1,1,1}
};


uint8_t level10[9][9] = {
	{0,0,1,1,1,1,1,1,0},
	{0,0,1,2,2,2,2,1,0},
	{0,0,1,2,2,2,2,1,0},
	{0,0,1,2,1,1,6,1,1},
	{1,1,1,2,1,2,4,2,1},
	{1,2,3,3,1,2,4,2,1},
	{1,2,2,2,2,2,2,2,1},
	{1,2,2,1,1,1,1,1,1},
	{1,1,1,1,0,0,0,0,0}
};

uint8_t level9[8][11] = {
	{0,0,0,0,0,0,1,1,1,1,1},
	{0,0,0,0,0,0,1,3,2,2,1},
	{0,0,0,0,0,0,1,3,1,2,1},
	{1,1,1,1,1,1,1,3,1,2,1},
	{1,2,6,2,4,2,4,2,4,2,1},
	{1,2,1,2,1,2,1,2,1,1,1},
	{1,2,2,2,2,2,2,2,1,0,0},
	{1,1,1,1,1,1,1,1,1,0,0}
};

uint8_t level8[7][6] = {
	{1,1,1,1,1,0},
	{1,3,2,2,1,1},
	{1,6,4,4,2,1},
	{1,1,2,2,2,1},
	{0,1,1,2,2,1},
	{0,0,1,1,3,1},
	{0,0,0,1,1,1}
};


uint8_t level7[12][8] = {
	{0,0,1,1,1,1,1,1},
	{0,0,1,2,3,3,6,1},
	{0,0,1,2,4,4,2,1},
	{0,0,1,1,2,1,1,1},
	{0,0,0,1,2,1,0,0},
	{0,0,0,1,2,1,0,0},
	{1,1,1,1,2,1,0,0},
	{1,2,2,2,2,1,1,0},
	{1,2,1,2,2,2,1,0},
	{1,2,2,2,1,2,1,0},
	{1,1,1,2,2,2,1,0},
	{0,0,1,1,1,1,1,0}
};


uint8_t level6[8][7] = {
	{1,1,1,1,1,1,1},
	{1,2,2,2,2,2,1},
	{1,2,3,4,3,2,1},
	{1,2,4,3,4,2,1},
	{1,2,3,4,3,2,1},
	{1,2,4,3,4,2,1},
	{1,2,2,6,2,2,1},
	{1,1,1,1,1,1,1},
};


uint8_t level5[6][12] = {
	{1,1,1,1,1,1,0,1,1,1,1,1},
	{1,2,2,2,2,1,1,1,2,2,2,1},
	{1,2,4,4,2,2,2,2,2,1,6,1},
	{1,2,4,2,1,3,3,3,2,2,2,1},
	{1,2,2,2,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,0,0,0,0,0,0,0}
};


uint8_t level4[7][8] = {
	{0,1,1,1,1,1,1,1},
	{0,1,2,2,2,2,2,1},
	{0,1,2,3,4,3,2,1},
	{1,1,2,4,6,4,2,1},
	{1,2,2,3,4,3,2,1},
	{1,2,2,2,2,2,2,1},
	{1,1,1,1,1,1,1,1}
};


uint8_t level3[6][8] = {
	{1,1,1,1,1,1,1,1},
	{1,2,2,2,2,2,2,1},
	{1,2,3,5,5,4,6,1},
	{1,2,2,2,2,2,2,1},
	{1,1,1,1,1,2,2,1},
	{0,0,0,0,1,1,1,1}
};


uint8_t level2[6][9] = {
	{0,0,1,1,1,1,0,0,0},
	{1,1,1,2,2,1,1,1,1},
	{1,2,2,2,2,2,4,2,1},
	{1,2,1,2,2,1,4,2,1},
	{1,2,3,2,3,1,6,2,1},
	{1,1,1,1,1,1,1,1,1}
};


uint8_t level1[7][6] = {
	{1,1,1,1,1,1},
	{1,2,2,2,2,1},
	{1,2,1,6,2,1},
	{1,2,4,5,2,1},
	{1,2,3,5,2,1},
	{1,2,2,2,2,1},
	{1,1,1,1,1,1}
};


uint8_t level0[7][6] = {
	{1,1,1,1,0,0},
	{1,2,3,1,0,0},
	{1,2,2,1,1,1},
	{1,5,6,2,2,1},
	{1,2,2,4,2,1},
	{1,2,2,1,1,1},
	{1,1,1,1,0,0}
};




uint8_t *getAddress(uint8_t item) {

    if (item == 0) {
        return (void*)level0;
    }
    if (item == 1) {
        return (void*)level1;
    }
    if (item == 2) {
		return (void*)level2;
	}
    if (item == 3) {
		return (void*)level3;
	}
    if (item == 4) {
		return (void*)level4;
	}
    if (item == 5) {
		return (void*)level5;
	}
    if (item == 6) {
		return (void*)level6;
	}
    if (item == 7) {
		return (void*)level7;
	}
	if (item == 8) {
		return (void*)level8;
	}
	if (item == 9) {
		return (void*)level9;
	}
	if (item == 10) {
		return (void*)level10;
	}
	if (item == 11) {
		return (void*)level11;
	}
	if (item == 12) {
		return (void*)level12;
	}
	if (item == 13) {
		return (void*)level13;
	}
	if (item == 14) {
		return (void*)level14;
	}
	if (item == 15) {
		return (void*)level15;
	}
	if (item == 16) {
		return (void*)level16;
	}
	if (item == 17) {
		return (void*)level17;
	}
	if (item == 18) {
		return (void*)level18;
	}
	if (item == 19) {
		return (void*)level19;
	}
    return NULL;
}



void generateLevel(uint8_t w, uint8_t h, uint8_t arr[h][w]){

	currentLevelWidth  	 = w;
	currentLevelHeight 	 = h;
    gameBoxAmount 		 = 0;
    currentMovementCount = 0;

    offsetMap[0] = (240 - 20*w) / 2; // offsetX
    offsetMap[1] = (240 - 20*h) / 2; // offsetY

    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
            uint8_t value = arr[y][x];

            if ( arr[y][x] == 6 ){
                playerX = x;
                playerY = y;
            }

            if ( gameBoxAmount < 5 && (value == 4 || value == 5) ){
                boxList[gameBoxAmount].active = value == 5;
                boxList[gameBoxAmount].x = x;
                boxList[gameBoxAmount].y = y;
                gameBoxAmount++;
            }

            if ( value != 0 ){
            	renderBitmap(20*x+offsetMap[0], 20*y+offsetMap[1], 20, 20, spriteList[value-1]);
            }

        }

    }

}



void generateLevelByIndex(uint8_t levelIndex){

	if ( levelIndex == 0 ){
		generateLevel(6, 7, level0);
		return;
	}
	if ( levelIndex == 1 ){
		generateLevel(6, 7, level1);
		return;
	}
	if ( levelIndex == 2 ){
		generateLevel(9, 6, level2);
		return;
	}
	if ( levelIndex == 3 ){
		generateLevel(8, 6, level3);
		return;
	}
	if ( levelIndex == 4 ){
		generateLevel(8, 7, level4);
		return;
	}
	if ( levelIndex == 5 ){
		generateLevel(12, 6, level5);
		return;
	}
	if ( levelIndex == 6 ){
		generateLevel(7, 8, level6);
		return;
	}
	if ( levelIndex == 7 ){
		generateLevel(8, 12, level7);
		return;
	}
	if ( levelIndex == 8 ){
		generateLevel(6, 7, level8);
		return;
	}
	if ( levelIndex == 9 ){
		generateLevel(11, 8, level9);
		return;
	}
	if ( levelIndex == 10 ){
		generateLevel(9, 9, level10);
		return;
	}
	if ( levelIndex == 11 ){
		generateLevel(9, 8, level11);
		return;
	}
	if ( levelIndex == 12 ){
		generateLevel(7, 9, level12);
		return;
	}
	if ( levelIndex == 13 ){
		generateLevel(7, 6, level13);
		return;
	}
	if ( levelIndex == 14 ){
		generateLevel(9, 7, level14);
		return;
	}
	if ( levelIndex == 15 ){
		generateLevel(10, 8, level15);
		return;
	}
	if ( levelIndex == 16 ){
		generateLevel(6, 7, level16);
		return;
	}
	if ( levelIndex == 17 ){
		generateLevel(7, 9, level17);
		return;
	}
	if ( levelIndex == 18 ){
		generateLevel(8, 8, level18);
		return;
	}
	if ( levelIndex == 19 ){
		generateLevel(9, 8, level19);
		return;
	}


}





int8_t hasBoxAt(uint8_t x, uint8_t y){
	for (uint8_t boxIndex = 0; boxIndex < gameBoxAmount; boxIndex++){
		if ( boxList[boxIndex].x == x && boxList[boxIndex].y == y ){
			return boxIndex;
		}
	}
	return -1;
}



void updateBox(uint8_t levelIndex){
	for (uint8_t boxIndex = 0; boxIndex < gameBoxAmount; boxIndex++){
		uint8_t (*mapa)[currentLevelHeight][currentLevelWidth] = (uint8_t (*)[currentLevelHeight][currentLevelWidth]) getAddress(currentLevelIndex);
		boxList[boxIndex].active = ((*mapa)[boxList[boxIndex].y][boxList[boxIndex].x] == 3 || (*mapa)[boxList[boxIndex].y][boxList[boxIndex].x] == 5);
		renderBitmap(20*boxList[boxIndex].x+offsetMap[0], 20*boxList[boxIndex].y+offsetMap[1], 20, 20, spriteList[3 + boxList[boxIndex].active]);
	}
}




uint8_t gameWin(){

	uint8_t (*mapa)[currentLevelHeight][currentLevelWidth] = (uint8_t (*)[currentLevelHeight][currentLevelWidth]) getAddress(currentLevelIndex);

	for (uint8_t boxIndex = 0; boxIndex < gameBoxAmount; boxIndex++){
		uint8_t box_x = boxList[boxIndex].x;
		uint8_t box_y = boxList[boxIndex].y;

		if ( (*mapa)[box_y][box_x] != 3 && (*mapa)[box_y][box_x] != 5 ){
			return 0;
		}
	}

	return 1;

}





void showSummary(){
	char text[10];
	sprintf(text, "Moves: %i", currentMovementCount);
	tft_fillRect(0, 0, 240, 240, 0x0000);
	tft_drawText(30, 108, text, 0xFFFF, 0x0000, 3);
}


void showCurrentLevel(){
	char text[9];
	sprintf(text, "Level: %i", currentLevelIndex+1);
	tft_fillRect(0, 0, 240, 240, 0x0000);
	tft_drawText(39, 108, text, 0xFFFF, 0x0000, 3);
}



void showMenu(){
	char text[6];
	sprintf(text, "< %2i >", currentLevelIndex+1);
	tft_drawText(30, 100, text, 0xFFFF, 0x0000, 5);
}





// 1 -- UP
// 2 -- DOWN
// 3 -- LEFT
// 4 -- RIGHT

void updateLevel(uint8_t direction){

	updateBox(currentLevelIndex);

	uint8_t (*mapa)[currentLevelHeight][currentLevelWidth] = (uint8_t (*)[currentLevelHeight][currentLevelWidth]) getAddress(currentLevelIndex);



	if ( (*mapa)[playerY][playerX] == 3 || (*mapa)[playerY][playerX] == 5 ){
		renderBitmap(20*playerX+offsetMap[0], 20*playerY+offsetMap[1], 20, 20, spriteList[2]);
	}else{
		renderBitmap(20*playerX+offsetMap[0], 20*playerY+offsetMap[1], 20, 20, spriteList[1]);
	}



	// UP
	if ( direction == 1 ){

		int8_t boxIndex = hasBoxAt(playerX, playerY-1);

		if ( playerY > 0 ){
			if ( boxIndex == -1 ){
				if ( (*mapa)[playerY-1][playerX] > 1 ){
					playerY--;
					currentMovementCount++;
				}
			}else if ( playerY >= 3 ){
				if ( boxIndex >= 0 && hasBoxAt(playerX, playerY-2) == -1 && (*mapa)[playerY-2][playerX] > 1 ){
					boxList[boxIndex].y--;
					playerY--;
					currentMovementCount++;
				}
			}
		}

	}



	// DOWN
	else if ( direction == 2 ){
		int8_t boxIndex = hasBoxAt(playerX, playerY+1);

		if ( playerY < currentLevelHeight-1 ){
			if ( boxIndex == -1 ){
				if ( (*mapa)[playerY+1][playerX] > 1 ){
					playerY++;
					currentMovementCount++;
				}
			}else if ( playerY < currentLevelHeight-2-1 ){
				if ( boxIndex >= 0 && hasBoxAt(playerX, playerY+2) == -1 && (*mapa)[playerY+2][playerX] > 1 ){
					boxList[boxIndex].y++;
					playerY++;
					currentMovementCount++;
				}
			}
		}
	}



	// LEFT
	else if ( direction == 3 ){

		int8_t boxIndex = hasBoxAt(playerX-1, playerY);

		if ( playerX > 0 ){
			if ( boxIndex == -1 ){
				if ( (*mapa)[playerY][playerX-1] > 1 ){
					playerX--;
					currentMovementCount++;
				}
			}else if ( playerX >= 3 ){
				if ( boxIndex >= 0 && hasBoxAt(playerX-2, playerY) == -1 && (*mapa)[playerY][playerX-2] > 1 ){
					boxList[boxIndex].x--;
					playerX--;
					currentMovementCount++;
				}
			}
		}

	}



	// RIGHT
	else if ( direction == 4 ){

		int8_t boxIndex = hasBoxAt(playerX+1, playerY);

		if ( playerX < currentLevelWidth-1 ){
			if ( boxIndex == -1 ){
				if ( (*mapa)[playerY][playerX+1] > 1 ){
					playerX++;
					currentMovementCount++;
				}
			}else if ( playerX < currentLevelWidth-2-1 ){
				if ( boxIndex >= 0 && hasBoxAt(playerX+2, playerY) == -1 && (*mapa)[playerY][playerX+2] > 1 ){
					boxList[boxIndex].x++;
					playerX++;
					currentMovementCount++;
				}
			}
		}

	}





	// UPDATE
	updateBox(currentLevelIndex);
	renderBitmap(20*playerX+offsetMap[0], 20*playerY+offsetMap[1], 20, 20, spriteList[5]);


}



#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */


  /*uint8_t buffer[3] = {0x37, 0xA0, 0xF5};
  HAL_SPI_Transmit(&hspi1, buffer, 3, 1000);*/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // SCK LOW STATE
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);


  //HAL_UART_Transmit(&huart2, (uint8_t *)"INIT", 4, 1000);

  printf("INIT\r\n");





  tft_init();




  //currentSpeed = 0;


  // black screen


  tft_fillRect(0, 0, 240, 240, 0x0000);
  showMenu();


  //tft_fillRect(0, 0, 240, 240, 0x0000);
  //generateLevelByIndex(currentLevelIndex);

  //printf("boxQTY:%i\r\n", gameBoxAmount);

	/*for (uint8_t boxIndex = 0; boxIndex < gameBoxAmount; boxIndex++){
		printf("%i=%i,%i\r\n", boxIndex, boxList[boxIndex].x, boxList[boxIndex].y);
	}*/









  //setSpeed2(currentSpeed);

  while (1){

	//currentSpeed += 0.1;

	/*if ( currentSpeed > 100 ){
	  currentSpeed = 0;
	}*/


	// center
	//tft_drawFastHLine(0, 240/2, 240, tft_color565(255, 0, 255) );
	//tft_drawFastVLine(240/2, 0, 240, tft_color565(255, 0, 255) );

	if ( !keyLocked ){

		if ( !HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin) ){
			if ( !keyPressed ){
				keyPressed = 1;
				movementDirection = 1;
				HAL_Delay(5);
			}
		}else if ( !HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin) ){
			if ( !keyPressed ){
				keyPressed = 1;
				movementDirection = 2;
				HAL_Delay(5);
			}
		}else if ( !HAL_GPIO_ReadPin(KEY_LEFT_GPIO_Port, KEY_LEFT_Pin) ){
			if ( !keyPressed ){
				keyPressed = 1;
				movementDirection = 3;
				HAL_Delay(5);
			}
		}else if ( !HAL_GPIO_ReadPin(KEY_RIGHT_GPIO_Port, KEY_RIGHT_Pin) ){
			if ( !keyPressed ){
				keyPressed = 1;
				movementDirection = 4;
				HAL_Delay(5);
			}
		}
		else if ( !HAL_GPIO_ReadPin(KEY_ENTER_GPIO_Port, KEY_ENTER_Pin) ){
			if ( !keyPressed ){
				keyPressed = 1;

				if ( isMenuMode ){
					tft_fillRect(0, 0, 240, 240, 0x0000);
					generateLevelByIndex(currentLevelIndex);
				}else{
					tft_fillRect(0, 0, 240, 240, 0x0000);
					showMenu();
				}
				isMenuMode = !isMenuMode;


				HAL_Delay(5);
			}
		}else if ( !HAL_GPIO_ReadPin(KEY_RESTART_GPIO_Port, KEY_RESTART_Pin) ){
			if ( !keyPressed ){
				keyPressed = 1;
				if ( !isMenuMode ){
					tft_fillRect(0, 0, 240, 240, 0x0000);
					generateLevelByIndex(currentLevelIndex);
				}
				HAL_Delay(5);
			}
		}

		else{
			movementDirection = 0;
			keyPressed = 0;
		}

	}




	if ( movementDirection != 0 ){

		if ( isMenuMode ){

			if ( movementDirection == 3 ){
				if (currentLevelIndex > 0){
					currentLevelIndex--;
					showMenu();
				}else{
					currentLevelIndex = 20 - 1;
				}
			}else if ( movementDirection == 4 ){
				currentLevelIndex = (currentLevelIndex + 1) % 20;
				showMenu();
			}
			movementDirection = 0;
			continue;
		}



		updateLevel(movementDirection);

		if ( gameWin() ){
			keyLocked = 1;
			keyPressed = 0;

			showSummary();
			HAL_Delay(1000);

			currentLevelIndex = (currentLevelIndex + 1) % 20;
			if ( currentLevelIndex == 0 ){
				tft_drawText(30, 100, "END :)", 0xFFFF, 0x0000, 5);
				HAL_Delay(1000);
				isMenuMode = 1;
				tft_fillRect(0, 0, 240, 240, 0x0000);
				showMenu();
			}else{
				showCurrentLevel();
				HAL_Delay(1000);
				tft_fillRect(0, 0, 240, 240, 0x0000);
				generateLevelByIndex(currentLevelIndex);
			}


			keyLocked = 0;
		}

		movementDirection = 0;
	}



	//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }



  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_RESET_Pin|LCD_DC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RESET_Pin LCD_DC_Pin */
  GPIO_InitStruct.Pin = LCD_RESET_Pin|LCD_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : KEY_UP_Pin KEY_DOWN_Pin KEY_LEFT_Pin KEY_RIGHT_Pin
                           KEY_ENTER_Pin KEY_RESTART_Pin */
  GPIO_InitStruct.Pin = KEY_UP_Pin|KEY_DOWN_Pin|KEY_LEFT_Pin|KEY_RIGHT_Pin
                          |KEY_ENTER_Pin|KEY_RESTART_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
