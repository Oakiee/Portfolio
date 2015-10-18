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

//******************************************************************
//
//  Function:   cube::generate_cube
//
//  Purpose:    generates a dynamic 3D array to simulate a cube
//              containing the input numbers set to the size of the cube
//
//  Parameters:  none
//
// Member/Global Variables: none
//
// Pre Conditions: it has valid values, and a valid amount of values
//
// Post Conditions: sets up the arrays
//
// Calls:       none
//
//******************************************************************

//******************************************************************
//
//  Function:   repeats
//
//  Purpose:    determines whether or not there are repeats within the cube
//
//  Parameters:  ifs - input
//
// Member/Global Variables: SIZE - the size of the array
//                          tempArr[SIZE] - the temp array to store the data
//
// Pre Conditions: there is a size input right before a series of numbers
//                 of which there are (SIZE * SIZE * SIZE) of
//
// Post Conditions: returns whether there are repeats (true) or not (false)
//
// Calls:       algorithm
//
//******************************************************************

//******************************************************************
//
//  Function:   check_row
//
//  Purpose:    determines whether or not the sums of the rows are equal
//
//  Parameters:  none
//
// Member/Global Variables: sum - the sum of a single row
//			  temp - temporary storage for comparison
//
// Pre Conditions: the cube_arr has values
//
// Post Conditions: returns the sum or 0 if it's not equal
//
// Calls:       none
//
//******************************************************************

//******************************************************************
//
//  Function:   check_column
//
//  Purpose:    determines whether or not the sums of the columns are equal
//
//  Parameters:  none
//
// Member/Global Variables: sum - the sum of a single column
//			  temp - temporary storage for comparison
//
// Pre Conditions: the cube_arr has values
//
// Post Conditions: returns the sum or 0 if it's not equal
//
// Calls:       none
//
//******************************************************************

//******************************************************************
//
//  Function:   check_pillar
//
//  Purpose:    determines whether or not the sums of the pillars are equal
//
//  Parameters:  none
//
// Member/Global Variables: sum - the sum of a single pillar
//			  temp - temporary storage for comparison
//
// Pre Conditions: the cube_arr has values
//
// Post Conditions: returns the sum or 0 if it's not equal
//
// Calls:       none
//
//******************************************************************

//******************************************************************
//
//  Function:   check_super_diagonal
//
//  Purpose:    determines whether or not the sums of the super
//              diagonals are equal
//
//  Parameters:  none
//
// Member/Global Variables: sum - the sum of a single diagonal
//			  temp - temporary storage for comparison
//
// Pre Conditions: the cube_arr has values
//
// Post Conditions: returns the sum or 0 if it's not equal
//
// Calls:       none
//
//******************************************************************

//******************************************************************
//
//  Function:   check_orthogonal_diagonal
//
//  Purpose:    determines whether or not the sums of the o-diagonals
//		 are equal
//
//  Parameters:  none
//
// Member/Global Variables: sum - the sum of a single diagonal
//			  temp - temporary storage for comparison
//
// Pre Conditions: the cube_arr has values
//
// Post Conditions: returns the sum or 0 if it's not equal
//
// Calls:       none
//
//******************************************************************

//******************************************************************
//
//  Function:   magic_constant
//
//  Purpose:    sees whether the sums of rows, columns, etc.
//		abide by the magic constant
//
//  Parameters:  int row_sum - sum of a row
//		int column_sum - sum of a column
//	        int pillar_sum - sum of a pillar
//
// Member/Global Variables: magic - the magic constant
//
// Pre Conditions: the sums are calculated
//
// Post Conditions: returns true if it has a magic constant,
//			false if not
//
// Calls:       none
//
//******************************************************************




#include <iostream>
#include <algorithm>
#include <vector>
#include "cube.h"
using namespace std;



cube::cube()
{
    size = 0;
    cube_arr = NULL;
}

cube::~cube()
{
    delete[] cube_arr;
}

cube::cube(int initial_size)
{
    size = initial_size;
}

void cube::set_size(int new_size)
{
    size = new_size;
}

void cube::generate_cube()
{
    cin >> size;  //get the size on the top line
    
    //Create a cube the correct size (using 3D pointer arrays)
    cube_arr = new int**[size];
    
    for (int i = 0; i < size; ++i)
    {
        cube_arr[i] = new int *[size];
    }
    
    for (int j = 0; j < size; ++j)
    {
        for (int k = 0; k < size; ++k)
        {
            cube_arr[j][k] = new int[size];
        }
    }
    
    
    for (int l = 0; l < size; ++l)
    {
        for (int h = 0; h < size; ++h)
        {
            for (int g = 0; g < size; ++g)
            {
                cin >> cube_arr[l][h][g];
            }
        }
    }
    
}

int cube::check_row()
{
    int sum = 0;  //the sum of a given row
    int temp = 0;  //temporary placeholder to determine if the sums are equal
    
    
    for (int i = 0; i < size; ++i)
    {
        
        for (int j = 0; j < size; ++j)
        {
            
            sum = 0;  //reset the sum
            for (int k = 0; k < size; ++k)
            {
                
                
                sum += cube_arr[i][j][k];
                
                //initialize the temp value for the first row
                if (i == 0 && j == 0 && k == size - 1)
                {
                    temp = sum;
                }
            }
            if (temp != sum)
            {
                //there are at least two rows that are not equal
                return 0;
            }
            temp = sum;
            // cout << "the sum of a row: " << sum << endl;  //to check
        }
    }
    
    //all the rows are equal
    return temp;
    
}

int cube::check_column()
{
    int sum = 0;  //the sum of a given column
    int temp = 0;  //temporary placeholder to determine if the sums are equal
    
    //restructured from the check_row, so go to that for reference
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            sum = 0;  //reset the sum
            for (int k = 0; k < size; ++k)
            {
                sum += cube_arr[k][i][j];
                
                //initialize the temp value for the first column
                if (i == 0 && j == 0 && k == size - 1)
                {
                    temp = sum;
                }
            }
            if (temp != sum)
            {
                //there are at least two columns that are not equal
                return 0;
            }
            temp = sum;
        }
    }
    
    //all the columns are equal
    return temp;
}

int cube::check_pillar()
{
    int sum = 0;  //the sum of a given pillar
    int temp = 0;  //temporary placeholder to determine if the sums are equal
    
    //restructured from the check_row, so go to that for reference
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            sum = 0;  //reset the sum
            for (int k = 0; k < size; ++k)
            {
                sum += cube_arr[i][k][j];
                
                //initialize the temp value for the first pillar
                if (i == 0 && j == 0 && k == size - 1)
                {
                    temp = sum;
                }
            }
            if (temp != sum)
            {
                //there are at least two pillars that are not equal
                return 0;
            }
            temp = sum;
        }
    }
    
    //all the columns are equal
    return temp;
}

int cube::check_super_diagonal()
{
    int sum = 0;  //the sum of the diagonal(s)
    int temp = 0;  //the temporary holder for the previous sum
    
    //first super diagonal top left to bottom right
    for (int i = 0; i < size; ++i)
    {
        sum += cube_arr[i][i][i];
    }
    
    temp = sum;
    sum = 0;  //reset sum
    
    int m = size - 1;
    
    //top right to bottom left
    for (int j = 0; j < size; ++j)
    {
        sum += cube_arr[j][j][m];
        m--; //iterate the m alongside j
        
    }
    
    if (temp != sum)
    {
        return 0;
    }
    temp = sum;
    sum = 0;
    
    int k = size - 1;
    //bottom left to top right
    for (int l = 0; l < size; ++l)
    {
        sum += cube_arr[l][k][l];
        --k;  //iterate the k alongside l
        
    }
    
    
    if (temp != sum)
    {
        return 0;
    }
    temp = sum;
    sum = 0;
    
    int u = size - 1;
    //bottom right to top left
    for (int h = 0; h < size; ++h)
    {
        sum += cube_arr[h][u][u];
        --u;  //iterate the u alongside h
    }
    
    if (temp != sum)
    {
        return 0;
    }
    
    return sum;
    
}

int cube::check_orthogonal_diagonal()
{
    int sum = 0;  //the diagonal sum
    int temp = 0;  //placeholder
    int previous_sum = 0; //the sum of the previous diagonal set, for comparison
    
    //top left to bottom left
    for (int i = 0; i < size; ++i)
    {
        sum = 0;  //reset the sum
        for (int j = 0; j < size; ++j)
        {
            sum += cube_arr[j][j][i];
        }
        if (i == 0)
        {
            temp = sum;  // initializes the temp value first time through
        }
        if (temp != sum)
        {
            return 0;
        }
    }
    
    previous_sum = sum;
    
    //bottom left to top left
    for (int h = 0; h < size; ++h)
    {
        sum = 0; //reset the sum;
        int m = size - 1;
        for (int k = 0; k < size; ++k)
        {
            sum += cube_arr[k][m][h];
            --m;  //iterate the m along with the k
        }
        if (h == 0)
        {
            temp = sum;  // initializes the temp value first time through
        }
        if (temp != sum)
        {
            return 0;
        }
    }
    //check to see if the diagonal sets are equal
    if (previous_sum != sum)
    {
        return 0;
    }
    
    previous_sum = sum;
    
    //bottom left to bottom right
    for (int b = size - 1; b > -1; --b)
    {
        sum = 0; //reset the sum;
        
        for (int a = 0; a < size; ++a)
        {
            sum += cube_arr[a][b][a];
        }
        if (b == size - 1)
        {
            temp = sum;  // initializes the temp value first time through
        }
        if (temp != sum)
        {
            return 0;
        }
    }
    //check to see if the diagonal sets are equal
    if (previous_sum != sum)
    {
        return 0;
    }
    
    previous_sum = sum;
    
    //bottom right to bottom left
    for (int b = 0; b < size; ++b)
    {
        sum = 0; //reset the sum;
        int c = size - 1; //initialize c
        for (int a = 0; a < size; ++a)
        {
            sum += cube_arr[a][b][c];
            c--; //iterate c along with a
        }
        if (b == 0)
        {
            temp = sum;  // initializes the temp value first time through
        }
        if (temp != sum)
        {
            return 0;
        }
    }
    
    //check to see if the diagonal sets are equal
    if (previous_sum != sum)
    {
        return 0;
    }
    
    previous_sum = sum;
    
    
    return sum;
}

bool cube::magic_constant(int row_sum, int column_sum, int pillar_sum)
{
    float magic;  //this is the magic_constant
    
    magic = ((size * size * size + 1) * size) / 2;
    // cout << "magic num is " << magic << endl;
    
    if (magic == row_sum && magic == column_sum && magic == pillar_sum)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

bool cube::repeats()
{
    
    //traverse the cube, comparing to each element to find any repeats
    //if there is one, return
    
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int m = 0; m < size; m++)
            {
                //the value to be compared to all other values
                int first = cube_arr[m][j][i];
                
                for (int b = i; b < size; b++)
                {
                    for (int h = j; h < size; h++)
                    {
                        for (int t = m + 1; t < size; t++)
                        {
                            int second = cube_arr[t][h][b];
                            //check if they are equal, if so return
                            if (first == second)
                            {
                                return (true);
                            }
                            
                        }
                    }
                }
            }
        }
    }
    
    return (false);
    
}
