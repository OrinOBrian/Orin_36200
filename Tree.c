#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Tree {
    struct Tree *right, *left; 
    int s;
} Tree;

void PrintT(Tree *,char*, bool);
Tree* InsertT(Tree *,int);
Tree* rotateL(Tree *);
Tree* rotateR(Tree *);
void FreeT(Tree *);
int HeightT(Tree *);
void PreeT(Tree * head);
void fprintT(Tree *,FILE *);



void main(int ac,char* av[]){ 
    Tree* root=NULL; 
    
    char c='0';
    //Fills the Tree with the Test Values when there are no added flags
    if(ac==1){
        int l[]= {7,36,30,3,11,44,5,32,20,24,19,54,17,33,31,34,13,64,18,27,12,29,74,35,15,4,40,84,39,28,1,23,22,94,26,8,14,9,25,104,10,21,43,37,16,57,38,66,6,2};
        for(int i=0; i<50;i++){
            root = InsertT(root,l[i]);
            PreeT(root);
            printf(" %d\n",ac);
        }
    }
    while(c!='q'){
        printf("\no________--OWO--________o\n|\t OPTIONS \t|\n");
        printf("|\tInsert:\t'i'\t|\n|\tPrint:\t'p'\t|\n|\tQuit:\t'q'\t|");
        printf("\nb-----------------------d\n");
        printf("Enter a Command... ");

        /*
        o______________------OWO------______________o
        |                   *TIP*                   |
        |     Scanf is a queue, so if you write     |
        |     i12i13i14 when entering a command     |
        |     it inserts in the order you wrote.    |
        |     This makes inserting less tedious     |
        |                              -ORIN        |
        b-------------------------------------------d
        */

        int catch = scanf(" %c",&c);
        if (catch != 1) {
            printf("Error reading character.\n");
            break; 
        }

        switch(c){
            case 'i':{
                //set or create value
                int val;
                int throw = scanf("%d",&val);
                if((throw==1))
                    root = (Tree *)InsertT(root,val);
                else printf("Not a Valid Input\n");
                break;
            }
            case 'p':
                // print Tree
                PrintT(root,"",0);
                break;
            case 'f':{
                char fn[50];
                int throw = scanf(" %s",&fn);
                
                FILE *fp = fopen(fn, "w");
                if (fp == NULL) {
                    printf("Error opening file\n");
                    return;
                }
                if(throw==1)
                    fprintT(root,fp);
                else printf("Not a Valid Input\n");
                
                fclose(fp);
                break;
            }
            default:
                break;
        }
    }
    // free memory
    FreeT(root);
}

void FreeT(Tree * head){
    if(head==NULL){
        return;
    }
    FreeT(head->left);
    FreeT(head->right);
    free(head);
}
void PreeT(Tree * head){
    //Fast print that prints elements from the left to the right starting with Roots
    if(head==NULL){
        return;
    }
    printf("%d ", head->s);
    
    PreeT(head->left);
    PreeT(head->right);
}
void PrintT(Tree * head,char* pipe, bool lft){
    if(head==NULL)return;
    //Use String Manipulation
    printf("%s", pipe);
    printf(lft ? "|--" : "'--");
    printf("%d\n", head->s);
    char npipe[1024];
    strcpy(npipe, pipe);
    strcat(npipe, lft ? "|   " : "    ");
    //similar to FreeT
    PrintT(head->left,npipe,true);
    PrintT(head->right,npipe,false);
}

int HeightT(Tree *head) {
    if (head == NULL) {
        return 0;
    }
    int left = HeightT(head->left);
    int right = HeightT(head->right);
    return (left > right ? left : right) + 1;
}
struct Tree* rotateL(struct Tree* y) {
    struct Tree* x = y->right;
    struct Tree* T2 = x->left;
  
    x->left = y;
    y->right = T2;
    return x;
  }
struct Tree* rotateR(struct Tree* y) {
    struct Tree* x = y->left;
    struct Tree* T2 = x->right;
  
    x->right = y;
    y->left = T2;
    return x;
  }
  Tree* InsertT(Tree *root, int value) {
    // If tree is empty, create new node
    if (root == NULL) {
        Tree* newNode = (Tree*)malloc(sizeof(Tree));
        newNode->s = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    
    // Structural Comment
    if (value < root->s) {
        root->left = InsertT(root->left, value);
    } else if (value > root->s) {
        root->right = InsertT(root->right, value);
    } else {
        return root;
    }
    
    int balanceFactor = HeightT(root->left) - HeightT(root->right);
    
    // Left Cases
    if (balanceFactor > 1) {
        // Left-Right Case
        if (value > root->left->s) {
            root->left = rotateL(root->left);
            return rotateR(root);
        }
        // Left-Left Case
        return rotateR(root);
    }
    
    // Right Cases
    if (balanceFactor < -1) {
        // Right-Left Case
        if (value < root->right->s) {
            root->right = rotateR(root->right);
            return rotateL(root);
        }
        // Right-Right Case
        return rotateL(root);
    }
    
    return root;
}
void fprintT(Tree *root, FILE *fp) {
    if(root==NULL){
        return;
    }
    fprintf(fp,"%d,",root->s);
    fprintT(root->left,fp);
    fprintT(root->right,fp);
}
