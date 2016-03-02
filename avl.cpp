#include "avl.h"
#include <math.h>
#include <iostream>
using namespace std;

AVL::AVL(void)
{
    AVLRootNode = new node;
    AVLRootNode->key = 0;

    cout << "Enter the k-value : ";
    cin >> kValue;

    do {
        cout << "Enter the landing time for the root node of AVL : ";
        cin >> AVLRootNode->key;
        cout << endl;
    } while (AVLRootNode->key <= 0);


    AVLRootNode->parent = nullptr;
    AVLRootNode->left = nullptr;
    AVLRootNode->right = nullptr;
    AVLRootNode->height = 0;
}

void AVL::addNode(void)
{
    node* nodeToBeAdded = new node;
    cout << "New Node Being Added!" << endl;
    cout << "Enter landing time of new node : ";
    cin >> nodeToBeAdded->key;
    nodeToBeAdded->parent = nullptr;
    nodeToBeAdded->left = nullptr;
    nodeToBeAdded->right = nullptr;
    nodeToBeAdded->height = 0;

    node* currentNode = AVLRootNode;
    while (1)
    {
        if ((abs(nodeToBeAdded->key - currentNode->key) <= kValue))
        {
            cout << "Landing time to be added violates k-value property!";
            cout << endl << "Landing time not added" << endl;
            return;
        }
        if (nodeToBeAdded->key < 0)
        {
            cout << "Landing time has to be greater than 0";
            cout << endl << "Landing time not added" << endl;
            return;
        }
        
        if (nodeToBeAdded->key < currentNode->key)
        {
            if (currentNode->left == nullptr)
            {
                currentNode->left = nodeToBeAdded;
                nodeToBeAdded->parent = currentNode;
                int temp = setHeight(AVLRootNode);
                setHeaviness(AVLRootNode);                
                makeAVL(nodeToBeAdded);
                printAVL(AVLRootNode);
                return;
            }
            else
            {
                currentNode = currentNode->left;
            }
        }
        else
        {
            if (currentNode->right == nullptr)
            {
                currentNode->right = nodeToBeAdded;
                nodeToBeAdded->parent = currentNode;
                int temp = setHeight(AVLRootNode);
                setHeaviness(AVLRootNode);
                makeAVL(nodeToBeAdded);
                printAVL(AVLRootNode);
                return;
            }
            else
            {
                currentNode = currentNode->right;
            }
        }
    }
}

void AVL::printAVL(node* temp)
{
    cout << "Key : " << temp->key << "\tHeight : " << temp->height << "\tHeaviness : " << temp->heaviness << endl;
    if (temp->left != nullptr)
    {
        printAVL(temp->left);
    }
    if (temp->right != nullptr)
    {
        printAVL(temp->right);
    }
}

node* AVL::getRootNode(void)
{
    return AVLRootNode;
}

int AVL::setHeight(node* given)//recursive algo to find heights of all nodes
{
    int leftHeight, rightHeight;

    if (given->left == nullptr)
    {
        leftHeight = -1;
    }
    else
    {
        leftHeight = setHeight(given->left);
    }
    if (given->right == nullptr)
    {
        rightHeight = -1;
    }
    else
    {
        rightHeight = setHeight(given->right);
    }
    int max = rightHeight;
    if (leftHeight > max)
    {
        max = leftHeight;
    }
    given->height = max + 1;
    return (max + 1);
}

void AVL::setHeaviness(node* temp)//recursive algo to find heaviness of all nodes
{
    int leftHeight, rightHeight;
    if(temp->left == nullptr)
    {
        leftHeight = -1;
    }
    else
    {
        leftHeight = temp->left->height;
    }
    if (temp->right == nullptr)
    {
        rightHeight = -1;
    }
    else
    {
        rightHeight = temp->right->height;
    }
    temp->heaviness = rightHeight - leftHeight;
    if (temp->left != nullptr)
    {
        setHeaviness(temp->left);
    }
    if (temp->right != nullptr)
    {
        setHeaviness(temp->right);
    }
}

void AVL::leftRotate(node* given)
{
    bool flag;
    if (given->parent != nullptr)
    {
        if (given == given->parent->right)
        {
            flag = true;//given is right child
        }
        else
        {
            flag = false;//given is left child
        }
    }
    else
    {
        AVLRootNode = given->right;//if given->parent == nullptr, then it means given is AVLRootnNode and now AVLRootNode has to be set to given->right
    }
    node* temp = given->right;
    node* parent = given->parent;
    given->right = given->right->left;
    if (given->right != nullptr)
    {
        given->right->parent = given;
    }
    temp->left = given;
    given->parent = temp;
    temp->parent = parent;
    if (given->parent->parent != nullptr)
    {
        if (flag == true)
        {
            parent->right = temp;
        }
        else
        {
            parent->left = temp;
        }
    }
}

void AVL::rightRotate(node* given)
{
    bool flag;
    if (given->parent != nullptr)
    {
        if (given == given->parent->right)
        {
            flag = true;//given is right child
        }
        else
        {
            flag = false;//given is left child
        }
    }
    else
    {
        AVLRootNode = given->left;//if given->parent == nullptr, then it means given is AVLRootnNode and now AVLRootNode has to be set to given->left
    }
    node* temp = given->left;
    node* parent = given->parent;
    given->left = given->left->right;
    if (given->left != nullptr)
    {
        given->left->parent = given;
    }
    temp->right = given;
    given->parent = temp;
    temp->parent = parent;
    if (given->parent->parent != nullptr)
    {
        if (flag == true)
        {
            parent->right = temp;
        }
        else
        {
            parent->left = temp;
        }
    }
}

void AVL::makeAVL(node* given)
{
    if (given->heaviness<2 && given->heaviness>-2)
    {
        if (given->parent != nullptr)
        {
            makeAVL(given->parent);
        }
        return;
    }
    if (given->heaviness >= 2)//doubly right heavy
    {
        if (given->right->heaviness > 0)//right node is right heavy
        {
            leftRotate(given);
        }
        else//right node is left heavy
        {
            rightRotate(given->right);
            leftRotate(given);
        }
    }
    else//doubly left heavy
    {
        if (given->left->heaviness < 0)//left node is left heavy
        {
            rightRotate(given);
        }
        else
        {
            leftRotate(given->left);
            rightRotate(given);
        }
    }
    //update height and heaviness after rotation procedure
    int temp = setHeight(AVLRootNode);
    setHeaviness(AVLRootNode);
    if (given->parent->parent != nullptr)
    {
        makeAVL(given->parent->parent);
    }
}