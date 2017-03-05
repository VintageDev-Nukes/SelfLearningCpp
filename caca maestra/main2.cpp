#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{

fstream fstr;
fstr.open("mapa.txt");

char mapa[31][9];
int x = 0, y = 0;
char c;
while(fstr.good())
{
    c = fstr.get();
    if (c!= ',') {
        cout << c;
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

for (int y = 0; y<=9; y++) {
    for (int x = 0; x<=30; x++) { //Prueba a cambiar el 30 por 31 xD
        cout << mapa[x][y];
    }
}

cin.get();

}