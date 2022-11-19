#include <iostream>
#include "../include/Training.h"
//void printHello();

using std::cout;
using std::endl;

int main(int argc, char **argv) 
{
    printHello();
    int a = 2;
    int* pa = &a;
    cout << "a = " << a << " Location of a in RAM: " << pa << endl;
    return 0;
}

void printHello() {

    std::cout << "Hello" << std::endl;

}