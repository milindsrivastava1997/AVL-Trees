#include "avl.h"
#include <conio.h>
#include <iostream>
using namespace std;

int main()
{
    AVL obj;
    char c = 'n';
    do {
        cout << "Do you want to enter another landing time ? ";
        cin >> c;
        if (c == 'y' || c == 'Y')
        {
            obj.addNode();
        }
    } while (c == 'y' || c == 'Y');

    cout << "---Done Adding New Nodes---" << endl;
    cout << "Printing tree : " << endl << endl;

    int temp = obj.setHeight(obj.getRootNode());
    obj.setHeaviness(obj.getRootNode());
    obj.printAVL(obj.getRootNode());

    _getch();
    return 0;
}