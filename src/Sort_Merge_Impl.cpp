// 归并排序 递归
/*
通过不断的将两个有序的数组进行合并，最终得到一个有序的数组
*/

#include <iostream>
#include <vector>
using namespace std;

// merge：合并两个相邻的有序区间
//   左区间：[left, mid]
//   右区间：[mid + 1, right]
// 合并结果先写入 tmp，再整体拷回 a

void merge(vector<int> &a, vector<int> &tmp, int left, int mid, int right) {
  int i = left;    // 左区间当前指针
  int j = mid + 1; // 右区间当前指针
  int k = left;    // 临时数组写入位置

  // 1. 两个区间都还有元素时，取较小者放入 tmp
  while (i <= mid && j <= right) {
    if (a[i] <= a[j]) {
      tmp[k++] = a[i++]; // 左边更小（<= 保证稳定性）
    } else {
      tmp[k++] = a[j++]; // 右边更小
    }
  }

  // 2. 左区间剩余元素直接搬过去
  while (i <= mid) {
    tmp[k++] = a[i++];
  }

  // 3. 右区间剩余元素直接搬过去
  while (j <= right) {
    tmp[k++] = a[j++];
  }

  // 4. 把合并好的结果从 tmp 拷回原数组
  for (int p = left; p <= right; ++p) {
    a[p] = tmp[p];
  }
}

// mergeSortImpl：递归排序区间 [left, right]

void mergeSortImpl(vector<int> &a, vector<int> &tmp, int left, int right) {
  // 递归终止条件：区间只有一个元素（或为空），天然有序
  if (left >= right) {
    return;
  }

  // 取中点，拆分区间（这样写可防止 left + right 溢出）
  int mid = left + (right - left) / 2;

  // 递归排序左半部分
  mergeSortImpl(a, tmp, left, mid);

  // 递归排序右半部分
  mergeSortImpl(a, tmp, mid + 1, right);

  // 合并两个已排好序的半区间
  merge(a, tmp, left, mid, right);
}

// mergeSort：对外接口

void mergeSort(vector<int> &a) {
  if (a.size() < 2) {
    return;
  }
  vector<int> tmp(a.size()); // 临时数组，只分配一次
  mergeSortImpl(a, tmp, 0, (int)a.size() - 1);
}

int main() {
  vector<int> v = {5, 2, 9, 1, 5, 6, 3, 8, 0, 7};

  mergeSort(v);

  for (int x : v) {
    cout << x << ' ';
  }
  cout << '\n';

  return 0;
}