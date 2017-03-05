#include <iostream>
#include <time.h>

int random(int n = 0) {

srand(time(NULL));

if(n!=0){
return rand() % n;
} else {
return rand();
}

}

using namespace std;

int main()
{
    cout << random() << endl;
    return 0;
}
