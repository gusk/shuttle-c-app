//File:ortho.cxx
//Written by: August King (august.king@colorado.edu) on December 3, 2010.
//The purpose of this program is to project a wire-model of a space shuttle.
//This program will use a file on the local directory that will contain the
//needed x,y points to make the vertex. Also, when the user presses a key the
//program will exit. 

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//Directives
#include <cstdlib>
#include <cmath>
#include <graphics.h>
#include <iomanip>   
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// Global Named Constants:
const int S = 500; //A global constant for height and the width of the window

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//Structs
struct point
{
    double x,y,z;
};

struct edge
{
    unsigned int num;
    int color;
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//Function Prototypes:
//The read_point funtion will stream the x, y, and z coordinates from the
//shuttle.dat file.
void read_points(istream &ins, vector<point>& points);
//The read edges funtion will stream the movement and the color from the
//shuttle.dat file.
void read_edges(istream &ins, vector<edge>& edges);
//The draw function will draw the lines for the wire-frame shuttle.
void draw(vector<point>points, vector<edge>edges);
//The pixel function will convert the world coordinates into pixel coordinates
int pixel(double v, double v0, double v1, int pmax);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

int main()
{
    // Creates the vectors
    vector<point>points;
    vector<edge>edges;

    //Streams the shuttle x,y,z data
    ifstream ins;
    ins.open("shuttle.dat");

    //Calls the points and edges functions, then opens a graphics window
    read_points(ins, points);
    read_edges(ins, edges);
  
    initwindow(S, S, "Wire");

    //Uses the draw function to draw the lines
    draw (points, edges);

    getch();
}
 

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//The read_point funtion will stream the x, y, and z coordinates from the
//shuttle.dat file.
void read_points(istream& ins, vector<point>& points)
{
    unsigned int many_p;
    unsigned int i;
    point v;
    
    ins>>many_p;

    //This loop take the points fromm the shuttle data and transfer to points
    for(i=0; i < many_p; ++i)
    {
	ins>>v.x>>v.y>>v.z;
	points.push_back(v);
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//The read edges funtion will stream the movement and the color from the
//shuttle.dat file.
void read_edges(istream& ins, vector<edge>& edges)
{
    unsigned int many_p;
    unsigned int i;
    edge e;
    
    ins>>many_p;

    //This loop takes the points from the shuttle data and transfers to the edges
    for(i=0; i < many_p; ++i)
    {
	ins>>e.num>>e.color;
	edges.push_back(e);
    }
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//The draw function will draw the lines for the wire-frame shuttle.
void draw(vector<point> points, vector<edge> edges)
{
    unsigned int i;
    unsigned int vertex_index;
    int color;

    unsigned int size = edges.size();
    double wx, wy;
    int px, py;
    double wmin, wmax;

    wmin = -10900 * 1.2;
    wmax = 10900 * 1.2;

    //This loop will use the pixel funtion to change the x,y to pixels on the screen
    for(i = 0; i < size; ++i)
    {
	color = edges[i].color;
	vertex_index = (edges[i].num) - 1;
	wx = points[vertex_index].x;
	wy = points[vertex_index].y;
	px = pixel(wx, wmin, wmax, S);
	py = pixel(wy, wmax, wmin, S);
	
	//This if statement will determine if the color on the screen is 0, then it
	// will move to the next point on the screen. 
	if(color == 0)
	{
	    moveto(px,py);
	   
	}
	//This will take the current position and draw the line to the next point,
	// then change the current position each time through
	else
	{
	    setcolor(color);
	    lineto(px,py);
	
	}
    }
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//The pixel function will convert the world coordinates into pixel coordinates
int pixel(double v, double v0, double v1, int pmax)
{
    double ratio = (v - v0)/(v1 - v0);
    return int(ratio*pmax);
}
