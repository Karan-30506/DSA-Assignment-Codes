#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Element {
    int rowid;
    int colid;
    int value;
}Element;

typedef struct SparseMatrix {
    int rows; // total rows of original input matrix
    int cols; // total columns of original input matirx
    int nz; // No of non-zero Elements
    Element elements[MAX];
} SpMat;

void getOriginalMatrix(SpMat *sp){
    int k = 0;
    for(int i = 0; i < sp->rows; i++){
        for(int j = 0; j < sp->cols; j++){
            if(i == sp->elements[k].rowid && j == sp->elements[k].colid){
                printf(" %d\t ", sp->elements[k].value);
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

// Inserts Elements in the Empty Sparse Matrix Representation
void giveSparseRep(SpMat *spmat) {
    int ROWID = -1, COLID = -1, VALUE = 0;

    printf("Insert Elements in the Format:\n");
    printf("RowID    ColID    Value\n");

    for(int k = 0; k < spmat->nz; k++){
        scanf("%d", &ROWID);
        if(ROWID < 0 || ROWID >= spmat->rows){
            printf("Invalid Input\n");
            exit(1);
        }
        spmat->elements[k].rowid = ROWID;

        scanf("%d", &COLID);
        if(COLID < 0 || COLID >= spmat->cols){
            printf("Invalid Input\n");
            exit(1);
        }
        spmat->elements[k].colid = COLID;

        scanf("%d", &VALUE);
        if(VALUE == 0){
            printf("Invalid Input\n");
            exit(1);
        }
        spmat->elements[k].value = VALUE;
    }
}

void sortSparseRep(SpMat *spm){
    Element temp;
    for(int i = 0; i < spm->nz - 1; i++){
        for(int j = 0; j < spm->nz - i - 1; j++){
            if(spm->elements[j].rowid > spm->elements[j+1].rowid){
                // swap
                temp = spm->elements[j];
                spm->elements[j] = spm->elements[j+1];
                spm->elements[j+1] = temp;
            }
            else if(spm->elements[j].rowid == spm->elements[j+1].rowid){
                if(spm->elements[j].colid > spm->elements[j+1].colid){
                    // swap
                    temp = spm->elements[j];
                    spm->elements[j] = spm->elements[j+1];
                    spm->elements[j+1] = temp;
                }
            }
        }
    }
}

// Prints Sparse Matrix representation
void printSparseRep(SpMat *spmat){
    printf("Rows    Cols    Value\n");
    for(int i = 0; i < spmat->nz; i++){
        printf(" %d\t %d\t  %d\n", spmat->elements[i].rowid, spmat->elements[i].colid, spmat->elements[i].value);
    }
    printf("---------------------\n");
}

void giveTranspose(SpMat *spmat, SpMat *transpm) {
    int k = 0;
    transpm->cols = spmat->rows;
    transpm->rows = spmat->cols;
    transpm->nz = spmat->nz;
    for(int i = 0; i < spmat->cols; i++){
        for(int j = 0; j < spmat->nz; j++){
            if(spmat->elements[j].colid == i){
                transpm->elements[k].rowid = spmat->elements[j].colid;
                transpm->elements[k].colid = spmat->elements[j].rowid;
                transpm->elements[k].value = spmat->elements[j].value;
                k++;
            }
        }
    }
}

int addSparseMatrices(SpMat *spmat1, SpMat *spmat2, SpMat *result){
    int i = 0, j = 0, k = 0;
    if(spmat1->rows != spmat2->rows || spmat1->cols != spmat2->cols){
        printf("Rows and Columns of Matrices do not Match\nCannot perform Addition of the Matrices\n");
        return -1;
    }

    result->rows = spmat1->rows;
    result->cols = spmat1->cols;

    while(i < spmat1->nz && j < spmat2->nz){
        if(spmat1->elements[i].rowid == spmat2->elements[j].rowid){
            if(spmat1->elements[i].colid == spmat2->elements[j].colid){
                int sum = spmat1->elements[i].value + spmat2->elements[j].value;
                if(sum != 0){
                    result->elements[k].rowid = spmat1->elements[i].rowid;
                    result->elements[k].colid = spmat1->elements[i].colid;
                    result->elements[k].value = sum;
                    k++;
                }
                i++;
                j++;
            }
            else if(spmat1->elements[i].colid < spmat2->elements[j].colid){
                result->elements[k] = spmat1->elements[i];
                k++;
                i++;
            }
            else {
                result->elements[k] = spmat2->elements[j];
                k++;
                j++;
            }
        }
        else{
            if(spmat1->elements[i].rowid < spmat2->elements[j].rowid){
                result->elements[k] = spmat1->elements[i];
                k++;
                i++;
            }
            else {
                result->elements[k] = spmat2->elements[j];
                k++;
                j++;
            }
        }
    }

    // for leftover elements in Sparse Matrix 1
    while(i < spmat1->nz){
        result->elements[k].rowid = spmat1->elements[i].rowid;
        result->elements[k].colid = spmat1->elements[i].colid;
        result->elements[k].value = spmat1->elements[i].value;
        k++;
        i++;
    }
    
    // for leftover elements in Sparse Matrix 2
    while(j < spmat2->nz){
        result->elements[k].rowid = spmat2->elements[j].rowid;
        result->elements[k].colid = spmat2->elements[j].colid;
        result->elements[k].value = spmat2->elements[j].value;
        k++;
        j++;
    }
    
    return k;
}

// Performs all the Matrix Operations
void performMatrixOperations(){
    SpMat spMat1, spMat2;
    SpMat trsp1, trsp2;
    SpMat result;

    // Sparse matrix 1
    printf("Enter Rows of Matrix 1: ");
    scanf("%d", &spMat1.rows);
    printf("Enter Columns of Matrix 1: ");
    scanf("%d", &spMat1.cols);
    printf("Enter Number of Non-Zero Elements in Matrix 1: ");
    scanf("%d", &spMat1.nz);
    giveSparseRep(&spMat1);
    printf("---------------------\n");
    printf("   Sparse Matrix 1\n");
    printf("---------------------\n");
    printSparseRep(&spMat1);

    // Sparse Matrix 2
    printf("Enter Rows of Matrix 2: ");
    scanf("%d", &spMat2.rows);
    printf("Enter Columns of Matrix 2: ");
    scanf("%d", &spMat2.cols);
    printf("Enter Number of Non-Zero Elements in Matrix 2: ");
    scanf("%d", &spMat2.nz);
    giveSparseRep(&spMat2);
    printf("---------------------\n");
    printf("   Sparse Matrix 2\n");
    printf("---------------------\n");
    printSparseRep(&spMat2);

    // Sorted Sparse Matrix 1
    sortSparseRep(&spMat1);
    printf("----------------------\n");
    printf("Sorted Sparse Matrix 1\n");
    printf("----------------------\n");
    printSparseRep(&spMat1);
    printf("----------------------\n");
    printf("       Matrix 1\n");
    printf("----------------------\n");
    getOriginalMatrix(&spMat1);

    // Sorted Sparse Matrix 2
    sortSparseRep(&spMat2);
    printf("----------------------\n");
    printf("Sorted Sparse Matrix 2\n");
    printf("----------------------\n");
    printSparseRep(&spMat2);
    printf("----------------------\n");
    printf("      Matrix 2\n");
    printf("----------------------\n");
    getOriginalMatrix(&spMat2);

    // Transpose of sparse matrix 1
    giveTranspose(&spMat1, &trsp1);
    printf("---------------------\n");
    printf("Transpose of Matrix 1\n");
    printf("---------------------\n");
    printSparseRep(&trsp1);
    printf("----------------------\n");
    printf("  Transpose Matrix 1\n");
    printf("----------------------\n");
    getOriginalMatrix(&trsp1);

    // Transpose of sparse matrix 2
    giveTranspose(&spMat2, &trsp2);
    printf("---------------------\n");
    printf("Transpose of Matrix 2\n");
    printf("---------------------\n");
    printSparseRep(&trsp2);
    printf("----------------------\n");
    printf("  Transpose Matrix 2\n");
    printf("----------------------\n");
    getOriginalMatrix(&trsp2);

    // Addition of both the sparse matrices
    result.nz = addSparseMatrices(&spMat1, &spMat2, &result);
    if(result.nz == -1)
        return;
    printf("---------------------------\n");
    printf("Addition of Sparse Matrices\n");
    printf("---------------------------\n");
    printSparseRep(&result);
    printf("----------------------\n");
    printf(" Addition of Matrices \n");
    printf("----------------------\n");
    getOriginalMatrix(&result);
}

int main(){

    // Performs all Matrix Operations on the Sparse Matrix
    performMatrixOperations();
 
    return 0;
}