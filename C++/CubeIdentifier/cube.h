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
      //  Function:   generate_cube
      //                                                                  
      //  Purpose:    generates a dynamic 3D array to simulate a cube
      //              containing the input numbers set to the size of the cube                                
      //                                                                  
      //  Parameters:  none
      //
      // Member/Global Variables: none
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
      //                                                                  
      //******************************************************************



#include <iostream>
#include <algorithm>
#include <vector>

class cube
{
   public:
  
      cube();
      ~cube();
      cube(int initial_size);

      //mutators
      void set_size(int new_size);
      void generate_cube();

      //accessors
      int get_size() const {return size;}

      int check_row();
      int check_column();
      int check_pillar();
      int check_super_diagonal();
      int check_orthogonal_diagonal();       
      bool magic_constant(int row_sum, int column_sum, int pillar_sum);
      bool repeats();

      

   private:

      int size;  //this is the size n of the cube
      int ***cube_arr;   //the pointer to the 3D array signifying a cube

}; 




