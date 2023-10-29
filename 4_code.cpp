#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* Search(struct Node* root, int target) {
    if (root == NULL || root->data == target)
        return root;

    if (target < root->data)
        return Search(root->left, target);
    else
        return Search(root->right, target);
}

struct Node* CreateTree(struct Node* root, int data) {
    if (root == NULL) {
        root = (struct Node*)malloc(sizeof(struct Node));
        if (root == NULL) {
            printf("Something went wrong");
            exit(0);
        }
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
    }

   //TASK 3
    if (data < root->data) {                         // traversing past the alraedy existing values TASK 3
        root->left = CreateTree(root->left, data);
    }
    else if (data > root->data) {
        root->right = CreateTree(root->right, data);
    }
    else if (data == root->data) {
        root->right = CreateTree(root->right, data);
    };

    return root;
}

int CountOccurrences(struct Node* root, int target) {
    if (root == NULL)
        return 0;

    if (root->data == target)
        return 1 + CountOccurrences(root->left, target) + CountOccurrences(root->right, target);
    else if (target < root->data)
        return CountOccurrences(root->left, target);
    else
        return CountOccurrences(root->right, target);
}

void print_tree(struct Node* r, int l) {
    if (r == NULL)
        return;

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++) {
        printf(" ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

int main() {
    int D = 0;
    char buffer[10];
    int start = 1;

    struct Node* root = NULL;

    printf("gahdamn - type '-1' to stop\n");
    while (start) {
        printf("Enter number: ");
        std::cin >> buffer;
        if (atoi(buffer) == 0 && buffer[0] != '0')
        {
            std::cout << "wrong, only integers are allowed" << std::endl;
            continue;
        }
        D = atoi(buffer);
        //scanf("%d", &D);
        if (D == -1)
        {
            printf("Job well done\n\n");
            start = 0;
        }
        else {
            D = atoi(buffer);
            root = CreateTree(root, D);
        }
        
    }

    print_tree(root, 0);

    printf("What do you want to find? : ");
    scanf("%d", &D);

    struct Node* result = Search(root, D);
    if (result != NULL) {
        printf(" %d present in the structure:\n", D);
    }
    else {
        printf("%d bruh, nothing like that :( \n", D);
    }

    printf("Type in the number to calculate entry times: ");
    scanf("%d", &D);

    int count = CountOccurrences(root, D);

    printf("Value %d occurs %d times in this tree\n", D, count);

    return 0;
}