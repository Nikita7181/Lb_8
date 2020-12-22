#include <iostream>
#include <ctime>

using std::endl;
using std::cout;
using std::cin;


template <typename InfoType> //  шаблон поля информации
struct My_list_element {
    unsigned int index;  // индекс
    InfoType info; // информация
    
    My_list_element (InfoType info) // конструктор (дял элементов)
    {
        this->index = 0;
        this->info = info;
    }
    
    ~My_list_element ()// деструктор(Для элемента)
    {
        this->index = 0;
        cout << "My_list_element destuctor";
    }
    
    InfoType GetInfo() // функция для получчения информации
    {
        return this->info;
    }
    
    void PrintInfo () // Функция для пеати
    {
      cout << this->GetInfo() << endl;
    }
    
};

template <typename ListType, unsigned int size>
struct My_list // орисание самого списка
{
    unsigned int count;
    unsigned int maxCount = size;
    
    My_list_element <ListType> ** data;
    
    My_list () // конструктор
    {
        count = 0;
        data = new My_list_element <ListType> * [maxCount];
        
        for (unsigned int i = 0; i < maxCount; i++)
        {
            data[i] = NULL;
        }
    }
    
    My_list destructor () // деструктор
    {
        count = 0;
        maxCount = 0;
        delete[] data;
    }
    
    void PrintList () // функция пеати списка
    {
        for (int i = 0; i < count; i++)
        {
            data[i]->PrintInfo();
        }
    }
    
    void  addLast (ListType value)// функция добавления в конец
    {
        if (count > (maxCount - 1)) {return; }
        data [count] = new My_list_element <ListType> (value);
        count++;
    }
    
    void addFirst (ListType value)// фугкция добавления в наало
    {
        addAtIndex (value, 1);
    }
    
    void addAtIndex(ListType value, unsigned int index)// функция доавления по индексу
    {
        if (count > (maxCount - 1) || index > count) {return; }
        if (data[index] != NULL)
        {
            for (int i = maxCount-1; i > index; i--)
            {
                data[i] = data[i-1];
            }
        }
        
        data [index] = new My_list_element <ListType> (value);
        count++;
    }
    
    int searchByValue (ListType value)// функия поиска по значению
    {
        for (int i = 0; i < count; i++)
        {
            if (data[i]->info == value) return i; //data[i] ;
        }
        
        return -1;
    }
    
    My_list_element <ListType> * getByIndex (unsigned int index)// Фугкция получчения значения по индексу
    {
        if (index > count) {return NULL;}
        
        return data[index];
    }
    
    int getCount ()// функция определения размера
    {
        return count;
    }
    
    My_list_element <ListType> * getFirst ()// Функция получения первого элемента
    {
        return this -> getByIndex(0);
    }
    
    My_list_element <ListType> * getLast ()// Функция получения последнего элемента
    {
        return this->getByIndex(this-> getCount() );
    }
    
    
    
};


struct my_time// пользовательский тип данных
{
    short int HH;
    short int MM;
    short int SS;
    
    my_time ()
    {
        HH = MM = SS = 0;
    }
    
    my_time& operator=(const my_time& tm)
    {
        HH = tm.HH;
        MM = tm.MM;
        SS = tm.SS;
        return *this;
    }
    
};



std::ostream& operator<<(std::ostream& os, const my_time& mt)// перегрузка пользовательского типа
{
    os << mt.HH << ":" << mt.MM << ":" << mt.SS;
    
    return os;
}

int main ()
{
    // конструктор работает при инициализации переменной
    int k = 0;
    int size = 0;
    int element = 0;
    std::srand(std::time(nullptr));
    My_list <int, 100> * my_test_list = new My_list <int, 100>;
    cout << "Enter the size of the list : ";
    cin >> size;
    for(int i = 0; i<size ; ++i)
    {
        cout << "enter " << "{" << i << "}" << " element:";
        cin >> element;
    my_test_list -> addLast(element);
    }
    cout << "Enter a value: ";
    cin >> element;
    cout << "index: " << my_test_list->searchByValue(element) << endl;
    cout << "Get the value by index" << endl;
    my_test_list->getByIndex(5);
    cout << "Value from the beginning: ";
    my_test_list -> getFirst();
    cout << endl;
    my_test_list-> PrintList();
    cout << "Add an item to the top of the list: ";
    cin >> element;
    my_test_list->addFirst(element);
    cout <<"Adding a value by index";
    my_test_list->addAtIndex(10, 4);
    cout << "Get the value by index" << endl;
    my_test_list->getByIndex(5);
    cout << "search for the position of the first element equal in value to the desired one" << endl;
    cout << endl;
    cout << "Value from the end: ";
    my_test_list -> getLast();
    cout << endl;
    cout << "Size: " << my_test_list->getCount() << endl;
    my_test_list->PrintList();
    my_test_list->destructor();
    my_test_list->PrintList();
   
    
    // проверка работы на пользовательском типа данных
    cout << "---------my time---------" << endl;
    
    my_time mt1, mt2;
    mt1.HH = 10;
    mt1.MM = 30;
    mt1.SS = 10;
    
    mt2.HH = 16;
    mt2.MM = 17;
    mt2.SS = 18;
    
    //cout << mt1 << endl;
    
    My_list <my_time, 5> * my_time_list = new My_list <my_time, 5>;
    my_time_list->addLast(mt1);
    my_time_list->addFirst(mt2);
    cout << "Get the value by index" << endl;
    my_test_list->getByIndex(1);
    my_time_list->addAtIndex(mt1,3);
    cout << "Value from the beginning: ";
    my_time_list->getFirst();
    cout << endl;
    cout << "Value from the end: ";
    my_time_list->getLast();
    cout << endl;
    my_time_list->PrintList();
    cout << "Size: " << my_time_list->getCount() << endl;
   my_time_list->destructor();
    return 0;
}