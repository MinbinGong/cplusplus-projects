#include <cstdio>
#include <cstdlib>
using namespace std;

int solution(int M, int A[], int N)
{
	int *counter = new int[M + 1];
	int i;
	for (i = 0; i <= M; i++)
	{
		counter[i] = 0;
	}

	int maxOccurrence = 1;
	int index = -1;
	for (i = 0; i < N; ++i)
	{
		if (counter[A[i]] > 0)
		{
			int tmp = counter[A[i]];
			if (tmp > maxOccurrence) {
				maxOccurrence = tmp + 1;
				index = i;
			}
			counter[A[i]] = tmp + 1;
		}
		else {
			counter[A[i]] = 1;
		}
	}
	return A[index];
}


int main()
{
	int a[7]{ 1,2,3,4,1,1,5 };

	int ret = solution(5, a, 7);

	return 0;
}