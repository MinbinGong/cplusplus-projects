#include <stdio.h>
#include <stdlib.h>

int threeSumClosest(int a[], int size, int target);

int main(void)
{
    int src[] = {0, 2, 1, -3};
    int target = 1;
    int ret = threeSumClosest(src, sizeof(src) / sizeof(src[0]), target);
    printf("The closest sum: %d\n", ret);

    return 0;
}

int threeSumClosest(int a[], int size, int target)
{
    int value = a[0] + a[1] + a[2];

    for (size_t i = 1; i < size - 2; i++)
    {
        if (abs(a[i] + a[i + 1] + a[i + 2] - target) < abs(value - target))
            value = a[i] + a[i + 1] + a[i + 2];
    }

    return value;
}