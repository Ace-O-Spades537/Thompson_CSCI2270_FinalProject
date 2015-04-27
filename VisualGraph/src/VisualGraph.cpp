#include "VisualGraph.h"
#include <fstream>
#include <iostream>

using namespace std;

VisualGraph::VisualGraph(int width,int  height)
{
   //Using given width and height we will initialize a graph

   anchor = createNode(0 , 0);
   Node* pointerNode = anchor;



   for(int y = 0; y < height; y++)
   {
       if(y != height-1)
       {
           Node* temp1 = createNode(0, y+1);
           temp1->down = pointerNode;
           pointerNode->up = temp1;
       }

       for(int x = 1; x < width; x++)
       {

           Node* temp = createNode(x, y);
           pointerNode->right = temp;
           temp->left = pointerNode;

           if(y != 0)
           {
               //Setting the down connectors

               Node* tempDown = findNode(x, y-1);
               temp->down = tempDown;

           }
           else
           {
               temp->down = NULL;
           }
           pointerNode = temp;


       }

       if( y != height-1)
       {
            pointerNode = shiftPointerNode(pointerNode, "LEFT");
            pointerNode = pointerNode->up;
       }

   }


}

Node* VisualGraph::findNode(int x, int y)
{
    Node* PointerNode = anchor;
    for(int yVar = 0; yVar < y; yVar++)
    {
        PointerNode = PointerNode->up;
    }

    for( int xVar = 0; xVar < x; xVar++)
    {
        PointerNode = PointerNode->right;
    }

    return PointerNode;
}

void VisualGraph::sendNodeStatus(string fileName)
{
    ofstream outfile;
    outfile.open(fileName);

    //For printing to a file we want to start at the top of the graph not at the origin to make
    //interpreting the data easier when it is in the file;

    Node* PointerNode = anchor;
    PointerNode = shiftPointerNode(PointerNode, "UP");

    for(int y = PointerNode->yCord; y >= 0 ; y--)
   {
       outfile << to_string(PointerNode->height) << " ";
       cout << "Sending " << to_string(PointerNode->height) << endl;

       while(PointerNode->right != NULL)
       {
           PointerNode = PointerNode->right;
           outfile << to_string(PointerNode->height) << " ";
       }
       outfile << endl;
       PointerNode = shiftPointerNode(PointerNode, "LEFT"); // returning to y = 0 index
       PointerNode = PointerNode->down; //moving one line down
   }

    outfile.close();

}


Node* VisualGraph::createNode(int x,int y)
{
    Node* n = new Node;

    //Starting the height at a neutral position
    n->height = 0;

    n->xCord = x;
    n->yCord = y;

    //all connections are initialized to NULL
    //they will be set later in addNode()
    n->left = NULL;
    n->right = NULL;
    n->up = NULL;
    n->down = NULL;

    return n;

}

Node* VisualGraph::shiftPointerNode(Node* n,int value, string direction)
{
    Node* starting = n; //Used for later error checking

    if(direction == "RIGHT")
    {
        for(int i = 1; i <= value; i++)
        {
            if(n->right == NULL)
            {
                outOfBound();
                return starting;
            }
            n = n->right;
        }
    }
    else if(direction == "LEFT")
    {
        for(int i = 1; i <= value; i++)
        {
            if(n->left == NULL)
            {
                outOfBound();
                return starting;
            }
            n = n->left;
        }
    }
    else if(direction == "DOWN")
    {
        for(int i = 1; i <= value; i++)
        {
            if(n->down == NULL)
            {
                outOfBound();
                return starting;
            }
            n = n->down;
        }
    }
    else if(direction == "UP")
    {
        for(int i = 1; i <= value; i++)
        {
            if(n->up == NULL)
            {
                outOfBound();
                return starting;
            }
            n = n->up;
        }
    }

    //ERROR checking
    else
    {
        cout << "INVALID DIRECTION PLEASE ENTER ONE OF THE FOLLOWING (ALL CAPS):" << endl;
        cout << " \"RIGHT\" \"LEFT\" \"UP\" \"DOWN\"" << endl;
    }

    return n;
}

Node* VisualGraph::shiftPointerNode(Node* n, string direction)
{
    if(direction == "RIGHT")
    {
        while(n->right != NULL)
        {
            n = n->right;
        }

    }
    else if(direction == "LEFT")
    {
        while(n->left != NULL)
        {
            n = n->left;
        }
    }
    else if(direction == "DOWN")
    {
        while(n->down != NULL)
        {
            n = n->down;
        }
    }
    else if(direction == "UP")
    {
        while(n->up != NULL)
        {
            n = n->up;
        }
    }

    //ERROR checking
    else
    {
        cout << " ERROR: INVALID DIRECTION PLEASE ENTER ONE OF THE FOLLOWING (ALL CAPS):" << endl;
        cout << " \"RIGHT\" \"LEFT\" \"UP\" \"DOWN\"" << endl;
    }

    return n;
}

void VisualGraph::outOfBound()
{
    cout << "ERROR: YOU ARE OUT OF BOUNDS OF THE GRAPH" << endl;
}

VisualGraph::~VisualGraph()
{

}
