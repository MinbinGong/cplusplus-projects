#include <algorithm>

bool int_ptr_less(int *a, int *b)
{
    return *a < *b;
}

int main()
{
    int x = 17, y = 42, z = 33;

    int *px = &x, *py = &y, *pz = &z;

    int *pmax = std::max(px, py, int_ptr_less);

    std::pair<int *, int *> extremes = std::minmax({px, py, pz}, int_ptr_less);

    return 0;
}