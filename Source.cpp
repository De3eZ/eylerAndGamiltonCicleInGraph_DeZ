#include <iostream>

using namespace std;

struct List
{
	int inf;
	List* next;
};

void push(List*& st, int dat)
{
	List* el = new List;
	el->inf = dat;
	el->next = st;
	st = el;
}

int pop(List*& st)
{
	int value = st->inf;
	List* temp = st;
	st = st->next;
	delete temp;

	return value;
}

int peek(List* st)
{
	return st->inf;
}

void add(List*& list, int data)
{
	if (!list)
	{
		list = new List;
		list->inf = data;
		list->next = 0;
		return;
	}

	List* temp = list;
	while (temp->next)
	{
		temp = temp->next;
	}
	List* elem = new List;
	elem->inf = data;
	elem->next = NULL;
	temp->next = elem;
}

void del(List*& l, int key)
{
	if (l->inf == key) { List* tmp = l; l = l->next; delete tmp; }
	else
	{
		List* tmp = l;
		while (tmp)
		{
			if (tmp->next)
				if (tmp->next->inf == key)
				{
					List* tmp2 = tmp->next;
					tmp->next = tmp->next->next;
					delete tmp2;
				}
			tmp = tmp->next;
		}
	}
}

int eiler(List** gr, int num)
{
	int count;
	for (int i = 0; i < num; i++)
	{
		count = 0;
		List* tmp = gr[i];

		while (tmp)
		{
			count++;
			tmp = tmp->next;
		}
		if (count % 2 == 1)return 0;
	}
	return 1;
}

void eiler_path(List** gr, int vertex)
{
	List* S = NULL;
	int v = vertex;
	int u;

	push(S, v);
	while (S)
	{
		v = peek(S);
		if (!gr[v])
		{
			v = pop(S);
			cout << v + 1 << " ";
		}
		else
		{
			u = gr[v]->inf;
			push(S, u);
			del(gr[v], u);
			del(gr[u], v);
		}
	}
}

bool gamilton(int n, int** a, int k, int* c, int* path, int v0)
{
	bool q1 = false;

	for (int v = 0; v < n && !q1; v++)
	{
		if (a[v][path[k - 1]] || a[path[k - 1]][v])
		{
			if (k == n && v == v0)
				q1 = 1;
			else if (c[v] == -1)
			{
				c[v] = k; path[k] = v;
				q1 = gamilton(n, a, k + 1, c, path, v0);
				if (!q1) c[v] = -1;
			}
			else continue;
		}
	}   return q1;
}

void printGamilton(int n, int* path)
{
	int p;
	for (p = 0; p < n; p++)
		printf("%d ", path[p] + 1);
	printf("%d ", path[0] + 1);
	printf("\n");
}

int main()
{
	setlocale(LC_ALL, "Russian");

	int size;
	cout << "Введите количество элементов графа: ";
	cin >> size;

	int** graf = new int* [size];

	for (int i = 0; i < size; i++)
	{
		graf[i] = new int[size];
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			graf[i][j] = 0;
		}
	}

	int var;

	cout << "Заполните граф" << endl;

	for (int i = 0; i < size; i++)
	{
		var = 1;

		cout << "Введите с какими вершинами соединён " << i + 1 << " используя цифры, если ввели все вершины, то введите 0" << endl;

		while (var != 0)
		{
			cin >> var;

			if (var != 0)
			{
				graf[i][var - 1] = 1;
			}
		}
	}

	int v0;
	cout << "С какой вершины начать?" << endl;
	cin >> v0;
	v0--;

	int zn;

	List** graph = new List * [size];
	for (int i = 0; i < size; i++)
	{
		graph[i] = NULL;
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (graf[i][j])
			{
				add(graph[i], j);
			}
		}
	}
	system("cls");

	cout << "Таблица смежности: " << endl;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << graf[i][j] << " ";
		}
		cout << endl;
	}

	int* c = new int(size);
	int* path = new int(size);


	for (int j = 0; j < size; j++)
		c[j] = -1;
	path[0] = v0;
	c[v0] = v0;
	cout << "Эйлеров цикл: ";

	if (eiler(graph, size))
	{
		eiler_path(graph, v0);
		cout << endl;
	}
	else
	{
		cout << "Отсутствует" << endl;
	}

	cout << "Гамильтонов цикл: ";
	if (gamilton(size, graf, 1, c, path, v0))
	{
		printGamilton(size, path);
	}
	else {
		cout << "Отсутствует" << endl;
	}
	return 0;
}