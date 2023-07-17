// Алгоритм Дейкстри 2.0.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <Windows.h>

const int INF = 1e9;

using namespace std;

void Show_result_of_dijkstra(int* cur_distence, int kil_top);
int Find_min_distance(int* cur_distence, bool* proven_peaks, int kil_top);
void dijkstra(int** graph, int given_vertex, int kil_top);

int main() 
{
    setlocale(LC_ALL, "ukr");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Введіть кількість вершин: ";
    int kil_top;
    cin >> kil_top;
    cout << "Задайте матрицю: " << endl;
    int** graph = new int* [kil_top];
    for (int i = 0; i < kil_top; i++) {
        graph[i] = new int[kil_top];
        for (int j = 0; j < kil_top; j++) {
            cin >> graph[i][j];
        }
    }
    cout << endl;
    int top_that_chose_user;
    cout << "Введіть номер вершини з якої хочете розпочати алгоритм: "; cin >> top_that_chose_user;
    top_that_chose_user--;
    dijkstra(graph, top_that_chose_user, kil_top);

    return 0;
}


void dijkstra(int** graph, int given_vertex, int kil_top)
{
    int* cur_distence = new int[kil_top];
    bool* proven_peaks = new bool[kil_top];
    int** paths = new int* [kil_top];
    for (int i = 0; i < kil_top; i++)
    {
        cur_distence[i] = INF;
        proven_peaks[i] = false;
        paths[i] = new int[kil_top];
        for (int j = 0; j < kil_top; j++)
        {
            paths[i][j] = -1;
        }
    }

        cur_distence[given_vertex] = 0;

    for (int K = 0; K < kil_top - 1; K++)
    {
        int u = Find_min_distance(cur_distence, proven_peaks, kil_top);
        proven_peaks[u] = true;

        for (int i = 0; i < kil_top; i++)
        {
            if (!proven_peaks[i] && graph[u][i] && cur_distence[u] != INF && cur_distence[u] + graph[u][i] < cur_distence[i])
            {
                cur_distence[i] = cur_distence[u] + graph[u][i];
                int j = 0;
                while (paths[u][j] != -1)
                {
                    paths[i][j] = paths[u][j];
                    j++;
                }
                paths[i][j] = u;
            }
        }
    }

    Show_result_of_dijkstra(cur_distence, kil_top);
    cout << endl;
    cout << "----------------------" << endl;
    for (int i = 0; i < kil_top; i++)
    {
        cout << "Vertex " << i + 1 << ": ";
        int j = 0;
        while (paths[i][j] != -1)
        {
            cout << paths[i][j] + 1 << " ";
            j++;
        }
        cout << i + 1 << endl;
    }

    // Free memory
    for (int i = 0; i < kil_top; i++)
    {
        delete[] paths[i];
    }
    delete[] paths;
    delete[] cur_distence;
    delete[] proven_peaks;

}

int Find_min_distance(int* cur_distence, bool * proven_peaks, int kil_top)
{
    int min = INF, cur_min;

    for (int i = 0; i < kil_top; i++)
    {
        if (proven_peaks[i] == false && cur_distence[i] <= min)
        {
            min = cur_distence[i];
            cur_min = i;
        }
    }
    return cur_min;
}

void Show_result_of_dijkstra(int * cur_distence, int kil_top)
{
    cout << "Відстані до вершини: " << endl;
    cout << endl;
    for (int i = 0; i < kil_top; i++)
    {
       cout << setw(4) << i + 1;
    }
    cout << endl;
    
    for (int i = 0; i < kil_top; i++)
    {
        if (cur_distence[i] == INF)
        {
            cout << setw(4) << "INF";
        }
        else cout << setw(4) << cur_distence[i];
    }
}




// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
