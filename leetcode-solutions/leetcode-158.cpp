/*
 * Read N Characters Given Read4 II - Call multiple times
 * 
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 * 
 * Return the number of actual characters read.
 * 
 * Constraints:
 * 1. 1 <= n <= 104
 * 2. buf has a length of at least n. 
 * 3. buf is guaranteed to have at least n characters.
 * 4. You can only call the read4 API once per call.
 * 5. You may not modify the values in the list's nodes. Only nodes themselves may be changed.
 * 6. buf is guaranteed to have at least n characters.
 */
/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

class Solution {
public:
    Solution() : readPtr(0), writePtr(0) {
        // 构造函数初始化，buffer 是成员变量，无需在此初始化
    }

    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        int idx = 0; // 当前写入 buf 的字符数

        // 1. 优先消耗内部缓冲区 buffer 中的字符
        while (idx < n && readPtr < writePtr) {
            buf[idx++] = buffer[readPtr++];
        }

        // 2. 如果内部缓冲区已空，则通过 read4 从文件补充
        while (idx < n) {
            // 用 read4 填充内部缓冲区
            writePtr = read4(buffer);
            readPtr = 0; // 重置读指针

            // 如果文件读完，read4 返回 0，则跳出循环
            if (writePtr == 0) break;

            // 将新读入的内部缓冲区字符复制到 buf 中
            while (idx < n && readPtr < writePtr) {
                buf[idx++] = buffer[readPtr++];
            }
        }

        return idx;
    }

private:
    char buffer[4];   // 内部缓冲区，用于存储从 read4 读来但未被消耗的字符
    int readPtr;      // 内部缓冲区的读指针 (指向下一个待读取的字符)
    int writePtr;     // 内部缓冲区的写指针 (指向有效数据的末尾，即有效字符数量)
};