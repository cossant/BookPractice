#include <iostream>
#include <fstream>
using namespace std;

class person
{
private:
	char info[];
public:
	person() 
	{
		cout << "������� ������ ������ ���������� � ������� <���> <�������> <���������> <������ ���>\n";
		cin.getline(info,100);
	}

	~person()
	{
		delete info;
		delete this;
	}

	char* get_info()
	{
		return info;
	}
};

ostream& operator << (ostream& stream, person& per)
{
	stream.write(reinterpret_cast<char*>(&per), sizeof(per));
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



	ofstream workFile;
	workFile.open("persSvgs.dat");



	if (workFile.fail())
	{
		cout << "������ ��� ��������/�������� �����.";
		return (-1);
	}
	do
	{
		person* curr_pers = new person();
		workFile << curr_pers;
		workFile.close();
		delete curr_pers;
		cout << "��������� ������ ������ ����������? Y/N\n";
	} while (answ_is_yes());
}