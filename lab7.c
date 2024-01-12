#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Function to create a binary tree using level order traversal
struct Node* insertLevelOrder(int arr[], struct Node* root, int i, int n) {
    if (i < n) {
        struct Node* temp = newNode(arr[i]);
        root = temp;

        root->left = insertLevelOrder(arr, root->left, 2 * i + 1, n);
        root->right = insertLevelOrder(arr, root->right, 2 * i + 2, n);
    }
    return root;
}

// Function to perform in-order traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to perform pre-order traversal
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Function to perform post-order traversal
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Function to create a binary tree using pre-order and in-order traversals
struct Node* buildTree(int pre[], int in[], int start, int end) {
    static int preIndex = 0;

    if (start > end)
        return NULL;

    struct Node* root = newNode(pre[preIndex++]);

    if (start == end)
        return root;

    int inIndex = search(in, start, end, root->data);

    root->left = buildTree(pre, in, start, inIndex - 1);
    root->right = buildTree(pre, in, inIndex + 1, end);

    return root;
}

// Helper function to search an element in an array
int search(int arr[], int start, int end, int value) {
    int i;
    for (i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return i;
}

int main() {
    int n, i;

    // Example 1: Creating a binary tree using level order traversal
    printf("Enter the number of nodes for level order traversal: ");
    scanf("%d", &n);

    int levelOrderArr[n];
    printf("Enter the nodes in level order: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &levelOrderArr[i]);
    }

    struct Node* levelOrderRoot = insertLevelOrder(levelOrderArr, NULL, 0, n);

    printf("Level Order Traversal: ");
    inorder(levelOrderRoot);
    printf("\n");

    printf("In-order Traversal: ");
    inorder(levelOrderRoot);
    printf("\n");

    printf("Pre-order Traversal: ");
    preorder(levelOrderRoot);
    printf("\n");

    printf("Post-order Traversal: ");
    postorder(levelOrderRoot);
    printf("\n\n");

    // Example 2: Creating a binary tree using pre-order and in-order traversals
    printf("Enter the number of nodes for pre-order and in-order traversals: ");
    scanf("%d", &n);

    int preOrderArr[n], inOrderArr[n];
    printf("Enter the nodes for pre-order traversal: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &preOrderArr[i]);
    }

    printf("Enter the nodes for in-order traversal: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &inOrderArr[i]);
    }

    struct Node* preInOrderRoot = buildTree(preOrderArr, inOrderArr, 0, n - 1);

    printf("In-order Traversal: ");
    inorder(preInOrderRoot);
    printf("\n");

    printf("Pre-order Traversal: ");
    preorder(preInOrderRoot);
    printf("\n");

    printf("Post-order Traversal: ");
    postorder(preInOrderRoot);
    printf("\n");

    return 0;
}
