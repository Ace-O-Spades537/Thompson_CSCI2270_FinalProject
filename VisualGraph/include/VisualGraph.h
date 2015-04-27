#ifndef VISUALGRAPH_H
#define VISUALGRAPH_H

#include <string>

using namespace std;

struct Node
{
    //The visual height of the node
    int height;

    //Position of the node in the graph
    int xCord;
    int yCord;

    //Connectors to other nodes.
    // Make it easier to program events for graph
    Node* left;
    Node* right;
    Node* up;
    Node* down;



};


class VisualGraph
{
    public:
        Node* anchor; //This will create a easy starting point of the graph at position (0,0)
        Node* findNode(int x, int y);
        void sendNodeStatus(string fileName);

        //These next methods are to help with manipulation of the graph by easily shifting the pointerNode;
        // One to shift a specified value
        // Two to shift till graph ends in the specified direction
        Node* shiftPointerNode(Node* n,int value, string direction);
        Node* shiftPointerNode(Node* n, string direction);

        Node* createNode(int x,int y);

        VisualGraph(int width,int height);
        virtual ~VisualGraph();

    private:
        void outOfBound();
};

#endif // VISUALGRAPH_H
