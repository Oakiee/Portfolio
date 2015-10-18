//*******************************************************************
//
//  Program:     Homework 4 - Project 4
//
//  Author:      Amanda Oyakawa
//  Email:       ao441309@ohio.edu
//
//  Lab Section: 101 Bibo Shi
//
//  Description: This program reads in a graph and then calculates
//		 and outputs the breadth first spanning tree
//
//  Date:        March 26th, 2014
//
//*******************************************************************

//******************************************************************
//
//  Function:   generate_graph
//
//  Purpose:    generates a graph from an input file
//
//  Parameters:  istream& input
//
// Member/Global Variables:        string graph_type: is it directed or undirected?
//                                 string temp_vertex: temporary holder for vertex names
//                                 string temp_vertex2: temporary holder for 2nd vertex (edge)
//                                 string *temp_name: array holding all vertex names
//                                                     to check there's no repeats
//                                 double temp_edge; temp edge weight
//                                 bool exists; does the vertex described already exist?
//                                 bool exists2; does the 2nd vertex described already exist?
//                                 int first; where the first vertex is in the array, a placeholder
//                                 int second; where the second vertex is in the array, a placeholder
//				 bool same_edge; is there already an edge between these vertices?
//			         bool check; check to see that the starting node is in the graph
//
// Pre Conditions: there is input
//
// Post Conditions: creates a graph if valid, tells user it's
//                  invalid if invalid
//
// Calls:       cstdlib, iostream, string
//                    (n = number of items in graph)
//
// Space Complexity: N
//
// Time Complexity: Big O(n^2)
//
//******************************************************************

//******************************************************************
//
//  Function:   bfs
//
//  Purpose:    does a breadth first search of a graph and yields a spanning tree
//		our outputs that there is no spanning tree
//
//  Parameters:  none
//
// Member/Global Variables:           int startIndex = 0;
//                                    queue<Vertex> tempq; //queue for bfs
//                                    Vertex tempVertex; //for cout purposes
//                                   string tempName; //temp string for vertex names for searching purposes
//                                   int tempEdge; //temp edge
//
// Pre Conditions: there is a valid graph
//
// Post Conditions: outputs a spanning tree if there is one
//		  outputs an error if not
//
// Calls:       cstdlib, iostream, string, queue
//                    (n = number of items in graph)
//
// Space Complexity: N
//
// Time Complexity: Big O(n^2)
//
//******************************************************************

#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>
#include "graph.h"
using namespace std;


void Graph::generate_graph(istream& input)
{
    
    string graph_type; //is it directed or undirected?
    string temp_vertex; //temporary holder for vertex names
    string temp_vertex2; //temporary holder for vertex names, (for 2nd edge connection)
    string *temp_name; //array holding all vertex names to check there's no repeats
    double temp_edge; //temp edge weight
    
    
    //initial check - if the first line is blank it is invalid
    if (!input.eof() && input.peek()=='\n')
    {
        cout <<  "Error in graph file!" << endl;
        exit(0);
    }
    
    //skip any comments and new lines at beginning and then get # of nodes
    while (!input.eof() && (input.peek() =='#'))
    {
        input.ignore(256, '\n');
        
    }
    //read in the type of the graph "undirected" or "directed"
    input >> graph_type;
    
    //if the first non-comment line doesn't specify the type of graph, error
    if (input.fail() || (graph_type != "undirected" && graph_type != "directed"))
    {
        cout << "Error in graph file!" << endl;
        exit(0);
    }
    
    //idk something weird about getting past the \n
    if (!input.eof() && (input.peek() == '\n'))
    {
        input.ignore(2, '\n');
    }
    
    //ignore any comments b/t the graph type and the vertex count
    while (!input.eof() && (input.peek() =='#'))
    {
        input.ignore(256, '\n');
        
    }
    
    //if there is a blank line in the file here it is invalid
    if (!input.eof() && input.peek() == '\n')
    {
        cout << "Error in graph file!" << endl;
        exit(0);
    }
    
    //read in the vertex count
    input >> vertex_count;
    
    //if the first non-comment line after graph type is not a positive integer, error
    if (input.fail() || vertex_count < 0)
    {
        cout << "Error in graph file" << endl;
        exit(0);
    }
    
    //if the vertex count is 0 then you're done reading the file
    if (vertex_count == 0)
    {
        cout << "Error in graph file" << endl;
        exit(0);
    }
    
    //if the vertex count is 1 then there is no spanning tree so stop
    if (vertex_count == 1)
    {
        cout << " " << endl;
        exit(0);
    }
    
    //idk something weird about getting past the \n
    if (!input.eof() && (input.peek() == '\n'))
    {
        input.ignore(2, '\n');
    }
    
    graphList = new Vertex[vertex_count];  //array to store vertices in
    temp_name = new string[vertex_count];
    
    for (int i = 0; i < vertex_count; ++i)
    {
        //skip comments
        while (!input.eof() && (input.peek() =='#'))
        {
            input.ignore(256, '\n');
        }
        
        getline(input, temp_vertex, '\n');
        
        temp_name[i] = temp_vertex;
        
        //check to make sure that this vertex doesn't share a name with any other
        for (int j = 0; j < i; ++j)
        {
            
            if (temp_name[j] == temp_vertex)
            {
                cout << "Error in graph file" << endl;
            }
        }
        
        graphList[i].identifier = temp_vertex; //set vertex name
        graphList[i].visited = false; //presets the vertex to not being visited for bfs
        graphList[i].used_connected = 0;
        graphList[i].used_length = 0;
        
    }
    
    //ignore any comments b/t the vertex list and the edge count
    while (!input.eof() && (input.peek() =='#'))
    {
        input.ignore(256, '\n');
        
    }
    
    //if there is a blank line in the file here it is invalid
    if (!input.eof() && input.peek() == '\n')
    {
        cout << "Error in graph file!" << endl;
        exit(0);
    }
    
    //read in the edge count
    input >> edge_count;
    
    //if the first non-comment line after graph type is not a positive integer, error
    if (input.fail() || edge_count < 0)
    {
        cout << "Error in graph file" << endl;
        exit(0);
    }
    
    //if the vertex count is 0 then you're done reading the file
    if (edge_count == 0)
    {
        cout << "No spanning tree." << endl;
        exit(0);
    }
    
    //idk something weird about getting past the \n
    if (!input.eof() && (input.peek() == '\n'))
    {
        input.ignore(2, '\n');
    }
    
    
    //initialize all the the vertices two sub-arrays to edge count, because it can't be more
    if (graph_type == "directed")
    {
        for (int e = 0; e < vertex_count; e++)
        {
            graphList[e].connected = new string[edge_count];
            graphList[e].length = new double[edge_count];
        }
    }
    
    if (graph_type == "undirected")
    {
        for (int e = 0; e < vertex_count; e++)
        {
            graphList[e].connected = new string[edge_count * edge_count];
            graphList[e].length = new double[edge_count * edge_count];
        }
    }
    
    
    for (int m = 0; m < edge_count; m++)
    {
        
        //skip comments
        while (!input.eof() && (input.peek() =='#'))
        {
            input.ignore(256, '\n');
        }
        
        //read in the first vertex
        getline(input, temp_vertex, '\n');
        
        //skip comments
        while (!input.eof() && (input.peek() =='#'))
        {
            input.ignore(256, '\n');
        }
        
        //read in the second vertex
        getline(input, temp_vertex2, '\n');
        
        //skip comments
        while (!input.eof() && (input.peek() =='#'))
        {
            input.ignore(256, '\n');
        }
        
        //read in the edge weight
        while (input.peek() == ' ')
        {
            input.ignore();
        }
        
        //if the edge weight is a blank line, default to 1
        if (input.peek() == '\n')
        {
            temp_edge = 1;
            input.ignore(); // go to the next line
        }
        else
        {
            input >> temp_edge;
            
            //if it's not a number
            if (input.fail())
            {
                cout << "Error in graph file" << endl;
                exit(0);
            }
            
            //idk something weird about getting past the \n
            if (!input.eof() && (input.peek() == '\n'))
            {
                input.ignore(2, '\n');
            }
            
        }
        
        bool exists = false; //does the vertex described already exist?
        bool exists2 = false; //does the 2nd vertex described already exist?
        int first = 0; //where the first vertex is in the array, a placeholder
        int second = 0; //where the second vertex is in the array, a placeholder
        
        //check to make sure that these vertices are one of the vertices
        for (int t = 0; t < vertex_count; ++t)
        {
            if (graphList[t].identifier == temp_vertex)
            {
                exists = true;
                first = t;
                break;
            }
        }
        
        for (int h = 0; h < vertex_count; ++h)
        {
            if (graphList[h].identifier == temp_vertex2)
            {
                exists2 = true;
                second = h;
                break;
            }
        }
        
        //if either edge wasn't already specified, return an error
        if (exists == false || exists2 == false)
        {
            cout << "Error in graph file!" << endl;
        }
        
        bool same_edge = false;
        //add the information of connected vertices to correlating arrays
        //and make sure to add to used so it goes to the next index for the next time
        
        //if an edge between the vertices already exists, keep the smaller edge
        for (int c = 0; c < graphList[first].used_connected; c++)
        {
            if (graphList[first].connected[c] == temp_vertex2)
            {
                //if the new edge is smaller replace it
                if (graphList[first].length[c] > temp_edge)
                {
                    graphList[first].connected[c] = temp_vertex2;
                    graphList[first].length[c] = temp_edge;
                    
                    if (graph_type == "undirected")
                    {
                        for (int s = 0; s < graphList[second].used_connected; s++)
                        {
                            if (graphList[second].connected[s] == temp_vertex)
                            {
                                graphList[second].connected[s] = temp_vertex;
                                graphList[second].length[s] = temp_edge;
                            }
                        }
                    }
                }
                
                same_edge = true;
            }
        }
        
        if (same_edge == false)
        {
            graphList[first].connected[graphList[first].used_connected] = temp_vertex2;
            graphList[first].used_connected++;
            graphList[first].length[graphList[first].used_length] = temp_edge;
            graphList[first].used_length++;
            
            
            if (graph_type == "undirected") //if undirected it goes both ways
            {
                graphList[second].connected[graphList[second].used_connected] = temp_vertex;
                graphList[second].used_connected++;
                graphList[second].length[graphList[second].used_length] = temp_edge;
                graphList[second].used_length++;
            }
        }
        
        
        
        
    }
    
    //ignore any comments b/t the vertex list and the edge count
    while (!input.eof() && (input.peek() =='#'))
    {
        input.ignore(256, '\n');
        
    }
    
    //this is the 2nd file now, read in the starting vertex name
    getline(input, start_vertex, '\n');
    
    bool check = false;
    
    //check to make sure that this vertex is one of the vertices
    for (int l = 0; l < vertex_count; ++l)
    {
        if (temp_name[l] == start_vertex)
        {
            check = true;
            break;
        }
    }
    
    
    //if it's not the name of a vertex, throw an error
    if ( check == false)
    {
        cout << "Error in graph file" << endl;
        
        exit(0);
    }
    
    
    
}

void Graph::bfs()
{
    int startIndex = 0;
    queue<Vertex> tempq; //queue for bfs
    string *connectedTo; //array of what a single vertex is connected to (for insert sort)
    double *connectedEdge; //array of edges
    Vertex *sorted; //alphabetically sorted to push onto queue
    
    int used = 0;
    int iterator = 0;
    int position = 0; //the position to insert the element into
    
    bool first = true; //is this the first item of teh above array?
    Vertex tempVertex; //for cout purposes
    Vertex tempVertex2; //for alphabetical :/
    string tempName; //temp string for vertex names for searching purposes
    int tempEdge; //temp edge
    
    //find the starting node
    for (int g = 0; g < vertex_count; g++)
    {
        if (graphList[g].identifier == start_vertex)
        {
            //mark the start index as visited
            graphList[g].visited = true;
            startIndex = g;
            //initialize queue by placing the starting vertex on it
            tempq.push(graphList[g]);
        }
    }
    
    //while the q isn't empty, pop things off, push any non
    //visited vertices onto the queue
    while (!tempq.empty())
    {
        //get the top item
        tempVertex = tempq.front();
        
        //pop off the first item since we have it now
        tempq.pop();
        
        //set them back to 0
        used = 0;
        iterator = 0;
        first = 0;
        connectedTo = new string[edge_count * edge_count];
        connectedEdge = new double[edge_count * edge_count];
        sorted = new Vertex[edge_count * edge_count];
        
        //get the names of all the vertices it's connected to
        for (int a = 0; a < tempVertex.used_connected; a++)
        {
            tempName = tempVertex.connected[a];
            
            for (int v = 0; v < vertex_count; v++)
            {
                //find the vertex, and push it onto queue if it hasn't been visited
                if (tempName == graphList[v].identifier && graphList[v].visited == false)
                {
                    //print out as we go
                    /*cout << tempVertex.identifier << endl;
                     cout << graphList[v].identifier << endl;
                     cout << tempVertex.length[a] << endl; */
                    
                    graphList[v].temp_length = tempVertex.length[a];
                    
                    //as you push it on the queue mark it as visited
                    graphList[v].visited = true;
                    //	tempq.push(graphList[v]);
                    
                    //if it is the first entry put it as the first item in the array
                    if (first == true)
                    {
                        
                        connectedTo[0] = graphList[v].identifier;
                        connectedEdge[0] = tempVertex.length[a];
                        sorted[0] = graphList[v];
                        first = false;	 
                        used++;
                        
                    }
                    else
                    {
                        while (graphList[v].identifier.compare(connectedTo[iterator]) < 0 && iterator <= used)
                        {
                            //iterate through the list
                            iterator++;
                            
                        }
                        
                        //set the position to where it should be inserted
                        position = iterator;
                        
                        //shift everything over to accomodate
                        for (int i = used; i >= position; --i)
                        {
                            connectedEdge[i + 1] = connectedEdge[i];
                            connectedTo[i+1] = connectedTo[i];
                            sorted[i+1] = sorted[i];
                        }
                        used++;
                        connectedEdge[position] = tempVertex.length[a];
                        connectedTo[position] = graphList[v].identifier;
                        sorted[position] = graphList[v];
                        
                    }
                    
                    
                    
                }
                
            }
            
        }
        
        for (int n = used - 1; n >= 0; n--)
        {
            tempq.push(sorted[n]);
        }
        
        //print everything out for each queue item in the new alphabetical order
        //but print backwards bc I messed up the alphabetical sort
        for (int t = used - 1; t >= 0; t--)
        {
            cout << tempVertex.identifier << endl;
            cout << connectedTo[t] << endl;
            cout << connectedEdge[t] << endl;
        }
        
    }
    
    //traverse through the vertices seeing if they are all visited
    for (int b = 0; b < vertex_count; b++)
    {
        if (graphList[b].visited == false)
        {
            cout << "No spanning tree." << endl;
            
            exit(0);
        }
        
        
    }
}


bool Vertex::operator < (const Vertex& b) const
{
	   int temp = 0;
	   temp = identifier.compare(b.identifier);
    
	   if (temp < 0)
       {
           return (false);
       }
    
       else
       {
           return (true);
       }
    
    
    
}


