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


 RBNode * RBNode::uncle() {
    // If no parent or grandparent, then no uncle
    if (parent == NULL or parent->parent == NULL)
      return NULL;

    if (parent->isOnLeft())
      // uncle on right
      return parent->parent->right;
    else
      // uncle on left
      return parent->parent->left;
  }

  // check if node is left child of parent
bool RBNode::isOnLeft()
{
    return (this == this->parent->left);
}

  // returns pointer to sibling
  RBNode * RBNode::sibling() {
    // sibling null if no parent
    if (parent == NULL)
      return NULL;

    if (isOnLeft())
      return parent->right;

    return parent->left;
  }

  // moves node down and moves given node in its place
  void RBNode::moveDown(RBNode *nParent) {
    if (parent != NULL) {
      if (isOnLeft()) {
        parent->left = nParent;
      } else {
        parent->right = nParent;
      }
    }
    nParent->parent = parent;
    parent = nParent;
  }

  bool RBNode::hasRedChild() {
    return (left != NULL and left->color == RED) or
           (right != NULL and right->color == RED);
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

// A recursive function to do level order traversal
void RBTree::inorderHelper(RBNode *root)
{
    if (root == NULL)
        return;

    inorderHelper(root->left);
    cout << root->get_building()->get_building_num() << " ( "<<root->get_color()<<")  ";
    inorderHelper(root->right);
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
        cout << temp->get_building()->get_building_num() << " ( "<<temp->get_color()<<")  ";
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


// ------------------------------------------ //


  // deletes the given node
  void RBTree::deleteNode(RBNode *v) {
    RBNode *u = BSTreplace(v);

    // True when u and v are both black
    bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
    RBNode *parent = v->parent;

    if (u == NULL) {
      // u is NULL therefore v is leaf
      if (v == RBRoot) {
        // v is RBRoot, making RBRoot null
        RBRoot = NULL;
      } else {
        if (uvBlack) {
          // u and v both black
          // v is leaf, fix double black at v
          fixDoubleBlack(v);
        } else {
          // u or v is red
          if (v->sibling() != NULL)
            // sibling is not null, make it red"
            v->sibling()->color = RED;
        }

        // delete v from the tree
        if (v->isOnLeft()) {
          parent->left = NULL;
        } else {
          parent->right = NULL;
        }
      }
     // delete v;
      return;
    }

    if (v->left == NULL or v->right == NULL) {
      // v has 1 child
      if (v == RBRoot) {
        // v is RBRoot, assign the value of u to v, and delete u
        v->bldg = u->bldg;
        v->left = v->right = NULL;
        delete u;
      } else {
        // Detach v from tree and move u up
        if (v->isOnLeft()) {
          parent->left = u;
        } else {
          parent->right = u;
        }
        delete v;
        u->parent = parent;
        if (uvBlack) {
          // u and v both black, fix double black at u
          fixDoubleBlack(u);
        } else {
          // u or v red, color u black
          u->color = BLACK;
        }
      }
      return;
    }

    // v has 2 children, swap values with successor and recurse
    swapValues(u, v);
    deleteNode(u);
  }

 // utility function that deletes the node with given value
  void RBTree::deleteByVal(int bldg_num) {
    if (RBRoot == NULL)
      // Tree is empty
      return;

    RBNode *v = search(bldg_num);

    if (v->get_building()->building_num != bldg_num) {
      cout << "No node found to delete with value:" << bldg_num << endl;
      return;
    }

    deleteNode(v);
  }

   // searches for given value
  // if found returns the node (used for delete)
  // else returns the last node while traversing (used in insert)
  RBNode *RBTree::search(int bldg) {
    RBNode *temp = RBRoot;
    while (temp != NULL) {
      if (bldg < temp->get_building()->get_building_num()) {
        if (temp->left == NULL)
          break;
        else
          temp = temp->left;
      } else if (bldg == temp->get_building()->get_building_num()) {
        break;
      } else {
        if (temp->right == NULL)
          break;
        else
          temp = temp->right;
      }
    }

    return temp;
  }


  void RBTree::fixDoubleBlack(RBNode *x) {
    if (x == RBRoot)
      // Reached RBRoot
      return;

    RBNode *sibling = x->sibling(), *parent = x->parent;
    if (sibling == NULL) {
      // No sibiling, double black pushed up
      fixDoubleBlack(parent);
    } else {
      if (sibling->color == RED) {
        // Sibling red
        parent->color = RED;
        sibling->color = BLACK;
        if (sibling->isOnLeft()) {
          // left case
          rightRotate(parent);
        } else {
          // right case
          leftRotate(parent);
        }
        fixDoubleBlack(x);
      } else {
        // Sibling black
        if (sibling->hasRedChild()) {
          // at least 1 red children
          if (sibling->left != NULL and sibling->left->color == RED) {
            if (sibling->isOnLeft()) {
              // left left
              sibling->left->color = sibling->color;
              sibling->color = parent->color;
              rightRotate(parent);
            } else {
              // right left
              sibling->left->color = parent->color;
              rightRotate(sibling);
              leftRotate(parent);
            }
          } else {
            if (sibling->isOnLeft()) {
              // left right
              sibling->right->color = parent->color;
              leftRotate(sibling);
              rightRotate(parent);
            } else {
              // right right
              sibling->right->color = sibling->color;
              sibling->color = parent->color;
              leftRotate(parent);
            }
          }
          parent->color = BLACK;
        } else {
          // 2 black children
          sibling->color = RED;
          if (parent->color == BLACK)
            fixDoubleBlack(parent);
          else
            parent->color = BLACK;
        }
      }
    }
  }


    // find node that replaces a deleted node in BST
  RBNode * RBTree::BSTreplace(RBNode *x) {
    // when node have 2 children
    if (x->left != NULL and x->right != NULL)
      return successor(x->right);

    // when leaf
    if (x->left == NULL and x->right == NULL)
      return NULL;

    // when single child
    if (x->left != NULL)
      return x->left;
    else
      return x->right;
  }

  // find node that do not have a left child
  // in the subtree of the given node
  RBNode *RBTree::successor(RBNode *x) {
    RBNode *temp = x;

    while (temp->left != NULL)
      temp = temp->left;

    return temp;
  }

  // fix red red at given node
  void RBTree::fixRedRed(RBNode *x) {
    // if x is RBRoot color it black and return
    if (x == RBRoot) {
      x->color = BLACK;
      return;
    }

    // initialize parent, grandparent, uncle
    RBNode *parent = x->parent, *grandparent = parent->parent,
         *uncle = x->uncle();

    if (parent->color != BLACK) {
      if (uncle != NULL && uncle->color == RED) {
        // uncle red, perform recoloring and recurse
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        fixRedRed(grandparent);
      } else {
        // Else perform LR, LL, RL, RR
        if (parent->isOnLeft()) {
          if (x->isOnLeft()) {
            // for left right
            swapColors(parent, grandparent);
          } else {
            leftRotate(parent);
            swapColors(x, grandparent);
          }
          // for left left and left right
          rightRotate(grandparent);
        } else {
          if (x->isOnLeft()) {
            // for right left
            rightRotate(parent);
            swapColors(x, grandparent);
          } else {
            swapColors(parent, grandparent);
          }

          // for right right and right left
          leftRotate(grandparent);
        }
      }
    }
}

  void RBTree::swapColors(RBNode *x1, RBNode *x2) {
    int temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
  }

  void RBTree::swapValues(RBNode *u, RBNode *v) {
    Building* temp;
    temp = u->bldg;
    u->bldg = v->bldg;
    v->bldg = temp;
  }

    // left rotates the given node
  void RBTree::leftRotate(RBNode *x) {
    // new parent will be node's right child
    RBNode *nParent = x->right;

    // update RBRoot if current node is RBRoot
    if (x == RBRoot)
      RBRoot = nParent;

    x->moveDown(nParent);

    // connect x with new parent's left element
    x->right = nParent->left;
    // connect new parent's left element with node
    // if it is not null
    if (nParent->left != NULL)
      nParent->left->parent = x;

    // connect new parent with x
    nParent->left = x;
  }

  void RBTree::rightRotate(RBNode *x) {
    // new parent will be node's left child
    RBNode *nParent = x->left;

    // update RBRoot if current node is RBRoot
    if (x == RBRoot)
      RBRoot = nParent;

    x->moveDown(nParent);

    // connect x with new parent's right element
    x->left = nParent->right;
    // connect new parent's right element with node
    // if it is not null
    if (nParent->right != NULL)
      nParent->right->parent = x;

    // connect new parent with x
    nParent->right = x;
  }
