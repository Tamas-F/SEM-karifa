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

#define ANIM_NUM	10
#define ANIM_BYTES	15

extern const PROGMEM word anims_start[ANIM_NUM + 1];
extern const PROGMEM byte anims[100*ANIM_BYTES];


#endif /* ANIMS_H_ */