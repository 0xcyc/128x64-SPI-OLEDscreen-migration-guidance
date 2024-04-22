#ifndef __OLED_H
#define __OLED_H 

#include "main.h"
#include "stm32f4xx_hal.h"
#include "stdlib.h"
#include "stdio.h"

extern SPI_HandleTypeDef hspi2;

//定义亮度变量类型
typedef enum{
LIGHT_HIGH=1,
LIGHT_MID,
LIGHT_LOW,
}LIGHT_LEVEL;
//-----------------OLED端口定义---------------- 

extern unsigned char BMP1[];

#define OLED_RES_Clr() HAL_GPIO_WritePin(OLED_RES_GPIO_Port,OLED_RES_Pin,GPIO_PIN_RESET)//RES
#define OLED_RES_Set() HAL_GPIO_WritePin(OLED_RES_GPIO_Port,OLED_RES_Pin,GPIO_PIN_SET)

#define OLED_DC_Clr() HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,GPIO_PIN_RESET)//DC
#define OLED_DC_Set() HAL_GPIO_WritePin(OLED_DC_GPIO_Port,OLED_DC_Pin,GPIO_PIN_SET)

#define OLED_CS_Clr()  HAL_GPIO_WritePin(OLED_CS_GPIO_Port,OLED_CS_Pin,GPIO_PIN_RESET)//CS
#define OLED_CS_Set()  HAL_GPIO_WritePin(OLED_CS_GPIO_Port,OLED_CS_Pin,GPIO_PIN_SET)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define uint8_t unsigned char
#define uint32_t unsigned int
#define WHICH_SPI &hspi1//根据使用的SPI更改

void OLED_ClearPoint(uint8_t x,uint8_t y);
void OLED_ColorTurn(uint8_t i);
void OLED_DisplayTurn(uint8_t i);
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y);
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
//void OLED_DrawSquare(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1);
void OLED_ShowStringPro(uint8_t x,uint8_t y,char* chr,uint8_t size1);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1);
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1);
void OLED_ScrollDisplay(uint8_t y,uint8_t num,uint8_t space,uint32_t timess,uint8_t infinit);
void OLED_WR_BP(uint8_t x,uint8_t y);
void OLED_ShowPic(uint8_t xmin,uint8_t ymin,uint8_t xmax,uint8_t ymax,uint8_t BMP[]);
void OLED_Printf(uint8_t str[]);
void zhunxing(void);
void OLED_Init(void);
void OLED_Clearlist(uint8_t n,uint8_t p);
void OLED_ShowData_String(uint8_t x, uint8_t y,uint8_t char_size ,const char* fmt,...);

void OLED_show_light(uint32_t light_level);
void OLED_ShowChinese_Sentence(uint8_t x,uint8_t y,uint32_t BEGIN,uint32_t END,uint8_t SIZE);

void OLED_inShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1);
void OLED_inShowStringPro(uint8_t x,uint8_t y,char* chr,uint8_t size1);
void OLED_inShowData_String(uint8_t x, uint8_t y,uint8_t char_size ,const char* fmt,...);

void OLED_DrawSquare(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t rev,uint8_t solid,uint8_t line_width);

#endif
