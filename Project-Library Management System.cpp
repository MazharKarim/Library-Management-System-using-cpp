#include <iostream>
#include <fstream>
#include <process.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <ctime>
using namespace std;

COORD coord={0,0};


//*******************************************
//THIS FUNCTION CLEARS TO THE END OF THE LINE
//*******************************************

void clreol()
{
    printf("                                                                              ") ;
}


//**********************************
//THIS FUNCTION SETS THE CUSOR POINT
//**********************************

void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


//************************************************
//THIS CLASS CONTROL ALL THE FUNCTIONS IN THE MENU
//************************************************

class MENU
{
	public :
			void main_menu(void) ;
			void introduction(void) ;
			void rules(void) ;
	private :
			void edit_menu(void) ;
			void edit_book(void) ;
			void edit_member(void) ;
} ;


//**********************************************
//THIS CLASS CONTAINS FUNCTIONS RELATED TO BOOKS
//**********************************************

class BOOK
{
	public :
			void list(void) ;
			char *bookname(int) ;
	protected :
			void add_new_book(int, char tname[33], char tauthor[26], int, int) ;
			void update_copies(int, int, int) ;
			void modify(int, char[], char[]) ;
			void deletion(void) ;
			int  book_found(int) ;
			int  bookname_found(char []) ;
			int  available(int) ;
			char *authorname(int) ;
			float bookprice(int) ;
			int  no_of_copies(int) ;
			int  bookcodeof(char[]) ;
			void display(int) ;
			int  reccount(void) ;
			void delete_rec(int) ;
	private :
			int   bookcode, copies ;
			char  name[33], author[26] ;
			int   avail ;
} ;


//************************************************
//THIS CLASS CONTAINS FUNCTIONS RELATED TO MEMBERS
//************************************************

class MEMBER
{
	public :
			void list(void) ;
	protected :
			void add_mem(int, int, char [], char [], char[], int, int, int) ;
			void modify(int, char[], char[], char[]) ;
			int  member_found(int) ;
			void update_book(int, int, int, int, int) ;
			char *membername(int) ;
			char *memberphone(int) ;
			char *memberaddress(int) ;
			int  lastcode(void) ;
			int  issued(int) ;
			int  fine(int) ;
			void display(int) ;
			void delete_rec(int) ;
	private :
			int  memcode, bookcode ;
			char name[26], phone[11], address[33] ;
			int  dd, mm, yy ;   // DATE OF RETURNING THE BOOK //
} ;


//***********************************************************************************************
//THIS IS DERIVED FROM CLASS BOOK & MEMBER AND CONTAINS FUNCTIONS FOR WORKING (ISSUE,RETURN,ETC.)
//***********************************************************************************************

class WORKING : public BOOK, public MEMBER
{
	public :
			void issue_book(void) ;
			void return_book(void) ;
			void add_book(void) ;
			void add_member(void) ;
			void modify_book(void) ;
			void modify_member(void) ;
			void delete_book(void) ;
			void delete_member(void) ;
} ;


//*************************************************
//THIS CLASS CONTAINS FUNCTIONS RELATED DATE & FINE
//*************************************************

class DATES
{
	public :
			void extend_date(int,int,int,int) ;
			int  diff(int, int, int, int, int, int) ;
			int  day, mon, year ;
} ;



//***************************************
//FUNCTION TO EXTEND GIVEN DATES BY 7 DAYS
//***************************************

void DATES :: extend_date(int d1, int m1, int y1, int days)
{
	static int month[] = {31,29,31,30,31,30,31,31,30,31,30,31} ;
	for (int i=1; i<=days; i++)
	{
		d1++ ;
		if ((d1 > month[m1-1]) || (y1%4 != 0 && m1 == 2 && d1 > 28)) { d1 = 1 ; m1++ ; }
		if (m1 > 12) { m1 = 1 ; y1++ ; }
	}
	day  = d1 ; mon  = m1 ; year = y1 ;
}


//************************************************************
//THIS FUNCTION RETURNS THE DIFFERENCE BETWEEN TWO GIVEN DATES
//************************************************************

int DATES :: diff(int d1, int m1, int y1, int d2, int m2, int y2)
{
	int days = 0 ;
	if ((y2<y1) || (y2==y1 && m2<m1) || (y2==y1 && m2==m1 && d2<d1))
		return days ;
	static int month[] = {31,29,31,30,31,30,31,31,30,31,30,31} ;
	while (d1 != d2 || m1 != m2 || y1 != y2)
	{
		days++ ; d1++ ;
		if ((d1 > month[m1-1]) || (y1%4 != 0 && m1 == 2 && d1 > 28)) { d1 = 1 ; m1++ ; }
		if (m1 > 12) { m1 = 1 ; y1++ ; }
	}
	return days ;
}


//***************************************************************************
//FUNCTION TO DISPLAY MAIN MENU AND CONTROL ALL THE FUNCTION IN THE MAIN MENU
//***************************************************************************

void MENU :: main_menu(void)
{
	char ch ;
	while (1)
	{
	    system("cls") ;


        gotoxy(14,4) ; printf("  Bangladesh University of Business and Technology  ") ;
        gotoxy(14,6) ; printf("                   DIGITAL LIBRARY                  ") ;
        gotoxy(14,9) ; printf("                        MENU                        ") ;
        gotoxy(14,11) ;printf("                    1. RULES                        ") ;
        gotoxy(14,12) ;printf("                    2. ADD NEW BOOK                 ") ;
        gotoxy(14,13) ;printf("                    3. ADD NEW MEMBER               ") ;
        gotoxy(14,14) ;printf("                    4. ISSUE BOOK                   ") ;
        gotoxy(14,15) ;printf("                    5. RETURN BOOK                  ") ;
        gotoxy(14,16) ;printf("                    6. LIST OF BOOKS                ") ;
        gotoxy(14,17) ;printf("                    7. LIST OF MEMBERS              ") ;
        gotoxy(14,18) ;printf("                    8. EDIT                         ") ;
        gotoxy(14,19) ;printf("                    0. QUIT                         ") ;
        gotoxy(14,22) ;printf("                Enter your choice : ") ;
        gotoxy(50,22) ; ch = getche() ;

		if (ch == 27) { break ; }
		else if (ch == '1') { rules() ; }
		else if (ch == '2') { WORKING W ; W.add_book() ; }
		else if (ch == '3') { WORKING W ; W.add_member() ; }
		else if (ch == '4') { WORKING W ; W.issue_book() ; }
		else if (ch == '5') { WORKING W ; W.return_book() ; }
		else if (ch == '6') { BOOK B ; B.list() ; }
		else if (ch == '7') { MEMBER M ; M.list() ; }
		else if (ch == '8') { edit_menu() ; }
		else if (ch == '0') { break ; }
	}
}


//*****************************
//FUNCTION TO DISPLAY EDIT MENU
//*****************************

void MENU :: edit_menu(void)
{
	char ch ;
	while (1)
	{
	    system("cls") ;


        gotoxy(14,4) ; printf("  Bangladesh University of Business and Technology  ") ;
        gotoxy(14,6) ; printf("                   DIGITAL LIBRARY                  ") ;
        gotoxy(14,9) ; printf("                     EDIT  MENU                     ") ;
        gotoxy(14,12) ;printf("                     1. BOOKS                       ") ;
        gotoxy(14,13) ;printf("                     2. MEMBERS                     ") ;
        gotoxy(14,14) ;printf("                     0. EXIT                        ") ;
        gotoxy(14,17) ;printf("                 Enter your choice: ") ;
        gotoxy(50,17) ; ch = getche() ;

		if (ch == 27) { break ; }
		else if (ch =='1') { edit_book() ; }
		else if (ch == '2') { edit_member() ; }
		else if (ch == '0') { break ; }
	}
}


//************************************************************************************
//FUNCTION TO DISPLAY EDIT MENU FOR BOOK AND CONTROL ALL THE FUNCTION IN THE EDIT MENU
//************************************************************************************

void MENU :: edit_book(void)
{
	char ch ;
	while (1)
	{
	    system("cls") ;


        gotoxy(14,4) ; printf("  Bangladesh University of Business and Technology  ") ;
        gotoxy(14,6) ; printf("                   DIGITAL LIBRARY                  ") ;
        gotoxy(14,9) ; printf("                     EDIT  BOOKS                    ") ;
        gotoxy(14,12) ;printf("                     1. MODIFY                      ") ;
        gotoxy(14,13) ;printf("                     2. DELETE                      ") ;
        gotoxy(14,14) ;printf("                     0. EXIT                        ") ;
        gotoxy(14,17) ;printf("                 Enter your choice: ") ;
        gotoxy(50,17) ; ch = getche() ;

		if (ch == 27) { break ; }
		else if (ch == '1') { WORKING W ; W.modify_book() ; }
		else if (ch == '2') { WORKING W ; W.delete_book() ; }
		else if (ch == '0') { break ; }
	}
}


//***************************************************************************************
//FUNCTION TO DISPLAY EDIT MENU FOR MEMBERS AND CONTROL ALL THE FUNCTION IN THE EDIT MENU
//***************************************************************************************

void MENU :: edit_member(void)
{
	char ch ;
	while (1)
	{
	    system("cls") ;


        gotoxy(14,4) ; printf("  Bangladesh University of Business and Technology  ") ;
        gotoxy(14,6) ; printf("                   DIGITAL LIBRARY                  ") ;
        gotoxy(14,9) ; printf("                    EDIT MEMBERS                    ") ;
        gotoxy(14,12) ;printf("                     1. MODIFY                      ") ;
        gotoxy(14,13) ;printf("                     2. DELETE                      ") ;
        gotoxy(14,14) ;printf("                     0. EXIT                        ") ;
        gotoxy(14,17) ;printf("                 Enter your choice: ") ;
        gotoxy(50,17) ; ch = getche() ;

		if (ch == 27) { break ; }
		else if (ch == '1') { WORKING W ; W.modify_member() ; }
		else if (ch == '2') { WORKING W ; W.delete_member() ; }
		else if (ch == '0') { break ; }
	}
}


//****************************************************
//FUNCTION TO DISPLAY THE INTRODUCTION FOR THE PROJECT
//****************************************************

void MENU :: introduction(void)
{
    system("cls") ;


	gotoxy(14,4) ; printf("               Welcome to my Project                ") ;
	gotoxy(14,6) ; printf("             Library Management System              ") ;
	gotoxy(14,11) ;printf(" This  project has facility of maintaining  records ") ;
	gotoxy(14,12) ;printf("                of BOOKS and MEMBERS.               ") ;
	gotoxy(14,24) ;printf("             Press any key to continue...") ;

	getch() ;
}

//*********************************************
//FUNCTION TO DISPLAY THE IRULES OF THE LIBRARY
//*********************************************

void MENU :: rules(void)
{
	system("cls") ;

	gotoxy(14,4) ; printf("  Bangladesh University of Business and Technology  ") ;
	gotoxy(14,6) ; printf("                   DIGITAL LIBRARY                  ") ;
	gotoxy(14,9) ; printf("                       RULES                        ") ;
	gotoxy(14,12) ;printf(" 1. This book may be kept for a week and may be ren-") ;
	gotoxy(14,13) ;printf("    ewed once for the same period.                  ") ;
	gotoxy(14,14) ;printf(" 2. Late fine of Taka 5.00/day will be charged if t-") ;
	gotoxy(14,15) ;printf("    he book is not returned in time.                ") ;
	gotoxy(14,16) ;printf(" 3. No book will be issued if the fine is not paid. ") ;
	gotoxy(14,17) ;printf(" 4. A student borrower will be held solely responsi-") ;
	gotoxy(14,18) ;printf("    ble for any borrowed book(s).                   ") ;
	gotoxy(14,19) ;printf(" 5. A borrower may take one book at a time.         ") ;
	gotoxy(14,20) ;printf(" 6. Fine will be charged for damage/loss of book(s).") ;
	gotoxy(14,25) ;printf("             Press any key to continue...") ;
	getch() ;
}


//***************************************************
//THIS FUNCTION RETURN 0 IF GIVEN BOOK CODE NOT FOUND
//***************************************************

int BOOK :: book_found(int tcode)
{
	ifstream file ;
	file.open("BOOK.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	int found=0 ;
	while (file.read((char *) this, sizeof(BOOK)))
	{ if (bookcode == tcode) { found = 1 ; break ; } }
	file.close() ;
	return found ;
}


//***************************************************
//THIS FUNCTION RETURN 0 IF GIVEN BOOK NAME NOT FOUND
//***************************************************

int BOOK :: bookname_found(char t1code[33])
{
	ifstream file ;
	file.open("BOOK.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	int found=0 ;
	while (file.read((char *) this, sizeof(BOOK)))
	{ if (!strcmpi(name,t1code)) { found = 1 ; break ; } }
	file.close() ;
	return found ;
}


//*************************************************************************
//THIS FUNCTION RETURNS THE NO. OF AVAILABLE COPIES FOR THE GIVEN BOOK CODE
//*************************************************************************

int BOOK :: available(int tcode)
{
	ifstream file ;
	file.open("BOOK.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	int tavail=0 ;
	while (file.read((char *) this, sizeof(BOOK)))
	{ if (bookcode == tcode) { tavail = avail ; break ; } }
	file.close() ;
	return tavail ;
}


//***************************************************************
//THIS FUNCTION RETURNS THE NO. OF COPIES FOR THE GIVEN BOOK CODE
//***************************************************************

int BOOK :: no_of_copies(int tcode)
{
	ifstream file ;
	file.open("BOOK.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	int tcopies=0 ;
	while (file.read((char *) this, sizeof(BOOK)))
	{ if (bookcode == tcode) { tcopies = copies ; break ; } }
	file.close() ;
	return tcopies ;
}


//**********************************************************
//THIS FUNCTION RETURNS THE BOOK NAME OF THE GIVEN BOOK CODE
//**********************************************************

char *BOOK :: bookname(int tcode)
{
	ifstream file ;
	file.open("BOOK.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	char tname[33] ;
	while (file.read((char *) this, sizeof(BOOK)))
	{ if (bookcode == tcode) { strcpy(tname,name) ; break ; } }
	file.close() ;
	return tname ;
}


//************************************************************
//THIS FUNCTION RETURNS THE AUTHOR NAME OF THE GIVEN BOOK CODE
//************************************************************

char *BOOK :: authorname(int tcode)
{
	ifstream file ;
	file.open("BOOK.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	char tauthor[26] ;
	while (file.read((char *) this, sizeof(BOOK)))
	{ if (bookcode == tcode) { strcpy(tauthor,author) ; break ; } }
	file.close() ;
	return tauthor ;
}


//**********************************************************
//THIS FUNCTION RETURNS THE BOOK CODE OF THE GIVEN BOOK NAME
//**********************************************************

int BOOK :: bookcodeof(char t1code[33])
{
	ifstream file ;
	file.open("BOOK.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	int tcode=0 ;
	while (file.read((char *) this, sizeof(BOOK)))
	{ if (!strcmpi(name,t1code)) { tcode = bookcode ; break ; } }
	file.close() ;
	return tcode ;
}


//*************************************************************
//THIS FUNCTION RETURNS THE NO. OF THE RECORDS IN THE BOOK FILE
//*************************************************************

int BOOK :: reccount(void)
{
	ifstream file ;
	file.open("BOOK.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	int count=0 ;
	while (file.read((char *) this, sizeof(BOOK))) { count++ ; }
	file.close() ;
	return count ;
}


//*******************************************************
//THIS FUNCTION DELETES THE RECORD OF THE GIVEN BOOK CODE
//*******************************************************

void BOOK :: delete_rec(int tcode)
{
	fstream file ;
	file.open("BOOK.DAT", ios::in) ;
	fstream temp ;
	temp.open("temp.dat", ios::out) ;
	file.seekg(0,ios::beg) ;
	while ( !file.eof() )
	{
		file.read((char *) this, sizeof(BOOK)) ;
		if ( file.eof() ) { break ; }
		if ( bookcode != tcode ) { temp.write((char *) this, sizeof(BOOK)) ; }
	}
	file.close() ;
	temp.close() ;
	file.open("BOOK.DAT", ios::out) ;
	temp.open("temp.dat", ios::in) ;
	temp.seekg(0,ios::beg) ;
	while ( !temp.eof() )
	{
		temp.read((char *) this, sizeof(BOOK)) ;
		if ( temp.eof() ) { break ; }
		file.write((char *) this, sizeof(BOOK)) ;
	}
	file.close() ;
	temp.close() ;
}


//*********************************************
//THIS FUNCTION ADD THE RECORD IN THE BOOK FILE
//*********************************************

void BOOK :: add_new_book(int tcode,char tname[33], char tauthor[26], int tcopies, int tavail)
{
	ofstream file ;
	file.open("BOOK.DAT", ios::app) ;
	bookcode = tcode ;
	strcpy(name,tname) ;
	strcpy(author,tauthor) ;
	copies = tcopies ;
	avail = tavail ;
	file.write((char *) this, sizeof(BOOK)) ;
	file.close() ;
}


//************************************************************************
//THIS FUNCTION UPDATE THE RECORD IN THE BOOK FILE FOR THE GIVEN BOOK CODE
//************************************************************************

void BOOK :: update_copies(int tcode, int tcopies, int tavail)
{
	fstream file ;
	file.open("BOOK.DAT", ios::in) ;
	fstream temp ;
	temp.open("temp.dat", ios::out) ;
	file.seekg(0,ios::beg) ;
	while ( !file.eof() )
	{
		file.read((char *) this, sizeof(BOOK)) ;
		if ( file.eof() ) { break ; }
		if ( bookcode == tcode )
		{
			copies = tcopies ; avail = tavail ;
			temp.write((char *) this, sizeof(BOOK)) ;
		}
		else { temp.write((char *) this, sizeof(BOOK)) ; }
	}
	file.close() ;
	temp.close() ;
	file.open("BOOK.DAT", ios::out) ;
	temp.open("temp.dat", ios::in) ;
	temp.seekg(0,ios::beg) ;
	while ( !temp.eof() )
	{
		temp.read((char *) this, sizeof(BOOK)) ;
		if ( temp.eof() ) { break ; }
		file.write((char *) this, sizeof(BOOK)) ;
	}
	file.close() ;
	temp.close() ;
}


//************************************************************************
//THIS FUNCTION MODIFY THE RECORD IN THE BOOK FILE FOR THE GIVEN BOOK CODE
//************************************************************************

void BOOK :: modify(int tcode, char tname[33], char tauthor[26])
{
	fstream file ;
	file.open("BOOK.DAT", ios::in) ;
	fstream temp ;
	temp.open("temp.dat", ios::out) ;
	file.seekg(0,ios::beg) ;
	while ( !file.eof() )
	{
		file.read((char *) this, sizeof(BOOK)) ;
		if ( file.eof() ) { break ; }
		if ( bookcode == tcode )
		{
			strcpy(name,tname) ; strcpy(author,tauthor) ;
			temp.write((char *) this, sizeof(BOOK)) ;
		}
		else { temp.write((char *) this, sizeof(BOOK)) ; }
	}
	file.close() ;
	temp.close() ;
	file.open("BOOK.DAT", ios::out) ;
	temp.open("temp.dat", ios::in) ;
	temp.seekg(0,ios::beg) ;
	while ( !temp.eof() )
	{
		temp.read((char *) this, sizeof(BOOK)) ;
		if ( temp.eof() ) { break ; }
		file.write((char *) this, sizeof(BOOK)) ;
	}
	file.close() ;
	temp.close() ;
}


//***************************************************************************
//THIS FUNCTION DISPLAY THE RECORD FROM THE BOOK FILE FOR THE GIVEN BOOK CODE
//***************************************************************************

void BOOK :: display(int tcode)
{
	ifstream file ;
	file.open("BOOK.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	while (file.read((char *) this, sizeof(BOOK)))
	{
		if (bookcode == tcode)
		{
			gotoxy(5,5) ;  cout <<"Book Code   : " <<bookcode ;
			gotoxy(5,7) ;  cout <<"Book Name   : " <<name ;
			gotoxy(5,8) ;  cout <<"Author Name : " <<author ;
			gotoxy(5,10) ; cout <<"Copies      : " <<copies ;
			gotoxy(5,11) ; cout <<"Available   : " <<avail ;
			break ;
		}
	}
	file.close() ;
}


//***************************************
//THIS FUNCTION DISPLAY THE LIST OF BOOKS
//***************************************

void BOOK :: list(void)
{
	system("cls") ;
	int row = 4 , found=0, flag=0 ;
	char ch ;

	gotoxy(1,2) ; printf("                                 LIST OF BOOKS                                ") ;
	gotoxy(1,3) ; printf(" CODE BOOK NAME                        AUTHOR                          COPIES ") ;
	ifstream file ;
	file.open("BOOK.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	while (file.read((char *) this, sizeof(BOOK)))
	{
		flag = 0 ;

		found = 1 ;
		gotoxy(2,row) ;  cout <<bookcode ;
		gotoxy(7,row) ;  cout <<name ;
		gotoxy(40,row) ; cout <<author ;
		gotoxy(73,row) ; cout <<copies ;

		gotoxy(40,row+1) ;printf("STATUS: ") ;

		printf("%d copies available",avail) ;

		if ( row == 22 )
		{
			flag = 1 ;
			row = 6 ;
			gotoxy(1,25) ; cout <<"Press any key to continue or Press <ESC> to exit" ;
			ch = getch() ;
			if (ch == 27) { break ; }
			system("cls") ;

            gotoxy(1,2) ; printf("                                 LIST OF BOOKS                                ") ;
            gotoxy(1,3) ; printf(" CODE BOOK NAME                        AUTHOR                          COPIES ") ;
		}
		else { row = row + 2 ; }
	}
	if (!found) { gotoxy(5,10) ; cout <<"\7Records not found" ; }
	if (!flag) { gotoxy(1,25) ; cout <<"Press any key to continue..." ; getch() ; }

	file.close () ;
}


//*********************************************************
//THIS FUNCTION RETURN 0 IF THE GIVEN MEMBER CODE NOT FOUND
//*********************************************************

int MEMBER :: member_found(int mcode)
{
	ifstream file ;
	file.open("MEMBER.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	int found=0 ;
	while (file.read((char *) this, sizeof(MEMBER)))
	{ if (memcode == mcode) { found = 1 ; break ; } }
	file.close() ;
	return found ;
}


//*************************************************************
//THIS FUNCTION RETURN 0 IF THE MEMBER HAVE NOT ISSUED ANY BOOK
//*************************************************************

int MEMBER :: issued(int mcode)
{
	ifstream file ;
	file.open("MEMBER.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	int missue=0 ;
	while (file.read((char *) this, sizeof(MEMBER)))
	{ if (memcode == mcode) { missue = bookcode ; break ; } }
	file.close() ;
	return missue ;
}


//*****************************************************************
//THIS FUNCTION CALCULATE AND RETURN FINE FOR THE GIVEN MEMBER CODE
//*****************************************************************

int MEMBER :: fine(int mcode)
{
	DATES D ;
	int d1, m1, y1 ;
	time_t t = time(0);   // get time now
	struct tm * now = localtime( & t );
	d1 = now->tm_mday ; m1 = now->tm_mon + 1 ; y1 = now->tm_year + 1900 ;
	ifstream file ;
	file.open("MEMBER.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	int days, t_fine ;
	while (file.read((char *) this, sizeof(MEMBER)))
	{
		if (memcode == mcode)
		{ days = D.diff(dd,mm,yy,d1,m1,y1) ; t_fine = days * 5 ; }
	}
	file.close() ;
	return t_fine ;
}


//*****************************************************
//THIS FUNCTION RETURN THE LAST CODE OF THE MEMBER FILE
//*****************************************************

int MEMBER :: lastcode(void)
{
	ifstream file ;
	file.open("MEMBER.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	int mcode=0 ;
	while (file.read((char *) this, sizeof(MEMBER))) mcode = memcode ;
	file.close() ;
	return mcode ;
}


//**********************************************************
//THIS FUNCTION RETURNS MEMBER NAME OF THE GIVEN MEMBER CODE
//**********************************************************

char *MEMBER :: membername(int mcode)
{
	ifstream file ;
	file.open("MEMBER.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	char mname[26] ;
	while (file.read((char *) this, sizeof(MEMBER)))
	{ if (memcode == mcode) { strcpy(mname,name) ; break ; } }
	file.close() ;
	return mname ;
}


//***********************************************************
//THIS FUNCTION RETURNS MEMBER PHONE OF THE GIVEN MEMBER CODE
//***********************************************************

char *MEMBER :: memberphone(int mcode)
{
	ifstream file ;
	file.open("MEMBER.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	char mphone[11] ;
	while (file.read((char *) this, sizeof(MEMBER)))
	{ if (memcode == mcode) { strcpy(mphone,phone) ; break ; } }
	file.close() ;
	return mphone ;
}


//*************************************************************
//THIS FUNCTION RETURNS MEMBER ADDRESS OF THE GIVEN MEMBER CODE
//*************************************************************

char *MEMBER :: memberaddress(int mcode)
{
	ifstream file ;
	file.open("MEMBER.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	char maddress[33] ;
	while (file.read((char *) this, sizeof(MEMBER)))
	{ if (memcode == mcode) { strcpy(maddress,address) ; break ; } }
	file.close() ;
	return maddress ;
}


//*****************************************************
//THIS FUNCTION DELETE RECORD FOR THE GIVEN MEMBER CODE
//*****************************************************

void MEMBER :: delete_rec(int mcode)
{
	fstream file ;
	file.open("MEMBER.DAT", ios::in) ;
	fstream temp ;
	temp.open("temp.dat", ios::out) ;
	file.seekg(0,ios::beg) ;
	while ( !file.eof() )
	{
		file.read((char *) this, sizeof(MEMBER)) ;
		if ( file.eof() ) { break ; }
		if ( memcode != mcode )  { temp.write((char *) this, sizeof(MEMBER)) ; }
	}
	file.close() ;
	temp.close() ;
	file.open("MEMBER.DAT", ios::out) ;
	temp.open("temp.dat", ios::in) ;
	temp.seekg(0,ios::beg) ;
	while ( !temp.eof() )
	{
		temp.read((char *) this, sizeof(MEMBER)) ;
		if ( temp.eof() ) { break ; }
		file.write((char *) this, sizeof(MEMBER)) ;
	}
	file.close() ;
	temp.close() ;
}


//*****************************************************
//THIS FUNCTION UPDATE RECORD FOR THE GIVEN MEMBER CODE
//*****************************************************

void MEMBER :: update_book(int mcode, int tcode, int d1, int m1, int y1)
{
	fstream file ;
	file.open("MEMBER.DAT", ios::in) ;
	fstream temp ;
	temp.open("temp.dat", ios::out) ;
	file.seekg(0,ios::beg) ;
	while ( !file.eof() )
	{
		file.read((char *) this, sizeof(MEMBER)) ;
		if ( file.eof() ) { break ; }
		if ( memcode == mcode )
		{
			bookcode = tcode ;
			dd = d1 ; mm = m1 ; yy = y1 ;
			temp.write((char *) this, sizeof(MEMBER)) ;
		}
		else { temp.write((char *) this, sizeof(MEMBER)) ; }
	}
	file.close() ;
	temp.close() ;
	file.open("MEMBER.DAT", ios::out) ;
	temp.open("temp.dat", ios::in) ;
	temp.seekg(0,ios::beg) ;
	while ( !temp.eof() )
	{
		temp.read((char *) this, sizeof(MEMBER)) ;
		if ( temp.eof() ) { break ; }
		file.write((char *) this, sizeof(MEMBER)) ;
	}
	file.close() ;
	temp.close() ;
}


//*****************************************************
//THIS FUNCTION MODIFY RECORD FOR THE GIVEN MEMBER CODE
//*****************************************************

void MEMBER :: modify(int mcode, char mname[26], char mphone[11], char maddress[33])
{
	fstream file ;
	file.open("MEMBER.DAT", ios::in) ;
	fstream temp ;
	temp.open("temp.dat", ios::out) ;
	file.seekg(0,ios::beg) ;
	while ( !file.eof() )
	{
		file.read((char *) this, sizeof(MEMBER)) ;
		if ( file.eof() ) { break ; }
		if ( memcode == mcode )
		{
			strcpy(name,mname) ; strcpy(phone,mphone) ; strcpy(address,maddress) ;
			temp.write((char *) this, sizeof(MEMBER)) ;
		}
		else { temp.write((char *) this, sizeof(MEMBER)) ; }
	}
	file.close() ;
	temp.close() ;
	file.open("MEMBER.DAT", ios::out) ;
	temp.open("temp.dat", ios::in) ;
	temp.seekg(0,ios::beg) ;
	while ( !temp.eof() )
	{
		temp.read((char *) this, sizeof(MEMBER)) ;
		if ( temp.eof() ) { break ; }
		file.write((char *) this, sizeof(MEMBER)) ;
	}
	file.close() ;
	temp.close() ;
}


//**************************************************************
//THIS FUNCTION ADD RECORD IN THE FILE FOR THE GIVEN MEMBER CODE
//**************************************************************

void MEMBER :: add_mem(int mcode, int bcode, char mname[26], char maddress[33], char mphone[11], int d1, int m1, int y1)
{
	ofstream file ;
	file.open("MEMBER.DAT", ios::app) ;
	memcode = mcode ; bookcode = bcode ;
	strcpy(name,mname) ; strcpy(address,maddress) ; strcpy(phone,mphone) ;
	dd = d1 ; mm = m1 ; yy = y1 ;
	file.write((char *) this, sizeof(MEMBER)) ;
	file.close() ;
}


//**********************************************************
//THIS FUNCTION DISPLAY THE RECORD FOR THE GIVEN MEMBER CODE
//**********************************************************

void MEMBER :: display(int mcode)
{
	ifstream file ;
	file.open("MEMBER.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	while (file.read((char *) this, sizeof(MEMBER)))
	{
		if (memcode == mcode)
		{
			gotoxy(5,3) ; cout <<"Member Code # " <<mcode ;
			gotoxy(5,4) ; cout <<"~~~~~~~~~~~~~~~~~" ;
			gotoxy(5,6) ; cout <<"Name    : " <<name ;
			gotoxy(5,7) ; cout <<"Phone   : " <<phone ;
			gotoxy(5,8) ; cout <<"Address : " <<address ;
			break ;
		}
	}
	file.close() ;
}


//*********************************************
//THIS FUNCTION DISPLAY THE LIST OF THE MEMBERS
//*********************************************

void MEMBER :: list(void)
{
	system("cls") ;
	BOOK B ;
	int row = 4 , found=0, flag=0 ;
	char ch ;

	gotoxy(1,2) ; printf("                               LIST OF MEMBERS                                ") ;
	gotoxy(1,3) ; printf(" CODE BOOK CODE   NAME                         PHONE                  ADDRESS ") ;
	ifstream file ;
	file.open("MEMBER.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	while (file.read((char *) this, sizeof(MEMBER)))
	{
		flag = 0 ;

		found = 1 ;
		gotoxy(2,row) ;  cout <<memcode ;
		gotoxy(10,row) ; cout <<bookcode ;
		gotoxy(19,row) ; cout <<name ;
		gotoxy(48,row) ; cout <<phone ;
		gotoxy(71,row) ; cout <<address ;

		gotoxy(7,row+1) ;
		if (bookcode == 0) {printf("BOOK NAME: (No Book Issued)") ; }
		else
		{
			printf("BOOK NAME: %s",B.bookname(bookcode)) ;
			gotoxy(42,row+1) ;printf("Date of return: ") ;
			printf("%d/%d/%d",dd,mm,yy) ;
		}

		if ( row == 22 )
		{
			flag = 1 ;
			row = 6 ;
			gotoxy(1,25) ; cout <<"Press any key to continue or Press <ESC> to exit" ;
			ch = getch() ;
			if (ch == 27) { break ; }
			system("cls") ;


            gotoxy(1,2) ; printf("                               LIST OF MEMBERS                                ") ;
            gotoxy(1,3) ; printf(" CODE BOOK CODE   NAME                         PHONE                  ADDRESS ") ;
		}
		else { row = row + 2 ; }
	}
	if (!found) { gotoxy(5,10) ; cout <<"\7Records not found" ; }
	if (!flag) { gotoxy(1,25) ; cout <<"Press any key to continue..." ; getche() ; }

	file.close () ;
}

//*******************************************************
//THIS FUNCTION GIVES DATA TO ADD RECORD IN THE BOOK FILE
//*******************************************************

void WORKING :: add_book(void)
{
	if (!reccount())  // MEMBER FUNCTION OF BOOK
	{
		add_new_book(0,"null","null",0,0) ;
		BOOK::delete_rec(0) ;
	}
	char ch ;
	int tcode, tcopies, tavail ;
	char tname[33], tauthor[26] ;
	do
	{
		int found=0, valid=0 ;
		int tc ;
		char t[10], t1[10] ;
		system("cls") ;

		gotoxy(72,1) ; cout <<"<0>=Exit" ;
		gotoxy(29,3) ; cout <<"ADDITION OF THE BOOKS" ;
		gotoxy(5,25) ; cout <<"Enter code no. of the book" ;
		gotoxy(5,6) ;  cout <<"Code no. " ;
		gets(t) ;
		tc = atoi(t) ;
		tcode = tc ;
		if (tcode == 0) { return ; }
		if (book_found(tcode))
		{
			found = 1 ;
			gotoxy(19,9) ;  cout <<bookname(tcode) ;
			gotoxy(19,11) ; cout <<authorname(tcode) ;
		}
		gotoxy(5,9) ;  cout <<"Book Name   : " ;
		gotoxy(5,11) ; cout <<"Author Name : " ;
		gotoxy(5,13) ; cout <<"Copies      : " ;
		valid = 0 ;
		while (!valid && !found)
		{
			valid = 1 ;
			gotoxy(5,25) ;printf("Enter the name of the book") ;
			gotoxy(19,9) ; clreol() ; gotoxy(19,9) ; gets(tname) ; strupr(tname) ;
			if (tname[0] == '0') { return ; }
			if (strlen(tname) < 1 || strlen(tname) > 32)
			{
				valid = 0 ; gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
                printf("\7Enter correctly (Range: 1..32)") ;
                getch() ;
			}
		}
		valid = 0 ;
		while (!valid && !found)
		{
			valid = 1 ;
			gotoxy(5,25) ; printf("Enter the author's name of the book") ;
			gotoxy(19,11) ; clreol() ; gotoxy(19,11) ; gets(tauthor) ; strupr(tauthor) ;
			if (tauthor[0] == '0') { return ; }
			if (strlen(tauthor) < 1 || strlen(tauthor) > 25)
			{
				valid = 0 ; gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
                printf("\7Enter correctly (Range: 1..25)") ;
                getch() ;
			}
		}
		valid = 0 ;
		while (!valid)
		{
			valid = 1 ;
			gotoxy(5,25) ;printf("Enter no. of copies of book to be added") ;
			gotoxy(19,13) ; clreol() ; gotoxy(19,13) ; gets(t) ; tc = atoi(t) ; tcopies = tc ;
			if (t[0] == '0') { return ; }
			if (tcopies < 1 || tcopies > 50)
			{
				valid = 0 ; gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
                printf("\7Enter correctly") ;
                getch() ;
			}
		}
		tavail = available(tcode) + tcopies ;
		tcopies = no_of_copies(tcode) + tcopies ;
		gotoxy(5,25) ;
		do
		{
			gotoxy(5,15) ; cout <<"Do you want to save (y/n) : " ;
			ch = getche() ; ch = toupper(ch) ;
		} while (ch != 'Y' && ch != 'N') ;

		if (ch == 'Y')
		{
			if (found) { update_copies(tcode,tcopies,tavail) ; }
			else { add_new_book(tcode,tname,tauthor,tcopies,tavail) ; }
		}
		do
		{
			gotoxy(5,17) ; cout <<"Do you want to add more (y/n) : " ;
			ch = getche() ; ch = toupper(ch) ;
		} while (ch != 'Y' && ch != 'N') ;
	} while (ch == 'Y') ;

}


//*********************************************************
//THIS FUNCTION GIVES DATA TO ADD RECORD IN THE MEMBER FILE
//*********************************************************

void WORKING :: add_member(void)
{
    char ch ;
	int mcode, bcode ;
	char mname[26], mphone[11], maddress[33] ;
	int d1, m1, y1 ;
	mcode = lastcode() ;
	if (mcode == 0)
	{
		add_mem(mcode,0,"null","null","null",0,0,0) ;
		MEMBER::delete_rec(mcode) ;
	}
	mcode++ ;
	do
	{
	    int valid=0 ;
		system("cls") ;

		gotoxy(72,1) ; cout <<"<0>=Exit" ;
		gotoxy(28,3) ; cout <<"ADDITION OF THE MEMBERS" ;
		gotoxy(5,6) ;  cout <<"Member Code # " <<mcode ;
		gotoxy(5,9) ;  cout <<"Name    : " ;
		gotoxy(5,11) ; cout <<"Phone   : " ;
		gotoxy(5,13) ; cout <<"Address : " ;
		do
		{
			valid = 1 ;
			gotoxy(5,25) ;printf("Enter the name of the New Member") ;
			gotoxy(15,9) ; clreol() ; gotoxy(15,9) ; gets(mname) ; strupr(mname) ;
			if (mname[0] == '0') { return ; }
			if (strlen(mname) < 1 || strlen(mname) > 25)
			{
				valid = 0 ; gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
               printf("\7Enter correctly (Range: 1..25)") ;
                 getch() ;
			}
		} while (!valid) ;
		do
		{
			valid = 1 ;
			gotoxy(5,25) ;printf("Enter Phone no. of the Member or Press <ENTER> for none") ;
			gotoxy(15,11) ; clreol() ; gotoxy(15,11) ; gets(mphone) ;
			if ((strlen(mphone) == 1) && (mphone[0] == '0')) { return ; }
			if ((strlen(mphone) < 7 && strlen(mphone) > 0) || (strlen(mphone) > 11))
            {
                valid = 0 ; gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
               printf("\7Enter correctly") ;
                 getch() ;
            }
		} while (!valid) ;
		if (strlen(mphone) == 0) { strcpy(mphone,"-") ; }
		do
		{
			valid = 1 ;
			gotoxy(5,25) ;printf("Enter the address of the New Member") ;
			gotoxy(15,13) ; clreol() ; gotoxy(15,13) ; gets(maddress) ; strupr(maddress) ;
			if (maddress[0] == '0') { return ; }
			if (strlen(maddress) < 1 || strlen(maddress) > 32)
			{
			    valid = 0 ; gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
               printf("\7Enter correctly (Range: 1..32)") ;
                 getch() ;
            }
		} while (!valid) ;
		gotoxy(5,25) ;
		do
		{
			gotoxy(5,17) ; cout <<"Do you want to save (y/n) : " ;
			ch = getche() ;
			ch = toupper(ch) ;
			if (ch == '0') { return ; }
		} while (ch != 'Y' && ch != 'N') ;
		if (ch == 'Y')
		{
			bcode = 0 ;
			d1 = 0 ; m1 = 0 ; y1 = 0 ;
			add_mem(mcode,bcode,mname,maddress,mphone,d1,m1,y1) ;
			mcode++ ;
		}
		do
		{
			gotoxy(5,19) ; cout <<"Do you want to add more (y/n) : " ;
			ch = getche() ;
			ch = toupper(ch) ;
			if (ch == '0') { return ; }
		} while (ch != 'Y' && ch != 'N') ;
	} while (ch == 'Y') ;

}


//*****************************
//THIS FUNCTION ISSUES THE BOOK
//*****************************

void WORKING :: issue_book(void)
{
	BOOK B ; MEMBER M ; DATES D ;
	char t1code[33], ch ;
	int t2code=0, tcode=0, mcode=0 ;
	int valid ;
	int d1, m1, y1 ;
	time_t t = time(0);
	struct tm * now = localtime( & t );
	d1 = now->tm_mday ; m1 = now->tm_mon + 1 ; y1 = now->tm_year + 1900 ;
	do
	{
		valid = 1 ;
		while (1)
		{
			system("cls") ;

			gotoxy(5,2) ;  cout <<"Date : " <<d1 <<"/" <<m1 <<"/" <<y1 ;
			gotoxy(72,1) ; cout <<"<0>=Exit" ;
			gotoxy(5,5) ;  cout <<"Enter Code or Name of the Book to be issued" ;
			gotoxy(5,6) ;  cout <<"                  or                       " ;
			gotoxy(5,7) ;  cout <<"Press <ENTER> for help  " ;
			gets(t1code) ;
			if (t1code[0] == '0') { return ; }
			if (strlen(t1code) == 0) { B.list() ; }
			else { break ; }
		}
		t2code = atoi(t1code) ; tcode = t2code ;
		if ((tcode == 0 && !bookname_found(t1code)) || (tcode != 0 && !book_found(tcode)))
		{
			valid = 0 ;
			gotoxy(5,10) ; cout <<"\7Record not found" ;
			gotoxy(5,11) ; cout <<"Press <ESC> to exit or any other key to continue..." ;
			ch = getch() ;
			if (ch == 27) { return ; }
		}
	} while (!valid) ;
	if (tcode == 0) { tcode = bookcodeof(t1code) ; }
	if (!available(tcode))
	{
		gotoxy(5,10) ; cout <<"\7Sorry! Book (" <<bookname(tcode) <<") is not available" ;
		gotoxy(5,11) ; cout <<"Kindly issue any other Book" ;
		gotoxy(5,12) ; cout <<"See List of Books" ;
		getch() ;
		return ;
	}
	do
	{
		valid = 1 ;
		while (1)
		{
			system("cls") ;

			gotoxy(72,01) ; cout <<"<0>=Exit" ;
			gotoxy(5,2) ;   cout <<"Date : " <<d1 <<"/" <<m1 <<"/" <<y1 ;
			gotoxy(5,5) ;   cout <<"Book Name: " <<bookname(tcode) ;
			gotoxy(5,7) ;   cout <<"Enter Code no. of the Member" ;
			gotoxy(5,8) ;   cout <<"            or              " ;
			gotoxy(5,9) ;   cout <<"Press <ENTER> for help  " ;
			gets(t1code) ;
			if (t1code[0] == '0') { return ; }
			if (strlen(t1code) == 0) { M.list() ; }
			else { break ; }
		}
		t2code = atoi(t1code) ;
		mcode = t2code ;
		if (mcode == 0)
		{
		    valid = 0 ; gotoxy(5,25) ;
           printf("\7Enter Correctly") ;  getch() ;
        }
		if (!member_found(mcode) && valid)
		{
			valid = 0 ; gotoxy(5,13) ;
			cout <<"\7Record not found" ; gotoxy(5,14) ;
			cout <<"Press <ESC> to exit or any other key to continue..." ;
			ch = getch() ;
			if (ch == 27) { return ; }
		}
	} while (!valid) ;
	int tcopies, tavail ;
	tcopies = no_of_copies(tcode) ;  // member function of BOOK
	tavail  = available(tcode) - 1 ;  // member function of BOOK
	update_copies(tcode,tcopies,tavail) ;  // member function of BOOK
	D.extend_date(d1,m1,y1,7) ;
	d1 = D.day ; m1 = D.mon ; y1 = D.year ;
	update_book(mcode,tcode,d1,m1,y1) ;  // member function of MEMBER
	gotoxy(5,13) ; cout <<"\7Book is issued to " <<membername(mcode) ;
	gotoxy(5,15) ; cout <<"Date of Return : " <<d1 <<"/" <<m1 <<"/" <<y1 ;
	getch() ;

}


//*********************************************
//THIS FUNCTION RETURNS THE BOOK FOR THE MEMBER
//*********************************************

void WORKING :: return_book(void)
{
	MEMBER M ;
	char t1code[5], ch ;
	int t2code=0, mcode=0, valid ;
	int d1, m1, y1 ;
	time_t t = time(0);
	struct tm * now = localtime( & t );
	d1 = now->tm_mday ; m1 = now->tm_mon + 1 ; y1 = now->tm_year + 1900 ;
	do
	{
		valid = 1 ;
		while (1)
		{
			system("cls") ;

			gotoxy(72,01) ; cout <<"<0>=Exit" ;
			gotoxy(5,2) ;   cout <<"Date : " <<d1 <<"/" <<m1 <<"/" <<y1 ;
			gotoxy(5,7) ;   cout <<"Enter Code no. of the Member who wants to return book" ;
			gotoxy(5,8) ;   cout <<"                        or              " ;
			gotoxy(5,9) ;   cout <<"Press <ENTER> for help  " ;
			gets(t1code) ;
			if (t1code[0] == '0') { return ; }
			if (strlen(t1code) == 0) { M.list() ; }
			else { break ; }
		}
		t2code = atoi(t1code) ; mcode = t2code ;
		if (mcode == 0)
		{
		    valid = 0 ; gotoxy(5,25) ;
           printf("\7Enter Correctly") ;  getch() ;
        }
		if (!member_found(mcode) && valid)
		{
			valid = 0 ;
			gotoxy(5,13) ; cout <<"\7Record not found" ;
			gotoxy(5,14) ; cout <<"Press <ESC> to exit or any other key to continue..." ;
			ch = getch() ;
			if (ch == 27) { return ; }
		}
		if (!issued(mcode) && valid)
		{
			valid = 0 ;
			gotoxy(5,13) ; cout <<"\7Member have no book to return" ;
			gotoxy(5,14) ; cout <<"Press <ESC> to exit or any other key to continue..." ;
			ch = getch() ;
			if (ch == 27) { return ; }
		}
	} while (!valid) ;
	int bcode, tcopies, tavail ;
	bcode = issued(mcode) ;
	gotoxy(5,13) ; cout <<"Book Code : " <<bcode ;
	gotoxy(5,14) ; cout <<"Book Name : " <<bookname(bcode) ;
	tcopies = no_of_copies(bcode) ;
	tavail = available(bcode) + 1 ;
	int f ;
	f = fine(mcode) ;
	if (f != 0)
	{
		gotoxy(5,16) ; cout <<"You have to pay a fine of Taka- " <<f ;
		gotoxy(5,17) ; cout <<"Please do not delay the Return of Book again" ;
	}
	update_copies(bcode,tcopies,tavail) ;
	update_book(mcode,0,0,0,0) ;
	gotoxy(5,19) ; cout <<"\7Book has been returned" ;
	getch() ;

}


//**************************************************
//THIS FUNCTION GIVES DATA TO MODIFY THE BOOK RECORD
//**************************************************

void WORKING :: modify_book(void)
{
	BOOK B ;
	char t1code[5], tname[33], tauthor[26], *t1, ch ;
	int t2code=0, tcode=0 ;
	int valid ;
	do
	{
		valid = 1 ;
		while (1)
		{
			system("cls") ;


			gotoxy(72,1) ; cout <<"<0>=Exit" ;
			gotoxy(5,5) ;  cout <<"Enter Code or Name of the Book to be modified" ;
			gotoxy(5,6) ;  cout <<"                  or                       " ;
			gotoxy(5,7) ;  cout <<"Press <ENTER> for help  " ;
			gets(t1code) ;
			if (t1code[0] == '0') { return ; }
			if (strlen(t1code) == 0) { B.list() ; }
			else { break ; }
		}
		t2code = atoi(t1code) ;
		tcode = t2code ;
		if ((tcode == 0 && !bookname_found(t1code)) || (tcode != 0 && !book_found(tcode)))
		{
			valid = 0 ;
			gotoxy(5,10) ; cout <<"\7Record not found" ;
			gotoxy(5,11) ; cout <<"Press <ESC> to exit or any other key to continue..." ;
			ch = getch() ;
			if (ch == 27) { return ; }
		}
	} while (!valid) ;
	if (tcode == 0) { tcode = bookcodeof(t1code) ; }
	system("cls") ;


	gotoxy(72,1) ; cout <<"<0>=Exit" ;
	BOOK::display(tcode) ;
	do
	{

		gotoxy(5,13) ;printf("Do you want to modify this record (y/n)") ;
		ch = getch() ; ch = toupper(ch) ;
		if (ch == '0') { return ; }
	} while (ch != 'Y' && ch != 'N') ;
	if (ch == 'N') { return ; }
	gotoxy(5,16) ; cout <<"Book Name   : " ;
	gotoxy(5,17) ; cout <<"Author Name : " ;
	do
	{
		valid = 1 ;
		gotoxy(5,25) ; printf("Enter the name of the book or <ENTER> for no change") ;
		gotoxy(19,16) ; clreol() ; gotoxy(19,16) ; gets(tname) ; strupr(tname) ;
		if (tname[0] == '0') { return ; }
		if (strlen(tname) > 32)
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
           printf("\7Enter correctly (Range: 1..32)") ;
			 getch() ;
		}
	} while (!valid) ;
	if (strlen(tname) == 0) { strcpy(tname,bookname(tcode)) ; }
	do
	{
		valid = 1 ;
		gotoxy(5,25) ; printf("Enter the author's name or <ENTER> for no change") ;
		gotoxy(19,17) ; clreol() ; gotoxy(19,17) ; gets(tauthor) ; strupr(tauthor) ;
		if (tauthor[0] == '0') { return ; }
		if (strlen(tauthor) > 25)
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
           printf("\7Enter correctly (Range: 1..25)") ;
			 getch() ;
		}
	} while (!valid) ;
	if (strlen(tauthor) == 0) { strcpy(tauthor,authorname(tcode)) ; }
	gotoxy(5,25) ;
	do
	{
		gotoxy(5,20) ; cout <<"Do you want to save changes (y/n)" ;
		ch = getch() ; ch = toupper(ch) ;
		if (ch == '0') { return ; }
	} while (ch != 'Y' && ch != 'N') ;
	if (ch == 'N') { return ; }
	BOOK::modify(tcode,tname,tauthor) ;
	gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
	printf("\7Record Modified") ;
	getch() ;
}


//****************************************************
//THIS FUNCTION GIVES DATA TO MODIFY THE MEMBER RECORD
//****************************************************

void WORKING :: modify_member(void)
{
	MEMBER M ;
	char m1code[10], mname[26], mphone[11], maddress[33], ch ;
	int m2code=0, mcode=0 ;
	int valid ;
	do
	{
		valid = 1 ;
		while (1)
		{
			system("cls") ;


			gotoxy(72,1) ; cout <<"<0>=Exit" ;
			gotoxy(5,7) ;  cout <<"Enter Code no. of the Member to be Modify" ;
			gotoxy(5,8) ;  cout <<"                        or              " ;
			gotoxy(5,9) ;  cout <<"Press <ENTER> for help  " ;
			gets(m1code) ;
			m2code = atoi(m1code) ;
			mcode = m2code ;
			if (m1code[0] == '0') { return ; }
			if (strlen(m1code) == 0) { M.list() ; }
			else { break ; }
		}
		if (mcode == 0)
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
           printf("\7Enter Correctly") ;
			 getch() ;
		}
		if (valid && !member_found(mcode))
		{
			valid = 0 ;
			gotoxy(5,13) ; cout <<"\7Record not found" ;
			gotoxy(5,14) ; cout <<"Press <ESC> to exit or any other key to continue..." ;
			ch = getch() ;
			if (ch == 27) { return ; }
		}
	} while (!valid) ;
	system("cls") ;


	gotoxy(72,1) ; cout <<"<0>=Exit" ;
	MEMBER::display(mcode) ;
	do
	{

		gotoxy(5,10) ;printf("Do you want to modify this record (y/n)") ;
		ch = getch() ; ch = toupper(ch) ;
		if (ch == '0') { return ; }
	} while (ch != 'Y' && ch != 'N') ;
	if (ch == 'N') { return ; }
	gotoxy(5,13) ; cout <<"Name    : " ;
	gotoxy(5,14) ; cout <<"Phone   : " ;
	gotoxy(5,15) ; cout <<"Address : " ;
	do
	{
		valid = 1 ;
		gotoxy(5,25) ; printf("Enter the name of the member or <ENTER> for no change") ;
		gotoxy(19,13) ; clreol() ; gotoxy(19,13) ; gets(mname) ; strupr(mname) ;
		if (mname[0] == '0') { return ; }
		if (strlen(mname) > 25)
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
           printf("\7Enter correctly (Range: 1..25)") ;
			 getch() ;
		}
	}
	while (!valid) ;
	if (strlen(mname) == 0) { strcpy(mname,membername(mcode)) ; }
	do
	{
		valid = 1 ;
		gotoxy(5,25) ; printf("Enter the Phone no. of Member or <ENTER> for no change") ;
		gotoxy(19,14) ; clreol() ; gotoxy(19,14) ; gets(mphone) ;
		if (mphone[0] == '0') { return ; }
		if ((strlen(mphone) < 7 && strlen(mphone) > 0) || (strlen(mphone) > 9))
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
           printf("\7Enter correctly") ;
			 getch() ;
		}
	} while (!valid) ;
	if (strlen(mphone) == 0) { strcpy(mphone,memberphone(mcode)) ; }
	do
	{
		valid = 1 ;
		gotoxy(5,25) ; printf("Enter the address of the member or <ENTER> for no change") ;
		gotoxy(19,15) ; clreol() ; gotoxy(19,15) ; gets(maddress) ; strupr(maddress);
		if(maddress[0]='0') { return ; }
		if (strlen(maddress) > 32)
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
           printf("\7Enter correctly (Range: 1..32)") ;
			 getch() ;
		}
	} while (!valid) ;
	if (strlen(maddress) == 0) { strcpy(maddress,memberaddress(mcode)) ; }
	gotoxy(5,25) ;
	do
	{
		gotoxy(5,20) ; cout <<"Do you want to save changes (y/n)" ;
		ch = getch() ; ch = toupper(ch) ;
		if (ch == '0') { return ; }
	} while (ch != 'Y' && ch != 'N') ;
	if (ch == 'N') { return ; }
    if (ch == 'Y') { MEMBER::modify(mcode,mname,mphone,maddress) ; }
	gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
	printf("\7Record Modified") ;
	getch() ;
}


//*******************************************************
//THIS FUNCTION GIVES BOOK CODE TO DELETE THE BOOK RECORD
//*******************************************************

void WORKING :: delete_book(void)
{
	BOOK B ;
	char t1code[5], tname[33], tauthor[26], ch ;
	int t2code=0, tcode=0 ;
	int valid ;
	do
	{
		valid = 1 ;
		while (1)
		{
			system("cls") ;


			gotoxy(72,1) ; cout <<"<0>=Exit" ;
			gotoxy(5,5) ;  cout <<"Enter Code or Name of the Book to be Deleted" ;
			gotoxy(5,6) ;  cout <<"                  or                       " ;
			gotoxy(5,7) ;  cout <<"Press <ENTER> for help  " ;
			gets(t1code) ;
			if (t1code[0] == '0') { return ; }
			if (strlen(t1code) == 0) { B.list() ; }
			else { break ; }
		}
		t2code = atoi(t1code) ; tcode = t2code ;
		if ((tcode == 0 && !bookname_found(t1code)) || (tcode != 0 && !book_found(tcode)))
		{
			valid = 0 ;
			gotoxy(5,10) ; cout <<"\7Record not found" ;
			gotoxy(5,11) ; cout <<"Press <ESC> to exit or any other key to continue..." ;
			ch = getch() ;
			if (ch == 27) { return ; }
		}
	} while (!valid) ;
	if (tcode == 0) { tcode = bookcodeof(t1code) ; }
	system("cls") ;


	gotoxy(72,1) ; cout <<"<0>=Exit" ;
	BOOK::display(tcode) ;
	do
	{

		gotoxy(5,13) ;printf("Do you want to delete this record (y/n)") ;
		ch = getch() ; ch = toupper(ch) ;
		if (ch == '0') { return ; }
	} while (ch != 'Y' && ch != 'N') ;
	if (ch == 'N') { return ; }
	int tavail, tcopies ;
	tavail = available(tcode) ;
	tcopies = no_of_copies(tcode) ;
	if (tavail != tcopies)
	{
		gotoxy(5,15) ; cout <<"\7Record cannot be deleted. This book is issued." ;
		getch() ;
		return ;
	}
	BOOK::delete_rec(tcode) ;
	gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
	printf("\7Record Deleted") ;
	getch() ;
}


//***********************************************************
//THIS FUNCTION GIVES MEMBER CODE TO DELETE THE MEMBER RECORD
//***********************************************************

void WORKING :: delete_member(void)
{
	MEMBER M ;
	char m1code[5], mname[26], mphone[11], maddress[33], ch ;
	int m2code=0, mcode=0 ;
	int valid ;
	do
	{
		valid = 1 ;
		while (1)
		{
			system("cls") ;


			gotoxy(72,1) ; cout <<"<0>=Exit" ;
			gotoxy(5,7) ;  cout <<"Enter Code no. of the Member to be Deleted" ;
			gotoxy(5,8) ;  cout <<"                        or              " ;
			gotoxy(5,9) ;  cout <<"Press <ENTER> for help  " ;
			gets(m1code) ;
			m2code = atoi(m1code) ; mcode = m2code ;
			if (m1code[0] == '0') { return ; }
			if (strlen(m1code) == 0) { M.list() ; }
			else { break ; }
		}
		if (mcode == 0)
		{
			valid = 0 ;
			gotoxy(5,25) ;
           printf("\7Enter Correctly") ;
			 getch() ;
		}
		if (valid && !member_found(mcode))
		{
			valid = 0 ;
			gotoxy(5,13) ; cout <<"\7Record not found" ;
			gotoxy(5,14) ; cout <<"Press <ESC> to exit or any other key to continue..." ;
			ch = getch() ;
			if (ch == 27) { return ; }
		}
	} while (!valid) ;
	system("cls") ;


	gotoxy(72,1) ; cout <<"<0>=Exit" ;
	MEMBER::display(mcode) ;
	do
	{

		gotoxy(5,10) ;printf("Do you want to Delete this record (y/n)") ;
		ch = getch() ; ch = toupper(ch) ;
		if (ch == '0') { return ; }
	} while (ch != 'Y' && ch != 'N') ;
	if (ch == 'N') { return ; }
	if (issued(mcode))
	{
		gotoxy(5,15) ; cout <<"\7Record cannot be delete. Member has a book" ;
		getch() ;
		return ;
	}
	MEMBER::delete_rec(mcode) ;
	gotoxy(5,25) ; clreol() ; gotoxy(5,25) ;
	printf("\7Record Deleted") ;
	getch() ;
}



//************************************************
//MAIN FUNCTION CALLING INTRODUCTION AND MAIN MENU
//************************************************

main(void)
{
	MENU menu ;
	menu.introduction() ;
	menu.main_menu() ;
}
