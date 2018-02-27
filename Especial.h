#ifndef ESPECIAL_H
#define ESPECIAL_H
#include <allegro.h>
#include "Animacao.h"

class Especial
{
public:
        Especial(char Cod);
        BITMAP* getNome();
        unsigned char getCode();
        bool getAtivo();
        bool getTemMusica();
        void update(BITMAP*);
        void inicioEspecial(BITMAP* buffer, char player);
        bool getExclusivo();
        bool getAnimInicial();
        virtual ~Especial();
protected:
private:
    char* nomeAnimNormal, *nomeAnimInicial, * nomeMusica;
    Animacao* animacaoInicial, *animacaoNormal;
    enum cod{NENHUM = 0, AUMENTA_SEMTOP_ADV_20 = 10, AUMENTA_SEMTOP_ADV_15 = 11, AUMENTA_SEMTOP_ADV_10 = 12,
                    PISCAPISCA = 30, DUAS_MARTELADAS = 31, MATAR_NA_HORA_EXATA = 32,
                    EMBARALHAR_TECLAS_COL_ESQ = 33, ROUBAR_ESPECIAL_ADV = 52, ROUBAR_E_PARAR_ESPECIAL_ADV = 53,
                    DIMINUE_VELO_PROPRIA = 50, MATAR_TODAS = 51,  COLUNA_SEM_TOP_1 = 70} eCod;
    MIDI* musica;
    int tempoVida, contVida;
    BITMAP* nome;
    bool ativo, exclusivo, temMusica, animInicial, animNormal;
};

/*
            TABELA DE ESPECIAIS
    0 < 10             SEM ESPECIAL
    10<30            ESPECIAL ATUANTE NO OUTRO JOGADOR QUE É RESOLVIDO NA CLASSE FASE
    30<50            ESPECIAL ATUANTE NO OUTRO JOGADOR QUE É RESOLVIDO NA CLASSE TOUPEIRA
    50<70            ESPECIAL ATUANTE NO PRÓPRIO JOGADOR QUE É RESOLVIDO NA CLASSE FASE
    70<90            ESPECIAL ATUANTE NO PRÓPRIO JOGADOR QUE É RESOLVIDO NA CLASSE TOUPEIRA
*/

#endif // ESPECIAL_H
