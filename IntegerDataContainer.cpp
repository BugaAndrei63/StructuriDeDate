#include <iostream>
using namespace std;


struct element
{
    int value;

    int index;

    element * next;
    element * prev;
};

class idc //integer data container
{
    public:

    element * last;
    element * first;
    int cardinal;
        
    idc()
    {
         last = nullptr;
         first = nullptr;
         cardinal = 0;
    }

    void insert(int val)
    {
        element * new_element = new element;

        if(first == nullptr)
        {
            new_element->next = last;
            new_element->prev = nullptr;
            new_element->value = val;
            new_element->index = 0;

            first = new_element;
            last = new_element;
        }else
        {
            
            last->next = new_element;

            new_element->next = nullptr;
            new_element->prev = last;
            new_element->value = val;
            new_element->index = cardinal + 1;

            cardinal++;
            
            last = new_element;
        }


    }


    friend ostream& operator << (ostream& os, const idc container)
    {
        
        element * start =  container.first;
        //element * start = container.last;
        
        while(start->index <= container.cardinal)
        {
            os<<" "<<start->value;
            
            start = start->next;
        }

        /*while(start->index >= 0)
        {
            os<<" "<<start->value;
            
            start = start->prev;
        }*/

        return os;
    }
    


};




int main()
{
    
    idc lista;
    lista.insert(1);
    lista.insert(2);
    lista.insert(3);
    lista.insert(4);
    lista.insert(4);
    lista.insert(4);
    lista.insert(6);
    lista.insert(5);
    lista.insert(62323);
    lista.insert(122222);
    lista.insert(12);
    cout<<lista;
    

    return 1;
}
