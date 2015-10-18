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
      //******************************************************************

#include <iostream>
#include <string>



      struct Vertex
      {
         std::string identifier; //the name of this vertex 
         //the following two arrays have correlating index values
         std::string *connected; //array of what vertex is connected to
         double *length; //array of edge lengths
	 int temp_length; //used for alphabetical order because when I'm about to 
		          //fail a class, forget about logic and do what works.
         bool visited;
	 int used_connected;
	 int used_length;
	 //overload comparison operator for priority queue (hantai desu ne)
	// because I don't want to deal with priority queue being backwards
	//from what I want
         bool operator > (const Vertex& b) const;
	 bool operator < (const Vertex& b) const;

      };



class Graph
{

   public:
      void generate_graph(std::istream& input);
      void bfs(); 

   private:

      int vertex_count;
      int edge_count; 
      std::string start_vertex; //the vertex you start the bfs from 
      Vertex *graphList; //list containing all the verteces in the graph

};



