#ifndef TOUPEIRA_H
#define TOUPEIRA_H
#include <allegro.h>

class Toupeira
{
public:
    Toupeira(char, char, unsigned short);
    void update(BITMAP*, char&, char&);
    void criar(unsigned char, char, bool, bool);
    void matar(); //Mata, com direito a animação e tudo mais!
    void desativar(); //Desativa
    virtual ~Toupeira();
    bool getAtiva();
protected:
private:
    BITMAP* figura;
    SAMPLE* somCria, *somMorre1, *somMorre2, *somMorre3,*somMorre4, *somMorre5;
    SAMPLE* somMorre6,*somMorre7, *somMorre8, *somMorre9, *somMorre10, *somMorreEspecial;
    SAMPLE* somImpacto1, *somImpacto2, *somImpacto3, *somImpacto4;
    SAMPLE* estrelaAparecendo, *clicouErrado, *estrela, *matouCoelho;
    unsigned short KEY_KILL, KEY_KILL_TOUPEIRA; //tecla que mata atualmente | tecla fixa pra cada toupeira
    char contVida, tempoVida, levandoEspecial, toupeiraID;
    short x,y;
    char frame, contApa, contMorte, contPerm, contDesap; //Variáveis de controle
    enum {NADA = 0, MORRER, DESAPARECER, APARECER} anim;
    bool ativa, brinde, keyAnt, maligna;
    void especiais(BITMAP*);
    void imprimir(BITMAP*);
    void carregaSons();
    void fazerSom(char);
    void aparecer();
    void permanecer();
    void morrer(char&, char&);
    void desaparecer(char&);
    bool key1x();
};

#endif // TOUPEIRA_H
