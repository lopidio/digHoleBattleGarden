#ifndef TECLA_H
#define TECLA_H
#include <allegro.h>


class Tecla
{
public:
    Tecla();
    Tecla(char tecla_);
    void update();
    bool x1();
    bool x2(unsigned char fps);
    bool release();
    bool perFrame(unsigned char velo);
    bool down();
    bool up();
    bool another();
    void setTecla(char tecla_);
    virtual ~Tecla();
protected:
private:
    char tecla;
    bool keyAnt, keyAtual, outra;
    unsigned int contFrame, contx2;
};

#endif // TECLA_H

