#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include "mobile_phone.h"
#include "human.h"
#include "weights.h"
#include "door.h"
#include "room.h"

class Vector
{
    unsigned int size = 0; // количество действительно присутствующих элементов в контейнере
    unsigned int capacity = 10; // ёмкость (вместительность, запас памяти)
    int* data = nullptr; // указатель на динамический массив целых чисел

public:
    Vector() : Vector(10)
    {
        // cout << "C-TOR WITHOUT PARAMS!\n";
    }

    Vector(unsigned int capacity)
    {
        if (capacity < 10)
        {
            capacity = 10;
        }
        this->capacity = capacity;
        data = new int[capacity];
        // cout << "C-TOR WITH PARAMS!\n";
    }

    ~Vector()
    {
        // cout << "DESTRUCTOR!\n";
        if (data != nullptr)
        {
            delete[] data;
            data = nullptr;
        }
    }

private:
    void EnsureCapacity()
    {
        if (size < capacity)
        {
            return;
        }

        capacity *= 2;

        int* temp = new int[capacity];
        for (int i = 0; i < size; i++)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }

public:
    void PushBack(int value)
    {
        EnsureCapacity(); // проверка, хватит ли места для нового элемента
        data[size] = value;
        size++;
        // cout << capacity << "\n";
    }

    void PushFront(int value)
    {
        EnsureCapacity();
        for (int i = size; i > 0; i--)
        {
            data[i] = data[i - 1];
        }
        data[0] = value;
        size++;
    }

    void Clear()
    {
        size = 0;
    }

    bool IsEmpty() const
    {
        return size == 0;
    }

    void Print() const
    {
        if (IsEmpty())
        {
            cout << "Vector is empty.\n";
            return;
        }

        for (int i = 0; i < size; i++)
        {
            cout << data[i] << " ";
        }
        cout << "\n";
    }

    unsigned int GetSize() const
    {
        return size;
    }

    unsigned int GetCapacity() const
    {
        return capacity;
    }

    void Insert(int value, unsigned int index)
    {
        if (index > size)
        {
            cout << "Error\n";
            return;
        }

        EnsureCapacity();

        for (int i = size; i > index; i--)
        {
            data[i] = data[i - 1];
        }
        data[index] = value;
        size++;
    }

    void RemoveByIndex(unsigned int index)
    {
        if (index >= size)
        {
            cout << "Error\n";
            return;
        }

        for (int i = index; i < size - 1; i++)
        {
            data[i] = data[i + 1];
        }
        size--;
    }

    void RemoveByValue(int value)
    {
        int index = 0;
        while (index < size)
        {
            if (data[index] == value)
            {
                RemoveByIndex(index);
            }
            else
            {
                index++;
            }
        }
    }

    void PopFront()
    {
        if (size == 0)
        {
            cout << "Error\n";
            return;
        }

        for (int i = 0; i < size - 1; i++)
        {
            data[i] = data[i + 1];
        }
        size--;
    }

    void PopBack()
    {
        if (size == 0)
        {
            cout << "Error\n";
            return;
        }

        size--;
    }

    Vector(const Vector& other)
    {
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        for (unsigned int i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
    }

    int LastIndexOf(int value) const
    {
        for (int i = size - 1; i >= 0; --i)
        {
            if (data[i] == value)
            {
                return i;
            }
        }
        return -1;
    }

    void SortDesc()
    {
        for (unsigned int i = 0; i < size - 1; ++i)
        {
            for (unsigned int j = 0; j < size - i - 1; ++j)
            {
                if (data[j] < data[j + 1])
                {
                    int temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }

    void Shuffle()
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = size - 1; i > 0; --i)
        {
            int j = rand() % (i + 1);
            swap(data[i], data[j]);
        }
    }

    void RandomFill()
    {
        std::srand(static_cast<unsigned int>(time(nullptr)));
        for (unsigned int i = 0; i < size; ++i)
        {
            data[i] = rand();
        }
    }

    int GetElementAt(unsigned int index) const
    {
        if (index < size)
        {
            return data[index];
        }
        else
        {
            cout << "out of bounds\n";
            return 0;
        }
    }

    bool IsEmpty(int size) const
    {
        return size == 0;
    }

    bool IsFull() const
    {
        return size == capacity;
    }

    bool Contains(int value) const
    {
        return LastIndexOf(value) != -1;
    }

    int Peek() const
    {
        if (!IsEmpty())
        {
            return data[size - 1];
        }
        else
        {
            cout << "Error\n";
            return 0;
        }
    }


    bool operator==(const Vector& other) const
    {
        if (size != other.size)
        {
            return false;
        }

        for (unsigned int i = 0; i < size; ++i)
        {
            if (data[i] != other.data[i])
            {
                return false;
            }
        }

        return true;
    }

    friend ostream& operator<<(ostream& cout, const Vector& vec)
    {
        for (unsigned int i = 0; i < vec.size; ++i)
        {
            cout << vec.data[i] << " ";
        }
        return cout;
    }

    friend istream& operator>>(istream& cin, Vector& vec)
    {
        for (unsigned int i = 0; i < vec.size; ++i)
        {
            cin >> vec.data[i];
        }
        return cin;
    }
};
class Stack
{
private:
    Vector vector;

public:
    void Clear()
    {
        vector.Clear();
    }

    bool IsEmpty() const
    {
        return vector.IsEmpty();
    }

    bool IsFull() const
    {
        return vector.IsFull();
    }

    int GetCount() const
    {
        return vector.GetSize();
    }

    void Push(int value)
    {
        if (!IsFull())
        {
            vector.PushBack(value);
        }
        else
        {
            cout << "overflow!\n";
        }
    }

    int Pop()
    {
        if (!IsEmpty())
        {
            int top_element = vector.Peek();
            vector.PopBack();
            return top_element;
        }
        else
        {
            cout << "empty\n";
            return 0;
        }
    }

    bool Contains(int value) const
    {
        return vector.Contains(value);
    }

    int Peek() const
    {
        return vector.Peek();
    }
};


/// <summary>
/// class Student
/// </summary>
class Student {
private:

    static int students_sum;

    string name;
    string surname;
    string fathname;
    string homeadress;
    string phone_number;

    int* hometask_rates = nullptr;
    int hometask_rates_count = 0;

    int* practask_rates = nullptr;
    int practask_rates_count = 0;

    int* examtask_rates = nullptr;
    int examtask_rates_count = 0;

public:
    /// <summary>
    /// а method that allows you to change a student's name
    /// </summary>
    /// <param name="name">some new value for student name</param>
    void SetName(string name)
    {
        this->name = name;
    }
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string GetName() const
    {
        return name;
    }
    /// <summary>
    /// а method that allows you to change a student's surname
    /// </summary>
    /// <param name="surname">some new value for student surname</param>
    void SetSurname(string surname)
    {
        this->surname = surname;
    }
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string GetSurname() const
    {
        return surname;
    }
    /// <summary>
    /// а method that allows you to change a student's father`s name
    /// </summary>
    /// <param name="fathname">some new value for student father`s name</param>
    void SetFathname(string fathname)
    {
        this->fathname = fathname;
    }
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string GetFathname() const
    {
        return fathname;
    }
    /// <summary>
    /// а method that allows you to change a student`s home adress
    /// </summary>
    /// <param name="homeadress">some new value for student home adress</param>
    void SetHomeAdress(string homeadress)
    {
        this->homeadress = homeadress;
    }
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string GetHomeAdress() const
    {
        return homeadress;
    }
    /// <summary>
    /// а method that allows you to change a student`s phone number
    /// </summary>
    /// <param name="phone_number">some new value for student phone number</param>
    void SetPhoneNumber(string phone_number)
    {
        this->phone_number = phone_number;
    }
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string GetPhoneNumber() const
    {
        return phone_number;
    }

    Student()
    {
        SetName("Alexey");
        SetSurname("Kosmolenko");
        SetFathname("Denisovich");
        SetHomeAdress("Blicker street 325a");  
        SetPhoneNumber("+1439430493049");
    } 
    
    Student(string name) : Student("Alexey", "Kosmolenko","Denisovich","Blicker street 325a","+1 439 4930 49"){}

    Student(string name, string surname, string fathname, string home_adress, string phone_number) {
        
        SetName(name);
        SetSurname(surname);
        SetFathname(fathname);
        SetHomeAdress(home_adress);
        SetPhoneNumber(phone_number);
    }
    /// <summary>
    /// Defines a destructor for the class Student
    /// </summary>
    ~Student() {
        if (hometask_rates != nullptr)
        {
            delete[] hometask_rates;
            hometask_rates = nullptr;
        }
        if (practask_rates != nullptr)
        {
            delete[] practask_rates;
            practask_rates = nullptr;
        }
        if (examtask_rates != nullptr)
        {
            delete[] examtask_rates;
            examtask_rates = nullptr;
        }

    }
    /// <summary>
    /// This method involves adding a grade to the student's homework grade list, and the grade should be between 1 and 12 points 
    /// </summary>
    /// <param name="rate">value from 1 to 12</param>
    void AddHometaskRate(int rate)
    {
        if (rate < 1 || rate > 12)
        {
            cout << "No\n";
            throw "error";
        }
        if (hometask_rates_count == 0)
        {
            hometask_rates = new int[1];
            hometask_rates[0] = rate;
        }
        else
        {
            int* temp = new int[hometask_rates_count + 1];
            for (int i = 0; i < hometask_rates_count; i++) {
                temp[i] = hometask_rates[i];
                temp[i + 1] = rate;
            }
            delete[] hometask_rates;
            hometask_rates = temp;
        }
        hometask_rates_count++;
    }
    int* GetHometaskRates() const
    {
        return hometask_rates;
    }
    int GetHometaskRatesCount() const
    {
        return hometask_rates_count;
    }
    /// <summary>
    /// show grades for the student`s hometask
    /// </summary>
    void PrintHometaskRates()
    {
        for (int i = 0; i < hometask_rates_count; i++) {
            cout << i + 1 << hometask_rates[i] << "\n";
        }
    }
    /// <summary>
    /// This method involves adding a grade to the student's practice grade list, and the grade should be between 1 and 12 points 
    /// </summary>
    /// <param name="rate">value from 1 to 12</param>
    void AddPractaskRate(int rate)
    {
        if (rate < 1 || rate > 12)
        {
            cout << "No\n";
            throw "error";
        }
        if (practask_rates_count == 0)
        {
            practask_rates = new int[1];
            practask_rates[0] = rate;
        }
        else
        {
            int* temp = new int[practask_rates_count + 1];
            for (int i = 0; i < practask_rates_count; i++) {
                temp[i] = practask_rates[i];
                temp[i + 1] = rate;
            }
            delete[] practask_rates;
            practask_rates = temp;
        }
        practask_rates_count++;
    }
    int* GetPractaskRates() const
    {
        return practask_rates;
    }
    int GetPractaskRatesCount() const
    {
        return practask_rates_count;
    }
    /// <summary>
    /// show grades for the student`s practice
    /// </summary>
    void PrintPractaskRates()
    {
        for (int i = 0; i < practask_rates_count; i++) {
            cout << i + 1 << practask_rates[i] << "\n";
        }
    }
    /// <summary>
    /// This method involves adding a grade to the student's exam grade list, and the grade should be between 1 and 12 points 
    /// </summary>
    /// <param name="rate">value from 1 to 12</param>
    void AddExamtaskRate(int rate)
    {
        if (rate < 1 || rate > 12)
        {
            cout << "No\n";
            throw "error";
        }
        if (examtask_rates_count == 0)
        {
            examtask_rates = new int[1];
            examtask_rates[0] = rate;
        }
        else
        {
            int* temp = new int[examtask_rates_count + 1];
            for (int i = 0; i < examtask_rates_count; i++) {
                temp[i] = examtask_rates[i];
                temp[i + 1] = rate;
            }
            delete[] examtask_rates;
            examtask_rates = temp;
        }
        examtask_rates_count++;
    }
    int* GetExamtaskRates() const
    {
        return examtask_rates;
    }
    int GetExamtaskRatesCount() const
    {
        return examtask_rates_count;
    }
    /// <summary>
    /// show grades for the student`s exam`s
    /// </summary>
    void PrintExamtaskRates()
    {
        for (int i = 0; i < examtask_rates_count; i++) {
            cout << i + 1 << examtask_rates[i] << "\n";
        }
    }
    void PrintStud()
    {
        cout << name << " " << surname;
    }
};



int Student::students_sum = 0;

bool operator == (const Student& left, const Student& right)
{
    return left.GetHometaskRatesCount() == right.GetHometaskRatesCount();
}

bool operator != (const Student& left, const Student& right)
{
    return left.GetHometaskRatesCount() != right.GetHometaskRatesCount();
}

bool operator > (const Student& left, const Student& right)
{
    return left.GetHometaskRatesCount() > right.GetHometaskRatesCount();
}

bool operator < (const Student& left, const Student& right)
{
    return left.GetHometaskRatesCount() < right.GetHometaskRatesCount();
}

istream& operator >> (istream& cin, Student& s)
{
    string name;
    cout << "Set student`s name:";
    cin >> name;
    s.SetName(name);

    string surname; 
    cout << "Set student`s surname:";
    cin >> surname;
    s.SetSurname(surname);
    return cin;
}

ostream& operator << (ostream& cout, const Student& s)
{
    cout << "Student name: " << s.GetName() << "\n";
    cout << "Student surname: " << s.GetSurname() << "\n";
    return cout;
}


/// <summary>
/// class name DateTime
/// </summary>
class DateTime
{
private:
    int day;
    int month;
    int year;

public:
    /// <summary>
    /// а method that allows you to set day 
    /// </summary>
    /// <param name="day">value from 1 to 31</param> 
    void SetDay(int day)
    {
        if (day >= 1 && day <= 31)
        {
            this->day = day;
        }
        else
        {
            cout << "No\n";
        }
    }
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    int GetDay() const
    {
        return day;
    }
    /// <summary>
    /// a method that allows you to set month
    /// </summary>
    /// <param name="month">value from 1 to 12</param>
    void SetMonth(int month)
    {
        if (month >= 1 && month <= 12)
        {
            this->month = month;
        }
        else
        {
            cout << "No\n";
        }
    }
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    int GetMonth() const
    {
        return month;
    }
    /// <summary>
    /// a method that allows you to set a year
    /// </summary>
    /// <param name="year"></param>
    void SetYear(int year)
    {
        this->year = year;
    }
    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    int GetYear() const
    {
        return year;
    }
    void PrintDate()
    {
        cout << day << month << year;
    }

    DateTime(int day) : DateTime(day, month, year){}

    DateTime(int day, int month, int year) {
        SetDay(day);
        SetMonth(month);
        SetYear(year);
    }
    
};

istream& operator>>(istream& cin, DateTime& dt) //dt - object
{
    int day, month, year;
    cout << "Day: \n";
    cin >> day;
    dt.SetDay(day);
    cout << "Month: \n";
    cin >> month;
    dt.SetMonth(month);
    cout << "Year: \n";
    cin >> year;
    dt.SetYear(year);
    return cin;
}

ostream& operator<<(ostream& cout, DateTime& dt)
{
    dt.PrintDate();
    return cout;
}

class Group
{
    static int group_sum;

    
    Student** students = nullptr;
    int student_count = 0;
    string group_name;
    string specializ;
    int course;
    int date;
    int start_day;
    int start_month;
    int start_year;

public:
    Group()
    {
        SetGroupName(group_name);
        SetSpecializ(specializ);
        SetCourseNumber(course);
    }

    Group(const Group& field) //конструктор копирования
    {
        this->student_count = field.student_count;
        this->group_name = field.group_name;
        this->specializ = field.specializ;
        this->course = field.course;
        this->students = new Student * [this->student_count];
        for(int i = 0; i < this->student_count; i++)
        {
            this->students[i] = field.students[i];
        }
    }

    ~Group()
    {
        if (students != nullptr)
        {
            for (int i = 0; i < student_count; i++)
            {
                delete students[i];
            }
            delete[] students;
        }
    }
    friend istream& operator>>(istream& input, Group& group);
    friend ostream& operator<<(ostream& output, const Group& group);
    Group& operator=(const Group& other);
    void SetStudentCount(int student_count)
    {
        if (student_count > 0)
        {
            this->student_count = student_count;
        }
        else
        {
            cout << "No\n";
        }
    }
    int GetStudentCount() const
    {
        return student_count;
    }
    
    void SetGroupName(string group_name)
    {
        this->group_name = group_name;
    }
    string GetGroupName() const
    {
        return group_name;
    }

    void SetSpecializ(string specializ)
    {
        this->specializ = specializ;
    }
    string GetSpecializ() const
    {
        return specializ;
    }

    void SetCourseNumber(int course)
    {
        this->course = course;
    }
    int GetCourseNumber() const
    {
        return course;
    }

    int StudentCount() const
    {
        return student_count;
    }

    Student GetStudent(int index) const
    {
        if (index < student_count)
        {
            return *students[index];
        }
        else
        {
            cout << "No\n";
        }
    }

    void AddStudent(const Student& new_student)
    {
        Student** temp = new Student * [student_count + 1];
        for (int i = 0; i < student_count; i++)
        {
            temp[i] = new Student(*students[i]);
        }
        temp[student_count] = new Student(new_student);
        delete[] students;
        students = temp;
        student_count++;
        
        /*if (student_count < 16)
        {
            cout << "To many students!\n";
            throw "Error";
        }*/
    }

    void RemoveStudent()
    {
        if (student_count == 0)
        {
            
            cout << "Where are students?\n";
            return;
        }
        int minidex = 0;
        int lowaverage = students[0]->GetHometaskRatesCount();
        for (int i = 1; i < student_count; i++)
        {
            int nowaverage = students[i]->GetHometaskRatesCount();
            if (nowaverage < lowaverage)
            {
                lowaverage = nowaverage;
                minidex = i;
            }
        }
        for (int i = minidex; i < student_count - 1; i++)
        {
            students[i] = students[i + 1];
        }
        student_count--;
    }

    void MergeWithGroup(Group& another_group)
    {
        for (int i = 0; i < another_group.StudentCount(); i++)
        {
            this->AddStudent(another_group.GetStudent(i));
        }

        int k = another_group.StudentCount();
        for (int i = 0; i < k; i++)
        {
            another_group.RemoveStudent();
        }
    }
        
    void GoStudent(Group& another, int index)
    {
        if (index >= 0 && index < student_count)
        {
            another.AddStudent(*students[index]);
            for (int i = index; i < student_count - 1; i++)
            {
                students[i] = students[i + 1];
            }
            student_count--;
        }
    }
    void SetStartStudyDate(int day, int month, int year) {
        start_day = day;
        start_month = month;
        start_year = year;
    }
    string GetStartStudyDate() const {

        return "01.09.2022";
    }
    operator string() const {
        ostringstream cout;

        cout << "Группа " << GetGroupName() << ", " << GetCourseNumber() << " курс, " << "дата начала обучения " << GetStartStudyDate() << ".";
        return cout.str();
    }
    
};


istream& operator>>(istream& cin, Group& g) {
    string group_name, specializ;
    int course, student_count;
    cout << "Enter name of group: ";
    cin >> g.group_name;

    cout << "Enter specialization: ";
    cin >> g.specializ;

    cout << "Enter Course Number: ";
    cin >> g.course;

    cout << "Enter Student Count: ";
    cin >> g.student_count;

    return cin;
}

ostream& operator<<(ostream& cout, const Group& g) {

    cout << "Group Name: " << g.group_name << "\n";
    cout << "Specialization: " << g.specializ << "\n";
    cout << "Course: " << g.course << "\n";
    cout << "Student Count: " << g.student_count << "\n";

    for (int i = 0; i < g.student_count; i++) {
        cout << "Student " << i + 1 << ":\n" << *(g.students[i]) << "\n";
    }

    return cout;
}


int Group::group_sum = 0;

bool operator == (const Group& left, const Group& right)
{
    return left.GetStudentCount() == right.GetStudentCount();
}

bool operator != (const Group& left, const Group& right)
{
    return left.GetStudentCount() != right.GetStudentCount();
}

Group& Group::operator=(const Group& other) {
    if (this != &other) {
        if (students != nullptr) {
            for (int i = 0; i < student_count; i++) {
                delete students[i];
            }
            delete[] students;
        }

        student_count = other.student_count;
        group_name = other.group_name;
        specializ = other.specializ;
        course = other.course;

        students = new Student * [student_count];
        for (int i = 0; i < student_count; i++) {
            students[i] = new Student(*other.students[i]);
        }
    }
    return *this;
}

int main()
{
    /*Student s("Alex");
    Group g;
    g.SetGroupName("KND-221");
    g.SetCourseNumber(2);
    g.SetStartStudyDate(1, 9, 2022);
    g.AddStudent(s);

    string info = static_cast<string>(g);
    cout << info << "\n";*/

    /*Group group1;
    cout << "Group 1 (default constructor):\n" << group1 << "\n";

    Group group2(group1);
    cout << "Group 2 (copy constructor):\n" << group2 << "\n";*/

    /*Vector v;

    for (int i = 0; i < 10000; i++)
    {
        v.PushBack(rand() % 100);
        Sleep(15);
    }

    cout << "Size: " << v.GetSize();
    cout << "Capacity: " << v.GetCapacity();

    v.Insert(48, 3);
    v.Print();

    v.RemoveByIndex(2);
    v.Print();

    v.RemoveByValue(48);
    v.Print();

    v.PopFront();
    v.Print();

    v.PopBack();
    v.Print();

    return 0;*/


   // /*DateTime dt;*/
   // cout << "Enter date: \n";
   ///* cin >> dt;*/

   // Group g;
   // cout << "Enter group: \n";
   // cin >> g;

    /*g.SetGroupName("Group B");
    g.SetSpecializ("Computer Science");
    g.SetCourseNumber(2);
    g.SetStudentCount(3);*/
 
    //string UserName = "anon";

    /*Student* student1 = new Student(" Student1");
    Student* student2 = new Student(" Student2");

    delete student1;
    delete student2;*/


    /*s.AddHometaskRate(12);
    s.AddHometaskRate(6);
    s.AddHometaskRate(1);
    s.AddHometaskRate(8);
    s.PrintHometaskRates();

    s.AddPractaskRate(12);
    s.AddPractaskRate(5);
    s.AddPractaskRate(3);
    s.AddPractaskRate(8);
    s.PrintPractaskRates();*/

    /*Group g;

    g.SetGroupName("Group");
    g.SetSpecializ("Programmers");
    g.SetCourseNumber(3);

    for (int i = 0; i < 15; i++)
    {
        Student s("Vasylij");

        for (int ht = 0; ht < 5; ht++)
            s.AddHometaskRate(rand() % 12 + 1);

        g.AddStudent(s);

    }
    Group g1;

    g1.SetGroupName("Group1");
    g1.SetSpecializ("Designers");
    g1.SetCourseNumber(3);

    for (int i = 0; i < 15; i++)
    {
        Student s("Sasha");

        for (int ht = 0; ht < 5; ht++)
            s.AddHometaskRate(rand() % 12 + 1);

        g.AddStudent(s);

    }
    g.MergeWithGroup(g1);*/
}




