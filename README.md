# Guidance of 128x64 SPI OLEDscreen migration based on stm32f4xx

128x64 OLED SPI 0.96" Display
=============================
_2023/5/27 from cyc
___
You can see four files: 
>oled.c
>oled.h
>bmp.h
>oledfont.h

To use it properly you need to 
### Physicial wiring
```
Screen | label_name |  PCB_Silkscreen
  GND --> GND      --> GND
  VCC --> 3.3V     --> 3V3
  DO  --> SPI_SCK  --> SCL
  D1  --> SPI_MOSI --> SDA
  RES --> OLED_RES --> RES
  DC  --> OLED_DC  --> DC
  CS  --> OLED_CS  --> CS
* label_name is configuration in cubeMX
* PCB label is designed on extern board of f407 by zq
```
### Pin configuration
- In cubeMX you need to configure **SPI1** as below                                       
  > Mode: **Transmit only Master**

  Confirm the default settings:                       
  >  Hardware Nss Signal: Disable                        
     Data Size: 8Bits                                  
     First Bit: MSB First                              
     CPOL: Low                                         
     CPHA: 1 Edge

- For the extern board of f407 designed by zq, pin configuration is as below
  ```
  PB0: output,  label: OLED_DC
  PB1: output,  label: OLED_RES
  NA   output,  label: OLED_CS
  ```
  Silkscreen of CS is suspend, so you need an extra line to GPIO and configure it as CS
### Program implantation
- Add **oled.c** to your project in keil (Application / User / Core), Don't forget to **check** ok & close
- Move these files to your project folder and add the **path** in Keil (Options for Target/ C/C++/Include Paths)
- Add below code
  ```c
  /* USER CODE BEGIN Includes */
  #include "oled.h"
  /* USER CODE END Includes */
   ```
- Add below code to **main.h** file
  hspi1 is the SPI handler, number is up to your configuration
  ```c
  /* USER CODE BEGIN Private defines */
  extern SPI_HandleTypeDef hspi1; 
  /* USER CODE END Private defines */
  ```
  
- Initialization	
  ```c
  OLED_Init();
  OLED_Clear();
  OLED_DisPlay_On();
  your function
  
  OLED_Refresh();
  ```
