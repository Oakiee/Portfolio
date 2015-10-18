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

#include <iostream>
#include <string>
using namespace std;
#include "graph.h"

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

int main()
{
    Graph graph1;
    
    graph1.generate_graph(cin);
    
    graph1.bfs();
}
