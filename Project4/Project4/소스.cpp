#include<iostream>
#include<queue>
using namespace std;

int in[100001]; // 각 노드의 진입차수를 저장

void topologicalSort(int n, vector<int>adj_list[]) {
	queue<int> Q; // 진입차수가 0인 노드를 저장

	for (int i = 1; i <= n; i++)
	{
		if (in[i] == 0)
			Q.push(i); // 진입 차수가 0인 노드를 Q에 넣음
	}
	

	for (int i = 1; i <= n; i++)
	{
		if (Q.empty())
		{
			cout << "Yes" << endl; // 큐가 비면 사이클이 존재한다는 의미
			return; // 현재있는 함수에서 빠져나감
		}

		int node = Q.front(); // 현재 노드
		Q.pop();

		for (int k = 0; k < adj_list[node].size(); k++)
		{
			int n_node = adj_list[node][k]; // 현재 노드가 가르키는 다음 노드
			in[n_node]--; // 다음 노드의 진입차수를 하나 줄여줌

			if (in[n_node] == 0) // 노드의 진입 차수가 0이면
				Q.push(n_node); // Q에 n_node를 푸시
		}
		
	}cout << "No" << endl;	
}

int main() {
	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m; // 노드, 간선

	vector<int> adj_list[500001]; // 노드와 노드가 가르키는 노드를 저장

	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;

		adj_list[u].push_back(v); // u는 v를 가르킴
		in[v]++; // v를 가르키는 노드의 수+1
	}

	topologicalSort(n, adj_list);
	
	return 0;
}