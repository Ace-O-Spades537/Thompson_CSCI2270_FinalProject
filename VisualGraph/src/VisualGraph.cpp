#include "VisualGraph.h"
#include <fstream>
#include <iostream>

using namespace std;

/*
    Function prototype:
    VisualGraph::VisualGraph(int width,int  height)

    Function description:
    This is the constructor for a VisualGraph. It takes a desired height and width.
    It will go along and create the required nodes to make a graph the size you want.
    It will also create all the unweighted edges between the nodes. The include up,
    down, right and left. It will also initialize all the heights to zero.

    Example:
    VisualGraph g(10,10)

    This would give you a graph that looked like this
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0

    Example 2:
    VisualGraph g(5,2);

    This would give you a graph that looked like this
    0 0 0 0 0
    0 0 0 0 0
*/

VisualGraph::VisualGraph(int width,int  height)
{
   //Using given width and height we will initialize a graph
   GraphHeight = height;
   GraphWidth = width;

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
               tempDown->up = temp;



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

/*
    Function prototype:
    Node* VisualGraph::findNode(int x, int y)

    Function description:
    This method will allow you to find a specific Node at a given (x,y) cord.
    Note that the (0,0) Node is the anchor node and is located at the most bottom left
    corner of the graph.

    Example:
    g.findNode(2,4);
*/

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

/*
    Function prototype:
    void VisualGraph::sendNodeStatus(string fileName)

    Function description:
    This method lets you send the Node statuses to a file. This would allow you to
    communicate will 3rd party programs.

    Example:
    VisualGraph g(10,10)
    g.sendNodeStatus(test.txt);

    <IN TEST.TXT>
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0

*/

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

/*
    Function prototype:
    void VisualGraph::printNodeStatus()

    Function description:
    This will print the status of the nodes to the command prompt.

    Example:
    VisualGraph g(10,10)
    g.printNodeStatus();

    <IN COMMAND PROMPT>
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0 0 0

*/

void VisualGraph::printNodeStatus()
{

    Node* PointerNode = anchor;
    PointerNode = shiftPointerNode(PointerNode, "UP");

    for(int y = PointerNode->yCord; y >= 0 ; y--)
   {
       cout << to_string(PointerNode->height) << " ";

       while(PointerNode->right != NULL)
       {
           PointerNode = PointerNode->right;
           cout << to_string(PointerNode->height) << " ";
       }
       cout << endl;
       PointerNode = shiftPointerNode(PointerNode, "LEFT"); // returning to y = 0 index
       PointerNode = PointerNode->down; //moving one line down
   }

}

/*
    Function prototype:
    Node* VisualGraph::createNode(int x,int y)

    Function description:
    This Method is used to create a new Node to be later be added to the Graph.
    It takes a x and y value to assign its cordinates on the graph. It does not create
    the edges though.

    Example:
    <IN CONSTRUCTOR>
    Node *n = createNode(0,0)

*/

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

/*
    Function prototype:
    Node* VisualGraph::shiftPointerNode(Node* n,int value, string direction)

    Function description:
    This Method is Used to make it easier to manipulate the graph. What it does
    is takes a pointer to a node and will go along the edges connecting the nodes
    across a desired amount of nodes(given by int value) and in a certain direction.

    Example:
    Node* pointerNode = g.anchor //pointerNode->xCord,pointerNode->yCord = 0,0
    pointerNode = shiftPointerNode(pointerNode, 2, "UP)
    //pointerNode->xCord,pointerNode->yCord = 0,2
*/

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

/*
    Function prototype:
    Node* VisualGraph::shiftPointerNode(Node* n, string direction)

    Function description:
    This Method is Used to make it easier to manipulate the graph. What it does
    is takes a pointer to a node and will go along the edges connecting the nodes
    till it hits the bound of the graph and in a certain direction.

    Example:
    VisualGraph g(10,10)
    Node* pointerNode = g.anchor //pointerNode->xCord,pointerNode->yCord = 0,0
    pointerNode = shiftPointerNode(pointerNode, "UP)
    //pointerNode->xCord,pointerNode->yCord = 0,9
*/

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

/*
    Function prototype:
    void VisualGraph::bufferToGraph(int** buffer)

    Function description:
    This method is used by the Event class to allow for buffer to graph conversion.
    The GraphEvents class works in terms of int[][] and VisualGraphs works in terms of
    graphs.

*/

void VisualGraph::bufferToGraph(int** buffer)
{
    Node* pointerNode = anchor;

    for(int y = 0; y < GraphHeight; y++)
    {
        for(int x = 0; pointerNode->right != NULL; x++)
        {
            pointerNode->height = buffer[y][x];
            pointerNode = pointerNode->right;
        }
        pointerNode = shiftPointerNode(pointerNode, "LEFT");
        if( y != GraphHeight - 1)
        {

            pointerNode = pointerNode->up;
        }
    }
}

/*
    Function prototype:
    void VisualGraph::ChangeAllTo(int val)

    Function description:
    This Method allows you to change all the heights in the graph. This can be used
    to recalibrate the graph after an event is quit.

    Example:
    VisualGraph g(10,10)
        <STATE OF GRAPH>
        0 0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0 0
        0 0 0 0 0 0 0 0 0 0
    g.ChangeAllTo(10);
        <NEW STATE OF GRAPH>
        10 10 10 10 10 10 10 10 10 10
        10 10 10 10 10 10 10 10 10 10
        10 10 10 10 10 10 10 10 10 10
        10 10 10 10 10 10 10 10 10 10
        10 10 10 10 10 10 10 10 10 10
        10 10 10 10 10 10 10 10 10 10
        10 10 10 10 10 10 10 10 10 10
        10 10 10 10 10 10 10 10 10 10
        10 10 10 10 10 10 10 10 10 10
        10 10 10 10 10 10 10 10 10 10
*/

void VisualGraph::ChangeAllTo(int val)
{
    Node* pointerNode = anchor;

    for(int y = 0; y < GraphHeight; y++)
    {
        pointerNode->height = val;
        for(int x =0; pointerNode->right != NULL; x++)
        {
            pointerNode = pointerNode->right;
            pointerNode->height = val;

        }
        pointerNode = shiftPointerNode(pointerNode, "LEFT");

        if(y != GraphHeight-1)
        {
            pointerNode = pointerNode->up;

        }
    }
}

/*
    Function prototype:
    void VisualGraph::outOfBound()

    Function description:
    This is used for when you try to go out of the bounds of the Graph. It will
    display this error.

*/

void VisualGraph::outOfBound()
{
    cout << "ERROR: YOU ARE OUT OF BOUNDS OF THE GRAPH" << endl;
}

/*
    Function prototype:
    int VisualGraph::getHeight()
    int VisualGraph::getWidth()

    Function description:
    These two methods allow you to retrieval the private data of height and width

    Example:
    VisualGraph g(10,10);
    int checkHeight = g.getHeight(); // checkHeight is now 10
*/

int VisualGraph::getHeight()
{
    return GraphHeight;
}

int VisualGraph::getWidth()
{
    return GraphWidth;
}

VisualGraph::~VisualGraph()
{

}
