/*
 * Homework #6
 * Name: 박진우 ID: 22100311
 *
 * References
 *   (1) 강의 slide chapter 16 — All Pairs Shortest Path (Dijkstra, Floyd)
 *
 *   (2) Blog: 다익스트라 우선순위 큐 구현 (ChanBLOG)
 *       https://chanhuiseok.github.io/posts/ds-4/
 *
 *   (3) Blog: C++ priority_queue 사용법
 *       https://jungeu1509.github.io/algorithm/use-priorityqueue/
 *
 *   (4) Blog: 플로이드-워셜 알고리즘 (MinWiki)
 *       https://minboykim.github.io/algorithm/FloydWarshall/
 *
 *   (5) cppreference — std::priority_queue
 *       https://en.cppreference.com/w/cpp/container/priority_queue
 */

 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <string>
 #include <vector>
 #include <queue>
 #include <iomanip>
 #include <climits>
 
 using namespace std;
 
 const long long INF = LLONG_MAX / 4;   // overflow 방지용 큰 값
 
 // 한 행을 탭 기준으로 분리
 static vector<string> split_tab(const string& line) {
     // 토큰 저장
     vector<string> tokens;
     // 문자열 스트림
     stringstream ss(line);
     // 토큰
     string tok;
     // 탭 기준으로 분리
     while (getline(ss, tok, '\t')) {
         // 끝의 \r(윈도우 개행) 제거
         while (!tok.empty() && (tok.back() == '\r' || tok.back() == '\n'))
             // 끝의 \r(윈도우 개행) 제거
             tok.pop_back();
         // 토큰 저장
         tokens.push_back(tok);
     }
     // 토큰 반환
     return tokens;
 }
 
 
 int main(int argc, char* argv[]) {
     // 데이터 파일 읽기
     string fname = (argc > 1) ? argv[1] : "hw6.data";
     // 파일 열기
     ifstream fin(fname);
     if (!fin) {
         cerr << "Cannot open file: " << fname << endl;
         return 1;
     }
 
     // 입력 파일 읽기
 
     // 도시 이름
     vector<string> names;       
     // 인접행렬
     vector<vector<long long>> adj;  
 
     string line;
 
     // 각 행: [도시이름]\t[값들...] 형식 (별도 헤더 행 없음)
     // 각 도시 행 읽기
     while (getline(fin, line)) {
         // 빈 줄 제거
         if (line.empty()) continue;
         // 탭 기준으로 분리
         vector<string> tok = split_tab(line);
         // 도시명 + 최소 1개 값
         if (tok.size() < 2) continue;
         // 첫 토큰 = 도시 이름
         names.push_back(tok[0]);
         // 행 생성
         vector<long long> row;
         // 나머지 토큰 = 거리 값
         for (size_t j = 1; j < tok.size(); j++) {
             const string& v = tok[j];
             // 빈 토큰 무시
             if (v.empty()) continue;
             // INF 또는 inf 이면 INF 설정
             if (v == "INF" || v == "inf")
                 row.push_back(INF);
             // 그 외 값 설정
             else
                 row.push_back(stoll(v));
         }
         // 행렬 생성
         adj.push_back(row);
     }
     fin.close();
 
     // 도시 개수
     int n = (int)names.size();
     // 데이터 없으면 오류
     if (n == 0) {
         cerr << "No data read from file." << endl;
         return 1;
     }
     // 정방행렬 크기 체크
     for (int i = 0; i < n; i++) {
         if ((int)adj[i].size() != n) {
             cerr << "Matrix size mismatch at row " << i
                  << " (expected " << n << ", got " << adj[i].size() << ")" << endl;
             return 1;
         }
     }
 
     // 출력 표 너비 계산
     int w = 8;
     for (const string& s : names) w = max(w, (int)s.size() + 2);
     // 출력 표 너비 계산
 
     // 출력 표 출력 함수
     auto printTable = [&](const vector<vector<long long>>& dist) {
         // 헤더 출력
         cout << setw(w) << " ";
         // 도시 이름 출력
         for (int j = 0; j < n; j++) cout << setw(w) << names[j];
         // 줄 바꿈
         cout << "\n";
         for (int i = 0; i < n; i++) {
             // 도시 이름 출력
             cout << setw(w) << names[i];
             // 각 도시 값 출력
             for (int j = 0; j < n; j++) {
                 // INF 출력
                 if (dist[i][j] >= INF) cout << setw(w) << "INF";
                 // 그 외 값 출력
                 else                   cout << setw(w) << dist[i][j];
             }
             // 줄 바꿈
             cout << "\n";
         }
     };
 
     // a) Dijkstra |V| times 알고리즘
     vector<vector<long long>> distD(n, vector<long long>(n, INF));
 
     // 각 도시에 대해 Dijkstra 알고리즘 실행
     for (int src = 0; src < n; src++) {
         // 거리 배열 초기화
         vector<long long> d(n, INF);
         // 시작 도시 거리 0
         d[src] = 0;
         // 우선순위 큐 -> 거리, 정점
         // 최소 힙 -> 거리, 정점
         priority_queue <pair<long long,int>,
                        vector<pair<long long,int>>,
                        greater<pair<long long,int>>> pq;
         // 시작 도시 거리 0
         pq.push({0, src});
         // 우선순위 큐가 비어있지 않으면 계속 진행
         while (!pq.empty()) {
             // 거리
             long long cd = pq.top().first;
             // 정점
             int u = pq.top().second;
             pq.pop();
             // 거리가 이미 최소 거리보다 크면 무시
             if (cd > d[u]) continue;            
             // 각 도시에 대해 거리 계산
             for (int v = 0; v < n; v++) {
                 // 직접 연결 없으면 무시
                 if (adj[u][v] >= INF) continue;  
                 // 거리 계산
                 long long nd = cd + adj[u][v];
                 // 거리가 이미 최소 거리보다 작으면 업데이트
                 if (nd < d[v]) {
                     // 거리 업데이트
                     d[v] = nd;
                     // 우선순위 큐에 추가
                     pq.push({nd, v});
                 }
             }
         }
         // 거리 배열 업데이트
         distD[src] = d;
     }
 
     // 출력
     cout << "The shortest distance between cities using Dijkstra's algorithm is:\n\n";
     printTable(distD);
     cout << "\n";
 
     // b) Floyd's algorithm 알고리즘
     // 인접행렬 복사
     vector<vector<long long>> distF = adj;   
     // 자기 자신으로 가는 거리 0
     for (int i = 0; i < n; i++) distF[i][i] = 0;
 
     // 각 도시에 대해 Floyd 알고리즘 실행
     for (int k = 0; k < n; k++)
         for (int i = 0; i < n; i++) {
             // 불필요 연산 + overflow 방지
             if (distF[i][k] >= INF) continue;        
             // 각 도시에 대해 거리 계산
             for (int j = 0; j < n; j++) {
                 // 불필요 연산 + overflow 방지
                 if (distF[k][j] >= INF) continue;
                 // 거리 계산
                 long long nd = distF[i][k] + distF[k][j];
                 // 거리가 이미 최소 거리보다 작으면 업데이트
                 if (nd < distF[i][j]) distF[i][j] = nd;
             }
         }
 
     // 출력
     cout << "The shortest distance between cities using Floyd's algorithm is:\n\n";
     printTable(distF);
     cout << "\n";
 
     return 0;
 }
 