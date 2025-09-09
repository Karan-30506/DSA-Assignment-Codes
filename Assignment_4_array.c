#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// Display Original Matrix
void getOriginalMatrix(int spMat[][3], int rows, int cols, int nz){
    int k = 0;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(i == spMat[k][0] && j == spMat[k][1]){
                printf(" %d\t ", spMat[k][2]);
                k++;
            }
            else {
                printf(" %d\t ", 0);
            }
        }
        printf("\n");
    }
    printf("---------------------\n");
}

// Inserts Elements in the empty sparse matrix representation
void giveSparseRep(int rows, int cols, int repr[][3], int nz){
    int rowid = -1, colid = -1, value = 0;

    printf("Insert Elements in the Format:\n");
    printf("RowID    ColID    Value\n");

    for(int k = 0; k < nz; k++){
        scanf("%d", &rowid);
        if(rowid < 0 || rowid >= rows){
            printf("Invalid Input\n");
                exit(1);
        }
        repr[k][0] = rowid;

        scanf("%d", &colid);
        if(colid < 0 || colid >= cols){
            printf("Invalid Input\n");
                exit(1);
        }
        repr[k][1] = colid;

        scanf("%d", &value);
        if(value == 0){
            printf("Invalid Input\n");
                exit(1);
        }
        repr[k][2] = value;
    }
}

void sortSparseRep(int repr[][3], int nz){
    int temp;

    for(int i = 0; i < nz - 1; i++){
        for(int j = 0; j < nz - i - 1; j++){
            // Condition if Rowid is greater
            if(repr[j][0] > repr[j+1][0]){
                // swap
                for(int k = 0; k < 3; k++){
                    temp = repr[j][k];
                    repr[j][k] = repr[j+1][k];
                    repr[j+1][k] = temp;
                }
            }
            // Condition if Row index is <= and colId is greater
            else if(repr[j][0] == repr[j+1][0]){
                if(repr[j][1] > repr[j+1][1])
                // swap
                for(int k = 0; k < 3; k++){
                    temp = repr[j][k];
                    repr[j][k] = repr[j+1][k];
                    repr[j+1][k] = temp;
                }
            }
        }
    }
}

// Prints the sparse matrix representation
void printSparseRep(int mat[][3], int nz){
    printf("Rows    Cols    Value\n");
    for(int i = 0; i < nz; i++){
        printf(" %d\t %d\t  %d\n", mat[i][0], mat[i][1], mat[i][2]);
    }
    printf("---------------------\n");
}

void giveTranspose(int spmat[][3], int nz, int trans[][3], int cols){
    int k = 0;
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < nz; j++){
            if(spmat[j][1] == i){
                trans[k][0] = spmat[j][1];
                trans[k][1] = spmat[j][0];
                trans[k][2] = spmat[j][2];
                k++;
            }
        }
    }
}

int addSparseMatrices(int spMat1[][3], int rows1, int cols1, int nz1, int spMat2[][3], int rows2, int cols2, int nz2, int result[][3]){

    if(rows1 != rows2 || cols1 != cols2){
        printf("Rows and Columns of Matrices do not Match\nCannot perform Addition of the Matrices\n");
        return -1;
    }

    int i = 0, j = 0, k = 0;

    while(i < nz1 && j < nz2){

        if(spMat1[i][0] == spMat2[j][0]){
            if(spMat1[i][1] == spMat2[j][1]){
                int sum = spMat1[i][2] + spMat2[j][2];
                if(sum != 0){
                    result[k][0] = spMat1[i][0];
                    result[k][1] = spMat1[i][1];
                    result[k][2] = sum;
                    k++;
                }
                i++;
                j++;
            }
            else if(spMat1[i][1] < spMat2[j][1]){
                result[k][0] = spMat1[i][0];
                result[k][1] = spMat1[i][1];
                result[k][2] = spMat1[i][2];
                k++;
                i++;
            }
            else {
                result[k][0] = spMat2[j][0];
                result[k][1] = spMat2[j][1];
                result[k][2] = spMat2[j][2];
                k++;
                j++;
            }
        }
        else{
            if(spMat1[i][0] < spMat2[j][0]){
                result[k][0] = spMat1[i][0];
                result[k][1] = spMat1[i][1];
                result[k][2] = spMat1[i][2];
                k++;
                i++;
            }
            else{
                result[k][0] = spMat2[j][0];
                result[k][1] = spMat2[j][1];
                result[k][2] = spMat2[j][2];
                k++;
                j++;
            }
        }
    }

    // if spMat1 was leftover
    while(i < nz1){
        result[k][0] = spMat1[i][0];
        result[k][1] = spMat1[i][1];
        result[k][2] = spMat1[i][2];
        k++;
        i++;
    }

    // if spMat2 was leftover
    while(j < nz2){
        result[k][0] = spMat2[j][0];
        result[k][1] = spMat2[j][1];
        result[k][2] = spMat2[j][2];
        k++;
        j++;
    }
    return k;
}

// Performs the sparse matrix operations
void performMatrixOperations(int rows1, int cols1, int rows2, int cols2){
    // Initializing Empty Sparse Matrices
    int spMat1[MAX][3], spMat2[MAX][3];
    int trsp1[MAX][3], trsp2[MAX][3];
    int result[MAX][3];
    int nz1 = 0, nz2 = 0, totalnz = 0;

    // Sparse Matrix 1
    printf("Enter the Number of Non-Zero Elements in Matrix 1: ");
    scanf("%d", &nz1);
    giveSparseRep(rows1, cols1, spMat1, nz1);
    printf("---------------------\n");
    printf("   Sparse Matrix 1\n");
    printf("---------------------\n");
    printSparseRep(spMat1, nz1);
    printf("---------------------\n");
    
    // Sparse Matrix 2
    printf("Enter the Number of Non-Zero Elements in Matrix 2: ");
    scanf("%d", &nz2);
    giveSparseRep(rows2, cols2, spMat2, nz2);
    printf("---------------------\n");
    printf("   Sparse Matrix 2\n");
    printf("---------------------\n");
    printSparseRep(spMat2, nz2);

    // Sorted Sparse Matrix 1
    sortSparseRep(spMat1, nz1);
    printf("----------------------\n");
    printf("Sorted Sparse Matrix 1\n");
    printf("----------------------\n");
    printSparseRep(spMat1, nz1);
    printf("----------------------\n");
    printf("   Original Matrix 1\n");
    printf("----------------------\n");
    getOriginalMatrix(spMat1, rows1, cols1, nz1);


    // Sorted Sparse Matrix 2
    sortSparseRep(spMat2, nz2);
    printf("----------------------\n");
    printf("Sorted Sparse Matrix 2\n");
    printf("----------------------\n");
    printSparseRep(spMat2, nz2);
    printf("----------------------\n");
    printf("   Original Matrix 2\n");
    printf("----------------------\n");
    getOriginalMatrix(spMat2, rows2, cols2, nz2);

    // Transpose of Sparse Matrix 1's Representation
    giveTranspose(spMat1, nz1, trsp1, cols1);
    printf("---------------------\n");
    printf("Transpose of Matrix 1\n");
    printf("---------------------\n");
    printSparseRep(trsp1, nz1);
    printf("----------------------\n");
    printf("   Transpose Matrix 1\n");
    printf("----------------------\n");
    getOriginalMatrix(trsp1, rows1, cols1, nz1);

    // Transpose of Sparse Matrix 2's Representation
    giveTranspose(spMat2, nz2, trsp2, cols2);
    printf("---------------------\n");
    printf("Transpose of Matrix 2\n");
    printf("---------------------\n");
    printSparseRep(trsp2, nz2);
    printf("----------------------\n");
    printf("   Transpose Matrix 2\n");
    printf("----------------------\n");
    getOriginalMatrix(trsp2, rows2, cols2, nz2);

    // Addition of Two Sparse Matrix Representations
    totalnz = addSparseMatrices(spMat1, rows1, cols1, nz1, spMat2, rows2, cols2, nz2, result);
    if(totalnz == -1)
        return;
    printf("---------------------------\n");
    printf("Addition of Sparse Matrices\n");
    printf("---------------------------\n");
    printSparseRep(result, totalnz);
    printf("----------------------\n");
    printf(" Addition of Matrices\n");
    printf("----------------------\n");
    getOriginalMatrix(result, rows1, cols1, totalnz);

}

int main() {
    int rows1, cols1, rows2, cols2;

    printf("Enter Rows of Matrix 1: ");
    scanf("%d", &rows1);
    printf("Enter Columns of Matrix 1: ");
    scanf("%d", &cols1);

    printf("Enter Rows of Matrix 2: ");
    scanf("%d", &rows2);
    printf("Enter Columns of Matrix 2: ");
    scanf("%d", &cols2);

    performMatrixOperations(rows1, cols1, rows2, cols2);
 
    return 0;

}