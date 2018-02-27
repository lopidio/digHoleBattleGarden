#ifndef ANIMACAO_H
#define ANIMACAO_H
#include <allegro.h>


class Animacao
{
public:
    Animacao();
    Animacao(const char* nomeArquivo, char numFrames, short, short, char numAnim, bool loop);
    void setPosicao(short x, short y);
    void imprime(BITMAP* buffer);
    void setAnimacao(char anim);
    void defineLoop(unsigned char, unsigned char, unsigned char);
    void defineLoop(unsigned char, unsigned char);
    void edit(char numFrames, short x, short y, char numAnim, bool loop);
    virtual ~Animacao();
    void inverteFigura();
    void inverte();
    bool finalizada();
protected:
private:
    BITMAP* figura;
    bool loop;
    char numFrames, numAnimacoes, contFrame, contAnim;
    short x, y;
    unsigned char min, max;
};

#endif // ANIMACAO_H
