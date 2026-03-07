/*
 * 1628. Design an Expression Tree With Evaluate Function
 *
 * Given the postfix tokens of an arithmetic expression, build and return the binary expression tree that represents this expression.
 * 
 * Example 1:
 * Input: s = ["3","4","+","2","*","7","/"]
 * Output: 2
 * Explanation: this expression evaluates to the above binary tree with expression ((3+4)*2)/7) = 14/7 = 2.
 * 
 * Example 2:
 * Input: s = ["4","5","2","7","+","-","*"]
 * Output: -16
 * Explanation: this expression evaluates to the above binary tree with expression 4*(5-2)+7 = 4*3+7 = 13.
 * 
 * Constraints:
 * 1 <= s.length <= 100
 * s.length is odd.
 * s consists of numbers and the characters '+', '-', '*', and '/'.
 * If s[i] is a number, its integer representation is no more than 105.
 * It is guaranteed that s is a valid expression.
 * 
 */
#include <vector>
#include <stack>
#include <string>
using namespace std;

/**
 * This is the interface for the expression tree Node.
 * You should not remove it, and you can define some classes to implement it.
 */

class Node {
public:
    virtual ~Node() {};
    virtual int evaluate() const = 0;
};

class NumNode : public Node {
private:
    int val;
public:
    NumNode(int v) : val(v) {}
    int evaluate() const override { return val; }
};

class OpNode : public Node {
private:
    char op;
    Node* left;
    Node* right;
public:
    OpNode(char op, Node* l, Node* r) : op(op), left(l), right(r) {}
    ~OpNode() {
        delete left;
        delete right;
    }
    int evaluate() const override {
        int l = left->evaluate();
        int r = right->evaluate();
        switch (op) {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/': return l / r;
        }
        return 0;
    }
};

/**
 * This is the TreeBuilder class.
 * You can treat it as the driver code that takes the postinfix input 
 * and returns the expression tree represnting it as a Node.
 */

class TreeBuilder {
public:
    Node* buildTree(vector<string>& postfix) {
        stack<Node*> stk;
        for (const string& token : postfix) {
            if (isdigit(token[0])) {
                int val = stoi(token);
                stk.push(new NumNode(val));
            } else {
                Node* right = stk.top(); stk.pop();
                Node* left = stk.top(); stk.pop();
                stk.push(new OpNode(token[0], left, right));
            }
        }
        return stk.top();
    }
};