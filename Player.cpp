//Feito pelo Lopídio Guigui
//Espero q naum dê bug
//Se der, naum foi ele que fez
//Boa sorte a todos nós!
//Ave Lopídio!
#include "Player.h"

int random(int min, int max){
    return rand()%max + min;
}

//{ Construtor e Destrutor
Player::Player(){
}
Player::Player(Personagem* personagem_, char playerID_){
    srand(time(NULL)); //ativa a função random
    //personagem = new Personagem(personagem_);
    personagem = personagem_;
    personagem->carregaEspeciais();
    playerID = playerID_;
    KEY_ESPECIAL =  (playerID == 1)? KEY_T : KEY_UP;
    (playerID == 1)?especialProprio = 0:especialProprio = 0; //contador de especiais
    levandoEspecial = 0; //Não tá levando nenhum especial do inimigo!
    semTop = 50;
    durTop = 48;
    veloTop = 100; //Valor absurdamente maior do que qualquer um setado na classe Fase!
    contCria = 0; //contador que cria as toupeiras
    contBrinde = 0; //contador que diz se a toupeira é brinde ou não
    especialAtivo = false; //O especial começa sendo falso!
//{ inicializando toupeiras!!
    if (playerID == 2){
        toupeira.push_back(Toupeira(playerID, 1, KEY_1_PAD));
        toupeira.push_back(Toupeira(playerID, 2, KEY_2_PAD));
        toupeira.push_back(Toupeira(playerID, 3, KEY_3_PAD));
        toupeira.push_back(Toupeira(playerID, 4, KEY_4_PAD));
        toupeira.push_back(Toupeira(playerID, 5, KEY_5_PAD));
        toupeira.push_back(Toupeira(playerID, 6, KEY_6_PAD));
        toupeira.push_back(Toupeira(playerID, 7, KEY_7_PAD));
        toupeira.push_back(Toupeira(playerID, 8, KEY_8_PAD));
        toupeira.push_back(Toupeira(playerID, 9, KEY_9_PAD));
    }
    else if (playerID == 1){
        toupeira.push_back(Toupeira(playerID, 1, KEY_Z));
        toupeira.push_back(Toupeira(playerID, 2, KEY_X));
        toupeira.push_back(Toupeira(playerID, 3, KEY_C));
        toupeira.push_back(Toupeira(playerID, 4, KEY_A));
        toupeira.push_back(Toupeira(playerID, 5, KEY_S));
        toupeira.push_back(Toupeira(playerID, 6, KEY_D));
        toupeira.push_back(Toupeira(playerID, 7, KEY_Q));
        toupeira.push_back(Toupeira(playerID, 8, KEY_W));
        toupeira.push_back(Toupeira(playerID, 9, KEY_E));
    }
//}

}

Player::~Player()
{
    toupeira.clear();
}
//}


void Player::carregarObj(){
    tabuleiro =load_bitmap("FX/TabuleiroProfissional.pcx", NULL);
    if (!tabuleiro){
         allegro_message("Nao e possivel ler 'FX/TabuleiroProfissional.pcx'");
         exit(1);
    }
    mudaCor();
}
void Player::descarregarObj(){
    destroy_bitmap(tabuleiro);
}
BITMAP* Player::getTabuleiro(){
    return tabuleiro;
}
void Player::desativarEspecial(){
    especialAtivo = false;
    especialProprio = 0;
}

void Player::ativarEspecial(){
    especialAtivo = true;
}

bool Player::requisitarEspecial(){
    return key[KEY_ESPECIAL] && especialProprio > 0 && !especialAtivo;
}
void Player::mudaCor(){
    for (short linha = 310; linha <tabuleiro->h; linha++)
        for (short coluna = 0; coluna< tabuleiro->w; coluna++){
            int x = getpixel(tabuleiro, coluna, linha);
            if (x== makecol(0,255,0))
                playerID==1? putpixel(tabuleiro, coluna, linha, makecol(0,0,128)): putpixel(tabuleiro, coluna, linha, makecol(128,0,0));

        }
}

bool Player::is_especialAtivo(){
    return especialAtivo;
}
Especial* Player::getEspecial(){
    return personagem->getEspecial(especialProprio);
}
void Player::vitoria(BITMAP* buffer){
    personagem->vitoria(buffer, playerID);
}
void Player::derrota(BITMAP* buffer){
    personagem->derrota(buffer, playerID);
}
void Player::update(BITMAP* buffer){
    char esp = especialProprio; //Não aumentar de especial enquanto usa outro.
    for (char indice = 0; indice < 9 ; indice++){
        //textprintf_ex(buffer, font, 10, 10*indice, makecol(0, 100, 200), -1, "Ativa %d contCria %d  veloTop %d", toupeira[indice].getAtiva(), contCria, veloTop);
        toupeira[indice].update(buffer, semTop, especialProprio); //update de todas as toupeiras
        if ( especialAtivo && esp < especialProprio){ //Não pode aumentar o numero de especial enquanto tiver usando outro
            especialProprio = esp;
        }
    }
    if (contCria++ > veloTop){ //já tá na hora de criar uma toupeira!
        contCria = 0;
        char x= random(0,8), y = 7;//X é qual toupeira vai ser criada
        do{
            (++x )%=9; // não ser completamente aleatorio!
        }while(toupeira[x].getAtiva() || y-- <0); //até ser escolhida uma toupeira que não tiver sendo usada, ou passar de random tentativas
        char mal = random(1,20); //chance de ser do mal!
        float aux = ((float)mal)/5; //Estático só por boiolagem.. Aliviando 4 bytes de memória. =]
        toupeira[x].criar(levandoEspecial, durTop , contBrinde++>=29, !(contBrinde>=29)&&(mal >=19)); //atualiza o contador de brindes
        contBrinde%=30; //limita o valor de contBrine = 0-29;
        durTop = (char)((aux + 1 - (contBrinde==29) )*veloTop); //atualiza a duracao das toupeiras, e faz demorar menos, caso seja estrelinha
    }
}
Personagem* Player::getPersonagem(){
    return personagem;
}

char Player::getID(){
    return playerID;
}

void Player::reiniciarPlayer(){
    especialProprio = 0;
    especialAtivo = false;
    semTop = 50;
    contCria = 0; //contador que cria as toupeiras
    contBrinde = 0; //contador que diz se a toupeira é brinde ou não
    levandoEspecial = 0;
    for (char i = 0; i < 9; i++)
        toupeira[i].desativar();
}

void Player::matarToupeiras(){
    for (char i = 0; i < 9; i++)
        toupeira[i].matar();
}
