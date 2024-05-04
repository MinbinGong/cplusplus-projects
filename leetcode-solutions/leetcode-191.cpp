/*
 * Number of 1 Bits
 *
 * Write a function that takes the binary representation of a positive integer and returns the number of 
 * set bits it has (also known as the Hamming weight).
 */

int hammingWeight(uint32_t n) {
    int cnt = 0;
    while (n != 0) {
        cn += (n%2);
        n >>= 1;
    }
    return cnt;
}

