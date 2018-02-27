#include <allegro.h>
#include "Fase.h"

int main()
{
    if (allegro_init() != 0) exit(1);
    set_color_depth(32);
    if (set_gfx_mode(GFX_AUTODETECT, 800, 600, 00, 00) != 0) { //Tava 800, 600 o virtual
        if (set_gfx_mode(GFX_SAFE, 800, 600, 00, 00) != 0) { //Aqui também!
            set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
            allegro_message("Impossivel setar modo grafico\n%s\n", allegro_error);
            return 1;
        }
   }
    install_keyboard();
    set_window_title("Dig Hole Battle Garden");
    install_timer();
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0) != 0) {
        allegro_message("Impossivel setar dispositivo de som");
        exit(1);
    }
    char a;
    set_volume(220, 100); //WAV, MIDI    ----> 220, 100  <-- Melhor que tem!
    do{
        clear_bitmap(screen);
        Personagem* pe1 = new Personagem(1);
        Personagem* pe2 = new Personagem(2);
        Fase *x = new Fase(pe1,pe2,12); //-> já faz a abertura completa!
        a = x->principal();// Reiniciar = 3;
        delete x;
        delete pe1;
        delete pe2;
    } while (a==3);

    //textprintf_ex(screen, font,0,40,makecol(255,128,0),-1, "resultado %d", a);
    clear_keybuf();
    readkey();
    allegro_exit();
    return 0;
}
END_OF_MAIN()
