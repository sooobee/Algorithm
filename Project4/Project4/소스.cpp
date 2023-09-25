#include<iostream>
#include<queue>
using namespace std;

int in[100001]; // �� ����� ���������� ����

void topologicalSort(int n, vector<int>adj_list[]) {
	queue<int> Q; // ���������� 0�� ��带 ����

	for (int i = 1; i <= n; i++)
	{
		if (in[i] == 0)
			Q.push(i); // ���� ������ 0�� ��带 Q�� ����
	}
	

	for (int i = 1; i <= n; i++)
	{
		if (Q.empty())
		{
			cout << "Yes" << endl; // ť�� ��� ����Ŭ�� �����Ѵٴ� �ǹ�
			return; // �����ִ� �Լ����� ��������
		}

		int node = Q.front(); // ���� ���
		Q.pop();

		for (int k = 0; k < adj_list[node].size(); k++)
		{
			int n_node = adj_list[node][k]; // ���� ��尡 ����Ű�� ���� ���
			in[n_node]--; // ���� ����� ���������� �ϳ� �ٿ���

			if (in[n_node] == 0) // ����� ���� ������ 0�̸�
				Q.push(n_node); // Q�� n_node�� Ǫ��
		}
		
	}cout << "No" << endl;	
}

int main() {
	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m; // ���, ����

	vector<int> adj_list[500001]; // ���� ��尡 ����Ű�� ��带 ����

	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;

		adj_list[u].push_back(v); // u�� v�� ����Ŵ
		in[v]++; // v�� ����Ű�� ����� ��+1
	}

	topologicalSort(n, adj_list);
	
	return 0;
}