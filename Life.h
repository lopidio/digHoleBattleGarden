#ifndef LIFE_H
#define LIFE_H
#include <allegro.h>

class Life
{
public:
    Life();
    void imprime (BITMAP* buffer, char);
    void finalizar (BITMAP* buffer, char);
    virtual ~Life();
protected:
private:
    char semTopAnt;
    short x, y;
    BITMAP* borda, *figura;
    char contFrame;
};

#endif // LIFE_H
