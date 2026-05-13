/*
 * References:
 * (1) AI-generated sources: Gemini 3.1 Pro (for overall implementation of Brute Force, DP, B&B, Greedy)
 * (2) Random data generation uses std::mt19937 with modulo to guarantee cross-platform and compiler-independent sequence consistency.
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <random>

using namespace std;
using namespace std::chrono;

struct Item {
    int weight;
    int benefit;
    double ratio;
    int index;
};

// ==========================================
// 1. Brute Force (0-1 Knapsack)
// ==========================================
int max_bf_benefit = 0;
void brute_force(const vector<Item>& items, int W, int index, int current_weight, int current_benefit) {
    if (index == items.size()) {
        if (current_benefit > max_bf_benefit) {
            max_bf_benefit = current_benefit;
        }
        return;
    }
    // Exclude the current item
    brute_force(items, W, index + 1, current_weight, current_benefit);
    
    // Include the current item
    if (current_weight + items[index].weight <= W) {
        brute_force(items, W, index + 1, current_weight + items[index].weight, current_benefit + items[index].benefit);
    }
}

// ==========================================
// 2. Greedy (Fractional Knapsack)
// ==========================================
double greedy_fractional(int W, vector<Item> items) {
    // Sort items by benefit/weight ratio in descending order
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });

    double total_benefit = 0.0;
    int current_weight = 0;

    for (const auto& item : items) {
        if (current_weight + item.weight <= W) {
            current_weight += item.weight;
            total_benefit += item.benefit;
        } else {
            int remain = W - current_weight;
            total_benefit += item.benefit * ((double)remain / item.weight);
            break;
        }
    }
    return total_benefit;
}

// ==========================================
// 3. Dynamic Programming (0-1 Knapsack)
// ==========================================
int dynamic_programming(int W, const vector<Item>& items) {
    vector<int> dp(W + 1, 0);
    for (const auto& item : items) {
        for (int w = W; w >= item.weight; --w) {
            if (dp[w - item.weight] + item.benefit > dp[w]) {
                dp[w] = dp[w - item.weight] + item.benefit;
            }
        }
    }
    return dp[W];
}

// ==========================================
// 4. Branch and Bound (0-1 Knapsack)
// ==========================================
struct Node {
    int level;
    int profit;
    int weight;
    double bound;
    bool operator<(const Node& other) const {
        return bound < other.bound; // Max-heap based on bound
    }
};

double get_bound(Node u, int n, int W, const vector<Item>& items) {
    if (u.weight >= W) return 0;
    
    double profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;
    
    // Greedily take items as whole
    while (j < n && totweight + items[j].weight <= W) {
        totweight += items[j].weight;
        profit_bound += items[j].benefit;
        j++;
    }
    // Take fractional part of the next item
    if (j < n) {
        profit_bound += (W - totweight) * items[j].ratio;
    }
    return profit_bound;
}

int branch_and_bound(int W, vector<Item> items) {
    // Sort items by ratio descending
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });

    int n = items.size();
    priority_queue<Node> Q;
    Node u, v;
    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = get_bound(u, n, W, items);

    int max_profit = 0;
    Q.push(u);

    while (!Q.empty()) {
        u = Q.top();
        Q.pop();

        // If bound is not strictly greater than max_profit, we can't find a better solution here
        if (u.bound <= max_profit) continue;
        if (u.level == n - 1) continue;

        // 1. Include next item
        v.level = u.level + 1;
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].benefit;

        if (v.weight <= W && v.profit > max_profit) {
            max_profit = v.profit;
        }

        v.bound = get_bound(v, n, W, items);
        if (v.bound > max_profit) {
            Q.push(v);
        }

        // 2. Exclude next item
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = get_bound(v, n, W, items);
        if (v.bound > max_profit) {
            Q.push(v);
        }
    }
    return max_profit;
}

// ==========================================
// Utility: Generate Items
// ==========================================
vector<Item> generate_items(int n) {
    mt19937 rng(100); // Fixed seed 100 for consistency across tests
    vector<Item> items(n);
    
    // By using mt19937 and modulo, we ensure exact same values regardless of compiler or standard library
    for (int i = 0; i < n; ++i) {
        items[i].index = i;
        items[i].benefit = (rng() % 500) + 1; // 1 to 500
        items[i].weight = (rng() % 100) + 1;  // 1 to 100
        items[i].ratio = (double)items[i].benefit / items[i].weight;
    }
    return items;
}

// ==========================================
// Main Function
// ==========================================
int main() {
    // Prevent scientific notation
    cout << fixed << setprecision(2);
    
    // --- 1. Brute force ---
    cout << "1. Brute force\n";
    cout << "Number of Items\tProcessing time in milliseconds / Maximum benefit value\n";
    
    vector<int> bf_sizes = {11, 21, 31};
    for (int n : bf_sizes) {
        vector<Item> items = generate_items(n);
        int W = n * 25;
        max_bf_benefit = 0;

        auto start = high_resolution_clock::now();
        brute_force(items, W, 0, 0, 0);
        auto end = high_resolution_clock::now();
        double ms = duration<double, milli>(end - start).count();

        cout << n << "\t\t" << ms << " / " << max_bf_benefit << "\n";
    }
    cout << "\n";

    // --- 2. Greedy / D.P. / B.&B. ---
    cout << "2. Greedy / D.P. / B.&B.\n";
    cout << "Number of Items\tProcessing time in milliseconds / Maximum benefit value\n";
    cout << "\t\tGreedy\t\t\tD.P.\t\t\tB.&B.\n";
    
    vector<int> other_sizes = {10, 100, 1000, 10000};
    for (int n : other_sizes) {
        vector<Item> items = generate_items(n);
        int W = n * 25;

        // Greedy
        auto start1 = high_resolution_clock::now();
        double greedy_ans = greedy_fractional(W, items);
        auto end1 = high_resolution_clock::now();
        double ms1 = duration<double, milli>(end1 - start1).count();

        // DP
        auto start2 = high_resolution_clock::now();
        int dp_ans = dynamic_programming(W, items);
        auto end2 = high_resolution_clock::now();
        double ms2 = duration<double, milli>(end2 - start2).count();

        // Branch and Bound
        auto start3 = high_resolution_clock::now();
        int bb_ans = branch_and_bound(W, items);
        auto end3 = high_resolution_clock::now();
        double ms3 = duration<double, milli>(end3 - start3).count();

        // Print row
        cout << n << "\t\t" 
             << ms1 << " / " << greedy_ans << "\t\t"
             << ms2 << " / " << dp_ans << "\t\t"
             << ms3 << " / " << bb_ans << "\n";
    }

    return 0;
}