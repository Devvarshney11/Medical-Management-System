#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <cstring>
using namespace std;

class billing
{
public:
    int sn;
    char name[30];
    float price;
    int quantity;
    float total;
    void setdata(char *na, float p, int q)
    {
        strcpy(name, na);
        price = p;
        quantity = q;
        total = price * quantity;
    }
} b;
class medicine
{
public:
    int sno;
    char name[30];
    char pharma[100];
    float price;
    char details[100];
    char uses[100];
    int q;
    void setdata()
    {
        cout << "Enter serial no : ";
        cin >> sno;
        cin.ignore();
        cout << "Enter Medicine's Name : ";
        cin.getline(name, 30);
        cout << "Enter Pharmacy Name : ";
        cin.getline(pharma, 100);
        cout << "Enter Medicine's salts : ";
        cin.getline(details, 100);
        cout << "Enter  Medicine's uses : ";
        cin.getline(uses, 100);
        cout << "Enter Medicine's price : ";
        cin >> price;
        cout << "Enter Medicine's quantity : ";
        cin >> q;
    }
    void show()
    {
        cout << "Serial No            :: " << sno << endl
             << "Medicine name        :: " << name << endl
             << "Pharma Company name  :: " << pharma << endl
             << "Medicine's price     :: " << price << endl
             << "Medicine's quantity  :: " << q << endl
             << "Salts                :: " << details << endl
             << "Uses                 :: " << uses << endl
             << endl;
    }
} m;
void addmedicine()
{
    ofstream f;
    f.open("medicine.txt", ios::out | ios::app);
    if (!f)
    {
        cout << "File is not open" << endl;
    }
    else
    {
        m.setdata();
        f.write((char *)&m, sizeof(m));
        f.close();
        cout << endl
             << endl
             << "**********Data Added Sucessfully**********" << endl;
    }
}
void displaymedicine()
{
    ifstream f;
    f.open("medicine.txt", ios::in);
    if (!f)
    {
        cout << "File is not open" << endl;
    }
    else
    {
        while (f.read((char *)&m, sizeof(m)))
        {
            m.show();
        }
        f.close();
    }
}
void deletemedicine()
{
    fstream f, f1, f2;
    int flag = 0;
    int n;
    cout << "Enter the Medicine serial no to be deleted : ";
    cin >> n;
    f.open("medicine.txt", ios::in);
    f1.open("medicine1.txt", ios::out | ios::binary | ios::app);
    f2.open("medicine2.txt", ios::out | ios::binary);

    while (f.read((char *)&m, sizeof(m)))
    {
        if (n == m.sno)
        {
            f2.write((char *)&m, sizeof(m));
        }
        else
        {
            f1.write((char *)&m, sizeof(m));
        }
    }
    f.close();
    f1.close();
    f2.close();
    remove("medicine.txt");
    remove("medicine2.txt");
    rename("medicine1.txt", "medicine.txt");
}
void updatemedicine(int n)
{
    int pos;
    fstream f;
    f.open("medicine.txt", ios::in | ios::out | ios::binary);
    while (f.read((char *)&m, sizeof(m)))
    {
        if (n == m.sno)
        {
            pos = f.tellg();
            m.setdata();
            f.seekg(pos - sizeof(m));
            f.write((char *)&m, sizeof(m));
        }
    }
    f.close();
}
void Stock()
{
    cout << "**********STOCK**********" << endl
         << endl;
    cout << "Sno                    Medicine Name                    Quantity" << endl;
    fstream f;
    f.open("medicine.txt", ios::in);
    while (f.read((char *)&m, sizeof(m)))
    {
        cout << m.sno << "                    " << m.name << "                          " << m.q << endl;
    }
    f.close();
}
void updatestock()
{
    cout << "Enter the medicnine id to be updated : ";
    int n;
    cin >> n;
    fstream f;
    int pos;
    f.open("medicine.txt", ios::out | ios::in | ios::binary);
    while (f.read((char *)&m, sizeof(m)))
    {
        if (n == m.sno)
        {
            pos = f.tellg();
            f.seekg(pos - sizeof(m.q));
            cout << "Enter the new quantity for medicine no " << m.sno << " : ";
            cin >> m.q;
            f.write((char *)&m.q, sizeof(m.q));
            break;
        }
    }
    f.close();
}
void Billing()
{
    float total = 0;
    int i = 1;
    int n;
    fstream f, f1;
    f1.open("bill.txt", ios::out | ios::app);
    int pos;
    do
    {
        f.open("medicine.txt", ios::in | ios::out | ios::binary);
        cout << "Enter the Medicine id and 0 for exit : ";
        cin >> n;
        if (n == 0)
        {
            break;
        }
        cout << "Enter the Quantity of medicine to purchase : ";
        int qu;
        cin >> qu;
        while (f.read((char *)&m, sizeof(m)))
        {
            if (n == m.sno)
            {
                if (m.q == 0)
                {
                    cout << "No Stock for medicine" << endl;
                    break;
                }
                b.sn = i;
                b.setdata(m.name, m.price, qu);
                f1.write((char *)&b, sizeof(b));
                total += (m.price * qu);
                i++;
                pos = f.tellg();
                f.seekg(pos - sizeof(m.q));
                m.q = m.q - qu;
                f.write((char *)&m.q, sizeof(m.q));
                break;
            }
        }
        f.close();
    } while (n);
    f.close();
    system("cls");
    if (total == 0)
    {
        return;
    }
    f1.close();
    f1.open("bill.txt", ios::in);
    cout << "Sno          MedicineName                    Price          Quantity          Total" << endl;
    while (f1.read((char *)&b, sizeof(b)))
    {
        cout << b.sn << "             " << b.name << "                    " << b.price << "            " << b.quantity << "             " << b.total << endl;
    }
    cout << endl
         << "                                                                                                 Total :: " << total << endl
         << endl
         << endl;
    f1.close();
    remove("bill.txt");
}
void Medicine()
{
    int n;
    do
    {
        system("cls");
        cout << "**********Medicine Portal**********" << endl
             << endl
             << "0. Exit()" << endl
             << "1. Add Medicine" << endl
             << "2. Update Medicine" << endl
             << "3. Delete Meidcine" << endl
             << "4. Display Medicines"
             << endl
             << endl;
        cout << "Enter your choice : ";
        cin >> n;
        system("cls");
        switch (n)
        {
        case 1:
            addmedicine();
            break;
        case 2:
            int n;
            cout << "Enter the Medicine's  serial no to be updatded : ";
            cin >> n;
            updatemedicine(n);
            cout << "**********Updation Sucessfull**********" << endl;
            break;
        case 3:

            deletemedicine();
            cout << "**********Deletion Sucessful**********" << endl;
            break;
        case 4:
            displaymedicine();
            break;
        }
        system("pause");
    } while (n != 0);
}
void mainmenu()
{
    int n;
    do
    {
        system("cls");
        cout << "********************MEDICINE SHOP********************"
             << endl
             << endl
             << "0. Exit()" << endl
             << "1. Medicine" << endl
             << "2. Stock of Medicine" << endl
             << "3. Billing" << endl
             << "4. Update Stock" << endl
             << endl;
        cout << "Enter your choice : ";
        cin >> n;
        system("cls");
        switch (n)
        {
        case 1:
            Medicine();
            break;
        case 2:
            Stock();
            break;
        case 3:
            Billing();
            break;
        case 4:
            updatestock();
            break;
        }
        system("pause");
    } while (n != 0);
}
int main()
{
    mainmenu();
    return 0;
}
