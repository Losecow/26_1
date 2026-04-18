#include <iostream>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 재귀 방식을 이용한 유리구슬 떨어뜨리기 문제 해결 함수
// k: 유리구슬의 개수, n: 건물의 층 수
int recursive(int k, int n) {
    // Base case (기저 조건)
    // 층이 0이거나 1인 경우, 각각 0번 또는 1번의 시도가 필요함
    if (n == 0 || n == 1) return n;
    
    // 유리구슬이 1개인 경우, 1층부터 n층까지 순서대로 모두 시도해야 함
    if (k == 1) return n;


    // 최소 시도 횟수를 찾기 위해 초기값을 매우 큰 수로 설정
    int min_drops = INT_MAX;
    
    // 1층부터 n층까지(x층) 모든 층에서 떨어뜨려보고, 최악의 경우 중 최소 시도 횟수를 찾음
    for (int x = 1; x <= n; x++) {
        // case1: 유리구슬이 깨진 경우 -> 구슬 개수는 1개 줄고, 남은 탐색 층은 x-1층이 됨
        int case1 = recursive(k - 1, x - 1);
        
        // case2: 유리구슬이 깨지지 않은 경우 -> 구슬 개수는 그대로, 남은 탐색 층은 n-x층이 됨
        int case2 = recursive(k, n - x);
        
        // 최악의 상황(worst_case)을 고려하기 위해 두 경우 중 더 큰 값을 선택하고,
        // 현재 층에서 떨어뜨린 1회의 시도를 더해줌
        int worst_case = 1 + max(case1, case2);
        
        // 모든 시도 중 가장 최소가 되는 횟수를 업데이트
        min_drops = min(min_drops, worst_case);
    }
    
    return min_drops;
}

// 동적 계획법(DP)을 이용한 유리구슬 떨어뜨리기 문제 해결 함수
// k: 유리구슬의 개수, n: 건물의 층 수
int DP(int k, int n) {
    // DP Table: dp[i][j]는 i개의 유리구슬로 j층 건물을 탐색할 때 필요한 최소 시도 횟수
    // DP Table 초기화 (k+1) x (n+1) 크기로 초기화 (k개의 구슬과 n개의 층을 고려)
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 0));

    // Base cases 채우기
    for (int i = 1; i <= k; i++) {
        // 건물이 0층이면 시도할 필요가 없고, 1층이면 1번의 시도만 필요
        dp[i][0] = 0;
        dp[i][1] = 1;
    }

    for (int j = 1; j <= n; j++) {
        // 유리구슬이 1개뿐이라면 j층까지 전부 확인해야 하므로 j번 시도해야 함
        dp[1][j] = j;
    }

    // DP 테이블 채우기 (구슬은 2개부터, 층수도 2층부터 채워나감)
    for (int i = 2; i <= k; i++) {       // 구슬의 개수
        for (int j = 2; j <= n; j++) {   // 층의 수
            dp[i][j] = INT_MAX;          // 초기값은 매우 큰 수로 설정
            
            // 1층부터 j층까지(x층) 떨어뜨리는 경우를 모두 시도
            for (int x = 1; x <= j; x++) {
                // b (깨진 경우): 남은 구슬 (i-1)개로 아래의 (x-1)개 층 확인
                int b = dp[i - 1][x - 1];
                
                // s (안 깨진 경우): 남은 구슬 i개로 위의 (j-x)개 층 확인
                int s = dp[i][j - x];
                
                // 최악의 경우를 선택하고 1회 시도를 더함
                int worst = 1 + max(b, s);
                
                // 지금까지의 최소 시도 횟수와 비교하여 갱신
                dp[i][j] = min(dp[i][j], worst); 
            } 
        } 
    }

    return dp[k][n];
}

int main() {

    int n, k;
    cout << "건물의 층 수(n)를 입력하세요: ";
    cin >> n;

    cout << "유리구슬의 개수(k)를 입력하세요: ";
    cin >> k;

    // DP 방법 실행 및 시간 측정

    // 1. 시간 측정 시작
    auto start_dp = high_resolution_clock::now();
    // 2. DP 방법 실행
    int res_dp = DP(k, n);
    // 3. 시간 측정 종료
    auto end_dp = high_resolution_clock::now();
    // 4. 시간 측정 결과 계산
    auto duration_dp = duration_cast<microseconds>(end_dp - start_dp);

    cout << "\n[동적 계획법 (DP) 결과]" << endl;
    cout << "최소 시도 횟수: " << res_dp << endl;
    cout << "실행 시간: " << duration_dp.count() << " microseconds" << endl;

   
    // 재귀 방법 실행 및 시간 측정
    
    // 1. 시간 측정 시작
    auto start_rec = high_resolution_clock::now();
    // 2. 재귀 방법 실행
    int res_rec = recursive(k, n);
    // 3. 시간 측정 종료
    auto end_rec = high_resolution_clock::now();
    // 4. 시간 측정 결과 계산
    auto duration_rec = duration_cast<microseconds>(end_rec - start_rec);

    cout << "\n[재귀 방식 (Recursive) 결과]" << endl;
    cout << "최소 시도 횟수: " << res_rec << endl;
    cout << "실행 시간: " << duration_rec.count() << " microseconds" << endl;

    return 0;
}