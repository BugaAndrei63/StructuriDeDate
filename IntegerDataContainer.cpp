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

    ///FUNCTIONS///
    
    void insert(int value)
    {
        element * new_element = new element;

        if(first == nullptr)
        {
            new_element->next = last;
            new_element->prev = nullptr;
            new_element->value = value;
            new_element->index = 0;

            first = new_element;
            last = new_element;

        }else
        {
            
            last->next = new_element;

            new_element->next = nullptr;
            new_element->prev = last;
            new_element->value = value;
            new_element->index = cardinal + 1;

            cardinal++;
            
            last = new_element;
        }


    }

    bool index_check(int index)
    {
        if(index > cardinal || index < 0)
        {
            cout<<"Invalid index"<<endl;
            return 0;
        }
        return 1;
    }

    void del(int index)
    {
        if(index_check(index) != 0)
        {
            int i = 0;
            while(i <= cardinal)
            {
                
                if(i == index)
                {
                    element * temp_prev = (*this)[i]->prev;
                    element * temp_next = (*this)[i]->next;

                    if(temp_prev != nullptr)
                    {
                        temp_prev->next = temp_next;
                    }
                    else
                    {
                        first = temp_next;
                    }

                    if(temp_next != nullptr)
                    {
                        temp_next->prev = temp_prev;
                        element * temp = temp_next;
                        while(temp->next != nullptr)
                        {
                            temp->index -=1;
                            temp = temp->next;
                        }
                        temp->index -=1;
                    }else
                    {
                        last = temp_prev;
                    }
                    cardinal -= 1;
                    
                    break;            
                }
                i++;
            }
        }
     
    }

    element* min()
    {
        element * min = first;
        element * start = first;

        while(start->next != nullptr)
        {
            if(start->value < min->value)
            {
                min = start;
            }
            start = start->next;
        }
        if(start->value < min->value)
        {
            min = start;
        }

        return min;
    }

    element* max()
    {
        element * max = first;
        element * start = first;

        while(start->next != nullptr)
        {
            if(start->value > max->value)
            {
                max = start;
            }
            start = start->next;
        }
        if(start->value > max->value)
        {
            max = start;
        }

        return max;
    }

    element* succesor(int index)
    {
        if(index_check(index) != 0)
        {
            element * start = first;
            element * my_element = (*this)[index];

            int difference = my_element->value - (*this).min()->value;
            int pos = -1;

            
           
            while(start != nullptr)
            {
                if(start != my_element && start->value > my_element->value && abs(start->value - my_element->value) < difference)
                {
                    difference = abs(start->value - my_element->value);
                    pos = start->index;
                }
                start = start->next;
            }
            
            
            if(pos == -1)
            {
                cout<<"No succesors.";
            }else
            {
                return (*this)[pos];
            }

        }else
        {
            cout<<"Null";
            return nullptr;
        }

        
        
    }

    element* predecessor(int index)
    {
       if(index_check(index) != 0)
       {
            element * start = first;
            element * my_element = (*this)[index];

            int difference = abs(my_element->value - (*this).min()->value);
            int pos = -1;

           while(start !=nullptr)
            {
                if(start != my_element && start->value < my_element->value && abs(my_element->value - start->value) <= difference)
                {
                    difference = abs(my_element->value - start->value);
                    pos = start->index;
                }
                start = start->next;
            }

            if(pos == -1)
            {
                cout<<"No predecesors.";
            }else
            {
                return (*this)[pos];
            }

       }else
        {
            cout<<"Null";
            return nullptr;
        }

        
    }

    element * k_element(int order)
    {
        if(index_check(order) != 0)
        {
            idc temp_list;
            element * start = first;

            while(start != nullptr)
            {
                temp_list.insert(start->value);
                start = start->next;
            }

            for(int i = 1; i < order ; i++)
            {
                temp_list.del(temp_list.min()->index);
            }
             
            int min = temp_list.min()->value;
            
            start = first;

            while(start != nullptr)
            {
                if(start->value == min)
                {
                    return start;
                }
                start = start->next;
                
            }
            

        }else
        {
            cout<<"Null";
            return nullptr;
        }      
    }


    int get_cardinal()
    {
        return cardinal + 1;
    }

    bool inside(int value)
    {
        element * start = first;

        while(start != nullptr)
        {
            if(start->value == value )
            {
                return 1;
            }
            start = start->next;
        }
        return 0;
    }

    ///OPERATORS///

    friend ostream& operator << (ostream& os, const idc container)
    {
        
        element * start =  container.first;
        //element * start = container.last;       invers
        
        while(start->index < container.cardinal)
        {
            os<<" "<<start->value;
            start = start->next;
            
        }
        os<<" "<<start->value;
        /*while(start->index >= 0)       invers
        {
            os<<" "<<start->value;
            
            start = start->prev;
        }*/
        
        return os;
    }
    
    element* operator [](int index)
    {
        index_check(index);

        if(index >= cardinal/2)
        {
            element * start =  last;
            if(start->index == index)
            {
                return start;
            }

            while(start->index != index)
            {   
                start = start->prev;
                if(start->index == index)
                {
                    return start;
                }
            }
            
        }
        else
        {
            element * start =  first;
            if(start->index == index)
            {
                return start;
            }
            while(start->index != index)
            {   
                start = start->next;
                if(start->index == index)
                {
                    return start;
                }
            }
            
        }
    }

};




int main()
{
    
    idc lista;
    lista.insert(9);
    lista.insert(-3);
    lista.insert(-568);
    lista.insert(-4);
    lista.insert(-10);
    lista.insert(1000);
    lista.insert(32);
    lista.insert(45);
    lista.insert(-324);
    lista.insert(40392);
    lista.insert(-3232);
    lista.insert(-2);
    lista.insert(62323);
    lista.insert(-122222);
    lista.insert(-12);


    cout<<lista[10]->value<<endl; //afisare valoare singulara
    cout<<lista<<endl; //afisare lista
    //lista.del(-1); //stergere elementul de pe pozitia 3
    cout<<endl;
    cout<<lista[9]->value<<endl;
    cout<<lista<<endl; //reafisare lista
    
    cout<<"Min: "<<lista.min()->value<<endl; //min
    cout<<"Max: "<<lista.max()->value<<endl; //max
    cout<<"Succesor: "<<lista.succesor(5)->value<<endl; //succesor
    cout<<"Predecesor: "<<lista.predecessor(0)->value<<endl; //predecesor
    cout<<"k-element: "<<lista.k_element(3)->value<<endl;  //smallest element in ascending order
    cout<<"Inside: "<<lista.inside(-12)<<endl; //is in the list
    cout<<"Inside: "<<lista.inside(11)<<endl;
    return 1;
}
