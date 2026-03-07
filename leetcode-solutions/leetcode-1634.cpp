/*
 * 1634. Add Two Polynomials Represented as Linked Lists
 *
 * A polynomial linked list is a special type of linked list where every node represents a term in a polynomial expression.
 * 
 * Each node has three attributes:
 * coefficient: an integer representing the number multiplier of the term. The coefficient of the term 9x4 is 9.
 * power: an integer representing the exponent. The power of the term 9x4 is 4.
 * next: a pointer to the next node in the list, or null if it is the last node of the list.
 * 
 * For example, the linked list 1 + 3x + 2x^2 + 5x^3 is represented by the polynomial linked list pictured below:
 * 
 * Example 1:
 * Input: poly1 = [[1,1],[2,0],[3,2]], poly2 = [[4,3],[5,2]]
 * Output: [[5,3],[1,0],[3,2]]
 * Explanation: 5x^3 + 4x^3 + 3x^2 = 5x^3 + 4x^3 + 3x^2.
 * 
 * Example 2:
 * Input: poly1 = [[1,2]], poly2 = [[-1,2]]
 * Output: [[-1,2]]
 * Explanation: -1x^2 + 1x^2 = -1x^2.
 * 
 * Constraints:
 * 1 <= poly1.length, poly2.length <= 104
 * -109 <= poly1[i][0] <= 109
 * 1 <= poly1[i][1] <= 100
 * -109 <= poly2[i][0] <= 109
 * 1 <= poly2[i][1] <= 100
 * poly1 and poly2 are sorted by power in descending order.
 * 
 */
/**
 * Definition for polynomial singly-linked list.
 * struct PolyNode {
 *     int coefficient, power;
 *     PolyNode *next;
 *     PolyNode(): coefficient(0), power(0), next(nullptr) {};
 *     PolyNode(int x, int y): coefficient(x), power(y), next(nullptr) {};
 *     PolyNode(int x, int y, PolyNode* next): coefficient(x), power(y), next(next) {};
 * };
 */
struct PolyNode {
    int coefficient, power;
    PolyNode *next;
    PolyNode(): coefficient(0), power(0), next(nullptr) {};
    PolyNode(int x, int y): coefficient(x), power(y), next(nullptr) {};
    PolyNode(int x, int y, PolyNode* next): coefficient(x), power(y), next(next) {};
};

class Solution {
public:
    PolyNode* addPoly(PolyNode* poly1, PolyNode* poly2) {
        PolyNode dummy(0, 0);
        PolyNode* tail = &dummy;
        
        while (poly1 && poly2) {
            if (poly1->power > poly2->power) {
                tail->next = new PolyNode(poly1->coefficient, poly1->power);
                tail = tail->next;
                poly1 = poly1->next;
            } else if (poly1->power < poly2->power) {
                tail->next = new PolyNode(poly2->coefficient, poly2->power);
                tail = tail->next;
                poly2 = poly2->next;
            } else { // 幂相等
                int sum = poly1->coefficient + poly2->coefficient;
                if (sum != 0) {
                    tail->next = new PolyNode(sum, poly1->power);
                    tail = tail->next;
                }
                poly1 = poly1->next;
                poly2 = poly2->next;
            }
        }
        
        // 处理剩余节点
        tail->next = poly1 ? poly1 : poly2;
        
        return dummy.next;
    }
};