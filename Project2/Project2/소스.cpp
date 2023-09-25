#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <queue>
#define DUMMY 0
#define INF 1e9 // use this to represent the infinity

using namespace std;

class Graph {
private:
    struct Node {
        int v; int w;
        Node(int v, int w) : v(v), w(w) { }
        bool operator < (const Node& node) const { return this->v < node.v; } // v를 비교
    };

    vector<vector<Node>> adj_list; //adjacency list used for Prim's algorithm(인접 목록 리스트)
    int n;                         //number of edges(간선의 개수)
public:
    Graph(int n) : n(n) {
        adj_list = vector<vector<Node>>(n + 1, vector<Node>());// vector<Node>로 초기화된 n+1 개의 원소를 가지는 벡터 생성

    }

    void insert_edge(int u, int v, int w) { // 간선을 집어넣음(adj_list에)
        adj_list[u].push_back(Node(v, w));
        adj_list[v].push_back(Node(u, w));
    }

    void sort_neighbors() {
        for (auto& neighbors : adj_list) // adj_list에서 차례로 객체를 꺼내서 neighbors에 넣음(auto& : 초기화 값에 따라 타입을 추론하여 결정해주는 키워드)
            std::sort(neighbors.begin(), neighbors.end()); // 이웃 첨부터 끝까지 정렬(v)
    }

    vector<int> prim(int s) {
        vector<int> prim_sequence; // 거리 저장 
        priority_queue<pair<int, int>> Q;
        bool S[500001] = { 0, }; // 집합 S에 포함됐는지 여부 확인, 전부 0으로 초기화

        prim_sequence.push_back(0); // 시작 노드까지의 거리 0
        S[s] = 1; // 시작 노드는 S에 포함

        for (int i = 0; i < adj_list[s].size(); i++) // 시작 노드와 연결된 노드 모두 Q에 넣음
        {
            int n_node = adj_list[s][i].v; // 시작 노드와 연결된 노드
            int n_dist = adj_list[s][i].w; // 그때의 가중치

            Q.push({ -n_dist, n_node }); // 연결된 노드를 Q에 넣음
        }

        while (!Q.empty()) {
            int now = Q.top().second; // Q에서 가중치가 가장 작은 노드
            int d = -Q.top().first; // 그때의 가중치

            Q.pop(); // now를 Q에서 삭제 Q.remove();

            if (S[now] == 0) // now가 S에 포함이 안 됐을때
            {
                S[now] = 1; // S에 포함시켜줌
                prim_sequence.push_back(d); // now일 때의 거리 d

                for (int k = 0; k < adj_list[now].size(); k++) // now와 연결된 노드 탐색
                {
                    int next = adj_list[now][k].v; // now와 연결된 노드
                    int next_dist = -adj_list[now][k].w; // 그때의 가중치

                    if (S[next] == 0) // next노드가 S에 포함안됐을 때
                        Q.push({ next_dist, next }); // now와 연결된 노드를 Q에 넣음
                }
            }
        }
        return prim_sequence;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n; // 노드 수
    int m; // 간선의 수
    int i; // 인덱스
    cin >> n >> m >> i;

    Graph graph(n); // 그래프 선언 

    for (int j = 0; j < m; j++) {
        int s, t, w;
        cin >> s >> t >> w;
        graph.insert_edge(s, t, w); // 그래프에 간선을 추가 
    }

    // 노드의 이웃이 증가하는 순서대로 반복되도록 보장
    graph.sort_neighbors(); // 간선의 v들을 정렬

    vector<int> prim_sequence = graph.prim(1); // 첫번째 노드부터 시작

    // sum all entries of prim_sequence
    long long cost = std::accumulate(prim_sequence.begin(), prim_sequence.end(), 0L);

    cout << cost << endl;
    cout << prim_sequence[i] << endl; // 인덱스 i번째의 가중치 w 

    return 0;
}