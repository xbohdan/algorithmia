#include <iostream>

using namespace std;

int iParent(int i)
{
	return (i - 1) / 2;
}

int iLeftChild(int i)
{
	return 2 * i + 1;
}

int iRightChild(int i)
{
	return 2 * i + 2;
}

void siftDown(int* a, int start, int end)
{
	int root = start;
	while (iLeftChild(root) <= end) {
		int child = iLeftChild(root);
		int temp = root;
		if (a[temp] < a[child])
			temp = child;
		if (child + 1 <= end and a[temp] < a[child + 1])
			temp = child + 1;
		if (temp == root)
			return;
		swap(a[root], a[temp]);
		root = temp;
	}
}

void heapify(int* a, int count)
{
	int start = iParent(count - 1);
	while (start >= 0) {
		siftDown(a, start, count - 1);
		--start;
	}
}

void heapsort(int* a, int count)
{
	heapify(a, count);
	int end = count - 1;
	while (end > 0) {
		swap(a[end], a[0]);
		--end;
		siftDown(a, 0, end);
	}
}

int main()
{
	const int count = 7;
	int a[] = { 2, 4, 1, 3, 5, 7, 6 };
	heapsort(a, count);
	for (int i = 0; i < count; ++i)
		cout << a[i] << ' ';
	cout << '\n';
	return 0;
}