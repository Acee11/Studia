#include <stdio.h>
#define INF 0x7FFFFFFF

typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
};

struct node* utworz(int wart)
{
    struct node *pom;
    pom = malloc(sizeof(struct node));
    pom->left = NULL;
    pom->right = NULL;
    pom->val = wart;
    return pom;
}

struct node* insert(struct node *root, int nkey)
{
    if (!root) return utworz(nkey);
    if (nkey < root->val)
        root->left = insert(root->left, nkey);
    else if (nkey >= root->val)
        root->right = insert(root->right, nkey);
    return root;
}


int treeSize(struct node *root) //zad2
{
    if(!root) return 0;
    return treeSize(root->left) + treeSize(root->right) + 1;
}

int treeHeight(struct node *root)
{
    if(!root) return 0;
    int m1 = treeHeight(root->left);
    int m2 = treeHeight(root->right);
    if (m1 > m2) return m1 +1;
    else return m2 + 1;
}

void wypisz(struct node *root)
{
    if(!root) return;
    wypisz(root->left);
    printf("%d",root->val);
    wypisz(root->right);
}

int check(struct node *root,int a, int b)
{
    if (!root) return 1;
    if(root->val < a  ||  root->val >= b) return 0;
    return (check(root->left,a,root->val) && check(root->right,root->val,b));
}


int main()
{
    struct node *root = utworz(0);
    int i;

    printf("%d %d\n",INF,-INF);


    printf("%d",check(root,-INF,INF));

    return 0;
}
