#include <iostream>
#include <vector>
#include<queue>
#define DUMMY 0
#define INF 1e9 
using namespace std;

vector<int> dijkstra(int s, int n, vector < pair<int, int>> adj_list[]) {

	vector<int>dist(n+1, INF);
	
	priority_queue<pair<int, int>> Q; // �������� �Ÿ�

	dist[s] = 0; // s���� �Ÿ� 0 ����
	Q.push(make_pair(0, s)); // s���� ���� �� �ɸ��� �Ÿ��� 0���� ����

	while (!Q.empty()) {

		int d = -Q.top().first; // ���� �������� �Ÿ�, �Ÿ��� ���� ���Һ��� ���������� - ����
		int node = Q.top().second; // ���� ���

		Q.pop();

		for (int i = 0; i < adj_list[node].size(); i++)
		{
			int n_node = adj_list[node][i].first; // ���� ���
			int n_dist = d + adj_list[node][i].second; // ������������ �Ÿ�

			if (n_dist < dist[n_node])
			{
				dist[n_node] = n_dist; // �Ÿ��� ���Ӱ� ����
				Q.push(make_pair(-n_dist, n_node));
			}
		}
	}
	return dist;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m; // ���, ����
	int s; // ���� ����

	cin >> n >> m >> s;

	vector<pair<int, int>> adj_list[1000001]; // ���� ����� ���, �Ÿ� ����

	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;

		adj_list[u].push_back(make_pair(v, w));
		adj_list[v].push_back(make_pair(u, w));
	}

	vector<int>dist = dijkstra(s, n, adj_list);

	for (int k = 1; k <= n; k++) {

		if (dist[k] == INF)
			cout << "INF" << endl;

		else
			cout << dist[k] << endl; // s���� k������ �Ÿ� ���
	}
}
