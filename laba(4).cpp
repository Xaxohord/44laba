#include <iostream>
#include<chrono>
#include<vector>

using namespace std;


class Timer
{
private:
	using clock_t = chrono::high_resolution_clock;
	using second_t = chrono::duration<double, ratio<1> >;

	chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};
struct T_List
{
	T_List* next;
	int x;
};

void ADD(T_List* head, int x)
{
	T_List* p = new T_List;
	p->x = x;
	p->next = head->next;
	head->next = p;

}

void PRINT(T_List* head)
{
	T_List* p = head->next;
	while (p != nullptr)
	{
		std::cout << p->x << std::endl;
		p = p->next;
	}
}

void CLEAR(T_List* head)
{
	T_List* tmp;
	T_List* p = head->next;
	while (p != nullptr)
	{
		tmp = p;
		p = p->next;
		delete tmp;
	}
}

//добавляем в конец с помощью списка
void AddEnd1(T_List* head, int& k)
{

	T_List* p = head->next;
	while (p != nullptr)
	{
		if (p->next == nullptr)
		{
			T_List* q = new T_List;
			q->next = p->next;
			p->next = q;
			q->x = k;
			p = p->next;
		}
		p = p->next;
	}
}

//добавляем в конец с помощью вектора
void AddEnd2(std::vector<int>& vec, int& k)
{

	vec.push_back(k);
}

int main()
{
	int N = 10000;
	int M = 1000;
	srand(time(0));
	int k = rand();
	T_List* head = new T_List;
	head->next = nullptr;

	for (int i = 0; i < N; i++)
	{

		ADD(head, rand() % 100);


	}

	PRINT(head);

	cout << '\n';

	Timer t1;
	for (int i = 0; i < M; i++)
	{
		k = rand();
		AddEnd1(head, k);
		cout << k << " - element K" << endl;

	}
	cout << "Time elapsed1: " << t1.elapsed() << '\n';
	cout << '\n';
	PRINT(head);

	CLEAR(head);
	delete head;
	cout << '\n';
	vector<int> vec;
	for (int i = 0; i < N; i++)
	{
		vec.push_back(rand() % 100);
	}

	Timer t2;
	for (int i = 0; i < M; i++)
	{
		k = rand();
		AddEnd2(vec, k);
	}
	cout << "Time elapsed2: " << t2.elapsed() << '\n';
	//cout << "////////////////////////////////////////////" << endl;
}