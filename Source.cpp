/***Лабороторна робота №3																	*** /
/*** Варiант №21																			***/
/*** З курсу																				***/
/*** Чисельнi методи																		***/
/*** ІТЕРАЦІЙНІ МЕТОДИ РОЗВ'ЯЗУВАННЯ СИСТЕМ													***/
/***ЛІНІЙНИХ АЛГЕБРАЇЧНИХ РІВНЯНЬ															***/
/*** Завдання:																				***/
/***Скласти програму для розв'язування системи iтерацiйним методом послiдовних наближень.	***/
/***Передбачити максимально допустиму кількість iтерацiй 40. На кожнiй iтерацiї надрукувати її***/
/***номер i вектор невiдомих. Надрукувати початкову та перетворену системи. У програмi передбачити***/
/***побудову графiка залежностi величини || x(n)- x*|| від n для n=1, 2,...,k при e =10-6.	***/
/***Виконав:Редько Денис ТР-71***/

#include <iostream>
#include <windows.h>

#include <iomanip>
#include <conio.h>
#include <math.h>
const int N = 3;
using namespace std;

float a[N][N];
float b[N];
float x[N];
float graphEPS[40];
float eps = 0.0001;


void init();				// Инициализация начальной матрицы
void print();				// Вывод матрицы
void gradApprox();			// Решение слау методом простых итераций
void miss();				// Погрешность
void graph(HANDLE hStdOut);


int main()
{
	system("chcp 1251 & cls");
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	
	init();
	print();
	gradApprox();
	miss();
	Sleep(500);
	graph(hStdOut);
	
	getchar();
}



void init() {
	a[0][0] = 2;	a[0][1] = 2;	a[0][2] = 10; 		b[0] = 14;
	a[1][0] = 10;   a[1][1] = 1;   a[1][2] = 1;		b[1] = 12;
	a[2][0] = 2;	a[2][1] = 10;	a[2][2] = 1;		b[2] = 13;
}

//void init() {
//	a[0][0] = 4;	a[0][1] = 3000;	a[0][2] = 4; a[0][3] = 9; 		b[0] = 0;
//	a[1][0] = 7;    a[1][1] = 0;    a[1][2] = 8; a[1][3] = 7;	    b[1] = 87;
//	a[2][0] = 8;	a[2][1] = 8;	a[2][2] = 5; a[2][3] = 5;		b[2] = 7;
//	a[3][0] = 6;	a[3][1] = -4;	a[3][2] = 3; a[3][3] = 8;		b[3] = 6;
//}




void print() {
	cout << "\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j <N; j++)
		{
			cout << fixed << setprecision(1) << setw(5) << a[i][j] << "  ";
		}
		cout << "=  " << b[i] << "\n";
	}
	cout << "\n";
}

int k = 0;   //k = 0
void gradApprox() {
	float xk[N];
	float sum;
	float acc;									// metca = 0;
	
	
	for (int j = 0; j <N; j++) {				//for i : =1 to N do
		for (int i = 0; i <N; i++) {//
			// 	Пошук суми елементiв рядка
			sum = 0;							//s = 0
			for (int k = 0; k <N; k++) {        // |
				sum += fabs(a[i][k]);			// |
			}									//
			sum -= fabs(a[i][j]);				//
			// Перестановка рядкiв				
			if (a[i][j] > sum)					//
			{									//
				for (int l = 0; l <N; l++) {	//
					swap(a[j][l], a[i][l]);		//
				}								//
				swap(b[j], b[i]);				//
			}
		}
	}
	//Перетворення матрицi до вигляду x = ax + b
	for (int i = 0; i <N; i++) {
		b[i] /= a[i][i];
		for (int j = 0; j < N; j++) {
			if (j != i) {
				a[i][j] /= -a[i][i];
			}
		}
		a[i][i] = 0;
	}
	print();
	// Перевiра на схiднiсть
	for (int i = 0; i < N; i++) {
		sum = 0;
		for (int j = 0; j < N; j++) {
			sum += fabs(a[i][j]);
		}
		if (sum >= 1) {
			cout << "\n Помилка! Матриця не сходиться!\n";
			return;
		}
	}
	// 
	cout << "   i         x1         x2         x3         eps\n";
	for (int i = 0; i < N; i++) {
		x[i] = b[i];
	}
	for (int k = 0; k < 40; k++) {
		// Обчислення x(k + 1)
		for (int i = 0; i < N; i++) {
			xk[i] = 0;
			for (int j = 0; j < N; j++) {
				xk[i] += a[i][j] * x[j];
			}
			xk[i] += b[i];
		}
		//Обчислення точностi
		acc = abs(xk[N- 1] - x[N- 1]);
		// Вивiд результатiв
		cout << endl << fixed << setprecision(5) << setw(4) << k + 1 << " ";
		cout << setw(11) << xk[0] << " " << setw(10) << xk[1] << " " << setw(10) << xk[2] << " " << setw(11) << acc;
		for (int i = 0; i <N; i++) {
			x[i] = xk[i];
		}
		graphEPS[k] = acc;
		if (eps > acc) {// while metka = 0
			cout << "\n\nРозв'язок знайдено.\n";
			return;
		}
	}
	cout << "\nIтераційний процес не збігається.\n";// k< 50
}


void miss()
{
	init();
	cout << "\n";
	for (int i = 0; i <N; i++)
	{
		cout << "x[" << i + 1 << "] = " << x[i] << endl;
	}
	cout << "\n";
	for (int i = 0; i <N; i++)
	{
		double s = 0;								
		for (int j = 0; j <N; j++)
		{
			s += a[i][j] * x[j];
		}
		printf("a[%d] = %lf\n", i + 1, s - b[i]);
	}
}


void graph(HANDLE hStdOut)
{
	double x, y;
	SetConsoleTitle("My Menu");
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetWindowDC(hwnd);
	HPEN PEN = CreatePen(PS_DOT, 2, RGB(200, 0, 0));
	SelectObject(hdc, PEN);
	int x0 = 200;
	int y0 = 300;
	

	
	

	//=========================================================
	MoveToEx(hdc, 600, y0, NULL);
	LineTo(hdc, 800, y0);
	MoveToEx(hdc, x0 + 400, 100, NULL);
	LineTo(hdc, x0 + 400, 300);


	
	
	TextOutA(hdc, 220 + 400, 100, "eps", 3);
	TextOutA(hdc, 400 + 400, 270, "N", 2);
	
	//=========================================================

	//func
	//SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE | BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_RED);
	COLORREF newPen = RGB(0, 0, 0);
	HPEN PEN2 = CreatePen(PS_SOLID, 5, RGB(0, 200, 0));
	SelectObject(hdc, PEN2);
	int scale = 100;
	MoveToEx(hdc, x0, y0, NULL);

	for (int i = 0; i < 8; i ++)
	{
		MoveToEx(hdc, x0 + 415 + i*15, 300 , NULL);
		LineTo(hdc, x0 + 415 + i * 15, 300 - 400*graphEPS[i]);
		
		/*LineTo(hdc, x0 + x * scale, (y0 - asin(x)* scale));
		SetPixel(hdc, 535 + int(x) * 3 - i, 300 - int(y)*7.5 - i, newPen);*/
	}
}