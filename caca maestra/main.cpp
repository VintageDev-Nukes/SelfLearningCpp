/*#include <iostream>

const int worldWidth = 30;
const int worldHeight = 10;
int topOfTheWorld = 5;
int xPos = 0;
int yPos = 0;
int scene[worldWidth][worldHeight];

std::string ruta(int id) {

if (id==0) return "air";
if (id==1) return "stone";
if (id==2) return "dirt";
if (id==3) return "grass_side";
if (id==4) return "coal_ore";

}

using namespace std;

int main()
{

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
            goto Render;
		}
	}

	Render:
        /*for (int y = 0; y<=worldHeight; y++) {
            for (int x = 0; x<=worldWidth; x++) {
                string directorio = "images/blocks/" & ruta(scene[x][y]) & ".png";
                cout << directorio << ", ";
            }
            cout << endl;
        }

        cout << "hola" << scene[0][1] << "hola" << endl;

    cin.get();

    return 0;
}*/

/*#include <iostream.h>
#include <time.h>


class timer {
	private:
		unsigned long begTime;
	public:
		void start() {
			begTime = clock();
		}

		unsigned long elapsedTime() {
			return ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
		}

		bool isTimeout(unsigned long seconds) {
			return seconds >= elapsedTime();
		}
};


int main() {
    int sec;
	unsigned long seconds = 10;
	timer t;
	t.start();
	cout << "timer started . . ." << endl;
	while(true) {
		if(t.elapsedTime() >= seconds) {
			break;
		}
		else {
			cout << sec << endl;
			sec++;
		}
	}
	cout << seconds <<  " seconds elapsed" << endl;

	cin >> seconds;	// it's just to stop the execution and look at the output

	return 0;
}*/

#include <iostream>
#include <fstream>

using namespace std;

int main()
{

fstream fstr;
fstr.open("mapa.txt");

char mapa[30][16];
int x = 0, y = 0;
char c;
while(fstr.good())
{
    c = fstr.get();
    if (int(c) != -1  && c!= ',' && c!= '\n') {
        mapa[x][y] = c;
        x++;
    }
    if (c=='\n')
    {
        x = 0;
        y++;
    }
}
fstr.close();
cout << endl << endl << "El valor de 'X' es: " << x << ", y el de 'Y': " << y << endl << endl;

for (int y = 0; y<16; y++) { //Prueba a cambiar el 30 por 31 xD
    for (int x = 0; x<30; x++) {
        cout << mapa[x][y];
    }
    cout << endl;
}
cin.get();
}

/*#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>*/
/*#include <iostream>
#include <string>
#include <fstream>


using namespace std;

fstream myfile;
size_t row=0, column=0;
std::string s;
int myArray[30][10];

int main() {

myfile.open("mapa.txt");

while(getline(myfile, s))
{
    size_t i=0;
    while(s[i]!='\n')
    {
         myArray[column][row] = s[i];
         std::cout << myArray[column][row];
         column++;
    }
    row++;
    column = 0;
}

std::cout << myArray[3][1] << std::endl;
std::cin.get();

return 0;
}*/

/*	#include <iostream>
	#include <string>
	#include <fstream>

	using namespace std;
	int main()
	{
		ifstream archivo;
		archivo.open("mapa.txt");
		int tamano=0;
		while(archivo.get() != ' ')
		{
			tamano++;
		}
		archivo.close();
		archivo.open("mapa.txt");
		string b[tamano];
		//copiamos string en vector
		char c;
		for(int i=0;i<tamano;i++)
		{
			c = archivo.get();
			if (c != ',') {b[i]=c;}
		}
		//mostramos vector
		for (int i=0;i<tamano;i++)
		{
			cout << b[i];
		}
		archivo.close();
	}*/

/*struct int_reader : std::ctype<char>
{
    int_reader() : std::ctype<char>(get_table()) {}

    static std::ctype_base::mask const* get_table()
    {
        static std::vector<std::ctype_base::mask> rc(table_size, std::ctype_base::mask());
        rc[','] = std::ctype_base::space;
        rc['\n'] = std::ctype_base::space;
        return &rc[0];
    }
};

int main()
{
    std::vector<std::vector<int> > myFileData;
    std::ifstream fin("mapa.txt", std::ifstream::in);
    std::string buffer;
    while (std::getline(fin, buffer))
    {
        std::stringstream ss(buffer);
        std::vector<int> t;
            int_reader reader;
        ss.imbue(std::locale(std::locale(), &reader));
        std::copy(std::istream_iterator<int>(ss), std::istream_iterator<int>(), std::back_inserter(t));
        myFileData.push_back(t);
    }
    // do whatever you need to with the loaded arrays ...

    std::cout << myFileData[1][3] << std::endl;
    std::cin.get();

    return 0;
}*/
