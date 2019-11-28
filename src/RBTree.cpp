#include "RBTree.h"
#include "Building.h"
#include <stddef.h>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>
#include<strstream>
#include <cstdlib>

using namespace std;
extern unsigned int days_timer;
extern ofstream op;

RBNode::RBNode(Building* b)
{
    this->bldg = b;
    this->color = RED;
    this->left = NULL;
    this->parent = NULL;
    this->right = NULL;
}

/* Returns color of this node */
int RBNode::get_color()
{
    return this->color;
}

/* Returns left child of this node */
RBNode* RBNode::get_left()
{
    return this->left;
}

/* Returns right child of this node */
RBNode* RBNode::get_right()
{
    return this->right;
}

/* Returns parent of this node */
RBNode* RBNode::get_parent()
{
    return this->parent;
}

/* Returns Building ID of this node */
Building * RBNode::get_building()
{
    return this->bldg;
}

/* Returns sibling of parent */
 RBNode * RBNode::get_uncle() {
    // There will not be uncle if parent or grand parent is NULL
    if (parent == NULL or parent->parent == NULL)
      return NULL;

    if (parent->is_left_child())
      // uncle on right
      return parent->parent->right;
    else
      // uncle on left
      return parent->parent->left;
  }

/* check if node is left child of parent */
bool RBNode::is_left_child()
{
    return (this == this->parent->left);
}

/* returns pointer to sibling */
  RBNode * RBNode::get_sibling() {
    // sibling null if no parent
    if (parent == NULL)
      return NULL;

    if (is_left_child())
      return parent->right;

    return parent->left;
  }

  /* moves node down and moves given node in its place*/
  void RBNode::move_down(RBNode *new_parent) {
    if (parent != NULL) {
      if (is_left_child()) {
        parent->left = new_parent;
      } else {
        parent->right = new_parent;
      }
    }
    new_parent->parent = parent;
    parent = new_parent;
  }

  /* Tells if the node has RED child, used in deletion */
  bool RBNode::has_red_child() {
    return (left != NULL and left->color == RED) or
           (right != NULL and right->color == RED);
  }



// Red Black Tree

RBTree::RBTree()
{
    //constructor
    this->RBRoot = NULL;

}

RBTree::~RBTree()
{
    //destructor
}

/* Returns whether the building id in node 1 is smaller than greater than
* or equal to the building id in node 2 */
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
/* Returns the node with building having lesser executed time */
int RBTree::compare_executed_time(RBNode* r1, RBNode * r2)
{
    if(r1->get_building()->get_executed_time() < r2->get_building()->get_executed_time())
    {
        return SMALLER;
    }
    else if (r1->get_building()->get_executed_time() > r2->get_building()->get_executed_time())
    {
        return LARGER;
    }
    else if(r1->get_building()->get_executed_time() == r2->get_building()->get_executed_time())
    {
        return (r1->get_building()->get_building_num() < r2->get_building()->get_building_num())? SMALLER: LARGER;
    }
    return SMALLER;
}

/* level order traversal */
void RBTree::inorder_aux(RBNode *root)
{
    if (root == NULL)
        return;

    inorder_aux(root->left);
    cout << root->get_building()->get_building_num() << "("<<root->get_color()<<")  ";
    inorder_aux(root->right);
}

/* Traverses the nodes from the given range in order
* root - root of the tree
* start - starting range of building ID
* end - end's building ID */
string RBTree::inorder_aux_range(RBNode *root, int start, int end)
{
    string ret = ""; // String containing data of nodes to be printed.
    if (root == NULL)
        return ret;

    ret.append(inorder_aux_range(root->left, start, end));
    if((root->get_building()->get_building_num() >= start) && (root->get_building()->get_building_num() <= end))
    {
        cout<<",("<<root->get_building()->get_building_num()<<","
                    <<root->get_building()->get_executed_time()<<","
                    <<root->get_building()->get_total_time()<<")";
        std::stringstream s;
        s<<",("<<root->get_building()->get_building_num()<<","
                    <<root->get_building()->get_executed_time()<<","
                    <<root->get_building()->get_total_time()<<")";
        ret.append(s.str());
    }
    // Keeps appending in each recursive call
    ret.append(inorder_aux_range(root->right, start, end));
    return ret;
}

/* level order traversal jusr for testing*/
void RBTree::level_order_aux(RBNode *root)
{
    if (root == NULL)
        return;
    // A queue to maintain nodes
    queue<RBNode *> q;
    q.push(root);

    while (!q.empty())
    {
        RBNode *temp = q.front();
        cout << temp->get_building()->get_building_num() << "("<<temp->get_color()<<")  ";
        q.pop();

        if (temp->get_left() != NULL)
            q.push(temp->get_left());

        if (temp->get_right() != NULL)
            q.push(temp->get_right());
    }
}

/* Rotate left */
void RBTree::rotate_left(RBNode *&root, RBNode *&node)
{
    RBNode *node_right = node->get_right();

    node->right = node_right->get_left();

    if (node->get_right() != NULL)
        node->right->parent = node;

    node_right->parent = node->get_parent();

    if (node->get_parent() == NULL)
        root = node_right;

    else if (node == node->get_parent()->get_left())
        node->parent->left = node_right;

    else
        node->parent->right = node_right;

    node_right->left = node;
    node->parent = node_right;
}
/* Rotate right */
void RBTree::rotate_right(RBNode *&root, RBNode *&node)
{
    RBNode *node_left = node->get_left();

    node->left = node_left->get_right();

    if (node->get_left() != NULL)
        node->left->parent = node;

    node_left->parent = node->get_parent();

    if (node->get_parent() == NULL)
        root = node_left;

    else if (node == node->get_parent()->get_left())
        node->parent->left = node_left;

    else
        node->parent->right = node_left;

    node_left->right = node;
    node->parent = node_left;
}

/* This function fixes violations caused by BST insertion */
void RBTree::fix_violation(RBNode *&root, RBNode *&node)
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
                    rotate_left(root, parent_pt);
                    node = parent_pt;
                    parent_pt = node->get_parent();
                }

                /* Case : 3
                   pt is left child of its parent
                   Right-rotation required */
                rotate_right(root, grand_parent_pt);
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
                    rotate_right(root, parent_pt);
                    node = parent_pt;
                    parent_pt = node->get_parent();
                }

                /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
                rotate_left(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                node = parent_pt;
            }
        }
    }

    root->color = BLACK;
}


/* Binary Search Tree insert */
RBNode* RBTree::BST_Insert(RBNode* root, RBNode *node)
{
    // insert the RBNode here
    // if root null, first node
    if(root == NULL)
    {
        //root = node;
        return node;
    }

    // Otherwise, recur down the tree
    int ret = compare_building_num(node, root);
    if (ret == SMALLER) // new node is smaller
    {
        root->left = BST_Insert(root->get_left(), node);
        root->left->parent = root;
    }
    else if (ret == LARGER)
    {
        root->right = BST_Insert(root->get_right(), node);
        root->right->parent = root;
    }
    else if(ret == EQUAL)
    {
        // Stop execution when duplicate building IDs
        cout<<"Error: Duplicate Building IDs !"<<endl;
        std::exit(0);
    }

    return root;
}

void RBTree:: RBTree_insert(RBNode * node)
{
// Do a normal BST insert
    this->RBRoot = BST_Insert(this->RBRoot, node);

    // fix Red Black Tree violations
    fix_violation(this->RBRoot, node);
}


// ------------------------------------------ //


  // deletes the given node by address
  void RBTree::delete_node(RBNode *node) {
    RBNode *replacement_node = BST_replace(node);

    // True when replacement and node are both black
    bool both_black = ((replacement_node == NULL or replacement_node->color == BLACK) and (node->color == BLACK));
    RBNode *parent = node->parent;

    if (replacement_node == NULL) {
      // replacement_node is NULL therefore node is leaf
      //cout<<"\\n RBroot = "<<RBRoot<<endl;
      //cout<<"\n node = "<<node<<endl;
      if (node == RBRoot) {
        // node is RBRoot, making RBRoot null
        //cout<<"\n %%%%%%%%%%%%%%%%%%%% deleting RBRoot %%%%%%%%%%%%%% "<<endl;
        RBRoot = NULL;
      } else {
        if (both_black) {
          // replacement_node and node both black
          // node is leaf, fix black black at node
          //cout<<"\nhere 1"<<endl;
          fix_black_black(node);
        } else {
          // replacement_node or node is red
          if (node->get_sibling() != NULL)
            // sibling is not null, make it red"
            node->get_sibling()->color = RED;
        }

        // delete node from the tree
        if (node->is_left_child()) {
          parent->left = NULL;
        } else {
          parent->right = NULL;
        }
      }
      //cout<<"just before deleting node "<<node->bldg->building_num<<endl;
      //delete node;
      return;
    }

    if (node->left == NULL or node->right == NULL) {
      // node has 1 child
      if (node == RBRoot) {
        // node is RBRoot, assign the value of replacement_node to node, and delete replacement_node
        /*
        node->bldg = replacement_node->bldg;
        node->left = node->right = NULL;
        delete replacement_node;*/
        //  since we delete actual node not just values
        // in order to retain original memory address
        replacement_node->left = replacement_node->right = NULL;
        // root is updated with new node
        RBRoot = replacement_node;
        //delete node;
      } else {
        // Detach node from tree and move replacement_node up
        if (node->is_left_child()) {
          parent->left = replacement_node;
        } else {
          parent->right = replacement_node;
        }
        replacement_node->parent = parent;
        if (both_black) {
          // replacement_node and node both black, fix double black at replacement_node
          fix_black_black(replacement_node);
        } else {
          // replacement_node or node red, color replacement_node black
          replacement_node->color = BLACK;
        }
      }
      return;
    }

    // node has 2 children, swap values with successor and recurse
    //cout<<"\n node has 2 children\n"<<endl;
    values_flip(replacement_node, node);
    delete_node(node); // since node is now at leaf node because actual memory address is to be deleted not just value
    //deleteNode(replacement_node);
  }

 /* deletes the node with given value*/
  void RBTree::delete_val(int bldg_num) {
    if (RBRoot == NULL)
      // Tree is empty
      return;

    RBNode *v = search(bldg_num);

    if (v->get_building()->building_num != bldg_num) {
      cout << "No node found to delete with value:" << bldg_num << endl;
      return;
    }

    delete_node(v);
  }

   /*searches for given value
  // if found returns the node (used for delete)
  // else returns the last node while traversing (used in insert)*/
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


  void RBTree::fix_black_black(RBNode *x) {
    if (x == RBRoot)
      // Reached RBRoot
      return;

    RBNode *sibling = x->get_sibling(), *parent = x->get_parent();
    if (sibling == NULL) {
      // No sibiling, double black pushed up
      fix_black_black(parent);
    } else {
      if (sibling->color == RED) {
        // Sibling red
        parent->color = RED;
        sibling->color = BLACK;
        if (sibling->is_left_child()) {
          // left case
          del_right_rotate(parent);
        } else {
          // right case
          del_left_rotate(parent);
        }
        fix_black_black(x);
      } else {
        // Sibling black
        if (sibling->has_red_child()) {
          // at least 1 red children
          if (sibling->get_left() != NULL and sibling->get_left()->get_color() == RED) {
            if (sibling->is_left_child()) {
              // left left
              sibling->left->color = sibling->get_color();
              sibling->color = parent->get_color();
              del_right_rotate(parent);
            } else {
              // right left
              sibling->left->color = parent->get_color();
              del_right_rotate(sibling);
              del_left_rotate(parent);
            }
          } else {
            if (sibling->is_left_child()) {
              // left right
              sibling->right->color = parent->get_color();
              del_left_rotate(sibling);
              del_right_rotate(parent);
            } else {
              // right right
              sibling->right->color = sibling->get_color();
              sibling->color = parent->get_color();
              del_left_rotate(parent);
            }
          }
          parent->color = BLACK;
        } else {
          // 2 black children
          sibling->color = RED;
          if (parent->color == BLACK)
            fix_black_black(parent);
          else
            parent->color = BLACK;
        }
      }
    }
  }


    /* finds replacement node for a deleted node in BST*/
  RBNode * RBTree::BST_replace(RBNode *x) {
    // when node have 2 children
    if (x->get_left() != NULL and x->get_right() != NULL)
      return get_successor(x->get_right());

    // when leaf
    if (x->get_left() == NULL and x->get_right() == NULL)
      return NULL;

    // when single child
    if (x->get_left() != NULL)
      return x->get_left();
    else
      return x->get_right();
  }

  /*find node that do not have a left child
  * in the subtree of the given node */
  RBNode *RBTree::get_successor(RBNode *x) {
    RBNode *temp = x;

    while (temp->get_left() != NULL)
      temp = temp->get_left();

    return temp;
  }

/* fix red red at given node */
  void RBTree::fix_red_red(RBNode *x) {
    // if x is RBRoot color it black and return
    if (x == RBRoot) {
      x->color = BLACK;
      return;
    }

    // initialize parent, grandparent, uncle
    RBNode *parent = x->get_parent(), *grandparent = parent->get_parent(),
         *uncle = x->get_uncle();

    if (parent->get_color() != BLACK) {
      if (uncle != NULL && uncle->get_color() == RED) {
        // uncle red, perform recoloring and recurse
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        fix_red_red(grandparent);
      } else {
        // Else perform LR, LL, RL, RR
        if (parent->is_left_child()) {
          if (x->is_left_child()) {
            // for left right
            colors_flip(parent, grandparent);
          } else {
            del_left_rotate(parent);
            colors_flip(x, grandparent);
          }
          // for left left and left right
          del_right_rotate(grandparent);
        } else {
          if (x->is_left_child()) {
            // for right left
            del_right_rotate(parent);
            colors_flip(x, grandparent);
          } else {
            colors_flip(parent, grandparent);
          }

          // for right right and right left
          del_left_rotate(grandparent);
        }
      }
    }
}

/* Flip the colors */
  void RBTree::colors_flip(RBNode *x1, RBNode *x2) {
    int temp;
    temp = x1->get_color();
    x1->color = x2->get_color();
    x2->color = temp;
  }

  /* Swaps actual nodes with its parent and children pointer
  * not just values */
  void RBTree::values_flip(RBNode *u, RBNode *v) {

    // just swap actual nodes
    // in order to retain their original addresses
    // since Min heap access their address.
    int root_detected = 0, v_left_child = 0;
    //cout<<"Swapping nodes with values : "<<u->get_building()->get_building_num()<<" & "<<v->get_building()->get_building_num()<<endl;
    if(v == RBRoot)
    {
        root_detected = 1;
    }
    RBNode * temp_parent = v->get_parent();
    RBNode * temp_left = v->get_left();
    RBNode * temp_right = v->get_right();

    // if u is child of v
    if (v->right == u)
    {
        if(temp_parent != NULL)
        {
            if(v->is_left_child())
            {
                temp_parent->left = u;
            }
            else{
                temp_parent->right = u;
            }
        }
        if(temp_left != NULL)
        {
            temp_left->parent = u;
            //cout<<"temp_left val = "<<temp_left->get_building()->building_num<<"parent = u val = "<<u->get_building()->building_num<<endl;
        }
        // no need to change right child since u itself is the right child.
        v->right = u->right;
        v->left = u->left;
        v->parent = u;
        // no need of v->parent = u->parent because will cause self loop
        u->parent = temp_parent;
        u->left = temp_left;
        //u->right = temp_right; not needed it will go in selfloop

    }
    else{

    if( (!root_detected) && v->is_left_child())
    {
        v_left_child = 1;
    }

    v->parent = u->parent; //itself
    v->left = u->left;
    v->right = u->right;

    if(u->right != NULL)
    {
        u->right->parent = v;
    }
    if(u->is_left_child())
    {
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }

    u->parent = temp_parent;
    u->left = temp_left;
    u->right = temp_right;
    //cout<<"----- u val :"<<u->get_building()->building_num<<" and right = tmep_right : "<<temp_right->get_building()->get_building_num()<<endl;

    if(!root_detected)
    {
        if(v_left_child)
        {
            temp_parent->left = u;
        }
        else
        {
            temp_parent->right = u;
        }
    }
    if(u->left != NULL)
    {
        u->left->parent = u;
    }
    if(u->right != NULL)
    {
       u->right->parent = u;
    }
    }
    if(root_detected)
    {
        RBRoot = u;
    }


  }

    // left rotates the given node
  void RBTree::del_left_rotate(RBNode *x) {
    // new parent will be node's right child
    RBNode *new_parent = x->get_right();

    // update RBRoot if current node is RBRoot
    if (x == RBRoot)
      RBRoot = new_parent;

    x->move_down(new_parent);

    // connect x with new parent's left element
    x->right = new_parent->get_left();
    // connect new parent's left element with node
    // if it is not null
    if (new_parent->get_left() != NULL)
      new_parent->left->parent = x;

    // connect new parent with x
    new_parent->left = x;
  }

  void RBTree::del_right_rotate(RBNode *x) {
    // new parent will be node's left child
    RBNode *new_parent = x->get_left();

    // update RBRoot if current node is RBRoot
    if (x == RBRoot)
      RBRoot = new_parent;

    x->move_down(new_parent);

    // connect x with new parent's right element
    x->left = new_parent->right;
    // connect new parent's right element with node
    // if it is not null
    if (new_parent->get_right() != NULL)
      new_parent->right->parent = x;

    // connect new parent with x
    new_parent->right = x;
  }

  /* Prints and writed in file Building with id passed as argument */
  void RBTree :: print_single_building(int bldg_id)
  {
        cout<<"________________________________________________________"<<endl;
        if(RBRoot == NULL)
        {
            cout<<"\nERROR : Cannot print RBTree is empty"<<endl;
            return;
        }
        RBNode * ret = search(bldg_id);
        // If no matching BID is found prints (0,0,0)
        if(ret->get_building()->get_building_num() != bldg_id)
        {
            cout<<"\n Print Error : Cannot find Building : "<<bldg_id<<endl;
            cout<<"(0,0,0)"<<endl;
            op<<days_timer<<" : (0,0,0)"<<endl;
        }
        else
        {
            cout<<"\n"<<days_timer<<": _________ Print single building cmd ______________"<<endl;
            cout<<"\n("<<ret->get_building()->get_building_num()<<","
                    <<ret->get_building()->get_executed_time()<<","
                    <<ret->get_building()->get_total_time()<<")"<<endl;
            op<<days_timer<<" : ("<<ret->get_building()->get_building_num()<<","
                    <<ret->get_building()->get_executed_time()<<","
                    <<ret->get_building()->get_total_time()<<")"<<endl;

        }
        cout<<"________________________________________________________\n\n"<<endl;

  }

  /* Prints and writes in file all buildings in the given range start to end */
  void RBTree :: print_building_range(int start, int end)
  {
        string to_write; // String to be written to the file
        cout<<"\n"<<days_timer<<":________________________________________________________"<<endl;
        cout<<"\n Inside print range building for "<<start<<" and "<<end<<endl;
        if(RBRoot == NULL)
        {
            cout<<"\nERROR : Cannot print RBTree is empty"<<endl;
            return;
        }
        string ret = this->inorder_aux_range(this->RBRoot, start, end);
        if(ret.length() == 0)// if no building found in given range
        {
            to_write = "(0,0,0)";
            cout<<"\n NO building found in this range\n"<<endl;
        }
        else
        {
            to_write = ret.substr(START_POS, ret.length()); // to remove initial extra comma
        }
        op<<days_timer<<" : "<<to_write<<endl; // to print on next line

        cout<<"\n________________________________________________________\n\n"<<endl;

  }
