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
//*******************************************************************

//******************************************************************
//
//  Function:   generate_tree
//
//  Purpose:    generates a binary tree from an input file
//
//  Parameters:  istream& input
//
// Member/Global Variables:      NODE - used to compare
//                               LEFT_CHILD -  used to compare
//                               RIGHT_CHILD  - used to compare
//                               node_count //the number of nodes
//                               current_count  //how many nodes have been read in thus far?
//                               type //node, right or left children
//                               identifier//name of the node
//                               arr  //array to store nodes in
//                               used //initialize used to 0
//                               current_parent  //this s the current array index selected for
//                               current_index//what index is currently selected in the array?
//
// Pre Conditions: there is input
//
// Post Conditions: creates a tree if valid, tells user it's
//                  invalid if invalid
//
// Calls:       cstdlib, iostream
//                    (n = number of items in list)
// Space Complexity: N
//
// Time Complexity: Big O(n)
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
// Member/Global Variables:     root_count - This counts the number of roots
//                                           because if there is more than 1
//					  it is invalid
//
// Pre Conditions: there is a valid tree
//
// Post Conditions: sets the tree's root pointer
//
// Calls:       cstdlib, iostream
//                    (n = number of items in list)
// Space Complexity: N
//
// Time Complexity: Big O(n)
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
// Member/Global Variables:      temp_stack - the temporary stack to hold all nodes
//                               *current_node - current node for traversal
//
// Pre Conditions: there is a valid binary tree
//
// Post Conditions: prints out pre-order traversal
//
// Calls:       stack, iostream
//                    (n = number of items in list)
// Space Complexity: N * 2
//
// Time Complexity: Big O(n^2)
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
// Member/Global Variables:      temp_stack - the temporary stack to hold all nodes
//                               *current_node - current node for traversal
//
// Pre Conditions: there is a valid binary tree
//
// Post Conditions: exits the program and tells the user if it is invalid, does
//		   nothing discernable to user if it is valid
//
// Calls:       stack, iostream
//                    (n = number of items in list)
// Space Complexity: N * 2
//
// Time Complexity: Big O(n^2)
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
// Member/Global Variables:          decoded :  the decoded message to print out
//                                   str_count : number of 1's and 0's in the message
//                                   next_character : used for the loop
//                                   current : keeps track of the current node
//				   is_leaf : bool to make sure the message isn't too long
//
// Pre Conditions: there is a valid binary tree
//
// Post Conditions: prints out the decoded Huffman message
//
// Calls:       iostream
//                    (n = number of strings in message)
// Space Complexity: N * 2
//
// Time Complexity: Big O(n)
//
//******************************************************************


#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include "tree.h"
using namespace std;


TreeNode::TreeNode()
{
    
    left_child = NULL;
    right_child = NULL;
    root = true; //initialize it as being a root
    parent = "                 ";
    
}


void TreeNode::set_left(TreeNode *left)
{
    left_child = left;
}

void TreeNode::set_right(TreeNode *right)
{
    right_child = right;
}

void TreeNode::set_data(std::string new_data)
{
    data = new_data;
}

void TreeNode::set_root(bool new_value)
{
    root = new_value;
}


// Space Complexity: N
// Time Complexity: Big O(n)
void Tree::generate_tree(istream& input)
{
    //strings to compare
    string NODE = "NODE";
    string LEFT_CHILD = "LEFT_CHILD";
    string RIGHT_CHILD = "RIGHT_CHILD";
    string MESSAGE = "MESSAGE";
    
    int node_count = 0;  //the number of nodes
    int current_count = 0;  //how many nodes have been read in thus far?
    string type = " ";
    string identifier = " ";
    
    //initial check - if the first line is blank it is invalid
    if (!input.eof() && input.peek()=='\n')
    {
        cout <<  "The first line was blank, which is invalid" << endl;
        exit(0);
    }
    
    //skip any comments and new lines at beginning and then get # of nodes
    while (!input.eof() && (input.peek() =='#'))
    {
        input.ignore(256, '\n');
        
    }
    //read in the first number as the node count
    input >> node_count;
    if (!input.eof() && (input.peek() == '\n'))
    {
        input.ignore(2, '\n');
    }
    
    //if the first non-comment line is not an integer, error
    if (input.fail() || node_count < 0)
    {
        cout << "The input tree is not in the correct format!" << endl;
        exit(0);
    }
    //if the node count is 0 then you're done reading the file
    if (node_count == 0)
    {
        cout << "error, cannot have a message with an empty tree" << endl;
        exit(0);
    }
    
    
    //ignore any comments b/t the node count and first item
    while (!input.eof() && (input.peek() =='#'))
    {
        input.ignore(256, '\n');
        
    }
    
    //if there is a blank line in the file it is invalid
    if (!input.eof() && input.peek() == '\n')
    {
        
        cout << "Any blank lines in the file make it invalid" << endl;
        exit(0);
    }
    
    // read the word, hopefully "MESSAGE"
    getline(input, type, ' ');
    
    if (type.compare(MESSAGE) != 0)
    {
        cout << "The input tree is not in the correct format!" << endl;
        exit(0);
    }
    
    else
    {
        getline(input, message , '\n');
    }
    
    //ignore any comments b/t the message and first item
    while (!input.eof() && (input.peek() =='#'))
    {
        input.ignore(256, '\n');
        
    }
    
    //if there is a blank line in the file it is invalid
    if (!input.eof() && input.peek() == '\n')
    {
        cout << "Any blank lines in the file make it invalid" << endl;
        exit(0);
    }
    count = node_count; //set the count in the tree to the number read in
    arr = new TreeNode*[node_count];  //array to store nodes in
    used = 0; //initialize used to 0
    int current_parent = 0; //this is the current array index selected for
    //node parent declaration
    //in order to attach children to them
    int current_index = 0; //what index is currently selected in the array?
    
    //Initial read
    getline(input, type, ' ');
    
    //if the first thing is anything other than a node than it is invalid
    if (type.compare(NODE) != 0)
    {
        cout << "The input tree is not in the correct format!" << endl;
        exit(0);
    }
    
    while (current_count < node_count)
    {
        
        //if there is a blank line in the file it is invalid
        if (!input.eof() && input.peek() == '\n')
        {
            cout << "The input tree is not in the correct format!" << endl;
            exit(0);
        }
        
        //it says NODE *************************************
        if (type.compare(NODE) == 0)
        {
            getline(input, identifier, '\n');
            
            //is this an original identifier/node?
            bool original = true; //default to true
            
            //see if this node has already been declared or not
            for (int i = 0; i < used; i++)
            {
                if (arr[i] -> data == identifier)
                {
                    original = false;
                    current_parent = i;
                    break; //break out early if so
                }
                
            }
            
            if (original)
            {
                arr[used] = new TreeNode;
                arr[used] -> data = identifier;
                current_parent = used;
                
                used++;
                current_count++;
            }
            
        }
        
        
        //it says RIGHT_CHILD **********************************
        else if (type.compare(RIGHT_CHILD) == 0)
        {
            
            if (node_count == 2)
            {
                cout << "The input tree is not in the correct format!" << endl;
                exit(0);
            }
            
            getline(input, identifier, '\n');
            
            //is this an original identifier/node?
            bool original = true; //default to true
            
            //see if this node has already been declared or not
            for (int i = 0; i < used; i++)
            {
                if (arr[i] -> data == identifier)
                {
                    original = false;
                    
                    //if it's root bool is false that means it already has a parent
                    if (arr[i] -> root == false && arr[current_parent] -> data != arr[i] -> parent)
                    {
                        cout << "The input tree is not in the correct format!" << endl;
                        exit(0);
                    }
                    
                    current_index = i;
                    break; //break out early if so
                }
                
            }
            
            if (arr[current_parent] -> right_child == NULL)
            {
                
                //if it has not been declared yet
                if (original)
                {
                    //create a new node in the array
                    arr[used] = new TreeNode;
                    arr[used] -> data = identifier;
                    
                    //set the node as a child
                    arr[current_parent] -> right_child = arr[used];
                    
                    //set the name of the parent
                    arr[used] -> parent = arr[current_parent] -> data;
                    
                    //set the node as not being a root anymore
                    arr[used] -> root = false;
                    
                    used++;
                    current_count++;
                }
                else
                {
                    //set the node as a child
                    arr[current_parent] -> right_child = arr[current_index];
                    
                    //set the name of the parent
                    arr[current_index] -> parent = arr[current_parent] -> data;
                    
                    //set the node as not being a root anymore
                    arr[current_index] -> root = false;
                    
                }
            }
            
            //there is already a left child, it can only be a degree 2 node
            else
            {
                cout << "The input tree is not in the correct format!" << endl;
                exit(0);
            }
            
            
            
        }
        
        //it says LEFT_CHILD ********************************
        else if (type.compare(LEFT_CHILD) == 0)
        {
            getline(input, identifier, '\n');
            
            //is this an original identifier/node?
            bool original = true; //default to true
            
            //see if this node has already been declared or not
            for (int i = 0; i < used; i++)
            {
                if (arr[i] -> data == identifier)
                {
                    original = false;
                    
                    //if it's root bool is false that means it already has a parent
                    if (arr[i] -> root == false && arr[current_parent] -> data != arr[i] -> parent)
                    {
                        cout << "The input tree is not in the correct format!" << endl;
                        exit(0);
                    }
                    
                    current_index = i;
                    break; //break out early if so
                }
                
            }
            if (arr[current_parent] -> left_child == NULL)
            {
                //if it has not been declared yet
                if (original)
                {
                    //create a new node in the array
                    arr[used] = new TreeNode;
                    arr[used] -> data = identifier;
                    
                    //set the node as a child
                    arr[current_parent] -> left_child = arr[used];
                    
                    //set the name of the parent
                    arr[used] -> parent = arr[current_parent] -> data;
                    
                    //set the node as not being a root anymore
                    arr[used] -> root = false;
                    
                    used++;
                    current_count++;
                }
                else
                {
                    //set the node as a child
                    arr[current_parent] -> left_child = arr[current_index];
                    
                    //set the name of the parent
                    arr[current_index] -> parent = arr[current_parent] -> data;
                    
                    //set the node as not being a root anymore
                    arr[current_index] -> root = false;
                    
                }
                
            }
            //there is already a left child, it can only be a degree 2 node
            else
            {
                cout << "The input tree is not in the correct format!" << endl;
                exit(0);
            }
            
        }
        
        else
        {
            cout << "The input tree is not in the correct format!" << endl;
            exit(0);
        }
        
        
        //skip comments
        while (!input.eof() && (input.peek() =='#'))
        {
            input.ignore(256, '\n');
        }
        
        //if there aren't enough nodes declared, throw an error
        if (!input.eof())
        {
            getline(input, type, ' ');
        }
        
        else if (current_count != node_count)
        {
            cout << "The input tree is not in the correct format!" << endl;
            exit(0);
        }
        
    }
    
}

// Space Complexity: N
// Time Complexity: Big O(n)
void Tree::find_root()
{
    //this will help check if there is more than one root
    int root_count = 0;
    
    for (int i = 0; i < used; i++)
    {
        if (arr[i] -> root == true)
        {
            //set the root to point to the current index it found
            root = arr[i];
            root_count++;
        }
    }
    
    if (root_count != 1)
    {
        cout << "The input tree is not in the correct format!" << endl;
        
        exit(0);
    }
    
    
}

// Space Complexity: N
// Time Complexity: Big O(n^2)
void Tree::check_degrees()
{
    if (count == 2)
    {  //if there are only 2 nodes, there has to be  a node with one child
        return;
    }
    
    //otherwise if there are any nodes with only one child,
    // it is an invalid Huffman code tree, due to being
    //inefficient
    
    //this is a preorder traversal, but e won't print anything out
    stack<TreeNode*> temp_stack;
    TreeNode *current_node = root;
    
    while(true)
    {
        while (current_node != NULL)
        {
            //if it only has a left child
            if (current_node -> left_child != NULL && current_node -> right_child == NULL)
            {
                cout << "The input tree is not in the correct format!" << endl;
                exit(0);
            }
            
            //if it only has a right child
            if (current_node -> right_child != NULL && current_node -> left_child == NULL)
            {
                cout << "The input tree is not in the correct format!" << endl;
                exit(0);
            }
            //traverse towards the left
            temp_stack.push(current_node);
            current_node = current_node -> left_child;
        }
        
        if (!temp_stack.empty())
        {
            //move to the right
            current_node = temp_stack.top();
            temp_stack.pop();
            current_node = current_node -> right_child;
            
        }
        else if (temp_stack.empty())
        {
            break; //get out of infinite loop
        }
        
    }
    
    
}


// Space Complexity: N * 2
// Time Complexity: Big O(n)
void Tree::preorder()
{
    cout << endl << endl;
    // cout << "Pre-order Traversal list of nodes: " << endl;
    stack<TreeNode*> temp_stack;
    TreeNode *current_node = root;
    
    while(true)
    {
        while (current_node != NULL)
        {
            //      cout << current_node -> data << endl;
            temp_stack.push(current_node);
            current_node = current_node -> left_child;
        }
        
        if (!temp_stack.empty())
        {
            //move to the right
            current_node = temp_stack.top();
            temp_stack.pop();
            current_node = current_node -> right_child;
            
        }
        else if (temp_stack.empty())
        {
            break; //get out of infinite loop
        }
        
    } 
    
}


// Space Complexity: N * 2
// Time Complexity: Big O(n)
void Tree::decode()
{
    string decoded = ""; // the decoded message to print out
    int str_count = message.size();
    string next_character = " "; //used for the loop
    TreeNode *current = root; //keeps track of the current node
    bool is_leaf = true; //did you end the message on a leaf? if not it is an error
    
    cout << endl << endl;
    
    for (int i = 0; i < str_count; i++)
    {
        is_leaf = false; //set it to false each time
        next_character = message[i];
        next_character = message[i];
        if (next_character.compare("0") == 0) //if the character is 0
        {
            
            //can't traverse left any more
            if (current -> left_child == NULL) 
            {
                cout << "Error in message." << endl;
                exit(0);
            }
            
            //if there is a left child
            else 
            {
                current = current -> left_child;
                
                //if it is a leaf
                if (current -> left_child == NULL && current -> right_child == NULL)
                {
                    is_leaf = true;
                    decoded = decoded + current -> data;
                    current = root; 
                }
                
            } 
        }
        
        else if (next_character.compare("1") == 0) //if the character is 1
        {
            
            //can't traverse right anymore
            if (current -> right_child == NULL) 
            {
                cout << "Error in message." << endl;
                exit(0);
            }
            //if there is a right child
            else 
            {
                current = current -> right_child;
                
                //if it is a leaf
                if (current -> right_child == NULL && current -> left_child == NULL)
                {
                    is_leaf = true;
                    decoded = decoded + current -> data;
                    current = root; 
                }
                
            }}
        
        //it is not a 1 or 0 so it is invalid
        else 
        {
            cout << "Error in message." << endl;
            exit(0);
        }
        
        
    }
    
    if (is_leaf == false)
    {
        cout << "Error in message." << endl;
        exit(0);
    }
    
    cout << decoded << endl << endl;
}




