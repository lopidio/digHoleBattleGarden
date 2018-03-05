#ifndef FPS_H_INCLUDED
#define FPS_H_INCLUDED
#include "allegro.h"

volatile bool tempoFPS = true;
void funcTempo(void)
{
    tempoFPS = true;
}
END_OF_FUNCTION(funcTempo)

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
#endif // FPS_H_INCLUDED
