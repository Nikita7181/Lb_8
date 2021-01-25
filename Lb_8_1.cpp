#include <iostream>
#include <ctime>

using std::endl;
using std::cout;
using std::cin;

#define SIZE 5

template <typename InfoType> //  шаблон поля информации
struct My_list_element
{
    //unsigned int index;  // индекс
    InfoType info; // информация
    
    My_list_element (InfoType info) // конструктор (дял элементов)
    {
        //this->index = 0;
        this->info = info;
    }

    My_list_element () // конструктор (дял элементов)
    {
        this->info = 0;
    }
    
    InfoType GetInfo() // функция для получчения информации
    {
        //if (this)
            return this->info;
    }
    
    void PrintInfo () // Функция для пеати
    {
      if (this)
        cout << this->info << endl;
    }

    My_list_element& operator=(const My_list_element& el)
    {
        info = el.info;
        return *this;
    }
    
};

//template <typename ListType, unsigned int size>
template <typename ListType>
struct My_list // орисание самого списка
{
    unsigned int count;
    const unsigned int maxCount = SIZE;
    
    My_list_element <ListType> * data[SIZE];
    
    My_list () // конструктор
    {
        count = 0;
        //data = new My_list_element <ListType> * [maxCount];
        
        for (unsigned int i = 0; i < maxCount; i++)
        {
            data[i] = nullptr;
        }
    }
    
    ~My_list () // деструктор
    {
        count = 0;
        //delete[] data;
    }
    
    void PrintList () // функция пеати списка
    {
        for (int i = 0; i < SIZE; i++)
        {
            if (data[i])
                data[i]->PrintInfo();
            //else
            //    std::cout << "null" << std::endl;
                
        }
    }
    
    void  addLast (ListType value)// функция добавления в конец
    {
        if (count > (maxCount - 1)) {return; }
        data [count] = new My_list_element <ListType> (value);
        count++;
    }
    
    void addAtIndex(ListType value, unsigned int index)// функция доавления по индексу
    {
        if (count > (maxCount - 1) || index > count) {return; }
        if (data[index] != nullptr)
        {
            for (int i = maxCount-1; i > index-1; i--)
            {
                data[i] = data[i-1];
            }
        }
        
        data [index] = new My_list_element <ListType> (value);
        count++;
    }
    
    My_list_element <ListType> pop_last()
    {
        for(int i = SIZE; i >= 0; i--)
        {
            if(data[i]  != nullptr)
            {
                count--;

                My_list_element <ListType> res = *data[i];
                data[i] = nullptr;
                return res;
            }
        }
        return 0;
    }

    My_list_element <ListType> pop_first()
    {
        My_list_element <ListType> res;
        for(int i = 0; i < SIZE; i++)
        {
            if(data[i]  != nullptr)
            {
                count--;

                res = *data[i];
                data[i] = nullptr;
                break;
            }
        }

        for (int i = 0; i < SIZE - 1; i++)
        {
            data[i] = data[i+1];
        }
        return res;
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
        if (index > count) {std::cout << "Index out of range " << std::endl; return nullptr;}
        
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
        return this->getByIndex( getCount ()-1);
    }
    
    
    
};

std::ostream & operator<< (std::ostream& os , const My_list_element<int> & el)
{
    os << el.info;
   return os;
}

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
    My_list <int> * my_test_list = new My_list <int>;
    //cout << "Enter the size of the list : ";
    //cin >> size;
    for(int i = 0; i<SIZE ; ++i)
    {
        cout << "enter " << "{" << i << "}" << " element:";
        cin >> element;
    my_test_list -> addLast(element);
    }
    std::cout << "Search by Value" << std::endl;
    std::cout << "Enter a value : ";
    int value = 0;
    std::cin>>value;
    int position = my_test_list->searchByValue (value);
    if (position != -1) {
        std::cout << "first position with value " << value << " at index " << position << std::endl;
    }
    else
    {
        std::cout << "value not found" << std::endl;
    }
    cout << "Value from the beginning: ";
    my_test_list -> getFirst()-> PrintInfo();
    cout << endl;

    //My_list_element <int> result = ;
    cout <<"Pop last: " << my_test_list->pop_last() << endl;
    my_test_list -> PrintList();

    cout <<"Pop first: " << my_test_list->pop_first() << endl;

    my_test_list -> PrintList();
    cout <<"Adding a value by index (2)" << endl;
    my_test_list->addAtIndex(10, 2);
    cout << "Get the value by index" << endl;
    my_test_list->getByIndex(40) -> PrintInfo();
    cout << endl;
    cout << "Size: " << my_test_list->getCount() << endl;
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
    
    My_list <my_time> * my_time_list = new My_list <my_time>;
    my_time_list->addLast(mt1);
    my_time_list->addLast(mt2);
    cout << "Value from the beginning: ";
    my_time_list -> getFirst()-> PrintInfo();
    cout << endl;
  // cout << "Value from the end: ";
   //my_time_list -> getByIndex(0) -> PrintInfo();
   //cout << endl;
    std::cout << "Search by Value" << std::endl;
    std::cout << "Enter a value : ";
    cout << "Get the value by index : " ;
    my_time_list->getByIndex(1) -> PrintInfo();
    my_time_list->addAtIndex(mt1,2);
    my_time_list->PrintList();
    //my_time_list->delete_last(my_time_list->getCount()-1);
    cout << "Size: " << my_time_list->getCount() << endl;
   delete  my_time_list;
   delete my_test_list;
    return 0;
}
