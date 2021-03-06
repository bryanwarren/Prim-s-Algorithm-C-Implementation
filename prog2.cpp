#include <iostream>
#include <vector>
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//Used to store points
struct Point{
  double x;
  double y;
};

//Used to store vertexes connected by edges
struct VertexPair{
  int v1;
  int v2;
  VertexPair(int v11, int v22):v1(v11),v2(v22){}
};

//Used by the quicksort function to sort base on x values
int compareX(const void*a, const void*b){
  VertexPair *pair1=(VertexPair *)a;
  VertexPair *pair2=(VertexPair *)b;
  int compare=pair1->v1-pair2->v1;
  //If the x values are the same, sort by y
  if(compare==0){
    return pair1->v2-pair2->v2;
  }
  else{
    return compare;
  }
}

//Computes the distance(weight) of an edge
double distance(Point p1, Point p2){
  double y=(p1.y-p2.y)*(p1.y-p2.y);
  double x=(p1.x-p2.x)*(p1.x-p2.x);
  return sqrt(x+y);
}

//Produces the output
void print(int parent[], int n){
  vector<VertexPair>out;
  out.push_back(VertexPair(0,0));
  for(int i=1; i<n; i++){
    if(parent[i]<i){
      out.push_back(VertexPair(parent[i],i));
    }
    else{
      out.push_back(VertexPair(i, parent[i]));
    }
  }
  qsort(&out[0], out.size(), sizeof(VertexPair), compareX);
  for(int i=1; i<n; i++){
    cout<<out.at(i).v1<<" "<<out.at(i).v2<<"\n";
  }
}

//Function that finds the vertex with the smallest
//key value(weight)
int findMin(double key[], bool inSet[], int n){
  double min=DBL_MAX;
  int index=-1;
  for(int i=0; i<n; i++){
    if(inSet[i]==false && key[i]<=min){
      min=key[i];
      index=i;
    }
  }
  return index;
}

void prims(vector<vector<double>> edges, int n){
  //Stores the MST
  int parent[n];
  //Used to pick the minimum weight
  double key[n];
  //The set of vertices included/not included in MST
  bool inSet[n];

  //Initialize all keys to infinity
  //Initialize all vertices to not in MST
  for(int i=0; i<n; i++){
    key[i]=DBL_MAX;
    inSet[i]=false;
  }
  //Start with vertex 0
  key[0]=0;
  parent[0]=-1;

  //Loop through to get V vertices
  for(int i=0; i<n-1; i++){
    int minKey=findMin(key, inSet, n);
    //Add the vertex to the MST
    inSet[minKey]=true;
    for(int j=0; j<n; j++){
      //Edges only exist where edges[minKey][j] is nonzero
      //We can only look at vertices that have not been included yet
      //Find the smaller of edges[minKey][j] and key[j]
      if(edges[minKey][j]!=0 && inSet[j]==false && edges[minKey][j]<=key[j]){
	parent[j]=minKey;
	key[j]=edges[minKey][j];
      }
    }
  }
  print(parent, n);
}

int main(int argc, char** argv){
  int n;
  double x;
  double y;
  int npoints=0;
  //Get the number of vertices
  int temp=(scanf("%i", &n));

  //Error if number of vertices<=1
  if(n<=1){
    cerr<<"ERROR: Insufficient number of vertices. Number of vertices must be greater than 1"<<"\n";
    exit(1);
  }

  Point vertices[n];
  int nr=(scanf("%lf %lf", &x, &y));

  Point p;
  p.x=x;
  p.y=y;
  vertices[npoints]=p;
  npoints++;

  //Loop through to get all the vertices
  while(nr==2){
    if(npoints>=n){
      break;
    }
    nr=(scanf("%lf %lf", &x, &y));

    Point q;
    q.x=x;
    q.y=y;
    vertices[npoints]=q;
    npoints++;
  }
  
  int m;
  int v1;
  int v2;
  int mpoints=0;

  //Get the number of edges
  int temp1=(scanf("%i", &m));

  //Edges are stored in a multidimensional vector.
  //(row,column) represents an edge and the value
  //at that index is the weight of the edge. Edges
  //that don't exist are represented by a 0.
  vector<vector<double>>edges;
  edges.resize(n);
  for(int i=0; i<n; i++){
    edges[i].resize(n);
  }

  //If m=0, the graph is fully connected, so store
  //all possible edges into the array
  if(m==0){
    for(int i=0; i<n; i++){
      for(int j=i; j<n; j++){
	double dist=distance(vertices[i], vertices[j]);
	edges[i][j]=dist;
	edges[j][i]=dist;
      }
    }
    prims(edges, n);
    return 0;
  }
  //Error if an MST is not possible
  if(m!=0 && m<n-1){
    cerr<<"ERROR: MST is not possible. Number of edges must be at least n-1"<<"\n";
    exit(1);
  }
  //Initialize all weights to 
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      edges[i][j]=0;
    }
  }
  
  int nr2=(scanf("%i %i", &v1, &v2));
  double dist=distance(vertices[v1], vertices[v2]);
  edges[v1][v2]=dist;
  edges[v2][v1]=dist;
  mpoints++;

  //Loop through to get all the edges
  while(nr2==2){
    if(mpoints>=m){
      break;
    }
    nr2=(scanf("%i %i", &v1, &v2));
    double dist1=distance(vertices[v1], vertices[v2]);
    edges[v1][v2]=dist1;
    edges[v2][v1]=dist1;
    
    mpoints++;
  }
  
  prims(edges, n);
  return 0;
}
