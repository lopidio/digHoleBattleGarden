//Feito pelo Lopídio Guigui
//Espero q naum dê bug
//Se der, naum foi ele que fez
//Boa sorte a todos nós!
//Ave Lopídio!
#include "Especial.h"

//{        TIMER!!!
volatile bool EStempoFPS = true;
void ESfuncTempo(void)
{
    EStempoFPS = true;
}
END_OF_FUNCTION(ESfuncTempo)

void ESinstallFPS(char fps){
    LOCK_VARIABLE(EStempoFPS);
    LOCK_FUNCTION(ESfuncTempo);
    install_int(ESfuncTempo, (int)(1000/fps));
}

void ESsyncFPS(){
        while (!EStempoFPS){} //responsavel pelo FPS
        EStempoFPS = false;
}

void ESremoveFps(){
    remove_int(ESfuncTempo);
}


//}

//{Construtor e Destrutor
Especial::Especial(char Cod_)
{
    eCod = (cod)Cod_;
    exclusivo = true;
    tempoVida = 0;
    temMusica = false;
    animInicial = false;
    animNormal = false;
    switch (eCod){
        case PISCAPISCA: //{ 30
                         //Dar nome às animações e à música
                         exclusivo = true;
                         tempoVida = 180;
                         temMusica = true;
                         nomeMusica = "Sounds/especial.mid";
                         animInicial = true;
                         nomeAnimInicial = "FX/dark1.bmp";
                     break;//}
        case NENHUM://{ 0
                    break;//}
        case AUMENTA_SEMTOP_ADV_20: //{10
                        exclusivo = true;
                        tempoVida = 0;
                    break;//}
        case DIMINUE_VELO_PROPRIA: //{ 50
                        exclusivo = false;
                        tempoVida = 180;
                    break;//}
        case COLUNA_SEM_TOP_1: //{ 70
                        exclusivo = true;
                        tempoVida = 180;
                        animNormal = true;
                        nomeAnimNormal = "FX/especialColuna.bmp";
                        temMusica = false;
                        animInicial = true;
                        nomeAnimInicial = "FX/dark1.bmp";
                    break;//}
        case EMBARALHAR_TECLAS_COL_ESQ: //{ 33
                        animNormal = true;
                        nomeAnimNormal = "FX/DeslocaEsquerda.bmp";
                        tempoVida = 240;
                    break;//}
        case ROUBAR_ESPECIAL_ADV: //{ 52
                    break; //}
        case MATAR_TODAS: //{ 51
                        tempoVida = 120;
                    break;//}
        case ROUBAR_E_PARAR_ESPECIAL_ADV: //{ 53
                    break;//}
        case MATAR_NA_HORA_EXATA: //{ 32
                        tempoVida = 240;
                    break; //}
    }
    if ( animInicial) {
        animacaoInicial = new Animacao(nomeAnimInicial,0,0,0,0, false); //Checa a existência do arquivo
        delete animacaoInicial;
    }
    if ( animNormal) {
        animacaoNormal = new Animacao(nomeAnimNormal,0,0,0,0, false); //Checa a existência do arquivo
        delete animacaoNormal;
    }
    if ( temMusica){
        musica = load_midi(nomeMusica);//Checa a existência do arquivo.
        if (!musica){
            allegro_message("Impossivel carregar '%s'", nomeMusica);
            exit(1);
        }
        destroy_midi(musica);
    }
    ativo = false;
    contVida = 0;
}

Especial::~Especial()
{
}
//}

unsigned char Especial::getCode(){
    return (unsigned char)eCod;
}
bool Especial::getAnimInicial(){
    return animInicial;
}
BITMAP* Especial::getNome(){
    return nome;
}
void Especial::update(BITMAP* buffer){
    if (contVida++ >= tempoVida){ //verifica se ainda vive o especial
        ativo = false;
        if (temMusica){
            stop_midi();
            destroy_midi(musica);
        }
        if ( animNormal) delete animacaoNormal; //Só deleta caso especial não seja instantâneo
        return;
    }
    if ( animNormal) animacaoNormal->imprime(buffer); //Atualiza a animação normal
}
bool Especial::getAtivo(){
    return ativo;
}
void Especial::inicioEspecial(BITMAP* telaAntiga, char player){
    if ( animInicial) { //Carrega o arquivo.
        animacaoInicial = new Animacao(nomeAnimInicial, 13, 150 + 400*(player-1), 200, 1, false); //Carrega para o uso
    }
    if ( animNormal) {//tem que ser editado no switch
        animacaoNormal = new Animacao(nomeAnimNormal, 0,0, 0, 1, true); //Carrega para o uso
    }
    if ( temMusica){
        musica = load_midi(nomeMusica);//Carrega para o uso
        play_midi(musica, true);
    }
    switch (eCod){ //Serve só para bulir nas animações.. Utilizar o método Animacao::edit.
        case COLUNA_SEM_TOP_1:
                animacaoNormal->edit( 2, 60 + 400*(player-1), 150, 1, true); //Modificando bunitin
            break;
        case PISCAPISCA:
            break;
        case DIMINUE_VELO_PROPRIA:
            break;
        case AUMENTA_SEMTOP_ADV_20:
            break;
        case NENHUM:
            break;
        case EMBARALHAR_TECLAS_COL_ESQ:
                animacaoNormal->edit(3, 50 + 400*(player==1), 140,1,true);
            break;
    }
    ativo = true;
    contVida = 0;
    if (!animInicial) return;
//{ Resto   ANIMAÇÃO INICIAL É TOCADA AQUI!
    ESinstallFPS(12);
    BITMAP *buffer = create_bitmap(800, 600);
    BITMAP* tela = create_bitmap ( SCREEN_W, SCREEN_H);
    draw_sprite(tela, telaAntiga,0,0);
    for (char i = 0; !animacaoInicial->finalizada(); ++i){
        draw_sprite(buffer, tela,0,0);
        animacaoInicial->imprime(buffer);
        draw_sprite(screen, buffer, 0,0);
        ESsyncFPS();
    }
    //carrega as animacoes

    //Fica em loop até a animacao acabar
    destroy_bitmap(tela);
    destroy_bitmap(buffer);
    delete animacaoInicial;
    ESremoveFps();
//}
}
bool Especial::getExclusivo(){
    return exclusivo;
}
bool Especial::getTemMusica(){
    return temMusica;
}

/* TABELA DE ESPECIAIS
    0 < 10             SEM ESPECIAL
    10<30            ESPECIAL ATUANTE NO OUTRO JOGADOR QUE É RESOLVIDO NA CLASSE FASE
    30<50            ESPECIAL ATUANTE NO OUTRO JOGADOR QUE É RESOLVIDO NA CLASSE TOUPEIRA
    50<70            ESPECIAL ATUANTE NO PRÓPRIO JOGADOR QUE É RESOLVIDO NA CLASSE FASE
    70<90            ESPECIAL ATUANTE NO PRÓPRIO JOGADOR QUE É RESOLVIDO NA CLASSE TOUPEIRA
*/
