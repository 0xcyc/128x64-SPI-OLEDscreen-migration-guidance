/*********************************************************
*   ���Ŷ��壺                                         
*   OLED_CS OLED_RES OLED_DC OUTPUT    Output push pull
*********************************************************
*   SPI���壺                                          
*   Mode:Transmit only Master                          
*   Hardware Nss Signal:Disable                        
*   Data Size : 8Bits                                  
*   First Bit : MSB First                              
*   CPOL : Low                                         
*   CPHA : 1 Edge	 
*********************************************************
*   ���ߣ�                                             
*   GND ---> GND                                       
*   VCC ---> 3.3V                                      
*   DO  ---> SPI_SCK                                   
*   D1  ---> SPI_MOSI                                  
*   RES ---> OLED_RES                                  
*   DC  ---> OLED_DC                                   
*   CS  ---> OLED_CS                                   
*
*********************************************************
2023/4/1		�Ż��˻�Բ���㷨����Բ����
2023/4/6		�Ż��˻����κ�������֪��ΪʲôҪ+1
2023/4/6		�������¶���ʾ����ShowTemp()
Ŀǰ�����Ƿ��ģ����Ծ����ҷ�����ʾ��
2023/4/19 	�����˷�ɫ��ʾ����
*/ 

/********************************************************/
#include "oled.h"
#include "oledfont.h"
#include "stdio.h"
#include "main.h"
#include "bmp.h"
#include <string.h>
#include <stdarg.h>
uint8_t OLED_GRAM[128][8];
 
 


//����������ʾ(Modified)
//(�����꣬�����꣬�ֿ⿪ʼ���꣬�ֿ���ֹ���꣬�ֺŴ�С)
void OLED_ShowChinese_Sentence(uint8_t x,uint8_t y,uint32_t BEGIN,uint32_t END,uint8_t SIZE){
   for(int i=BEGIN;i<=END;i++){
   OLED_ShowChinese(x,y,i,SIZE);
   x+=SIZE;
   if(x>120){
   x=1,y+=2;
   }
   }
}

//��������(ssd1309�У����ȵ���û����)
void OLED_show_light(uint32_t light_level){
OLED_WR_Byte(0x81,OLED_CMD);
OLED_WR_Byte(light_level ,OLED_CMD); //���ȵ��� 0x00~0xff (0~255) 80|160|240
	OLED_Refresh();
} 
//ˢ��ʱ�ӻ�(Modified)
//void OLED_Cleartime(uint8_t n,uint8_t p)
//{
//	uint8_t i;
//	OLED_GRAM[p][2]=0xfe;
//	OLED_GRAM[p-1][2]=0x02;
//	OLED_GRAM[p][7]=0xff;
//	OLED_GRAM[p-1][7]=0x80;
//	for(i=3;i<7;i++)
//	{
//    for(uint8_t s=n;s!=p+1;s++)
//			 OLED_GRAM[s][i]=0;//�����������
//		OLED_GRAM[p][i]=0xff;
//  }
//	OLED_Refresh();
////	for(s=0;s<8;s++)
////	{
////	   OLED_WR_Byte(0xb0+s,OLED_CMD); //��������ʼ��ַ
////	   OLED_WR_Byte(0x00,OLED_CMD);   //���õ�����ʼ��ַ
////	   OLED_WR_Byte(0x10,OLED_CMD);   //���ø�����ʼ��ַ
////	   for(t=n-1;t<p+1;t++)
////		 OLED_WR_Byte(OLED_GRAM[t][s],OLED_DATA);
////  }//������ʾ
//}
/*******************ʾ����ר�ú���-ˢ������(Modified)*********************/
void OLED_Clearlist(uint8_t n,uint8_t p)
{
	uint8_t i;
	OLED_GRAM[p][2]=0xfe;
	OLED_GRAM[p-1][2]=0x02;
	OLED_GRAM[p][7]=0xff;
	OLED_GRAM[p-1][7]=0x80;
	for(i=3;i<7;i++)
	{
    for(uint8_t s=n;s!=p+1;s++)
			 OLED_GRAM[s][i]=0;//�����������
		OLED_GRAM[p][i]=0xff;
  }
	OLED_Refresh();
	for(uint8_t s=0;s<8;s++)
	{
	   OLED_WR_Byte(0xb0+s,OLED_CMD); //��������ʼ��ַ
	   OLED_WR_Byte(0x00,OLED_CMD);   //���õ�����ʼ��ַ
	   OLED_WR_Byte(0x10,OLED_CMD);   //���ø�����ʼ��ַ
	   for(uint8_t t=n-1;t!= p+1;t++)
		 OLED_WR_Byte(OLED_GRAM[t][s],OLED_DATA);
  }//������ʾ
}
/***********END**************/
//printf(Modified)
void OLED_ShowData_String(uint8_t x, uint8_t y,uint8_t char_size ,const char* fmt,...){
	x-=1,y-=1;//ת���ɴ�1����
 //�ַ���ת��	
 //�ַ����洢���飬������һ��
	 char Display[50];             
 //��ʽת����
	 va_list BEGIN;  
	 va_start(BEGIN,fmt);  
	 vsprintf(Display,fmt,BEGIN);  
	 va_end(BEGIN);
 //ת��Ϊ�ַ�����ʾ	
	OLED_ShowStringPro(x,y,Display,char_size);
}


void OLED_inShowData_String(uint8_t x, uint8_t y,uint8_t char_size ,const char* fmt,...){
	x-=1,y-=1;//ת���ɴ�1����
 //�ַ���ת��	
 //�ַ����洢���飬������һ��
	 char Display[50];             
 //��ʽת����
	 va_list BEGIN;  
	 va_start(BEGIN,fmt);  
	 vsprintf(Display,fmt,BEGIN);  
	 va_end(BEGIN);
 //ת��Ϊ�ַ�����ʾ	
	OLED_inShowStringPro(x,y,Display,char_size);
}


//���Ժ���
void OLED_ColorTurn(uint8_t i)
{
	if(i==0)
		{
			OLED_WR_Byte(0xA6,OLED_CMD);//������ʾ
		}
	if(i==1)
		{
			OLED_WR_Byte(0xA7,OLED_CMD);//��ɫ��ʾ
		}
}
 
//��Ļ��ת180��
void OLED_DisplayTurn(uint8_t i)
{
	if(i==0)
		{
			OLED_WR_Byte(0xC8,OLED_CMD);//������ʾ
			OLED_WR_Byte(0xA1,OLED_CMD);
		}
	if(i==1)
		{
			OLED_WR_Byte(0xC0,OLED_CMD);//��ת��ʾ
			OLED_WR_Byte(0xA0,OLED_CMD);
		}
	if(i==2)
		{
			OLED_WR_Byte(0xC0,OLED_CMD);//��ת��ʾ
			OLED_WR_Byte(0xA1,OLED_CMD);
		}
}
 
 
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{	
	uint8_t * data = &dat;		  
	if(cmd)
	  OLED_DC_Set();
	else
	  OLED_DC_Clr();
	OLED_CS_Clr();
	
HAL_SPI_Transmit(WHICH_SPI,(uint8_t *)data,1,200); //�����ʵ������޸� 
	
	OLED_CS_Set();
	OLED_DC_Set();   	  
}
 
//����OLED��ʾ 
void OLED_DisPlay_On(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//��ɱ�ʹ��
	OLED_WR_Byte(0x14,OLED_CMD);//������ɱ�
	OLED_WR_Byte(0xAF,OLED_CMD);//������Ļ
}
 
//�ر�OLED��ʾ 
void OLED_DisPlay_Off(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//��ɱ�ʹ��
	OLED_WR_Byte(0x10,OLED_CMD);//�رյ�ɱ�
	OLED_WR_Byte(0xAF,OLED_CMD);//�ر���Ļ
}
 
//�����Դ浽OLED	
void OLED_Refresh(void)
{
	uint8_t i,n;
	for(i=0;i<8;i++)
	{
	   OLED_WR_Byte(0xb0+i,OLED_CMD); //��������ʼ��ַ
	   OLED_WR_Byte(0x00,OLED_CMD);   //���õ�����ʼ��ַ
	   OLED_WR_Byte(0x10,OLED_CMD);   //���ø�����ʼ��ַ
	   for(n=0;n<128;n++)
		 OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
  }
}
//��������
void OLED_Clear(void)
{
	uint8_t i,n;
	for(i=0;i<8;i++)
	{
	   for(n=0;n<128;n++)
			{
			 OLED_GRAM[n][i]=0;//�����������
			}
  }
	OLED_Refresh();//������ʾ
}
 
//���� ,��Ҫˢ���Դ�
//x:0~127
//y:0~63
void OLED_DrawPoint(uint8_t x,uint8_t y)
{
	uint8_t i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	OLED_GRAM[x][i]|=n;
}
 
//���һ����,��Ҫˢ���Դ棡
//x:0~127
//y:0~63
void OLED_ClearPoint(uint8_t x,uint8_t y)
{
	uint8_t i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	OLED_GRAM[x][i]=~OLED_GRAM[x][i];
	OLED_GRAM[x][i]|=n;
	OLED_GRAM[x][i]=~OLED_GRAM[x][i];
}
 
 
//����
//x:0~128
//y:0~64
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)
{
	uint8_t i,k,k1,k2;
	if((x2>128)||(y2>64)||(x1>x2)||(y1>y2))return;
	if(x1==x2)    //������
	{
			for(i=0;i<(y2-y1);i++)
			{
				OLED_DrawPoint(x1,y1+i);
			}
  }
	else if(y1==y2)   //������
	{
			for(i=0;i<(x2-x1);i++)
			{
				OLED_DrawPoint(x1+i,y1);
			}
  }
	else      //��б��
	{
		k1=y2-y1;
		k2=x2-x1;
		k=k1*10/k2;
		for(i=0;i<(x2-x1);i++)
			{
			  OLED_DrawPoint(x1+i,y1+i*k/10);
			}
	}
	OLED_Refresh();
}
//������;x:0~127 y:0~63
//x1,y1,���Ͻ����ꣻx2,y2,���½�����
void OLED_DrawSquare(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)
{
	OLED_DrawLine(x1,y1,x2,y1);
	OLED_DrawLine(x1,y2,x2,y2);
	OLED_DrawLine(x1,y1,x1,y2);
	OLED_DrawLine(x2,y1,x2,y2+1);
	OLED_Refresh();
}
//x,y:Բ������
//r:Բ�İ뾶
void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r)
{
	int a, b,num;
    a = 0;
    b = r;
    while(2 * b * b >= (r-1) * (r))      
    {
        OLED_DrawPoint(x + a, y - b);
        OLED_DrawPoint(x - a, y - b);
        OLED_DrawPoint(x - a, y + b);
        OLED_DrawPoint(x + a, y + b);
 
        OLED_DrawPoint(x + b, y + a);
        OLED_DrawPoint(x + b, y - a);
        OLED_DrawPoint(x - b, y - a);
        OLED_DrawPoint(x - b, y + a);
        
        a++;
        num = (a * a + b * b) - r*r- 4;//���㻭�ĵ���Բ�ĵľ���
        if(num > 0)
        {
            b--;
            
        }
    }
			OLED_Refresh();
}
 
 
 
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//size:ѡ������ 12/16/24
//ȡģ��ʽ ����ʽ
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1)
{
	uint8_t i,m,temp,size2,chr1;
	uint8_t y0=y;
	size2=(size1/8+((size1%8)?1:0))*(size1/2);  //�õ�����һ���ַ���Ӧ������ռ���ֽ���
	chr1=chr-' ';  //����ƫ�ƺ��ֵ
	for(i=0;i<size2;i++)
	{
		if(size1==12)
        {temp=asc2_1206[chr1][i];} //����12 06����
		else if(size1==16)
        {temp=asc2_1608[chr1][i];} //����16 08����
		else if(size1==24)
        {temp=asc2_2412[chr1][i];} //����24 12����
		else return;
				for(m=0;m<8;m++)           //д������
				{
					if(temp&0x80)OLED_DrawPoint(x,y);
					else OLED_ClearPoint(x,y);
					temp<<=1;
					y++;
					if((y-y0)==size1)
					{
						y=y0;
						x++;
						break;
          }
				}
  }
		OLED_Refresh();
}


void OLED_inShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1)
{
	uint8_t i,m,temp,size2,chr1;
	uint8_t y0=y;
	size2=(size1/8+((size1%8)?1:0))*(size1/2);  //�õ�����һ���ַ���Ӧ������ռ���ֽ���
	chr1=chr-' ';  //����ƫ�ƺ��ֵ
	for(i=0;i<size2;i++)
	{
		if(size1==12)
        {temp=asc2_1206[chr1][i];} //����12 06����
		else if(size1==16)
        {temp=asc2_1608[chr1][i];} //����16 08����
		else if(size1==24)
        {temp=asc2_2412[chr1][i];} //����24 12����
		else return;
				for(m=0;m<8;m++)           //д������
				{
					if(temp&0x80)OLED_ClearPoint(x,y);
					else OLED_DrawPoint(x,y);
					temp<<=1;
					y++;
					if((y-y0)==size1)
					{
						y=y0;
						x++;
						break;
          }
				}
  }
		OLED_Refresh();
}



//��ʾ�ַ���PRO(Modified)
//x,y:�������  
//size1:�����С 
//*chr:�ַ��� 
void OLED_ShowStringPro(uint8_t x,uint8_t y,char* chr,uint8_t size1)
{
	while((*chr>=' ')&&(*chr<='~'))//�ж��ǲ��ǷǷ��ַ�!
	{
		OLED_ShowChar(x,y,*chr,size1);
		x+=size1/2;
		if(x>128-size1)  //����
			
		{
			x=2;//x=0
			y+=size1;
    }
		chr++;
  }
		OLED_Refresh();
}


void OLED_inShowStringPro(uint8_t x,uint8_t y,char* chr,uint8_t size1)
{
	while((*chr>=' ')&&(*chr<='~'))//�ж��ǲ��ǷǷ��ַ�!
	{
		OLED_inShowChar(x,y,*chr,size1);
		x+=size1/2;
		if(x>128-size1)  //����
		{
			x=2;//x=0
			y+=size1;
    }
		chr++;
  }
		OLED_Refresh();
}

 
//��ʾ�ַ���
//x,y:�������  
//size1:�����С 
//*chr:�ַ�����ʼ��ַ 
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1)
{
	while((*chr>=' ')&&(*chr<='~'))//�ж��ǲ��ǷǷ��ַ�!
	{
		OLED_ShowChar(x,y,*chr,size1);
		x+=size1/2;
		if(x>128-size1)  //����
			
		{
			x=2;//x=0
			y+=size1;
    }
		chr++;
  }
		OLED_Refresh();
}
 
//m^n
uint32_t OLED_Pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;
	while(n--)
	{
	  result*=m;
	}
	return result;
}
 
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1)
{
	uint8_t t,temp;
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_Pow(10,len-t-1))%10;
			if(temp==0)
			{
				OLED_ShowChar(x+(size1/2)*t,y,'0',size1);
      }
			else 
			{
			  OLED_ShowChar(x+(size1/2)*t,y,temp+'0',size1);
			}
  }
		OLED_Refresh();
}
//д�ļ��������ĺ�����ʾ������ˢ���ٶȼ��� ��֧�ֶ��������С ��

//��ʾ����
//x,y:�������
//num:���ֶ�Ӧ�����
//ȡģ��ʽ ����ʽ
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1)
{
	uint8_t i,m,n=0,temp,chr1;
	uint8_t x0=x,y0=y;
	uint8_t size3=size1/8;
	while(size3--)
	{
		chr1=num*size1/8+n;
		n++;
			for(i=0;i<size1;i++)
			{
				if(size1==16)
						{temp=Chinese16[chr1][i];}//����16*16����
				else if(size1==24)
						{temp=Hzk2[chr1][i];}//����24*24����
				else if(size1==32)       
						{temp=Hzk3[chr1][i];}//����32*32����
				/*else if(size1==64)
						{temp=Hzk4[chr1][i];}//����64*64���屻�˸�**/
				else return;
							
						for(m=0;m<8;m++)
							{
								if(temp&0x01)OLED_DrawPoint(x,y);
								else OLED_ClearPoint(x,y);
								temp>>=1;
								y++;
							}
							x++;
							if((x-x0)==size1)
							{x=x0;y0=y0+8;}
							y=y0;
			 }
	}

}

/*void oled_ShowChinese(uint8_t x,uint8_t y,uint8_t NO) //�����ĺ��֣�16x16����ʾ����
{    
	uint8_t t,adder=0;
	//�ϰ���
	oled_location(x,y);	
    for(t=0;t<16;t++)
		{
				oled_data(Chinese16[2*NO][t]);
				adder+=1;
     }	
	//�°���
    oled_location(x,y+1);	
    for(t=0;t<16;t++)
			{	
				oled_data(Chinese16[2*NO+1][t]);
				adder+=1;
      }					
}
*/


//num ��ʾ���ֵĸ���
//space ÿһ����ʾ�ļ��
void OLED_ScrollDisplay(uint8_t y,uint8_t num,uint8_t space,uint32_t timess,uint8_t infinit)
{
	uint8_t i,n,t=0,m=0,r;
	timess=(timess-1)*(16*num)+16*(space);
	while(timess!=1)
	{
		if(m==0)
		{
	    OLED_ShowChinese(128,y,t,16); //д��һ�����ֱ�����OLED_GRAM[][]������
			t++;
		}
		if(t==num)
			{
				for(r=0;r<16*space;r++)      //��ʾ���
				 {
					for(i=0;i<144;i++)
						{
							for(n=0;n<8;n++)
							{
								OLED_GRAM[i-1][n]=OLED_GRAM[i][n];
							}
						}
           OLED_Refresh();
				 }
        t=0;
      }
		m++;
		if(m==16){m=0;}
		for(i=0;i<144;i++)   //ʵ������
		{
			for(n=0;n<8;n++)
			{
				OLED_GRAM[i-1][n]=OLED_GRAM[i][n];
			}
		}
		OLED_Refresh();
		if(!infinit){timess--;}
	}

}
 
//����д�����ݵ���ʼλ��
void OLED_WR_BP(uint8_t x,uint8_t y)
{
	OLED_WR_Byte(0xb0+y,OLED_CMD);//��������ʼ��ַ
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}
 
//x0,y0���������
//x1,y1���յ�����
//BMP[]��Ҫд���ͼƬ����
void OLED_ShowPicture(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[])
{
	//uint32_t j=0;
	uint8_t x=0,y=0;
	//if(y%8==0)y=0;
	//else y+=1;
	for(y=y0;y<y1;y++)
	 {
		// OLED_WR_BP(x0,y);
		 for(x=x0;x<x1;x++)
		 {
			 OLED_GRAM[x][y]=BMP[x+(y*128)];
			 //OLED_WR_Byte(BMP[x+(y0*128)],OLED_DATA);
			// j++;
     }
	 }
	 	OLED_Refresh();
}
//
//
void OLED_Printf(uint8_t str[])
{
OLED_Clear();
OLED_ShowString(2,2,str,12);
OLED_Refresh();
}
//��һ��׼��
void zhunxing(void)
	{	
	OLED_DrawCircle(64,32,10);
	OLED_DrawCircle(64,32,20);
	OLED_DrawLine(64,17,64,47);
	OLED_DrawLine(64-15,32,64+15,32);
	}
	

	
//OLED�ĳ�ʼ��
void OLED_Init(void)
{
	

	
	
	OLED_RES_Clr();
	HAL_Delay(200);
	OLED_RES_Set();
	
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD);// Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);
	OLED_Clear();
}
