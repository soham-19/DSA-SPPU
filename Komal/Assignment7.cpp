//assignment 7
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
class graphnode
{
public:
    int vertex;
    graphnode *next;
};
class graph
{
public:
    graphnode *header[10];
    int n = 0;
    int visited[10];
    graph()
    {
        for (int i = 0; i < 10; i++)
        {
            header[i] = new graphnode;
            header[i]->vertex = i;
            header[i]->next = NULL;
            visited[i] = 0;
        }
    }
    void createlist();
    int visite(int);
    void dfs();
    void bfs();
};
void graph::createlist()
{

    graphnode *New, *temp;
    int v1, v2;

    cout << "enter edge vertex 1:";
    cin >> v1;
    cout << "enter edge vertex 2:";
    cin >> v2;
    cout << endl;
    New = new graphnode;
    New->vertex = v2;
    New->next = NULL;
    if (header[v1]->next == NULL)
    {
        header[v1]->next = New;
    }
    else
    {
        temp = new graphnode;
        temp = header[v1]->next;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        if (temp->next == NULL)
        {
            temp->next = New;
        }
    }
    n++;
}
int graph::visite(int x)
{
    if (visited[x] == 1)
        return 1;
    else
        return 0;
}
void graph::dfs()
{
    stack<graphnode *> s;
    int visited[n], x, m;
    graphnode *v, *temp;
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    cout << "enter from which point do you want to start:";
    cin >> x;
    for (int j = 0; j < n; j++)
    {
        if (header[j]->vertex == x)
        {
            m = j;
        }
    }
    s.push(header[m]);
    while (!s.empty())
    {
        v = s.top();
        if (visited[v->vertex] != 1)
        {
            cout << v->vertex << "-->";
        }
        s.pop();
        if (!visite(v->vertex))
        {
            visited[v->vertex] = 1;
            temp = new graphnode;
            temp = header[v->vertex]->next;
            while (temp != NULL)
            {
                s.push(temp);
                temp = temp->next;
            }
        }
        else
        {
            v = s.top();
            s.pop();
        }
    }
}
void graph::bfs()
{
    queue<graphnode *> s;
    int visited[n], x, m;
    graphnode *v, *temp;
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    cout << "enter from which point do you want to start:";
    cin >> x;
    for (int j = 0; j < n; j++)
    {
        if (header[j]->vertex == x)
        {
            m = j;
        }
    }
    s.push(header[m]);
    while (!s.empty())
    {
        v = s.front();
        if (visited[v->vertex] != 1)
        {
            cout << v->vertex << "-->";
        }
        s.pop();
        if (!visite(v->vertex))
        {
            visited[v->vertex] = 1;
            temp = new graphnode;
            temp = header[v->vertex]->next;
            while (temp != NULL)
            {
                s.push(temp);
                temp = temp->next;
            }
        }
        else
        {
            v = s.front();
            s.pop();
        }
    }
}
int main()
{
    graph g;
    int ch;
    do
    {
        cout << "\n\nGraph operations" << endl;
        cout << "\n1.insert edge\n2.Depth First Search\n3.Breadth First Search" << endl;
        cout << "Enter your choice:";
        cin >> ch;
        switch (ch)
        {
        case 1:
            g.createlist();
            break;
        case 2:
            g.dfs();
            break;
        case 3:
            g.bfs();
            break;
        default:
            cout << "enter valid choice" << endl;
            break;
        }
    } while (ch != 0);
}