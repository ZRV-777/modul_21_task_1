#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct salary
{
    string first_name = "unknown";
    string last_name = "unknown";
    string issue_date = "dd.mm.yyyy";
    long double salary = 0;
};

bool date_validation (string& date)
{
    int dot_position = 0;
    int day, month, year;

    //day
    if (date[1] == '.')
    {
        day = stoi(date.substr(0,1));
        dot_position = 1;
    }
    else if (date[2] == '.')
    {
        day = stoi(date.substr(0,2));
        dot_position = 2;
    }
    else return false;

    //month
    if (date[dot_position + 2] == '.')
    {
        month = stoi(date.substr(dot_position + 1, 1));
        dot_position += 2;
    }
    else if (date[dot_position + 3] == '.')
    {
        month = stoi(date.substr(dot_position + 1, 2));
        dot_position += 3;
    }
    else return false;

    //year
    year = stoi(date.substr(dot_position + 1, 4));

    //check validation
    if (!(year > 0 && year < 9999))
        return false;
    if (!(month >= 1 && month <= 12))
        return false;
    if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day >= 1 && day <= 31))
        return true;
    if((month == 4 || month == 6 || month == 9 || month == 11) && (day >= 1 && day <= 30))
        return true;
    if (((year % 4 == 0) && !(year % 100 == 0)) || (year % 400 == 0))
        return (day >= 1 && day <= 29);
    else
        return (day >= 1 && day <= 28);
}

void list_salary(ifstream& file_out, salary& company)
{
    company = {"", "", "", 0.0};
    file_out >> company.first_name;
    file_out >> company.last_name;
    file_out >> company.issue_date;
    file_out >> company.salary;
}

void add_salary(ofstream& file_in, salary& company)
{
    file_in << company.first_name << " ";
    file_in << company.last_name << " ";
    file_in << company.issue_date << " ";
    file_in << company.salary << endl;
}

int main()
{
    string command = " ";
    string date = " ";
    cout << "Input command (list or add): ";
    cin >> command;

    salary company;

    while (command != "exit")
    {
        if (command == "list")
        {
            ifstream file_out ("salary.txt");
            while(!file_out.eof())
            {
                list_salary(file_out, company);
                if (company.first_name != " ")
                {
                    cout << endl << company.first_name << " " << company.last_name << " " << company.issue_date << " " << company.salary << endl;
                }
            }
            file_out.close();
        }
        else if (command == "add")
        {
            ofstream file_in ("salary.txt", ios::app);
            if (!file_in.is_open())
            {
                cerr << "Error! File is not open!";
                return 1;
            }

            file_in.setf(ios::fixed);
            file_in.precision(2);

            cout << "Enter first name: ";
            cin >> company.first_name;

            cout << "Enter last name: ";
            cin >> company.last_name;

            while (!(date_validation(date)))
            {
                cout << "Enter date (dd.mm.yyyy): ";
                cin >> date;
                if (!date_validation(date))
                {
                    cerr << "Incorrect date! Try again!" << endl;
                }
            }
            company.issue_date = date;

            cout << "Enter salary: ";
            cin >> company.salary;

            add_salary(file_in, company);
            file_in.close();
        }
        else
        {
            cerr << "Unknown command!" << endl;
        }

        cout << endl << "Do you want to continue? (add/list/exit): ";
        cin >> command;
    }
}