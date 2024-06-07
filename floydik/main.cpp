#include <iostream>
#include <fstream>
#include <vector>

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define INF 9999

using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == INF) {
                cout << "~ ";
            }
            else {
                cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void printPath(vector<vector<int>>& pathMatrix, int start, int end) {
    if (pathMatrix[start - 1][end - 1] == 0) {
        cout << "Нет пути из " << start << " в " << end << endl;
    }
    else {
        cout << "Путь из " << start << " в " << end << ": " << start << " ";
        int current = start;
        while (current != end) {
            current = pathMatrix[current - 1][end - 1];
            cout << "-> " << current << " ";
        }
        cout << endl;
    }
}


int main() {
    setlocale(LC_ALL, "Rus");

    ifstream file("data.txt");
    int n;
    file >> n;
    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> pathMatrix(n, vector<int>(n));

    char* elem = new char[10];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> elem;
            if (strcmp(elem, "INF") == 0) {
                A[i][j] = INF;
            }
            else {
                A[i][j] = atoi(elem);
            }
            if (A[i][j] != INF && A[i][j] != 0)
                pathMatrix[i][j] = j + 1;
            else
                pathMatrix[i][j] = 0;
        }
    }

    cout << "Матрица расстояний" << endl;
    printMatrix(A);

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (A[i][k] < INF && A[k][j] < INF) {
                    if (A[i][j] > A[i][k] + A[k][j]) {
                        pathMatrix[i][j] = pathMatrix[i][k];
                    }
                    A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
                }
            }
    cout << "Матрица минимальных расстояний" << endl;
    printMatrix(A);

    cout << "Матрица путей" << endl;
    printMatrix(pathMatrix);
    

    int start, end;
    cout << "Введите начальную вершину: ";
    cin >> start;
    cout << "Введите конечную вершину: ";
    cin >> end;

    printPath(pathMatrix, start, end);

    cout << "\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << endl;
    cout << "Вывод различных путей:" << endl;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                printPath(pathMatrix, i, j);
                cout << endl;
            }
        }
    }
}

