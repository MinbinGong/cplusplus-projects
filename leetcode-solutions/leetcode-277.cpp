/*
 * Find the Celebrity
 * 
 * Suppose you are at a party with n people labeled from 0 to n - 1 and among them, there may exist one celebrity. The definition of a celebrity is that all the other n - 1 people know the celebrity, but the celebrity does not know any of them.
 * 
 * Now you want to find out who the celebrity is or verify that there is not one. You are only allowed to ask questions like: "Hi, A. Do you know B?" to get information about whether A knows B. You need to find out the celebrity (or verify there is not one) by asking as few questions as possible (in the asymptotic sense).
 * 
 * You are given a helper function bool knows(a, b) that tells you whether a knows b. Implement a function int findCelebrity(n). There will be exactly one celebrity if they are at the party.
 * 
 * Return the celebrity's label if there is a celebrity at the party. If there is no celebrity, return -1.
 * 
 * Example 1:
 * Input: graph = [[1,1,0],[0,1,0],[1,1,1]]
 * Output: 1
 */

/* The knows API is defined for you.
      bool knows(int a, int b); */

class Solution {
public:
    int findCelebrity(int n) {
        // 第一阶段：筛选出唯一的候选人
        int candidate = 0;
        for (int i = 1; i < n; ++i) {
            if (knows(candidate, i)) {
                // 如果 candidate 认识 i，则 candidate 不是名人
                // 同时可以证明，从原 candidate 到 i 之间的所有人（不包括 i）也都不是名人
                candidate = i;  // i 成为新的候选人
            }
        }

        // 第二阶段：验证候选人是否是真正的名人
        for (int i = 0; i < n; ++i) {
            if (i == candidate) continue;
            // 检查候选人是否认识别人，或者有人不认识候选人
            if (knows(candidate, i) || !knows(i, candidate)) {
                return -1;  // 违反名人条件
            }
        }

        return candidate;
    }
};