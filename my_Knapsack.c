#include <stdio.h>
#include <stdlib.h> 
#define MAX_ITEMS 5
#define MAX_WEIGHT 20

int maximum (int x, int y);  // all the functions 
int *create_matrix(int weights[], int values[],int selected_bool[]);
int* Items_in_bag(int **matrix, int values[], int selected_bool[]);
int knapSack(int weights[], int values[], int selected_bool[]);


int knapSack(int weights[], int values[], int selected_bool[]){  //in the loop move on all the items and if is selected bool 
   int maxV = 0;
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        if (selected_bool[i])
        {
            maxV = maxV + values[i];
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

int *create_matrix(int weights[], int values[], int selected_bool[]){
    int **create_matrix = (int**) malloc ((MAX_WEIGHT+1)* sizeof(int*));  // make matrix 

    for (int i = 0; i < MAX_WEIGHT+1; i++)
    {
        create_matrix[i] = (int*) malloc (MAX_ITEMS* sizeof(int*));
    }

    for (int i =0; i<MAX_ITEMS+1; i++){
        for(int j =0; j<MAX_WEIGHT+1; j++){ // if the row and colon is 0 so put there 0

            if (i == 0 || j==0){
                create_matrix[i][j] = 0 ;
            }

            else 
            {
                create_matrix[i][j] = maximum (create_matrix[i-1][j] , (create_matrix[i-1][j-weights[i-1]]+values[i-1]) );// find the max
            }
        }
    }

    int *new_selected_bool = Items_in_bag(create_matrix, values ,selected_bool);

    // Free allocated memory for the matrix
    for (int i = 0; i < MAX_ITEMS + 1; ++i) {
        free(create_matrix[i]);
    }
    free(create_matrix); // free

    return new_selected_bool;
}

int* Items_in_bag(int **matrix, int values[], int selected_bool[]){

    int Current_val = matrix[MAX_ITEMS][MAX_WEIGHT]; // the max value
    
    for (int y = MAX_ITEMS; y > 0; y--)  // start from the left
    {
        int b = 0;
        for (int i = 0; i < MAX_WEIGHT + 1; i++)
        {
            if (matrix[y-1][i] == Current_val)
            {
                b = 1;  //true meaning that there is the same weight in the row above
                break;
            }
        }

        if (b)  // infinity loop 
        {
            selected_bool[y-1] = 0;  // y-1 in the list = y in the matrix
        }
        else
        {
            selected_bool[y-1] = 1;  // Add true to list
            Current_val = Current_val - values[y-1];  // Update the value
        }
    }
    return selected_bool;
}

int main(){
    char result [MAX_ITEMS];
    int weights [MAX_ITEMS];
    int values [MAX_ITEMS];
    int selected_bool [MAX_ITEMS];

    for (int i =0; i<MAX_ITEMS; i++){
        printf ("the type of the weight %c :", 'A'+i);
        scanf("%d", &weights[i]);

        printf ("the type of the value %c :", 'A'+i);
        scanf("%d" , &values[i]);

    }
    
    int  maxValue = knapSack(weights, values, selected_bool);
    int *new_selected_bool = create_matrix(weights, values, selected_bool);  // Stores the selected bool which determins which items to take

    // Add the items to the result list
    int x = 0;
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        if (new_selected_bool[i])   // When true add the item
        {
            result[x] = 'A' + i;     // i + 65 = {A,B,C,D,....}
            x++;
        } 
    }

    // Print
    printf("Maximum profit: %d\n", maxValue);   // the print
    printf("Selected items: ");

    for (int j = 0; j < x; j++) {
        printf("%c", result[j]);
    }

    return 0;
}