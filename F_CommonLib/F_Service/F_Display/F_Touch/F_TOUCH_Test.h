#ifndef __F_TOUCH_TEST_H
#define __F_TOUCH_TEST_H
#include "all_config.h"
#ifdef Service_TOUCH
#ifdef F_STM32_F4
#include "../../F_Input/F_Key/F_Key.h"


/*调用
if(tp_dev.touchtype&0X80)
  TOUCH_Test();//电容屏测试，这里边是个死循环
 * */


/*画水平线
 * x0,y0:坐标
 * len:线长度
 * color:颜色
 * */
void TOUCH_Test_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	if(len==0)return;
	LCD_Fill(x0,y0,x0+len-1,y0,color);
}


/*画实心圆
 *x0,y0:坐标
 *r:半径
 *color:颜色
 * */
void TOUCH_Test_fill_circle(u16 x0,u16 y0,u16 r,u16 color)
{
	u32 i;
	u32 imax = ((u32)r*707)/1000+1;
	u32 sqmax = (u32)r*(u32)r+(u32)r/2;
	u32 x=r;
	TOUCH_Test_draw_hline(x0-r,y0,2*r,color);
	for (i=1;i<=imax;i++)
	{
		if ((i*i+x*x)>sqmax)// draw lines from outside
		{
 			if (x>imax)
			{
 				TOUCH_Test_draw_hline (x0-i+1,y0+x,2*(i-1),color);
 				TOUCH_Test_draw_hline (x0-i+1,y0-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)
		TOUCH_Test_draw_hline(x0-x,y0+i,2*x,color);
		TOUCH_Test_draw_hline(x0-x,y0-i,2*x,color);
	}
}






/*清空屏幕并在右上角显示"RST"
 * */
void TOUCH_Test_Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//清屏
 	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
  	POINT_COLOR=RED;//设置画笔蓝色
}


/*画一条粗线
 *  (x1,y1),(x2,y2):线条的起始坐标
 *  size：线条的粗细程度
 *  color：线条的颜色
 * */
void TOUCH_Test_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
	u16 t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	if(x1<size|| x2<size||y1<size|| y2<size)return;
	delta_x=x2-x1; //计算坐标增量
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1; //设置单步方向
	else if(delta_x==0)incx=0;//垂直线
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;//水平线
	else{incy=-1;delta_y=-delta_y;}
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )//画线输出
	{
		TOUCH_Test_fill_circle(uRow,uCol,size,color);//画点
		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}



/*电容触摸屏测试函数
 * 5个触控点的颜色(电容触摸屏用)
 * */
const u16 POINT_COLOR_TBL[5]={RED,GREEN,BLUE,BROWN,GRED};
void TOUCH_Test(void)
{
	u8 t=0;
	u8 i=0;
 	u16 lastpos[5][2];		//最后一次的数据
	while(1)
	{
		F_key_Value = Key_Scan();//按键按下，屏幕校准
		if (F_key_Value)
		{
			printf("%d\r\n", F_key_Value);
			LCD_Clear(WHITE);	//清屏
			TP_Adjust();  		//屏幕校准
			TP_Save_Adjdata();
			TOUCH_Test_Load_Drow_Dialog();
		}
		tp_dev.scan(0);
		for(t=0;t<5;t++)
		{
			if((tp_dev.sta)&(1<<t))
			{
                //printf("X坐标:%d,Y坐标:%d\r\n",tp_dev.x[0],tp_dev.y[0]);
				if(tp_dev.x[t]<lcddev.width &&tp_dev.y[t]<lcddev.height)
				{
					if(lastpos[t][0]==0XFFFF)
					{
						lastpos[t][0] = tp_dev.x[t];
						lastpos[t][1] = tp_dev.y[t];
					}

					TOUCH_Test_draw_bline(lastpos[t][0], lastpos[t][1], tp_dev.x[t],tp_dev.y[t], 2, POINT_COLOR_TBL[t]);//画线
					lastpos[t][0] = tp_dev.x[t];
					lastpos[t][1] = tp_dev.y[t];
					if(tp_dev.x[t]>(lcddev.width-24)&&tp_dev.y[t]<20)
					{
						TOUCH_Test_Load_Drow_Dialog();//清除
					}
				}
			}else lastpos[t][0]=0XFFFF;
		}

		HAL_Delay(5);i++;
	}
}



#endif
#endif
#endif
