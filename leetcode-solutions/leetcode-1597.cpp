/*
 * 1597. Build Binary Expression Tree From Infix Expression
 *
 * A binary expression tree is a kind of binary tree used to represent arithmetic expressions. Each node of a binary expression tree has either zero or two children. Leaf nodes (nodes with 0 children) correspond to operands (numbers), and internal nodes (nodes with two children) correspond to the operators '+' (addition), '-' (subtraction), '*' (multiplication), and '/' (division).
 *
 * For each internal node with operator o, the infix expression that it represents is (A o B), where A is the expression the left subtree represents and B is the expression the right subtree represents.
 *
 * You are given a string s, an infix expression containing operands, the operators described above, and parentheses '(' and ')'.
 *
 * Return any valid binary expression tree, whose in-order traversal reproduces s after omitting the parenthesis from it.
 *
 * Please note that order of operations applies in s. That is, expressions in parentheses are evaluated first, and multiplication and division happen before addition and subtraction.
 *
 * Example 1:
 * Input: s = "2-3/(5*2)+1"
 * Output: [+,-,1,2,/,null,null,null,null,3,*,null,null,5,2]
 * Explanation: The inorder traversal of the tree above is 2-3/5*2+1 which is the same as s without the parenthesis.
 * 
 * Example 2:
 * Input: s = "3+4*2/(1-5)"
 * Output: [+,-,*,3,4,/,null,null,null,null,1,5]
 * Explanation: The inorder traversal of the tree above is 3+4*2/(1-5) which is the same as s without the parenthesis.
 * 
 * Constraints:
 * 1 <= s.length <= 100
 * s consists of digits and the characters '+', '-', '*', '/', '(', and ')'.
 * Operands in s are exactly 1 digit.
 * It is guaranteed that s is a valid expression.
 * 
 */
/**
 * Definition for a binary tree node.
 * struct Node {
 *     char val;
 *     Node *left;
 *     Node *right;
 *     Node() : val(' '), left(nullptr), right(nullptr) {}
 *     Node(char x) : val(x), left(nullptr), right(nullptr) {}
 *     Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
 * };
 */

#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

struct Node {
    char val;
    Node *left;
    Node *right;
    Node() : val(' '), left(nullptr), right(nullptr) {}
    Node(char x) : val(x), left(nullptr), right(nullptr) {}
    Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    // 辅助函数：将运算符栈顶与节点栈顶的两个节点组合成一棵子树
    void combine(stack<Node*>& nodes, stack<char>& ops) {
        // 注意顺序：先弹出的是右子节点，后弹出的是左子节点
        Node* right = nodes.top(); nodes.pop();
        Node* left = nodes.top(); nodes.pop();
        char op = ops.top(); ops.pop();
        
        // 创建新的运算符节点，左右子树分别为 left 和 right
        Node* newNode = new Node(op, left, right);
        nodes.push(newNode);
    }
    
    // 获取运算符优先级
    int getPriority(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0; // 对于 '(' 优先级最低，便于处理
    }

public:
    Node* expTree(string s) {
        stack<Node*> nodes;  // 节点栈，存储操作数节点或已经构建好的子树根节点
        stack<char> ops;     // 运算符栈，存储运算符和左括号
        
        for (char c : s) {
            if (isdigit(c)) {
                // 操作数：直接作为叶子节点入节点栈
                nodes.push(new Node(c));
            } else if (c == '(') {
                // 左括号：直接入运算符栈
                ops.push(c);
            } else if (c == ')') {
                // 右括号：触发计算，直到遇到左括号
                while (!ops.empty() && ops.top() != '(') {
                    combine(nodes, ops);
                }
                ops.pop(); // 弹出左括号
            } else {
                // 运算符：+ - * /
                // 如果当前运算符优先级 <= 栈顶运算符优先级，则需要先计算栈顶
                while (!ops.empty() && getPriority(ops.top()) >= getPriority(c)) {
                    combine(nodes, ops);
                }
                ops.push(c);
            }
        }
        
        // 处理剩余未计算的运算符
        while (!ops.empty()) {
            combine(nodes, ops);
        }
        
        // 节点栈中剩下的唯一节点就是整个表达式的根节点
        return nodes.top();
    }
};