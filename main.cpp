#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct salary
{
    string name = "Coworker";
    string birth_date = "dd.mm.yyyy";
    double salary = 0;
};

void list_salary(ifstream& file_out, salary& company)
{
    int len;
    file_out.read((char*)&len, sizeof(len));
    company.name.resize(len);
    file_out.read((char*)company.name.c_str(), len);
    file_out.read((char*)company.birth_date.c_str(), len);
    file_out.read((char*)&company.salary, sizeof(company.salary));
}

int main()
{
    string command = " ";
    cout << "Input command (list or add): ";
    cin >> command;

    salary company = {};

    if (command == "list")
    {
        ifstream file_out ("salary.txt");
        for (int i = 0; !file_out.eof(); i++)
        {
            list_salary(file_out, company);
        }
    }

    for (int i = 0; i < sizeof(company); i++);
    {
        cout << company.name  << company.birth_date << company.salary << endl;
    }
}
