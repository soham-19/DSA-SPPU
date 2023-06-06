/*
Use a sequential file to maintain student data and peform operations on it
*/

#include <iostream>
#include <fstream>   							// fstream = filestream
using namespace std;							// fstream == it is used to create files,write information to files, and read information from files..

//student structure
struct student
{
int roll;
char name[20];
char div;
string add;

void getdata()
{ 
        cout << "\n Enter roll\n";
        cin >> roll;
        cout<<"Enter your name\n";
        cin>>name;
        cout<<"Enter your division\n";
        cin>>div;
        cout<<"Enter your address\n";
        cin>>add;
}

void putdata()
{
    cout << "\n" << roll << ":" << name<<":"<< div<<":"<< add ;
}

};

class file	// file == a collection of related data records ;; provides a mechanism for the long term storage of data ;; they remain to exist in computer even if the 
			//     computer is switched off ;; files are stored in the concentric circular tracks of a floppy or a hard disk ;;

{
  	fstream fp; 			//declare      
    student s;
    public:  
    void create() 
    {
        char ans;
        fp.open("student.dat",ios::out);    //fpopen()= open an existing file or create a new file for use
        do									// ios::out = allows output (write operation)to a stream
		{
            s.getdata();
            fp.write((char*)&s,sizeof(s));
            cout <<"\n Add more? :";
            cin>> ans;
        }
		while(ans=='y');
        fp.close(); 
    }


    void display()
    {
        fp.open("student.dat",ios::in);					// ios::in = allows output (read  operation)to a stream
        while (!fp.eof())								// cpp provides a special function,eof(). that returns non-zero (meaning true ) when there are no more data to be
        {												//     from an input file stream, and zero (meaninf false) otherwise .
            fp.read((char*)&s,sizeof(s));
             											//  (!fp.eof())	== checks if the end of the file has not been reached .as long as the condition evaluates to true, 
            if (!fp.eof())								//                 the code block asssociated with the while loop will executed .This allows you to read and process
            {    										//                 the contents of the file until you reach the end...
                if (s.roll==0)
                cout<<"-------------";
                //break;
                else
                s.putdata();
            }
        }
        fp.close();
    }

    void search()
    {
        fp.open("student.dat",ios::in); 
        int r,flag;
        cout << "\n Enter roll to be searched :";
        cin >> r;
        while (!fp.eof())
        {
            fp.read((char*)&s,sizeof(s));
            if (!fp.eof() and s.roll==r) 
            {
                s.putdata();
                flag=1;
                break;
            }
        }
        if(flag==0);
        cout<<"\n not found!!!!";
        fp.close();
    }
    
    void append()
    {
        char ans;
        fp.open("student.dat",ios::app); 
        s.getdata();
        fp.write((char*)&s,sizeof(s));
        fp.close();

    }
    
    void physical_delete()
    {
        int r;
        fstream tfp;
        fp.open("student.dat",ios::in);
        tfp.open("temp",ios::out);
        cout << "\n Enter roll to be deleted :";
        cin >> r;
        while (fp.read((char*)&s,sizeof(s)))
        {
            if (s.roll==r)
            {
                cout << "\n Deleting .....\n";  
                s.putdata();
            }
            else
            {
                tfp.write((char*)&s,sizeof(s));
            }
        }

        fp.close();
        tfp.close();
        remove("student.dat");
        rename("temp","student.dat");
        
    }
    
    void logical_delete()
    {
        int r;
        fstream tfp;
        fp.open("student.dat",ios::in|ios::out); 
        cout<<"Enter the roll no to be deleted logicaly: ";
        cin>>r;
        while(fp.read((char*)&s,sizeof(s)))
        {
            if(s.roll==r)
            {
                cout<<"\n Deleting......";
                s.putdata();
                s.roll=0;
                //move pointer to previous record
                fp.seekp(-1*sizeof(s),ios::cur);
                fp.write((char*)&s,sizeof(s));
                break;
            }
        }
        fp.close();
      
        //remove("student.dat");
        //rename("temp1","student.dat");
    }
    
    void update()
    {
        int r;
        fstream tfp;
        fp.open("student.dat",ios::in|ios::out);
       
        cout<<"Enter the roll no to be updated: ";
        cin>>r;
        while(fp.read((char*)&s,sizeof(s)))
        {
            if(s.roll==r)
            {
                cout<<"\n Updating......";
                cout<<"Enter the name to be updated: ";
                cin>>s.name;
                //move pointer to previous record
                fp.seekp(-1*sizeof(s),ios::cur);
                fp.write((char*)&s,sizeof(s));
                break;
            }      
        }
        fp.close();
       
        //remove("student.dat");
        //rename("temp3","student.dat");
    }
}; 

int main()
{
    file f;
    int ch;
    do
    {
        cout<<"\n............main menu..............\n";
        cout<<"1.inseart\n";
        cout<<"2.display\n";
        cout<<"3.search\n";
        cout<<"4.append\n";
        cout<<"5.physical_delete\n";
        cout<<"6.logical_delete\n";
        cout<<"7.update\n";
        cout<<"8.Exit\n";
        cout<<"\n Enter your choice :";
        cin>>ch;
        switch(ch)
        {
            case 1:
                f.create();
                break;
            case 2:
                f.display();
                break;
            case 3:
                f.search();
                break;
            case 4:
                f.append();
                break;
            case 5:
                f.physical_delete();
                break;
            case 6:
                f.logical_delete();
                break;
            case 7:
                f.update();
                break;
            case 8:
                cout<<"Thank You!!!!!\n";
                break;
                
        }
    }
	while(ch<9);
return 0;
}
