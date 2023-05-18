/*
 * PlaySound.cpp
 *
 *  Created on: 04.04.2020
 *      Author: student
 */

#include <PlaySound.h>
#include <math.h>

PlaySound::PlaySound() : _delay_us(0), _sum_us(0), _buzzer( 14 ), _tone_timer(0)
{
    _buzzer.gpioMode(GPIO::OUTPUT);
}

void PlaySound::playTone(TONE t, int ms) {
    _delay_us = _calculateDelay_us(t);
    _sum_us   = 0;
    _tone_timer.setPeriod(_delay_us, TIMER::PERIODIC);
    _tone_timer.setCallback([this]() {
        _buzzer.gpioToggle();
        _sum_us += _delay_us;
    });
    _buzzer.gpioMode(t == P ? GPIO::INPUT : GPIO::OUTPUT);
    _tone_timer.start();
    while (_sum_us / 1000 < ms) ;
    _tone_timer.stop();
}

void PlaySound::playMelody(ENTRY t[], int scale) {
    int idx = 0;
    while (t[idx].ms) {
        playTone(t[idx].t, t[idx].ms * scale);
        idx++;
    }
}

int PlaySound::_calculateDelay_us(TONE t) {
    float exponent = (37.0 - (float)t) / 12.0;
    float cnt = pow(2, exponent) * 2272.7272;
    return (int)(cnt + 0.5);
}
