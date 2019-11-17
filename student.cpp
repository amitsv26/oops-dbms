#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <iomanip>
#include<stdlib.h>
#include <mysql/mysql.h>
#include <string>
using std::string;
using namespace std;

// Global Variable
int qstate, previousQuantity = 0;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
// Global Variable End

class Student
{
public:
    Student();
    void show();
    void displaystudents();
    void add();
    void editStudents();
    void deleteStudents();
    bool searchById(string);
    void updatefees();
 
};

Student::Student()
{
   conn = mysql_init(0);
    if (conn)
    {
        cout << "Database Connected" << endl;
    
      
    }
    else {
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
    }
    conn = mysql_real_connect(conn, "localhost", "root", "root1234", "Student", 0, NULL, 0);
    if (conn)
    {
        cout << "Database Connected To MySql" << conn << endl;
      
    }
    else
        cout << "Failed To Connect!" << mysql_errno(conn) << endl;
}

void Student::add()
{
   

    string name;
    string usn;
    string clas;
    string fees;
    cout<<"Enter name: ";
    cin>>name;
    cout<<"Enter usn: ";
    cin>>usn;
    cout<<"Enter class: ";
    cin>>clas;
    //cout<<"Enter fees: ";
    //cin>>fees;

    string query = "insert into inventory (name, usn, clas) values ('"+name+"','"+usn+"','"+clas+"');";

    const char* q = query.c_str();
    cout<<"Insertion done\n";
    qstate = mysql_query(conn, q);

    
}


// Developed by CodeWithC.com

bool Student::searchById(string id)
{
    string query = "SELECT usn FROM inventory;";
    cout<<1;
    int s,x;
    s = stoi(id);
 
    const char* q = query.c_str();
    cout<<2;
    qstate = mysql_query(conn, q);
    cout<<3;
    res = mysql_store_result(conn);
    cout<<4;
    bool found = false;
    cout<<5;

    if(!qstate)
    {
        cout<<6;
        
        while ((row = mysql_fetch_row(res)))
        {
            cout<<"\t"<<7;
            x= stoi(row[0]);
            
            if(x == s)
            {
                found = true;
                cout<<"found\n";
                break;
            }
        }
    }

    return found;
}


void Student::editStudents()
{
    
    Student::displaystudents();

    string num;
    cout<<"Enter item Id to edit: ";
    cin>>num;

    bool found = searchById(num);

    if(found)
    {

        string query = "select * from inventory where usn = '"+num+"';";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);

        if(!qstate)
        {
            res = mysql_store_result(conn);
            row =mysql_fetch_row(res);
            cout<<"Name "<<row[0]<<" Class "<<row[2]<<" with ID "<<row[1];
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }

        string name, quantity;
        cout<<"\n\nEnter new name: ";
        cin>>name;
        cout<<"Enter new class: ";
        cin>>quantity;
        

        string update_query = "update inventory set name = '"+name+"', clas = '"+quantity+"' where usn = '"+num+"';";

        q = update_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << endl << "Successfully Updated In Database." << endl;
        }
        else
        {
            cout << "Failed To Update!" << mysql_errno(conn) << endl;
        }
    }
    else
    {
        cout << "Please Enter a valid ID." << endl;
    }
}


void Student::updatefees()
{
    
    Student::displaystudents();

    string num;
    float f,rem;
  
    string cr;
    cout<<"Enter Student id to pay the fees ";
    cin>>num;
    bool found = searchById(num);

    if(found)
    {

        string query = "select * from inventory where usn = '"+num+"';";
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);

        if(!qstate)
        {
            res = mysql_store_result(conn);
            row =mysql_fetch_row(res);
            cout<<"Name "<<row[0]<<" Class "<<row[2]<<" with ID "<<row[1]<<" has "<<row[3]<<" balance remaining.";
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }

        cout<<"\nHow much you want to deposit?\t";
        cin>>f;
        rem = stof(row[3]);
        rem = rem - f;
      
        cr = to_string(rem);

        string update_query = "update inventory set fees = '"+cr+"' where usn = '"+num+"';";

        q = update_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << endl << "Successfully Updated In Database." << endl;
        }
        else
        {
            cout << "Failed To Update!" << mysql_errno(conn) << endl;
        }
    }
    else
    {
        cout << "Please Enter a valid ID." << endl;
    }
}



void Student::deleteStudents()
{
    

    string id;
    cout<<"Enter item Id to delete: ";
    cin>>id;

    bool found = false;

    string query = "SELECT usn FROM inventory;";
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    res = mysql_store_result(conn);

    if(!qstate)
    {
        while ((row = mysql_fetch_row(res)))
        {
            if(row[0] == id)
            {
                found = true;
                break;
            }
        }
    }

    if(found)
    {
        query = "delete from inventory where usn = '"+id+"';";
        q = query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate)
        {
            cout << "Successfully Deleted From Item Record." << endl;
        }
        else
        {
            cout << "Failed To Delete!" << mysql_errno(conn) << endl;
        }
    }
    else
    {
        cout << "Please Enter a valid ID." << endl;
    }
}


void Student::show()
{
    cout << "\nStudent Fees Management System" << endl;

    cout << "1.Add student record" << endl;
    cout << "2.Display student record" << endl;
    cout << "3.Modify student record" << endl;
    cout << "4.Delete student record" << endl;
    cout << "5.Update Fees Details" << endl;
    cout << "6.Exit" << endl;
    cout<<"Enter your choice: ";
}

void Student::displaystudents()
{
   // conn = mysql_real_connect(conn, "localhost", "root", "root1234", "Student", 0, NULL, 0);
    qstate = mysql_query(conn, "select * from inventory;");

    if (!qstate)
    {
        res = mysql_store_result(conn);
        printf("\n------------------------------------------------------------\n");
        printf("| %-20s | %-10s | %-10s |%-10s\n", "Name","USN", "Class","fees");
        while ((row = mysql_fetch_row(res)))
        {
            printf("| %-20s | %-10s | %-10s |%-10s\n", row[0], row[1], row[2], row[3]);
        }
        printf("------------------------------------------------------------\n");
    }
    else
    {
        cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
    }
}

















int main()
{
    string num;
    int choice=0;
    Student st;
    while(choice!=8)
    {
        st.show();
        cin>>choice;
        switch(choice)
        {
            case 1:
            st.add();
            break;
            case 2:
            st.displaystudents();
            break;
            case 3:
            st.editStudents();
            break;
            case 4:
            st.deleteStudents();
            break;
            case 5:
            st.updatefees();
            break;
            case 6:
            exit(0);
            break;
            default:
            cout<<"Invalid Input\n";
            break;
        }
    }


    
    return 0;
}
