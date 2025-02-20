#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
void fgetsM(LMat *root, const char *filename);
void freeM(LMat* head);


int main() {
    LMat *root = (LMat *)malloc(sizeof(LMat));
    root->s = 0;
    root->right = NULL;
    root->left = NULL;
    root->down = NULL;
    root->up = NULL;
    char c ='0';
    while(c!='q'){
        printf("\n_________________________\n");
        printf("| Register Student: m\n| Print Students Classes:s\n| Print Classes Roster:c\n| Print Matrix:p\n| Read from File:r\n| Save to file:f\n| Quit:q");
        printf("\n|________________________\n");
        printf("Enter a Command... ");
        int catch = scanf(" %c",&c);
        if (catch != 1) {
            printf("Error reading character.\n");
            break; 
        }

        switch(c){
            case 'm':{
                //set or create value
                int st;
                int cl;
                printf("Enter Student Number... ");
                catch = scanf("%d",&st);
                printf("Enter Class Number for Registration... ");
                int throw = scanf("%d",&cl);
                if((catch==1)&&(throw==1))
                    packM(root,st,cl);
                else printf("Not a Valid Input\n");
                break;
            }
            case 'p':
                // print matrix
                printM(root);
                break;
            case 'f':{
                // print to file
                FILE *fp = fopen("matrix.txt", "w");
                if (fp != NULL) {
                    fprintM(root, fp);
                    fclose(fp);
                }
                break;
            }
            case 's':{
                int st;
                //print a students class list
                printf("Enter Student Number... ");
                int throw = scanf("%d",&st);
                if(throw==1)
                    stprintM(root, st);
                else printf("Not a Valid Input\n");
                break;
            }
            case 'c':{
                //print a classes student list
                int cl;
                printf("Enter Class Number... ");
                int throw = scanf("%d",&cl);
                if(throw==1)
                    clprintM(root, cl);
                else printf("Not a Valid Input\n");
                break;
            }
            case 'r':{
                fgetsM(root, "input.txt");
                break;
            }
            default:
                break;
        }
    }
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
// test function to verify the matrix
void printM(LMat* head) {
    LMat* rowStart = head;
    while(rowStart != NULL) {
        LMat* current = rowStart;
        while(current != NULL) {
            printf( "%d\t", current->s);
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
    while (current->right != NULL) {
        if (current->s == s) {
            printf("\nStudent ID %d:", current->s);
            current=current->down;
            rowStart = rowStart->down;
            break;
        }
        current = current->right;
    }
    printf("\nClasses: ");
    while (rowStart != NULL) {
        if(current->s > 0)
            printf("%d ",rowStart->s);
        current=current->down;
        rowStart = rowStart->down;
    }
    printf("\n");
    return;
}

// Search for cln s and if taken print the student numbers
void clprintM(LMat* head, int s) {
    LMat* colStart = head;
    LMat* current = head;
    while (current->down != NULL) {
        if (current->s == s) {
            printf("\nClass ID %d:", current->s);
            current=current->right;
            colStart = colStart->right;
            break;
        }
        current = current->down;
    }
    printf("\nStudents: ");
    while (colStart != NULL) {
        if(current->s > 0)
            printf("%d ",colStart->s);
        current=current->right;
        colStart = colStart->right;
    }
    printf("\n");
    return;
}

// Print matrix to file
void fprintM(LMat* head, FILE *fp) {
    LMat* rowStart = head;
    LMat* current = rowStart;
    current=current->right;
    rowStart = rowStart->down;
    while(rowStart != NULL) {
        fprintf(fp,"%d ", current->s);
        current=current->down;
        while (rowStart != NULL) {
            if(current->s > 0)
                fprintf(fp,"%d ",rowStart->s);
            current=current->down;
            rowStart = rowStart->down;
        }
        fprintf(fp, "\n");
        rowStart = rowStart->down;
    }
}

//Reads st,cl,cl,cl from a file 
void fgetsM(LMat *root, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        // Remove newline if present
        line[strcspn(line, "\n")] = 0;
        
        char *token = strtok(line, ",");
        if (token == NULL) continue;
        
        // First token is the student number
        int student = atoi(token);
        
        // Remaining tokens are class numbers
        while ((token = strtok(NULL, ",")) != NULL) {
            int class = atoi(token);
            if (student > 0 && class > 0) {
                packM(root, student, class);
            }
        }
    }
    
    fclose(fp);
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
