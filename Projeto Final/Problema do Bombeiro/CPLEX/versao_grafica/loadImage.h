// Inclui o cabeçalho da bibilioteca Allegro 5
#include <allegro5/allegro.h>
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std; 
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
 
class loadImage{
	
public:
		ALLEGRO_DISPLAY *janela;
		ALLEGRO_BITMAP *imagem;


 loadImage(){
  // Variável representando a janela principal
  janela = NULL;
 
  // Variável representando a imagem
  imagem = NULL;
 
  // Inicializa a Allegro
  al_init();
 
  // Inicializa o add-on para utilização de imagens
  al_init_image_addon();
  // Carrega a imagem
  imagem = al_load_bitmap((char*)"hw.png");

  // Configura a janela
  janela = al_create_display(al_get_bitmap_width(imagem),al_get_bitmap_height(imagem));
 }
 void desenha(){
  
  // Carrega a imagem
  imagem = al_load_bitmap((char*)"hw.png");
  
  // Desenha a imagem na tela
  al_draw_bitmap(imagem, 0, 0, 0);
 
  // Atualiza a tela
  al_flip_display();
 
  // Segura a execução por 10 segundos
  al_rest(5.0);

 }
 
 void sair(){
  // Finaliza a janela
  al_destroy_display(janela);
 }
};
