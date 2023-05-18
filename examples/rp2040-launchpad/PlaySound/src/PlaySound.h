/*
 * PlaySound.h
 *
 *  Created on: 04.04.2020
 *      Author: student
 */

#ifndef PLAYSOUND_H_
#define PLAYSOUND_H_

#include "gpio_rp2040.h"
#include "timer_rp2040.h"

enum TONE {
   H2 = 3,
   C1, Cis1, D1, Dis1, E1, F1, Fis1, G1, Gis1, A1, B1, H1,
   C , Cis,  D,  Dis,  E,  F,  Fis,  G,  Gis,  A,  B,  H,
   c , cis,  d,  dis,  e,  f,  fis,  g,  gis,  a,  b,  h,
   c1, cis1, d1, dis1, e1, f1, fis1, g1, gis1, a1, b1, h1,
   c2, cis2, d2, dis2, e2, f2, fis2, g2, gis2, a2, b2, h2,
   c3, cis3, d3, dis3, e3, f3, fis3, g3, gis3, a3, b3, h3,
   P  = 80,
};

struct ENTRY {
    TONE    t;
    int     ms;
};

class PlaySound
{
public:
    PlaySound();

    void playTone   (TONE  t,   int ms);
    void playMelody (ENTRY t[], int scale = 1);

private:
    int             _calculateDelay_us(TONE t);
    int             _delay_us;
    int             _sum_us;
    gpio_rp2040_pin _buzzer;
    timer_rp2040    _tone_timer;

};

#endif /* PLAYSOUND_H_ */
