#ifndef FASE_H
#define FASE_H
#include <allegro.h>
#include <math.h>
#include "Player.h"
#include "Life.h"
#include "Animacao.h"
#include "Tecla.h"
#include <vector.h>

class Fase
{
public:
        char principal();
        Fase(Personagem*, Personagem*, char);
        virtual ~Fase();
protected:
private:
    double variadorVelo;
    Life life;
    Animacao *roundsNome, *roundsNum, *barraEspeciais1, *barraEspeciais2, *terra1, *terra2, *terra3, *trofeu1, *trofeu2;
    char FPS;
    void animRound();
    BITMAP* background;
    Tecla* enter;
    BITMAP *video_page[2];
    bool viraPagina;
    Player* p1, *p2;
    MIDI* musica;
    BITMAP* num, *pause, *menuPause;
    void desenhaNumero(unsigned int valor, char precisao, short x, short y, BITMAP* buffer);
    enum eModo {NENHUM, SELECIONAR, MENU_PRINCIPAL, REINICIAR} proximo;
    double veloGeral;
    unsigned char roundP1, roundP2;
    void variaVelo();
    void pausar(BITMAP* telaAntiga_);// retorna o destino //    int vol1, vol2; get_volume(&vol1, &vol2); <-- Funciona assim o get Volume! //Fazer essa função em outra classe.
    void fimRound(BITMAP*buffer, Player*, Player*);//retorna o destino
    void fimJogo(Player*, Player*);
    void desenharTela(BITMAP* buffer);
    void carregandoTela();
    void especial(BITMAP*, Player*, Player*);
};

#endif // FASE_H
