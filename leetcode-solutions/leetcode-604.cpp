/*
 * Design Compressed String Iterator
 * 
 * Design and implement a data structure for a compressed string iterator.
 * It should support the following operations: next and hasNext.
 * 
 * The given compressed string will be in the form of each letter followed by a positive integer representing the number of this letter existing in the original uncompressed string.
 * Next should return the next character if the decompressed string is not empty.
 * Otherwise, it should return a white space.
 * 
 * Example:
 * 
 * StringIterator iterator = new StringIterator("L1e2t1C1o1d1e1");
 * 
 * iterator.next(); // return 'L'
 * iterator.next(); // return 'e'
 * iterator.next(); // return 'e'
 * iterator.next(); // return 't'
 * iterator.next(); // return 'C'
 * iterator.next(); // return 'o'
 * iterator.next(); // return 'd'
 * iterator.hasNext(); // return true
 * iterator.next(); // return 'e'
 * iterator.hasNext(); // return false
 * iterator.next(); // return ' '
 * 
 * Note:
 * 1 <= compressedString.length <= 1000
 * compressedString consists of lower-case an upper-case English letters and digits.
 * The number of a single character repetitions in compressedString is in the range [1, 10^9]
 * At most 100 calls will be made to next and hasNext.
 * 
 */
#include <string>
using namespace std;

class StringIterator {
public:
    StringIterator(string compressedString) {
        str = compressedString;
        index = 0;
        cur = ' ';
        count = 0;
    }
    
    char next() {
        if (!hasNext()) {
            return ' ';
        }
        if (count > 0) {
            count--;
            return cur;
        }
        // 解析新的字符和数字（可能出现多位数）
        cur = str[index++];
        while (index < str.size() && isdigit(str[index])) {
            count = count * 10 + (str[index] - '0');
            index++;
        }
        count--; // 返回当前字符，消耗一次
        return cur;
    }
    
    bool hasNext() {
        return index < str.size() || count > 0;
    }

private:
    string str;
    int index;      // 当前解析位置
    char cur;       // 当前字符
    int count;      // 当前字符剩余次数
};