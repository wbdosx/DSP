;****************************************************************************/
;*                                                                          */
;* 广州创龙电子科技有限公司                                                 */
;*                                                                          */
;* Copyright (C) 2014-2016 Guangzhou Tronlong Electronic Technology Co.,Ltd */
;*                                                                          */
;****************************************************************************/
;****************************************************************************
;****************************************************************************
;*                                                                          *
;*              底板 LED（汇编）                                            *
;*                                                                          *
;*              2016年02月18日                                              *
;*                                                                          *
;****************************************************************************
    .sect		".text"
    .global		main

main:
        MVKL	.S2    0x1C14124, B4
||      MVKL	.S1    0x88800800, A3

        MVKH	.S2    0x1C14124, B4
||      MVKH	.S1    0x88800800, A3

        STW		.D2T1  A3, *B4

        MVKL	.S2    0x1E26010, B6
||      MVKL	.S1    0, A5

        MVKH	.S2    0x1E26010, B6
||      MVKH	.S1    0, A5

        STW		.D2T1  A5, *B6

        ADD		.L1X   4, B6, A4

LED_D7:
        MVK		.S1    0x00000001, A3
        STW		.D1T1  A3, *A4

	    MVKL	.S2    0x00FFFFFF, B1
        MVKH	.S2    0x00FFFFFF, B1
delay0:
        SUB		B1, 1, B1
   [B1] B		delay0
        NOP		5

LED_D6:
        MVK		.S1    0x00000020, A3
        STW		.D1T1  A3, *A4

	    MVKL	.S2    0x00FFFFFF, B1
        MVKH	.S2    0x00FFFFFF, B1
delay1:
        SUB		B1, 1, B1
   [B1] B		delay1
        NOP		5

LED_D9:
        MVK		.S1    0x00000002, A3
        STW		.D1T1  A3, *A4

	    MVKL	.S2    0x00FFFFFF, B1
        MVKH	.S2    0x00FFFFFF, B1
delay2:
        SUB		B1, 1, B1
   [B1] B		delay2
        NOP		5

LED_D10:
        MVK		.S1    0x00000004, A3
        STW		.D1T1  A3, *A4

	    MVKL	.S2    0x00FFFFFF, B1
        MVKH	.S2    0x00FFFFFF, B1
delay3:
        SUB		B1, 1, B1
   [B1] B		delay3
        NOP		5

        B		LED_D7
        NOP		5
