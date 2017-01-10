//
//  main.c
//  HouseHolderMethod
//
//  Created by 袁萍 on 2017/1/10.
//  Copyright © 2017年 袁萍. All rights reserved.
//

#include <stdio.h>
#include "math.h"

double * matrixCopy(double * , int , int );
void solveMatrixWithHouseHolderMethod(double * , int ,int );
void houseHolder(double * , int , double * ,int );
void resetMarixWithBonderIJ(double * , double * , int ,int ,int ,int );
void calculateSubMatrix(double * , int ,int ,double *,int,int,double *,double);
void printfVector(double * , int );
void printfMatrix(double * ,int ,int );
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    int rows = 4 , columns = 4;
    double  orgMatrix[16] = {1,2,3,1,4,5,2,1,3,2,4,1,5,1,2,3};
    
    double * matrix = malloc(rows*columns*sizeof(double));
    // to access i,j use *(matrix+i * row +j)
    //initialization
    /*
    double r1 = {1,2,3,1};
    *(matrix) = r1;
    double r2 = {4,5,2,1};
    *(matrix+rows) = r2;
    double r3 = {3,2,4,1};
    *(matrix+2*rows) = r3;
    double r4 = {5,1,2,3};
    *(matrix+3*rows) = r4;
    */
    int i = 0, j = 0;
    for (i=0; i<rows; i++) {
        for (j = 0; j<columns; j++) {
            *(matrix+i*rows+j) = orgMatrix[i*rows+j];
        }
    }
    //double * matrix = &orgMatrix;
    printfMatrix(matrix,rows,columns);
    double * b = matrixCopy(matrix, rows, columns);
    houseHolder(matrix, rows, b, columns);
    printf("the result of A is :\n");
    printfMatrix(matrix,rows,columns);
   // solveMatrixWithHouseHolderMethod(matrix,rows,columns);
    
    return 0;
}
// a is n*n , b n*m matrix
void houseHolder(double * A, int n ,double * b, int m){
    //solveMatrixWithHouseHolderMethod(<#double *matrix#>, <#int rows#>, <#int columns#>)
    int i = 0 , j = 0 ; // i , j means the point to be handled
    for( i = 0 ; i< n -1; i++){
        resetMarixWithBonderIJ(A,b,n,m,i,j);
        j++;
    }
}
void resetMarixWithBonderIJ(double * A, double *b, int rows,int columns, int i ,int j){
    double normA = 0;
    double a1 = *(A+i*rows+j);
    double sumOfSquareA = 0 ;
    int rowsNumberOfSubMatrix = columns -(i);
    //calcuate normA
    int r = 0 ,c = 0;
    for (r = i; r<rows; r++) {
        sumOfSquareA += pow((*(A+r*rows+j)),2);
    }
    normA = sqrt(sumOfSquareA);
    
    
    // initialize e1
    double *e1 = malloc(rowsNumberOfSubMatrix*sizeof(double));
    *(e1) = 1;
    for(r = 1;r < rowsNumberOfSubMatrix;r++){
        *(e1+r) = 0;
    }
    printf("vector of e1");
    printfVector(e1, rowsNumberOfSubMatrix);
    double * v = malloc(rowsNumberOfSubMatrix*sizeof(double));
    //calcuate the vector v
    for(r = 0; r<rows;r++){
        
        if(a1 > 0){
            *(v+r) = *(A+(i+r)*rows + j)+normA*(*(e1+r));
        }else{
            *(v+r) = *(A+(i+r)*rows + j)-normA*(*(e1+r));
        }
    }
    printf("vector of v ");
    printfVector(v, rowsNumberOfSubMatrix);
    double VStartV2 = normA*(normA+(a1>0?a1:-a1));
   // double VStartB = 0;
    // calcuate vstartb
    calculateSubMatrix(A, rows, columns, v, i, j, b,VStartV2);

}
double getSquareSumFromVector(double * vector, int length){
    double result = 0;
    int i =0 ;
    for( i = 0 ;i<length ;i++){
        result+=pow((*(vector+i)),2);
    }
    return result;
}
void calculateSubMatrix(double * A,int rows, int columns ,double * v , int i ,int j , double * b,double VStartV2){
    int r = 0, c = 0,rSub = 0 , cSub = 0;
    // calculate for each columns
   // for(c = j ; c < columns; c++){
        double VStartB = 0;
        // calcuate each columns in the sub matrix.
        for (cSub = j; cSub<columns; cSub++) {
            VStartB = 0;
            for(r = 0 ;r+i<rows; r++){
                VStartB+= *(v+r)*(*(A+(i+r)*rows+cSub));
            }
            for (rSub = 0; rSub+i<rows; rSub++) {
                *(A+(i+rSub)*rows+cSub) = *(A+(i+rSub)*rows+cSub)-(VStartB/VStartV2)*(*(v+rSub));
            }
             printfMatrix(A, rows, columns);
     //   }
        
       // printfMatrix(A, rows, columns);
        
    }
    
}

double * matrixCopy(double * origianMatrix, int rows, int columns){
    double * result = malloc(rows*columns*sizeof(double));
    int i = 0 , j = 0;
    for (i=0; i<rows; i++) {
        for (j=0; j<columns; j++) {
            *(result+i*rows+j) = *(origianMatrix+i* rows+j);
        }
    }
    return result;
}
void printfMatrix(double * matrix, int rows , int columns){
    int i = 0 ,j = 0;
    for (i = 0; i<rows; i++) {
        //printf("\n");
        for(j = 0;j<columns;j++){
            printf("%f ",*(matrix+i*rows+j));
        }
        printf("\n");
    }
}
void printfVector(double * vector, int length){
    int i =0;
    printf("\n");
    for (i= 0 ; i<length; i++) {
        printf("%f ",*(vector+i));
    }
    printf("\n");
}
