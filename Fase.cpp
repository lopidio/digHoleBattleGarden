//Feito pelo Lopídio Guigui
//Espero q naum dê bug
//Se der, naum foi ele que fez
//Boa sorte a todos nós!
//Ave Lopídio!
#include "Fase.h"
#include <iostream>

//{        TIMER!!!
volatile bool tempoFPS = true;
void funcTempo(void)
{
    tempoFPS = true;
}
END_OF_FUNCTION(funcTempo)

void installFPS(char fps){
    LOCK_VARIABLE(tempoFPS);
    LOCK_FUNCTION(funcTempo);
    install_int(funcTempo, (int)(1000/fps));
}

void syncFPS(){
        while (!tempoFPS){} //responsavel pelo FPS
        tempoFPS = false;
}

void removeFps(){
    remove_int(funcTempo);
}


//}

void loading(){ //Page flip
    BITMAP* bmp = create_video_bitmap(800,600);
    #define numFrame 8
    static char step = 1, contFrame = 0;
    BITMAP* gui = load_bitmap("Fx/guilogo.pcx", NULL);
    if (!gui){
        allegro_message("Erro ao ler arquivo 'Fx/guilogo.pcx'");
        exit(1);
    }
    contFrame+=step;
    if (contFrame >= 7 || contFrame <1) step*=-1;
    blit( gui, bmp, contFrame*(gui->w/8),0,400-gui->w/16,300-gui->h/2, gui->w/8,gui->h);
    show_video_bitmap(bmp);
    destroy_bitmap(bmp);
    destroy_bitmap(gui);
}
END_OF_FUNCTION(loading)


//{ Construtor e Destrutor
Fase::Fase(Personagem* pe1, Personagem* pe2, char frames)
{
    install_int(loading, 1000/frames); //Animação do loading!
    variadorVelo = 3*(AL_PI/2);
    FPS = frames;
    enter = new Tecla(KEY_ENTER);
    p1 = new Player(pe1, 1);
    p2 = new Player(pe2, 2);
    p1->getPersonagem()->carregaObj();
    rest(1000);
    musica = p1->getPersonagem()->getMusica(); //Pega a música do p1
    background = p1->getPersonagem()->getBackground();//pega o cenário do p1
    //{ inicia as animações e Bitmaps
    trofeu1 = new Animacao("Fx/trofeu.bmp", 6,0,60,3, true);
    trofeu2 = new Animacao("Fx/trofeu.bmp", 6,650,60,3, true);
    trofeu2->inverteFigura();
    terra1 =  new Animacao("Fx/terra.pcx", 4 , 110, 560, 1, true);
    terra2 =  new Animacao("Fx/terra.pcx", 4 , 610, 560, 1, true);
    terra3 =  new Animacao("Fx/terra.pcx", 4 , 710, 560, 1, true);
    barraEspeciais1 = new Animacao("Fx/estrelinhas.bmp",7, 0, 200, 5, true);
    barraEspeciais2 = new Animacao("Fx/estrelinhas.bmp",7, 740, 200, 5, true);
    terra2->defineLoop(2,1,4); //Só pra mudar o frame atual, pra não ficar com os msms frames que as outras
    terra1->inverte();
    barraEspeciais1->defineLoop(1,3,6);
    barraEspeciais2->defineLoop(1,3,6);
    trofeu1->defineLoop(1,3,6);
    trofeu2->defineLoop(1,3,6);
    num = load_bitmap("Fx/Numeros.bmp", NULL);
    if (!num){
        allegro_message("Impossivel carregar 'Fx/Numeros.bmp");
        exit(1);
    }
    pause = load_bitmap("Fx/Pause.bmp", NULL);
    if (!pause){
        allegro_message("Impossivel carregar 'Fx/Pause.bmp");
        exit(1);
    }
    destroy_bitmap(pause);
    menuPause = load_bitmap("Fx/MenuPause.bmp", NULL);
    if (!pause){
        allegro_message("Impossivel carregar 'Fx/MenuPause.bmp");
        exit(1);
    }
    destroy_bitmap(menuPause);

//} animações
    proximo = NENHUM;
    roundP1 = 0;
    roundP2 = 0;
    remove_int(loading);

    video_page[0] = create_video_bitmap(SCREEN_W, SCREEN_H);
    video_page[1] = create_video_bitmap(SCREEN_W, SCREEN_H);
    viraPagina = false;
            std::cout << " pagina0: " << video_page[0] << std::endl;
            std::cout << " pagina1: " << video_page[1] << std::endl;

    animRound();
    carregandoTela();
}

Fase::~Fase()
{
    delete enter;
    delete p1;
    delete p2;
    destroy_midi(musica);
    destroy_bitmap(num);
    destroy_bitmap(background);
    delete terra1;
    delete terra2;
    delete terra3;
    delete barraEspeciais1;
    delete barraEspeciais2;
    delete trofeu1;
    delete trofeu2;
    destroy_bitmap(video_page[0]);
    destroy_bitmap(video_page[1]);
}

//}

void Fase::carregandoTela(){ //Carrega o background
    p1->carregarObj();//Carrega e muda a cor do tabuleiro
    p2->carregarObj();
    draw_sprite(background, p1->getTabuleiro(), 50, 200);
    draw_sprite(background, p2->getTabuleiro(), 450, 200);
    p1->descarregarObj();
    p2->descarregarObj();
}

void Fase::animRound(){ //Double Buffer!
    play_midi(musica, true);
    roundsNome =  new Animacao("Fx/RoundNome.pcx", 6 , 400 -535/2, 300-114/2, 1, false);
    roundsNum =  new Animacao("Fx/RoundNum.pcx", 6 , 600 , 300-114/2, 3, false);

    roundsNum->setAnimacao(roundP1 + roundP2);
    installFPS(FPS);
    //BITMAP * buffer = create_bitmap( SCREEN_W, SCREEN_H);  //declarando as páginas do page flipping

    for (short i = 0; i <2*FPS; i++){ //Tempinho parado
        viraPagina = !viraPagina;
        draw_sprite(video_page[viraPagina], background,0,0);
        trofeu1->imprime(video_page[viraPagina]);
        trofeu2->imprime(video_page[viraPagina]);
//        draw_sprite(screen, buffer,0,0);
        show_video_bitmap(video_page[viraPagina]);
        syncFPS();
    }
                    std::cout << " Saiu!!\n";

    for (char i = 1; i <2*FPS; i++, viraPagina = viraPagina^true){ //Animação do nome e do número
        draw_sprite(video_page[viraPagina], background,0,0);
        roundsNome->imprime(video_page[viraPagina]);
        roundsNum->imprime(video_page[viraPagina]);
        trofeu1->imprime(video_page[viraPagina]);
        trofeu2->imprime(video_page[viraPagina]);
        show_video_bitmap(video_page[viraPagina]);
        syncFPS();
    }

    removeFps();
    //destroy_bitmap(buffer);
    delete roundsNome;
    delete roundsNum;
}
void Fase::variaVelo(){
        if (variadorVelo >= 2*AL_PI)
            variadorVelo = 0;
        veloGeral = 5 + (4)*sin( variadorVelo+= ((2*AL_PI)/(FPS*60*20))); //faz a velocidade geral variar entre 1 e 9 Topeiras/segundo
        static char semTop1ant=50, semTop2ant=50;                                  // 1 ciclo completo dura 10 minutos
        char variacao1 = p1->semTop - semTop1ant;
        char variacao2 = p2->semTop - semTop2ant;
        if ( semTop1ant >= 95 || semTop2ant >=95){ //CAso reinicie um round!
            if (p1->semTop == 50 && p2->semTop == 50){
                variacao1 = 0;
                variacao2 = 0;
                semTop1ant = 50;
                semTop2ant = 50;
            }
        }
        if (variacao1 == variacao2){
            p1->semTop = semTop1ant;
            p2->semTop = semTop2ant;
        }
        else if (variacao1 > variacao2){ //regula os semTop...
            variacao1-= variacao2;
            p2->semTop-=variacao1;
            p1->semTop = 100 - p2->semTop;
        }
        else if (variacao2 > variacao1){
            variacao2-= variacao1;
            p1->semTop-=variacao2;
            p2->semTop = 100 - p1->semTop;
        }
        semTop1ant = p1->semTop;
        semTop2ant = p2->semTop;

        p1->veloTop = (int)((p2->semTop/30)+(FPS/veloGeral)); //regula os veloTop
        p2->veloTop = (int)((p1->semTop/30)+(FPS/veloGeral));
        p1->veloTop = MAX(p1->veloTop, 1);
        p2->veloTop = MAX(p2->veloTop, 1);
}

void Fase::fimRound(BITMAP* telaAntiga_, Player* pVencedor, Player* pDerrotado){ //é responsável pelo jogo sempre que acaba algum round //Double buffer
    p1->reiniciarPlayer();
    p2->reiniciarPlayer();
    variadorVelo+= 120*((2*AL_PI)/(FPS*60*20));
    (pVencedor->getID() == 1)? roundP1++: roundP2++; //incrementa contador de rounds
    trofeu1->setAnimacao(roundP1);
    trofeu2->setAnimacao(roundP2);

//    BITMAP* buffer = create_bitmap( SCREEN_W, SCREEN_H);
    for (char i = 0; i <2.5*FPS; i++, viraPagina = viraPagina ^true){ //Animação da taça aparecendo
         draw_sprite(video_page[viraPagina], background,0,0);
         trofeu1->imprime(video_page[viraPagina]);
         trofeu2->imprime(video_page[viraPagina]);
         show_video_bitmap(video_page[viraPagina]);
         syncFPS();
    }
//    destroy_bitmap(buffer);
    if (roundP1 >= 2){
        return fimJogo(p1, p2);
    }
    else if (roundP2 >= 2){
        return fimJogo(p2, p1);
    }
        //textprintf_ex(screen, font,10,20,makecol(128,255,128),-1, "Mais que burro, player %d perdeu o round!", pDerrotado->getID());
    animRound();
    //textprintf_ex(screen, font,10,10,makecol(0,128,255),-1, "rounds p1 %d         p2 %d", roundP1, roundP2);
}

void Fase::fimJogo(Player* pVencedor, Player* pDerrotado){//Double buffer
    //BITMAP* buffer = create_bitmap( SCREEN_W, SCREEN_H);
    //Tocar a musica do buneco vencedor!
    for (; !enter->x1(); viraPagina = viraPagina ^true){
         enter->update();
         draw_sprite( video_page[viraPagina], background,0,0);
         trofeu1->imprime(video_page[viraPagina]);
         trofeu2->imprime(video_page[viraPagina]);
         pVencedor->vitoria(video_page[viraPagina]);
         pDerrotado->derrota(video_page[viraPagina]);
         show_video_bitmap(video_page[viraPagina]);
         syncFPS();
    }
    enter->update();
    roundP1 = 0;
    roundP2 = 0;
    trofeu1->setAnimacao(roundP1);
    trofeu2->setAnimacao(roundP2);
}

void Fase::desenharTela(BITMAP* buffer){ //chamado em toda iteração
    //draw_sprite(buffer, background,0,0);
    masked_stretch_blit(background, buffer, 0, 0, background->w, background->h, 0, 0, SCREEN_W, SCREEN_H);
    terra1->imprime(buffer);
    terra2->imprime(buffer);
    terra3->imprime(buffer);
    life.imprime(buffer, p1->semTop);
    if (p1->is_especialAtivo()){
        barraEspeciais1->defineLoop(7,7,7);
    }
    else barraEspeciais1->defineLoop(3,6);
    if (p2->is_especialAtivo()){
        barraEspeciais2->defineLoop(7,7,7);
    }
    else barraEspeciais2->defineLoop(3,6);
    barraEspeciais1->setAnimacao(p1->especialProprio);
    barraEspeciais2->setAnimacao(p2->especialProprio);
    barraEspeciais1->imprime(buffer);
    barraEspeciais2->imprime(buffer);
    trofeu1->imprime(buffer);
    trofeu2->imprime(buffer);
    //desenhar nome dos buneco e dos especial
}
void Fase::especial(BITMAP* buffer, Player* pRemetente, Player* pDestinatario){//Chamado duas vezes em toda iteração
    //fazer voltar a musica caso especial tenha acabado
    if (!pRemetente->requisitarEspecial() && !pRemetente->is_especialAtivo()) //se não tiver querendo usar o especial e não tiver usando nenhum especial
        return;
    if ( pRemetente->requisitarEspecial()){ //Análise do requisito!
        if (!pDestinatario->is_especialAtivo()) //Se o outro player não tiver usando nenuhm especial
            pRemetente->ativarEspecial();
        else if (!pDestinatario->getEspecial()->getExclusivo()) //Se tiver usando especial, e não for exclusivo
            pRemetente->ativarEspecial();
        else //Caso nada, saia daqui pq tu não pode usar o especial!
            return;
// COMEÇA AQUI!!! TOCAR SOM!
        if ( pRemetente->getEspecial()->getTemMusica())
            midi_pause();
        unsigned char cod = pRemetente->getEspecial()->getCode(); //Pegar o código!
        if (cod >= 10 && cod < 50)
                pDestinatario->levandoEspecial = cod; //O player q tá levando especial, saber q tá levando especial
        if (cod >=50 && cod < 90)
                pRemetente->levandoEspecial = cod; //O player q tá levando especial, saber q tá levando especial
        if ( pRemetente->getEspecial()->getAnimInicial() ) pRemetente->getPersonagem()->especialAnim(buffer, pRemetente->getID());//Se tiver animação inicial, fazer a animação do personagem tb.
        pRemetente->getEspecial()->inicioEspecial(buffer, pRemetente->getID()); //Fazer a primeira animacao do especial
        if ( (cod >=10 && cod < 30) || (cod >=50 && cod <70)){ // Se o especial for resolvido nessa classe aqui. ||
            switch (cod){ //Efeito do especial no início
                case 10: //{ Aumenta semTop adv em 20
                    pDestinatario->semTop+=20;
                break;//}
                case 11: //{ Aumenta semTop adv em 15
                    pDestinatario->semTop+=15;
                break;//}
                case 12: //{ Aumenta semTop adv em 10
                    pDestinatario->semTop+=10;
                break;//}
                case 52: //{ Rouba a quantidade de espqcial do adversario
                    pRemetente->desativarEspecial();
                    pRemetente->especialProprio = pDestinatario->especialProprio;
                break; //}
                case 53: //{ Rouba a quantidade de espqcial do adversario
                    pRemetente->desativarEspecial();
                    pRemetente->especialProprio = pDestinatario->especialProprio;
                    pDestinatario->desativarEspecial();
                break; //}
            }
        }
        return;
    }
    if (pRemetente->is_especialAtivo()){  // UPDATE DO ESPECIAL!!!
        unsigned char cod = pRemetente->getEspecial()->getCode();
        switch (cod){ //Efeito do especial em cada rodada
            case 50:
                pRemetente->veloTop = 24; //1 Toupeira em 2 segundos, em média.
            break;
            case 51: //Mata todas as toupeiras em campo
                    pRemetente->matarToupeiras();
            break;
        }
        pRemetente->getEspecial()->update(buffer); //Atualizar a animação do especial e saber se ainda tá vivo
        if (!pRemetente->getEspecial()->getAtivo()){ //Se o especial não for mais ativo!
            if (cod >= 10 && cod < 50)
                pDestinatario->levandoEspecial = 0; //O jogador alvo não leva mais o especial
            if (cod >= 50 && cod < 90)
                pRemetente->levandoEspecial = 0; //O jogador alvo não leva mais o especial
            if ( pRemetente->getEspecial()->getTemMusica()){
                play_midi(musica, true);
            }
            pRemetente->desativarEspecial(); //desativar especial!
        }
        return;
    }
}

/*            TABELA DE ESPECIAIS
    0 < 10             SEM ESPECIAL
    10=<30          ESPECIAL ATUANTE NO OUTRO JOGADOR QUE É RESOLVIDO NA CLASSE FASE
    30<50            ESPECIAL ATUANTE NO OUTRO JOGADOR QUE É RESOLVIDO NA CLASSE TOUPEIRA
    50=<70          ESPECIAL ATUANTE NO PRÓPRIO JOGADOR QUE É RESOLVIDO NA CLASSE FASE
    70<90            ESPECIAL ATUANTE NO PRÓPRIO JOGADOR QUE É RESOLVIDO NA CLASSE TOUPEIRA
*/

char Fase::principal(){ /**retorna: 0-> selecionar; 1-> menu principal; 2-> reiniciar*/
    installFPS(FPS);

    for (; proximo == NENHUM; viraPagina = viraPagina^true){ //     //Loop principal!
        desenharTela(video_page[viraPagina]); //desenha a tela!
        p1->update(video_page[viraPagina]); //updatando evilbari
        p2->update(video_page[viraPagina]);
        variaVelo(); //Função responsável por ajustar os atributos da Fase
        especial(video_page[viraPagina], p1, p2); //chamando os especiais
        especial(video_page[viraPagina], p2, p1);
        if (p1->semTop >= 100 || p2->semTop>= 100){ //Se acabou o round!
            life.finalizar(screen, p1->semTop); //Ajeita a animação do life!
            (p1->semTop >= 100)? fimRound(video_page[viraPagina], p2, p1):  fimRound(video_page[viraPagina], p1, p2);//Cahamando a função fimRound
            installFPS(FPS);
            continue;
        }
        if (enter->x1()) {
            pausar(video_page[viraPagina]);
            if ( proximo != NENHUM) break;
        }
        desenhaNumero(100-p1->semTop,3,10,10, video_page[viraPagina]);
        desenhaNumero(100-p2->semTop,3,740,10, video_page[viraPagina]);
        desenhaNumero(p1->semTop + p2->semTop,3,370,10, video_page[viraPagina]);
        //textprintf_ex(video_page[i], font,0,40,makecol(255,128,0),-1, "semTop1 %d         veloTop1 %d     soma %d", p1->semTop, p1->veloTop, p1->semTop+p2->semTop);

        show_video_bitmap(video_page[viraPagina]); //desenha na tela do pc
        enter->update();
        syncFPS();
    }
    removeFps();
    return proximo;
}

void Fase::desenhaNumero(unsigned int valor, char precisao, short x, short y, BITMAP* buffer){
    char dimensao = num->w/10;
    for (;precisao>0 ;precisao--)
    {
        masked_blit(num, buffer, (valor%10)*dimensao,0, (precisao-1)*dimensao + x,y,dimensao,num->h);
        valor/=10;
    }
}

void Fase::pausar(BITMAP* telaAntiga){
    std::vector<Tecla> tecla;
    tecla.push_back(Tecla(KEY_UP));
    tecla.push_back(Tecla(KEY_DOWN));
    tecla.push_back(Tecla(KEY_RIGHT));
    tecla.push_back(Tecla(KEY_LEFT));
    int volWave = 100, volMid = 100;
    pause = load_bitmap("Fx/Pause.bmp", NULL);
    menuPause = load_bitmap("Fx/MenuPause.bmp", NULL);
    BITMAP *fundo = create_bitmap(800, 600);
    draw_sprite(fundo, telaAntiga,0,0);
    draw_sprite(fundo, pause, 400 - pause->w/2,300- pause->h/2);
    short larg = menuPause->w/2, alt = menuPause->h/6;
    char linha = 0;
    enter->update();
    for (; true; viraPagina = viraPagina^true){
        if (enter->x2(3) || (enter->x1() && linha <= 3)){
            if (linha == 3) proximo = MENU_PRINCIPAL;
            if (linha == 1) proximo = REINICIAR;
            if (linha == 2) proximo = SELECIONAR;
            break;
        }
        linha%=6;
        enter->update();
        for (char i = 0; i < tecla.size(); i++)
            tecla[i].update();

        if (tecla[1].perFrame(2))
            (++linha)%=6;
        if (tecla[0].perFrame(2))
            (linha>0)? (--linha): linha = 5;

        if (linha==4){
            if (tecla[2].x2(3))
                set_volume( volMid + 50, volWave);
            else if (tecla[3].x2(3))
                set_volume( volMid - 50, volWave);
            else if (tecla[2].perFrame(1))
                set_volume( volMid + 1, volWave);
            else if (tecla[3].perFrame(1))
                set_volume( volMid - 1, volWave);
        }
        if (linha==5){
            if (tecla[2].x2(3))
                set_volume( volMid, volWave + 50);
            else if (tecla[3].x2(3))
                set_volume( volMid, volWave - 50);
            else if (tecla[2].perFrame(1))
                set_volume(volMid, volWave + 1);
            else if (tecla[3].perFrame(1))
                set_volume(volMid, volWave - 1);
        }

        get_volume(&volMid, &volWave);
        draw_sprite(video_page[viraPagina], fundo,0,0);
        masked_blit( menuPause, video_page[viraPagina], 0 + (linha==0)*larg, 0*alt, 200, 150+ 0*alt, larg, alt);
        masked_blit( menuPause, video_page[viraPagina], 0 + (linha==1)*larg, 1*alt, 200, 150+ 1*alt, larg, alt);
        masked_blit( menuPause, video_page[viraPagina], 0 + (linha==2)*larg, 2*alt, 200, 150+ 2*alt, larg, alt);
        masked_blit( menuPause, video_page[viraPagina], 0 + (linha==3)*larg, 3*alt, 200, 150+ 3*alt, larg, alt);
        masked_blit( menuPause, video_page[viraPagina], 0 + (linha==4)*larg, 4*alt, 200, 150+ 4*alt, larg, alt);
        masked_blit( menuPause, video_page[viraPagina], 0 + (linha==5)*larg, 5*alt, 200, 150+ 5*alt, larg, alt);
        desenhaNumero(volMid, 3, 500 , 380, video_page[viraPagina]);
        desenhaNumero(volWave, 3, 500 , 380 + alt, video_page[viraPagina]);
        show_video_bitmap(video_page[viraPagina]);
        syncFPS();
    }
    destroy_bitmap(fundo);
    destroy_bitmap(pause);
    destroy_bitmap(menuPause);
    tecla.clear();
}
