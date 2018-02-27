#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include <allegro.h>
#include <vector.h>
#include "Especial.h"


class Personagem
{
public:
        Especial* getEspecial(char indice);
        BITMAP* getBackground();
        BITMAP* getNome();
        MIDI* getMusica();
        void carregaObj(); //Carrega musica e background, checar se existe arquivos
        void descarregaObj(); //Descarrega musica e background
        void vitoria(BITMAP*, char);
        void derrota(BITMAP*, char);
        void escolha(BITMAP*, char);
        void especialAnim(BITMAP* buffer, char); //Diferentemente das outras, aqui fica num loop até acabar a animação. interessante, inclusive, tocar uma musicazinha pra cada personagem durante a animação.
        int getCode();
        void carregaEspeciais();//Carrega os 4 especiais e o efeito através de um switch
        Personagem();
        Personagem(char);
        virtual ~Personagem();
protected:
private:
        char *nomeMusica, *nomeBackground, *nomeFigura, cod;
        SAMPLE* somEspecial;
        vector<Especial> especial;
        int contFrame;
        BITMAP* nome;
        BITMAP* figura; //Animações aqui
        BITMAP* background;
        MIDI* musica;
};

#endif // PERSONAGEM_H
