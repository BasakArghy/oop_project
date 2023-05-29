#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
class guest
{
public:
    string name;
    string email;
public:
    guest(string name,string email)
    {
        this->name=name;
        this->email=email;

    }
};
class task
{
public:
    string functionName;
    int dateDD;
    int dateMM;
    int dateYY;
    string location;
    string shoping[5]= {"Balloons","Cold Drink","Cake","Cups","Flowers"};
    int shopPrice[5]= {2,30,500,20,50};
    vector<int>shop;
    vector<int>quantity;
    vector<guest> guestList;
    int price;

    friend istream &operator >>(istream &in,task &newTask)
    {
        int i;

        cout << "Enter event name(Birthday,Wedding,others): ";
        in.ignore();
        getline(in, newTask.functionName);

        cout << "Enter event date(dd/mm/yy): ";
        in>>newTask.dateDD;
        in>>newTask.dateMM;
        in>>newTask.dateYY;
        in.ignore();
        cout << "Enter event location(District,Thana,House Number): ";
        getline(in, newTask.location);



        cout<<endl;
        cout<<"---------------------------"<<"SHOPING PRODUCTS"<< "---------------------------" <<endl;
        cout<<endl;

        int num;
        char boli;
        do
        {
            for(i=0; i<5; i++)
            {
                cout<<i<<"."<<newTask.shoping[i]<<"         price : "<<newTask.shopPrice[i]<<" Taka"<<endl;
            }
            cout << "Enter shopping item number: ";
            in>>num;
            newTask.shop.push_back(num);
            cout<<"How much : ";
            in>>num;
            newTask.quantity.push_back(num);
            cout<<"Do you want to shop more ?(Y/N) : ";
            in>>boli;
            cout<<endl;
        }
        while(boli!='N');

        cout<<"How many guest do you want to invite : ";
        in>>num;
        string name,email;
        for(i=0; i<num; i++)
        {
            cout<<"Enter guest name : ";
            in>>name;
            cout<<"Enter guest email address : ";
            in>>email;
            cout<<endl;
            guest Guest(name,email);
            newTask.guestList.push_back(Guest);
        }
        return in;
    }


    friend ostream& operator<<(ostream& out,task & taski)
    {

        int i;
        out<<"                       ----------------------------                       "<<endl;
        out << "Event Name: " << taski.functionName << endl;
        out << "Organizing date : " << taski.dateDD<<"/"<<taski.dateMM<<"/"<<taski.dateYY<< endl;
        out<<"Event location : "<<taski.location<<endl;
        out<< endl;
        out<<"       ----Shopping Items----       "<<endl;
        for(i=0; i<taski.shop.size(); i++)
        {
            out<<i+1<<"."<< taski.shoping[taski.shop[i]]<<"     "<<taski.quantity[i]<<" pics"<<endl;
        }
        out<< endl;
        out<<"       ----Bills----       "<<endl;

        out<<"Shoping Price : "<<taski.price<<" Taka"<<endl;
        out<<"Cleaning price :  300 Taka"<<endl;
        out<<"Decorations price :  700 Taka"<<endl;
        out<<"Total price :   "<<(taski.price+1000)<<" Taka"<<endl;
        out<<endl;
        out<<"       ----Invited Guests----       "<<endl;

        for(i=0; i<taski.guestList.size(); i++)
        {

            out<<"Name : "<<taski.guestList[i].name<<"               Email : "<<taski.guestList[i].email<<endl;
        }

        out<< endl;

        return out;
    }


};
class cal
{
protected :
    virtual void ant()=0;

    int calculatePrice(task &thisTask)
    {
        int i,price=0;
        for(i=0; i<thisTask.shop.size(); i++)
        {
            price=price+thisTask.shopPrice[thisTask.shop[i]]*thisTask.quantity[i];

        }
        return price;
    }

};


class event :public cal
{

public:

    void ant()
    {

    };
    void createTask(vector<task>& tasks)
    {
        task newTask;
        cin>>newTask;
        newTask.price = calculatePrice(newTask);
        tasks.push_back(newTask);


        cout<<"Shoping Price : "<<newTask.price<<" Taka"<<endl;
        cout<<"Cleaning price :  300 Taka"<<endl;
        cout<<"Decorations price :  700 Taka"<<endl;
        cout<<"Total price :   "<<(newTask.price+1000)<<" Taka"<<endl;
        cout<<endl;
        cout << "Event created successfully!" << endl;
    }



    void viewTasks(const vector<task>& tasks)
    {
        int j;
        if (tasks.empty())
        {
            cout << "No events found." << endl;
        }
        else
        {
            cout << "Event List:" << endl;
            for (j=0; j<tasks.size(); j++ )
            {
                task taski;
                taski=tasks[j];
                cout<<"                                      "<<j<<"                                   "<<endl;
                cout<<taski;
            }
        }
    }


    void deleteTask(vector<task>& tasks)
    {
        if (tasks.empty())
        {
            cout << "No events found." << endl;
        }
        else
        {
            cout << "Enter the index of the event to delete: ";
            int index;
            cin >> index;

            if (index >= 0 && index < tasks.size())
            {
                tasks.erase(tasks.begin() + index);
                cout << "Task deleted successfully!" << endl;
            }
            else
            {
                cout << "Invalid event index." << endl;
            }
        }
    }
};
template<typename T>
inline void greeting(T st)
{
    cout<<st<<endl;
}
int main()
{
    event e;
    cal *c;
    event *p ;
    c=&e;
    p= dynamic_cast<event *> (c);  //dynmic cast
    if(p!=nullptr)
    {
        cout<<"Welcome!";
    }
    greeting<string>(" You can create new event planning here.");
    vector<task> tasks;

    int choice;

    do
    {
        cout << "Event Organizer Application" << endl;
        cout << "1. Create Event" << endl;
        std::cout << "2. View Events" << endl;
        cout << "3. Delete Event" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:

            e.createTask(tasks);
            break;
        case 2:
            e.viewTasks(tasks);
            break;
        case 3:
            e.deleteTask(tasks);
            break;
        case 4:
            cout << "Exiting application. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            break;
        }

        cout << endl;
    }
    while (choice != 4);

    return 0;
}

