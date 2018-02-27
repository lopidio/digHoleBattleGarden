#include "Animacao.h"



Animacao::Animacao(){
}
Animacao::Animacao(const char* nomeArquivo,char numFrames_, short x_, short y_, char numAnimacoes_ = 1, bool loop_ = false){
        figura = load_bitmap(nomeArquivo, NULL);
        if (!figura){
            allegro_message("Erro ao abrir arquivo '%s'", nomeArquivo);
            exit(1);
        }
        numFrames = numFrames_;
        loop = loop_;
        numAnimacoes = numAnimacoes_;
        x = x_;
        y = y_;
        contFrame = 0;
        contAnim = 0;
        min = 0;
        max = numFrames - 1;
}
Animacao::~Animacao()
{
    destroy_bitmap(figura);
}

void Animacao::edit( char numFrames_, short x_, short y_, char numAnimacoes_, bool loop_){
        this->numFrames = numFrames_;
        this->loop = loop_;
        this->numAnimacoes = numAnimacoes_;
        this->x = x_;
        this->y = y_;
        max = numFrames - 1;
}
void Animacao::inverte(){
    BITMAP* aux = create_bitmap(figura->w, figura->h);
    for (int i = 0; i < figura->w; i+=(figura->w/numFrames)){
        blit (figura, aux, i, 0, figura->w-i- figura->w/numFrames,0,figura->w/numFrames, figura->h);
    }
    destroy_bitmap(figura);
    figura = aux;
}
void Animacao::inverteFigura(){
    BITMAP* aux = create_bitmap(figura->w, figura->h);
    BITMAP* aux2 = create_bitmap(figura->w/numFrames, figura->h);
    clear_to_color(aux, makecol(255,0,255));
    for (int i = 0; i < figura->w; i+=(figura->w/numFrames)){
        blit (figura, aux2, i, 0, 0,0,figura->w/numFrames, figura->h);
        draw_sprite_h_flip(aux, aux2, i,0);
    }
    destroy_bitmap(figura);
    destroy_bitmap(aux2);
    figura = aux;
}
void Animacao::setPosicao(short x_, short y_){
    x = x_;
    y = y_;
}
void Animacao::imprime(BITMAP* buffer){
    if (loop){
        if (contFrame > max){
            contFrame = min;
        }
    }
    else{
        if (contFrame >= numFrames - 1) contFrame  = numFrames - 1;
    }
    masked_blit(figura, buffer, contFrame * (figura->w/numFrames), contAnim * (figura->h/numAnimacoes), x, y, (figura->w/numFrames),(figura->h/numAnimacoes));
    ++contFrame;
}
void Animacao::setAnimacao(char anim){
    if (anim != contAnim) contFrame= 0;
    contAnim = anim%numAnimacoes;
}

bool Animacao::finalizada(){
    return ( !loop&&(contFrame >= numFrames-1));
}

void Animacao::defineLoop(unsigned char cont_, unsigned char min_, unsigned char max_){
    loop = true;
    contFrame =cont_ -1;
    min = min_ - 1;
    max = max_ - 1;
}

void Animacao::defineLoop(unsigned char min_, unsigned char max_){
    loop = true;
    if (contFrame > max_) contFrame = min_ - 1;
    if (contFrame < min_) contFrame = min_ - 1;
    min = min_ - 1;
    max = max_ - 1;
}
