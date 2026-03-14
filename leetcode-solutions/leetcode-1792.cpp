/**
 * 1792. Maximum Average Pass Ratio
 * 
 * There is a school that has classes of students and each class will be having a final exam. You are given a 2D integer array classes, where classes[i] = [passi, totali]. You know beforehand that in the ith class, there are totali total students, but only passi number of students will pass the exam.
 * 
 * You are also given an integer extraStudents. There are another extraStudents brilliant students that are guaranteed to pass the exam of any class they are assigned to. You want to assign each of the extraStudents students to a class in a way that maximizes the average pass ratio across all the classes.
 * 
 * The pass ratio of a class is equal to the number of students of the class that will pass the exam divided by the total number of students of the class. The average pass ratio is the sum of pass ratios of all the classes divided by the number of the classes.
 * 
 * Example 1:
 * 
 * Input: classes = [[1,2],[3,5],[2,2]], extraStudents = 2
 * Output: 0.78333
 * Explanation: You can assign the two extra students to the first class. The average pass ratio will be equal to (3/4 + 3/5 + 2/2) / 3 = 0.78333.
 * Example 2:
 * 
 * Input: classes = [[2,4],[3,9],[4,5],[2,10]], extraStudents = 4
 * Output: 0.53485
 *  
 * 
 * Constraints:
 * 
 * 1 <= classes.length <= 105
 * classes[i].length == 2
 * 1 <= passi <= totali <= 105
 * 1 <= extraStudents <= 105
 */
class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        int n = classes.size();
        // lambda to compute the gain in pass ratio when adding one student
        auto gain = [](long long p, long long t) -> double {
            return (double)(p + 1) / (t + 1) - (double)p / t;
        };

        // max-heap: store (gain, (pass, total))
        priority_queue<pair<double, pair<int, int>>> pq;

        for (auto& c : classes) {
            int p = c[0], t = c[1];
            pq.push({gain(p, t), {p, t}});
        }

        // distribute extra students one by one
        while (extraStudents-- > 0) {
            auto [g, pt] = pq.top(); pq.pop();
            int p = pt.first, t = pt.second;
            ++p; ++t;                           // add one student
            pq.push({gain(p, t), {p, t}});
        }

        // compute the final average pass ratio
        double sum = 0.0;
        while (!pq.empty()) {
            auto [g, pt] = pq.top(); pq.pop();
            int p = pt.first, t = pt.second;
            sum += (double)p / t;
        }
        return sum / n;
    }
};