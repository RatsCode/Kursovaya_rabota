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
		// ������������ ������� �� ������ ���������� �� ������ (1)

		double det = 0;

		// ���� ������ 1*1 ������������ ����� ������������� ����� �������
		if (this->Get_Size() == 1)
		{
			det = this->ptr[0][0];
			return(det); // ���������� ������������
		}
		// ���� ������ ������� ����� 2*2 �� ����� ����� ����� ������������
		if (this->Get_Size() == 2)
		{
			det = (this->ptr[0][0] * this->ptr[1][1]) - (this->ptr[0][1] * this->ptr[1][0]);
			return(det); // ���������� ������������
		}

		// ����� ���� ������������ ����� ���������� �� ������ ������
		double det_minor = 0;
		symetric_matrix minor(this->Get_Size() - 1);

		for (int j = 0; j < this->Get_Size(); j++)
		{
			// ������� ����� ��� ��������������� ���������� �������� �[1][j]
			// m = 1 �.�. �� ���������� 1 ������ 
			for (int m = 1; m < this->Get_Size(); m++)
			{
				for (int n = 0, k = 0; n < this->Get_Size(); n++)
				{
					if (n == j)
					{
						k++;
						continue;
					}

					// �.�. ������ m � ������ ����� �� 1 ������ (������ ��� �� ������������ �� ������ ������)
					// �� �� �������� ��� 1; ���������� ������� n ������ ����� ������ �� 1, ����� �� ������� j-�� �������
					minor.Set_Element(m - 1, n - k, this->Get_Element(m, n));
				}
			}

			/*
			// �� ��������� �����, ����� ���� ��� ������������
			// ���� ������ ������ 2*2, �� �� ����� ����� ��� ������������
			// ����� �������� ��� ���� �������� ���������� ������������ �������
			if (minor.Get_Size() == 2)
			{
				det_minor = (minor.Get_Element(1, 1) * minor.Get_Element(2, 2)) - (minor.Get_Element(1, 2) * minor.Get_Element(2, 1));
			}
			else
			{
				det_minor = minor.det();
			}
			*/
			det_minor = minor.det(); // ��������� �����������������

			// det = a[1][j] * A[1][j] + ... + a[1][size] * A[1][size]
			// (�������� 1 � ������ ���������� ������� �������� ��� �� ������������� �� ������ ������)
			// ��� � - ������� �������, � - �������������� ���������� ����� ��������
			// � ��������� �[i][j] = (-1)^(i + j) * M[i][j]
			// ��� � - �����, �.�. ������������ ������� �������� ������� ��� i-�� � j-��� ������ � ������� ��������������
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

			// ��������� �������� ������� � � ������� �����
			for (int m = 0; m < minor.Get_Size(); m++)
			{
				for (int n = 0; n < minor.Get_Size(); n++)
				{
					minor.Set_Element(m, n, this->A.Get_Element(m, n));
				}
			}

			// ��������� ����� �� ������������ ����� ������ ����
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
				cout << "��������! ��� ������� �� ������ �������. �������� ��������:" << endl;
				cout << "1. ������� ���������� ������� � ����������." << endl;
				cout << "2. ������� �������� � ���������." << endl;

				sw = _getch();

				system("cls");

				if (sw == '2')
				{
					return(false);
				}
				else if (sw == '1')
				{
					Clear_System();
					cout << "������� ������� �������." << endl;
					system("pause");
					system("cls");
					return(true);
				}

				cout << "������ �������� ���" << endl;
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

		string equation; // �������������� ������
		bool sign = true; // ��� ����������� �����
		double value = 0; // ��������������� ����������

		for (int i = 0; i < this->Get_Size(); i++)
		{
		back1: // ������ �������� �����

			system("cls");

			Show_System();

			cout << endl;
			cout << "������� ������� ���������:" << endl;
			cout << "(������� ����� �������� � �������������� ����� ����� ������." << endl;
			cout << " ������� ������������ ������������� �� ����������� ����� �� ����������� ������ �����������." << endl;
			cout << " ��������, -7 * x1 + 4 * x2 - 10 * x3 = -15." << endl;
			cout << " ���� ������ ����������� ��������� �/��� ��������� ���� �����������, ���� \"-\" ������� ��� �������, ����� ����� ��������� ������ �����." << endl;
			cout << " ��������! ���� ����� ������� ������ ������������ ������������� �� �����������, �� ��������� ���� ���������� ������������ ������ ���������� �������!" << endl;
			cout << " ��������! ������� ������ ���� ������������! ��� ����� ���������� ���.)" << endl;
			cout << " (���������� ��������� ����� " << this->Get_Size() << "." << " �������: " << i << ".)" << endl << endl;

			getline(cin, equation);
			stringstream equat_st(equation); // ����� ��� ���� ������

			for (int j = 0; j < this->Get_Size(); j++)
			{
				equat_st >> value;
				if (!sign) // �������� ����
				{
					value = -value;
					sign = true;
				}
				A.Set_Element(i, j, value);

				for (char c = 0;;) // ���� ��������� ����
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

						back2: // ������ ������ ���������� "="

							cout << "��������! �� ������ ���� ��� ��������� ������������ ������������� �� �����������." << endl;
							cout << "1. ���������� � ������� �� ������� 0" << endl;
							cout << "2. ��������� � ������ ��������� ������" << endl;

							sw = _getch();

							if (sw == '1')
							{
								for (; j < this->Get_Size(); j++)
								{
									A.Set_Element(i, j, 0);
								}

								cout << "������� ����������� �������� 0" << endl;
								system("pause");

								equat_st >> value;
								B.Set_Element(i, value);
								break;
							}
							else if (sw == '2')
							{
								goto back1; // ������������ � ������ �������� �����
							}
							else
							{
								cout << "������: ������ ������ ���" << endl;
								system("pause");
								system("cls");
								goto back2; // ������������ � ������ ������
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

					back3: // ������ ������ ���������� EOF

						cout << "��������! �� ������ ���� ��� ��������� ������������ ������������� �� ����������� �/��� ���� ��������." << endl;
						cout << "1. ���������� � ������� �� ������� 0" << endl;
						cout << "2. ��������� � ������ ��������� ������" << endl;

						sw = _getch();

						if (sw == '1')
						{
							for (; j < this->Get_Size(); j++)
							{
								A.Set_Element(i, j, 0);
							}
							B.Set_Element(i, 0);

							cout << "������� ����������� �������� 0" << endl;
							system("pause");

							break;
							//goto forward1; // ���� � ����� �������� ����� ����� ������������ ���������� �����
						}
						else if (sw == '2')
						{
							goto back1; // ������������ � ������ �������� �����
						}
						else
						{
							cout << "������: ������ ������ ���" << endl;
							system("pause");
							system("cls");
							goto back3; // ������������ � ������ ������ ���������� EOF
						}
					}
				}
			}

			//forward1: // ����� �������� �����
		}

		if (!A.is_symetric())
		{
		back_self: // ������ ������ �������������� ��� ����� � ������

			char sw = 0;

			cout << "��������! ������� � �� �����������!" << endl;
			cout << "1. �������� ������� � ������ ������ �����" << endl;
			cout << "2. �������� ������� � ��������� �����" << endl;

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
				cout << "������ ������ ���" << endl;
				system("pause");
				system("cls");
				goto back_self; // ��������� � ������ ������ �������������� ��� ����� � ������
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

	r_f_f: // ���� �������� �����

		cout << "������� ���� ��� �������� �����(���� ���� � ����������� � ����������):" << endl;
		getline(cin, path);

		fs.open(path, fstream::in);
		
		// ��������� ������ �������� �����
		if (!fs.is_open())
		{
			char sw = 0;

			while (sw != '1' && sw != '2')
			{
				cout << "������ �������� �����. �������� ��������:" << endl;
				cout << "1. �������� ���������� �� ����� � ���������" << endl;
				cout << "2. ������ �������� ����� ������" << endl;
				sw = _getch();

				if (sw == '1')
				{
					return;
				}
				else if (sw == '2')
				{
					system("cls");
					goto r_f_f; // ��������� � ������ ������ ��� �������� �������� �����
				}

				cout << "������: ������ �������� ���" << endl;
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
				if (!sign) // �������� ����
				{
					value = -value;
					sign = true;
				}
				A.Set_Element(i, j, value);

				for (char c = 0;;) // ���� ��������� ����
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

						back2: // ������ ������ ���������� "="

							cout << "��������! �� ������ ���� ��� ��������� ������������ ������������� �� �����������." << endl;
							cout << "1. ���������� � ������� �� ������� 0" << endl;
							cout << "2. �������� ������ � ���������" << endl;

							sw = _getch();

							if (sw == '1')
							{
								for (; j < this->Get_Size(); j++)
								{
									A.Set_Element(i, j, 0);
								}

								cout << "������� ����������� �������� 0" << endl;
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
								cout << "������: ������ ������ ���" << endl;
								system("pause");
								system("cls");
								goto back2; // ������������ � ������ ������
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

					back3: // ������ ������ ���������� EOF

						cout << "��������! �� ������ ���� ��� ��������� ������������ ������������� �� ����������� �/��� ���� ��������." << endl;
						cout << "1. ���������� � ������� �� ������� 0" << endl;
						cout << "2. �������� ������ � ���������" << endl;

						sw = _getch();

						if (sw == '1')
						{
							for (; j < this->Get_Size(); j++)
							{
								A.Set_Element(i, j, 0);
							}
							B.Set_Element(i, 0);

							cout << "������� ����������� �������� 0" << endl;
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
							cout << "������: ������ ������ ���" << endl;
							system("pause");
							system("cls");
							goto back3; // ������������ � ������ ������ ���������� EOF
						}
					}
					else if (c == EOF)
					{
						char sw = 0;

					back4:

						cout << "��������! ������ ����� �����! �������� ��������:" << endl;
						cout << "1. ���������� � ������� ��� �� ��������� �������� ������� 0" << endl;
						cout << "2. �������� ������ � ���������" << endl;

						sw = _getch();

						if (sw == '1')
						{
							// ��� ��������� ������ �������� �� ��������� - 0

							cout << "������� ����������� �������� 0" << endl;
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
							cout << "������: ������ ������ ���" << endl;
							system("pause");
							system("cls");
							goto back4; // ������������ � ������ ������ ���������� EOF
						}
					}
				}
			}
		}

		if (!A.is_symetric())
		{
			fs.close();

		back_read: // ������ ������ �������������� ��� ����� � ������

			char sw = 0;

			cout << "��������! ������� � �� �����������!" << endl;
			cout << "1. �������� ������� � ������ ������ �����" << endl;
			cout << "2. �������� ������� � ��������� �����" << endl;

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
				cout << "������ ������ ���" << endl;
				system("pause");
				system("cls");
				goto back_read; // ��������� � ������ ������ �������������� ��� ����� � ������
			}
		}
	}

private:

	int size;

	symetric_matrix A; // ��������� ������ ������� �������������
	column_matrix X; // ������� ������� 1*size �����������
	column_matrix B; // ������� ������� 1*size ��������� ���������

	int Ask_Size()
	{
		int in_size;
		cout << "������� ���������� ����������� X: ";
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

		cout << "�������� ����� ����� �������� �������:" << endl;
		cout << "1. ������ ��� ������ ��������������" << endl;
		cout << "2. ������� ������ �� �����" << endl;
		cout << "3. ������������� �������� �������������" << endl;
		cout << "4. ������" << endl;
		cout << "5. ��������� � ������� ����" << endl;

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
			cout << "����� 1 ��������� ������ ������� � ����������� ���� �������, ��������������� �� 1 ���������" << endl;
			cout << "����� 2 ��������� ������� ����� ��� �������, ��������� �������������� � ���� � ����������� ����" << endl;
			cout << "����� 3 ��������� ������������� �������� �������������. (�������� ����� ������������� � ����������� ��� ���������� ������ ����)" << endl;
			cout << "�� ���� ���� ������� ���������� ������� ����� � ������� (��������������� ������ ����� � ������ ������) ���������� ����������� �" << endl;
			cout << "���������� �� �������� ������ ������������� � ������ ������ ����� ����������" << endl;
			cout << "����� 5 ���������� � ������� ����" << endl;

			break;

		case '5':

			return;

		default:

			cout << "������: ������ ������ ���." << endl;
			system("pause");
			break;
		}
	}
}

void square_root_method(system_of_equations &syst)
{
	system("cls");
	// �.�. �� ������� ����������� ������� ��� ��� �����, �� ��� ������ ��������� ���� �����

	// �������� ��������� ���� ������������ ������� �
	if (syst.Get_det_A() == 0)
	{
		cout << "��������! ������������ ������� � ����� 0, ������������� ������� ������������!" << endl;
		cout << "��������� ������ (� ��������� ���� �����) � ���������� �����" << endl;

		system("pause");
		return;
	}

	// �������� ��������� ���� ������� �������
	if (!syst.Zero_Major_Minors_A_Check())
	{
		cout << "��������! ������������ ������ ��� ���������� ������� ������� ������� � ����� 0!" << endl;
		cout << "��-�� ���� �� ��������� ��������� ������� � �� ��� �����������!" << endl;
		cout << "��������� ������ (� ��������� ���� �����) � ���������� �����" << endl;

		system("pause");
		return;
	}

	// �. �. ������� � � �' ���������������� ���� ������������ �����, �� ����� ������� ������ ���� ������������ ������� �
	// � ������� ������ ������� ���� ����� �������� �� �, � ������ ����� - �� �'
	symetric_matrix T;
	T.Generate_Matrix(syst.Get_Size());


	// ���������� �������� ����������� ������� T
	// -------------------------------------------------

	// t11 = sqrt(a11) [������� ������ �������]
	T.Set_Element(0, 0, sqrt(syst.Get_Element_A(0, 0)));

	// t1j = a1j / t11 [������� ������ ������ ��������� ������ �������]
	for (int j = 1; j < T.Get_Size(); j++)
	{
		T.Set_Element(0, j, syst.Get_Element_A(0, j) / T.Get_Element(0, 0));

		T.Set_Element(j, 0, T.Get_Element(0, j));
	}

	double sum = 0;

	// tii = sqrt(aii - ����� �� k �� n-1 tki^2) [������� �������� �� ������� ���������]
	for (int i = 1; i < T.Get_Size(); i++)
	{
		for (int k = 0; k < i; k++)
		{
			sum += pow(T.Get_Element(k, i), 2);
		}

		T.Set_Element(i, i, sqrt(syst.Get_Element_A(i, i) - sum));

		if (T.Get_Element(i, i) == 0)
		{
			cout << "�������� t[" << i << "][" << i << "] = 0 ! � ��������� �������� ����������� ��������� ������� �� ���� �������." << endl;
			cout << "��������� ������������ ����� ������ � ���������� ����� (���� ����� �������� ������ ��������)" << endl;
			cout << "�� ������ ���������� � ������� ����" << endl;

			system("pause");
			return;
		}

		sum = 0;
	}

	// tij = (aij - ����� �� k �� n-1 tki * tkj) / tii [������� �������� ������� �������� ���� ��� ������ �������]
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



	// ��������������� �������-������� ��� ����������
	column_matrix Y;
	Y.Generate_Matrix(syst.Get_Size());


	// ���������� �������� ��� ��������������� ������� Y
	// -------------------------------------------------

	// ������ �������
	Y.Set_Element(0, syst.Get_Element_B(0) / T.Get_Element(0, 0));

	// ��������� n ���������
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


	// ���������� �����������
	// -------------------------------------------------

	// ��������� �������
	syst.Set_Element_X(syst.Get_Size() - 1, Y.Get_Element(syst.Get_Size() - 1) / T.Get_Element(syst.Get_Size() - 1, syst.Get_Size() - 1));

	// ��������� ��������
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
		cout << "\t������� ����" << endl;
		cout << "1. ������ ������ ������� ���������" << endl;
		cout << "2. ������� ������� � ������� �� �����" << endl;
		cout << "3. �������� �������" << endl;
		cout << "4. ��������� ���������� ����������� ������� ����������� �����" << endl;
		cout << "5. ������" << endl;
		cout << "6. �����" << endl;

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
				cout << "��������! ������ ���� ���" << endl;
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
				cout << "��������! ������ ���� ���" << endl;
				system("pause");

				break;
			}
			else
			{
				syst.Clear_System();
				system("cls");
				cout << "������� ������� �������!" << endl;
				system("pause");

				break;
			}

		case '4':

			system("cls");
			if (syst.Get_Size() == 0)
			{
				cout << "��������! ������ ���� ���" << endl;
				system("pause");

				break;
			}
			else
			{
				square_root_method(syst);
				cout << "����� ������� ��������!!" << endl;
				system("pause");

				break;
			}

		case '5':

			system("cls");

			cout << "����� 1 ������� ��������������� ����, � ������� ���� ���� �������� ���� ��������" << endl;
			cout << "����� 2 ������� �� ����� ������� �, � � �" << endl;
			cout << "����� 3 ������� ������ ������ �������" << endl;
			cout << "����� 4 ������ ���������� ������ ���������� ������ � ������� � �������� ���������� ������� ����������� �" << endl;
			cout << "(��� �� �������� ����� ��������� �������������� ������� �������, �. �. ��� ��������� ��� ������ �������, ������ 0 �� ���������)" << endl;
			cout << "����� 6 - ���������� ���������" << endl;

			system("pause");

			break;

		case '6':

			exit(0);

		default:

			system("cls");
			cout << "������: ������ ������ ���." << endl;
			system("pause");

			break;

		}
	}
	

	return 0;
}