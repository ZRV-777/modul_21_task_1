#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct salary
{
    string name = "Coworker";
    string issue_date = "dd.mm.yyyy";
    double salary = 0;
};

void list_salary(ifstream& file_out, salary& company)
{
    int len_name;
    int len_date;
    file_out.read((char*)&len_name, sizeof(len_name));
    company.name.resize(len_name);
    file_out.read((char*)company.name.c_str(), len_name);
    file_out.read((char*)&len_date, sizeof(len_date));
    company.issue_date.resize(len_date);
    file_out.read((char*)company.issue_date.c_str(), len_date);
    file_out.read((char*)&company.salary, sizeof(company.salary));
}

void add_salary(ofstream& file_in, salary& company)
{

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
        list_salary(file_out, company);
        while(file_out.eof())
        {
            cout << company.name << " " << company.issue_date << " " << company.salary << endl;
        }
        file_out.close();
    }
    else if (command == "add")
    {
        ofstream file_in ("salary.txt", ios::app);

        file_in.close();
    }
    else
    {
        cerr << "Unknown command!" << endl;
    }
}
