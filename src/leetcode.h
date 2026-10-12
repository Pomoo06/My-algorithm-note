#pragma once
// ============================================================================
//  leetcode.h —— 本地刷题调试用的 LeetCode 数据类型与工具函数
//
//  用法：
//      #include "leetcode.h"      // 与本文件同目录，直接包含即可
//
//  说明：
//      ListNode / TreeNode / Node 的成员与构造函数和 LeetCode 官方定义完全一致，
//      所以可以直接把题目里给的 struct 定义删掉，改用本头文件；
//      反过来，如果你粘贴了题目里的定义，也可以删掉本文件里同名的那一段。
//
//      所有函数都带 inline，头文件被多个 .cpp 包含也不会重复定义。
// ============================================================================

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <optional>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// 让测试数据可以少写前缀，例如 makeTree({1, nullopt, 2})
using std::nullopt;
using std::optional;


// ---------------------------------------------------------------------------
// 一、单链表 ListNode
// ---------------------------------------------------------------------------
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 构造：makeList({1, 2, 3}) 或 makeList(v)
inline ListNode* makeList(const std::vector<int>& vals) {
    ListNode dummy;
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

inline ListNode* makeList(std::initializer_list<int> vals) {
    return makeList(std::vector<int>(vals));
}

inline std::string listToString(const ListNode* head, const std::string& sep = " -> ") {
    std::string s;
    for (const ListNode* p = head; p != nullptr; p = p->next) {
        if (!s.empty()) s += sep;
        s += std::to_string(p->val);
    }
    return s;
}

inline void printList(const ListNode* head, const std::string& sep = " -> ") {
    std::cout << listToString(head, sep) << '\n';
}

inline int listLength(const ListNode* head) {
    int n = 0;
    for (const ListNode* p = head; p != nullptr; p = p->next) ++n;
    return n;
}

// 取第 idx 个节点（idx 从 0 开始，越界返回 nullptr）
inline const ListNode* listAt(const ListNode* head, int idx) {
    const ListNode* p = head;
    while (p != nullptr && idx-- > 0) p = p->next;
    return p;
}

// ---------------------------------------------------------------------------
// 二、二叉树 TreeNode
// ---------------------------------------------------------------------------
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// 按 LeetCode 的层序序列构造二叉树，空节点写 nullopt
//     makeTree({3, 9, 20, nullopt, nullopt, 15, 7})   <==>   [3,9,20,null,null,15,7]
inline TreeNode* makeTree(const std::vector<optional<int>>& vals) {
    if (vals.empty() || !vals[0].has_value()) return nullptr;

    TreeNode* root = new TreeNode(vals[0].value());
    std::queue<TreeNode*> q;
    q.push(root);

    std::size_t i = 1;
    while (!q.empty() && i < vals.size()) {
        TreeNode* cur = q.front();
        q.pop();

        if (i < vals.size()) {
            if (vals[i].has_value()) {
                cur->left = new TreeNode(vals[i].value());
                q.push(cur->left);
            }
            ++i;
        }
        if (i < vals.size()) {
            if (vals[i].has_value()) {
                cur->right = new TreeNode(vals[i].value());
                q.push(cur->right);
            }
            ++i;
        }
    }
    return root;
}

inline TreeNode* makeTree(std::initializer_list<optional<int>> vals) {
    return makeTree(std::vector<optional<int>>(vals));
}

// 转成 LeetCode 层序字符串，末尾多余的 null 会被去掉
inline std::string treeToString(const TreeNode* root) {
    if (root == nullptr) return "[]";

    std::vector<std::string> out;
    std::queue<const TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        const TreeNode* cur = q.front();
        q.pop();
        if (cur == nullptr) {
            out.push_back("null");
            continue;
        }
        out.push_back(std::to_string(cur->val));
        q.push(cur->left);
        q.push(cur->right);
    }
    while (!out.empty() && out.back() == "null") out.pop_back();

    std::string s = "[";
    for (std::size_t i = 0; i < out.size(); ++i) {
        if (i != 0) s += ", ";
        s += out[i];
    }
    return s + "]";
}

inline void printTree(const TreeNode* root) {
    std::cout << treeToString(root) << '\n';
}

// 把树侧躺打印出来，看结构比一串数字直观
namespace lc_detail {
inline void treeShape(const TreeNode* node, const std::string& prefix, bool isLeft) {
    if (node == nullptr) return;
    std::cout << prefix << (isLeft ? "|-- " : "`-- ") << node->val << '\n';
    treeShape(node->left, prefix + (isLeft ? "|   " : "    "), true);
    treeShape(node->right, prefix + (isLeft ? "|   " : "    "), false);
}
}  // namespace lc_detail

inline void printTreeShape(const TreeNode* root) {
    if (root == nullptr) {
        std::cout << "(empty tree)\n";
        return;
    }
    std::cout << root->val << '\n';
    lc_detail::treeShape(root->left, "", true);
    lc_detail::treeShape(root->right, "", false);
}

// ---------------------------------------------------------------------------
// 三、带随机指针的链表 Node（第 138 题）
// ---------------------------------------------------------------------------
struct Node {
    int val;
    Node* next;
    Node* random;
    Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

// data[i] = {节点值, random 指向的下标}，下标用 -1 表示 null
//     makeRandomList({{7,-1}, {13,0}, {11,4}, {10,2}, {1,0}})
inline Node* makeRandomList(const std::vector<std::pair<int, int>>& data) {
    std::vector<Node*> nodes;
    nodes.reserve(data.size());
    for (const auto& p : data) nodes.push_back(new Node(p.first));

    for (std::size_t i = 0; i < nodes.size(); ++i) {
        if (i + 1 < nodes.size()) nodes[i]->next = nodes[i + 1];
        const int r = data[i].second;
        nodes[i]->random = (r >= 0 && r < static_cast<int>(nodes.size())) ? nodes[r] : nullptr;
    }
    return nodes.empty() ? nullptr : nodes.front();
}

inline Node* makeRandomList(std::initializer_list<std::pair<int, int>> data) {
    return makeRandomList(std::vector<std::pair<int, int>>(data));
}

// 打印成 [[7,null],[13,0],...] 的 LeetCode 形式
inline std::string randomListToString(const Node* head) {
    std::vector<const Node*> nodes;
    std::unordered_map<const Node*, int> index;
    for (const Node* p = head; p != nullptr; p = p->next) {
        index[p] = static_cast<int>(nodes.size());
        nodes.push_back(p);
    }

    std::string s = "[";
    for (std::size_t i = 0; i < nodes.size(); ++i) {
        if (i != 0) s += ", ";
        s += "[";
        s += std::to_string(nodes[i]->val);
        s += ", ";
        const auto it = nodes[i]->random == nullptr ? index.end() : index.find(nodes[i]->random);
        s += (it == index.end()) ? "null" : std::to_string(it->second);
        s += "]";
    }
    return s + "]";
}

inline void printRandomList(const Node* head) {
    std::cout << randomListToString(head) << '\n';
}

// ---------------------------------------------------------------------------
// 四、图节点 GraphNode（第 133 题；LeetCode 里同样叫 Node，这里改名以免冲突）
// ---------------------------------------------------------------------------
struct GraphNode {
    int val;
    std::vector<GraphNode*> neighbors;
    GraphNode() : val(0) {}
    GraphNode(int _val) : val(_val) {}
    GraphNode(int _val, std::vector<GraphNode*> _neighbors)
        : val(_val), neighbors(std::move(_neighbors)) {}
};

// 由邻接表构造无向图，节点值从 1 开始，与 LeetCode 133 的输入格式一致
//     makeGraph({{2,4}, {1,3}, {2,4}, {1,3}})
inline GraphNode* makeGraph(const std::vector<std::vector<int>>& adj) {
    const int n = static_cast<int>(adj.size());
    if (n <= 0) return nullptr;

    std::vector<GraphNode*> nodes(n + 1, nullptr);
    for (int i = 1; i <= n; ++i) nodes[i] = new GraphNode(i);
    for (int i = 1; i <= n; ++i) {
        for (int v : adj[i - 1]) {
            if (v >= 1 && v <= n) nodes[i]->neighbors.push_back(nodes[v]);
        }
    }
    return nodes[1];
}

// 以 node 为起点 BFS，按节点值升序输出邻接表（与 LeetCode 的写法一致）
inline std::string graphToString(const GraphNode* node) {
    if (node == nullptr) return "[]";

    std::vector<const GraphNode*> order;
    std::unordered_map<const GraphNode*, int> index;
    std::queue<const GraphNode*> q;

    index[node] = 0;
    order.push_back(node);
    q.push(node);
    while (!q.empty()) {
        const GraphNode* cur = q.front();
        q.pop();
        for (const GraphNode* nb : cur->neighbors) {
            if (index.find(nb) == index.end()) {
                index[nb] = static_cast<int>(order.size());
                order.push_back(nb);
                q.push(nb);
            }
        }
    }
    std::sort(order.begin(), order.end(),
              [](const GraphNode* a, const GraphNode* b) { return a->val < b->val; });

    std::string s = "[";
    for (std::size_t i = 0; i < order.size(); ++i) {
        if (i != 0) s += ", ";
        s += "[";
        for (std::size_t j = 0; j < order[i]->neighbors.size(); ++j) {
            if (j != 0) s += ", ";
            s += std::to_string(order[i]->neighbors[j]->val);
        }
        s += "]";
    }
    return s + "]";
}

inline void printGraph(const GraphNode* node) {
    std::cout << graphToString(node) << '\n';
}

// ---------------------------------------------------------------------------
// 五、N 叉树 NaryNode（第 559 / 589 题）
// ---------------------------------------------------------------------------
struct NaryNode {
    int val;
    std::vector<NaryNode*> children;
    NaryNode() : val(0) {}
    NaryNode(int _val) : val(_val) {}
    NaryNode(int _val, std::vector<NaryNode*> _children) : val(_val), children(std::move(_children)) {}
};

// 按 LeetCode 的层序序列构造：根节点后面跟一个 nullopt，此后每个节点的孩子列表
// 也以 nullopt 收尾（收尾的 nullopt 可以省略）
//     makeNaryTree({1, nullopt, 3, 2, 4, nullopt, 5, 6})   <==>   [1,null,3,2,4,null,5,6]
inline NaryNode* makeNaryTree(const std::vector<optional<int>>& vals) {
    if (vals.empty() || !vals[0].has_value()) return nullptr;

    NaryNode* root = new NaryNode(vals[0].value());
    std::queue<NaryNode*> q;
    q.push(root);

    std::size_t i = 1;
    if (i < vals.size() && !vals[i].has_value()) ++i;  // 跳过根节点后的分隔 nullopt

    while (!q.empty() && i < vals.size()) {
        NaryNode* cur = q.front();
        q.pop();
        while (i < vals.size() && vals[i].has_value()) {
            NaryNode* child = new NaryNode(vals[i].value());
            cur->children.push_back(child);
            q.push(child);
            ++i;
        }
        if (i < vals.size()) ++i;  // 跳过该节点孩子列表结尾的 nullopt
    }
    return root;
}

inline NaryNode* makeNaryTree(std::initializer_list<optional<int>> vals) {
    return makeNaryTree(std::vector<optional<int>>(vals));
}

inline std::string naryTreeToString(const NaryNode* root) {
    if (root == nullptr) return "[]";

    std::vector<std::string> out{std::to_string(root->val), "null"};
    std::queue<const NaryNode*> q;
    q.push(root);
    while (!q.empty()) {
        const NaryNode* cur = q.front();
        q.pop();
        for (const NaryNode* c : cur->children) {
            out.push_back(std::to_string(c->val));
            q.push(c);
        }
        out.push_back("null");  // 该节点的孩子列表结束
    }
    while (!out.empty() && out.back() == "null") out.pop_back();

    std::string s = "[";
    for (std::size_t i = 0; i < out.size(); ++i) {
        if (i != 0) s += ", ";
        s += out[i];
    }
    return s + "]";
}

inline void printNaryTree(const NaryNode* root) {
    std::cout << naryTreeToString(root) << '\n';
}

// ---------------------------------------------------------------------------
// 六、通用打印小工具
// ---------------------------------------------------------------------------
// 让 vector（含嵌套）能直接 cout，例如 cout << vector<vector<int>>{{1,2}} << '\n';
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i != 0) os << ", ";
        os << v[i];
    }
    return os << "]";
}

// println(a, b, c) => 以空格分隔后换行，快速查看结果
template <typename... Args>
inline void println(Args&&... args) {
    bool first = true;
    ((std::cout << (first ? "" : " ") << args, first = false), ...);
    std::cout << '\n';
}

// 任意支持 << 的对象转成字符串
template <typename T>
inline std::string toStr(const T& value) {
    std::ostringstream os;
    os << value;
    return os.str();
}
