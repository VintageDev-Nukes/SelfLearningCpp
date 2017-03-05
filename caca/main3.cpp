#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

const int worldWidth = 30;
const int worldHeight = 10;
int topOfTheWorld = 5;
int xPos = 0;
int yPos = 0;
int scene[worldWidth][worldHeight];
int status;
std::fstream fstr;

std::string NumberToString(int number) {

std::stringstream ss;
std::string s;

ss << number;
ss >> s;

return s;

}

std::string ruta(int id) {

if (id=='0') return "air";
if (id=='1') return "stone";
if (id=='2') return "dirt";
if (id=='3') return "grass_side";
if (id=='4') return "coal_ore";

}

void generar() {

bool finished = false;
	while (!finished) {
		if (yPos >= topOfTheWorld) {
            scene[xPos][yPos] = 1;
		} else if(yPos < topOfTheWorld) {
		    scene[xPos][yPos] = 0;
        }

        yPos++;

        if(yPos == worldHeight) {
            yPos = 0;
		    xPos++;
		}

		if (xPos>worldWidth) {
			finished = true;
            goto Guardar;
		}
	}

Guardar:

std::ofstream output("mapa.txt");
    for(int y=0;y<worldHeight;y++) {
        for(int x=0;x<worldWidth;x++) {
            output<<scene[x][y];

            if(x<(worldWidth-1)){output<<",";}
        }
        if(y<(worldHeight-1)){output<<std::endl;}
    }

}

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Prueba de caca");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    generar();
                }
            }

        }

        window.clear(sf::Color(0,223,215));

fstr.open("mapa.txt");

char mapa[worldWidth-1][worldHeight-1];
int x = 0, y = 0;
char c;
while(fstr.good())
{
    c = fstr.get();
    if (int(c) != -1 && c!= ',' && c!= '\n') {
        mapa[x][y] = c;
        x++;
    }
    if (c=='\n')
    {
        x = 0;
        y++;
    }
}

        for (int x = 0; x<(worldWidth-1); x++) {
            for (int y = 0; y<(worldHeight-1); y++) {
                sf::Texture texture;
                if (!texture.loadFromFile("images/blocks/" + ruta(mapa[y][x]) + ".png"))
                return -1;

                sf::RectangleShape rectCaja(sf::Vector2f(16, 16));
                rectCaja.setPosition(sf::Vector2f(x*16, y*16));
                rectCaja.setTexture(&texture);
                window.draw(rectCaja);
            }
        }

        window.display();

    }

    return 0;
}