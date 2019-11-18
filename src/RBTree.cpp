#include "RBTree.h"
#include "Building.h"
#include <stddef.h>
#include <queue>
#include <iostream>

using namespace std;

RBNode::RBNode(Building* b)
{
    this->bldg = b;
    this->color = RED;
    this->left = NULL;
    this->parent = NULL;
    this->right = NULL;
}

int RBNode::get_color()
{
    return this->color;
}

RBNode* RBNode::get_left()
{
    return this->left;
}

RBNode* RBNode::get_right()
{
    return this->right;
}

RBNode* RBNode::get_parent()
{
    return this->parent;
}

Building * RBNode::get_building()
{
    return this->bldg;
}

// Tree

RBTree::RBTree()
{
    //ctor
    this->RBRoot = NULL;

}

RBTree::~RBTree()
{
    //dtor
}

int RBTree::compare_building_num(RBNode * r1, RBNode * r2)
{
    if(r1->get_building()->get_building_num() < r2->get_building()->get_building_num())
    {
        return SMALLER;
    }
    else if(r1->get_building()->get_building_num() > r2->get_building()->get_building_num())
    {
        return LARGER;
    }
    else
    {
        return EQUAL;
    }
}



// Utility function to do level order traversal
void RBTree::levelOrderHelper(RBNode *root)
{
    if (root == NULL)
        return;

    queue<RBNode *> q;
    q.push(root);

    while (!q.empty())
    {
        RBNode *temp = q.front();
        cout << temp->get_building()->get_building_num() << "  ";
        q.pop();

        if (temp->get_left() != NULL)
            q.push(temp->get_left());

        if (temp->get_right() != NULL)
            q.push(temp->get_right());
    }
}

void RBTree::rotateLeft(RBNode *&root, RBNode *&pt)
{
    RBNode *pt_right = pt->get_right();

    pt->right = pt_right->get_left();

    if (pt->get_right() != NULL)
        pt->right->parent = pt;

    pt_right->parent = pt->get_parent();

    if (pt->get_parent() == NULL)
        root = pt_right;

    else if (pt == pt->get_parent()->get_left())
        pt->parent->left = pt_right;

    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

void RBTree::rotateRight(RBNode *&root, RBNode *&pt)
{
    RBNode *pt_left = pt->get_left();

    pt->left = pt_left->get_right();

    if (pt->get_left() != NULL)
        pt->left->parent = pt;

    pt_left->parent = pt->get_parent();

    if (pt->get_parent() == NULL)
        root = pt_left;

    else if (pt == pt->get_parent()->get_left())
        pt->parent->left = pt_left;

    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

// This function fixes violations caused by BST insertion
void RBTree::fixViolation(RBNode *&root, RBNode *&node)
{
    RBNode *parent_pt = NULL;
    RBNode *grand_parent_pt = NULL;

    while ((node != root) && (node->color != BLACK) &&
           (node->get_parent()->color == RED))
    {

        parent_pt = node->get_parent();
        grand_parent_pt = node->get_parent()->get_parent();

        /*  Case : A
            Parent of pt is left child of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->get_left())
        {

            RBNode *uncle_pt = grand_parent_pt->get_right();

            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->color == RED)
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                node = grand_parent_pt;
            }

            else
            {
                /* Case : 2
                   pt is right child of its parent
                   Left-rotation required */
                if (node == parent_pt->get_right())
                {
                    rotateLeft(root, parent_pt);
                    node = parent_pt;
                    parent_pt = node->get_parent();
                }

                /* Case : 3
                   pt is left child of its parent
                   Right-rotation required */
                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                node = parent_pt;
            }
        }

        /* Case : B
           Parent of pt is right child of Grand-parent of pt */
        else
        {
            RBNode *uncle_pt = grand_parent_pt->get_left();

            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->color == RED))
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                node = grand_parent_pt;
            }
            else
            {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (node == parent_pt->get_left())
                {
                    rotateRight(root, parent_pt);
                    node = parent_pt;
                    parent_pt = node->get_parent();
                }

                /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                node = parent_pt;
            }
        }
    }

    root->color = BLACK;
}



RBNode* RBTree::BSTInsert(RBNode* root, RBNode *node)
{
    // insert the RBNode here
    // if root null, first node
    if(root == NULL)
    {
        //root = node;
        return node;
    }

    /* Otherwise, recur down the tree */
    int ret = compare_building_num(node, root);
    if (ret == SMALLER) // new node is smaller
    {
        root->left = BSTInsert(root->get_left(), node);
        root->left->parent = root;
    }
    else if (ret == LARGER)
    {
        root->right = BSTInsert(root->get_right(), node);
        root->right->parent = root;
    }
    else if(ret == EQUAL)
    {
        cout<<"Error: Duplicate Building IDs !"<<endl;
        return NULL;
    }

    /* return the (unchanged) node pointer */
    return root;
}

void RBTree:: RBTree_insert(RBNode * node)
{
// Do a normal BST insert
    this->RBRoot = BSTInsert(this->RBRoot, node);

    // fix Red Black Tree violations
    fixViolation(this->RBRoot, node);


}
