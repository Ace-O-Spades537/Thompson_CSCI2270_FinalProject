
#ifndef GRAPHEVENTS_H
#define GRAPHEVENTS_H

#include "VisualGraph.h"

#define RAINDROP 1



struct Water
{
    int** buffer1;
    int** buffer2;

    Water()
    {

    }

    void iniWater(int width,int height)
    {
        buffer1 = new int*[height];
        for(int i = 0; i < width; i++)
        {
            buffer1[i] = new int[width];
        }

        buffer2 = new int*[height];
        for(int i = 0; i < width; i++)
        {
            buffer2[i] = new int[width];
        }
    }
};

class GraphEvents
{
    public:
        void update();
        GraphEvents(VisualGraph* graph, int ET);
        void initializeBuffers();
        virtual ~GraphEvents();

    protected:
    private:
        void addRainDrop();
        void ProcessWater(int** buffer1, int** buffer2);
        Water waterStruct;
        VisualGraph* g;
        int EventType;
        int counter;
        int newAction;
};

#endif // GRAPHEVENTS_H
