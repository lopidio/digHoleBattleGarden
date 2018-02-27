//Feito pelo Lopídio Guigui
//Espero q naum dê bug
//Se der, naum foi ele que fez
//Boa sorte a todos nós!
//Ave Lopídio!
#include "Toupeira.h"
#define FRAMES 8



SAMPLE* loadSom(const char* nomeSom){
    SAMPLE * som = load_wav(nomeSom);
    return som;
}
BITMAP* loadFigura(){
    static BITMAP* bmp = load_bitmap("FX/Toupeiras.pcx", NULL);
    return bmp;
}

//{Construtor e destrutor
Toupeira::Toupeira(char playerID, char ID, unsigned short KEY_KILL_TOUPEIRA_)
{
    toupeiraID = ID;
    KEY_KILL_TOUPEIRA = KEY_KILL_TOUPEIRA_;
    KEY_KILL = KEY_KILL_TOUPEIRA;
    ativa = false;
    figura = loadFigura(); //load_bitmap("FX/Toupeiras.pcx", NULL);
    if (!figura){
         allegro_message("Nao e possivel ler 'FX/Toupeiras.bmp'");
         exit(1);
    }
    x = (playerID - 1)*400; //Ajeitar esses valores!!!
    switch (ID){
        case 1: x+= 61;
            break;
        case 2: x+= 153;
            break;
        case 3: x+= 256;
            break;
        case 4: x+= 60;
            break;
        case 5: x+= 158;
            break;
        case 6: x+= 250;
            break;
        case 7: x+= 70;
            break;
        case 8: x+= 155;
            break;
        case 9: x+= 241;
            break;
    }
    y = -((ID-1)/3)*105 +210+ 170;
    keyAnt = true;
    carregaSons();
    anim = NADA;
    contVida = 0;
}
Toupeira::~Toupeira()
{
    //delete tecla;
    //destroy_bitmap(figura);
    //destroy_sample(somCria);
    /*SAMPLE* somCria, *somMorre1, *somMorre2, *somMorre3,*somMorre4, *somMorre5;
    SAMPLE* somMorre6,*somMorre7, *somMorre8, *somMorre9, *somMorre10, *somMorreEspecial;
    SAMPLE* somImpacto1, *somImpacto2, *somImpacto3, *somImpacto4;
    SAMPLE* estrelaAparecendo, *clicouErrado, *estrela, *matouCoelho;*/
}
//}

void Toupeira::carregaSons(){
    somCria =loadSom("Sounds/digpop.wav");
    somMorre1 = loadSom("Sounds/morre1.wav");
    somMorre1 = loadSom("Sounds/morre1.wav");
    somMorre2 = loadSom("Sounds/morre2.wav");
    somMorre3 = loadSom("Sounds/morre3.wav");
    somMorreEspecial = loadSom("Sounds/morreEspecial.wav");
    somMorre4 = loadSom("Sounds/morre4.wav");
    somMorre5 = loadSom("Sounds/morre5.wav");
    somMorre6 = loadSom("Sounds/morre6.wav");
    somMorre7 = loadSom("Sounds/morre7.wav");
    somMorre8 = loadSom("Sounds/morre8.wav");
    somMorre9 = loadSom("Sounds/morre9.wav");
    somMorre10 = loadSom("Sounds/morre10.wav");
    somImpacto1 = loadSom("Sounds/impacto1.wav");
    somImpacto2 = loadSom("Sounds/impacto2.wav");
    somImpacto3 = loadSom("Sounds/impacto3.wav");
    somImpacto4 = loadSom("Sounds/impacto4.wav");
    matouCoelho = loadSom("Sounds/matoucoelho.wav");
    estrela = loadSom("Sounds/estrela.wav");
    estrelaAparecendo = loadSom("Sounds/estrelaaparecendo.wav");
    clicouErrado = loadSom("Sounds/clicouerrado.wav");
}


void Toupeira::imprimir(BITMAP* buffer){
        if (!ativa) return;
        if (!brinde && !maligna)
            masked_blit(figura, buffer, frame*(figura->w/(3*FRAMES)), anim*(figura->h/4), x, y,(figura->w/(3*FRAMES)), figura->h/4);
        else if (!maligna)
            masked_blit(figura, buffer, (figura->w/3) + frame*(figura->w/(3*FRAMES)), anim*(figura->h/4), x, y,(figura->w/(3*FRAMES)), figura->h/4);
        else
            masked_blit(figura, buffer, 2*(figura->w/3) + frame*(figura->w/(3*FRAMES)), anim*(figura->h/4), x, y,(figura->w/(3*FRAMES)), figura->h/4);
}
void Toupeira::criar(unsigned char levandoEspecial_, char tempoVida_,bool brinde_, bool maligna_){
    maligna = maligna_;
    levandoEspecial = levandoEspecial_;
    tempoVida = tempoVida_;
    brinde = brinde_;
    ativa = true;
    contVida = 0;
    anim = APARECER;
    contMorte = 0;
    contApa = 0;
    contPerm = 0;
    contDesap = 0;
    KEY_KILL = KEY_KILL_TOUPEIRA;
    keyAnt = key[KEY_KILL];
    //fazer som!! SAMPLE* somCria;

}
bool Toupeira::getAtiva(){
    return ativa;
}
void Toupeira::fazerSom(char tipo){ //tipo: 1 -> Morte, 2 -> cria, 3 -> morre rápido, 4 Impacto, 5 clicou errado
    static char contSom = 0;
    if (tipo == 5) //clcou sem ter toupeira alguma
        play_sample( clicouErrado, 255, 128, 1000, false);
    if (!brinde && !maligna){ //Sons característicos duma toupeira comum
        if (tipo ==1) {
            switch (contSom){
                case 0: play_sample(somMorre1, 255, 128, 1000, false); break;
                case 1: play_sample(somMorre2, 255, 128, 1000, false); break;
                case 2: play_sample(somMorre3, 255, 128, 1000, false); break;
                case 3: play_sample(somMorre4, 255, 128, 1000, false); break;
                case 4: play_sample(somMorre5, 255, 128, 1000, false); break;
                case 5: play_sample(somMorre6, 255, 128, 1000, false); break;
                case 6: play_sample(somMorre7, 255, 128, 1000, false); break;
                case 7: play_sample(somMorre8, 255, 128, 1000, false); break;
                case 8: play_sample(somMorre9, 255, 128, 1000, false); break;
                case 9: play_sample(somMorre10, 255, 128, 1000, false); break;
            }
        }
        else if (tipo ==2){
            play_sample(somCria, 255, 128, 1000, false); //criar
        }
        else if (tipo == 3){
            play_sample(somMorreEspecial, 255, 128, 1000, false); //quando uma toupeira morre mto rápido
        }
        else if (tipo == 4){
            switch (contSom%4){
                case 0: play_sample(somImpacto1, 128,128, 1000, false);break;
                case 1: play_sample(somImpacto2, 255, 128, 1000, false); break;
                case 2: play_sample(somImpacto3, 255, 128, 1000, false); break;
                case 3: play_sample(somImpacto4, 255, 128, 1000, false); break;
            }
        }
    }
    else if (brinde){ //Sons da estrelinha
            if (tipo == 1  || tipo == 3)
                play_sample( estrela, 255, 128, 1000, false);
            else if (tipo == 2) //estrela aparecendo
                play_sample( estrelaAparecendo, 255, 128, 1000, false);
    }
    else if (maligna){ // "Som dos Coelhos"

        if (tipo == 2)
            play_sample(somCria, 255, 128, 1000, false); //criar
        else if (tipo == 1 || tipo == 3)
            play_sample(matouCoelho, 255, 128, 1000, false); //morreu :/
        else if (tipo == 4){
            switch (contSom%4){
                case 0: play_sample(somImpacto1, 128,128, 1000, false);break;
                case 1: play_sample(somImpacto2, 255, 128, 1000, false); break;
                case 2: play_sample(somImpacto3, 255, 128, 1000, false); break;
                case 3: play_sample(somImpacto4, 255, 128, 1000, false); break;
            }
        }
    }
    (++contSom)%=10;
}
void Toupeira::aparecer(){
    frame = contApa;
    anim = APARECER;
    if (contApa++ >= FRAMES - 1){
        anim = NADA;
    }
}
void Toupeira::morrer(char & especialProprio, char & semToupeira){
    if (contApa < 4 && anim == APARECER){
        fazerSom(3); //morrer rapidamente
        contApa = 5;
    }
    if (contMorte == 3 && contApa != 5){
        fazerSom(1); //morrer normalmente... Essa inveção de ser igual a 5, é só pra num tocar duas músicas
    }
    if (contMorte == 1){
        fazerSom(4); //som do impacto
    }
    frame = contMorte;
    anim = MORRER;
    if (contMorte == 1){
        if (brinde) especialProprio = MIN(4, especialProprio+1); //atualizar especiais
        if (maligna) semToupeira+=5; //se for do mal, perder 3 pontos
    }
    if (contMorte++ >= FRAMES - 1){
        ativa = false;
    }
}
bool Toupeira::key1x(){ //só retorna true quando ocorre o apertar do botão
    bool b = false;     //depois, msm q se mantenha apertado, retorna false!
    if (key[KEY_KILL] && !keyAnt)
        b = true;
    keyAnt = key[KEY_KILL];
    return b;
}
void Toupeira::permanecer(){
    frame = contPerm;
    anim = NADA;
    (++contPerm)%=FRAMES; //limita contPermanecer
}
void Toupeira::desaparecer(char & semToupeiras){
    frame = contDesap;
    anim = DESAPARECER;
    if (contDesap++ >= FRAMES - 1){
        ativa = false;
        if (/*levandoEspecial == 0 && */!brinde && !maligna) semToupeiras+=2; //Só perco ponto caso seja uma Toupeira comum
    }
}
void Toupeira::update(BITMAP* buffer, char& semToupeiras, char& especialProprio){
    bool b = key1x();
    if (b && !ativa ){ //CLICOU ERRADO
        semToupeiras+=1;
        fazerSom(5);
    }
    if (!ativa)
        return;
    contVida++;
    if (contVida == 3) {
        fazerSom(2);
    }

    if (b || anim == MORRER)
        morrer(especialProprio, semToupeiras);
    else if (contVida >= tempoVida - FRAMES || anim == DESAPARECER)
        desaparecer(semToupeiras);
    else if (contVida <= FRAMES || anim == APARECER)
        aparecer();
    else
        permanecer();

    if (levandoEspecial == 0)
        imprimir(buffer);
    else
        especiais(buffer);
}

void Toupeira::especiais(BITMAP* buffer){
         switch (levandoEspecial){
            case 30: //{ PISCA PISCA
                    if (frame%3 <= 1 || anim == MORRER) imprimir(buffer);
                break;//}
            case 70: //{ Coluna 1 sem aparecer nada
                    if (contVida >= FRAMES/2 && toupeiraID%3 == 1) anim = MORRER;
                    imprimir(buffer);
                break;//}
            case 33: //{ Desloca a tecla que mata para a esquerda
                    switch ( KEY_KILL_TOUPEIRA){ //Tecla principal da toupeira
                        case KEY_Q: KEY_KILL = KEY_W; break;
                        case KEY_W: KEY_KILL = KEY_E; break;
                        case KEY_E: KEY_KILL = KEY_Q; break;
                        case KEY_A: KEY_KILL = KEY_S; break;
                        case KEY_S: KEY_KILL = KEY_D; break;
                        case KEY_D: KEY_KILL = KEY_A; break;
                        case KEY_Z: KEY_KILL = KEY_X; break;
                        case KEY_X: KEY_KILL = KEY_C; break;
                        case KEY_C: KEY_KILL = KEY_Z; break;
                        case KEY_7_PAD: KEY_KILL = KEY_8_PAD; break;
                        case KEY_8_PAD: KEY_KILL = KEY_9_PAD; break;
                        case KEY_9_PAD: KEY_KILL = KEY_7_PAD; break;
                        case KEY_4_PAD: KEY_KILL = KEY_5_PAD; break;
                        case KEY_5_PAD: KEY_KILL = KEY_6_PAD; break;
                        case KEY_6_PAD: KEY_KILL = KEY_4_PAD; break;
                        case KEY_1_PAD: KEY_KILL = KEY_2_PAD; break;
                        case KEY_2_PAD: KEY_KILL = KEY_3_PAD; break;
                        case KEY_3_PAD: KEY_KILL = KEY_1_PAD; break;
                    }
                    imprimir(buffer);
                break;//}
            case 32: //{ Matar na hora exata
                    if (contVida >= tempoVida/2) circlefill(buffer, x + 45 , y -10, 10, makecol(contVida*100,contVida*200,contVida*55)); //Mudar essas cores
                    if (anim == MORRER && contVida <= tempoVida/2)
                        anim = NADA;
                imprimir(buffer);
                break;//}
            default:
                imprimir(buffer);
         }
}
void Toupeira::desativar(){
    ativa = false;
}
void Toupeira::matar(){
    if (ativa && contVida > FRAMES)
        anim = MORRER;
}
