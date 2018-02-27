#ifndef PLAYER_H
#define PLAYER_H
#include "Toupeira.h"
#include "Personagem.h"
#include <vector.h>
#include <ctime>
#include <allegro.h>


class Player
{
public:
        char veloTop, semTop, especialProprio, durTop;
        unsigned levandoEspecial;
        Especial *getEspecial();
        void reiniciarPlayer();
        bool is_especialAtivo();
        void ativarEspecial();
        void matarToupeiras();
        bool requisitarEspecial();
        void desativarEspecial();
        Player(Personagem*, char);
        Personagem* getPersonagem();
        void update(BITMAP*);
        void vitoria(BITMAP*);
        char getID();
        void descarregarObj();
        void carregarObj();
        void derrota(BITMAP*);
        Player();
        BITMAP* getTabuleiro();
        virtual ~Player();
protected:
private:
    BITMAP* tabuleiro;
    void mudaCor();
    char contCria, contBrinde;
    char playerID;
    unsigned short KEY_ESPECIAL;
    Personagem* personagem;
    vector<Toupeira> toupeira;
    bool especialAtivo;
};

#endif // PLAYER_H
