#include "equations_solve.h"
#include<stdio.h>
#include<math.h>


int get_values(int* m , int limit_row , int limit_col)
{
    for(int i=0;i<limit_row;i++)
    {
        for(int j=0 ; j<limit_col ;j++)
        {
            printf("enter the value for matrix[%d][%d] :",i+1,j+1);
            scanf("%d",(m + i * limit_col + j));
        // pointers for 2d array can be given as mentioned above

        }
    }

    return 0;
}

int print_mat(int* m , int limit_row , int limit_col)
{
    for(int i=0;i<limit_row;i++)
    {
        for(int j=0 ; j<limit_col ; j++)
        {
            printf("%d\t",*(m + i *limit_col + j));
        }
        printf("\n");
    }

    return 0;
}

double sum_of_dia(int* m , int limit_row , int limit_col)
{   
    // store the sum in the variable s1

    double s1=0 ;
    if(limit_col == 2 && limit_row == 2){
          s1=*(m + 0) + *(m + 3);
    } 

    if(limit_row == 3 && limit_col == 3){
            s1 = *(m + 0) + *(m + 4) + *(m + 8);   
    }
    return s1;
}


// this function can be used only when the order of the matrix is 3*3

    double sum_of_minor(int* m, int limit_row , int limit_col)
    {    
        // storing sum of minor in s2
            double s2=0;
            if(limit_col ==2 && limit_row ==2){
                s2 = (*(m + 0) * *(m + 3) ) - ( *(m + 1) * *(m + 2) ) ;
            }
    if(limit_col == 3 && limit_row ==3){
        for(int i=0;i<limit_row;i++)
        {   
            for(int j=0 ; j<limit_col ; j++)
            {
                if(i==0 && j==0)
                     s2+=*(m + 4) * *(m + 8) - *(m + 5) * *(m + 7);
                
                if(i==1 && j==1)
                     s2+=*(m + 3) * *(m + 8) - *(m + 5) * *(m + 6);
                
                if(i==2 && j==2)
                     s2+=*(m + 3) * *(m + 7) - *(m + 4) * *(m + 6);
            }
        } 
    }
        // if s2 is true return the value of s2 
        // else return an error code -1

             if(s2)
                return s2;
             else
                return -1 ;

    }


    double determinant(int* m ,int limit_row , int limit_col) 
{   
    double det;
    if(limit_col == 3 && limit_row == 3){
        det = (*(m + 0) * ((*(m + 4) * *(m + 8)) - (*(m + 5) * *(m + 7)))) 
             - (*(m + 1) * ((*(m + 3) * *(m + 8)) - (*(m + 5) * *(m + 6)))) 
             + (*(m + 2) * ((*(m + 3) * *(m + 7)) - (*(m + 4) * *(m + 6))));
    } 
    else if(limit_col == 2 && limit_row == 2){
        det = *(m + 0) * *(m + 3) - *(m + 1) * *(m + 2);
    } 
    else {
        fprintf(stderr, "Something Went Wrong!\n");
    }
        return det;
}


    solve find_eigen_value(int* m,int limit_row,int limit_col){
        solve s_equation; 
        double a,b,c;
        if(limit_col == 2 && limit_row == 2){
            s_equation.hasComplexRoots=0;
            b=sum_of_dia( m ,limit_row,limit_col) ;
            c=determinant( m , limit_row ,limit_col);
            s_equation.discriminant = (b * b) - (4 * c) ;

            if (s_equation.discriminant > 0) {
             // Two real and distinct roots
                s_equation.root1 = (b + sqrt(s_equation.discriminant)) / 2 ;
                s_equation.root2 = (b - sqrt(s_equation.discriminant)) / 2;
            }
            else if (s_equation.discriminant == 0) {
             // Two real and equal roots
                s_equation.root1 = s_equation.root2 = -b / 2 ;
            }
            else {
             // Complex roots
                s_equation.hasComplexRoots=1;
                s_equation.RealPart = -b /2 ;
                s_equation.ImagPart = sqrt(-s_equation.discriminant) / 2 ;
            }
        
        } else if(limit_col == 3 && limit_row==3){
            printf("Yet to be done\n");
        } else {
            //exit(0);
            printf("do something\n");
        }
        return s_equation;
    }