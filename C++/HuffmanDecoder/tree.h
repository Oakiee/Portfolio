//******************************************************************* 
//                                                                    
//  Program:     Homework 3 - Project 3                              
//                                                                     
//  Author:      Amanda Oyakawa
//  Email:       ao441309@ohio.edu
//                                                                    
//  Lab Section: 101 Bibo Shi
//                                                                    
//  Description: This program decodes a Huffman compressed message
//               it takes a Binary Tree input and Huffman encoded
//               message and it will output the decoded message 
//                                                                    
//  Date:        February 27th, 2014 
//
//
//		2nd and last   4th and last
//                                                                    
//*******************************************************************

      //******************************************************************
      //                                                                  
      //  Function:   generate_tree
      //                                                                  
      //  Purpose:    generates a binary tree from an input file                              
      //                                                                  
      //  Parameters:  istream& input
      //                                                                  
      //                                                                
      //******************************************************************

      //******************************************************************
      //                                                                  
      //  Function:   find_root()
      //                                                                  
      //  Purpose:    finds the root of a binary tree and sets the root pointer 
      //               to the root node                            
      //                                                                  
      //  Parameters:  none
      //                                                                  
      //                                                                
      //******************************************************************

      //******************************************************************
      //                                                                  
      //  Function:   preorder()
      //                                                                  
      //  Purpose:    prints out a binary tree in a preorder traversal manner                           
      //                                                                  
      //  Parameters:  none
      //                                                                
      //******************************************************************

      //******************************************************************
      //                                                                  
      //  Function:   check_degrees()
      //                                                                  
      //  Purpose:    determines if it is an inefficient Huffman code binary tree
      //		by seeing if there is any nodes with only one child
      //		with the exception of a 2 node tree                          
      //                                                                  
      //  Parameters:  none
      //                                                                                                                              
      //******************************************************************

      //******************************************************************
      //                                                                  
      //  Function:   decode()
      //                                                                  
      //  Purpose:    takes the message from the input and prints out the 
      //		corresponding message using the binary tree as a
      //		Huffman tree                       
      //                                                                  
      //  Parameters:  none
      //                                                                                                                       
      //******************************************************************

#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>

class Tree;

class TreeNode 
{ 

   friend class Tree; 

   public:
 
      TreeNode();

      //mutators
         void set_left(TreeNode *left);
	 void set_right(TreeNode *right);
	 void set_data(std::string new_data);
	 void set_root(bool new_value);

      //accessors
         bool get_root() const {return root;}
         TreeNode get_left() const {return *left_child;}
         TreeNode get_right() const {return *right_child;}
         std::string get_data() const {return data;}
   
   private:

      TreeNode *left_child; 
      std::string data;
      TreeNode *right_child;
      bool root;  //is this node the root? 
      std::string parent; //name of parent

};


class Tree
{

   public:

      //mutators
      void generate_tree(std::istream& input);
      //accessors
      int get_degree() const {return degree;}
      bool get_valid() const {return valid;}
      void find_root(); 
      void preorder();
      void check_degrees(); 
      void decode();


   private:
      std::string message; // the encoded huffman message
      int count; // number of nodes in the tree
      bool valid;  //was the file valid?
      int used; //amount of array used
      TreeNode *root;  //points to the root of the tree
      int degree;  //the degree of the tree
      TreeNode **arr; //array for sorting and searching purposes

};





