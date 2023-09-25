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
        bool operator < (const Node& node) const { return this->v < node.v; } // v�� ��
    };

    vector<vector<Node>> adj_list; //adjacency list used for Prim's algorithm(���� ��� ����Ʈ)
    int n;                         //number of edges(������ ����)
public:
    Graph(int n) : n(n) {
        adj_list = vector<vector<Node>>(n + 1, vector<Node>());// vector<Node>�� �ʱ�ȭ�� n+1 ���� ���Ҹ� ������ ���� ����

    }

    void insert_edge(int u, int v, int w) { // ������ �������(adj_list��)
        adj_list[u].push_back(Node(v, w));
        adj_list[v].push_back(Node(u, w));
    }

    void sort_neighbors() {
        for (auto& neighbors : adj_list) // adj_list���� ���ʷ� ��ü�� ������ neighbors�� ����(auto& : �ʱ�ȭ ���� ���� Ÿ���� �߷��Ͽ� �������ִ� Ű����)
            std::sort(neighbors.begin(), neighbors.end()); // �̿� ÷���� ������ ����(v)
    }

    vector<int> prim(int s) {
        vector<int> prim_sequence; // �Ÿ� ���� 
        priority_queue<pair<int, int>> Q;
        bool S[500001] = { 0, }; // ���� S�� ���Եƴ��� ���� Ȯ��, ���� 0���� �ʱ�ȭ

        prim_sequence.push_back(0); // ���� �������� �Ÿ� 0
        S[s] = 1; // ���� ���� S�� ����

        for (int i = 0; i < adj_list[s].size(); i++) // ���� ���� ����� ��� ��� Q�� ����
        {
            int n_node = adj_list[s][i].v; // ���� ���� ����� ���
            int n_dist = adj_list[s][i].w; // �׶��� ����ġ

            Q.push({ -n_dist, n_node }); // ����� ��带 Q�� ����
        }

        while (!Q.empty()) {
            int now = Q.top().second; // Q���� ����ġ�� ���� ���� ���
            int d = -Q.top().first; // �׶��� ����ġ

            Q.pop(); // now�� Q���� ���� Q.remove();

            if (S[now] == 0) // now�� S�� ������ �� ������
            {
                S[now] = 1; // S�� ���Խ�����
                prim_sequence.push_back(d); // now�� ���� �Ÿ� d

                for (int k = 0; k < adj_list[now].size(); k++) // now�� ����� ��� Ž��
                {
                    int next = adj_list[now][k].v; // now�� ����� ���
                    int next_dist = -adj_list[now][k].w; // �׶��� ����ġ

                    if (S[next] == 0) // next��尡 S�� ���Ծȵ��� ��
                        Q.push({ next_dist, next }); // now�� ����� ��带 Q�� ����
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

    int n; // ��� ��
    int m; // ������ ��
    int i; // �ε���
    cin >> n >> m >> i;

    Graph graph(n); // �׷��� ���� 

    for (int j = 0; j < m; j++) {
        int s, t, w;
        cin >> s >> t >> w;
        graph.insert_edge(s, t, w); // �׷����� ������ �߰� 
    }

    // ����� �̿��� �����ϴ� ������� �ݺ��ǵ��� ����
    graph.sort_neighbors(); // ������ v���� ����

    vector<int> prim_sequence = graph.prim(1); // ù��° ������ ����

    // sum all entries of prim_sequence
    long long cost = std::accumulate(prim_sequence.begin(), prim_sequence.end(), 0L);

    cout << cost << endl;
    cout << prim_sequence[i] << endl; // �ε��� i��°�� ����ġ w 

    return 0;
}