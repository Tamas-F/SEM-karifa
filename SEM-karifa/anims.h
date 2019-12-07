/*
 * anims.h
 *
 * Created: 2019. 12. 06. 16:02:46
 *  Author: Tomi
 */ 


#ifndef ANIMS_H_
#define ANIMS_H_

 #include <avr/pgmspace.h>
#include "commons.h"

#define ANIM_NUM	9
#define ANIM_BYTES	15

// Ki szamolja az anims start tomb-be, hogy mi lesz az animacio kezdo cime
#define SIZE_ANIM_0	8		// 0. animacio hossza (sor)
#define SIZE_ANIM_1	14		// 1. animacio hossza (sor)
#define SIZE_ANIM_2	3		// 2. animacio hossza (sor)
#define SIZE_ANIM_3	9		// 3. animacio hossza (sor)
#define SIZE_ANIM_4	2		// 4. animacio hossza (sor)
#define SIZE_ANIM_5	3		// 5. animacio hossza (sor)
#define SIZE_ANIM_6	14		// 6. animacio hossza (sor)
#define SIZE_ANIM_7	21		// 7. animacio hossza (sor)
#define SIZE_ANIM_8	18		// 8. animacio hossza (sor)

#define ANIM_0_START	0												// 0.animacio kezdocime
#define ANIM_1_START	ANIM_0_START + (SIZE_ANIM_0 * ANIM_BYTES)		// 1.animacio kezdocime
#define ANIM_2_START	ANIM_1_START + (SIZE_ANIM_1 * ANIM_BYTES)		// 2.animacio kezdocime
#define ANIM_3_START	ANIM_2_START + (SIZE_ANIM_2 * ANIM_BYTES)		// 3.animacio kezdocime
#define ANIM_4_START	ANIM_3_START + (SIZE_ANIM_3 * ANIM_BYTES)		// 4.animacio kezdocime
#define ANIM_5_START	ANIM_4_START + (SIZE_ANIM_4 * ANIM_BYTES)		// 5.animacio kezdocime
#define ANIM_6_START	ANIM_5_START + (SIZE_ANIM_5 * ANIM_BYTES)		// 6.animacio kezdocime
#define ANIM_7_START	ANIM_6_START + (SIZE_ANIM_6 * ANIM_BYTES)		// 7.animacio kezdocime
#define ANIM_8_START	ANIM_7_START + (SIZE_ANIM_7 * ANIM_BYTES)		// 8.animacio kezdocime
#define ANIM_END		ANIM_8_START + (SIZE_ANIM_8 * ANIM_BYTES)		// Animaciok vege cim

extern const PROGMEM word anims_start[ANIM_NUM + 1];
extern const PROGMEM byte anims[100*ANIM_BYTES];


#endif /* ANIMS_H_ */