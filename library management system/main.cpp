#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <limits>
#include <cstdio>
#include <windows.h> // Include for Windows API functions
using namespace std;

void clrscr() {
    system("cls");
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class book {
    char bno[6];
    char bname[50];
    char aname[20];

public:
    void createbook() {
        cout << "\nNEW BOOK ENTRY...\n";
        cout << "\nEnter The Book No.: ";
        cin >> bno;
        cin.ignore(); // to clear the '\n' left by cin
        cout << "\nEnter The Book Name: ";
        cin.getline(bname, 50);
        cout << "\nEnter The Author's Name: ";
        cin.getline(aname, 20);
        cout << "\n\n\nBOOK CREATED..";
    }

    void showbook() {
        cout << "\nBOOK NUMBER : " << bno;
        cout << "\nBOOK NAME : " << bname;
        cout << "\nAUTHOR NAME : " << aname;
    }

    void modifybook() {
        cout << "\nBOOK NUMBER : " << bno;
        cout << "\nMODIFY BOOK NAME : ";
        cin.ignore(); // to clear the '\n' left by cin
        cin.getline(bname, 50);
        cout << "\nMODIFY AUTHOR's NAME : ";
        cin.getline(aname, 20);
    }

    char* retbno() {
        return bno;
    }

    void report() {
        cout << bno << setw(30) << bname << setw(30) << aname << endl;
    }
};

class student {
    char admno[6];
    char name[100];
    char stbno[6];
    int token;

public:
    void createstudent() {
        clrscr();
        cout << "\nNEW STUDENT ENTRY...\n";
        cout << "\nEnter The Admission No. : ";
        cin >> admno;
        cin.ignore(); // to clear the '\n' left by cin
        cout << "\nEnter The Student Name : ";
        cin.getline(name, 100);
        token = 0;
        stbno[0] = '\0';
        cout << "\n\nStudent Record Created.. ";
    }

    void showstudent() {
        cout << "\nAdmission Number : " << admno;
        cout << "\nStudent Name : " << name;
        cout << "\nNo of Books issued : " << token;
        if (token == 1) {
            cout << "\nBook Number " << stbno;
        }
    }

    void modifystudent() {
        cout << "\nAdmission No. : " << admno;
        cout << "\nModify Student Name : ";
        cin.ignore(); // to clear the '\n' left by cin
        cin.getline(name, 100);
    }

    char* retadmno() {
        return admno;
    }

    char* retstbno() {
        return stbno;
    }

    int rettoken() {
        return token;
    }

    void addtoken() {
        token = 1;
    }

    void resettoken() {
        token = 0;
    }

    void getstbno(char t[]) {
        strcpy(stbno, t);
    }

    void report() {
        cout << "\t" << admno << setw(20) << name << setw(10) << token << endl;
    }
};

fstream fp, fp1;
book bk;
student st;

void writebook() {
    char ch;
    fp.open("book.dat", ios::out | ios::app);
    do {
        clrscr();
        bk.createbook();
        fp.write((char*)&bk, sizeof(book));
        cout << "\n\nDo you want to add more record..(y/n)? ";
        cin >> ch;
        cin.ignore(); // to clear the '\n' left by cin
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void writestudent() {
    char ch;
    fp.open("student.dat", ios::out | ios::app);
    do {
        clrscr();
        st.createstudent();
        fp.write((char*)&st, sizeof(student));
        cout << "\n\nDo you want to add more record..(y/n)? ";
        cin >> ch;
        cin.ignore(); // to clear the '\n' left by cin
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void displayspecificbook(char n[]) {
    cout << "\nBOOK DETAILS\n";
    int flag = 0;
    fp.open("book.dat", ios::in);
    while (fp.read((char*)&bk, sizeof(book))) {
        if (strcmp(bk.retbno(), n) == 0) {
            bk.showbook();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) {
        cout << "\n\nBook Doesn't Exist";
    }
    cin.get(); // Pause to let user see the message
}

void displayspecificstudent(char n[]) {
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;
    fp.open("student.dat", ios::in);
    while (fp.read((char*)&st, sizeof(student))) {
        if (strcmp(st.retadmno(), n) == 0) {
            st.showstudent();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) {
        cout << "\n\nStudent Doesn't Exist";
    }
    cin.get(); // Pause to let user see the message
}

void modifybook() {
    char n[6];
    int found = 0;
    clrscr();
    cout << "\n\nMODIFY BOOK RECORD...";
    cout << "\n\nEnter The Book No. : ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&bk, sizeof(book)) && found == 0) {
        if (strcmp(bk.retbno(), n) == 0) {
            bk.showbook();
            cout << "\nEnter The New Details of Book" << endl;
            bk.modifybook();
            int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&bk, sizeof(book));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0) {
        cout << "\n\nRecord Not Found";
    }
    cin.get(); // Pause to let user see the message
}

void modifystudent() {
    char n[6];
    int found = 0;
    clrscr();
    cout << "\n\nMODIFY STUDENT RECORD...";
    cout << "\n\nEnter The Admission No. : ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(student)) && found == 0) {
        if (strcmp(st.retadmno(), n) == 0) {
            st.showstudent();
            cout << "\nEnter The New Details of Student" << endl;
            st.modifystudent();
            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&st, sizeof(student));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0) {
        cout << "\n\nRecord Not Found";
    }
    cin.get(); // Pause to let user see the message
}

void deletestudent() {
    char n[6];
    int flag = 0;
    clrscr();
    cout << "\n\n\n\tDELETE STUDENT...";
    cout << "\n\nEnter The Admission No. : ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char*)&st, sizeof(student))) {
        if (strcmp(st.retadmno(), n) != 0) {
            fp2.write((char*)&st, sizeof(student));
        } else {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("temp.dat", "student.dat");
    if (flag == 1) {
        cout << "\n\n\tRECORD DELETED..";
    } else {
        cout << "\n\n\tRECORD NOT FOUND";
    }
    cin.get(); // Pause to let user see the message
}

void deletebook() {
    char n[6];
    int flag = 0;
    clrscr();
    cout << "\n\n\n\tDELETE BOOK...";
    cout << "\n\nEnter The BOOK No. : ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char*)&bk, sizeof(book))) {
        if (strcmp(bk.retbno(), n) != 0) {
            fp2.write((char*)&bk, sizeof(book));
        } else {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat", "book.dat");
    if (flag == 1) {
        cout << "\n\n\tRECORD DELETED..";
    } else {
        cout << "\n\n\tRECORD NOT FOUND";
    }
    cin.get(); // Pause to let user see the message
}

void displayallstudent() {
    clrscr();
    fp.open("student.dat", ios::in);
    if (!fp) {
        cout << "File couldn't be opened";
        return;
    } else {
        cout << "\n\n\t\tSTUDENT LIST\n\n";
        cout << "=====================================================\n";
        cout << "\tADMISSION NO." << setw(20) << "NAME" << setw(10) << "BOOK ISSUED\n";
        cout << "=====================================================\n";
        while (fp.read((char*)&st, sizeof(student))) {
            st.report();
        }
        fp.close();
        cin.get(); // Pause to let user see the message
    }
}

void displayallbook() {
    clrscr();
    fp.open("book.dat", ios::in);
    if (!fp) {
        cout << "File couldn't be opened";
        return;
    } else {
        cout << "\n\n\t\tBOOK LIST\n\n";
        cout << "==================================================================\n";
        cout << "BOOK NO." << setw(20) << "NAME" << setw(25) << "AUTHOR NAME\n";
        cout << "==================================================================\n";
        while (fp.read((char*)&bk, sizeof(book))) {
            bk.report();
        }
        fp.close();
        cin.get(); // Pause to let user see the message
    }
}

void bookissue() {
    char sn[6], bn[6];
    int found = 0, flag = 0;
    clrscr();
    cout << "\n\nBOOK ISSUE...";
    cout << "\n\n\tEnter Admission No. of Student : ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(student)) && found == 0) {
        if (strcmp(st.retadmno(), sn) == 0) {
            found = 1;
            if (st.rettoken() == 0) {
                cout << "\n\n\tEnter The Book No. : ";
                cin >> bn;
                while (fp1.read((char*)&bk, sizeof(book)) && flag == 0) {
                    if (strcmp(bk.retbno(), bn) == 0) {
                        flag = 1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                        int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*)&st, sizeof(student));
                        cout << "\n\n\tBook Issued Successfully\n\nPlease Note : Write the Book Issued date in backside of your Book & return Book within 15 days, Fine ₹1/day after 15 days period";
                    }
                }
                if (flag == 0) {
                    cout << "Book Doesn't Exist";
                }
            } else {
                cout << "You Have not returned the Last book";
            }
        }
    }
    if (found == 0) {
        cout << "Student Record Doesn't Exist";
    }
    fp.close();
    fp1.close();
    cin.get(); // Pause to let user see the message
}

void bookdeposit() {
    char sn[6], bn[6];
    int found = 0, flag = 0, day, fine;
    clrscr();
    cout << "\n\nBOOK DEPOSIT...";
    cout << "\n\n\tEnter Admission No. of Student : ";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(student)) && found == 0) {
        if (strcmp(st.retadmno(), sn) == 0) {
            found = 1;
            if (st.rettoken() == 1) {
                while (fp1.read((char*)&bk, sizeof(book)) && flag == 0) {
                    if (strcmp(bk.retbno(), st.retstbno()) == 0) {
                        flag = 1;
                        bk.showbook();
                        cout << "\n\nBook deposited in no. of days : ";
                        cin >> day;
                        if (day > 15) {
                            fine = (day - 15) * 1;
                            cout << "\n\nFine is to be deposited ₹ : " << fine;
                        }
                        st.resettoken();
                        int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*)&st, sizeof(student));
                        cout << "\n\n\tBook Deposited Successfully";
                    }
                }
                if (flag == 0) {
                    cout << "Book Doesn't Exist";
                }
            } else {
                cout << "No Book is Issued";
            }
        }
    }
    if (found == 0) {
        cout << "Student Record Doesn't Exist";
    }
    fp.close();
    fp1.close();
    cin.get(); // Pause to let user see the message
}

void start() {
    clrscr();
    gotoxy(35, 11);
    cout << "Library";
    gotoxy(35, 14);
    cout << "Management";
    gotoxy(35, 17);
    cout << "System";
    cout << "\n\nDeveloper : Arvind Kumar";
    cin.get(); // Pause the program
}

void adminmenu() {
    int ch2;
    do {
        clrscr();
        cout << "\n\n\n\tADMINISTRATOR MENU";
        cout << "\n\n\t1. CREATE STUDENT RECORD";
        cout << "\n\n\t2. DISPLAY ALL STUDENT RECORD";
        cout << "\n\n\t3. DISPLAY SPECIFIC STUDENT RECORD";
        cout << "\n\n\t4. MODIFY STUDENT RECORD";
        cout << "\n\n\t5. DELETE STUDENT RECORD";
        cout << "\n\n\t6. CREATE BOOK";
        cout << "\n\n\t7. DISPLAY ALL BOOKS";
        cout << "\n\n\t8. DISPLAY SPECIFIC BOOK";
        cout << "\n\n\t9. MODIFY BOOK RECORD";
        cout << "\n\n\t10. DELETE BOOK RECORD";
        cout << "\n\n\t11. BACK TO MAIN MENU";
        cout << "\n\n\tPLEASE ENTER YOUR CHOICE [1-11]: ";
        cin >> ch2;
        cin.ignore(); // to clear the '\n' left by cin
        switch (ch2) {
            case 1:
                writestudent();
                break;
            case 2:
                displayallstudent();
                break;
            case 3: {
                char num[6];
                clrscr();
                cout << "\n\n\tPLEASE ENTER THE ADMISSION NO.: ";
                cin >> num;
                displayspecificstudent(num);
                break;
            }
            case 4:
                modifystudent();
                break;
            case 5:
                deletestudent();
                break;
            case 6:
                writebook();
                break;
            case 7:
                displayallbook();
                break;
            case 8: {
                char num[6];
                clrscr();
                cout << "\n\n\tPLEASE ENTER BOOK NO.: ";
                cin >> num;
                displayspecificbook(num);
                break;
            }
            case 9:
                modifybook();
                break;
            case 10:
                deletebook();
                break;
            case 11:
                return;
            default:
                cout << "Invalid choice! Please try again";
                cin.get(); // Pause to let user see the message
                break;
        }
    } while (ch2 != 11);
}

int main() {
    start();
    char ch;
    do {
        clrscr();
        cout << "\n\n\n\tMain Menu";
        cout << "\n\n\t1. Book issue";
        cout << "\n\n\t2. Book Deposit";
        cout << "\n\n\t3. Admin Menu";
        cout << "\n\n\t4. Exit";
        cout << "\n\n\tPlease select Your Option [1-4]: ";
        ch = cin.get();
        cin.ignore(); // to clear the '\n' left by cin
        switch (ch) {
            case '1':
                bookissue();
                break;
            case '2':
                bookdeposit();
                break;
            case '3':
                adminmenu();
                break;
            case '4':
                break;
            default:
                cout << "\nInvalid Choice, try again";
                cin.get(); // Pause to let user see the message
                break;
        }
    } while (ch != '4');

    return 0;
}



