#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LMat {
    struct LMat *right, *left, *down, *up; 
    int s;
} LMat;

LMat* createM(int value);
void packM(LMat* head, int std, int cls);
void printM(LMat* head);
void stprintM(LMat* head, int s);
void clprintM(LMat* head, int s);
void fprintM(LMat* head, FILE *fp);
void freeM(LMat* head);

int main() {
    LMat *root = (LMat *)malloc(sizeof(LMat));
    root->s = 0;
    root->right = NULL;
    root->left = NULL;
    root->down = NULL;
    root->up = NULL;
    
    
    
    packM(root,3,1);
    packM(root,4,9);
    packM(root,5,9);
    packM(root,5,200);
    // print matrix
    printM(root);
    // print to file
    FILE *fp = fopen("matrix.txt", "w");
    if (fp != NULL) {
        fprintM(root, fp);
        fclose(fp);
    }
    

    stprintM(root, 4);
    clprintM(root, 9);

    // free memory
    freeM(root);
    return 0;
}

// create a new element
LMat* createM(int value) {
    LMat* newNode = (LMat*)malloc(sizeof(LMat));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->s = value;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->down = NULL;
    newNode->up = NULL;
    return newNode;
}

// add a new column
void addColumn(LMat* head, int std) {
    LMat* current = head;
    while(current->right != NULL) current = current->right;

    LMat* baseNode = createM(std);
    current->right = baseNode;
    baseNode->left = current;
    

    while(current->down != NULL) {
        current = current->down;
        LMat* node = createM(0);
        baseNode->down = node;
        node->up = baseNode;
        node->left = current;
        current->right = node;
        baseNode = node;
    }
}

// add a new row
void addRow(LMat* head, int cls) {
    LMat* current = head;
    
    while(current->down != NULL) current = current->down;

    LMat* baseNode = createM(cls);
    current->down = baseNode;
    baseNode->up = current;
    
    while(current->right != NULL) {
        current = current->right;
        LMat* node = createM(0);
        baseNode->right = node;
        node->left = baseNode;
        node->up = current;
        current->down = node;
        baseNode = node;
    }
}

//Finds an address and writes to it
//If that address doesn't exsist expand then write
void packM(LMat* head, int std, int cls) {
    LMat* colM = head;
    //find or create Column
    
    
    while(colM != NULL) {
        if(colM->s == std) {
            break;
        }else if(colM->right == NULL) {
            addColumn(head, std);
            while(colM->s != std) colM = colM->right;
            break;
        }
        colM = colM->right;
    }
    
    
    // find or create row
    LMat* rowM = head;
    int row = 0;
    while(rowM != NULL) {
        row++;
        if(rowM->s == cls) {
            row--;
            break;
        }else if(rowM->down == NULL) {
            addRow(head, cls);
            while(rowM->s != cls) rowM = rowM->down;
            break;
        }
        rowM = rowM->down;
    }
    //assign the value 
    for(int i=0;i<row;i++){colM=colM->down;}
    colM->s=1;
    return;
}

// print all matrix
void printM(LMat* head) {
    LMat* rowStart = head;
    while(rowStart != NULL) {
        LMat* current = rowStart;
        while(current != NULL) {
            printf( "%d ", current->s);
            current = current->right;
        }
        printf("\n");
        rowStart = rowStart->down;
    }
}

// search for stn s and if taken print the class numbers 
void stprintM(LMat* head, int s) {
    LMat* rowStart = head;
    LMat* current = head;
    while (current != NULL) {
        if (current->s == s) {
            printf("StID %d: ", current->s);
            current=current->down;
            rowStart = rowStart->down;
            break;
        }
        current = current->right;
    }
    while (rowStart != NULL) {
        if(current->s > 0)
            printf("%d ",rowStart->s);
        current=current->down;
        rowStart = rowStart->down;
    }
    printf("\n");
}

// Search for cln s and if taken print the student numbers
void clprintM(LMat* head, int s) {
    LMat* colStart = head;
    LMat* current = head;
    while (current != NULL) {
        if (current->s == s) {
            printf("ClassID %d: ", current->s);
            current=current->right;
            colStart = colStart->right;
            break;
        }
        current = current->down;
    }
    while (colStart != NULL) {
        if(current->s > 0)
            printf("%d ",colStart->s);
        current=current->right;
        colStart = colStart->right;
    }
    printf("\n");
}

// Print matrix to file
void fprintM(LMat* head, FILE *fp) {
    LMat* rowStart = head;
    while(rowStart != NULL) {
        LMat* current = rowStart;
        while(current != NULL) {
            fprintf(fp, "%d ", current->s);
            current = current->right;
        }
        fprintf(fp, "\n");
        rowStart = rowStart->down;
    }
}

// Free matrix memory
void freeM(LMat* head) {
    LMat* rowStart = head;
    while(rowStart != NULL) {
        LMat* current = rowStart;
        LMat* nextRow = rowStart->down;
        
        while(current != NULL) {
            LMat* next = current->right;
            free(current);
            current = next;
        }
        
        rowStart = nextRow;
    }
}
