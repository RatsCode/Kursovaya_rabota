#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <sstream>
#include <math.h>
using namespace std;


fstream fs;

class column_matrix
{
public:

	column_matrix()
	{
		size = 0;
		ptr = nullptr;
	}
	~column_matrix()
	{
		Clear();
	}

	void Set_Size(int size)
	{
		this->size = size;
	}
	int Get_Size()
	{
		return(size);
	}

	void Set_Element(int m, double value)
	{
		ptr[m] = value;
	}
	double Get_Element(int m)
	{
		return(ptr[m]);
	}

	void Show_Matrix()
	{
		for (int i = 0; i < size; i++)
		{
			cout << Get_Element(i) << endl;
		}
	}
	void Generate_Matrix(int size)
	{
		this->size = size;

		ptr = new double[size];
		for (int i = 0; i < size; i++)
		{
			ptr[i] = 0;
		}
	}
	void Fill_Rand_Values()
	{
		double value;

		for (int i = 0; i < Get_Size(); i++)
		{
			value = rand() % 100;
			Set_Element(i, value);
		}
	}
	void Clear()
	{
		delete[] ptr;

		ptr = nullptr;

		size = 0;
	}

private:

	int size;
	double* ptr;
};

class symetric_matrix
{
public:

	symetric_matrix()
	{
		this->size = 0;
		this->ptr = nullptr;
	}
	symetric_matrix(int n)
	{
		size = n;

		ptr = new double* [size];
		for (int i = 0; i < size; i++)
		{
			ptr[i] = new double[size];

			for (int j = 0; j < size; j++)
			{
				ptr[i][j] = 0;
			}
		}
	}
	~symetric_matrix()
	{
		Clear();
	}

	void Set_Size(int size)
	{
		this->size = size;
	}
	int Get_Size()
	{
		return(this->size);
	}

	void Set_Element(int m, int n, double value)
	{
		ptr[m][n] = value;
	}
	double Get_Element(int m, int n)
	{
		return(ptr[m][n]);
	}

	double det()
	{
		// определитель находим по методу разложения по строке (1)

		double det = 0;

		// если размер 1*1 определитель равен единственному члену матрицы
		if (this->Get_Size() == 1)
		{
			det = this->ptr[0][0];
			return(det); // возвращаем определитель
		}
		// если размер матрицы равен 2*2 мы можем сразу найти определитель
		if (this->Get_Size() == 2)
		{
			det = (this->ptr[0][0] * this->ptr[1][1]) - (this->ptr[0][1] * this->ptr[1][0]);
			return(det); // возвращаем определитель
		}

		// иначе ищем определитель через разложение по первой строке
		double det_minor = 0;
		symetric_matrix minor(this->Get_Size() - 1);

		for (int j = 0; j < this->Get_Size(); j++)
		{
			// находим минор для алгебраического дополнения элемента а[1][j]
			// m = 1 т.к. мы пропускаем 1 строку 
			for (int m = 1; m < this->Get_Size(); m++)
			{
				for (int n = 0, k = 0; n < this->Get_Size(); n++)
				{
					if (n == j)
					{
						k++;
						continue;
					}

					// т.к. строка m у минора будет на 1 меньше (потому что мы раскладываем по первой строке)
					// то мы вычитаем эту 1; аналогично столбец n минора будет меньше на 1, когда мы опустим j-ый столбец
					minor.Set_Element(m - 1, n - k, this->Get_Element(m, n));
				}
			}

			/*
			// мы заполнили минор, далее ищем его определитель
			// если размер минора 2*2, то мы можем найти его определитель
			// иначе вызываем для него рекурсию нахождения определителя матрицы
			if (minor.Get_Size() == 2)
			{
				det_minor = (minor.Get_Element(1, 1) * minor.Get_Element(2, 2)) - (minor.Get_Element(1, 2) * minor.Get_Element(2, 1));
			}
			else
			{
				det_minor = minor.det();
			}
			*/
			det_minor = minor.det(); // проверить работоспособность

			// det = a[1][j] * A[1][j] + ... + a[1][size] * A[1][size]
			// (значение 1 в первых крадратных скобках означает что мы расскладываем по первой строке)
			// где а - элемент матрицы, А - алгебраическое дополнение этого элемента
			// А находится А[i][j] = (-1)^(i + j) * M[i][j]
			// где М - минор, т.е. определитель матрицы меньшего порядка без i-ой и j-ого строки и столбца соответственно
			// => A[1][j] = pow((-1), 1 + j) * det_minor
			det += this->Get_Element(0, j) * pow((-1), 0 + j) * det_minor;
		}

		return(det);
	}
	bool is_symetric()
	{
		for (int i = 0; i < this->Get_Size(); i++)
		{
			for (int j = 0; j < this->Get_Size(); j++)
			{
				if (Get_Element(i, j) != Get_Element(j, i))
				{
					return(false);
				}
			}
		}

		return(true);
	}
	void Show_Matrix()
	{
		for (int i = 0; i < Get_Size(); i++)
		{
			for (int j = 0; j < Get_Size(); j++)
			{
				cout << Get_Element(i, j);

				if (j != Get_Size() - 1)
				{
					cout << "\t";
				}
				else
				{
					cout << "\n";
					break;
				}
			}
		}
	}
	void Generate_Matrix(int size)
	{
		this->size = size;

		ptr = new double* [size];
		for (int i = 0; i < size; i++)
		{
			ptr[i] = new double[size];

			for (int j = 0; j < size; j++)
			{
				ptr[i][j] = 0;
			}
		}
	}
	void Fill_Rand_Values()
	{
		double value;

		for (int i = 0, k = 0; i < Get_Size(); i++)
		{
			for (int j = 0 + k; j < Get_Size(); j++)
			{
				value = rand() % 100;
				Set_Element(i, j, value);

				if (i != j)
				{
					Set_Element(j, i, Get_Element(i, j));
				}
			}

			k++;
		}
	}
	void Clear()
	{
		for (int i = 0; i < Get_Size(); i++)
		{
			delete[] ptr[i];
		}

		delete[] ptr;

		ptr = nullptr;
		size = 0;
	}


private:

	int size;
	double** ptr;
};


class system_of_equations
{
public:

	system_of_equations()
	{
		size = 0;

		A;
		X;
		B;
	}
	~system_of_equations()
	{
		Clear_System();
	}

	void Set_Size(int value)
	{
		this->size = value;
	}
	int Get_Size()
	{
		return(this->size);
	}

	double Get_Element_A(int m, int n)
	{
		return(A.Get_Element(m, n));
	}
	double Get_det_A()
	{
		return(A.det());
	}
	bool Zero_Major_Minors_A_Check()
	{
		bool check = true;

		symetric_matrix minor;

		for (int i = 1; i < this->Get_Size(); i++)
		{
			minor.Generate_Matrix(i);

			// переносим значения матрицы А в главный минор
			for (int m = 0; m < minor.Get_Size(); m++)
			{
				for (int n = 0; n < minor.Get_Size(); n++)
				{
					minor.Set_Element(m, n, this->A.Get_Element(m, n));
				}
			}

			// проверяем равен ли определитель этого минора нулю
			if (minor.det() == 0)
			{
				check = false;
				return check;
			}

			minor.Clear();
		}

		return check;
	}

	double Get_Element_B(int m)
	{
		return(B.Get_Element(m));
	}

	double Get_Element_X(int m)
	{
		return(X.Get_Element(m));
	}
	void Set_Element_X(int m, double value)
	{
		X.Set_Element(m, value);
	}

	bool Void_Check()
	{
		if (this->Get_Size() != 0)
		{
			char sw = 0;

			while (sw != '1' && sw != '2')
			{
				system("cls");
				cout << "Внимание! Уже имеется НЕ пустая система. Выберите действие:" << endl;
				cout << "1. Удалить предыдущую систему и продолжить." << endl;
				cout << "2. Отмеить действие и вернуться." << endl;

				sw = _getch();

				system("cls");

				if (sw == '2')
				{
					return(false);
				}
				else if (sw == '1')
				{
					Clear_System();
					cout << "Система успешно очищена." << endl;
					system("pause");
					system("cls");
					return(true);
				}

				cout << "Такого действия нет" << endl;
				system("pause");
			}
		}
		else
		{
			return(true);
		}
	}
	void Show_System()
	{
		cout << endl << "A =" << endl;
		A.Show_Matrix();

		cout << endl << "B =" << endl;
		B.Show_Matrix();

		cout << endl << "X =" << endl;
		X.Show_Matrix();
	}
	void Clear_System()
	{
		A.Clear();
		X.Clear();
		B.Clear();

		size = 0;
	}
	void Generate_System_Self()
	{
		system("cls");

		if (!Void_Check())
		{
			return;
		}

		Set_Size(Ask_Size());

		A.Generate_Matrix(this->Get_Size());
		X.Generate_Matrix(this->Get_Size());
		B.Generate_Matrix(this->Get_Size());

		string equation; // впомогательная строка
		bool sign = true; // для определения знака
		double value = 0; // вспомогательная переменная

		for (int i = 0; i < this->Get_Size(); i++)
		{
		back1: // начало внешнего цикла

			system("cls");

			Show_System();

			cout << endl;
			cout << "Введите систему уравнений:" << endl;
			cout << "(Вводить нужно значения и математические знаки через пробел." << endl;
			cout << " Вводить произведения коэффициентов на неизвестные нужно по порядковому номеру неизвестных." << endl;
			cout << " Например, -7 * x1 + 4 * x2 - 10 * x3 = -15." << endl;
			cout << " Если первый коэффициент уравнения и/или свободный член отрицателен, знак \"-\" пишется без пробела, иначе может произойти потеря знака." << endl;
			cout << " Внимание! Если будет введено больше произведений коэффициентов на неизвестные, то считается лишь количество произведений равное указанному размеру!" << endl;
			cout << " Внимание! Матрица должна быть симметричной! При вводе учитывайте это.)" << endl;
			cout << " (Количество уравнений равно " << this->Get_Size() << "." << " Введено: " << i << ".)" << endl << endl;

			getline(cin, equation);
			stringstream equat_st(equation); // поток для этой строки

			for (int j = 0; j < this->Get_Size(); j++)
			{
				equat_st >> value;
				if (!sign) // изменяем знак
				{
					value = -value;
					sign = true;
				}
				A.Set_Element(i, j, value);

				for (char c = 0;;) // ищем следующий знак
				{
					c = equat_st.get();

					if ((j != this->Get_Size() - 1) && (c == '+' || c == '-'))
					{
						if (c == '-')
						{
							sign = false;
						}

						break;
					}
					else if (c == '=')
					{
						if (j != this->Get_Size() - 1)
						{
							char sw = 0;

						back2: // начало ошибки нахождения "="

							cout << "Внинание! Не найден один или несколько произведений коэффициентов на неизвестные." << endl;
							cout << "1. Продолжить и принять их равными 0" << endl;
							cout << "2. Вернуться и ввести уравнение заново" << endl;

							sw = _getch();

							if (sw == '1')
							{
								for (; j < this->Get_Size(); j++)
								{
									A.Set_Element(i, j, 0);
								}

								cout << "Успешно установлены значения 0" << endl;
								system("pause");

								equat_st >> value;
								B.Set_Element(i, value);
								break;
							}
							else if (sw == '2')
							{
								goto back1; // возвращаемся в начало внешнего цикла
							}
							else
							{
								cout << "Ошибка: такого пункта нет" << endl;
								system("pause");
								system("cls");
								goto back2; // возвращаемся в начало ошибки
							}
						}
						else
						{
							equat_st >> value;
							B.Set_Element(i, value);
							break;
						}
					}
					else if (c == EOF)
					{
						char sw = 0;

					back3: // начало ошибки нахождения EOF

						cout << "Внинание! Не найден один или несколько произведений коэффициентов на неизвестные и/или знак равентва." << endl;
						cout << "1. Продолжить и принять их равными 0" << endl;
						cout << "2. Вернуться и ввести уравнение заново" << endl;

						sw = _getch();

						if (sw == '1')
						{
							for (; j < this->Get_Size(); j++)
							{
								A.Set_Element(i, j, 0);
							}
							B.Set_Element(i, 0);

							cout << "Успешно установлены значения 0" << endl;
							system("pause");

							break;
							//goto forward1; // идем в конец внешнего цикла после присваивания свободного члена
						}
						else if (sw == '2')
						{
							goto back1; // возвращаемся в начало внешнего цикла
						}
						else
						{
							cout << "Ошибка: такого пункта нет" << endl;
							system("pause");
							system("cls");
							goto back3; // возвращаемся в начало ошибки нахождения EOF
						}
					}
				}
			}

			//forward1: // конец внешнего цикла
		}

		if (!A.is_symetric())
		{
		back_self: // начало ошибки симметричности при вводе в ручную

			char sw = 0;

			cout << "Внимание! Матрица А не симметрична!" << endl;
			cout << "1. Очистить систему и ввести данные снова" << endl;
			cout << "2. Очистить систему и вернуться назад" << endl;

			sw = _getch();

			if (sw == '1')
			{
				Clear_System();
				Generate_System_Self();
				return;
			}
			else if (sw == '2')
			{
				Clear_System();
				return;
			}
			else
			{
				cout << "Такого пункта нет" << endl;
				system("pause");
				system("cls");
				goto back_self; // вернуться в начало ошибки симметричности при вводе в ручную
			}
		}

	}
	void Generate_System_Rand()
	{
		system("cls");

		if (!Void_Check())
		{
			return;
		}

		this->Set_Size(Ask_Size());

		A.Generate_Matrix(this->Get_Size());
		X.Generate_Matrix(this->Get_Size());
		B.Generate_Matrix(this->Get_Size());

		A.Fill_Rand_Values();
		B.Fill_Rand_Values();
	}
	void Read_System_From_File()
	{
		system("cls");

		if (!Void_Check())
		{
			return;
		}

		string path;

	r_f_f: // ввод названия фаила

		cout << "Введите путь или название фаила(если фаил в дирректории с программой):" << endl;
		getline(cin, path);

		fs.open(path, fstream::in);
		
		// обработка ошибки открытия фаила
		if (!fs.is_open())
		{
			char sw = 0;

			while (sw != '1' && sw != '2')
			{
				cout << "Ошибка открытия фаила. Выберите действие:" << endl;
				cout << "1. Отменить считывание из фаила и вернуться" << endl;
				cout << "2. Ввести название фаила заново" << endl;
				sw = _getch();

				if (sw == '1')
				{
					return;
				}
				else if (sw == '2')
				{
					system("cls");
					goto r_f_f; // вернуться в начало метода где вводится название фаила
				}

				cout << "Ошибка: такого действия нет" << endl;
				system("pause");
				system("cls");
			}
		}

		Set_Size(Ask_Size());

		A.Generate_Matrix(this->Get_Size());
		X.Generate_Matrix(this->Get_Size());
		B.Generate_Matrix(this->Get_Size());

		double value = 0;
		bool sign = true;

		for (int i = 0; i < this->Get_Size(); i++)
		{
			for (int j = 0; j < this->Get_Size(); j++)
			{
				fs >> value;
				if (!sign) // изменяем знак
				{
					value = -value;
					sign = true;
				}
				A.Set_Element(i, j, value);

				for (char c = 0;;) // ищем следующий знак
				{
					c = fs.get();

					if ((j != this->Get_Size() - 1) && (c == '+' || c == '-'))
					{
						if (c == '-')
						{
							sign = false;
						}

						break;
					}
					else if (c == '=')
					{
						if (j != this->Get_Size() - 1)
						{
							char sw = 0;

						back2: // начало ошибки нахождения "="

							cout << "Внинание! Не найден один или несколько произведений коэффициентов на неизвестные." << endl;
							cout << "1. Продолжить и принять их равными 0" << endl;
							cout << "2. Отменить чтение и вернуться" << endl;

							sw = _getch();

							if (sw == '1')
							{
								for (; j < this->Get_Size(); j++)
								{
									A.Set_Element(i, j, 0);
								}

								cout << "Успешно установлены значения 0" << endl;
								system("pause");
								system("cls");

								fs >> value;
								B.Set_Element(i, value);
								break;
							}
							else if (sw == '2')
							{
								fs.close();
								system("cls");
								return;
							}
							else
							{
								cout << "Ошибка: такого пункта нет" << endl;
								system("pause");
								system("cls");
								goto back2; // возвращаемся в начало ошибки
							}
						}
						else
						{
							fs >> value;
							B.Set_Element(i, value);
							break;
						}
					}
					else if (c == '\n')
					{
						char sw = 0;

					back3: // начало ошибки нахождения EOF

						cout << "Внинание! Не найден один или несколько произведений коэффициентов на неизвестные и/или знак равентва." << endl;
						cout << "1. Продолжить и принять их равными 0" << endl;
						cout << "2. Отменить чтение и вернуться" << endl;

						sw = _getch();

						if (sw == '1')
						{
							for (; j < this->Get_Size(); j++)
							{
								A.Set_Element(i, j, 0);
							}
							B.Set_Element(i, 0);

							cout << "Успешно установлены значения 0" << endl;
							system("pause");
							system("cls");

							break;
						}
						else if (sw == '2')
						{
							fs.close();
							system("cls");
							return;
						}
						else
						{
							cout << "Ошибка: такого пункта нет" << endl;
							system("pause");
							system("cls");
							goto back3; // возвращаемся в начало ошибки нахождения EOF
						}
					}
					else if (c == EOF)
					{
						char sw = 0;

					back4:

						cout << "Внимание! Найден конец фаила! Выберите действие:" << endl;
						cout << "1. Продолжить и принять все не найденные значения равными 0" << endl;
						cout << "2. Отменить чтение и вернуться" << endl;

						sw = _getch();

						if (sw == '1')
						{
							// при генерации матриц значения по умолчанию - 0

							cout << "Успешно установлены значения 0" << endl;
							system("pause");
							system("cls");

							fs.close();
							system("cls");
							return;
						}
						else if (sw == '2')
						{
							fs.close();
							system("cls");
							return;
						}
						else
						{
							cout << "Ошибка: такого пункта нет" << endl;
							system("pause");
							system("cls");
							goto back4; // возвращаемся в начало ошибки нахождения EOF
						}
					}
				}
			}
		}

		if (!A.is_symetric())
		{
			fs.close();

		back_read: // начало ошибки симметричности при вводе в ручную

			char sw = 0;

			cout << "Внимание! Матрица А не симметрична!" << endl;
			cout << "1. Очистить систему и ввести данные снова" << endl;
			cout << "2. Очистить систему и вернуться назад" << endl;

			sw = _getch();

			if (sw == '1')
			{
				Clear_System();
				Generate_System_Self();
				return;
			}
			else if (sw == '2')
			{
				Clear_System();
				return;
			}
			else
			{
				cout << "Такого пункта нет" << endl;
				system("pause");
				system("cls");
				goto back_read; // вернуться в начало ошибки симметричности при вводе в ручную
			}
		}
	}

private:

	int size;

	symetric_matrix A; // двумерный массив матрицы коэффициентов
	column_matrix X; // матрица размера 1*size неизвестных
	column_matrix B; // матрица размера 1*size свободных элементов

	int Ask_Size()
	{
		int in_size;
		cout << "Введите количество неизвестных X: ";
		cin >> in_size;
		cin.ignore();

		return(in_size);
	}
};



void input_menu(system_of_equations &syst)
{
	char sw = 0;

	while (sw != 6)
	{
		system("cls");

		cout << "Выберите метод ввода значений матрицы:" << endl;
		cout << "1. Ввести все данные самостоятельно" << endl;
		cout << "2. Считать данные из фаила" << endl;
		cout << "3. Сгенерировать значения автоматически" << endl;
		cout << "4. Помощь" << endl;
		cout << "5. Вернуться в главное меню" << endl;

		sw = _getch();

		switch (sw)
		{
		case '1':

			system("cls");
			syst.Generate_System_Self();
			return;

		case '2':

			system("cls");
			syst.Read_System_From_File();
			return;

		case '3':

			system("cls");
			syst.Generate_System_Rand();
			return;

		case '4':

			system("cls");
			cout << "Пункт 1 позволяет ввести систему в стандартном виде вручную, последовательно по 1 уравнению" << endl;
			cout << "Пункт 2 позволяет считать сразу всю систему, введенную предварительно в фаил в стандартном виде" << endl;
			cout << "Пункт 3 позволяет сгенерировать значения автоматически. (Значения будут сгенерированы с необходимом для дальнейшей работы виде)" << endl;
			cout << "Во всех этих пунктах необходимо заранее знать и указать (соответствующий диалог будет в каждом пункте) количество неизвестных Х" << endl;
			cout << "Инструкции по введению данных предусмотрены в каждом пункте ввода информации" << endl;
			cout << "Пункт 5 возвращает в главное меню" << endl;

			break;

		case '5':

			return;

		default:

			cout << "Ошибка: такого пункта нет." << endl;
			system("pause");
			break;
		}
	}
}

void square_root_method(system_of_equations &syst)
{
	system("cls");
	// т.к. мы создали симметриную матрицу еще при вводе, то нет смысла проверять этот пункт

	// проверка равентсва нулю определителя матрицы А
	if (syst.Get_det_A() == 0)
	{
		cout << "Внимание! Определитель матрицы А равен 0, следовательно решение неоднозначно!" << endl;
		cout << "Проверьте данные (и исправьте если нужно) и попробуйте снова" << endl;

		system("pause");
		return;
	}

	// проверка равенства нулю главных миноров
	if (!syst.Zero_Major_Minors_A_Check())
	{
		cout << "Внимание! Определитель одного или нескольких главных миноров матрицы А равен 0!" << endl;
		cout << "Из-за чего не получится разложить матрицу А на две треугольных!" << endl;
		cout << "Проверьте данные (и исправьте если нужно) и попробуйте снова" << endl;

		system("pause");
		return;
	}

	// т. к. матрица Т и Т' транспонированны друг относительно друга, то можно создать только одну симметричную матрицу Т
	// в которой правый верхний угол будет отвечать за Т, а нижний левый - за Т'
	symetric_matrix T;
	T.Generate_Matrix(syst.Get_Size());


	// вычисление значений треугольной матрицы T
	// -------------------------------------------------

	// t11 = sqrt(a11) [находим первый элемент]
	T.Set_Element(0, 0, sqrt(syst.Get_Element_A(0, 0)));

	// t1j = a1j / t11 [находим первую строку элементов помимо первого]
	for (int j = 1; j < T.Get_Size(); j++)
	{
		T.Set_Element(0, j, syst.Get_Element_A(0, j) / T.Get_Element(0, 0));

		T.Set_Element(j, 0, T.Get_Element(0, j));
	}

	double sum = 0;

	// tii = sqrt(aii - сумма от k до n-1 tki^2) [находим элементы на главной диагонали]
	for (int i = 1; i < T.Get_Size(); i++)
	{
		for (int k = 0; k < i; k++)
		{
			sum += pow(T.Get_Element(k, i), 2);
		}

		T.Set_Element(i, i, sqrt(syst.Get_Element_A(i, i) - sum));

		if (T.Get_Element(i, i) == 0)
		{
			cout << "Внимание t[" << i << "][" << i << "] = 0 ! В следующем действии планируется выполнить деление на этот элемент." << endl;
			cout << "Проверьте правильность ввода данных и попробуйте снова (если нужно изменить данные измените)" << endl;
			cout << "Вы будете возвращены в главное меню" << endl;

			system("pause");
			return;
		}

		sum = 0;
	}

	// tij = (aij - сумма от k до n-1 tki * tkj) / tii [находим элементы правого верхнего угла под первой строкой]
	for (int i = 1; i < T.Get_Size() - 1; i++)
	{
		for (int j = i + 1; j < T.Get_Size(); j++)
		{
			for (int k = 0; k < i; k++)
			{
				sum += T.Get_Element(k, i) * T.Get_Element(k, j);
			}

			T.Set_Element(i, j, (syst.Get_Element_A(i, j) - sum) / T.Get_Element(i, i));

			T.Set_Element(j, i, T.Get_Element(i, j));

			sum = 0;
		}
	}
	
	// -------------------------------------------------



	// вспомогательная матрица-столбец для вычислений
	column_matrix Y;
	Y.Generate_Matrix(syst.Get_Size());


	// вычисление значений для вспомогательной матрицы Y
	// -------------------------------------------------

	// первый элемент
	Y.Set_Element(0, syst.Get_Element_B(0) / T.Get_Element(0, 0));

	// остальные n элементов
	for (int i = 1; i < Y.Get_Size(); i++)
	{
		for (int k = 0; k < i; k++)
		{
			sum += T.Get_Element(k, i) * Y.Get_Element(k);
		}

		Y.Set_Element(i, (syst.Get_Element_B(i) - sum) / T.Get_Element(i, i));

		sum = 0;
	}

	// -------------------------------------------------


	// нахождение неизвестных
	// -------------------------------------------------

	// последний элемент
	syst.Set_Element_X(syst.Get_Size() - 1, Y.Get_Element(syst.Get_Size() - 1) / T.Get_Element(syst.Get_Size() - 1, syst.Get_Size() - 1));

	// остальные элементы
	for (int i = syst.Get_Size() - 2; i >= 0; i--)
	{
		for (int k = i + 1; k < syst.Get_Size(); k++)
		{
			sum += T.Get_Element(i, k) * syst.Get_Element_X(k);
		}

		syst.Set_Element_X(i, (Y.Get_Element(i) - sum) / T.Get_Element(i, i));

		sum = 0;
	}
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	system("color 0B");

	system_of_equations syst;
	char menu = 0;

	while (menu != 9)
	{
		system("cls");
		cout << "\tГлавное меню" << endl;
		cout << "1. Ввести данные системы уравнений" << endl;
		cout << "2. Вывести матрицы с данными на экран" << endl;
		cout << "3. Очистить систему" << endl;
		cout << "4. Выполнить нахождение неизвестных методом квадратного корня" << endl;
		cout << "5. Помощь" << endl;
		cout << "6. Выход" << endl;

		menu = _getch();


		switch (menu)
		{
		case'1':

			input_menu(syst);

			break;

		case '2':

			system("cls");
			if (syst.Get_Size() == 0)
			{
				cout << "Внимание! Данных пока нет" << endl;
				system("pause");

				break;
			}
			else
			{
				syst.Show_System();
				system("pause");

				break;
			}

		case '3':

			system("cls");
			if (syst.Get_Size() == 0)
			{
				cout << "Внимание! Данных пока нет" << endl;
				system("pause");

				break;
			}
			else
			{
				syst.Clear_System();
				system("cls");
				cout << "Система успешно очищена!" << endl;
				system("pause");

				break;
			}

		case '4':

			system("cls");
			if (syst.Get_Size() == 0)
			{
				cout << "Внимание! Данных пока нет" << endl;
				system("pause");

				break;
			}
			else
			{
				square_root_method(syst);
				cout << "Метод успешно выполнен!!" << endl;
				system("pause");

				break;
			}

		case '5':

			system("cls");

			cout << "Пункт 1 откроет вспомогательное меню, в котором есть свое описание всех действий" << endl;
			cout << "Пункт 2 выведет на экран матрицу А, В и Х" << endl;
			cout << "Пункт 3 очистит данные матриц системы" << endl;
			cout << "Пункт 4 начнет выполнение метода квадратных корней и выведет в качестве результата матрицу неизвестных Х" << endl;
			cout << "(Все ее значения будут присвоены соответсвующей матрице системы, т. е. они выведутся при выводе матрицы, вместо 0 по умолчанию)" << endl;
			cout << "Пункт 6 - завершение программы" << endl;

			system("pause");

			break;

		case '6':

			exit(0);

		default:

			system("cls");
			cout << "Ошибка: такого пункта нет." << endl;
			system("pause");

			break;

		}
	}
	

	return 0;
}