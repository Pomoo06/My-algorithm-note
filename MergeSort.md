# 归并排序：从思路到代码

> 本文按「先讲地基 → 再讲拆解 → 最后讲两种落地方式」的顺序，完整梳理归并排序的实现过程。

---

## 目录

- [一、核心思路：分治](#一核心思路分治)
- [二、地基：合并两个有序段](#二地基合并两个有序段)
- [三、递归版：自顶向下](#三递归版自顶向下)
- [四、迭代版：自底向上](#四迭代版自底向上)
- [五、两种版本的本质差别](#五两种版本的本质差别)
- [六、总结](#六总结)

---

## 一、核心思路：分治

给一个长度为 n 的数组排序，直接排很难。但有一个操作**非常简单**：

> **把两个已经有序的数组，合并成一个有序数组。**

这个操作只需 O(n) 时间，且逻辑直观。归并排序的全部思想就一句话：

> **先把数组拆到只剩单个元素（天然有序），再一层层把有序的小段合并回有序的大段。**

拆解过程：

```
[5,2,9,1,5,6,3,8]
   ↓ 对半拆
[5,2,9,1]   [5,6,3,8]
   ↓ 继续拆
[5,2] [9,1]  [5,6] [3,8]
   ↓ 拆到单个
[5][2][9][1][5][6][3][8]
   ↓ 两两合并（每步都是合并两个有序段）
[2,5] [1,9] [5,6] [3,8]
   ↓
[1,2,5,9] [3,5,6,8]
   ↓
[1,2,3,5,5,6,8,9]
```

所以整个算法只需要解决两个问题：

1. **怎么合并两个有序段**（地基）
2. **怎么组织「拆」和「合」的流程**（递归 or 迭代）

---

## 二、地基：合并两个有序段

假设数组 `a` 中，`[left, mid]` 和 `[mid+1, right]` 两段各自已有序，要把它们合并成整段有序。

### 2.1 双指针扫描

用 `i` 指向左段头，`j` 指向右段头。每一步比较 `a[i]` 和 `a[j]`，取小的那个放进结果，对应指针后移：

```
左段 [1,3,5]   右段 [2,4,6]
 i              j
比较 1 vs 2 → 取 1，i 后移
比较 3 vs 2 → 取 2，j 后移
比较 3 vs 4 → 取 3，i 后移
...
```

### 2.2 为什么需要临时数组 `tmp`？

**关键问题**：如果直接把较小值写回 `a`，会覆盖还没处理的值。

左右两段都存放在 `a` 的连续区间里。当你要把右段的元素写到左侧位置时，`a` 中原本的值可能还没被处理。所以必须**先把结果写到辅助数组 `tmp`，扫描完再整体拷回 `a`**。这就是 `merge` 里 `tmp` 存在的唯一原因。

### 2.3 merge 的四个步骤

```cpp
void merge(vector<int>& a, vector<int>& tmp, int left, int mid, int right) {
    int i = left;      // 左段指针
    int j = mid + 1;   // 右段指针
    int k = left;      // 写入 tmp 的位置

    // 步骤 1：两段都有元素，取较小者写入 tmp
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else              tmp[k++] = a[j++];
    }

    // 步骤 2：左段剩余，直接搬
    while (i <= mid) tmp[k++] = a[i++];

    // 步骤 3：右段剩余，直接搬
    while (j <= right) tmp[k++] = a[j++];

    // 步骤 4：结果拷回原数组
    for (int p = left; p <= right; ++p) a[p] = tmp[p];
}
```

### 2.4 三个细节

| 细节 | 原因 |
|---|---|
| 用 `<=` 而不是 `<` | 相等时优先取左边，保持相等元素的相对顺序，排序**稳定** |
| 步骤 2/3 用 `while` 而非 `if` | 一段可能剩多个元素（如左段剩 `5`，右段耗尽） |
| 写回范围 `[left, right]` | 只回写本次合并涉及的那一段，不会破坏其他区间 |

---

## 三、递归版：自顶向下

### 3.1 递归函数要表达什么？

定义 `mergeSortImpl(a, tmp, left, right)` 的语义为：**把 `a[left..right]` 这一段排好序**。

有了这个语义，实现就自然了：

```cpp
void mergeSortImpl(vector<int>& a, vector<int>& tmp, int left, int right) {
    if (left >= right) return;                 // ① 终止条件

    int mid = left + (right - left) / 2;       // ② 找中点
    mergeSortImpl(a, tmp, left, mid);          // ③ 左半排好
    mergeSortImpl(a, tmp, mid + 1, right);     // ④ 右半排好
    merge(a, tmp, left, mid, right);           // ⑤ 合并
}
```

### 3.2 逐行解释「为什么」

**① 终止条件 `left >= right`**
区间只剩 1 个元素（或空）时天然有序。`>=` 而不是 `==` 是为了兼容空区间。

**② `mid = left + (right - left) / 2`**
本意是 `(left + right) / 2`，但当 `left`、`right` 接近 `INT_MAX` 时 `left + right` 会溢出，写成 `left + (right - left) / 2` 就安全。

**③④ 递归**
大问题拆成两个规模减半的子问题，交给递归解决。右半区间从 `mid + 1` 开始，避免与左半重叠。

**⑤ 合并**
此时左右两半各自已有序，调用前面写好的 `merge` 合二为一。

### 3.3 为什么要传 `tmp` 而不是在函数里 new？

如果每次递归都 `vector<int> tmp(...)`，整个排序会分配 O(n log n) 次内存，开销巨大。正确做法是**在最外层分配一次**，作为参数一路传下去复用：

```cpp
void mergeSort(vector<int>& a) {
    if (a.size() < 2) return;
    vector<int> tmp(a.size());               // 只分配这一次
    mergeSortImpl(a, tmp, 0, (int)a.size() - 1);
}
```

### 3.4 递归展开示意（以 `[5,2,9,1]` 为例）

```
mergeSortImpl(0,3)          mid=1
├─ mergeSortImpl(0,1)       mid=0
│  ├─ mergeSortImpl(0,0)    返回
│  ├─ mergeSortImpl(1,1)    返回
│  └─ merge(0,0,1)          → [2,5]
├─ mergeSortImpl(2,3)       mid=2
│  ├─ mergeSortImpl(2,2)    返回
│  ├─ mergeSortImpl(3,3)    返回
│  └─ merge(2,2,3)          → [1,9]
└─ merge(0,1,3)             → [1,2,5,9]
```

### 3.5 完整代码

```cpp
#include <iostream>
#include <vector>
using namespace std;

// ============================================================
// merge：合并两个相邻的有序区间
//   左区间：[left, mid]
//   右区间：[mid + 1, right]
// 合并结果先写入 tmp，再整体拷回 a
// ============================================================
void merge(vector<int>& a, vector<int>& tmp, int left, int mid, int right) {
    int i = left;      // 左区间当前指针
    int j = mid + 1;   // 右区间当前指针
    int k = left;      // 临时数组写入位置

    // 1. 两个区间都还有元素时，取较小者放入 tmp
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];   // 左边更小（<= 保证稳定性）
        } else {
            tmp[k++] = a[j++];   // 右边更小
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

// ============================================================
// mergeSortImpl：递归排序区间 [left, right]
// ============================================================
void mergeSortImpl(vector<int>& a, vector<int>& tmp, int left, int right) {
    // 递归终止条件：区间只有一个元素（或为空），天然有序
    if (left >= right) {
        return;
    }

    // 取中点（防止 left + right 溢出）
    int mid = left + (right - left) / 2;

    // 递归排序左半部分
    mergeSortImpl(a, tmp, left, mid);

    // 递归排序右半部分
    mergeSortImpl(a, tmp, mid + 1, right);

    // 合并两个已排好序的半区间
    merge(a, tmp, left, mid, right);
}

// ============================================================
// mergeSort：对外接口
// ============================================================
void mergeSort(vector<int>& a) {
    if (a.size() < 2) {
        return;
    }
    vector<int> tmp(a.size());   // 临时数组，只分配一次
    mergeSortImpl(a, tmp, 0, (int)a.size() - 1);
}

// ============================================================
// 测试
// ============================================================
int main() {
    vector<int> v = {5, 2, 9, 1, 5, 6, 3, 8, 0, 7};

    mergeSort(v);

    for (int x : v) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
```

---

## 四、迭代版：自底向上

### 4.1 核心观察

递归是**从上往下拆**，迭代是**从下往上合**——直接省略「拆」的过程，认为一开始每个元素就是一个长度 1 的有序段，然后不断合并相邻两段：

```
初始：每个元素是长度 1 的有序段
[5] [2] [9] [1] [5] [6] [3] [8]
 width=1，两两合并 →
[2,5] [1,9] [5,6] [3,8]
 width=2，两两合并 →
[1,2,5,9] [3,5,6,8]
 width=4，两两合并 →
[1,2,3,5,5,6,8,9]
```

「宽度」每轮翻倍：`1 → 2 → 4 → ...`，直到覆盖整个数组。

### 4.2 代码骨架的推导

```cpp
for (int width = 1; width < n; width *= 2) {
    // 这一轮，把每两个相邻的长度为 width 的段合并
}
```

**为什么终止是 `width < n`**：当 `width >= n` 时，整个数组已经是一整段有序（或只有一个段），无需再合并。

**内层循环怎么走**：每轮从 `left = 0` 开始，每次跳过 `2 * width`（一次处理左右两段），直到左段不存在为止：

```cpp
for (int left = 0; left + width < n; left += 2 * width) {
    int mid   = left + width - 1;                    // 左段末尾
    int right = min(left + 2 * width - 1, n - 1);    // 右段末尾，可能越界
    merge(a, tmp, left, mid, right);
}
```

### 4.3 三个边界的由来

| 表达式 | 含义与由来 |
|---|---|
| `left + width < n` | 左段起点 `left`，终点 `left + width - 1`。若 `left + width >= n`，连左段都凑不满，不存在「两段合并」 |
| `mid = left + width - 1` | 左段长度恰好是 `width`，所以左段末尾 = 起点 + 长度 - 1 |
| `right = min(left + 2*width - 1, n - 1)` | 理论上右段末尾是 `left + 2*width - 1`，但数组末尾可能不够长，必须截断到 `n-1` |

### 4.4 以 n = 10 完整推演

```
width=1:
  left=0: merge(0,0,1)
  left=2: merge(2,2,3)
  left=4: merge(4,4,5)
  left=6: merge(6,6,7)
  left=8: merge(8,8,9)
  (left=10: 10+1<10 不成立，停)

width=2:
  left=0: merge(0,1,3)
  left=4: merge(4,5,7)
  left=8: merge(8,9,9)        ← 右段只有 1 个元素，right 截断为 9

width=4:
  left=0: merge(0,3,7)
  left=8: merge(8,9,9)        ← 右段截断

width=8:
  left=0: merge(0,7,9)        ← right = 15 截断为 9

width=16: 16<10 不成立，结束
```

可以看到 `min` 截断让「尾部不完整的段」也能正确合并。

### 4.5 完整代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================
// merge：合并两个相邻的有序区间
//   左区间：[left, mid]
//   右区间：[mid + 1, right]
// ============================================================
void merge(vector<int>& a, vector<int>& tmp, int left, int mid, int right) {
    int i = left;      // 左区间当前指针
    int j = mid + 1;   // 右区间当前指针
    int k = left;      // 临时数组写入位置

    // 1. 两个区间都还有元素时，取较小者放入 tmp
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];   // 左边更小（<= 保证稳定性）
        } else {
            tmp[k++] = a[j++];   // 右边更小
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

// ============================================================
// mergeSortIterative：自底向上归并排序
//   从长度 width = 1 开始，每轮把相邻两段长度为 width 的
//   有序区间合并成一段长度为 2*width 的有序区间，
//   直到 width 覆盖整个数组。
// ============================================================
void mergeSortIterative(vector<int>& a) {
    int n = (int)a.size();
    if (n < 2) {
        return;
    }

    vector<int> tmp(n);   // 临时数组，只分配一次

    // 外层循环：控制当前「每段」的长度，按 1 → 2 → 4 → ... 倍增
    for (int width = 1; width < n; width *= 2) {

        // 内层循环：从左到右，每两段为一组进行合并
        for (int left = 0; left + width < n; left += 2 * width) {

            int mid = left + width - 1;

            // 右端点可能超出数组末尾，需要截断（最后可能只有一段）
            int right = min(left + 2 * width - 1, n - 1);

            merge(a, tmp, left, mid, right);
        }
    }
}

// ============================================================
// 测试
// ============================================================
int main() {
    vector<int> v = {5, 2, 9, 1, 5, 6, 3, 8, 0, 7};

    mergeSortIterative(v);

    for (int x : v) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
```

---

## 五、两种版本的本质差别

| 维度 | 递归版 | 迭代版 |
|---|---|---|
| **合并顺序** | 按递归树深度：先合最小子问题，逐层往上 | 按段长：width 从 1 倍增 |
| **谁驱动** | 递归调用栈 | 两层 for 循环 |
| **额外空间** | O(n) 临时数组 + O(log n) 栈 | 严格 O(n) |
| **好处** | 逻辑贴合「分治」直觉 | 无栈开销 |
| **时间/空间复杂度** | O(n log n) / O(n) | O(n log n) / O(n) |
| **稳定性** | 稳定 | 稳定 |

两者**最终合并的区间顺序不同，但整体结构一致**——都是「把相邻有序段合并成更大有序段」，直到整个数组为一段。所以 `merge` 函数可以直接复用。

---

## 六、总结

### 6.1 一张图看懂整体结构

```
               【核心思路】
      拆到单元素 → 逐层合并有序段
                    │
        ┌───────────┴───────────┐
     【怎么合】                【怎么组织】
   双指针 + 临时数组          递归 / 迭代
   merge(left,mid,right)      │
        │             ┌───────┴───────┐
        │           递归版            迭代版
        │      拆(a,left,right)     width 倍增
        │      递归左右 + merge     相邻段 merge
        └──────────────┴──────────────┘
                        │
                   完整排序
```

### 6.2 一句话总结

> **整个归并排序 = 「一次 merge 函数（双指针 + 临时数组）」+「一种把大区间拆成小区间、再把小区间逐层合回去的组织方式（递归或迭代）」。**

思路通了，代码就只是把这两件事写清楚而已。

### 6.3 复杂度速查

| 指标 | 值 |
|---|---|
| 最好时间 | O(n log n) |
| 平均时间 | O(n log n) |
| 最坏时间 | O(n log n) |
| 空间 | O(n) |
| 稳定性 | 稳定 |