#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "");
	ofstream MainFileOut;
	ifstream MainFileIn;
	ofstream file1Out;
	ifstream file1In;
	ofstream file2Out;
	ifstream file2In;
	ofstream BufferOut;
	ifstream BufferIn;
	cout << "Введите кол-во чисел для сортировки: ";
	unsigned long long quantity;
	cin >> quantity;
	int tek1, tek2;
	cout << "Выводить ли не отсортированное содержание файла? (1 - да, 0 - нет)\n";
	bool f;
	cin >> f;
	MainFileOut.open("Files/MainFile.dat");
	for (unsigned long long i = 0; i < quantity; i++)
	{
		tek1 = rand();
		MainFileOut.write((char*)&tek1, sizeof(int));
		if (f)
			cout << tek1 << '\n';
	}
	MainFileOut.close();
	quantity = 0; //предполагаем что кол-во сортируемых объектов не известно
	MainFileIn.open("Files/MainFile.dat");
	MainFileIn.seekg(0, ios::end);
	quantity = MainFileIn.tellg() / sizeof(int); //хранит кол-во сортируемых объектов
	MainFileIn.close();

	//НАЧАЛО АЛГОРИТМА

	unsigned long long k = 1;
	while (k < quantity)
	{
		MainFileIn.open("Files/MainFile.dat");
		//cout << "Первая позиция:    " << MainFileIn.tellg() << '\n'; //для отладки
		BufferOut.open("Files/Buffer.dat");
		while (MainFileIn.read((char*)&tek1, sizeof(int))) //проверка на конец файла
		{
			//cout << "Вторая позиция:    " << MainFileIn.tellg() << '\n'; //для отладки
			tek1 = sizeof(int);
			MainFileIn.seekg(-tek1, ios_base::cur); //для отката после проверки на конец файла
			//cout << "Позиция:    " << MainFileIn.tellg() << '\n'; //для отладки
			file1Out.open("Files/file1.dat");
			file2Out.open("Files/file2.dat");
			for (unsigned long long i = 0; (i < k) && MainFileIn.read((char*)&tek1, sizeof(int)); i++)
				file1Out.write((char*)&tek1, sizeof(int));
			for (unsigned long long i = 0; (i < k) && MainFileIn.read((char*)&tek2, sizeof(int)); i++)
				file2Out.write((char*)&tek2, sizeof(int));
			file1Out.close();
			file2Out.close();
			file1In.open("Files/file1.dat");
			file2In.open("Files/file2.dat");
			file1In.read((char*)&tek1, sizeof(int));
			file2In.read((char*)&tek2, sizeof(int));
			while (!(file1In.eof() || file2In.eof()))
			{
				if (tek1 < tek2)
				{
					BufferOut.write((char*)&tek1, sizeof(int));
					file1In.read((char*)&tek1, sizeof(int));
				}
				else
				{
					BufferOut.write((char*)&tek2, sizeof(int));
					file2In.read((char*)&tek2, sizeof(int));
				}
			}
			if (file1In.eof())
			{
				BufferOut.write((char*)&tek2, sizeof(int));
				while (file2In.read((char*)&tek2, sizeof(int)))
					BufferOut.write((char*)&tek2, sizeof(int));
			}
			else
			{
				BufferOut.write((char*)&tek1, sizeof(int));
				while (file1In.read((char*)&tek1, sizeof(int)))
					BufferOut.write((char*)&tek1, sizeof(int));
			}
			file1In.close();
			file2In.close();
		}
		MainFileIn.close();
		BufferOut.close();
		MainFileOut.open("Files/MainFile.dat");
		BufferIn.open("Files/Buffer.dat");
		while (BufferIn.read((char*)&tek1, sizeof(int)))
			MainFileOut.write((char*)&tek1, sizeof(int));
		MainFileOut.close();
		BufferIn.close();
		k *= 2;
	}
	MainFileIn.open("Files/MainFile.dat");
	cout << "Отсортированный файл:\n";
	while (MainFileIn.read((char*)&tek1, sizeof(int)))
		cout << tek1 << '\n';
	MainFileIn.close();
	return 0;
}