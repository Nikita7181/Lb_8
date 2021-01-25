#include <iostream>

template <typename InfoType> //  шаблон поля информации
struct My_list_element {
private:
    My_list_element * next; // следующий
    My_list_element * prev; // предыдущий
    unsigned int index;  // индекс, не знаю пока зачем, но пусть будет
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
    
    My_list_element () // конструктор, обнуляем переменные
    {
        this->next = nullptr;
        this->prev = nullptr;
        this->index = 0;
    }
    
    My_list_element (InfoType info) : My_list_element () //наследование, у нас же тут ооп
    {
        this->SetInfo (info);
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
    
};

template <typename ListType>
struct My_list
{
public:
    My_list_element <ListType> * first;
    My_list_element <ListType> * curent;
    int count;
    int maxIndex;
    
    My_list ()
    {
        first = nullptr;
        curent = nullptr;
        count = 0;
        maxIndex = 0;
    }
    
    ~My_list ()
    {
        My_list_element<ListType> *temp;
        curent = GetLast();

        while (first != curent)
        {
            curent=curent->GetPrev();
            delete curent->GetNext();
        }
    }
    
    int GetCount() {return this->count;}
    
    void add (ListType value)
    {
        My_list_element <ListType> * element = new My_list_element <ListType> (value);
        if (first == nullptr)
        {
            first = curent = element;
            first->SetNext(first);
            first->SetPrev(first);
            first->SetIndex(0);
            this->count=1;
            maxIndex++;
        }
        else
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
    
    void addFirst (ListType value)
    {
        My_list_element <ListType> * element = new My_list_element <ListType> (value);
        if (first == nullptr)
        {
            first = curent = element;
            first->SetNext(first);
            first->SetPrev(first);
            first->SetIndex(0);
            this->count=1;
            maxIndex++;
        }
        else
        {
            My_list_element <ListType> * old = first;
            
            first = element;
            first->SetNext(old);
            first->SetPrev(old->GetPrev());
            
            old->GetPrev()->SetNext(first);
            old->SetPrev(first);
            first->SetIndex(0);
            this->maxIndex++;
            this->count++;
            curent = first->GetNext();
            while (curent != first)
            {
                curent->SetIndex(curent->GetIndex()+1);
                curent=curent->GetNext();
            }
            
        }
        
    }
    
    void addAtIndex (ListType value, int index)
    {
        My_list_element <ListType> * element = new My_list_element <ListType> (value);
        if (first == nullptr)
        {
            first = curent = element;
            first->SetNext(first);
            first->SetPrev(first);
            first->SetIndex(0);
            this->count=1;
            maxIndex++;
        }
        else
        {
            curent = first;
            if ((index < 0)||(index>maxIndex)) {return;}
            
            while (curent->GetIndex() != index)
            {
                curent=curent->GetNext();
            }
            
            My_list_element <ListType> * old = curent;
            
            curent = element;
            curent->SetNext(old);
            curent->SetPrev(old->GetPrev());
            curent->SetIndex(index);
            
            old->GetPrev()->SetNext(curent);
            old->SetPrev(curent);
            
            this->maxIndex++;
            this->count++;
            curent = curent->GetNext();
            while (curent != first)
            {
                curent->SetIndex(curent->GetIndex()+1);
                curent=curent->GetNext();
            }
            
        }
        
    }

    void addAtPointer (ListType value, My_list_element <ListType> * pntr)
    {
        //My_list_element <ListType> * element = new My_list_element <ListType> (value);
        
        if (!first) {return;}

        curent = first;
        do
        {
            if (curent == pntr) {break;};
            curent=curent->GetNext();
        } while (curent != first) ;
        
        int indx = curent->GetIndex();
        addAtIndex(value, indx+1);
    }
    
    void printList ()
    {
        std::cout << "List: " << std::endl;
        curent = first;
        if ((first == nullptr) || ( curent == nullptr) ) {return;}
        

        //curent->PrintInfo();
        //while (curent->GetNext()->GetIndex() != 0)
        do
        {
            
            curent->PrintInfo();
            //if (curent->GetNext()->GetIndex() == 0) {break;}
            curent = curent->GetNext();
        }while (curent->GetIndex() != 0);
    }
    
    My_list_element <ListType> * GetFirst(){
        return this->first;
    }
    
    My_list_element <ListType> * GetLast(){
        return this->first->GetPrev();
    }
    
    My_list_element <ListType> * GetListElementAtIndex(int index)
    {
        curent = first;
        if ((first == nullptr) || ( curent == nullptr) || index < 0 || index > this->count) {return nullptr;}
        while (true)
        {
            if (curent->GetIndex() == index) {return curent;}
            curent = curent->GetNext();
        }
    }
    
    void deleteAtIndex(int index)
    {
        curent = this->GetListElementAtIndex(index);
        
        if (curent == nullptr) {return;}
        My_list_element <ListType> * next = curent->GetNext();
        
        curent->GetNext()->SetPrev(curent->GetPrev());
        curent->GetPrev()->SetNext(curent->GetNext());
        
        if (index == 0)
        {
            first = curent->GetNext();
            curent = curent->GetNext();
        }
        
        while (curent->GetIndex() != 0)
        {
            
            curent->SetIndex(curent->GetIndex() - 1);
            curent = curent->GetNext();

        }
        /*while (true)
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
        }*/

        this->count--;
        this->maxIndex--;
    }

    void deleteAtPointer ( My_list_element <ListType> * pntr)
    {
        if (!first) {return;}

        curent = first;
        do
        {
            if (curent == pntr) {break;};
            curent=curent->GetNext();
        } while (curent != first) ;
        
        int indx = curent->GetIndex();
        deleteAtIndex(indx);
    }
    
    int SearchByValue (ListType value)
    {
        this->curent = this->first;
        
        while (true)
        {
            if (curent->GetInfo() == value) {return curent->GetIndex();}
            My_list_element <ListType> * next = this->curent->GetNext();
            if (next->GetIndex() == 0)
            {
                return -1;
            }
            else
            {
                curent = next;
            }
        }
        
    }
    
    void pop_last()
    {
        std::cout << "Last index: " << GetLast() ->GetIndex()<< " " << "Last Info: " << GetLast() ->GetInfo() << std::endl;
        My_list_element <ListType> * tmp = GetLast();
        int indx = tmp->GetIndex();
        deleteAtIndex(indx);
    }
    
    void pop_first()
    {
        std::cout << "First index: " <<GetFirst() ->GetIndex() << " " << "First Info: " << GetFirst() ->GetInfo() << std::endl;
        My_list_element <ListType> * tmp = GetFirst();
        int indx = tmp->GetIndex();
        deleteAtIndex(indx);
    }

    void operator delete(void * ptr)
    {
        free(ptr);
    }
};


struct my2Dvector
{
public:
    double x, y;
    my2Dvector () {x=0;y=0;}
    my2Dvector (double x, double y) {this->x=x;this->y=y;}
    ~my2Dvector() {x=0;y=0;}
    
    bool operator==(const my2Dvector & mv)
    {
        if ((this->x == mv.x) && (this->y == mv.y)) { return true;}
        
        return false;
    }
    
    bool operator!=(const my2Dvector & mv)
    {
        if ((this->x != mv.x) && (this->y != mv.y)) { return true;}
        
        return false;
    }
    
    
};

std::ostream & operator<< (std::ostream& os, const my2Dvector& vctr)
{
    os << "(" << vctr.x << ", " << vctr.y << ")";
    return os;
}



int main ()
{
    My_list <int> * my_test_list = new My_list <int> ();
    for (int i = 0; i < 10; i++)
    {
        my_test_list->add(i);
        //std::cout << "Size: " << my_test_list->GetCount () << std::endl;
    }
    my_test_list->printList();
    std::cout << std::endl;
    std::cout << "Search by index(6): ";
    my_test_list->GetListElementAtIndex(6)->PrintInfo();
    std::cout << "delete at index(0) :" << std::endl;
    my_test_list->deleteAtIndex(0);
    //std::cout << "Size: " << my_test_list->GetCount () << std::endl;
    my_test_list->printList();
    std::cout << "Get element at index (5): ";
    my_test_list->GetListElementAtIndex(5)->PrintInfo();
    std::cout << "Search by Value" << std::endl;
    std::cout << "Enter a value : ";
    int value = 0;
    std::cin>>value;
    int position = my_test_list->SearchByValue (value);
    if (position != -1) {
        std::cout << "first position with value " << value << " at index " << position << std::endl;
    }
    else
    {
        std::cout << "value not found" << std::endl;
    }
    my_test_list->pop_last();
    my_test_list->printList();
    my_test_list->pop_first();
    my_test_list->printList();
    int new_fisrt = 100;// добавление первого элемента
    my_test_list->addFirst(new_fisrt);
    my_test_list->printList();
    my_test_list->addAtIndex(new_fisrt, 5);// добавление по индексу
    my_test_list->printList();
    std::cout << "Size: " << my_test_list->GetCount () << std::endl;

    my_test_list->addAtPointer(777, my_test_list->GetFirst()->GetNext()); //добавим 777 после 2
    my_test_list->printList();

    my_test_list->deleteAtPointer(my_test_list->GetFirst()->GetNext()); //удалим 2
    my_test_list->printList();

    delete my_test_list;
    // проверка пользовательского типа
    std::cout << "--------------------------------------------" << std::endl << std::endl;
    My_list <my2Dvector> * my_test_list2 = new My_list <my2Dvector>;
    my2Dvector vec1;
    for (int i = 0; i < 10; i++)
    {
        
        vec1.x = rand()%100;
        vec1.y = rand()%100;
        my_test_list2->add(vec1);// добавление в конец
    }
    my_test_list2->printList();
    vec1.x = 40;
    vec1.y = 27;
    int searchResult = my_test_list2->SearchByValue(vec1);// поиск по значению
    if (searchResult != -1)
    {
        std::cout << "vector" << vec1 << " found at index " << searchResult << std::endl;
    }
    else
    {
        std::cout  << "vector" << vec1 << " not found "<< std::endl;
    }
    vec1.x = 41;
    vec1.y = 28;
    my_test_list2->addFirst(vec1);// добавление в начало
    vec1.x = 4;
    vec1.y = 35;
    my_test_list2 -> addAtIndex(vec1, 6);
    my_test_list2 -> printList();
    std::cout << std::endl;
    my_test_list2->pop_last();
    my_test_list2->printList();
    my_test_list2->pop_first();
    my_test_list2->printList();
    my_test_list2->GetListElementAtIndex(6)->PrintInfo();
    std::cout << "Size: " << my_test_list2->GetCount() << std::endl;
    
    delete my_test_list2;
    return 0;
}
