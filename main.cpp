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
    file_out.read((char*)&len_name, sizeof(len_name));
    company.name.resize(len_name);
    file_out.read((char*)company.name.c_str(), len_name);

    int len_date;
    file_out.read((char*)&len_date, sizeof(len_date));
    company.issue_date.resize(len_date);
    file_out.read((char*)company.issue_date.c_str(), len_date);

    file_out.read((char*)&company.salary, sizeof(company.salary));
}

void add_salary(ofstream& file_in, salary& company)
{
    int len_name = company.name.length();
    file_in.write((char*)&len_name, sizeof(len_name));
    file_in.write(company.name.c_str(), len_name);

    int len_date = company.issue_date.length();
    file_in.write((char*)&len_date, sizeof(len_date));
    file_in.write(company.issue_date.c_str(), len_date);

    file_in.write((char*)&company.salary, sizeof(company.salary));
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
        char is_next = ' ';
        ofstream file_in ("salary.txt", ios::app);

        cout << "Enter name: ";
        cin >> company.name;

        cout << "Enter date (dd.mm.yyyy): ";
        cin >> company.issue_date;

        cout << "Enter salary: ";
        cin >> company.salary;

        add_salary(file_in, company);
        file_in.close();
    }
    else
    {
        cerr << "Unknown command!" << endl;
    }
}
