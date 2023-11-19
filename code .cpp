#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <fstream>

using namespace std;

struct Node {
	int data;
	Node* next;
};

//function to print the adjacency list
void printAdjacencyList(Node** adjacencyList, int size) {
	for (int i = 0; i < size; i++) {
		cout << "Vertex " << i << " is adjacent to: ";
		Node* current = adjacencyList[i];
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
}

// Function to convert an adjacency matrix to an adjacency list with reversed order of adjacent vertices
Node** adjacencyMatrixToAdjacencyList(int** matrix, int size) {
	Node** adjacencyList = new Node * [size];

	for (int i = 0; i < size; i++) {
		adjacencyList[i] = nullptr;  // Initialize the list for vertex i

		for (int j = size - 1; j >= 0; j--) { // Loop in reverse order to add adjacent vertices in reverse
			if (matrix[i][j] == 1) {
				Node* newNode = new Node;
				newNode->data = j;
				newNode->next = adjacencyList[i];
				adjacencyList[i] = newNode;
			}
		}
	}

	return adjacencyList;
}

// Function to free the memory used for adjacency lists
void freeAdjacencyList(Node** adjacencyList, int size) {
	for (int i = 0; i < size; i++) {
		Node* current = adjacencyList[i];
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] adjacencyList;
}

// Функция для выделения памяти под двумерный массив
int** createMatrix(int size) {
	int** matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
	}
	return matrix;
}

// Функция для освобождения памяти, выделенной под матрицу
void deleteMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

// Функция для заполнения матрицы случайными значениями
void fillMatrixRandom(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i == j) {
				matrix[i][j] = 0;
			}
			else {
				int randomValue = rand() % 2;
				matrix[i][j] = randomValue;
				matrix[j][i] = randomValue; // Матрица симметрична
			}
		}
	}
}

// Функция для вывода матрицы с элементами, разделенными запятой и пробелом
void printMatrix(int** matrix, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << matrix[i][j];
			cout << ", ";

		}
		cout << endl;
	}
}

int* breadthFirstSearch(int** graph, int size, int startVertex) {
	bool* visited = new bool[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false; // Initially, mark all vertices as not visited
	}

	int* traversalOrder = new int[size];
	int currentIndex = 0;

	queue<int> q;
	q.push(startVertex);
	visited[startVertex] = true;

	while (!q.empty()) {
		int currentVertex = q.front();
		q.pop();
		traversalOrder[currentIndex++] = currentVertex;

		for (int i = 0; i < size; i++) {
			if (graph[currentVertex][i] == 1 && !visited[i]) {
				q.push(i);
				visited[i] = true;
			}
		}
	}

	delete[] visited;
	return traversalOrder;
}

int* bfsTraversal(Node** adjacencyList, int size, int startVertex) {
	bool* visited = new bool[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false; // Initially, mark all vertices as not visited
	}

	int* traversalOrder = new int[size];
	int currentIndex = 0;

	queue<int> q;
	q.push(startVertex);
	visited[startVertex] = true;

	while (!q.empty()) {
		int currentVertex = q.front();
		q.pop();
		traversalOrder[currentIndex++] = currentVertex;

		// Traverse adjacent vertices using the adjacency list
		Node* current = adjacencyList[currentVertex];
		while (current != nullptr) {
			int neighbor = current->data;
			if (!visited[neighbor]) {
				q.push(neighbor);
				visited[neighbor] = true;
			}
			current = current->next;
		}
	}

	delete[] visited;
	return traversalOrder;
}

// Функция для добавления вершины в список смежности
void addEdge(Node** adjacencyList, int vertex, int data) {
	Node* newNode = new Node;
	newNode->data = data;
	newNode->next = adjacencyList[vertex];
	adjacencyList[vertex] = newNode;
}


// Структура для представления элемента очереди
struct QueueNode {
	int data;
	QueueNode* next;
};

// Структура для представления очереди
struct Queue {
	QueueNode* front;
	QueueNode* rear;
};

// Инициализация пустой очереди
Queue* createQueue() {
	Queue* queue = new Queue;
	queue->front = queue->rear = nullptr;
	return queue;
}

// Проверка, пуста ли очередь
bool isEmpty(Queue* queue) {
	return queue->front == nullptr;
}

// Добавление элемента в очередь
void enqueue(Queue* queue, int data) {
	QueueNode* newNode = new QueueNode;
	newNode->data = data;
	newNode->next = nullptr;

	if (isEmpty(queue)) {
		queue->front = queue->rear = newNode;
		return;
	}

	queue->rear->next = newNode;
	queue->rear = newNode;
}

// Извлечение элемента из очереди
int dequeue(Queue* queue) {
	if (isEmpty(queue)) {
		cerr << "Очередь пуста!" << endl;
		return -1; // Возвращаем -1, чтобы обозначить ошибку
	}

	int data = queue->front->data;
	QueueNode* temp = queue->front;
	queue->front = queue->front->next;
	delete temp;

	if (queue->front == nullptr) {
		queue->rear = nullptr; // Если очередь стала пустой
	}

	return data;
}

int* BFScustomList(int** matrix, int size, int startVertex) {
	bool* visited = new bool[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false; // Initially, mark all vertices as not visited
	}

	int* traversalOrder = new int[size];
	int currentIndex = 0;

	Queue* queue = createQueue();
	enqueue(queue, startVertex);
	visited[startVertex] = true;

	while (!isEmpty(queue)) {
		int currentVertex = dequeue(queue);
		traversalOrder[currentIndex++] = currentVertex;

		for (int i = 0; i < size; i++) {
			if (matrix[currentVertex][i] == 1 && !visited[i]) {
				enqueue(queue, i);
				visited[i] = true;
			}
		}
	}

	delete[] visited;
	delete(queue);

	return traversalOrder;
}

int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(0));
	int choice;

	do {
		// Отображаем меню
		cout << "Меню:" << endl;
		cout << "1. генерация матрицы и поиск в ширину" << endl;
		cout << "2. тест алгоритмов обхода в ширину" << endl;
		cout << "3. Выход" << endl;

		// Запрашиваем выбор пользователя
		//cout << "Пожалуйста, введите номер выбранного пункта: ";
		//cin >> choice;

		char buffer[20];
		//int size;
		while (1) {
			cout << "Пожалуйста, введите номер выбранного пункта: ";
			cin >> buffer;

			if (atoi(buffer) == 0)
			{
				cout << "Неправильный выбор. Пожалуйста, введите верный номер пункта." << endl;
				continue;
			}
			else {
				choice = atoi(buffer);
				break;
			}
		}

		// Обработка выбора пользователя
		switch (choice) {
		case 1: {
			cout << "Вы выбрали пункт 1." << endl;
			// Здесь можно разместить код для выполнения действий пункта 1
			int size;
			//cout << "\nВведите размер матрицы смежности: ";
			//cin >> size;

			while (1) {
				cout << "\nВведите размер матрицы смежности: ";
				cin >> buffer;

				if (atoi(buffer) == 0 || atoi(buffer) < 0)
				{
					cout << "Только целые числа > 0" << endl;
					continue;
				}
				else {
					size= atoi(buffer);
					break;
				}
			}

			int** adjacencyMatrix = createMatrix(size);
			fillMatrixRandom(adjacencyMatrix, size);
			printMatrix(adjacencyMatrix, size);

			// Convert the adjacency matrix to an adjacency list and print it
			cout << "\nAdjacency List:\n";
			Node** adjacencyList = adjacencyMatrixToAdjacencyList(adjacencyMatrix, size);
			printAdjacencyList(adjacencyList, size);

			int startVertex;
			//cout << "Введите начальную вершину для обхода: ";
			//cin >> startVertex; cout << "\n";

			while (1) {
				cout << "Введите начальную вершину для обхода: ";
				cin >> buffer;

				//if(atoi(buffer) == 0 && buffer[0] != '0') 
				if (atoi(buffer) < 0 || atoi(buffer) >= size || (atoi(buffer) == 0 && buffer[0] != '0'))
				{
					cout << "Только целые числа > 0 и < размера матрицы. bAbы$" << endl;
					continue;
				}
				else {
					startVertex = atoi(buffer);
					break;
				}
			}

			int* traversalOrder = breadthFirstSearch(adjacencyMatrix, size, startVertex);

			for (int i = 0; i < size; i++) {
				cout << traversalOrder[i] << " ";
			}

			cout << " ВbreadthFirstSearch\n" << endl;
			delete[] traversalOrder;

			int* traversalOrder1 = bfsTraversal(adjacencyList, size, startVertex);


			for (int i = 0; i < size; i++) {
				cout << traversalOrder1[i] << " ";
			}
			cout << " bfsTraversal\n" << endl;

			delete[] traversalOrder1;

			int* traversalOrder2 = BFScustomList(adjacencyMatrix, size, startVertex);

			for (int i = 0; i < size; i++) {
				cout << traversalOrder2[i] << " ";
			}

			delete[] traversalOrder2;

			cout << " BFScustomList\n" << endl;

			deleteMatrix(adjacencyMatrix, size);

			break; }
		case 2: {
			cout << "Вы выбрали пункт 2." << endl;
			// Здесь можно разместить код для выполнения действий пункта 2


			int sizes[] = { 1000, 1000, 1000 };

			// Open a file for writing
			ofstream outputFile("graph_traversal_times.txt");
			if (!outputFile.is_open()) {
				cerr << "Failed to open the output file." << endl;
				return 1;
			}

			outputFile << "Matrix Size\tBFS Matrix (s)\tBFS List (s)\tBFS Custom (s)\n";

			for (int i = 0; i < 3; i++) {
				int size = sizes[i];
				int** adjacencyMatrix = createMatrix(size);
				fillMatrixRandom(adjacencyMatrix, size);

				Node** adjacencyList = adjacencyMatrixToAdjacencyList(adjacencyMatrix, size);
				int startVertex = 0;

				clock_t startTime, endTime;

				startTime = clock();
				int* traversalOrder = breadthFirstSearch(adjacencyMatrix, size, startVertex);
				endTime = clock();
				double bfsMatrixTime = double(endTime - startTime) / CLOCKS_PER_SEC;
				delete[] traversalOrder;

				startTime = clock();
				int* traversalOrder1 = bfsTraversal(adjacencyList, size, startVertex);
				endTime = clock();
				double bfsListTime = double(endTime - startTime) / CLOCKS_PER_SEC;
				delete[] traversalOrder1;


				startTime = clock();
				int* traversalOrder2 = BFScustomList(adjacencyMatrix, size, startVertex);
				endTime = clock();
				double bfsCustomTime = double(endTime - startTime) / CLOCKS_PER_SEC;
				delete[] traversalOrder2;

				outputFile << size << "\t\t" << bfsMatrixTime << "\t\t" << bfsListTime << "\t\t" << bfsCustomTime << "\n";

				deleteMatrix(adjacencyMatrix, size);
				freeAdjacencyList(adjacencyList, size);
			}

			// Close the output file
			outputFile.close();
			cout << "Результаты теста алгоритмов обхода в ширину находятся в файле graph_traversal_times.txt" << endl;
			break; }
		case 3:
			cout << "Выход." << endl;
			break;
		default:
			cout << "Неправильный выбор. Пожалуйста, введите верный номер пункта." << endl;
			break;
		}

	} while (choice != 3); // Выход из меню при выборе "Выход" (пункт 4)

	return 0;
}