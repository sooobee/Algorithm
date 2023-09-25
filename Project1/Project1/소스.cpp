#include<iostream>
#include<algorithm>
#include<vector>
#include<numeric>
#define DUMMY 0
#define INF 1e9 // ������ ǥ���� �� ���

using namespace std;

class DisjointSet { // �и��� set
private:
	vector<int> p; // �θ� ���
	vector<int> rank; // Ʈ���� ����
public:
	DisjointSet(int n) {
		p = vector<int>(n + 1);
		rank = vector<int>(n + 1);
	}

	void make(int u) { p[u] = u; rank[u] = 0; } // ���ο� ��� u ����
	
	int find(int u) { // u�� �θ� ��� ã��
		if (p[u] != u) p[u] = find(p[u]); 
		return p[u];
	}

	bool merge(int u, int v) {  // u�� ���� ���հ� v�� ���� ������ ��ħ 
		int ur = find(u); // u�� �θ� ���
		int vr = find(v); // v�� �θ� ���

		if (ur == vr) return false; // �θ� ������ false -> ����Ŭ�� ����

		if (rank[ur] > rank[vr]) p[vr] = ur;  
		else { 
			p[ur] = vr;

			// Ʈ���� ���̰� ���� ��� Ʈ���� rank+1 ���ش�
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
		bool operator < (const Edge& edge) const { return this->w < edge.w; } // ����ġ ���� ���� �켱 ����
	};

	vector<Edge> edges; // edge ����Ʈ
	int n; // edge�� ����
public:
	Graph(int n) : n(n) {
		edges = vector<Edge>(); // edge ���͸� ����
	}

	void insert_edge(int u, int v, int w) {
		edges.push_back(Edge(u, v, w)); // u, v, w�� ���� ������ push
	}

	vector<int> kruskal() {
		vector<int> kruskal_sequence(1, DUMMY); // ������ w ���� 
		DisjointSet set(n);

		// w�� ������������ ����
		sort(edges.begin(), edges.end()); 

		// �ʱ�ȭ
		for (int i = 1; i <= n; i++)
			set.make(i); // set�� n���� ��带 ����, �θ���� �ڱ��ڽ��� ����Ŵ

		// w�� ���� ���� ������� ����, ����Ŭ�� ����
		for (int k = 0; k < edges.size(); k++) // ������ ������ŭ �ݺ�
		{
			if (set.find(edges[k].u) != set.find(edges[k].v)) // u, v �θ� ���� ���� ���(����Ŭ ����)
			{
				set.merge(edges[k].u, edges[k].v); // 2���� ��带 ����
				kruskal_sequence.push_back(edges[k].w); // ���� ���� w���� ������
			}
		}
			
		//  - kruskal�� ���� ������ ������ ����ġ�� kruskal_sequence�� push_back��(push back the weight of an edge selected by Kruskal into kruskal_sequence)
		//    (use kruskal_sequence.push_back(int weight))

		return kruskal_sequence;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n; // ����(���)�� ��
	int m; // ����(edge)�� ��
	int i; // ����ؾ��� �ε���
	cin >> n >> m >> i; 

	Graph graph(n); // n���� ������ ���� �׷��� ����

	for (int j = 0; j < m; j++) {
		int s, t, w; // ��� s, t, �� ����ġ w
		cin >> s >> t >> w;

		graph.insert_edge(s, t, w); //graph�� s, t, w�� ���� 
	}

	vector<int> kruskal_sequence = graph.kruskal();

	// kruskal_sequence�� ��� �׸� �հ�(sum all entries of kruskal_sequence)
	long long cost = std::accumulate(kruskal_sequence.begin(), kruskal_sequence.end(), 0L);

	cout << cost << endl; // MST cost
	cout << kruskal_sequence[i] << endl; // i��° ������ ����ġ

	return 0;
}