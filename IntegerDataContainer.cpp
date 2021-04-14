#include <iostream>
#include <fstream>
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
                return nullptr;
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
                return nullptr;
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
    ifstream f("in.txt");
    ofstream o("out.txt");



    idc lista;
    string integ;

    while(getline(f,integ))
    {
        lista.insert(stoi(integ));
    }
    o<<"Lista este: "<<lista<<endl;//afisare lista
    
    o<<"Elementul de pe pozitia 10 din lista este: "<<lista[10]->value<<endl; //afisare valoare singulara

    o<<"Am sters elementul de pe pozitia 10. "<<endl;

    lista.del(10); //stergere elementul de pe pozitia 3

    o<<"Elementul de pe pozitia 9 din lista este: "<<lista[9]->value<<endl;

    o<<"Lista este: "<<lista<<endl; //reafisare lista

    o<<"Min: "<<lista.min()->value<<endl; //min

    o<<"Max: "<<lista.max()->value<<endl; //max

    int i = 6;
    if(lista.succesor(i) != nullptr)
    {
        o<<"Valoarea succesorului elementului de pe pozitia "<<i<<" este: "<<lista.succesor(i)->value<<endl; //succesor
    }else
    {
        o<<"Elementul de pe pozitia "<<i<<" nu are succesor."<<endl;
    }

    int j = 0;
    if(lista.predecessor(j) != nullptr)
    {
        o<<"Valoarea predecesorului elementului de pe pozitia "<<j<<" este: "<<lista.predecessor(j)->value<<endl; //predecessor
    }else
    {
        o<<"Elementul de pe pozitia "<<j<<" nu are predecesor."<<endl;
    }

    int k = 0;
    if(lista.k_element(k) != nullptr) //smallest element in ascending order
    {
        o<<"Elementul numarul "<<k<<" in ordine crescatoare este: "<<lista.predecessor(k)->value<<endl; //predecessor
    }else
    {
        o<<"Nu exista element pe pozitia "<<k<<endl;
    }  

    o<<"Inside: "<<lista.inside(-12)<<endl; //is in the list

    o<<"Inside: "<<lista.inside(11)<<endl;

    f.close();
    o.close();
    return 1;
}
