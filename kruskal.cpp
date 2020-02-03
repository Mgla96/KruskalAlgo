#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <float.h>
#include <fstream>
#include "prog2.h"
using namespace std;
/*
Implementing - Kruskal's Algorithm a minimum cost spanning tree algorithm
*/

/*
Finds the weight based off the distance between 2 coordinate points using euclidian distance
*/
void Edge::setWeight(){
    weight = sqrt(pow(vertB->y-vertA->y,2)+pow(vertB->x-vertA->x,2));
}
/*
for qsort
cplusplus.com/reference/cstdlib/qsort
*/
int compEdges(const void* a, const void*b){ //sort by smallest weight
    Edge *a1= (Edge*)a, *b1=(Edge *)b;
    return (a1->weight > b1->weight) ? 1 : -1;
}
int compEdgeIndxs(const void* a, const void*b){ //sort by smallest indexes
    Edge *a1= (Edge*)a, *b1=(Edge *)b;
    if(a1->vertA->id > b1->vertA->id){
        return 1;
    }
    else if(a1->vertA->id < b1->vertA->id){
        return -1;
    }
    else{ //a1 and b1 vertA id are same so now check the vertB id
        if(a1->vertB->id >= b1->vertB->id){
            return 1;
        }
        else{
            return -1;
        }
    }
}

/*
Initializes Graph Class
edge stores initial array of all edges
result stores final group of edges in the mst
*/
Graph::Graph(int v, int e){
    this->numV=v;
    this->numE=e;
    this->edgeList = new Edge[e];
    this->result = new Edge[e];
}

int Find(int *subarr, int i){
    while(subarr[i]!=i){
        i=subarr[i];
    }
    return subarr[i];
}

void Union(int *subarr, int x, int y){
    int a=Find(subarr, x);
    int b=Find(subarr, y);
    subarr[b]=a;
}

int Kruskal(Graph *graph){
    int edgeI=0, j=0;
    qsort(graph->edgeList, graph->numE, sizeof(graph->edgeList[0]), compEdges);
    int vSize=graph->numV;
    int *subarr = new int [(vSize*sizeof(int))];
    for(int i=0; i<vSize; i++) //total vertices. Creating subset for each vertices
        subarr[i]=i;
    while (j<graph->numE && edgeI<vSize-1){ 
        Edge next=graph->edgeList[j];
        j++;
        int subArr1=Find(subarr, next.vertA->id);
        int subArr2=Find(subarr, next.vertB->id);
        if(subArr1!=subArr2){ //if they are equal this is a cycle
            graph->result[edgeI] = next;
            edgeI++;
            Union(subarr, subArr1, subArr2);
        }
    }
    return edgeI;
}

/*
Sorts the mst edges in order of indexes then prints them
*/
void printMST(Graph *graph, int E){
   //so now we have the result of edges in the MST 
   //but they are sorted in order of their weight
   //we must sort them in order of their indexes (I created function compEdgeIndxs to do just that with qsort)
   qsort(graph->result, E, sizeof(graph->result[0]), compEdgeIndxs);
   int i=0;
   cout << setprecision(4) << fixed; //set precision of cout to 4 decimal places
   for (i = 0; i < E; ++i)
       cout<<graph->result[i].vertA->id<<" "<<graph->result[i].vertB->id<<endl;       
}

int main()
{
    int v; //number of vertices
    cin >> v;
    struct coord cordArr[v];
    for (int i = 0; i < v; i++)
    {
        float one, two;
        cin >> one >> two;
        cordArr[i].x = one;
        cordArr[i].y = two;
        cordArr[i].id = i;
    }
    int e;
    cin>>e; //num edges
    /*
    e==0 is special case where there is complete graph and there exists an edge inbetween every pair of vertices
    */
    if(e==0){ 
        int numEdges=(v*(v-1))/2;
        Graph *graph=new Graph(v, numEdges);
        int index=0;
        for(int j=0; j<v-1; j++){ //one less edge than total vertices
            for(int k=j+1; k<v; k++){
                graph->edgeList[index].vertA=&cordArr[j];
                graph->edgeList[index].vertB=&cordArr[k];
                graph->edgeList[index].setWeight();
                index++; 
            }
        }
        int resultSize = Kruskal(graph);
        printMST(graph, resultSize);
    }
    else{
       Graph *graph=new Graph(v, e);
        for(int j=0; j<e; j++){
            int a, b;
            cin >>a>>b;
            graph->edgeList[j].vertA= &cordArr[a];
            graph->edgeList[j].vertB=&cordArr[b];
            graph->edgeList[j].setWeight();    
        }
        int resultSize = Kruskal(graph);
        printMST(graph, resultSize);
    }
    return 0;
}