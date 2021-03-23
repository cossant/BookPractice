#include <iostream>
#include <fstream>
using namespace std;

class person
{
private:
	char info[100];
public:
	person() 
	{
		
	}
	void fill()
	{
		cout << "Введите данные нового сотрудника в формате <Имя> <Фамилия> <должность> <личный код>\n";
		cin.ignore(); //Полумера. Вызывает игноррирование первого символа
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.getline(info, 100);
		
	}

	/*~person()
	{
		delete [] info;
	}*/

	char* get_info()
	{
		return info;
	}
};

ofstream& operator << (ofstream& stream, person& per)
{
	stream.write(reinterpret_cast<char*>(&per), sizeof(per));
	return stream;
}

ifstream& operator >> (ifstream& stream,person& per)
{
	stream.read(reinterpret_cast<char*>(&per), sizeof(per));
	return stream;
}

bool answ_is_yes()
{
	char answ;
	cin >> answ;
	if (answ == 'Y') return true;
	else return false;
}

int main()
{

	setlocale(LC_CTYPE, "Russian");



	ofstream * workFile = new ofstream();
	workFile->open("persSvgs.dat",ios::binary);



	if (workFile->fail())
	{
		cout << "Ошибка при открытии/создании файла.";
		return (-1);
	}
	do
	{
		person* curr_pers = new person();
		curr_pers->fill();
		*workFile << *curr_pers;
		delete curr_pers;
		cout << "Требуется задать нового сотрудника? Y/N\n";
	} while (answ_is_yes());
	workFile->close();

	ifstream iFile("persSvgs.dat", ios::binary);
	while (!iFile.eof())
	{
		person* outpers = new person();
		iFile >> *outpers;
		if (!iFile.eof())
			cout << "Считан сотрудник " << outpers->get_info() << endl;
		delete outpers;
	}
}