//Feito pelo Lopídio Guigui
//Espero q naum dê bug
//Se der, naum foi ele que fez
//Boa sorte a todos nós!
//Ave Lopídio!
#include "Personagem.h"
#define FRAMES 3

//{        TIMER!!!
volatile bool PEtempoFPS = true;
void PEfuncTempo(void)
{
    PEtempoFPS = true;
}
END_OF_FUNCTION(PEfuncTempo)

void PEinstallFPS(char fps){
    LOCK_VARIABLE(PEtempoFPS);
    LOCK_FUNCTION(PEfuncTempo);
    install_int(PEfuncTempo, (int)(1000/fps));
}

void PEsyncFPS(){
        while (!PEtempoFPS){} //responsavel pelo FPS
        PEtempoFPS = false;
}

void PEremoveFps(){
    remove_int(PEfuncTempo);
}


//}

void escureceBitmap(BITMAP* bmp){
    for (short lar = 0; lar< bmp->w; lar++)
        for (short alt = 0; alt < bmp->h; alt++){
            int cor = getpixel(bmp, lar, alt);
            putpixel(bmp, lar, alt, makecol( getr(cor)/2, getg(cor)/2, getb(cor)/2));
        }
}

//{  Construtor e Destrutor
Personagem::Personagem(){
}
Personagem::Personagem(char cod_)
{
    cod = cod_;
    contFrame = 0;
    somEspecial = load_sample("Sounds/especialPersonagem.wav"); //Ser carregado junto com os especiais.. no método carrega Eseciais.
    if (!somEspecial){
        allegro_message("Erro ao carregar 'Sounds/especialPersonagem.wav'");
        exit(1);
    }
    //destruir somEspecial, e carregar de novo no método carregaEspeciais..
    nomeMusica = "Sounds/andromedario.mid";
    nomeBackground = "Fx/Background.pcx";
    if (cod == 1) nomeFigura = "Fx/Personagem.bmp"; //Esse if é só pra teste tb..
    else nomeFigura = "Fx/Personagem2.bmp";

    figura = load_bitmap(nomeFigura, NULL); //Diferente dos outros, esse não vai ficar sendo carregado e descarregado todo tempo da memória
    if (!figura){
        allegro_message("erro ao carregar '%s'", nomeFigura);
        exit(1);
    }
    carregaObj(); //Checar existência...
    descarregaObj();

    switch (cod){
        case 1:/*Dar o nome dos arquivos de música e background*/break;
        case 2:break;
        case 3:break;
    }


}
Personagem::~Personagem(){

}
//}

void Personagem::carregaEspeciais(){ //Switch, iniciando especial de cada player
    if (cod == 1){
        especial.push_back(Especial(32));//SÓ  //30 = PISCA PISCA
        especial.push_back(Especial(12));//   PARA // 10 = aumentar semTop do outro em 20
        especial.push_back(Especial(52));//         TESTES
        especial.push_back(Especial(33));//                 APAGAR ESSAS LINHAS NO FINAL
    }
    else{
        especial.push_back(Especial(70));//SÓ  //30 = PISCA PISCA
        especial.push_back(Especial(50));//   PARA // 10 = aumentar semTop do outro em 20
        especial.push_back(Especial(51));//         TESTES
        especial.push_back(Especial(10));//                 APAGAR ESSAS LINHAS NO FINAL
    }
}
BITMAP* Personagem::getNome(){
    return nome;
}
MIDI* Personagem::getMusica(){
    return musica;
}
BITMAP* Personagem::getBackground(){
    return background;
}
Especial* Personagem::getEspecial(char indice){
    return &especial[indice - 1]; // é só pra garantir que não vai extrapolar os limites.
}
void Personagem::vitoria(BITMAP* buffer, char playerID_){
    (++contFrame)%=FRAMES;
    short x = 150+ (playerID_ - 1)*400; //ajeitar esses valores!
    short y = 200; //Ajeitar esses valores!
    masked_blit(figura, buffer, contFrame*(figura->w/FRAMES), 2*(figura->h/3), x, y, figura->w/FRAMES, figura->h/3);
}
void Personagem::derrota(BITMAP* buffer, char playerID_){
     (++contFrame)%=FRAMES;
    short x = 150+ (playerID_ - 1)*400; //ajeitar esses valores!
    short y = 200; //Ajeitar esses valores!
    masked_blit(figura, buffer, contFrame*(figura->w/FRAMES), (figura->h/3), x, y, figura->w/FRAMES, figura->h/3);
 }
void Personagem::escolha(BITMAP* buffer, char playerID_){
     (++contFrame)%=FRAMES;
    short x = 150+ (playerID_ - 1)*400; //ajeitar esses valores!
    short y = 200; //Ajeitar esses valores!
    masked_blit(figura, buffer, contFrame*(figura->w/FRAMES), 0, x, y, figura->w/FRAMES, figura->h/3);
 }
void Personagem::especialAnim(BITMAP* telaAntiga, char playerID){
    //Tocar uma musicazinha show de bolas aqui!
    short x = 150+ (playerID - 1)*400; //ajeitar esses valores!
    short y = 200; //Ajeitar esses valores!
    PEinstallFPS(12);
    char indice = -1;
    contFrame = 0;
    BITMAP*tela = create_bitmap( SCREEN_W, SCREEN_H);
    draw_sprite(tela, telaAntiga,0,0);
    escureceBitmap(tela);
    BITMAP* buffer = create_bitmap( SCREEN_W, SCREEN_H);
    while (indice++ < 6){ // 1 segundo!
        (++contFrame)%=FRAMES;
        draw_sprite(buffer, tela, 0,0);
        masked_blit(figura, buffer, contFrame*(figura->w/FRAMES), 0, x, y, figura->w/FRAMES, figura->h/3);
        draw_sprite(screen, buffer,0,0);
        if (indice == 3)     play_sample(somEspecial, 255,128,1000,false);
        PEsyncFPS();
    }
    destroy_bitmap(tela);
    destroy_bitmap(buffer);
    PEremoveFps();

}
/*            TABELA DE ESPECIAIS
    0 < 10             SEM ESPECIAL
    10<30            ESPECIAL ATUANTE NO OUTRO JOGADOR QUE É RESOLVIDO NA CLASSE FASE
    30<50            ESPECIAL ATUANTE NO OUTRO JOGADOR QUE É RESOLVIDO NA CLASSE TOUPEIRA
    50<70            ESPECIAL ATUANTE NO PRÓPRIO JOGADOR QUE É RESOLVIDO NA CLASSE FASE
    70<90            ESPECIAL ATUANTE NO PRÓPRIO JOGADOR QUE É RESOLVIDO NA CLASSE TOUPEIRA
*/

void Personagem::carregaObj(){ //Carrega musica e background, checar se existe arquivos
    musica = load_midi(nomeMusica);
    background = load_bitmap(nomeBackground, NULL);
    if (!musica){
         allegro_message("Nao e possivel ler '%s'", nomeMusica);
         exit(1);
    }
    if (!background){
         allegro_message("Nao e possivel ler '%s'", nomeFigura);
         exit(1);
    }
}
void Personagem::descarregaObj(){ //Descarrega musica e background
    destroy_bitmap(background);
    destroy_midi(musica);
}
