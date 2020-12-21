#include <iostream>
template <typename InfoType> //  шаблон поля информации
struct My_list_element// описание элементов списка
        {
private:
    My_list_element * next; // следующий
    My_list_element * prev; // предыдущий
    unsigned int index;  // индекс
    InfoType  info; // информация

public:
    
    void SetInfo (InfoType & info) // сеттер для инфо
    {
        this->info = info;
    }
    
    InfoType GetInfo () // геттер для инфо
    {
        return this->info;
    }
    
    void PrintInfo () // просто вывод в stdout
    {
        std::cout << "info: " << this->info << "       index: " << this->GetIndex() << std::endl; //просто вывод на экран
    }
    
    My_list_element () // #1 конструктор, обнуляем переменные
    {
        this->next = NULL;
        this->prev = NULL;
        this->index = 0;
        this->info = NULL;
    }
    
    My_list_element (InfoType & info) : My_list_element () //наследование, у нас же тут ооп
    {
        this->SetInfo (info);
    }
    
    ~My_list_element ()// #2 деструктор
    {
        this->next = NULL;
        this->prev = NULL;
        this->index = 0;
        this->info = NULL;
        std::cout << "My_list_element destuctor";
    }
    
    void SetNext(My_list_element * next)
    {
        this->next = next;
    }
    void SetPrev(My_list_element * prev)
    {
        this->prev = prev;
    }
    void SetIndex(int index)
    {
        this->index = index;
    }
    
    My_list_element * GetNext()
    {
        return this->next;
    }
    
    My_list_element * GetPrev()
    {
        return this->prev;
    }
    
    int GetIndex()
    {
        return this->index;
    }
    
    void PrintNextInfo()
    {
        std::cout << "next info value = " << this->GetNext()->GetInfo() << std::endl;
    }
    
    void PrintPrevInfo()
    {
        std::cout << "prev info value = " << this->GetPrev()->GetInfo() << std::endl;
    }
    
};

template <typename ListType>// описание самого списка
struct My_list
{
public:
    My_list_element <ListType> * first;
    My_list_element <ListType> * curent;
    int count;
    int maxIndex;
    
    My_list ()
    {
        first = NULL;
        curent = NULL;
        count = 0;
        maxIndex = 0;
    }
    
    int GetCount() {return this->count;}// #3 кол-во элементов
    
    void add (ListType value)// #4 функция заполнения
    {
        My_list_element <ListType> * element = new My_list_element <ListType> (value);
        if (first == NULL)
        {
            first = curent = element;
            first->SetNext(first);
            first->SetPrev(first);
            first->SetIndex(0);
            this->count=1;
            maxIndex++;
        }
        else //( first == curent )
        {
            My_list_element <ListType> * old = curent;
            curent = element;
            old->SetNext(curent);
            curent->SetPrev(old);
            curent->SetNext(first);
            curent->SetIndex(count++);
            first->SetPrev(curent);
            maxIndex++;
        }
    }
    
    void printList ()// #11 функция печати списка
    {
        std::cout << "List: " << std::endl;
        curent = first;
        if ((first == NULL) || ( curent == NULL) ) {return;};
        
        while (true)
        {
            
            curent->PrintInfo();
            //curent->PrintPrevInfo();
            //curent->PrintNextInfo();
            //std::cout << "-----------------------------" << std::endl;
            if (curent->GetNext()->GetIndex() == 0) {break;}
            curent = curent->GetNext();
        };
    }
    
    My_list_element <ListType> * GetFirst()
    {
        return this->first;
    }
    
    void printFirstInfo ()// #извлечение значения из начала
    {
        std::cout << "first element: " << this->GetFirst()->GetInfo() ;
    }
    
    My_list_element <ListType> * GetLast()
    {
        return this->first->GetPrev();
    }
    
    void printLastInfo () //#7 извлечение значения из конца
    {
        std::cout << "first element: " << this->GetLast()->GetInfo() << std::endl;
    }
    
    My_list_element <ListType> * GetListElementAtIndex(int index)// #8 получение элемента по индексу
    {
        curent = first;
        if ((first == NULL) || ( curent == NULL) || index < 0 || index > this->count) {return NULL;};
        while (true)
        {
            if (curent->GetIndex() == index) {return curent;}
            curent = curent->GetNext();
        }
        return NULL;
    }
    
    void printListElementAtIndex(int index)// #8 функция получения элемента по индексу(печать)
    {
        std::cout << "Element at index " << index << " = " << this->GetLast()->GetInfo() << std::endl;
    }
    
    void deleteAtIndex(int index)// #9 функция удаления элемента по индексу
    {
        curent = this->GetListElementAtIndex(index);
        
        if (curent == NULL) {return;}
        My_list_element <ListType> * next = curent->GetNext();
        
        curent->GetNext()->SetPrev(curent->GetPrev());
        curent->GetPrev()->SetNext(curent->GetNext());
        
        while (true)
        {
            if (next->GetIndex() != 0)
            {
                next->SetIndex(next->GetIndex() - 1);
                next = next->GetNext();
            }
            else
            {
                first = next;
                curent = first;
                break;
            }
        }
    }
};

int main ()
{
    int element;
    struct my2Dvector// пользовотельский тип данных
    {
    public:
        double x, y;
        my2Dvector () {x=0;y=0;}
        my2Dvector (double x, double y) {this->x=x;this->y=y;}
        ~my2Dvector() {x=0;y=0;}
    };
    setlocale(LC_ALL, "rus");
    my2Dvector * vec = new my2Dvector(1, 3);
    My_list <int> * my_test_list = new My_list <int> ();
    std::cout << "Заполним список" << std::endl;
    for (int i = 0; i < 10; i++)// заполненеие списка
    {
        my_test_list->add(i);
    }
    std::cout << "Выведем список" << std::endl;
    my_test_list->printList();
    std::cout << "Подсчитаем кол-во элементов :";
    my_test_list->GetCount();
    std::cout << std::endl;
    std::cout << "Найдем элемент из списка"<< std::endl;
    std::cout << "Выведите индекс элемента:";
    std::cin >> element;
    my_test_list->GetListElementAtIndex(element)->PrintInfo();
    std::cout << "Удалим эллемент из списка"<< std::endl;
    std::cout << "Выведите индекс элемента:";
    std::cin >> element;
    my_test_list->deleteAtIndex(element);
    my_test_list->printList();
    
    my_test_list->printList();
    
    std::cout << std::endl << std::endl;
    std::string k = "lol";
}