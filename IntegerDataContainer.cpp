#include <iostream>
#include <fstream>
#include <chrono>
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
    private:
    element * last;
    element * first;
    int cardinal;

    public:   
    idc()
    {
         last = nullptr;
         first = nullptr;
         cardinal = 0;
    }

    ///FUNCTIONS///
    
    void insert(int value)
    {
        if(value < -2147483648 || value > 2147483647)
        {
            cout<<"Invalid value";
        }else
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
            
            element * temp_prev = (*this)[index]->prev;
            element * temp_next = (*this)[index]->next;

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

            int difference = my_element->value - (*this).min()->value + 2;
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
        if(index_check(order-1) != 0)
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


            
            return start;
            
            

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
        //element * start = container.last;       from back to front *
        
        while(start->index < container.cardinal)
        {
            os<<" "<<start->value;
            start = start->next;
            
        }
        os<<" "<<start->value;
        /*while(start->index >= 0)       from back to front *
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




int main() //driver code for every function
{
    

    ifstream f("in.txt");
    ofstream o("out.txt");
    idc lista;
    string integ;

    while(getline(f,integ))
    {
        lista.insert(stoi(integ));
    }

    auto begin = chrono::high_resolution_clock::now();

    o<<"List is: "<<lista<<endl;//shows the list
    
    o<<"The element on the 10-th position is: "<<lista[10]->value<<endl; //showing a single handpicked element

    o<<"Deleted 19-th element "<<endl;

    lista.del(19); //deletes element 19

    o<<"The element on the 19-th position is: "<<lista[19]->value<<endl;

    o<<"List is: "<<lista<<endl; //reshowing of the list

    o<<"Min: "<<lista.min()->value<<endl; //min

    o<<"Max: "<<lista.max()->value<<endl; //max

    int i = 0;
    if(lista.succesor(i) != nullptr)
    {
        o<<"The value of the succesor of the "<<i<<" element is: "<<lista.succesor(i)->value<<endl; //succesor
    }else
    {
       o<<"The element on the "<<i<<" position doesn't have a succesor."<<endl;
    }

    int j = 0;
    if(lista.predecessor(j) != nullptr)
    {
        o<<"The value of the predeccesor of the "<<j<<" element is: "<<lista.predecessor(j)->value<<endl; //predecessor
    }else
    {
        o<<"The element on the "<<j<<" position doesn't have a predeccesor."<<endl;
    }

    int k = 10;
    if(lista.k_element(k) != nullptr) //smallest element in ascending order
    {
        o<<"The "<<k<<"-th element in ascending order is: "<<lista.k_element(k)->value<<endl; //k element
    }else
    {
        o<<"There is no element on the "<<k<<" position"<<endl;
    }

    o<<"Inside: "<<lista.inside(-12)<<endl; //is in the list

    o<<"Inside: "<<lista.inside(11)<<endl;

    

    f.close();
    o.close();

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end-begin);
    cout<<endl<<"Time till exit: "<<elapsed.count() * 1e-9<<" seconds";

    return 1;
}
