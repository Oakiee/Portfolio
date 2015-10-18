//*******************************************************************
//
//  Program:     Homework 1 - Project 1
//
//  Author:      Amanda Oyakawa
//  Email:       ao441309@ohio.edu
//
//  Lab Section: 101 Bibo Shi
//
//  Description: This determines what kind of cube you have from an input file
//		 whether it is Normal perfect, normal semi-perfect, abnormal perfect
//               abnormal semi-perfect, or imperfect.
//
//  Date:        January 26th, 2014
//
//*******************************************************************


#include <iostream>
#include "cube.h"
using namespace std;


int main()
{
    
    cube cube1;  //cube object type created for this project
    bool repeat = false;  //the bool to say if there are repeats in the cube or not
    int row = false;  //are the rows' sums equal?
    int column = false;   //are the columns' sums equal?
    int pillar = false;   //are the pillars' sums equal?
    int sdiagonal = false;  //are the super diagonals' sums equal?
    int odiagonal = false;  //are the orthogonal diagonals' sums equal?
    bool magic = false;  //does it abide by the magic constant?
    
    cube1.generate_cube();  //read the cin is as a 3d array
    
    row = cube1.check_row();
    column = cube1.check_column();
    pillar = cube1.check_pillar();
    sdiagonal = cube1.check_super_diagonal();
    odiagonal = cube1.check_orthogonal_diagonal();
    magic = cube1.magic_constant(row, column, pillar);
    repeat = cube1.repeats();   //see if there are any repeats
    
    //prints out a succinct summary of the cube - helps with debugging
    /* if (repeat != 0)
     {
     cout << "YES Repeats" << endl;
     }
     else
     {
     cout << "NO  Repeats" << endl;
     }
     
     if (row != 0)
     {
     cout << "YES, Rows' sums are equal" << endl;
     }
     else
     {
     cout << "NO, Rows' sums not equal" << endl;
     }
     
     if (column != 0)
     {
     cout << "YES, Columns' sums are equal" << endl;
     }
     else
     {
     cout << "NO, Columns' sums not equal" << endl;
     }
     
     if (pillar != 0)
     {
     cout << "YES, Pillars' sums are equal" << endl;
     }
     else
     {
     cout << "NO, Pillars' sums not equal" << endl;
     }
     
     if (sdiagonal != 0)
     {
     cout << "YES, Super Diagonals' sums are equal" << endl;
     }
     else
     {
     cout << "NO, Super Diagonals' sums not equal" << endl;
     }
     
     if (odiagonal != 0)
     {
     cout << "YES, Orthogonal Diagonals' sums are equal" << endl;
     }
     else
     {
     cout << "NO, Orthogonal Diagonals' sums not equal" << endl;
     }
     
     if (magic == true)
     {
     cout << "YES Magic Constant" << endl << endl;
     }
     else
     {
     cout << "NO  Magic Constant" << endl << endl;
     } */
    
    
    
    //print out what kind of cube it is
    if (repeat == false && magic == true && row != 0 && column != 0 && pillar != 0 && sdiagonal != 0)
    {
        if (odiagonal != 0)
        {
            cout << endl << "Normal perfect cube" << endl << endl;
        }
        else
        {
            cout << endl << "Normal semi-perfect cube" << endl << endl;
        }
        
    }
    
    else if (repeat == true)
    {
        cout << endl << "Imperfect cube" << endl << endl;
    }
    
    else if (row != 0 && column != 0 && pillar != 0 && sdiagonal != 0)
    {
        if (odiagonal != 0)
        {
            cout << endl << "Abnormal perfect cube" << endl << endl;
        }
        else
        {
            cout << endl << "Abnormal semi-perfect cube" << endl << endl;
        }
    }
    
    else 
    {
        cout << endl << "Imperfect cube" << endl << endl;
    }
    
}
