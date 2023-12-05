#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<string>
#include<cstring>
#include<time.h>
#include<Windows.h>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <locale.h>
#include <algorithm>

struct List_body {
	int vertex;
	struct List_body* next;
};

struct List_head {
	int number;
	struct List_body* head;
	struct List_head* next;
};

struct List_head* head_list1 = NULL, * head_spisok2 = NULL;
string* name;
bool name_number = TRUE;

struct List_body* creation_element(int number) {

	struct List_body* p = NULL;

	if ((p = (List_body*)malloc(sizeof(struct List_body))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	p->vertex = number;
	p->next = NULL;

	return p;


}

struct List_head* creation_element_head(int number, int** M, int size) {

	struct  List_head* p = NULL;
	struct List_body* q, * save = NULL;

	if ((p = (List_head*)malloc(sizeof(struct  List_head))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	p->next = NULL;
	p->number = number;
	p->head = NULL;

	for (int i = 0; i < size; i++) {
		if (M[number][i] == 1) {
			q = creation_element(i);
			if (p->head == NULL) {
				p->head = q;
				save = q;
			}
			else {
				save->next = q;
				save = q;
			}
		}
	}

	return p;


}

void creation_list(int** M, struct List_head* list, int size, struct List_head** head_spisok) {

	struct List_head* h, * save = NULL;
	for (int i = 0; i < size; i++) {
		h = creation_element_head(i, M, size);
		if ((*head_spisok) == NULL) {
			(*head_spisok) = h;
			save = h;
		}
		else {
			save->next = h;
			save = h;
		}
	}


}

void review(int size, struct List_head** head_spisok) {
	struct List_body* save;
	struct List_head* save_head = (*head_spisok);
	cout << "\n";
	for (int i = 0; i < size; i++) {
		save = save_head->head;
		cout << "[" << save_head->number << "]";
		while (save != NULL) {
			cout << " -> " << save->vertex;
			save = save->next;
		}
		cout << "\n";
		save_head = save_head->next;
	}
	cout << "\n";

}
void output_mas(int** M, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << M[i][j] << " ";
		}
		cout << "\n";
	}
}


void input_output(int** M, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) {
				// С вероятностью 50% создаем петлю
				M[i][j] = rand() % 2;
			}
			else {
				M[i][j] = rand() % 2;
				M[j][i] = M[i][j];
			}
		}
	}
	output_mas(M, size);
}

void rename(int size2) {

	for (int i = 0; i < size2; i++) {
		cout << "\nВведите название вершины номер " << i + 1 << ": ";
		cin >> name[i];
	}
	name_number = FALSE;
}
string perem;
int count_on_name(int size) {
	for (int i = 0; i < size; i++) {
		if ((perem.compare(name[i])) == 0) {
			return i;
		}
	}
}

int** identification(int** M, int* size, bool input) {
	int** M3, vertex1, vertex2;
	M3 = new int* [(*size) - 1]; // создаём двумерный массив 

	for (int i = 0; i < (*size) - 1; i++) {
		M3[i] = new int[(*size) - 1];
	}

	if (input) {
		cout << "Введите вершины для отождествления\n 1 вершина : ";
		cin >> vertex1;
		cout << " 2 вершина : ";
		cin >> vertex2;
	}
	else {
		cout << "Введите вершины инцидентные ребру, которое вы хотите стянуть\n 1 вершина : ";
		cin >> vertex1;
		cout << " 2 вершина : ";
		cin >> vertex2;
	}

	// Проверяем наличие ребра между вершинами
	if (M[vertex1][vertex2] == 1 || M[vertex2][vertex1] == 1) {
		// Удаляем ребро между вершинами
		M[vertex1][vertex2] = 0;
		M[vertex2][vertex1] = 0;

		// Объединяем вершины
		for (int i = 0; i < (*size) - 1; i++) {
			for (int j = i; j < (*size) - 1; j++) {
				if (i == min(vertex1, vertex2) && j >= max(vertex1, vertex2)) {
					M3[i][j] = (M[min(vertex1, vertex2)][j + 1] || M[max(vertex1, vertex2)][j + 1]);
					M3[j][i] = M3[i][j];
					if (i == min(vertex1, vertex2)) {
						M3[i][i] = 1;
					}
				}
				else if (i >= max(vertex1, vertex2) && j >= max(vertex1, vertex2)) {
					M3[i][j] = M[i + 1][j + 1];
					M3[j][i] = M3[i][j];
				}
				else if (i == min(vertex1, vertex2)) {
					M3[i][j] = (M[min(vertex1, vertex2)][j] || M[max(vertex1, vertex2)][j]);
					M3[j][i] = M3[i][j];
				}
				else if (j >= max(vertex1, vertex2)) {
					M3[i][j] = M[i][j + 1];
					M3[j][i] = M3[i][j];
				}
				else if (j == min(vertex1, vertex2)) {
					M3[i][j] = M[i][min(vertex1, vertex2)] || M[i][max(vertex1, vertex2)];
					M3[j][i] = M3[i][j];
				}
				else {
					M3[i][j] = M[i][j];
					M3[j][i] = M3[i][j];
				}
			}
		}

		output_mas(M3, (*size) - 1);
		(*size)--;
		return M3;
	}
	else {
		cout << "Невозможно стянуть - нет ребра между вершинами.\n";
		return M; // или другие действия по вашему выбору
	}
}


void check_of_vertexes(int* vertex, int size) {
	while ((*vertex) >= size || (*vertex) < 0) {
		cout << "Ошибка(отсутствие таковой вершины)\n Попробуйте ещё раз: ";
		cin >> (*vertex);
	}
}

struct List_head* search_of_vertex(struct List_head* save, int vertex) {
	while (save->number != vertex) {
		save = save->next;
	}
	return save;
}

void identification_spisok(struct List_head** head_spisok, bool input, int* size) {
	int vertex1, vertex2;
	struct List_head* save1 = NULL, * save2 = NULL;
	struct List_body* save1_soed = NULL, * save2_soed = NULL, * save2_1_soed = NULL;
	if (input) {
		cout << "Введите вершины для отождествления\n 1 вершина: ";
		cin >> vertex1;
		check_of_vertexes(&vertex1, *size);
		cout << " 2 вершина: ";
		cin >> vertex2;
		check_of_vertexes(&vertex2, *size);
	}
	else {
		cout << "Введите вершины инцидентные ребру ,которое вы хотите стянуть\n 1 вершина: ";
		cin >> vertex1;
		check_of_vertexes(&vertex1, *size);
		cout << " 2 вершина: ";
		cin >> vertex2;
		check_of_vertexes(&vertex2, *size);
	}
	save1 = search_of_vertex(*head_spisok, vertex1);
	save2 = search_of_vertex(*head_spisok, vertex2);
	save1_soed = save1->head;
	save2_soed = save2->head;
	if (save1->head == NULL) {
		save1->head = save2->head;
	}
	else {
		while (save2_soed != NULL && save2->head != NULL) {
			save1_soed = save1->head;

			if (save2_soed != NULL && save1_soed != NULL && save1_soed->vertex > save2_soed->vertex) {
				save2_1_soed = save2_soed;
				save2_soed = save2_soed->next;
				save2_1_soed->next = save1->head;
				save1->head = save2_1_soed;
			}
			else {
				while ((save1_soed->next->vertex != save2_soed->vertex) && (save1_soed->next != NULL) && (save1_soed->next->vertex < save2_soed->vertex)) {
					save1_soed = save1_soed->next;
				}
				if (save1_soed->next->vertex == save2_soed->vertex) {
					save2_soed = save2_soed->next;
				}
				else if (save1_soed->next == NULL) {
					save2_1_soed = save2_soed;
					save2_soed = save2_soed->next;
					save1_soed->next = save2_1_soed;
					save2_1_soed->next = NULL;
				}
				else {
					save2_1_soed = save2_soed;
					save2_soed = save2_soed->next;
					save2_1_soed->next = save1_soed->next;
					save1_soed->next = save2_1_soed;

				}
			}
		}
	}

	save2 = search_of_vertex(*head_spisok, vertex2 - 1);
	save2->next = save2->next->next;
	(*size)--;


}

int** splitting(int** M, int* size) {
	int** M3, vertex;
	M3 = new int* [*size + 1]; // создаём двумерный массив 

	for (int i = 0; i < *size + 1; i++) {
		M3[i] = new int[*size + 1];
	}
	
	if (name_number) {
		cout << "Введите вершину для расщипления : ";
		cin >> vertex;
	}
	else {
		cout << "Введите вершину для расщипления : ";
		cin >> perem;
		vertex = count_on_name(*size);
	}

	// Первая строка равна первому столбцу
	for (int i = 0; i < *size; i++) {
		M3[0][i + 1] = M[i][vertex];
		M3[i + 1][0] = M[vertex][i];
	}

	// Заполнение остальной части матрицы
	for (int i = 0; i < *size; i++) {
		for (int j = 0; j < *size; j++) {
			M3[i + 1][j + 1] = M[i][j];
			M3[i][j] = 0;

			//M3[0][0] = 0;
			
		}
	}
	if (M[vertex][vertex] == 0) {
		cout << "Невозможно стянуть\n";
		return M; // или другие действия по вашему выбору
	}

	output_mas(M3, *size + 1);
	(*size)++;
	return M3;
}


void splitting_list(struct List_head** head_spisok, int* size, int** M) {
	int vertex, colvo_reber = 0;
	struct List_head* save1 = NULL, * q = NULL;
	struct List_body* save1_soed = NULL, * save2_soed = NULL;


	cout << "Введите вершину для расщипления : ";
	cin >> vertex;
	check_of_vertexes(&vertex, *size);

	save1 = search_of_vertex(*head_spisok, vertex);
	save1_soed = save1->head;

	while (save1_soed != NULL) {
		save1_soed = save1_soed->next;
		colvo_reber++;
	}

	save1_soed = save1->head;
	for (int i = 0; i < ((colvo_reber / 2) - 1); i++) {
		save1_soed = save1_soed->next;
	}

	save2_soed = save1_soed->next;
	save1_soed->next = NULL;

	q = creation_element_head(*size, M, 0);
	q->head = save2_soed;

	save1 = search_of_vertex(*head_spisok, (*size) - 1);
	save1->next = q;

	(*size)++;

}

void Union(int** M1, int** M2, int size1, int size2) {
	int** M3, size;
	size = max(size1, size2);
	M3 = new int* [size];
	for (int i = 0; i < size; i++) {
		M3[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i < min(size1, size2) && j < min(size1, size2)) {
				M3[i][j] = M3[j][i] = (M1[i][j] | M2[i][j]);
			}
			else if (size1 < size2) {
				M3[i][j] = M3[j][i] = M2[i][j];
			}
			else { M3[i][j] = M3[j][i] = M1[i][j]; }
		}
	}
	output_mas(M3, size);

}

void intersection(int** M1, int** M2, int size1, int size2) {
	int** M3, size;
	size = min(size1, size2);
	M3 = new int* [size];
	for (int i = 0; i < size; i++) {
		M3[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i < min(size1, size2) && j < min(size1, size2)) {
				M3[i][j] = M3[j][i] = (M1[i][j] & M2[i][j]);
			}
			else {
				M3[i][j] = M3[j][i] = 0;
			}

		}
	}
	output_mas(M3, size);

}

void circle_sum(int** M1, int** M2, int size1, int size2) {
	int** M3, size, * colvo_reber, otstup;
	size = max(size1, size2);
	M3 = new int* [size];
	colvo_reber = new int[size];
	for (int i = 0; i < size; i++) {
		M3[i] = new int[size];
		colvo_reber[i] = 0;
	}

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i < min(size1, size2) && j < min(size1, size2)) {
				if (M1[i][j] == M2[i][j]) {
					M3[i][j] = M3[j][i] = 0;
				}
				else { M3[i][j] = M3[j][i] = 1; }
			}
			else if (size1 < size2) {
				M3[i][j] = M3[j][i] = M2[i][j];
			}
			else { M3[i][j] = M3[j][i] = M1[i][j]; }

		}
	}
	output_mas(M3, size);
	size1 = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (M3[i][j] == 1) {
				colvo_reber[i]++;
			}
		}
		if (colvo_reber[i] > 0) {
			size1++;
		}
	}
	M1 = new int* [size1];
	for (int i = 0; i < size1; i++) {
		M1[i] = new int[size1];
	}

	for (int i = 0; i < size1; i++) {
		otstup = 0;
		for (int j = 0; j < size1; j++) {
			if (colvo_reber[j] = 0) { otstup++; }
			M1[i][j] = M3[i + otstup][j + otstup];
		}
	}


}

int** dekartovo_proizvedenie(int** M1, int size1, int** M2, int size2) {
	int n1 = size1;
	int n2 = size2;
	int productSize = n1 * n2;
	int** productGraph = new int* [productSize + 1];

	for (int i = 0; i <= productSize; ++i) {
		productGraph[i] = new int[productSize + 1];
		for (int j = 0; j <= productSize; ++j) {
			productGraph[i][j] = 0;
		}
	}

	for (int i1 = 0; i1 < n1; ++i1) {
		for (int i2 = 0; i2 < n2; ++i2) {
			for (int j1 = 0; j1 < n1; ++j1) {
				for (int j2 = 0; j2 < n2; ++j2) {
					int v1 = i1 * n2 + i2 + 1;
					int v2 = j1 * n2 + j2 + 1;
					if (i1 == j1 && M2[i2][j2]) {
						productGraph[v1][v2] = 1;
					}
					if (i2 == j2 && M1[i1][j1]) {
						productGraph[v1][v2] = 1;
					}
				}
			}
		}
	}

	
	output_mas(productGraph, n1 * n2);
	return productGraph;
}





// Ваша функция main должна вызывать эту новую функцию для операции декартова произведения


int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int** M1, ** M2, size1, size2, choose1, choose2;
	struct List_head* spisok1, * spisok2;
	bool condition = TRUE;
	cout << " Матрицы смежности \n \n Введите количество вершин графа №1: ";
	cin >> size1;
	cout << " Введите количество вершин графа №2: ";
	cin >> size2;
	M1 = new int* [size1]; // создаём двумерный массив 
	M2 = new int* [size2];
	name = new string[size2];
	spisok1 = new struct List_head[size1];
	spisok2 = new struct List_head[size2];
	for (int i = 0; i < size1; i++) {
		M1[i] = new int[size1];
	}
	for (int i = 0; i < size2; i++) {
		M2[i] = new int[size2];
	}

	cout << "M1:\n";
	input_output(M1, size1);

	cout << "\nM2:\n";
	input_output(M2, size2);
	cout << "\n";
	cout << "Выберите действие\n 1) Матрицы\n 2) Списки\n Выберите действие: ";
	cin >> choose2;
	switch (choose2) {
	case(1):

		while (condition) {
			cout << "\n 1) Отождествление вершин\n 2) Стягивание ребра\n 3) Расщипление вершины\n 4) Объединение\n 5) Пересечение\n 6) Кольцевая сумма\n 7) Декартово произведение \n 8) Закончить\n Выберите действие: ";
			cin >> choose1;
			switch (choose1) {
			case(1):
				cout << "\n";
				M2 = identification(M2, &size2, TRUE);
				break;
			case(2):
				cout << "\n";
				M2 = identification(M2, &size2, FALSE);
				break;
			case(3):
				cout << "\n";
				M2 = splitting(M2, &size2);
				break;
			case(4):
				cout << "\n";
				Union(M1, M2, size1, size2);
				break;
			case(5):
				cout << "\n";
				intersection(M1, M2, size1, size2);
				break;
			case(6):
				cout << "\n";
				circle_sum(M1, M2, size1, size2);
				break;
			case(7):
				cout << "\n";
				dekartovo_proizvedenie(M1, size1, M2, size2);
				

				break;
			case(8):
				condition = FALSE;
				break;
			default:
				cout << "Ошибка";
			}
		}
		break;
	case(2):
		creation_list(M1, spisok1, size1, &head_list1);
		review(size1, &head_list1);

		creation_list(M2, spisok2, size2, &head_spisok2);
		review(size2, &head_spisok2);

		while (condition) {
			cout << "\n 1) Отождествление вершин\n 2) Стягивание ребра\n 3) Расщипление вершины\n 4) Завершить\n Выберите действие: ";
			cin >> choose1;
			switch (choose1) {
			case(1):
				identification_spisok(&head_list1, TRUE, &size1);
				review(size1, &head_list1);
				break;
			case(2):
				identification_spisok(&head_list1, FALSE, &size1);
				review(size1, &head_list1);
				break;
			case(3):
				splitting_list(&head_list1, &size1, M1);
				review(size1, &head_list1);
				break;
			case(4):
				condition = FALSE;
				break;
			

			default:
				cout << "Ошибка";
			}
		}
		break;
	case(3):

		break;
	default:
		cout << "Ошибка";



	}
	system("pause");
	return 0;
}