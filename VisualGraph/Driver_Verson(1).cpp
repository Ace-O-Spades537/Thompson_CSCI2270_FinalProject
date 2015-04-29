
#include <iostream>
#include <string>
#include <unistd.h>
#include "GraphEvents.h"
#include "VisualGraph.h"

using namespace std;

int main()
{
    int x;
    int y;

    cout << string(50, '\n');

    cout << "Please enter a width of the Graph:";
    cin >> x;

    cout << string(50, '\n');

    cout << "Please enter a height of the Graph:";
    cin >> y;

    cout << string(50, '\n');

    cout << "Thank you initializing Graph";

    VisualGraph g(x, y);

    cout << string(50, '\n');

    string fileName;
    cout << "Please enter the name that you want the Graph data to be sent:";
    cin >> fileName;

    g.sendNodeStatus(fileName);

    cout << string(50, '\n');

    int command= 0;

    while(command != 6)
    {
        cout << "OPTIONS:" << endl;
        cout << "1. Change value at (x,y)" << endl;
        cout << "2. Change all values to neutral" << endl;
        cout << "3. Change all values to max" << endl;
        cout << "4. Create Raindrop Event and loop(Event algorithm not finished)" << endl;

        g.printNodeStatus();

        cout << endl;
        cin >> command;

        int x;
        int y;
        int newVal;
        Node* pointerNode = g.anchor;

        GraphEvents GE(&g, 1);
        GE.initializeBuffers();

        switch(command)
        {
            case 1:
                cout << "Enter X value:";
                cin >> x;
                cout << "Enter Y value;";
                cin >> y;
                cout << "What would you like to change it to? (0-255):";
                cin >> newVal;
                pointerNode = g.findNode(x,y);
                pointerNode->height = newVal;
                break;
            case 2:
                g.ChangeAllTo(0);
                break;
            case 3:
                g.ChangeAllTo(255);
                break;
            case 4:
                while(true)
                {
                    GE.update();
                    g.printNodeStatus();
                    sleep(1);
                    cout << string(50, '\n');

                }
        }

        cout << string(50, '\n');


    }


}
