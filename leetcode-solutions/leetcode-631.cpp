/*
 * Design Excel Sum Formula
 * 
 * Your task is to design the basic function of Excel and implement the function of sum formula.
 * Specifically, you need to implement the following functions:
 *  
 * Excel(int n, char firstColumn) : A 2D array with n rows and columns labeled from firstColumn to firstColumn + n - 1.
 * The 2D array is initialized to be zero.
 * 
 * void set(int row, char column, int val) : Sets the value of cell with the label column + row to be val.
 * 
 * int get(int row, char column) : Returns the value of the cell with the label column + row.
 * 
 * int sum(int row, char column, List of Strings : numbers) : Returns the sum of the values of cells with labels in the
 * list numbers. This sum formula should exist until this cell is overlapped by another value or another sum formula.
 * 
 * numbers is a list of strings that each string is either a cell label or a range of cells labels.
 * 
 * Example 1:
 * Input: 
 * ["Excel","set","sum","set","get"]
 * [[3,"A"],[1,"A",2],[3,"A",["A1","A1:B2"]],[2,"B",2],[3,"A"]]
 * Output: 
 * [null,null,4,null,6]
 * 
 * Explanation:
 * Excel excel = new Excel(3, "A");
 *  // construct a 3*3 2D array with all zero.
 *  //   A B C
 *  // 1 0 0 0
 *  // 2 0 0 0
 *  // 3 0 0 0
 * excel.set(1, "A", 2);
 *  // set A1 to be 2.
 *  //   A B C
 *  // 1 2 0 0
 *  // 2 0 0 0
 *  // 3 0 0 0
 * excel.sum(3, "A", ["A1", "A1:B2"]);
 *  // sum of A1 and A1:B2 will be 4.
 *  //   A B C
 *  // 1 2 0 0
 *  // 2 0 0 0
 *  // 3 0 0 4
 * excel.set(2, "B", 2);
 *  // set B2 to be 2.
 *  //   A B C
 *  // 1 2 0 0
 *  // 2 0 2 0
 *  // 3 0 0 4
 * excel.get(3, "A");
 *  // return 6
 * 
 * Constraints:
 * 1 <= n <= 26
 * 'A' <= firstColumn <= 'Z'
 * 1 <= row <= n
 * 'A' <= column <= 'Z'
 * -100 <= val <= 100
 * 1 <= numbers.length <= 5
 * numbers[i] has the format "ColRow" or "ColRow1:ColRow2".
 * At most 100 calls will be made to set, get, and sum.
 * 
 */
#include <vector>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <cctype>

using namespace std;

class Excel {
public:
    // 构造函数：初始化 H 行，宽度为从 'A' 到 W 的列
    Excel(int H, char W) {
        // 调整矩阵大小，行索引从1开始方便使用，所以size为 H+1
        // 列索引将字符映射为数字，例如 'A' -> 1，因此列数需要计算
        int cols = W - 'A' + 1;
        // 初始化一个 (H+1) x (cols+1) 的矩阵，默认值为0
        data = vector<vector<int>>(H + 1, vector<int>(cols + 1, 0));
    }

    // 设置单元格的值，并移除其可能存在的公式
    void set(int r, char c, int v) {
        int colIdx = c - 'A' + 1;
        data[r][colIdx] = v;
        // 移除该单元格的公式映射
        formulaMap.erase({r, colIdx});
    }

    // 获取单元格的值，如果是公式单元格，则先重新计算
    int get(int r, char c) {
        int colIdx = c - 'A' + 1;
        // 如果该单元格有公式，重新计算并返回值
        if (formulaMap.find({r, colIdx}) != formulaMap.end()) {
            return sum(r, c, formulaMap[{r, colIdx}]);
        }
        return data[r][colIdx];
    }

    // 为单元格设置求和公式，并返回计算结果
    int sum(int r, char c, vector<string> strs) {
        int colIdx = c - 'A' + 1;
        // 保存公式字符串
        formulaMap[{r, colIdx}] = strs;

        int res = 0;
        for (const string& token : strs) {
            // 解析每一个表达式，可能是 "A1" 或 "A1:B2"
            size_t colonPos = token.find(':');
            if (colonPos == string::npos) {
                // 单个单元格
                res += getCellValue(token);
            } else {
                // 单元格范围
                string topLeft = token.substr(0, colonPos);
                string bottomRight = token.substr(colonPos + 1);

                auto [r1, c1] = parseCell(topLeft);
                auto [r2, c2] = parseCell(bottomRight);

                // 遍历矩形区域内的所有单元格并累加
                for (int row = r1; row <= r2; ++row) {
                    for (int col = c1; col <= c2; ++col) {
                        // 注意：这里调用 get(row, col) 是为了处理嵌套公式
                        res += get(row, col + 'A' - 1);
                    }
                }
            }
        }

        // 将计算结果存入数据矩阵，方便后续快速读取
        data[r][colIdx] = res;
        return res;
    }

private:
    // 数据矩阵，存储每个单元格当前的有效值
    vector<vector<int>> data;
    // 公式映射表，存储每个单元格的原始公式字符串
    map<pair<int, int>, vector<string>> formulaMap;

    // 解析类似 "A1" 的字符串，返回行号和列索引（列索引从1开始）
    pair<int, int> parseCell(const string& cell) {
        int col = cell[0] - 'A' + 1;
        int row = stoi(cell.substr(1));
        return {row, col};
    }

    // 根据字符串获取单元格的值（用于 sum 函数内部计算）
    int getCellValue(const string& token) {
        auto [row, col] = parseCell(token);
        return get(row, col + 'A' - 1);
    }
};