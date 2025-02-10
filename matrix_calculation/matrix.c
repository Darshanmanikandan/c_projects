// finding eigen values and eigen vectors 

#include<stdio.h>
#include<stdlib.h>
#include<complex.h>
#include<errno.h>
#include "equations_solve.h"

#define max_order_limit 3

int main()
{    
    solve result; 
    int matrix[3][3];
    short row,col ;
    printf("enter the number of rows and col:");
    scanf("%hd%hd",&row,&col);

    //getting input using the function "get_values"
    if((row <= max_order_limit && col <= max_order_limit) && (row == col) ){
        get_values(&matrix[0][0],row,col);
              short opt;
    //print the data
        print_mat(*matrix,row,col); 
        printf("\t\tWhat Option do you prefer\t\t\n");
        printf(" 1.find the trace of the matrix \n 2.find the sum of the minors \n 3.find the determinant of the matrix \n 4.Find the Eigen values\n");
        printf("Enter your choice :");
        scanf("%hd",&opt);

        switch(opt){
            case 1: printf("sum of the main diagonal elements : %f\n",sum_of_dia(&matrix[0][0],row,col)); break;
            case 2: printf("sum of the minor : %f\n",sum_of_minor(&matrix[0][0],row,col)); break;
            case 3: printf("the determinant of the matix :%2f\n",determinant(&matrix[0][0],row,col)); break;
            case 4:  
                   result = find_eigen_value(&matrix[0][0],row,col);
                   if(result.hasComplexRoots == 1)
                   {
                      printf("the eigen values are : %.2lf+%.2lfi and %.2lf-%.2lfi ",result.RealPart,result.ImagPart,result.RealPart,result.ImagPart);
                   }else {
                      printf("the eigen values are : %.2f,%.2f \n",result.root1,result.root2);
                   }
                   break;
            default: fprintf(stderr,"Invalid option...!"); exit(0);
        }
    } else{
        fprintf(stderr,"Invalid order of the matrix! \n");
        return -1;
    }

        return 0;
}

   