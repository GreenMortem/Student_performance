#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <iomanip>

using namespace std;

char a[100];
int x = 0;
int s[5];

class Student {
private:
    int Group;
    int Sr1;
    int Sr2;
    string FIO;
public:
    Student() {
        Group = 0;
        Sr1 = 0;
        Sr2 = 0;
        FIO = "";
    }

    int GetGroup() { return Group; }
    int GetSr1() { return Sr1; }
    int GetSr2() { return Sr2; }
    string GetFIO() { return FIO; }

    void set() {
        while (true) {
            try {
                cout << "Группа: ";
                cin >> Group;
                if (cin.fail()) { throw 1.0; }
                cout << "ФИО студента (С большой буквы через пробел): ";
                getline(cin.ignore(33333, '\n'), FIO);
                if (!regex_match(FIO, regex("[А-Я][а-я]+ [А-Я][а-я]+ [А-Я][а-я]+"))) { throw 1; }
                cout << "Экзаменационные оценки за 1 семестр (Введите 5 оценок через пробел): ";
                for (int i = 0; i < 5; i++)
                    cin >> s[i];
                for (int i = 0; i < 5; i++)
                    Sr1 = Sr1 + s[i];
                Sr1 = Sr1 / 5;
                if (cin.fail()) { throw 1.0; }
                cout << "Экзаменационные оценки за 2 семестр (Введите 5 оценок через пробел): ";
                for (int i = 0; i < 5; i++)
                    cin >> s[i];
                for (int i = 0; i < 5; i++)
                    Sr2 = Sr2 + s[i];
                Sr2 = Sr2 / 5;
                if (cin.fail()) { throw 1.0; }
                break;
            }
            catch (double) {
                cerr << "Некорректный ввод..." << endl;
                cin.clear();
                cin.ignore(33333, '\n');
            }
            catch (int) {
                cerr << "Некорректный ввод..." << endl;
            }
        }
    }
    void SetGroup(int G) { Group = G; }
    void SetSr1(int S1) { Sr1 = S1; }
    void SetSr2(int S2) { Sr2 = S2; }
    void SetFIO(string F) { FIO = F; }
};
void CheckFile(Student stu[]) {
    ifstream FileIn("D:\\rab\\Успеваемость студента за год.txt");
    if (FileIn) {
        for (int i = 0; FileIn.getline(a, 100); i++) {
            char* cc1 = strtok(a, ";");
            while (cc1) {
                stu[i].SetGroup(atoi(cc1));
                cc1 = strtok(NULL, ";");
                stu[i].SetFIO(cc1);
                cc1 = strtok(NULL, ";");
                stu[i].SetSr1(atoi(cc1));
                cc1 = strtok(NULL, ";");
                stu[i].SetSr2(atoi(cc1));
                cc1 = strtok(NULL, ";");
            }
            x++;
        }
    }
    else {
        cout << "Нужного файла нет, создайте его." << endl;
    }
    FileIn.close();
}
void CreateFile(Student stu[]) {
    ofstream FileOut("D:\\rab\\Успеваемость студента за год.txt");
    FileOut.close();
    for (int i = 0; i < x; i++) {
        stu[i].SetGroup(NULL);
        stu[i].SetFIO("");
        stu[i].SetSr1(NULL);
        stu[i].SetSr2(NULL);
    }
    x = 0;
    cout << "===================================================================================================" << endl;
}
void AddStudents(Student stu[]) {
    cout << "Введите данные студента:" << endl;
    stu[x].set();
    ofstream FileOut("D:\\rab\\Успеваемость студента за год.txt");
    for (int i = 0; i < x; i++)
        FileOut << stu[i].GetGroup() << ";" << stu[i].GetFIO() << ";" << stu[i].GetSr1() << ";" << stu[i].GetSr2() << ";" << endl;
    FileOut.close();
    x++;
    cout << "Данные введены!" << endl;
    cout << "===================================================================================================" << endl;
}
void LookStudents(Student stu[]) {
    if (x == 0) {
        cout << "Студенты не записанны!" << endl;
    }
    else {
        cout << setw(10) << left << "Группа" << setw(50) << "ФИО студента" << setw(10) << "1 семестр" << setw(10) << "2 семестр" << endl;
        for (int i = 0; i < x; i++)
            cout << setw(10) << left << stu[i].GetGroup() << setw(50) << stu[i].GetFIO() << setw(10) << stu[i].GetSr1() << setw(10) << stu[i].GetSr2() << endl;
        cout << "===================================================================================================" << endl;
    }
}
void CheckSpisok(Student stu[]) {
    cout << "Список студетов, у которых средний балл за 2 семестр меньше чем за 1 семестр:" << endl
        << "---------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < x; i++) {
        if (stu[i].GetSr1() > stu[i].GetSr2())
            cout << left << setw(40) << stu[i].GetGroup() << stu[i].GetFIO() << right << endl;
    }
    cout << "===================================================================================================" << endl;
}
void CreateSpisok(Student stu[]) {
    ofstream FileOut("D:\\rab\\Успеваемость студента за год, ухудшение.txt");
    for (int i = 0; i < x; i++) {
        if (stu[i].GetSr1() > stu[i].GetSr2())
            FileOut << stu[i].GetGroup() << ";" << stu[i].GetFIO() << ";" << stu[i].GetSr1() << ";" << stu[i].GetSr2() << ";" << endl;
    }
    FileOut.close();
    cout << "Файл со студентами, у которых средний результат за 2 семестр меньше чем за 1 семестр создан." << endl;
    cout << "===================================================================================================" << endl;
}
void PrintSpisok(Student stu[]) {
    system("print D:\\rab\\Успеваемость студента за год, ухудшение.txt");
    cout << "===================================================================================================" << endl;
}
void Delete(Student stu[]) {
    if (x == 0) {
        cout << "Ошибка! Файл пустой!" << endl;
    }
    else {
        int z = 0;
        int y;
        while (true) {
            cout << "Какую группу удалить?" << endl;
            cin >> y;
            if (cin.fail()) {
                cerr << "Ошибка!" << endl;
                cin.clear();
                cin.ignore(33333, '\n');
            }
            else {
                cin.ignore(33333, '\n');
                break;
            }
        }
        ofstream FileOut("D:\\rab\\Успеваемость студента за год.txt");
        for (int i = 0; i < x; i++) {
            if (stu[i].GetGroup() == y)
                z++;
            else
                FileOut << stu[i].GetGroup() << ";" << stu[i].GetFIO() << ";" << stu[i].GetSr1() << ";" << stu[i].GetSr2() << ";" << endl;

        }
        FileOut.close();
        for (int i = 0; i < x; i++) {
            stu[i].SetGroup(NULL);
            stu[i].SetFIO("");
            stu[i].SetSr1(NULL);
            stu[i].SetSr2(NULL);
        }
        x -= z;
        ifstream FileIn("D:\\rab\\Успеваемость студента за год.txt");
        for (int i = 0; i < x; i++) {
            FileIn.getline(a, 100);
            char* cc1 = strtok(a, ";");
            while (cc1) {
                stu[i].SetGroup(atoi(cc1));
                cc1 = strtok(NULL, ";");
                stu[i].SetFIO(cc1);
                cc1 = strtok(NULL, ";");
                stu[i].SetSr1(atoi(cc1));
                cc1 = strtok(NULL, ";");
                stu[i].SetSr2(atoi(cc1));
                cc1 = strtok(NULL, ";");
            }
        }
        FileIn.close();
        if (z > 0)
            cout << "Удалено!" << endl;
        else
            cout << "Не найдено!" << endl;
    }
}
void Corect(Student stu[]) {
    if (x == 0) {
        cout << "Ошибка! Файл пустой!" << endl;
    }
    else {
        int y;
        int z = 0;
        string s;
        string fio;
        while (true) {
            cout << "Группа: ";
            cin >> y;
            if (cin.fail()) {
                cerr << "Ошибка!" << endl;
                cin.clear();
                cin.ignore(33333, '\n');
            }
            else {
                cin.ignore(33333, '\n');
                break;
            }
        }
        cout << "Введите фамилию Имя Отчество: ";
        getline(cin, fio);
        for (int i = 0; i < x + 1; i++) {
            if (stu[i].GetGroup() == y && stu[i].GetFIO()._Equal(fio)) {
                cout << "Новое ФИО: ";
                getline(cin, s);
                stu[i].SetFIO(s);
                z++;
            }
        }
        if (z == 0) { cout << "Не найдено!"; }
        ofstream FileOut("D:\\rab\\Успеваемость студента за год.txt");
        for (int i = 0; i < x - 1; i++)
            FileOut << stu[i].GetGroup() << ";" << stu[i].GetFIO() << ";" << stu[i].GetSr1() << ";" << stu[i].GetSr2() << ";" << endl;
        FileOut << stu[x - 1].GetGroup() << ";" << stu[x - 1].GetFIO() << ";" << stu[x - 1].GetSr1() << ";" << stu[x - 1].GetSr2() << ";" << endl;
        FileOut.close();
        ifstream FileIn("D:\\rab\\Успеваемость студента за год.txt");
        for (int i = 0; i < x; i++) {
            char* cc1 = strtok(a, ";");
            while (cc1) {
                stu[i].SetGroup(atoi(cc1));
                cc1 = strtok(NULL, ";");
                stu[i].SetFIO(cc1);
                cc1 = strtok(NULL, ";");
                stu[i].SetSr1(atoi(cc1));
                cc1 = strtok(NULL, ";");
                stu[i].SetSr2(atoi(cc1));
                cc1 = strtok(NULL, ";");
            }

        }
        FileIn.close();
        cout << "===================================================================================================" << endl;
    }
}
int main()
{
    setlocale(0, "rus");
    system("chcp 1251");
    Student stu[30];
    CheckFile(stu);
    while (1) {
        cout << "===================================================================================================" << endl
            << "Напечатайте число, отвечающее за нужное вам действие: " << endl
            << "---------------------------------------------------------------------------------------------------" << endl
            << "1 - Создать или очистить файл." << endl
            << "2 - Добавить данные студента." << endl
            << "3 - Посмотреть данные студента." << endl
            << "4 - Вывести список студентов, у которых средний балл за 2 семестр ниже чем за 1 семестр." << endl
            << "5 - Создать файл со списком студентов, у которых средний балл за 2 семестр ниже чем за 1 семестр." << endl
            << "6 - Печать файла со списком студентов, у которых средний балл за 2 семестр ниже чем за 1 семестр." << endl
            << "7 - Удалить данные группы." << endl
            << "8 - Корректировать данные студентов." << endl
            << "0 - Выход." << endl
            << "===================================================================================================" << endl;
        int y;
        while (true) {
            cin >> y;
            if (cin.fail()) {
                cerr << "Ошибка!" << endl;
                cin.clear();
                cin.ignore(33333, '\n');
            }
            else {
                cin.ignore(33333, '\n');
                break;
            }
        }
        switch (y) {
        case 1:
            system("cls");
            CreateFile(stu);
            break;
        case 2:
            system("cls");
            AddStudents(stu);
            break;
        case 3: system("cls");
            LookStudents(stu);
            break;
        case 4: system("cls");
            CheckSpisok(stu);
            break;
        case 5: system("cls");
            CreateSpisok(stu);
            break;
        case 6: system("cls");
            PrintSpisok(stu);
            break;
        case 7: system("cls");
            Delete(stu);
            break;
        case 8: system("cls");
            Corect(stu);
            break;
        case 0:
            return 0;
        default:
            system("cls");
            cout << "Вы ничего не выбрали, введите число 0-7: " << endl;
        }
    }
}