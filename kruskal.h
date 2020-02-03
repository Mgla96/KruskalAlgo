#ifndef PROG2_H
#define PROG2_H


struct coord{
 int id;
 float x, y;
};


struct subArr{
    int parent, rank;
};

class Edge{
    public:
    struct coord *vertA, *vertB;
    float weight;
    void setWeight();
};

class Graph{
    public:
    Edge* edgeList, *result; //edge from vertA to vertB also edge from vertB to vertA both counted as 1 edge here
    int numV, numE; //V is num vertices E is num edges
    Graph(int v, int e);
};


#endif