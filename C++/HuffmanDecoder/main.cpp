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

#include <iostream>
#include <string>
using namespace std;
#include "tree.h"


int main()
{
    Tree tree_1;
    
    tree_1.generate_tree(cin);
    
    tree_1.find_root();
    
    tree_1.check_degrees();
    
    tree_1.preorder();
    
    tree_1.decode();
    
}