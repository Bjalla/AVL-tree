#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


struct node {
    int value;
    int level;
    int status;

    struct node *nextL;
    struct node *nextR;
    struct node *previous;
};

struct node *rootFirst;



struct node *balanceTreeLL(struct node *root) {
    struct node *new_root = root->nextL;
    root->nextL = new_root->nextR;
    new_root->nextR = root;

    new_root->nextR->nextL->previous = new_root->nextR;
    new_root->previous = new_root->nextR->previous;
    new_root->nextR->previous = new_root;

    int temp;
    temp = new_root->level;
    new_root->level = new_root->nextR->level;
    new_root->nextR->level = temp;

    temp = new_root->status;
    new_root->status = new_root->nextR->status;
    new_root->nextR->status = temp;
    return new_root;
}


struct node *balanceTreeRR(struct node *root) {
    struct node *new_root = root->nextR;
    root->nextR = new_root->nextL;
    new_root->nextL = root;

    new_root->nextL->nextR->previous = new_root->nextL;
    new_root->previous = new_root->nextL->previous;
    new_root->nextL->previous = new_root;

    int temp;
    temp = new_root->level;
    new_root->level = new_root->nextL->level;
    new_root->nextL->level = temp;

    temp = new_root->status;
    new_root->status = new_root->nextL->status;
    new_root->nextL->status = temp;
    return new_root;
}

int maxDepth(struct node *root) {
    if (root == NULL) {
        return 0;
    } else {
        /* find the depth of each subtree */
        int lDepth = maxDepth(root->nextL);
        int rDepth = maxDepth(root->nextR);

        /* use the larger one */
        if (lDepth > rDepth)
            return(lDepth+1);
        else return(rDepth+1);
    }
}




// level adjustment
void levelHandler(struct node *prev) {

    if (prev != NULL) {
        if (prev->nextL != NULL && prev->nextR != NULL) {
            if (prev->nextL->level > prev->nextR->level) {
                prev->level = prev->nextL->level + 1;
            } else {
                prev->level = prev->nextR->level + 1;
            }
            prev->status = prev->nextR->level - prev->nextL->level;
        } else if (prev->nextR == NULL && prev->nextL != NULL) {
            printf("Level %d\n", prev->value);
            prev->level =
                    prev->nextL->level + 1;
            prev->status = prev->nextL->level * (-1);
        } else if (prev->nextL == NULL && prev->nextR != NULL){
            prev->level = prev->nextR->level + 1;
            prev->status = prev->nextR->level * (-1);
        }



        levelHandler(prev->previous);
    }



    // return;
    /* struct node *cont;
    struct node *current;
    if (new->previous != NULL) {
        cont = new->previous;
        if (cont->nextL == NULL) {
            cont->status = cont->nextR->level;
        } else if (cont->nextR == NULL) {
            cont->status = cont->nextL->level * (-1);
        } else {
            cont->status = cont->nextR->level - cont->nextL->level;
        }
        statusHandler(cont);
    }

    /* if (new != rootFirst && new->previous->previous != NULL) {
        current = new;
        do {
            if (current->previous->status > 1) {
                printf("test\n");
                leftRotation(current->nextR);
                printf("test2\n");
            } else if (current->previous->status < -1) {
                rightRotation(current->nextL);
            }
            current = current->previous;
            printf("test3\n");
        } while (current->previous != NULL);

        printf("test4\n");
    }
    printf("test5\n"); */
}


void insert(int value) {
    // insertion
    printf("try to add value\n");
    struct node *newNode;
    newNode = malloc(sizeof(struct node));
    newNode->value = value;
    newNode->nextL = NULL;
    newNode->nextR = NULL;
    newNode->previous = NULL;
    if (rootFirst == NULL) {
        rootFirst = newNode;
        newNode->status = 0;
        newNode->level = 1;
        printf("%d has been added.\tStatus: %d\n", value, newNode->level);
    } else {
        struct node *current = rootFirst;
        while (current->nextL != NULL || current->nextR != NULL) {
            if (newNode->value > current->value && current->nextR != NULL) {
                printf("test1\n");

                current = current->nextR;
                printf("test2\n");

            } else if (newNode->value < current->value && current->nextL != NULL) {
                current = current->nextL;
            } else if (newNode->value == current->value){
                printf("%d has already been added.\n", value);
                break;
            } else {
                printf("Das sollte nicht passieren\n");
                break;
            }
            printf("test3\n");

        }
        printf("test4\n");

        if (value > current->value) {
            current->nextR = newNode;
            newNode->level = 1;
            newNode->previous = current;
            newNode->nextL = NULL;
            newNode->nextR = NULL;
            newNode->status = 0;
            printf("%d has been added on the right of %d.\tStatus: %d\n", value, current->value, newNode->status);
        } else {
            current->nextL = newNode;
            newNode->level = 1;
            newNode->previous = current;
            newNode->nextR = NULL;
            newNode->nextL = NULL;
            newNode->status = 0;
            printf("%d has been added on the left of %d.\tStatus: %d\n", value, current->value, newNode->status);
        }


        levelHandler(newNode->previous);
    }


}


void printTreeInt(struct node * root, int space){

    space += 10;

    if(root->nextR != NULL) {
        if (root->nextR->value) {
            printTreeInt(root->nextR, space);
        }
    }

    for (int i = 0; i < space; ++i) {
        if((space-i) < 10){
            printf("-");
        }else{
            printf(" ");
        }
        if((space-i)%10 == 0){
            printf("|");
        }
    }

    int foo = root->previous == NULL ? -1 : root->previous->value;
    printf("-%d (%d | %d | %d)\n", root->value, root->status, root->level, foo);

    if(root->nextL != NULL) {
        if (root->nextL->value) {
            printTreeInt(root->nextL, space);

        }
    }
}

void main() {
    // int data[15] = {200,300,400,500,350,100,125,50,60,70,80,150,180,170,140};
    //int data[5] = {4,2,1,5,3};
    int data[5] = {2,1,4,3,5};
    for (int i = 0; i < sizeof(data)/sizeof(int); i++) {
        // printf("added something\n");
        insert(data[i]);
        //printTreeInt(rootFirst, 0);
    }
    printTreeInt(rootFirst, 0);
    printf("\n\n\n");
    rootFirst = balanceTreeRR(rootFirst);
    //printf("%d\n", rootFirst->value);

    //printf("%d\n", rootFirst->nextR->nextR->value);
    printTreeInt(rootFirst, 0);
    printf("\n\n\n");

    //rootFirst = balanceTreeRR(rootFirst);
    //printTreeInt(rootFirst, 0);

    printf("sleeping");
    sleep(10);
}

