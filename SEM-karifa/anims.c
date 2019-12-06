/*
 * anims.c
 *
 * Created: 2019. 12. 06. 16:04:10
 *  Author: Tomi
 */ 

 #include "anims.h"

 const PROGMEM word anims_start[ANIM_NUM + 1] = {0, 8*ANIM_BYTES, 22*ANIM_BYTES, 24*ANIM_BYTES, 27*ANIM_BYTES, 41*ANIM_BYTES, 61*ANIM_BYTES, 79*ANIM_BYTES};

 const PROGMEM byte anims[] = {//120 = 1 sec
	 
	 //0 => 0 --- Classic
	 15,	0,	15,	0,	0,	15,	15,	0,	0,	15,	0,	15,	15,	0,	16,
	 0,	15,	0,	15,	15,	0,	0,	15,	15,	0,	15,	0,	0,	0,	16,
	 15,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	15,	0,	0,	16,
	 0,	15,	0,	15,	15,	0,	0,	15,	15,	0,	15,	0,	0,	0,	16,
	 15,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	15,	0,	0,	16,
	 0,	0,	0,	15,	0,	0,	0,	0,	15,	0,	0,	0,	0,	0,	16,
	 15,	0,	15,	0,	0,	15,	15,	0,	15,	0,	0,	15,	15,	0,	16,
	 0,	0,	0,	15,	0,	0,	0,	0,	15,	0,	0,	0,	0,	0,	16,

	 //8 => 8 ---
	 //Fade circle
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
	 //14 => 22
	 //fel, le villog
	 15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	15,	/*ismétlés*/	0,	/*várakozás*/	130,
	 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	/*ismétlés*/	0,	/*várakozás*/	130,
	 
	 //2 => 24 ---
	 //fel, le fade-el
	 0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	/*ismétlés*/	0,	/*várakozás*/	1,
	 1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	/*ismétlés*/	15,	/*várakozás*/	130/8,
	 -1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	/*ismétlés*/	15,	/*várakozás*/	130/8,
	 
	 //3 => 27 ---
	 //pseudorandomfade
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
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*ismétlés*/ 0, /*várakozás*/ 10,
	 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,  /*ismétlés*/ 15, /*várakozás*/ 7,
	 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 7,
	 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 7,
	 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 7,
	 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, /*ismétlés*/ 15, /*várakozás*/ 7,
	 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, /*ismétlés*/ 15, /*várakozás*/ 7,
	 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, /*ismétlés*/ 15, /*várakozás*/ 7,
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