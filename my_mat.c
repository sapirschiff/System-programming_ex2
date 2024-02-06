#include <stdio.h>
#include "my_mat.h"
#define LENGTH 3

/*'A'*/
void getNumbers(int A[LENGTH][LENGTH]){

/*Receiving the input to the matrix*/	
	for(int i=0;i<LENGTH;i++){
		for(int j=0;j<LENGTH;j++){
			scanf(" %d",&A[i][j]);
		}
	}
/*Using dinamic programing with Floyd–Warshall_algorithm*/	
	for(int k=0;k<LENGTH;k++){
		for(int i=0;i<LENGTH;i++){
			for(int j=0;j<LENGTH;j++){
				if(i==j){
				}
				else if (A[i][k]==0 || A[k][j]==0){
				}
				else{
					if(A[i][j] == 0){
						A[i][j] = A[i][k]+A[k][j];
					}
					else if(A[i][j] > A[i][k]+A[k][j]){
						A[i][j] = A[i][k]+A[k][j];
					}
				}
			}
		}	
	}	
}
/*'B'*/
void isPath(int A [LENGTH][LENGTH],int i,int j){
	if (A[i][j]!=0){
		printf("True\n");
	}
	else{
		printf("False\n");
	}
}
/*'C'*/
void shortest(int A [LENGTH][LENGTH],int i,int j){
	if(A[i][j] == 0){
		printf("-1\n"); // IF THERE IS NOT A WAY
	}
	else{
	
		printf("%d\n",A[i][j]);
	}
}