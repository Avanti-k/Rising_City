#ifndef RBTREE_H
#define RBTREE_H
#include "Building.h"
#include <string>
#include <sstream>

// for removing
#define START_POS 1
enum RBColor {
    BLACK,
    RED
};
/* Used in comparator functions */
enum COMPARE_RES
{
    SMALLER,
    LARGER,
    EQUAL
};

/* Class for nodes of the RedBlack Tree
* Each node will contain a building pointer, left right child and color */
class RBNode
{
    public:
        RBNode();
        RBNode(Building *bldg);

        /* Data Members */
        Building * bldg;
        RBNode * left;
        RBNode * right;
        RBNode * parent;
        int color;

        /* Getter functions */
        int get_color();
        RBNode* get_left();
        RBNode* get_right();
        RBNode* get_parent();
        Building* get_building();

        /* Delete funs */
        RBNode * get_uncle();
        bool is_left_child();
        RBNode * get_sibling();
        void move_down(RBNode *nParent);
        bool has_red_child();

};


/* Class for Red Black Tree */
class RBTree
{
    public:
        RBTree();
        virtual ~RBTree();
        RBNode * RBRoot;
        void RBTree_insert(RBNode * node);
        void delete_node(RBNode *v);

        static int compare_executed_time(RBNode * r1, RBNode * r2);
        void print_single_building(int bldg_id);
        void print_building_range(int b1, int b2);


    private:
       // RBNode* BSTInsert(RBNode* root, RBNode *node);
        int compare_building_num(RBNode * r1, RBNode * r2);
        void level_order_aux(RBNode *root);
        void inorder_aux(RBNode *root);
        std::string inorder_aux_range(RBNode *root, int b1, int b2);

        // delete functions
        void delete_val(int bldg_num);
        void fix_black_black(RBNode *x);
        RBNode * BST_replace(RBNode *x);
        RBNode *get_successor(RBNode *x);
        void fix_red_red(RBNode *x);
        void colors_flip(RBNode *x1, RBNode *x2);
        void values_flip(RBNode *u, RBNode *v);
        void del_right_rotate(RBNode *x);
        void del_left_rotate(RBNode *x);
        RBNode *search(int bldg);

        void rotate_left(RBNode *&root, RBNode *&pt);
        void rotate_right(RBNode *&root, RBNode *&pt);
        void fix_violation(RBNode *&root, RBNode *&node);
        RBNode* BST_Insert(RBNode* root, RBNode *node);

};

#endif // RBTREE_H
