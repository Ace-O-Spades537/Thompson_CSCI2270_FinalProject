#include "GraphEvents.h"

#include <cstdlib>


/*
    Function prototype:
    void GraphEvents::update()

    Function description:
    This method is used to update the Events. Every time it is called a set of actions
    are called depending on the EventType: This allows for later modifications and to
    add more Events types.

    Example:
    After a GraphEvent is initialized a loop can be used like this to step through frames

    while(true)
    {
        GraphEvent.update();
    }

    This will step through the frames continuously
*/

void GraphEvents::update()
{
    switch(EventType)
    {
        case RAINDROP:
            if(counter == newAction)
            {
                addRainDrop();
                counter = 0;
            }
            ProcessWater(waterStruct.buffer1, waterStruct.buffer2);
            counter++;
            g->bufferToGraph(waterStruct.buffer1);
            break;

    }
}

/*
    Function prototype:
    void GraphEvents::ProcessWater(int** buffer1, int** buffer2)

    Function description:
    This is a method for a specific Event type. This one is for the Raindrop event type.
    This uses a typical raindrop ripple algorithm to model a ripple effect. The two buffers
    are used to keep track of current state of the frame and the previous one.

*/


void GraphEvents::ProcessWater(int** buffer1, int** buffer2)
{
    for(int y= 1; y < g->getHeight() -1; y++)
    {
            for(int x = 1; x < g->getWidth(); x ++)
            {
                waterStruct.buffer2[y][x] = ((waterStruct.buffer1[y-1][x] +
                                   waterStruct.buffer1[y+1][x] +
                                   waterStruct.buffer1[y][x+1] +
                                   waterStruct.buffer1[y][x-1]) / 2) - waterStruct.buffer2[y][x];
                waterStruct.buffer2[y][x] = waterStruct.buffer2[y][x] * (.5);
            }
    }

    g->bufferToGraph(waterStruct.buffer2);

    //swapping buffers for next Process
    int** temp = waterStruct.buffer1;
    waterStruct.buffer1 = waterStruct.buffer2;
    waterStruct.buffer2 = temp;
}

/*
    Function prototype:
    void GraphEvents::initializeBuffers()

    Function description:
    This method is used to initialize the buffers to all neutral heights and the same
    dementions of the graph. You would need to do this before trying to update() the
    RainDrop Event.

*/

void GraphEvents::initializeBuffers()
{
    for(int y = 0; y < g->getHeight(); y++)
    {
        for(int x = 0; x < g->getWidth(); x++)
        {
            waterStruct.buffer1[y][x] = 0;
        }
    }
}

/*
    Function prototype:
    void GraphEvents::addRainDrop()

    Function description:
    This method is used to set a random point in the buffer to its max height to act
    like a rain drop. So the ProccessWater() can dissipate it among the graph. This gives
    the illusion of a raindrop rippling effect.

*/

void GraphEvents::addRainDrop()
{
    //Find random point in graph

    int randX = rand() % g->getWidth();
    int randY = rand() % g->getHeight();

    waterStruct.buffer1[randY][randX] = 255;
}

/*
    Function prototype:
    GraphEvents::GraphEvents(VisualGraph* graph, int ET)

    Function description:
    This is the constructor for a Graph event. It requires a VisualGraph to manipulate
    and the type of event you want given by an int. This initializes all the variables
    for a Event to work;

    Example:
    VisualGraph g(10,10);
    int eventType = 1;
    GraphEvents GE(g,eventType);

*/


GraphEvents::GraphEvents(VisualGraph* graph, int ET)
{
    EventType = ET;
    g = graph;
    newAction = 10;
    counter = 0;
    int graphHeight = g->getHeight();
    int graphWidth = g->getWidth();


    switch (EventType)
    {
        case RAINDROP:
            waterStruct.iniWater(graphHeight, graphWidth);
            initializeBuffers();
            break;
    }

}

GraphEvents::~GraphEvents()
{

}

