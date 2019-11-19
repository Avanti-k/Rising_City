#ifndef RBTREE_H
#define RBTREE_H
#include "Building.h"

enum RBColor {
    BLACK,
    RED
};

enum COMPARE_RES
{
    SMALLER,
    LARGER,
    EQUAL
};

class RBNode
{
    public:
        RBNode();
        RBNode(Building *b);

        int get_color();
        RBNode* get_left();
        RBNode* get_right();
        RBNode* get_parent();
        Building* get_building();

        //delete funs
        RBNode * uncle();
        bool isOnLeft();
        RBNode * sibling();
        void moveDown(RBNode *nParent);
        bool hasRedChild();

    //private:
        Building * bldg;
        RBNode * left;
        RBNode * right;
        RBNode * parent;
        int color;


};



class RBTree
{
    public:
        RBTree();
        virtual ~RBTree();
        void RBTree_insert(RBNode * node);
        RBNode* BSTInsert(RBNode* root, RBNode *node);
        int compare_building_num(RBNode * r1, RBNode * r2);
        void levelOrderHelper(RBNode *root);
        void inorderHelper(RBNode *root);

        // delete functions
        void deleteByVal(int bldg_num);
        void deleteNode(RBNode *v);
        void fixDoubleBlack(RBNode *x);
        RBNode * BSTreplace(RBNode *x);
        RBNode *successor(RBNode *x);
        void fixRedRed(RBNode *x);
        void swapColors(RBNode *x1, RBNode *x2);
        void swapValues(RBNode *u, RBNode *v);
        void rightRotate(RBNode *x); // not sure if this is needed
        void leftRotate(RBNode *x);
        RBNode *search(int bldg);

    //protected:

    //private:
    RBNode * RBRoot;
    private:
        void rotateLeft(RBNode *&root, RBNode *&pt);
        void rotateRight(RBNode *&root, RBNode *&pt);
        void fixViolation(RBNode *&root, RBNode *&node);
        RBNode* STInsert(RBNode* root, RBNode *node);

};

#endif // RBTREE_H
