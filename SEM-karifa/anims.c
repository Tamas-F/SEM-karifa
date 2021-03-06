/*
 * anims.c
 *
 * Created: 2019. 12. 06. 16:04:10
 *  Author: Tomi
 */ 

 #include "commons.h"
 #include "anims.h"
 #include <avr/io.h>
 #include <avr/pgmspace.h>
 

 const PROGMEM word anims_start[ANIM_NUM + 1] = {ANIM_0_START, ANIM_1_START, ANIM_2_START, ANIM_3_START, ANIM_4_START, ANIM_5_START, ANIM_6_START, ANIM_7_START, ANIM_8_START, ANIM_END};

 const PROGMEM byte anims[] = {//120 = 1 sec
	 
	 //Classic: régi animáció "retro"
	 // hossz: 8 sor
	  15,	0,	15,	0,	0,	15,	15,	0,	0,	15,	0,	15,	15,	0,	16,
	  0,	15,	0,	15,	15,	0,	0,	15,	15,	0,	15,	0,	0,	0,	16,
	  15,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	15,	0,	0,	16,
	  0,	15,	0,	15,	15,	0,	0,	15,	15,	0,	15,	0,	0,	0,	16,
	  15,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	15,	0,	0,	16,
	  0,	0,	0,	15,	0,	0,	0,	0,	15,	0,	0,	0,	0,	0,	16,
	  15,	0,	15,	0,	0,	15,	15,	0,	15,	0,	0,	15,	15,	0,	16,
	  0,	0,	0,	15,	0,	0,	0,	0,	15,	0,	0,	0,	0,	0,	16,

	 //Fade circle: egy pont megy körbe körbe a LED-ek között fadelve
	 // hossz: 14
	 15,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	/*ismétlés*/	0,	/*várakozás*/	1,
	 -1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	/*ismétlés*/	15,	/*várakozás*/	130/30,
	  0,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	/*ismétlés*/	15,	/*várakozás*/	130/30,
	  0,	0,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	/*ismétlés*/	15,	/*várakozás*/	130/30,
	  0,	0,	0,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	/*ismétlés*/	15,	/*várakozás*/	130/30,
	  0,	0,	0,	0,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	/*ismétlés*/	15,	/*várakozás*/	130/30,
	  0,	0,	0,	0,	0,	-1,	0,	0,	0,	0,	0,	0,	1,	/*ismétlés*/	15,	/*várakozás*/	130/30,
	  0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-1,	/*ismétlés*/	15,	/*várakozás*/	130/30,
	  0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-1,	0,	/*ismétlés*/	15,	/*várakozás*/	130/30,
	  0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	-1,	0,	0,	/*ismétlés*/	15,	/*várakozás*/	130/30,
	  0,	0,	0,	0,	0,	0,	0,	0,	1,	-1,	0,	0,	0,	/*ismétlés*/	15,	/*várakozás*/	130/30,
	  0,	0,	0,	0,	0,	0,	0,	1,	-1,	0,	0,	0,	0,	/*ismétlés*/	15,	/*várakozás*/	130/30,
	  0,	0,	0,	0,	0,	0,	1,	-1,	0,	0,	0,	0,	0,	/*ismétlés*/	15,	/*várakozás*/	130/30,
	  1,	0,	0,	0,	0,	0,	-1,	0,	0,	0,	0,	0,	0,	/*ismétlés*/	15,	/*várakozás*/	130/30,
	 
	 //Fade ring: felváltva fadelődnek az egymás melletti ledek
	 // hossz: 3
	 15,	1,	15,	1,	15,	1,	15,	1,	15,	1,	15,	1,	15,	/*ismétlés*/	0,	/*várakozás*/	1,
	 -1,	1,	-1,	1,	-1,	1,	-1,	1,	-1,	1,	-1,	1,	-1,	/*ismétlés*/	14,	/*várakozás*/	130/25,
	  1,	-1,	1,	-1,	1,	-1,	1,	-1,	1,	-1,	1,	-1,	1,	/*ismétlés*/	14,	/*várakozás*/	130/25,
	 
	 //Csordogáló jég: fentről lefelé szimmetrikus 2 fénypont csóvával
	 // hossz: 9
	 /*	B1		B2	B3	B4	B5	B6	J1	J2	J3	J4	J5	J6	CS	*/
		 0,		0,	14,	7,	0,	0,	0,	0,	14,	7,	0,	0,	14,	/*ismétlés*/	0,	/*várakozás*/	1,
		 0,		2,	-1,	-1,	0,	2,	0,	2,	-1,	-1,	0,	2,	-1,	/*ismétlés*/	7,	/*várakozás*/	130/25,
		 2,		-1,	-1,	0,	2,	-1,	2,	-1,	-1,	0,	2,	-1,	-1,	/*ismétlés*/	7,	/*várakozás*/	130/25,
		 -1,	-1,	0,	2,	-1,	-1,	-1,	-1,	0,	2,	-1,	-1,	0,	/*ismétlés*/	7,	/*várakozás*/	130/25,
		 -1,	0,	2,	-1,	-1,	0,	-1,	0,	2,	-1,	-1,	0,	2,	/*ismétlés*/	7,	/*várakozás*/	130/25,
		 0,		2,	-1,	-1,	0,	2,	0,	2,	-1,	-1,	0,	2,	-1,	/*ismétlés*/	7,	/*várakozás*/	130/25,
		 2,		-1,	-1,	0,	2,	-1,	2,	-1,	-1,	0,	2,	-1,	-1,	/*ismétlés*/	7,	/*várakozás*/	130/25,
		 -1,	-1,	0,	2,	-1,	-1,	-1,	-1,	0,	2,	-1,	-1,	0,	/*ismétlés*/	7,	/*várakozás*/	130/25,
		 -1,	0,	2,	-1,	-1,	0,	-1,	0,	2,	-1,	-1,	0,	2,	/*ismétlés*/	7,	/*várakozás*/	130/25,
	
	 
	 //fel, le villog
	 // hossz: 2
	  15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	/*ismétlés*/	0,	/*várakozás*/	130,
	  0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	/*ismétlés*/	0,	/*várakozás*/	130,
	 
	 //2 => 24 ---
	 //fel, le fade-el
	 // hossz: 3
	 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	/*ismétlés*/	0,	/*várakozás*/	1,
	 1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	/*ismétlés*/	15,	/*várakozás*/	130/8,
	 -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	/*ismétlés*/	15,	/*várakozás*/	130/8,
	 
	 //3 => 27 ---
	 //pseudorandomfade
	 // hossz: 14
	 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  /*ismétlés*/ 15, /*várakozás*/ 8, /*7*/
	 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 8, /*2*/
	 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 8, /*10*/
	 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 8, /*0*/
	 -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 8, /*5*/
	 0, 0, 0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 8, /*8*/
	 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 1, 0, /*ismétlés*/ 15, /*várakozás*/ 8, /*11*/
	 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, /*ismétlés*/ 15, /*várakozás*/ 8, /*1*/
	 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 8, /*3*/
	 0, 0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 8, /*6*/
	 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 1, /*ismétlés*/ 15, /*várakozás*/ 8, /*12*/
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, -1, /*ismétlés*/ 15, /*várakozás*/ 8, /*9*/
	 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 8, /*4*/
	 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 8, /*reset*/
	 
	 //17 => 41
	 //lalirandomja
	 // hossz: 21
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*ismétlés*/ 0, /*várakozás*/ 10,
	 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,  /*ismétlés*/ 15, /*várakozás*/ 7,
	 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 7,
	 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 7,
	 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 7,
	 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 7,
	 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, /*ismétlés*/ 15, /*várakozás*/ 7,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, /*ismétlés*/ 15, /*várakozás*/ 7,
	#if defined(_TYPE_MEZI) || defined(_TYPE_STAR)
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, /*ismétlés*/ 15, /*várakozás*/ 3,
	#else
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 1, /*várakozás*/ 1,
	#endif
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, /*ismétlés*/ 15, /*várakozás*/ 3,
	 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 3,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 3,
	 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 3,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 3,
	 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 3,
	 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 3,
	 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 3,
	 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 3,
	 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 3,
	 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 3,
	 -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 3,
	 
	 //20 => 61
	 //fadevertic
	 // hossz: 18
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*ismétlés*/ 0, /*várakozás*/ 1,
	 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,  /*ismétlés*/ 15, /*várakozás*/ 2,
	 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,  /*ismétlés*/ 15, /*várakozás*/ 2,
	 -1, 0, 1, 0, 0, 0, -1, 0, 1, 0, 0, 0, 0,  /*ismétlés*/ 15, /*várakozás*/ 2,
	 0, -1, 0, 1, 0, 0, 0, -1, 0, 1, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 2,
	 0, 0, -1, 0, 1, 0, 0, 0, -1, 0, 1, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 2,
	 0, 0, 0, -1, 0, 1, 0, 0, 0, -1, 0, 1, 0, /*ismétlés*/ 15, /*várakozás*/ 2,
	 0, 0, 0, 0, -1, 0, 0, 0, 0 ,0, -1, 0, 1, /*ismétlés*/ 15, /*várakozás*/ 2,
	 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, /*ismétlés*/ 15, /*várakozás*/ 2,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, /*ismétlés*/ 15, /*várakozás*/ 2,
	 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, /*ismétlés*/ 15, /*várakozás*/ 2,
	 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 2,
	 0, 0, 0, 1, 0, -1, 0, 0, 0, 1, 0, -1, 0, /*ismétlés*/ 15, /*várakozás*/ 2,
	 0, 0, 1, 0, -1, 0, 0, 0, 1, 0, -1, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 2,
	 0, 1, 0, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 2,
	 1, 0, -1, 0, 0, 0, 1, 0, -1, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 2,
	 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 2,
	 -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 2,
	 //18 => 79
 };