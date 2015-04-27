
#include <iostream>
#include <string>
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

    cout << "File has been updated with initial status of Graph" << endl;
    cout << "No Events yet added, will be added in later version" << endl;

}
