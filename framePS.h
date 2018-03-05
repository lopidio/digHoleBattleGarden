#include <allegro.h>
#ifndef FRAMEPS_H_INCLUDED
#define FRAMEPS_H_INCLUDED

bool tempoFPS = true;
void funcTempo(void)
{
    tempoFPS = true;
}

void installFPS(int fps){
    LOCK_VARIABLE(tempoFPS);
    LOCK_FUNCTION(funcTempo);
    install_int(funcTempo, (int)(1000/fps));
}

void syncFPS(){
        while (!tempoFPS){} //responsavel pelo FPS
        tempoFPS = false;
}

void removeFps(){
    remove_int(funcTempo);
}
#endif // FRAMEPS_H_INCLUDED
