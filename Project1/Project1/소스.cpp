#include<iostream>
#include<algorithm>
#include<vector>
#include<numeric>
#define DUMMY 0
#define INF 1e9 // 무한을 표현할 때 사용

using namespace std;

class DisjointSet { // 분리된 set
private:
	vector<int> p; // 부모 노드
	vector<int> rank; // 트리의 높이
public:
	DisjointSet(int n) {
		p = vector<int>(n + 1);
		rank = vector<int>(n + 1);
	}

	void make(int u) { p[u] = u; rank[u] = 0; } // 새로운 요소 u 만듬
	
	int find(int u) { // u의 부모 노드 찾음
		if (p[u] != u) p[u] = find(p[u]); 
		return p[u];
	}

	bool merge(int u, int v) {  // u를 가진 집합과 v를 가진 집합을 합침 
		int ur = find(u); // u의 부모 노드
		int vr = find(v); // v의 부모 노드

		if (ur == vr) return false; // 부모가 같으면 false -> 사이클이 생김

		if (rank[ur] > rank[vr]) p[vr] = ur;  
		else { 
			p[ur] = vr;

			// 트리의 높이가 같은 경우 트리의 rank+1 해준다
			if (rank[ur] == rank[vr]) rank[vr] = rank[vr] + 1;
		}
		return true;
	}
};

class Graph {
private:
	struct Edge {
		int u; int v; int w;
		Edge(int u, int v, int w) : u(u), v(v), w(w) {}
		bool operator < (const Edge& edge) const { return this->w < edge.w; } // 가중치 적은 것을 우선 정렬
	};

	vector<Edge> edges; // edge 리스트
	int n; // edge의 개수
public:
	Graph(int n) : n(n) {
		edges = vector<Edge>(); // edge 벡터를 생성
	}

	void insert_edge(int u, int v, int w) {
		edges.push_back(Edge(u, v, w)); // u, v, w를 가진 엣지를 push
	}

	vector<int> kruskal() {
		vector<int> kruskal_sequence(1, DUMMY); // 엣지의 w 저장 
		DisjointSet set(n);

		// w를 오름차순으로 정렬
		sort(edges.begin(), edges.end()); 

		// 초기화
		for (int i = 1; i <= n; i++)
			set.make(i); // set에 n개의 노드를 만듬, 부모노드는 자기자신을 가르킴

		// w가 작은 간선 순서대로 연결, 사이클은 피함
		for (int k = 0; k < edges.size(); k++) // 간선의 개수만큼 반복
		{
			if (set.find(edges[k].u) != set.find(edges[k].v)) // u, v 부모가 같지 않을 경우(사이클 방지)
			{
				set.merge(edges[k].u, edges[k].v); // 2개의 노드를 연결
				kruskal_sequence.push_back(edges[k].w); // 가장 작은 w부터 들어가야함
			}
		}
			
		//  - kruskal에 의해 선정된 엣지의 가중치를 kruskal_sequence로 push_back함(push back the weight of an edge selected by Kruskal into kruskal_sequence)
		//    (use kruskal_sequence.push_back(int weight))

		return kruskal_sequence;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n; // 정점(노드)의 수
	int m; // 간선(edge)의 수
	int i; // 출력해야할 인덱스
	cin >> n >> m >> i; 

	Graph graph(n); // n개의 정점을 가진 그래프 생성

	for (int j = 0; j < m; j++) {
		int s, t, w; // 노드 s, t, 와 가중치 w
		cin >> s >> t >> w;

		graph.insert_edge(s, t, w); //graph에 s, t, w를 삽입 
	}

	vector<int> kruskal_sequence = graph.kruskal();

	// kruskal_sequence의 모든 항목 합계(sum all entries of kruskal_sequence)
	long long cost = std::accumulate(kruskal_sequence.begin(), kruskal_sequence.end(), 0L);

	cout << cost << endl; // MST cost
	cout << kruskal_sequence[i] << endl; // i번째 간선의 가중치

	return 0;
}