#include <iostream>
#include <fstream>
using namespace std;

struct student
{
	int rollno = 0;
	string div = "";
	string name = "", address = "";
};

class studentDatabase
{
	public:
		void addData();
		void deleteData();
		void displayAll();
		void displayStudent();
};

void studentDatabase::addData()
{
	ofstream fout;
	fout.open("Assign11.dat", ios::app);
	student s1;
	cout<<"Enter roll no: ";
	cin>>s1.rollno;
	fout<<s1.rollno<<endl;
	cout<<"Enter division: ";
	cin>>s1.div;
	fout<<s1.div<<endl;
	cout<<"Enter name: ";
	cin>>s1.name;
	fout<<s1.name<<endl;
	cout<<"Enter address: ";
	cin>>s1.address;
	fout<<s1.address<<endl;
	cout<<"Student data stored successfully."<<endl;
	fout.close();
}

void studentDatabase::deleteData()
{
	string line, roll;
	bool present = false;
	ifstream fin;
	fin.open("Assign11.dat", ios::in);
	
	ofstream temp;
	temp.open("temp.dat", ios::out);
	cout<<"Give roll no. to delete: ";
	cin>>roll;
	while(getline(fin, line))
	{
		if(line == roll)
		{
			getline(fin, line);
			getline(fin, line);
			getline(fin, line);
			getline(fin, line);
			cout<<"Successfully deleted."<<endl;
			present = true;
		}
		temp<<line<<endl;
	}
	fin.close();
	temp.close();
	remove("Assign11.dat");
	rename("temp.dat", "Assign11.dat");
	if(present == false)
	{
		cout<<"Data for entered roll number not found."<<endl;
	}
}

void studentDatabase::displayStudent()
{
	string line, roll;
	bool present = false;
	ifstream fin;
	fin.open("Assign11.dat", ios::in);
	cout<<"Give roll no. to show data: ";
	cin>>roll;
	while(getline(fin, line))
	{
		if(line == roll)
		{
			cout<<"Roll No: "<<line<<endl;
			getline(fin, line);
			cout<<"Division: "<<line<<endl;
			getline(fin, line);
			cout<<"Name: "<<line<<endl;
			getline(fin, line);
			cout<<"Address: "<<line<<endl;
			present = true;
			break;
		}
	}
	if(present == false)
	{
		cout<<"Data for entered roll number not found."<<endl;
	}
}

void studentDatabase::displayAll()
{
	ifstream fin;
	string line;
	fin.open("Assign11.dat", ios::in);
	while(1)
	{
		getline(fin, line);
		if(fin.eof())
		{
			break;
		}
		cout<<"Roll No: "<<line<<endl;
		getline(fin, line);
		cout<<"Division: "<<line<<endl;
		getline(fin, line);
		cout<<"Name: "<<line<<endl;
		getline(fin, line);
		cout<<"Address: "<<line<<endl;
	}
}
int main()
{
	studentDatabase b1;
//	ofstream fout;
//	fout.open("Assign11.dat", ios::trunc);
//	fout.close();
	int ch = 0;
	while(ch != 5)
	{
		cout<<"--------------------------------------------------------------------------------"<<endl;
		cout<<"1. Add data"<<endl;
		cout<<"2. Delete data"<<endl;
		cout<<"3. Display all student data"<<endl;
		cout<<"4. Display specific student data"<<endl;
		cout<<"5. Exit"<<endl;
		cout<<"Enter choice: ";
		cin>>ch;
		cout<<"--------------------------------------------------------------------------------"<<endl;
		switch(ch)
		{
			case 1:
				b1.addData();
				break;
			case 2:
				b1.deleteData();
				break;
			case 3:
				b1.displayAll();
				break;
			case 4:
				b1.displayStudent();
				break;
			case 5:
				cout<<"Exiting...."<<endl;
				break;
			default:
				cout<<"Invalid choice."<<endl;
				break;
		}
	}	
}

