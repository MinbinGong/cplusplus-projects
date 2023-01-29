#ifndef UNIVERSAL_HASHING_HPP
#define UNIVERSAL_HASHING_HPP

const int DIGS = 31;
const int mersennep = (1 << DIGS) - 1;

int universalHash(int x, int A, int B, int M)
{
    long long hashVal = static_cast<long long>(A) * x + B;

    hashVal = ((hashVal >> DIGS) + (hashVal & mersennep));
    if (hashVal >= mersennep)
        hashVal -= mersennep;
    return static_cast<int>(hashVal) % M;
}

#endif