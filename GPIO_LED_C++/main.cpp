/****************************************************************************/
/*                                                                          */
/* 广州创龙电子科技有限公司                                                 */
/*                                                                          */
/* Copyright (C) 2014-2016 Guangzhou Tronlong Electronic Technology Co.,Ltd */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*              底板 LED（C++）                                             */
/*                                                                          */
/*              2016年06月07日                                              */
/*                                                                          */
/****************************************************************************/
#include <iostream>

using namespace std;
// 用于测试

/****************************************************************************/
/*                                                                          */
/*              宏定义                                                      */
/*                                                                          */
/****************************************************************************/
#define HWREG(x) (*((volatile unsigned int *)(x)))

/****************************************************************************/
/*                                                                          */
/*              LED 类                                                      */
/*                                                                          */
/****************************************************************************/
class LED
{
	public:
		// LED 类型和状态
		typedef enum { CoreBoardLED0, CoreBoardLED1,
                         /*  LED D7         LED D6         LED D9        LED D10 */
                         /* GPIO0[0]       GPIO0[5]       GPIO0[1]       GPIO0[2] */
			            MainBoardLED1, MainBoardLED2, MainBoardLED3, MainBoardLED4 } LEDType;

		typedef enum { LED_OFF, LED_ON } LEDStatus;

        // 方法
        LED(LEDType ID);					// 构造函数
        ~LED();								// 析构函数

        void LEDControl(LEDStatus value);	// LED 控制

    private:
        // 寄存器
		#define SYSCFG_PINMUX1_Regsiter  (0x01C14124)
		#define GPIO_DIR01_Regsiter      (0x01E26000 + 0x10)
		#define GPIO_OUT_DATA01_Regsiter (0x01E26000 + 0x14)

        // 寄存器原始值
        unsigned int SYSCFG_PINMUX1_Value;
        unsigned int GPIO_DIR01_Value;
        unsigned int GPIO_OUT_DATA01_Value;

        LEDType LED_ID;
};

LED::LED(LEDType ID)
{
	LED_ID = ID;

	SYSCFG_PINMUX1_Value  = HWREG(SYSCFG_PINMUX1_Regsiter);
	GPIO_DIR01_Value      = HWREG(GPIO_DIR01_Regsiter);
	GPIO_OUT_DATA01_Value = HWREG(GPIO_OUT_DATA01_Regsiter);

	switch(ID)
	{
		case CoreBoardLED0: ; break;
		case CoreBoardLED1: ; break;

		case MainBoardLED1: /* LED D7 GPIO0[0] */
							HWREG(SYSCFG_PINMUX1_Regsiter) = ((HWREG(SYSCFG_PINMUX1_Regsiter) & ~(0xFu << 28)) | (8u << 28));
							HWREG(GPIO_DIR01_Regsiter)     &= ~(1 << 0);
		                    break;

		case MainBoardLED2: /* LED D6 GPIO0[5] */
							HWREG(SYSCFG_PINMUX1_Regsiter) = ((HWREG(SYSCFG_PINMUX1_Regsiter) & ~(0xFu << 8)) | (8u << 8));
							HWREG(GPIO_DIR01_Regsiter)     &= ~(1 << 5);
							break;

		case MainBoardLED3: /* LED D9 GPIO0[1] */
							HWREG(SYSCFG_PINMUX1_Regsiter) = ((HWREG(SYSCFG_PINMUX1_Regsiter) & ~(0xFu << 24)) | (8u << 24));
							HWREG(GPIO_DIR01_Regsiter)     &= ~(1 << 1);
							break;

		case MainBoardLED4: /* LED D10 GPIO0[2] */
							HWREG(SYSCFG_PINMUX1_Regsiter) = ((HWREG(SYSCFG_PINMUX1_Regsiter) & ~(0xFu << 20)) | (8u << 20));
							HWREG(GPIO_DIR01_Regsiter)     &= ~(1 << 2);
							break;

		default:
				cout << "Wrong LED " << ID << endl;
				break;
	}
}

LED::~LED()
{
	switch(LED_ID)
	{
		case CoreBoardLED0: ; break;
		case CoreBoardLED1: ; break;

		case MainBoardLED1: /* LED D7 GPIO0[0] */
							HWREG(SYSCFG_PINMUX1_Regsiter) = ((HWREG(SYSCFG_PINMUX1_Regsiter) & ~(0xFu << 28)) | SYSCFG_PINMUX1_Value & (0xFu << 28));
							HWREG(GPIO_DIR01_Regsiter)     = ((HWREG(GPIO_DIR01_Regsiter) & ~(1 << 0)) | GPIO_DIR01_Value & (1 << 0));
		                    break;

		case MainBoardLED2: /* LED D6 GPIO0[5] */
							HWREG(SYSCFG_PINMUX1_Regsiter) = ((HWREG(SYSCFG_PINMUX1_Regsiter) & ~(0xFu << 8)) | SYSCFG_PINMUX1_Value & (0xFu << 8));
							HWREG(GPIO_DIR01_Regsiter)     = ((HWREG(GPIO_DIR01_Regsiter) & ~(1 << 5)) | GPIO_DIR01_Value & (1 << 5));
							break;

		case MainBoardLED3: /* LED D9 GPIO0[1] */
							HWREG(SYSCFG_PINMUX1_Regsiter) = ((HWREG(SYSCFG_PINMUX1_Regsiter) & ~(0xFu << 24)) | SYSCFG_PINMUX1_Value & (0xFu << 24));
							HWREG(GPIO_DIR01_Regsiter)     = ((HWREG(GPIO_DIR01_Regsiter) & ~(1 << 1)) | GPIO_DIR01_Value & (1 << 1));
							break;

		case MainBoardLED4: /* LED D10 GPIO0[2] */
							HWREG(SYSCFG_PINMUX1_Regsiter) = ((HWREG(SYSCFG_PINMUX1_Regsiter) & ~(0xFu << 20)) | SYSCFG_PINMUX1_Value & (0xFu << 20));
							HWREG(GPIO_DIR01_Regsiter)     = ((HWREG(GPIO_DIR01_Regsiter) & ~(1 << 2)) | GPIO_DIR01_Value & (1 << 2));
							break;

		default:
				cout << "Wrong LED " << LED_ID << endl;
				break;
	}
}

void LED::LEDControl(LEDStatus value)
{
	switch(LED_ID)
	{
		case CoreBoardLED0: ; break;
		case CoreBoardLED1: ; break;

		case MainBoardLED1: /* LED D7 GPIO0[0] */
							if(LED_OFF == value)
							{
								HWREG(GPIO_OUT_DATA01_Regsiter) &= ~(1 << 0);
							}
							else if(LED_ON == value)
							{
								HWREG(GPIO_OUT_DATA01_Regsiter) |= (1 << 0);
							}
		                    break;

		case MainBoardLED2: /* LED D6 GPIO0[5] */
							if(LED_OFF == value)
							{
								HWREG(GPIO_OUT_DATA01_Regsiter) &= ~(1 << 5);
							}
							else if(LED_ON == value)
							{
								HWREG(GPIO_OUT_DATA01_Regsiter) |= (1 << 5);
							}
							break;

		case MainBoardLED3: /* LED D9 GPIO0[1] */
							if(LED_OFF == value)
							{
								HWREG(GPIO_OUT_DATA01_Regsiter) &= ~(1 << 1);
							}
							else if(LED_ON == value)
							{
								HWREG(GPIO_OUT_DATA01_Regsiter) |= (1 << 1);
							}
							break;

		case MainBoardLED4: /* LED D10 GPIO0[2] */
							if(LED_OFF == value)
							{
								HWREG(GPIO_OUT_DATA01_Regsiter) &= ~(1 << 2);
							}
							else if(LED_ON == value)
							{
								HWREG(GPIO_OUT_DATA01_Regsiter) |= (1 << 2);
							}
							break;

		default:
				cout << "Wrong LED " << LED_ID << endl;
				break;
	}
}

/****************************************************************************/
/*                                                                          */
/*              指令延时                                                    */
/*                                                                          */
/****************************************************************************/
// 延时（非精确）
void Delay(unsigned int n)
{
	unsigned int i;

	for(i = n; i > 0; i--);
}

/****************************************************************************/
/*                                                                          */
/*              主函数                                                      */
/*                                                                          */
/****************************************************************************/
int main()
{
	cout << "\r\nTronlong GPIO LED Application(C++ Edition) ......" << endl;

	// LED 对象
	LED *LED_D7  = new LED(LED::MainBoardLED1);
	LED *LED_D6  = new LED(LED::MainBoardLED2);
	LED *LED_D9  = new LED(LED::MainBoardLED3);
	LED *LED_D10 = new LED(LED::MainBoardLED4);

	// 循环点亮 LED
	unsigned int i;
	for(i = 0; i < 15; i++)
	{
		LED_D7->LEDControl(LED::LED_ON);
		LED_D6->LEDControl(LED::LED_OFF);
		LED_D9->LEDControl(LED::LED_OFF);
		LED_D10->LEDControl(LED::LED_OFF);
		Delay(0x00FFFFFF);

		LED_D7->LEDControl(LED::LED_OFF);
		LED_D6->LEDControl(LED::LED_ON);
		LED_D9->LEDControl(LED::LED_OFF);
		LED_D10->LEDControl(LED::LED_OFF);
		Delay(0x00FFFFFF);

		LED_D7->LEDControl(LED::LED_OFF);
		LED_D6->LEDControl(LED::LED_OFF);
		LED_D9->LEDControl(LED::LED_ON);
		LED_D10->LEDControl(LED::LED_OFF);
		Delay(0x00FFFFFF);

		LED_D7->LEDControl(LED::LED_OFF);
		LED_D6->LEDControl(LED::LED_OFF);
		LED_D9->LEDControl(LED::LED_OFF);
		LED_D10->LEDControl(LED::LED_ON);
		Delay(0x00FFFFFF);
	}

	delete LED_D7;
	delete LED_D6;
	delete LED_D9;
	delete LED_D10;
}
