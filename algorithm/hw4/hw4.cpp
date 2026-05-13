/*
 * Homework #4
 * Name: 박진우 (Student ID: 22100311)
 *
 * [Reference Documentation]
 * (1) Lecture slide - Ch15 Dynamic Programming (week 4, 5)
 * (2) Lecture slide - Ch16 Greedy Algorithms / Knapsack Problem (week 7)
 * (3) Velog - 배낭 문제(Knapsack Problem)
 *     https://velog.io/@jxlhe46/알고리즘-배낭-문제-Knapsack-Problem
 * (4) GeeksforGeeks - Fractional Knapsack Problem
 *     https://www.geeksforgeeks.org/dsa/fractional-knapsack-problem/
 * (5) GeeksforGeeks - Implementation of 0/1 Knapsack using Branch and Bound
 *     https://www.geeksforgeeks.org/dsa/implementation-of-0-1-knapsack-using-branch-and-bound/
 * (6) Hyperscale AI: Gemini, Claude (for code review and recommendation)
 * (7) C++ Book reference: Introduction To Algorithms | Thomas H. Cormen
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
// 시간 측정 라이브러리
using namespace std::chrono;

struct Item {
    int weight;
    int benefit;
    double ratio;
    int index;
};

// max_bf_benefit: maximum benefit value for brute force
int max_bf_benefit = 0;

// 1. Brute Force (0-1 Knapsack)
void brute_force(const vector<Item>& items, int W, int index, int current_weight, int current_benefit) {
    // Base case: 모든 아이템을 확인했으면 최대 이익을 업데이트
    if (index == (int)items.size()) {
        if (current_benefit > max_bf_benefit) {
            max_bf_benefit = current_benefit;
        }
        return;
    }
    // Case 1: 현재 아이템을 선택하지 않는 경우
    brute_force(items, W, index + 1, current_weight, current_benefit);
    
    // Case 2: 현재 아이템을 선택하는 경우
    if (current_weight + items[index].weight <= W) {
        brute_force(items, W, index + 1, current_weight + items[index].weight, current_benefit + items[index].benefit);
    }
}

// 2. Greedy (Fractional Knapsack)
double greedy_fractional(int W, vector<Item> items) {

    // 무게 대비 이익 비율이 높은 순서대로 정렬
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });

    // 현재 무게와 이익을 0으로 초기화
    double total_benefit = 0.0;
    int current_weight = 0;
    
    // 무게 대비 이익 비율이 높은 순서대로 아이템을 확인
    for (const auto& item : items) {
        // 현재 무게와 아이템 무게를 더한 값이 최대 무게를 초과하지 않으면 선택
        if (current_weight + item.weight <= W) {
            current_weight += item.weight;
            total_benefit += item.benefit;
        } else {
            // 현재 무게와 아이템 무게를 더한 값이 최대 무게를 초과하면 남은 무게에 대한 이익을 계산
            int remain = W - current_weight;
            total_benefit += item.benefit * ((double)remain / item.weight);
            // 최대 무게를 초과하면 더 이상 아이템을 선택할 수 없으므로 반복문 종료
            break;
        }
    }
    // 최대 이익을 반환
    return total_benefit;
}

// 3. Dynamic Programming (0-1 Knapsack)
int dynamic_programming(int W, const vector<Item>& items) {
    // dp[w]: 무게 w를 만족하는 최대 이익
    vector<int> dp(W + 1, 0);
    // 무게 대비 이익 비율이 높은 순서대로 아이템을 확인
    for (const auto& item : items) {
        // 현재 무게와 아이템 무게를 더한 값이 최대 무게를 초과하지 않으면 선택
        for (int w = W; w >= item.weight; --w) {
            // 현재 무게와 아이템 무게를 더한 값이 최대 무게를 초과하면 남은 무게에 대한 이익을 계산
            if (dp[w - item.weight] + item.benefit > dp[w]) {
                // 현재 무게와 아이템 무게를 더한 값이 최대 무게를 초과하면 남은 무게에 대한 이익을 계산
                dp[w] = dp[w - item.weight] + item.benefit;
            }
        }
    }
    // 최대 이익을 반환
    return dp[W];
}

// 4. Branch and Bound (0-1 Knapsack)
struct Node {
    int level; // 현재 레벨
    int profit; // 현재 이익
    int weight; // 현재 무게
    double bound; // 현재 이익의 상한값
    bool operator<(const Node& other) const { // 상한값이 작은 순서대로 정렬
        return bound < other.bound;
    }
};

// 5. Get Bound (Branch and Bound)
double get_bound(Node u, int n, int W, const vector<Item>& items) {
    // 현재 무게가 최대 무게를 초과하면 상한값을 0으로 반환
    if (u.weight >= W) return 0;
    
    double profit_bound = u.profit; // 현재 이익
    // 현재 레벨 + 1부터 시작
    int j = u.level + 1; // 다음 아이템의 인덱스
    int totweight = u.weight; // 현재 무게
    
    // 다음 아이템이 최대 무게를 초과하지 않으면 계속 진행
    while (j < n && totweight + items[j].weight <= W) {
        // 현재 무게에 다음 아이템 무게를 더함
        totweight += items[j].weight; 
        // 현재 이익에 다음 아이템 이익을 더함
        profit_bound += items[j].benefit; 
        j++;
    }
    // 다음 아이템이 최대 무게를 초과하면 남은 무게에 대한 이익을 계산
    if (j < n) { 
        // 남은 무게에 대한 이익을 계산
        profit_bound += (W - totweight) * items[j].ratio;
    }
    // 상한값을 반환
    return profit_bound; 
}

// 6. Branch and Bound (0-1 Knapsack)
int branch_and_bound(int W, vector<Item> items) {
    // 무게 대비 이익 비율이 높은 순서대로 정렬
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });

    // 아이템의 개수
    int n = items.size(); // 아이템의 개수
    priority_queue<Node> Q; // 우선순위 큐
    Node u, v; // 노드 u와 v
    u.level = -1; // 레벨 -1
    u.profit = 0; // 이익 0
    u.weight = 0; // 무게 0
    u.bound = get_bound(u, n, W, items); // 상한값

    int max_profit = 0; // 최대 이익
    Q.push(u); // 우선순위 큐에 노드 u 추가

    // 우선순위 큐가 비어있지 않으면 계속 진행
    while (!Q.empty()) {
        u = Q.top();
        Q.pop();

        // 상한값이 최대 이익보다 작으면 다음 노드로 이동
        if (u.bound <= max_profit) continue;
        // 레벨이 아이템의 개수 - 1이면 최대 이익 업데이트
        if (u.level == n - 1) continue;

        // 다음 노드 초기화
        v.level = u.level + 1;
        // 무게 업데이트
        v.weight = u.weight + items[v.level].weight;
        // 이익 업데이트
        v.profit = u.profit + items[v.level].benefit;

        // 무게가 최대 무게를 초과하지 않고 이익이 최대 이익보다 크면 최대 이익 업데이트
        if (v.weight <= W && v.profit > max_profit) {
            max_profit = v.profit;
        }

        // 상한값 업데이트
        v.bound = get_bound(v, n, W, items);
        // 상한값이 최대 이익보다 크면 우선순위 큐에 노드 v 추가
        if (v.bound > max_profit) {
            Q.push(v);
        }

        // 다음 노드 초기화
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = get_bound(v, n, W, items);
        // 상한값이 최대 이익보다 크면 우선순위 큐에 노드 v 추가
        if (v.bound > max_profit) {
            Q.push(v);
        }
    }
    // 최대 이익을 반환
    return max_profit;
}

// 아이템 생성 함수
vector<Item> generate_items(int n) {
    // 랜덤 시드 100
    mt19937 rng(100); 
    // 아이템 배열 초기화
    vector<Item> items(n);
    
    // 아이템 배열 채우기
    for (int i = 0; i < n; ++i) {
        // 아이템 인덱스 업데이트
        items[i].index = i;
        // 아이템 이익 업데이트
        items[i].benefit = (rng() % 500) + 1;
        // 아이템 무게 업데이트
        items[i].weight = (rng() % 100) + 1;
        // 아이템 무게 대비 이익 비율 업데이트
        items[i].ratio = (double)items[i].benefit / items[i].weight;
    }
    // 아이템 배열 반환
    return items;
}

// 문자열 중앙 정렬 함수
string center(const string& s, int w) {
    // 문자열 길이와 원하는 길이의 차이를 계산
    int pad = w - (int)s.length();
    // 차이가 0 이하면 그대로 반환
    if (pad <= 0) return s;
    // 왼쪽 패딩 계산
    int pad_left = pad / 2;
    // 오른쪽 패딩 계산
    int pad_right = pad - pad_left;
    // 왼쪽 패딩 + 문자열 + 오른쪽 패딩 반환
    return string(pad_left, ' ') + s + string(pad_right, ' ');
}

// 결과 형식화 
string format_res(double ms, double ben, bool is_float) {
    // 소수점 2자리까지 표시
    ostringstream oss;
    oss << fixed << setprecision(2) << ms << " / ";
    // 소수점 2자리까지 표시
    if (is_float) oss << fixed << setprecision(2) << ben;
    // 정수로 표시
    else oss << (long long)ben;
    // 결과 문자열 반환
    return oss.str();
}

// 수평 선 출력 함수 (테이블 1)
void print_hr1(int w1, int w2) {
    // 수평 선 출력
    cout << "+" << string(w1, '-') << "+" << string(w2, '-') << "+\n";
}

// 수평 선 출력 함수 (테이블 2)
void print_hr2(int w0, int w1, int w2, int w3) {
    // 수평 선 출력
    cout << "+" << string(w0, '-') << "+" << string(w1, '-') << "+" 
         << string(w2, '-') << "+" << string(w3, '-') << "+\n";
}

// 테이블 1 출력 함수 (Brute force)
void print_table1() {

    // 테이블 출력을 위해 하드코딩된 값
    int W1_1 = 17;
    int W1_2 = 59;
    
    // 테이블 1 출력 시작
    cout << "1. Brute force\n";
    // 수평 선 출력
    print_hr1(W1_1, W1_2);
    // 테이블 1 내용 출력
    cout << "|" << center("Number of Items", W1_1) << "|" 
         << center("Processing time in milliseconds / Maximum benefit value", W1_2) << "|\n";
    // 수평 선 출력
    print_hr1(W1_1, W1_2);
    
    // 아이템 개수 배열
    vector<int> bf_sizes = {11, 21, 31};
    for (int n : bf_sizes) {
        vector<Item> items = generate_items(n);
        // 최대 무게 업데이트
        int W = n * 25;
        max_bf_benefit = 0;

        // 시간 측정 시작
        auto start = high_resolution_clock::now();
        // 브루트 포스 실행
        brute_force(items, W, 0, 0, 0);
        // 시간 측정 종료
        auto end = high_resolution_clock::now();
        // 시간 측정 결과 계산
        double ms = duration<double, milli>(end - start).count();
        
        // 테이블 1 내용 출력
        cout << "|" << center(to_string(n), W1_1) << "|"
             << center(format_res(ms, max_bf_benefit, false), W1_2) << "|\n";
        // 수평 선 출력
        print_hr1(W1_1, W1_2);
        // 테이블 1 내용 출력 종료
    }
    cout << "\n";
}

// 테이블 2 출력 함수 (Greedy, Dynamic Programming, Branch and Bound)
void print_table2() {
    // 테이블 2 출력 시작

    // 테이블 출력을 위해 하드코딩된 값
    int W2_0 = 15;
    int W2_1 = 26;
    int W2_2 = 26;
    int W2_3 = 26;
    // 테이블 2 총 너비
    int W2_TOTAL = W2_1 + W2_2 + W2_3 + 2;
    
    // 테이블 2 출력 시작
    cout << "2. Greedy / D.P. / B.&B.\n";
    // 수평 선 출력
    print_hr2(W2_0, W2_1, W2_2, W2_3);
    
    // 테이블 2 내용 출력 시작
    cout << "|" << center("Number of", W2_0) << "|" 
         << center("Processing time in milliseconds / Maximum benefit value", W2_TOTAL) << "|\n";
    // 수평 선 출력
    cout << "|" << center("Items", W2_0) << "+"
         << string(W2_1, '-') << "+" << string(W2_2, '-') << "+" << string(W2_3, '-') << "+\n";
    // 테이블 2 내용 출력 시작
    cout << "|" << center("", W2_0) << "|"
         << center("Greedy", W2_1) << "|"
         << center("D. P.", W2_2) << "|"
         << center("B. & B.", W2_3) << "|\n";
    // 수평 선 출력
    print_hr2(W2_0, W2_1, W2_2, W2_3);
    // 테이블 2 내용 출력 종료
    
    // 아이템 개수 배열
    vector<int> other_sizes = {10, 100, 1000, 10000};
    // 아이템 개수 배열 출력
    for (int n : other_sizes) {
        vector<Item> items = generate_items(n);
        // 최대 무게 업데이트
        int W = n * 25;
        
        // 그리디 시간 측정 시작
        auto s1 = high_resolution_clock::now();
        // 그리디 실행
        double greedy_ans = greedy_fractional(W, items);
        // 시간 측정 종료
        auto e1 = high_resolution_clock::now();
        // 그리디 시간 측정 결과 계산
        double ms1 = duration<double, milli>(e1 - s1).count();

        // 동적 프로그래밍 시간 측정 시작
        auto s2 = high_resolution_clock::now();
        // 동적 프로그래밍 실행
        int dp_ans = dynamic_programming(W, items);
        // 시간 측정 종료
        auto e2 = high_resolution_clock::now();
        // 동적 프로그래밍 시간 측정 결과 계산
        double ms2 = duration<double, milli>(e2 - s2).count();

        // 브랜치 앤 바운드 시간 측정 시작
        auto s3 = high_resolution_clock::now();
        // 브랜치 앤 바운드 실행
        int bb_ans = branch_and_bound(W, items);
        // 시간 측정 종료
        auto e3 = high_resolution_clock::now();
        // 브랜치 앤 바운드 시간 측정 결과 계산
        double ms3 = duration<double, milli>(e3 - s3).count();

        // 테이블 2 내용 출력
        cout << "|" << center(to_string(n), W2_0) << "|"
             << center(format_res(ms1, greedy_ans, true), W2_1) << "|"
             << center(format_res(ms2, dp_ans, false), W2_2) << "|"
             << center(format_res(ms3, bb_ans, false), W2_3) << "|\n";
        // 수평 선 출력
        print_hr2(W2_0, W2_1, W2_2, W2_3);
    }
    // 테이블 2 내용 출력 종료
}

// 메인 함수
int main() {
    // 테이블 1 출력
    print_table1();
    // 테이블 2 출력
    print_table2();
    return 0;
}