#pragma once

struct node
{
    node* parent;
    node* left;
    node* right;

    int key;
    int height;
    int heaviness;//right->height - left->height
};

class AVL
{
private:
    node* AVLRootNode;
    int kValue;

public:
    AVL(void);
    void addNode(void);
    void printAVL(node*);

    node* getRootNode(void);

    int setHeight(node*);
    void setHeaviness(node*);

    void rightRotate(node*);
    void leftRotate(node*);

    void makeAVL(node*);
    
    //~AVL(void);
};