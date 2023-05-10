/*
flight between two cities
matrix and linked list representation
take input any city and checks link
connected flight
*/
// assignment 8
#include <iostream>
#include <string.h>
using namespace std;
// using adjacancy matrix
class citygraph
{
    string name[10];
    char present[10][10];
    int time[10][10];
    int fual[10][10];
    int passenger[10][10];

public:
    int n;
    void accept_info();
    void accept_name_city();
    void display_matrix(int[10][10]);
    void checks_link(string);
    void city();
    void connected_cities(string, string);
};
void citygraph::connected_cities(string city1, string city2)
{
    int c1, c2;
    for (int i = 0; i < n; i++)
    {
        if (city1.compare(name[i]) == 0)
        {
            c1 = i;
        }
        if (city2.compare(name[i]) == 0)
        {
            c2 = i;
        }
    }
    if (present[c1][c2] == 'Y' || present[c1][c2] == 'y')
    {
        cout << "flight is available from " << name[c1] << " to " << name[c2] << endl;
    }
    else
    {
        cout << "direct flight is not available" << endl;
        for (int j = 0; j < n; j++)
        {
            if (present[c1][j] == 'y' || present[c1][j] == 'Y')
            {
                if (present[j][c2] == 'y' || present[j][c2] == 'Y')
                {
                    cout << "flight is available from " << name[c1] << " to " << name[j] << " to and from " << name[j] << " to " << name[c2] << endl;
                }
            }
        }
    }
}
void citygraph::city()
{
    for (int k = 0; k < n; k++)
    {
        if (k == 0)
        {
            cout << "\t";
        }
        cout << "\t" << name[k];
    }
}
void citygraph::checks_link(string city)
{
    int j, count;
    count = 0;
    for (int i = 0; i < n; i++)
    {
        if (city.compare(name[i]) == 0)
        {
            j = i;
        }
    }
    for (int k = 0; k < n; k++)
    {
        if (present[j][k] == 'y' || present[j][k] == 'Y')
        {
            cout << "flight is available from " << name[j] << " to " << name[k] << endl;
            count = 1;
        }
    }
    if (count == 0)
    {
        cout << "No flight is available from " << name[j] << endl;
    }
}
void citygraph::accept_name_city()
{
    cout << "enter how many cities do you want to connect:";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "enter name of city: ";
        cin >> name[i];
    }
}
void citygraph::accept_info()
{
    accept_name_city();
    int i, j;
    char ch;
    cout << "if cities are linked then enter y else n" << endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i != j)
            {
                cout << "enter whether flight is available from " << name[i] << " to " << name[j] << " (y/n) :";
                cin >> ch;
                present[i][j] = ch;
                if (ch == 'y' || ch == 'Y')
                {
                    cout << "enter time required for this:";
                    cin >> time[i][j];
                    cout << "\nenter fual required for this:";
                    cin >> fual[i][j];
                    cout << "\nenter passengers capacity of flight:";
                    cin >> passenger[i][j];
                }
                else
                {
                    time[i][j] = 0;
                    fual[i][j] = 0;
                    passenger[i][j] = 0;
                }
            }
            else
            {
                present[i][j] = 'n';
                time[i][j] = 0;
                fual[i][j] = 0;
                passenger[i][j] = 0;
            }
        }
    }
    cout << "present absent matrix" << endl;
    city();
    cout << endl;
    for (i = 0; i < n; i++)
    {
        cout << name[i] << "\t";

        for (j = 0; j < n; j++)
        {
            cout << "\t" << present[i][j];
        }
        cout << endl;
    }
    cout << "time matrix" << endl;
    display_matrix(time);
    cout << "fual matrix" << endl;
    display_matrix(fual);
    cout << "passengers matrix" << endl;
    display_matrix(passenger);
}
void citygraph::display_matrix(int arr[10][10])
{

    cout << "graph matrix using adjacancy matrix representation" << endl;
    city();
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << name[i] << "\t";

        for (int j = 0; j < n; j++)
        {
            cout << "\t" << arr[i][j];
        }
        cout << endl;
    }
}

int main()
{
    citygraph cg;
    string city, city1, city2;
    int ch;
    cg.accept_info();
    do
    {
        cout << "\n1.checks flights from any city \n2.check flight from one city to another city"
             << "\nEnter your choice:";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "from which city do you want to book flight:";
            cin >> city;
            cg.checks_link(city);
            break;

        case 2:
            cout << "from which city to which city do you want to book flight:";
            cin >> city1;
            cin >> city2;
            cg.connected_cities(city1, city2);
            break;
        }
    } while (ch != 0);
    return 0;
}