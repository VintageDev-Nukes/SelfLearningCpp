#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <windows.h>

int random(int n = 0) {
    if(n!=0){
    return rand() % n;
    } else {
    return rand();
    }
}

const int worldWidth = 50, worldHeight = 30, windowWidth = 800, windowHeight = 600;
int topOfTheWorld = worldHeight/2, xPos, yPos, x, y, scene[worldWidth][worldHeight], timeUntilNextBiome = random(10)+30, size_of = 1, slope, fondoR, fondoG=223, fondoB=215, tick, splash, rate, font = 3, sec = 3, pre_x, pre_y;
//sizeof(scene)/sizeof(scene[0]);
std::string biomes[] = {"forest", "desert"}, biome = biomes[random(size_of)]; //versión inadaptada de los biomas
std::fstream fstr;
float offsetX=0, offsetY=0, nuevapos, nuevaposset=1.5;
char mapa[worldWidth][worldHeight];
std::ifstream ifile("mapa.txt");
bool game=false, day=true, night=false, volver=true, splash_active=true;
//bool readed;
//sf::RectangleShape rectCaja;

std::string NumberToString(int number) {

std::stringstream ss;
std::string s;

ss << number;
ss >> s;

return s;

}

/*std::string ruta(char id) {

if (id=='0') {return "air";}
else if (id=='1') {return "stone";}
else if (id=='2') {return "dirt";}
else if (id=='3') {return "grass_side";}
else if (id=='4') {return "coal_ore";}
else if (id=='5') {return "sand";}
else if (id=='6') {return "log_oak";}
else if (id=='7') {return "leaves_oak";}
else if (id=='8') {return "cactus_side";}
else {continue;}

}*/

void generar() {

    //std::ofstream output("mapa.txt");

	while (true) {
		if (yPos == topOfTheWorld) {
            /*timeUntilNextBiome--;
			if (timeUntilNextBiome<=0) {
				biome = biomes[random(size_of)];
				timeUntilNextBiome = random(10)+30;
			}
			if (biome == "forest") {
				scene[xPos][yPos] = 1;
				if (random(6) == 1) {
					scene[xPos][yPos+1] = 6;
					scene[xPos][yPos+2] = 6;
					scene[xPos][yPos+3] = 6;
					scene[xPos-1][yPos+3] = 7;
					//if (scene[xPos+1] == undefined) {
						//scene[xPos+1] = new Array();
					//}
					scene[xPos+1][yPos+3] = 7;
					scene[xPos][yPos+4] = 7;
				}
			} else if (biome == "desert") {
				scene[xPos][yPos] = 5;
				if (random(5) == 1) {
					scene[xPos][yPos+1] = 8;
					scene[xPos][yPos+2] = 8;
					scene[xPos][yPos+3] = 8;
				}
			}*/ //Bigged generation
            scene[xPos][yPos] = 2;
		} else if (yPos >= topOfTheWorld) {
		    scene[xPos][yPos] = 1;
		} else if(yPos < topOfTheWorld) {
		    //scene[xPos][yPos] = 0;
        } else if (yPos>=topOfTheWorld-3 && random(3) != 1) {
			if (biome == "forest") {
				scene[xPos][yPos] = 3;
			} else if (biome == "desert") {
				scene[xPos][yPos] = 5;
			}
		} else {
			if (random(4) == 1) {
				scene[xPos][yPos] = 4;
			} else {
				scene[xPos][yPos] = 1;
			}
		}/* else if(yPos < topOfTheWorld) {
		    scene[xPos][yPos] = 0;
        } else {
            scene[xPos][yPos] = 0;
        }*/

        yPos++;

        if(yPos>=worldHeight) {
            slope = random(5)-2;
            if(topOfTheWorld<(worldHeight/6)) {
                slope = 1;
            } else if(topOfTheWorld>(worldHeight-10)) {
                slope = -1;
            }
			topOfTheWorld += slope;
            yPos = 0;
		    xPos++;
		}

        /*output<<scene[x][y];

        if(x<(worldWidth-1)){output<<",";}

        x++;

        if(x>=worldWidth){
            if(y<(worldHeight-1)){output<<std::endl;}
            x = 0;
		    y++;
        }*/ //First BUG! Oh yes!

		if (xPos>=worldWidth) {
			break;
		}

	}

std::ofstream output("mapa.txt");
for(int y=0;y<worldHeight;y++) {
    for(int x=0;x<worldWidth;x++) {
        output<<scene[x][y];
        if(x<(worldWidth-1)){output<<",";}
    }
    //if(y<(worldHeight-1)){output<<std::endl;}
    output<<std::endl;
}

MessageBox(0, "World generation has finished!", "Finished!", MB_OK);

}

/*sf::RectangleShape dibujar(std::string ruta) {
                sf::Texture texture;
                texture.loadFromFile("images/blocks/" + ruta + ".png");

                sf::RectangleShape rectCaja(sf::Vector2f(16, 16));
                rectCaja.setPosition(sf::Vector2f(x*16, y*16));
                rectCaja.setTexture(&texture);

                return rectCaja;
}*/

void read_map() {

    if (ifile) {
        fstr.open("mapa.txt");

        int x = 0, y = 0;
        char c;

        while (fstr.get(c)) {
            if (c == '\n'){
                x = 0;
                y++;
            }else if (c != ','){
                mapa[x][y] = c;
                x++;
            }
        }

    }

}

class PLAYER {

public:

float dx,dy;
sf::FloatRect rect;
bool onGround;
sf::Sprite sprite;
float currentFrame;

    PLAYER(sf::Texture &image)
   {
	sprite.setTexture(image);
	rect = sf::FloatRect(100,180,16,16);

	dx=dy=0.1;
	currentFrame = 0;
   }


   void update(float time)
   {

	 rect.left += dx * time;
     Collision(0);


	 if (!onGround) dy=dy+0.0005*time;
	 rect.top += dy*time;
	 onGround=false;
     Collision(1);


     currentFrame += time * 0.005;
     if (currentFrame > 3) currentFrame -= 3;


    if (dx>0) sprite.setTextureRect(sf::IntRect(112+31*int(currentFrame),144,16,16));
	if (dx<0) sprite.setTextureRect(sf::IntRect(112+31*int(currentFrame)+16,144,-16,16));

	 sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	 dx=0;
   }


   void Collision(int num)
{

    //if(readed){read_map();readed=false;}
    //read_map();

	for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++) {
		for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++)
			 {

			     //std::cout << mapa[i][j] << std::endl;

				 if ((mapa[i][j]=='1') || (mapa[i][j]=='2') || (mapa[i][j]=='3') || (mapa[i][j]=='4') || (mapa[i][j]=='5'))
				                         {
												   if (dy>0 && num==1)
												   { rect.top =   i*16 -  rect.height;  dy=0;   onGround=true; }
											       if (dy<0 && num==1)
												   { rect.top = i*16 + 16;   dy=0;}
												   if (dx>0 && num==0)
												   { rect.left =  j*16 -  rect.width; }
											       if (dx<0 && num==0)
												   { rect.left =  j*16 +16;}
										 }

				 /*if (TileMap[i][j]=='c') {
												 // TileMap[i][j]=' ';
			                          	 }*/
			 }
	}

}

};

bool check_mouse(sf::RenderWindow& window, const sf::FloatRect& punto) {

    int mouse_x = sf::Mouse::getPosition(window).x, mouse_y = sf::Mouse::getPosition(window).y;

    if(mouse_x >= punto.left && mouse_x <= (punto.left + punto.width) && mouse_y >= punto.top && mouse_y <= (punto.height + punto.top) ) {return true;}else{return false;}

}

void render(sf::RenderWindow& window) {

    sf::Texture texture;

            for (int x = 0; x<worldWidth; x++) {
                for (int y = 0; y<worldHeight; y++) {

                    if(mapa[x][y]=='1') texture.loadFromFile("images/blocks/stone.png");
                    else if(mapa[x][y]=='2') texture.loadFromFile("images/blocks/dirt.png");
                    else if(mapa[x][y]=='3') texture.loadFromFile("images/blocks/grass_side.png");
                    else if(mapa[x][y]=='4') texture.loadFromFile("images/blocks/coal_ore.png");
                    else if(mapa[x][y]=='5') texture.loadFromFile("images/blocks/sand.png");
                    else if(mapa[x][y]=='6') texture.loadFromFile("images/blocks/log_oak.png");
                    else if(mapa[x][y]=='7') texture.loadFromFile("images/blocks/leaves_oak.png");
                    else if(mapa[x][y]=='8') texture.loadFromFile("images/blocks/cactus_side.png");
                    else continue;

                    sf::RectangleShape rectCaja(sf::Vector2f(16, 16));
                    rectCaja.setPosition(sf::Vector2f(x*16, y*16));
                    rectCaja.setTexture(&texture);
                    window.draw(rectCaja);

                }
            }

}

void escribir(sf::RenderWindow& window, sf::Text& text, std::string ruta, std::string texto, int tamano, int R=255, int G=255, int B=255, int alpha=255, int x=0, int y=0, UINT32 estilos=0) {

    sf::Font MyFont;
    MyFont.loadFromFile(ruta);

    text.setFont(MyFont);
    text.setString(texto);
    text.setCharacterSize(tamano);
    text.setColor(sf::Color(R, G, B, alpha));
    text.setPosition(sf::Vector2f(x, y));
    text.setStyle(estilos);

    window.draw(text);

}

void shadow_text(sf::RenderWindow& window, sf::Text& text, std::string ruta, std::string texto, int tamano, int R=255, int G=255, int B=255, int alpha=255, int x=0, int y=0, UINT32 estilos=0, int Rs=128, int Gs=128, int Bs=128, int alphas=255, int xs=2, int ys=2, std::string tipo="nada") {

    sf::Font MyFont;
    MyFont.loadFromFile(ruta);

    text.setFont(MyFont);
    text.setString(texto);
    text.setColor(sf::Color(R, G, B, alpha));
    text.setStyle(estilos);

    sf::Text shadow;

    shadow.setFont(MyFont);
    shadow.setString(texto);
    shadow.setColor(sf::Color(Rs, Gs, Bs, alphas));
    shadow.setStyle(estilos);

    if(tipo=="nada") {
        text.setCharacterSize(tamano);
        text.setPosition(sf::Vector2f(x, y));
        shadow.setCharacterSize(tamano);
        shadow.setPosition(sf::Vector2f(x+xs, y+ys));
    }

    if(tipo=="splash") {

        pre_x = text.getLocalBounds().width/2;
        pre_y = text.getLocalBounds().height/2;

        if(texto.size()==1){tamano=100;}else if(texto.size()==2){tamano=90;}else if(texto.size()==3){tamano=80;}else if(texto.size()==4){tamano=70;}else if(texto.size()==5){tamano=60;}else if(texto.size()==6){tamano=50;}else if(texto.size()==6){tamano=40;}else if(texto.size()==7){tamano=30;}else{tamano=20;}

        if(splash_active) {
            if(volver){
                rate++;
                if(rate>sec) {
                splash++;
                nuevapos += nuevaposset;
                rate=0;
                }
                if(splash>font){
                    volver=false;
                }
                //std::cout << "Hola" << std::endl;
            }else{
                rate++;
                if(rate>sec) {
                splash--;
                nuevapos -= nuevaposset;
                rate=0;
                }
                if(splash<=0){
                    volver=true;
                }
                //std::cout << "Adios" << std::endl;
            }
        }

        text.setCharacterSize(tamano+splash);
        shadow.setCharacterSize(tamano+splash);

        text.setPosition(sf::Vector2f(x-nuevapos-pre_x,y-nuevapos-pre_y));
        shadow.setPosition(sf::Vector2f(x+xs-nuevapos-pre_x, y+ys-nuevapos-pre_y));

        text.setRotation(-20);
        shadow.setRotation(-20);

    }

    window.draw(shadow);
    window.draw(text);

}

int main()
{

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Mini-proyecto: programación \"solidaria\" [Haciendo un juego]");
    sf::View view;

    /*view.reset(sf::FloatRect(0, 0, 1366, 768));
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));*/

    sf::Texture tileSet;
	tileSet.loadFromFile("Mario_Tileset.png");

    //sf::Sprite tile(tileSet);
    //sf::Texture texture;

	PLAYER Mario(tileSet);

	sf::Clock clock;

    sf::Text texto;
    sf::Text texto1;

    sf::RectangleShape fondo(sf::Vector2f(windowWidth, windowHeight));
    fondo.setFillColor(sf::Color(fondoR,fondoG,fondoB));

    sf::RectangleShape playButton(sf::Vector2f(500, 100));
    playButton.setPosition(windowWidth/2-500/2, windowHeight/2-100/2);
    playButton.setFillColor(sf::Color(255, 255, 255));

    sf::Texture logoTexture;
    logoTexture.loadFromFile("logo.png");
    sf::RectangleShape logo(sf::Vector2f(382, 68));
    logo.setTexture(&logoTexture);
    logo.setPosition(windowWidth/2-382/2, 20);

    sf::Texture texFondo;
    texFondo.loadFromFile("fondo.jpg");
    sf::RectangleShape noFondo(sf::Vector2f(windowWidth, windowHeight));
    noFondo.setTexture(&texFondo);


    //if(mapa[worldWidth][worldHeight]==NULL) {read_map();}
    //if(readed){read_map();readed=false;}
    read_map();

    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time/500;  // çäåñü ðåãóëèðóåì ñêîðîñòü èãðû

		if (time > 20) time = 20;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    if(!game){
                        if(check_mouse(window, playButton.getGlobalBounds())) {
                            game = true;
                        }
                    } else {
                        generar();
                    }
                    //std::cout << check_mouse(window, playButton.getGlobalBounds()) << std::endl;

                }
            }

            if(game) {

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))    Mario.dx=-0.1;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))    Mario.dx=0.1;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))	if (Mario.onGround) { Mario.dy=-0.27; Mario.onGround=false;}

            }

        }

        window.clear();

    if(!game) {
        window.draw(noFondo);
        window.draw(logo);
        shadow_text(window, texto1, "minecraft.ttf", "Splash Text!", 24, 255, 255, 0, 255, 560, 100, 1, 134, 134, 0, 255, 3, 3, "splash");
        window.draw(playButton);
        escribir(window, texto, "segoe-ui.ttf", "Jugar!", 24, 0, 0, 0, 255, windowWidth/2-texto.getLocalBounds().width/2, windowHeight/2-texto.getLocalBounds().height/2);
    } else {

            //Mario.update(time);
            if (Mario.rect.left>200) offsetX = Mario.rect.left-200;

            //Day & Night Cicle
            if(day){
                if(fondoG>0){fondoG--;}else{day=false;night=true;}
                if(fondoB>30){fondoB--;}else{fondoB=30;}
            } else if(night) {
                if(fondoG<223){fondoG++;}else{day=true;night=false;}
                if(fondoB<215){fondoB++;}else{fondoB=215;}
            } /*else if(!day) {
                tick++;
                if(tick=300){night=false;tick=0;}
            }*/
            //End Day & Night Cicle

            window.draw(fondo);
            render(window);
            tick++;

            /*sf::RectangleShape rectSuelo(sf::Vector2f(800, 100));
            rectSuelo.setPosition(sf::Vector2f(0, 500));
            rectSuelo.setFillColor(sf::Color::Red);
            window.draw(rectSuelo);*/

            //window.draw(Mario.sprite);

    }

    window.display();

 }

    return EXIT_SUCCESS;
}
