#include <stdio.h>
#include <stdlib.h> 
#define MAX_ITEMS 5
#define MAX_WEIGHT 20

int maximum (int x, int y);  // all the functions 
int *create_matrix(int weights[], int values[],int selected_bool[]);
int* bag(int **matrix, int values[], int selected_bool[]);
int knapSack(int weights[], int values[], int selected_bool[]);


int knapSack(int weights[], int values[], int selected_bool[]){  //in the loop move on all the items and if is selected bool 
   int maxV = 0;
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        if (selected_bool[i]) // if the items choce
        {
            maxV = maxV + values[i];  // colculate the max value in the bag 
        }
    }
    return maxV;
}

   
int maximum (int x, int y){ // find the maximum
    if (x >= y){
        return x; 
    }
    else{
        return y;
    }
}

// int *create_matrix(int weights[], int values[], int selected_bool[]){

//     int **create_matrix = (int**) malloc ((MAX_WEIGHT+1)* sizeof(int*));  // make matrix 

//     for (int i = 0; i < MAX_WEIGHT+1; i++)
//     {
//         create_matrix[i] = (int*) malloc (MAX_ITEMS* sizeof(int*));
//     }

//     for (int i =0; i<MAX_ITEMS+1; i++){
//         for(int j =0; j<MAX_WEIGHT+1; j++){ // if the row and colon is 0 so put there 0

//             if (i == 0 || j==0){
//                 create_matrix[i][j] = 0 ;
//             }

//             else 
//             {
//                 create_matrix[i][j] = maximum (create_matrix[i-1][j] , (create_matrix[i-1][j-weights[i-1]]+values[i-1]) );// find the max
//             }
//         }
//     }

//     int *Nselected = bag(create_matrix, values ,selected_bool);

//     // Free allocated memory for the matrix
//     for (int i = 0; i < MAX_ITEMS + 1; ++i) {
//         free(create_matrix[i]);
//     }
//     free(create_matrix); // free

//     return Nselected;
// }
int *create_matrix(int weights[], int values[], int selected_bool[]){
    int **create_matrix = (int**) malloc ((MAX_ITEMS + 1) * sizeof(int*));  // make matrix 

    for (int i = 0; i < MAX_ITEMS + 1; i++)
    {
        create_matrix[i] = (int*) malloc ((MAX_WEIGHT + 1) * sizeof(int));
    }

    for (int i = 0; i < MAX_ITEMS + 1; i++){
        for(int j = 0; j < MAX_WEIGHT + 1; j++){ // if the row and colon is 0 so put there 0

            if (i == 0 || j==0){
                create_matrix[i][j] = 0 ;
            }

            else 
            {
                create_matrix[i][j] = maximum (create_matrix[i-1][j] , (create_matrix[i-1][j-weights[i-1]]+values[i-1]) );// find the max
            }
        }
    }

    int *Nselected = bag(create_matrix, values ,selected_bool);

    // Free allocated memory for the matrix
    for (int i = 0; i < MAX_ITEMS + 1; ++i) {
        free(create_matrix[i]);
    }
    free(create_matrix); // free

    return Nselected;
}

int* bag(int **matrix, int values[], int selected_bool[]){

    int val = matrix[MAX_ITEMS][MAX_WEIGHT]; // the max value
    
    for (int y = MAX_ITEMS; y > 0; y--)  // start from the left
    { 
        int s = 0;
        for (int w = 0; w < MAX_WEIGHT + 1; w++)
        {
            if (matrix[y-1][w] == val)
            {
                s = 1;  //true meaning that there is the same weight in the row above
                break;
            }
        }

        if (s)  // infinity loop 
        {
            selected_bool[y-1] = 0;  // y-1 in the list = y in the matrix
        }
        else
        {
            selected_bool[y-1] = 1;  // Add true to list
            val = val - values[y-1];  // Update the value
        }
    }
    return selected_bool;
}

int main(){
    char result [MAX_ITEMS];
    int weights [MAX_ITEMS];
    int values [MAX_ITEMS];
    int selected_bool [MAX_ITEMS];

     for (int i = 0; i < MAX_ITEMS; i++) {

        scanf(" %c", &result[i]); // the itemts to results
        scanf(" %d", &values[i]); // the value of th items
        scanf(" %d", &weights[i]); // the weights of the items
    }

    
    int  maxValue = knapSack(weights, values, selected_bool);
    int *Nselected = create_matrix(weights, values, selected_bool);  // call to the new selected

    // Print
    printf("Maximum profit: %d\n", maxValue);   // the print
    printf("Selected items:");

    for (int j = 0; j < MAX_ITEMS; j++) {

        if (Nselected[j])   // When true print item
        {
            printf(" %c", result[j]);
        } 
    }
    
    return 0;
}