#ifndef RBTREE_HPP
#define RBTREE_HPP

enum class Color { RED, BLACK, DOUBLE_BLACK };

struct node {
  int data;
  Color color;
  node *left, *right, *parent;

  node(int d)
      : data{d}, color{Color::RED}, left{nullptr}, right{nullptr},
        parent{nullptr} {}
};

class RBtree {
private:
  node *root;

protected:
  void rotate_left(node *&);
  void rotate_right(node *&);
  void fix_insert(node *&);
  void fix_delete(node *&);
  void inorder_bst(node *&);
  void preorder_bst(node *&);
  Color get_color(node *&);
  void set_color(node *&, Color);
  node *min_value_node(node *&);
  node *max_value_node(node *&);
  node *insert_bst(node *&, node *&);
  node *delete_bst(node *&, Color);
  int get_black_height(node *);

public:
  RBtree();
  ~RBtree() = default;

  void insert_value(int);
  void delete_value(int);
  void merge(RBtree);
  void inorder();
  void preorder();
};

#endif