#include <stdio.h>
#include <stdlib.h> 
#define MAX_ITEMS 5 //the max items that we can take
#define MAX_WEIGHT 20

int maximum (int x, int y);  // all the functions - is not thake place for in the memory
int *create_matrix(int weights[], int values[],int selected_bool[]);
int* bag(int **matrix, int values[], int selected_bool[]);
int knapSack(int weights[], int values[], int selected_bool[]);

// if we send matrix to the knapSack we should call to the mat[MAX_ITEMS+1][MAX_WEIGHT+1] and this is also the mav value
int knapSack(int weights[], int values[], int selected_bool[]){  //in the loop move on all the items and if is selected bool 
   int maxV = 0;
    for (int i = 0; i < MAX_ITEMS; i++) 
    {
        if (selected_bool[i]) // if the items choce
        {
            maxV += values[i];  // colculate the max value in the bag 
        }
    }
    return maxV;
}

   
int maximum(int x, int y) { // find the max
    int arr[2] = {x, y}; // x and y in an array
    return arr[(x - y) >> 31 & 0x1]; // return the element at index 0 if x >= y, else return the element at index 1
}



int* create_matrix(int weights[], int values[], int selected_bool[]){

    int **create_matrix = (int**) malloc ((MAX_ITEMS+1)* sizeof(int*));  // make matrix 

    for (int i = 0; i < MAX_ITEMS+1; i++)
    {
        create_matrix[i] = (int*) malloc ((MAX_WEIGHT+1)* sizeof(int*));
    }

    for (int i =0; i<MAX_ITEMS+1; i++){

        for(int j =0; j<MAX_WEIGHT+1; j++){ 

            if (j < weights[i-1]) // if the weight in the matrix is less than the weight of the items
            {
                    create_matrix[i][j] = create_matrix[i-1][j]; // so i take the upper value 
            }

            else if (i == 0 || j==0) // if the row and colon is 0 so put there 0
            {
                create_matrix[i][j] = 0 ;
            }

            else 
            {
                create_matrix[i][j] = maximum (create_matrix[i-1][j] , (create_matrix[i-1][j-weights[i-1]]+values[i-1]) );// find the max of the value in the bag
            }
        }
    }

    int *Nselected = bag(create_matrix, values ,selected_bool);

    for (int i = 0; i < MAX_ITEMS + 1; ++i) { // free every pieace in the matrix

        free(create_matrix[i]);
    }

    free(create_matrix); 

    return Nselected;
}

// void printMat(int** mat ) {
//     printf("mattt: \n");
//     for (int i = 0; i < MAX_ITEMS + 1; i++)
//     {
//         for (int j = 0; j < MAX_ITEMS + 1; j++)
//         {
//             printf("%d ", mat[i][j]);
//         }
//         printf("\n");
//     }
// }


int* bag(int **matrix, int values[], int selected_bool[]){

    int val = matrix[MAX_ITEMS][MAX_WEIGHT]; // the max value
    
    for (int y = MAX_ITEMS; y > 0; y--)  // start from the left
    { 
        int s = 0; //false
        for (int w = 0; w < MAX_WEIGHT + 1; w++)
        {
            if (matrix[y-1][w] == val) // check if i need to take the item
            {
                s = 1;   // true
                break;
            }
        }

        if (s)  // infinity loop 
        {
            selected_bool[y-1] = 0;  
        }
        else
        {
            selected_bool[y-1] = 1; 
            val = val - values[y-1]; 
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

    
    int *Nselected = create_matrix(weights, values, selected_bool);  // call to the new selected
    // printf("fwe\n");
    // for (int i = 0; i < MAX_ITEMS; i++) {

    //     printf("%d", selected_bool[i]); // the itemts to results
    // }
    // printf("fwwfwre\n");
    int  maxValue = knapSack(weights, values, Nselected); // give me the max value
    
    printf("Maximum profit: %d\n", maxValue);   // give me tha max value
    printf("Selected items:");

    for (int j = 0; j < MAX_ITEMS; j++) {

        if (Nselected[j])   // if we take this items in the bags
        {
            printf(" %c", result[j]);
        } 
    }
    
    return 0;
}