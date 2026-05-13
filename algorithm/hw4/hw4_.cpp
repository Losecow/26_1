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
 #include <sstream>
 
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
     if (index == (int)items.size()) {
         if (current_benefit > max_bf_benefit) {
             max_bf_benefit = current_benefit;
         }
         return;
     }
     brute_force(items, W, index + 1, current_weight, current_benefit);
     if (current_weight + items[index].weight <= W) {
         brute_force(items, W, index + 1, current_weight + items[index].weight, current_benefit + items[index].benefit);
     }
 }
 
 // ==========================================
 // 2. Greedy (Fractional Knapsack)
 // ==========================================
 double greedy_fractional(int W, vector<Item> items) {
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
         return bound < other.bound;
     }
 };
 
 double get_bound(Node u, int n, int W, const vector<Item>& items) {
     if (u.weight >= W) return 0;
     double profit_bound = u.profit;
     int j = u.level + 1;
     int totweight = u.weight;
     while (j < n && totweight + items[j].weight <= W) {
         totweight += items[j].weight;
         profit_bound += items[j].benefit;
         j++;
     }
     if (j < n) {
         profit_bound += (W - totweight) * items[j].ratio;
     }
     return profit_bound;
 }
 
 int branch_and_bound(int W, vector<Item> items) {
     sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
         return a.ratio > b.ratio;
     });
     int n = items.size();
     priority_queue<Node> Q;
     Node u, v;
     u.level = -1; u.profit = 0; u.weight = 0;
     u.bound = get_bound(u, n, W, items);
     int max_profit = 0;
     Q.push(u);
     while (!Q.empty()) {
         u = Q.top(); Q.pop();
         if (u.bound <= max_profit) continue;
         if (u.level == n - 1) continue;
         v.level = u.level + 1;
         v.weight = u.weight + items[v.level].weight;
         v.profit = u.profit + items[v.level].benefit;
         if (v.weight <= W && v.profit > max_profit) max_profit = v.profit;
         v.bound = get_bound(v, n, W, items);
         if (v.bound > max_profit) Q.push(v);
         v.weight = u.weight; v.profit = u.profit;
         v.bound = get_bound(v, n, W, items);
         if (v.bound > max_profit) Q.push(v);
     }
     return max_profit;
 }
 
 // ==========================================
 // Utility: Generate Items
 // ==========================================
 vector<Item> generate_items(int n) {
     mt19937 rng(100);
     vector<Item> items(n);
     for (int i = 0; i < n; ++i) {
         items[i].index = i;
         items[i].benefit = (rng() % 500) + 1;
         items[i].weight  = (rng() % 100) + 1;
         items[i].ratio   = (double)items[i].benefit / items[i].weight;
     }
     return items;
 }
 
 // ==========================================
 // Utility: Table Helpers
 // ==========================================
 string make_cell(double ms, double val, int cell_width) {
     ostringstream oss;
     oss << fixed << setprecision(2);
     oss << ms << " / " << val;
     string s = oss.str();
     // center-pad
     int pad = cell_width - (int)s.size();
     int lpad = pad / 2, rpad = pad - lpad;
     return string(lpad, ' ') + s + string(rpad, ' ');
 }
 
 void print_hline(int c0, int c1) {
     cout << "+" << string(c0, '-') << "+" << string(c1, '-') << "+\n";
 }
 
 void print_hline3(int c0, int c1, int c2, int c3) {
     cout << "+" << string(c0, '-') << "+"
          << string(c1, '-') << "+"
          << string(c2, '-') << "+"
          << string(c3, '-') << "+\n";
 }
 
 // ==========================================
 // Main Function
 // ==========================================
 int main() {
     cout << fixed << setprecision(2);
 
     // ----------------------------------------
     // Table 1: Brute Force
     // ----------------------------------------
     const int T1_C0 = 17;   // "Number of Items" column
     const int T1_C1 = 52;   // result column
 
     cout << "1. Brute force\n";
     print_hline(T1_C0, T1_C1);
 
     // Header row
     {
         string h0 = "Number of Items";
         string h1 = "Processing time in milliseconds / Maximum benefit value";
         int lp0 = (T1_C0 - (int)h0.size()) / 2, rp0 = T1_C0 - (int)h0.size() - lp0;
         int lp1 = (T1_C1 - (int)h1.size()) / 2, rp1 = T1_C1 - (int)h1.size() - lp1;
         cout << "|" << string(lp0,' ') << h0 << string(rp0,' ')
              << "|" << string(lp1,' ') << h1 << string(rp1,' ') << "|\n";
     }
     print_hline(T1_C0, T1_C1);
 
     vector<int> bf_sizes = {11, 21, 31};
     for (int n : bf_sizes) {
         vector<Item> items = generate_items(n);
         int W = n * 25;
         max_bf_benefit = 0;
 
         auto start = high_resolution_clock::now();
         brute_force(items, W, 0, 0, 0);
         auto end = high_resolution_clock::now();
         double ms = duration<double, milli>(end - start).count();
 
         string cell = make_cell(ms, (double)max_bf_benefit, T1_C1);
         // left-align number of items (centered)
         string nc = to_string(n);
         int lp = (T1_C0 - (int)nc.size()) / 2, rp = T1_C0 - (int)nc.size() - lp;
         cout << "|" << string(lp,' ') << nc << string(rp,' ')
              << "|" << cell << "|\n";
         print_hline(T1_C0, T1_C1);
     }
 
     cout << "\n";
 
     // ----------------------------------------
     // Table 2: Greedy / D.P. / B.&B.
     // ----------------------------------------
     const int T2_C0 = 11;   // "Number of Items"
     const int T2_C1 = 22;   // Greedy
     const int T2_C2 = 22;   // D. P.
     const int T2_C3 = 22;   // B. & B.
 
     cout << "2. Greedy / D.P. / B.&B.\n";
     print_hline3(T2_C0, T2_C1, T2_C2, T2_C3);
 
     // Header row 1: spanning title
     {
         int span = T2_C1 + T2_C2 + T2_C3 + 2; // +2 for inner '|' chars
         string h0a = "Number of";
         string h1  = "Processing time in milliseconds / Maximum benefit value";
         int lp0 = (T2_C0 - (int)h0a.size()) / 2, rp0 = T2_C0 - (int)h0a.size() - lp0;
         int lp1 = (span - (int)h1.size()) / 2,    rp1 = span - (int)h1.size() - lp1;
         cout << "|" << string(lp0,' ') << h0a << string(rp0,' ')
              << "|" << string(lp1,' ') << h1  << string(rp1,' ') << "|\n";
     }
     // Header row 2: sub-columns
     {
         string h0b  = "Items";
         string hg   = "Greedy";
         string hdp  = "D. P.";
         string hbb  = "B. & B.";
         auto center = [](const string& s, int w) {
             int lp = (w-(int)s.size())/2, rp = w-(int)s.size()-lp;
             return string(lp,' ')+s+string(rp,' ');
         };
         cout << "|" << center(h0b,T2_C0)
              << "+" << center(hg, T2_C1)
              << "|" << center(hdp,T2_C2)
              << "|" << center(hbb,T2_C3) << "|\n";
     }
     print_hline3(T2_C0, T2_C1, T2_C2, T2_C3);
 
     vector<int> other_sizes = {10, 100, 1000, 10000};
     for (int n : other_sizes) {
         vector<Item> items = generate_items(n);
         int W = n * 25;
 
         auto s1 = high_resolution_clock::now();
         double greedy_ans = greedy_fractional(W, items);
         auto e1 = high_resolution_clock::now();
         double ms1 = duration<double, milli>(e1 - s1).count();
 
         auto s2 = high_resolution_clock::now();
         int dp_ans = dynamic_programming(W, items);
         auto e2 = high_resolution_clock::now();
         double ms2 = duration<double, milli>(e2 - s2).count();
 
         auto s3 = high_resolution_clock::now();
         int bb_ans = branch_and_bound(W, items);
         auto e3 = high_resolution_clock::now();
         double ms3 = duration<double, milli>(e3 - s3).count();
 
         string nc = to_string(n);
         int lp = (T2_C0-(int)nc.size())/2, rp = T2_C0-(int)nc.size()-lp;
 
         cout << "|" << string(lp,' ') << nc << string(rp,' ')
              << "|" << make_cell(ms1, greedy_ans, T2_C1)
              << "|" << make_cell(ms2, (double)dp_ans,   T2_C2)
              << "|" << make_cell(ms3, (double)bb_ans,   T2_C3) << "|\n";
         print_hline3(T2_C0, T2_C1, T2_C2, T2_C3);
     }
 
     return 0;
 }