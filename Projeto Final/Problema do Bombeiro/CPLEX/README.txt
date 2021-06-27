instalar o graphviz:
sudo apt-get update
sudo apt-get install graphviz
instalar o allegro 5:
sudo apt-get update
sudo apt-get install liballegro5.0

Compilar com makefile
executar ./FFP ./nome_da_instância

ou executar com o ecplise,porém deve incluir as tags para compilação
-lalleg  -I/home/monstruosoft/libs/usr/local/include/ -L/home/monstruosoft/libs/usr/local/lib/ -lallegro -lallegro_primitives -lallegro_image 
e também incluir os códigos cpp e h na pasta src
