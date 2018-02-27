#include "Life.h"
#define FRAMES 4


Life::Life()
{
    borda = load_bitmap("FX/bordalife.pcx", NULL);
    figura = load_bitmap("FX/efeitoLife.pcx", NULL);
    if (!borda){
        allegro_message("Erro ao ler 'FX/bordalife.pcx'");
        exit(1);
    }
    if (!figura){
        allegro_message("Erro ao ler 'FX/efeitoLife.pcx'");
        exit(1);
    }
    contFrame =0;
    y = 80;
    x = (SCREEN_W - borda->w)/2 + 3;
    semTopAnt = 50;
}

Life::~Life()
{
    destroy_bitmap(borda);
    destroy_bitmap(figura);
}

void Life::imprime (BITMAP* buffer, char semTop){
    if (semTop > semTopAnt)
        semTopAnt+= ( semTop - semTopAnt)/10 + 1; //Dá um efeitozinho bonitinho pacas no life!
    else if (semTop < semTopAnt)
        semTopAnt-= ( semTopAnt - semTop)/10 + 1;
    semTopAnt = MIN( 100, semTopAnt);
    semTopAnt = MAX(0, semTopAnt);
    float div = (float)semTopAnt/100;
    div *= 500;
    masked_blit(figura, buffer, div +5 ,contFrame*(figura->h/FRAMES), x, y + 2, 493, 42);

    draw_sprite(buffer, borda, 150, y);
    //textprintf(buffer, font, 10,10, makecol(100,100,100), "Oi %d %f %d", contFrame, div, y);
    (++contFrame)%=FRAMES;
}

void Life::finalizar(BITMAP * buffer, char semTop){
    semTopAnt = semTop;
    imprime(buffer, semTop);
}
