#include <iostream>

using namespace std;

int amountOfDots();
int** createMatrix(int dots);
void inputFromKeyboard(int** matrix, int dots);
void output(int** matrix, int dots);
bool tightnessTest(int** matrix, int dots);
int** KruskalsAlgorith(int** matrix, int dots);

#define INF 200000;

int main()
{
	int dots = amountOfDots();
	int** matrix = createMatrix(dots);
	inputFromKeyboard(matrix, dots);
	cout << "Initial matrix of adjacency: " << endl;
	output(matrix, dots);
	bool testInfo = tightnessTest(matrix, dots);
	if (testInfo) {
		int** newMatrix = KruskalsAlgorith(matrix, dots);
		cout << "Edge of the least possible weight (adjacency table): " << endl;
		output(newMatrix, dots);
		for (int i = 0; i < dots; i++) {
			delete[]newMatrix[i];
		}
		delete[] newMatrix;
	}
	else {
		cout << "The graph is not tight!" << endl;
	}
	
	for (int i = 0; i < dots; i++) { 
		delete[]matrix[i]; 
	}
	delete[] matrix;
}

int amountOfDots() {
	cout << "Enter an amount of dots: ";
	int dots;
	cin >> dots;
	while (dots < 2) {
		cout << "Enter a correct number: ";
		cin >> dots;
	}
	return dots;
}

int** createMatrix(int dots)
{
	int** matrix = new int* [dots];
	for (int i = 0; i < dots; i++) {
		matrix[i] = new int[dots];
	}
	return matrix;
}

void inputFromKeyboard(int** matrix, int dots)
{
	for (int i = 0; i < dots; i++) {
		for (int j = 0; j < dots; j++) {
			cout << "Enter [" << i << "][" << j << "]: ";
			cin >> matrix[i][j];
		}
	}
}

void output(int** matrix, int dots) {
	for (int i = 0; i < dots; i++) {
		for (int j = 0; j < dots; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


bool tightnessTest(int** matrix, int dots) {
	for (int i = 0; i < dots; i++) {
		int count1 = 0;
		int count2 = 0;
		for (int j = 0; j < dots; j++) {
			if (matrix[i][j] == 0) {
				if (matrix[j][i] == 0) {
					count2++;
				}
				count1++;
				if (count1 == dots - 1 && count2 == dots - 1) {
					return false;
				}
			}
			
		}
	}
	return true;
}


int** KruskalsAlgorith(int** matrix, int dots) {

	int** newMatrix = new int* [dots];
	for (int i = 0; i < dots; i++) {
		newMatrix[i] = new int[dots];
	}
	int* temp = new int[dots];

	for (int i = 0; i < dots; i++) {
		for (int j = 0; j < dots; j++) {
			newMatrix[i][j] = 0;
			if (matrix[i][j] == 0) {
				matrix[i][j] = INF;
			}
		}
		temp[i] = i;
	}

	int nodoA;
	int nodoB;
	int arcos = 1;
	while (arcos < dots) {
		int min = INF;
		for (int i = 0; i < dots; i++) {
			for (int j = 0; j < dots; j++) {
				if (min > matrix[i][j] && temp[i] != temp[j] && matrix[i][j] != 0) {
					min = matrix[i][j];
					nodoA = i;
					nodoB = j;
				}
			}
		}
		if (temp[nodoA] != temp[nodoB]) {
			newMatrix[nodoA][nodoB] = min;
			newMatrix[nodoB][nodoA] = min;

			 //Усі вершини дерева nodoB зараз належать до дерева nodoA.
			int temporary = temp[nodoB];
			temp[nodoB] = temp[nodoA];
			for (int k = 0; k < dots; k++)
				if (temp[k] == temporary)
					temp[k] = temp[nodoA];
			arcos++;
		}
	}
	delete[] temp;
	return newMatrix;
}