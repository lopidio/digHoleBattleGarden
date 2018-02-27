//Feito pelo Lopídio Guigui
//Espero q naum dê bug
//Se der, naum foi ele que fez
//Boa sorte a todos nós!
//Ave Lopídio!
#include "Tecla.h"

//{Construtor e Destrutor
Tecla::Tecla()
{
}
Tecla::Tecla(char tecla_):tecla(tecla_){
    keyAnt = false;
    keyAtual = false;
    contFrame = 0;
    contx2 = 0;
}
Tecla::~Tecla()
{
}
//}

void Tecla::update(){
    keyAnt = keyAtual;
    keyAtual = key[tecla];
}
bool Tecla::x1(){
    return !keyAnt&&keyAtual;
}
bool Tecla::x2(unsigned char fps){
    bool b =  x1()&&contx2<fps&&contx2>0;
    contx2 = MIN((x1())?0: contx2+1, 2*fps);
    return b;
}
bool Tecla::release(){
    return keyAnt&&!keyAtual;
}
bool Tecla::perFrame(unsigned char velo){
    return keyAtual&&((++contFrame)%=velo)==0;
}
bool Tecla::down(){
    return keyAtual;
}
bool Tecla::up(){
    return !down();
}
bool Tecla::another(){
    outra = keypressed();
    clear_keybuf();
    return outra&&!keyAtual;
}
void Tecla::setTecla(char tecla_){
    tecla = tecla_;
}
