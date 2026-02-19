/*
 * Read N Characters Given Read4
 *
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 * 
 * Return the number of actual characters read.
 * 
 * Constraints:
 * 1. 1 <= n <= 104
 * 2. buf has a length of at least n. 
 */

/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

/**
 * @param buf Destination buffer
 * @param n   Number of characters to read
 * @return    The number of actual characters read
 */
int read(char *buf, int n) {
    int idx = 0;                     // 当前已写入 buf 的字符数
    char temp[4];                     // read4 的临时缓冲区

    while (idx < n) {
        int count = read4(temp);       // 从文件读取最多4个字符到 temp
        if (count == 0) break;         // 文件读取完毕

        // 计算本次实际需要从 temp 复制到 buf 的字符数
        int toRead = min(count, n - idx);
        for (int i = 0; i < toRead; ++i) {
            buf[idx++] = temp[i];
        }

        // 如果本次 read4 读取的字符数小于4，说明文件已到尾，无需继续
        if (count < 4) break;
    }
    return idx;
}
