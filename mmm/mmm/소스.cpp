#include <iostream>
#include <vector>
#include<queue>
#define DUMMY 0
#define INF 1e9 
using namespace std;

vector<int> dijkstra(int s, int n, vector < pair<int, int>> adj_list[]) {

	vector<int>dist(n+1, INF);
	
	priority_queue<pair<int, int>> Q; // 목적지와 거리

	dist[s] = 0; // s까지 거리 0 설정
	Q.push(make_pair(0, s)); // s까지 가는 데 걸리는 거리를 0으로 설정

	while (!Q.empty()) {

		int d = -Q.top().first; // 현재 노드까지의 거리, 거리가 작은 원소부터 꺼내지도록 - 붙임
		int node = Q.top().second; // 현재 노드

		Q.pop();

		for (int i = 0; i < adj_list[node].size(); i++)
		{
			int n_node = adj_list[node][i].first; // 다음 노드
			int n_dist = d + adj_list[node][i].second; // 다음노드까지의 거리

			if (n_dist < dist[n_node])
			{
				dist[n_node] = n_dist; // 거리를 새롭게 갱신
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

	int n, m; // 노드, 간선
	int s; // 시작 정점

	cin >> n >> m >> s;

	vector<pair<int, int>> adj_list[1000001]; // 노드와 연결된 노드, 거리 저장

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
			cout << dist[k] << endl; // s에서 k까지의 거리 출력
	}
}
