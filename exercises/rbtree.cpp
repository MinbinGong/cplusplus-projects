#include "rbtree.hpp"
#include <bits/stdc++.h>

RBtree::RBtree() : root{nullptr} {}

Color RBtree::get_color(node *&node) {
  if (nullptr == node) {
    return Color::BLACK;
  }
  return node->color;
}

void RBtree::set_color(node *&node, Color c) {
  if (nullptr == node) {
    return;
  }
  node->color = c;
}

node *RBtree::insert_bst(node *&root, node *&ptr) {
  if (nullptr == root) {
    return ptr;
  }

  if (ptr->data == root->data) {
    return root;
  }

  if (ptr->data < root->data) {
    root->left = insert_bst(root->left, ptr);
    root->left->parent = root;
    return root;
  }

  root->right = insert_bst(root->right, ptr);
  root->right->parent = root;
  return root;
}

void RBtree::insert_value(int n) {
  node *node = new node(n);
  root = insert_bst(root, node);
  fix_insert(node);
}

void RBtree::rotate_left(node *&ptr) {
  node *right_child = ptr->right;
  ptr->right = right_child->left;

  if (nullptr != ptr->right) {
    ptr->right->parent = ptr;
  }

  right_child->parent = ptr->parent;

  if (ptr->parent == nullptr) {
    root = right_child;
  } else if (ptr == ptr->parent->left) {
    ptr->parent->left = right_child;
  } else {
    ptr->parent->right = right_child;
  }

  right_child->left = ptr;
  ptr->parent = right_child;
}

void RBtree::rotate_right(node *&ptr) {
  node *left_child = ptr->left;
  ptr->left = left_child->right;

  if (nullptr != ptr->left) {
    ptr->left->parent = ptr;
  }

  left_child->parent = ptr->parent;

  if (nullptr == ptr->parent) {
    root = left_child;
  } else if (ptr == ptr->parent->left) {
    ptr->parent->left = left_child;
  } else {
    ptr->parent->right = left_child;
  }

  left_child->right = ptr;
  ptr->parent = left_child;
}

void RBtree::fix_insert(node *&ptr) {
  node *parent{nullptr}, *grand_parent{nullptr};

  while (ptr != root && get_color(ptr) == Color::RED &&
         get_color(ptr->parent) == Color::RED) {
    parent = ptr->parent;
    grand_parent = parent->parent;

    if (parent == grand_parent->left) {
      node *uncle = grand_parent->right;
      if (Color::RED == get_color(uncle)) {
        set_color(uncle, Color::BLACK);
        set_color(parent, Color::BLACK);
        set_color(grand_parent, Color::RED);
        ptr = grand_parent;
      } else {
        if (ptr == parent->right) {
          rotate_left(parent);
          ptr = parent;
          parent = ptr->parent;
        }
        rotate_right(grand_parent);
        std::swap(parent->color, grand_parent->color);
        ptr = parent;
      }
    } else {
      node *uncle = grand_parent->left;
      if (get_color(uncle) == Color::RED) {
        set_color(uncle, Color::BLACK);
        set_color(parent, Color::BLACK);
        set_color(grand_parent, Color::RED);
        ptr = grand_parent;
      } else {
        if (ptr == parent->left) {
          rotate_right(parent);
          ptr = parent;
          parent = ptr->parent;
        }

        rotate_left(grand_parent);
        std::swap(parent->color, grand_parent->color);
        ptr = parent;
      }
    }
  }

  set_color(root, Color::BLACK);
}

void RBtree::fix_delete(node *&node) {
  if (nullptr == node) {
    return;
  }

  if (node == root) {
    root = nullptr;
    return;
  }

  if (get_color(node) == Color::RED || get_color(node->left) == Color::RED ||
      get_color(node->right) == Color::RED) {
    node *child = node->left != nullptr ? node->left : node->right;

    if (node == node->parent->left) {
      node->parent->left = child;
      if (nullptr != child) {
        child->parent = node->parent;
      }

      set_color(child, Color::BLACK);
      delete (node);
    } else {
      node->parent->right = child;
      if (nullptr != child) {
        child->parent = node->parent;
      }
      set_color(child, Color::BLACK);
      delete (node);
    }
  } else {
    node *sibling = nullptr, *parent = nullptr;
    node *ptr = node;
    set_color(ptr, Color::DOUBLE_BLACK);

    while (ptr != root && get_color(ptr) == Color::DOUBLE_BLACK) {
      parent = ptr->parent;
      if (ptr == parent->left) {
        sibling = parent->right;
        if (get_color(sibling) == Color::RED) {
          set_color(sibling, Color::BLACK);
          set_color(parent, Color::RED);
          rotate_left(parent);
        } else {
          if (get_color(sibling->left) == Color::BLACK &&
              get_color(sibling->right) == Color::BLACK) {
            set_color(sibling, Color::RED);
            if (get_color(parent) == Color::RED) {
              set_color(parent, Color::BLACK);
            } else {
              set_color(parent, Color::DOUBLE_BLACK);
            }
            ptr = parent;
          } else {
            if (get_color(sibling->right) == Color::BLACK) {
              set_color(sibling->left, Color::BLACK);
              set_color(sibling, Color::RED);
              rotate_right(sibling);
              sibling = parent->right;
            }

            set_color(sibling, parent->color);
            set_color(parent, Color::BLACK);
            set_color(sibling->right, Color::BLACK);
            rotate_left(parent);
            break;
          }
        }
      } else {
        sibling = parent->left;
        if (get_color(sibling) == Color::RED) {
          set_color(sibling, Color::BLACK);
          set_color(parent, Color::RED);
          rotate_right(parent);
        } else {
          if (get_color(sibling->left) == Color::BLACK &&
              get_color(sibling->right) == Color::BLACK) {
            set_color(sibling, Color::RED);
            if (get_color(parent) == Color::RED) {
              set_color(parent, Color::BLACK);
            } else {
              set_color(parent, Color::DOUBLE_BLACK);
            }
            ptr = parent;
          } else {
            if (get_color(sibling->left) == Color::BLACK) {
              set_color(sibling->right, Color::BLACK);
              set_color(sibling, Color::RED);
              rotate_left(sibling);
              sibling = parent->left;
            }

            set_color(sibling, parent->color);
            set_color(sibling, Color::RED);
            set_color(sibling->left, Color::BLACK);
            rotate_right(parent);
            break;
          }
        }
      }
    }

    if (node == node->parent->left) {
      node->parent->left = nullptr;
    } else {
      node->parent->right = nullptr;
    }
    delete (node);
    set_color(root, Color::BLACK);
  }
}

node *RBtree::delete_bst(node *&root, int data) {
  if (nullptr == root) {
    return root;
  }

  if (data < root->data) {
    return delete_bst(root->left, data);
  }

  if (data > root->data) {
    return delete_bst(root->right, data);
  }

  if (root->left == nullptr || root->root == nullptr) {
    return root;
  }

  node *temp = min_value_node(root->right);
  root->data = temp->data;
  return delete_bst(root->right, temp->data);
}

void RBtree::delete_value(int data) {
  node *node = delete_bst(root, data);
  fix_delete(node);
}

void RBtree::inorder_bst(node *&ptr) {
  if (nullptr == ptr) {
    return;
  }

  return;
}

void RBtree::inorder() { inorder_bst(root); }

void RBtree::preorder_bst(node *&ptr) {
  if (nullptr == ptr) {
    return;
  }

  return;
}

void RBtree::preorder() { preorder_bst(root); }

node *RBtree::min_value_node(node *&node) {
  node *ptr = node;
  while (ptr->left != nullptr) {
    ptr = ptr->left;
  }
  return ptr;
}

node *RBtree::max_value_node(node *&node) {
  node *ptr = node;
  while (ptr->right != nullptr) {
    ptr = ptr->right;
  }

  return ptr;
}

int RBtree::get_black_height(node *node) {
  int black_height = 0;
  while (node != nullptr) {
    if (get_color(node) == Color::BLACK) {
      black_height++;
    }
    node = node->left;
  }

  return black_height;
}

void RBtree::merge(RBtree &tree2) {
  int temp;
  node *c, *temp_ptr;
  node *root1 = root;
  node *root2 = tree2.root;
  int initial_black_height1 = get_black_height(root1);
  int initial_black_height2 = get_black_height(root2);
  if (initial_black_height1 > initial_black_height2) {
    c = max_value_node(root1);
    temp = c->data;
    delete_value(c->data);
    root1 = root;
  } else if (initial_black_height1 < initial_black_height2) {
    c = min_value_node(root2);
    temp = c->data;
    tree2.delete_value(c->data);
    root2 = tree2.root;
  } else {
    c = min_value_node(root2);
    temp = c->data;
    tree2.delete_value(c->data);
    root2 = tree2.root;
    if (initial_black_height1 != get_black_height(root2)) {
      tree2.insert_value(c->data);
      root2 = tree2.root;
      c = max_value_node(root1);
      temp = c->data;
      delete_value(c->data);
      root1 = root;
    }
  }

  set_color(c, Color::RED);
  int final_black_height1 = get_black_height(root1);
  int final_black_height2 = get_black_height(root2);
  if (final_black_height1 == final_black_height2) {
    c->left = root1;
    root1->parent = c;
    c->right = root2;
    root2->parent = c;
    set_color(c, Color::BLACK);
    c->data = temp;
    root = c;
  } else if (final_black_height1 < final_black_height2) {
    node *ptr = root2;

    while (final_black_height1 != get_black_height(ptr)) {
      temp_ptr = ptr;
      ptr = ptr->left;
    }

    node *ptr_parent;
    if (ptr == nullptr) {
      ptr_parent = temp_ptr;
    } else {
      ptr_parent = ptr->parent;
    }

    c->left = root1;
    if (root1 != nullptr) {
      root1->parent = c;
    }
    c->right = ptr;
    if (ptr != nullptr) {
      ptr->parent = c;
    }

    ptr_parent->left = c;
    c->parent = ptr_parent;
    if (get_color(ptr_parent) == Color::RED) {
      fix_insert(c);
    } else if (get_color(ptr) == Color::RED) {
      fix_insert(ptr);
    }

    c->data = temp;
    root = root2;
  } else {
    node *ptr = root1;
    while (final_black_height2 != get_black_height(ptr)) {
      ptr = ptr->right;
    }
    node *ptr_parent = ptr->parent;
    c->right = root2;
    root2->parent = c;
    c->left = ptr;
    ptr->parent = c;
    ptr_parent->right = c;
    c->parent = ptr_parent;
    if (get_color(ptr_parent) == Color::RED) {
      fix_insert(c);
    } else if (get_color(ptr) == Color::RED) {
      fix_insert(ptr);
    }

    c->data = temp;
    root = root1;
  }
  return;
}
