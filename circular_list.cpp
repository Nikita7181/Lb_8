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
        this->next = NULL; //все таки оно NULL а не null
        this->prev = NULL;
        this->index = 0;
    }
    
    My_list_element (InfoType info) : My_list_element () //наследование, у нас же тут ооп
    {
        this->SetInfo (info);
    }
    
    ~My_list_element (){
        this->next = NULL;
        this->prev = NULL;
        this->index = 0;
        std::cout << "My_list_element destructor";
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
        first = NULL;
        curent = NULL;
        count = 0;
        maxIndex = 0;
    }
    
    int GetCount() {return this->count;}
    
    void add (ListType value)
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
    
    void addFirst (ListType value)
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
            My_list_element <ListType> * old = first;
            //curent = element;
            
            first = element;
            first->SetNext(old);
            first->SetPrev(old->GetPrev());
            
            old->GetPrev()->SetNext(first);
            old->SetPrev(first);
            //old->
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
            curent = first;
            if ((index < 0)||(index>maxIndex)) {return;}
            
            while (curent->GetIndex() != index)
            {
                curent=curent->GetNext();
            }
            
            My_list_element <ListType> * old = curent;
            //curent = element;
            
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
    
    void printList ()
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
    
    My_list_element <ListType> * GetFirst(){
        return this->first;
    }
    
    void printFirstInfo ()
    {
        std::cout << "first element: " << this->GetFirst()->GetInfo() ;
    }
    
    My_list_element <ListType> * GetLast(){
        return this->first->GetPrev();
    }
    
    void printLastInfo ()
    {
        std::cout << "first element: " << this->GetLast()->GetInfo() << std::endl;
    }
    
    My_list_element <ListType> * GetListElementAtIndex(int index)
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
    
    void printListElementAtIndex(int index)
    {
        std::cout << "Element at index " << index << " = " << this->GetLast()->GetInfo() << std::endl;
    }
    
    void deleteAtIndex(int index)
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
        this->count--;
        this->maxIndex--;
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
};


struct my2Dvector
{
public:
    double x, y;
    my2Dvector () {x=0;y=0;}
    my2Dvector (double x, double y) {this->x=x;this->y=y;}
    ~my2Dvector() {x=0;y=0;}
    
    
    
    /* std::string to_string (const my2Dvector vec)
     {
         std::ostringstream strm;
         strm << "(" << vec->x << ", " << vec->y << ")";
         return stream.str();
     } */
    
    bool operator==(const my2Dvector & mv)
    {
        if ((this->x == mv.x) && (this->y == mv.y)) { return true;};
        
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
    }
    my_test_list->printList();
    std::cout << std::endl;
    std::cout << "Search by index(6): ";
    my_test_list->GetListElementAtIndex(6)->PrintInfo();
    std::cout << "delete at inde(0) :" << std::endl;
    my_test_list->deleteAtIndex(0);
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
    std::cout << "Ger first: " << my_test_list-> GetFirst() -> GetInfo() << std::endl;
    std::cout << "Ger last: " << my_test_list-> GetLast() -> GetInfo() << std::endl;
    int new_fisrt = 100;// добавление первого элемента
    my_test_list->addFirst(new_fisrt);
    my_test_list->printList();
    my_test_list->addAtIndex(new_fisrt, 5);// удаление по индексу
    my_test_list->printList();
    std::cout << "Size: " << my_test_list->GetCount () << std::endl;
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
    std::cout << "Ger first: " << my_test_list2-> GetFirst() -> GetInfo() << std::endl;
    std::cout << "Ger last: " << my_test_list2-> GetLast() -> GetInfo() << std::endl;
    my_test_list->GetListElementAtIndex(6)->PrintInfo();
    std::cout << "Size: " << my_test_list2->GetCount() << std::endl;
    return 0;
}
