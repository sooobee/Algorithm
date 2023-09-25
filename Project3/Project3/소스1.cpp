#include <stdio.h>
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define INF 1e9 // ������ �ǹ��ϴ� ������ 10���� ����

// ����� ����(N), ������ ����(M), ���� ��� ��ȣ(Start)
// ����� ������ �ִ� 100,000����� ����
int n, m, start;

vector<pair<int, int> > graph[100001]; // �� ��忡 ����Ǿ� �ִ� ��忡 ���� ������ ��� �迭
int d[100001]; // �ִ� �Ÿ� ���̺� �����

void dijkstra(int start)
{
    priority_queue<pair<int, int>>pq; // �Ÿ�, ��� �ε���

    pq.push({ 0,start }); //���� ���� �������� �ִ� ��δ� 0���� �����Ͽ�, ť�� ����.
    d[start] = 0;

    while (!pq.empty())
    {
        int dist = -pq.top().first; //���� �������� ���
        int now = pq.top().second; // ���� ���
        pq.pop();

        if (d[now] < dist) // �̹� �ִܰ�θ� üũ�� ����� ��� �н�
            continue;

        for (int i = 0; i < graph[now].size(); i++)
        {
            int cost = dist + graph[now][i].second; // ���ļ� ���� ����� ����� ���
                                                  // ��������� ��� + ���� ��� ���
            if (cost < d[graph[now][i].first]) // ����� �� �۴ٸ� �ִܰ�� ���̺� ���� ����.
            {
                d[graph[now][i].first] = cost;
                pq.push(make_pair(-cost, graph[now][i].first));
            }
        }
    }
}

int main(void)
{
    cin >> n >> m >> start;

    // ��� ���� ������ �Է¹ޱ�
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        // a�� ��忡�� b�� ���� ���� ����� c��� �ǹ�
        graph[a].push_back({ b, c });
    }

    // �ִ� �Ÿ� ���̺��� ��� �������� �ʱ�ȭ
    fill(d, d + 100001, INF);

    // ���ͽ�Ʈ�� �˰����� ����
    dijkstra(start);

    // ��� ���� ���� ���� �ִ� �Ÿ��� ���
    for (int i = 1; i <= n; i++)
    {
        // ������ �� ���� ���, ����(INFINITY)�̶�� ���
        if (d[i] == INF) {
            cout << "INFINITY" << '\n';
        }
        // ������ �� �ִ� ��� �Ÿ��� ���
        else {
            cout << d[i] << '\n';
        }
    }
}