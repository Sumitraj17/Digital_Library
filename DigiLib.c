#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<unistd.h>

struct customer_id  //customer struct.
{
    long int cust_Id;
	char pass_Id[26];
};
typedef struct customer_id cust;

struct user_node   //new-user struct
{
	struct data{
		char name[21];
		long long int phn_no;
		char dob[10];
		int borrowing;
		char fines[5];
	}d;
	struct user_node* link;
};
typedef struct user_node nd;

struct library   //library data.
{
    char title[200];
    char author[100];
    int id;
    int stock;
};
typedef struct library lib;

struct borrowing{   //borrowing data.
	char user_name[21];
	char book_name[50],date_of_borrowing[21];
};
typedef struct borrowing bd;

void customer();  //Customer functions.
void borrow_history();
void Book_Available();
void existing_cust();
int verify_cust_id(int);
void update_files(nd*);
nd* insert_user_node(nd*);
void outstanding_fine(char*);
int update_user_data(char*);

void librarian();  //Librarian functions.
void entry();
void borrow_book(char*);
void customer_data();
void new_cust_count(nd*);
void fine_history(FILE*);
void add_fine(FILE*);
void fine_management();

nd* first=NULL;

int main()
{
    printf("\xcd\xcd\xcd\xcd WELCOME \xcd\xcd\xcd\xcd\n\n");
    nd* head=NULL;
    int ch;
    while(1)
    {
        printf("\xcd\xcd\xcd\xcd 1.Customer\t2.Librarian   3.Exit \xcd\xcd\xcd\xcd\n\n");
        scanf("%d",&ch);
        switch (ch)
        {
        case 1:	printf("\nPress any key to proceed...");
				getch();
				system("cls");
				customer();   //CALL TO THE CUSTOMER FUNCTION.
				printf("\nPress any key to proceed...");
				getch();
				system("cls");
              	break;
        case 2:	printf("\nPress any key to proceed...");
				getch();
				system("cls");
				librarian();	//CALL TO THE LIBRARIAN FUNCTION.
				printf("\nPress any key to proceed...");
				getch();
				system("cls");
				break;
        default:printf("END OF PROCESS\n\n");
				exit(0);
        }
    }

}

//Customer...

void customer()
{
    printf("\xcd\xcd\xcd\xcd WELCOME TO THE LIBRARY \xcd\xcd\xcd\xcd\n\n");
    int c;
    //nd* head=NULL;
    while(1)
    {
        printf("\xcd\xcd\xcd\xcd 1.New_Customer\t2.Existing_Customer\t3.Return_Back \xcd\xcd\xcd\xcd\n\n");
        scanf("%d",&c);
        switch(c)
        {
            case 1: printf("\nPress any key to proceed...");
					getch();
					system("cls");
					first=insert_user_node(first);  // NEW USER
                    break;
            case 2:	printf("\nPress any key to proceed...");
					getch();
					system("cls");
					existing_cust();  //EXISTING USER.
					break;              
            default: return;        
        }
    }
}

nd* insert_user_node(nd* h)		// NEW USER FUNCTION.
{
	nd* t=(nd*)malloc(sizeof(nd));
	printf("Name -- ");
	scanf("%s",(t->d).name);
	printf("Contact_No -- ");
	scanf("%lld",&((t->d).phn_no));
	printf("DOB{DD/MM/YYYY}-- ");
	scanf("%s",(t->d).dob);
	(t->d).borrowing=0;
	strcpy((t->d).fines,"000");
	t->link=NULL;
	update_files(t);
	printf("\xcd\xcd\xcd\xcd NEW DATA STORED \xcd\xcd\xcd\xcd\n\n");
	srand(time(0));
	int m=8;
	cust c;
	c.cust_Id=0;
	for(int i=0;i<m;i++)
	{
		c.cust_Id=((c.cust_Id)*10)+(rand()%m);//GENERATION OF CUSTOMER_ID.
	}
	printf("\xcd\xcd\xcd\xcd YOUR CUSTOMER_ID:- %ld \xcd\xcd\xcd\xcd\n",c.cust_Id);
	//strcat()
	strcpy(c.pass_Id,((t->d).name));
	strcat(c.pass_Id,((t->d).dob));
	printf("\xcd\xcd\xcd\xcd YOUR NAME_ID:- %s \xcd\xcd\xcd\xcd\n\n",c.pass_Id);
	FILE* fp=fopen("customer.txt","a+");
	fprintf(fp,"%s %ld ",c.pass_Id,c.cust_Id);
	fclose(fp);
	if(h==NULL)
	{
		return t;	
	}
	t->link=h;
	return t;
}

int verify_cust_id(int n)
{
	if(n==1)
	{
		int x=2;
		while(x>=1)
		{
			printf("ENTER YOUR CUSTOMER_ID[8]: ");
			char c[21],d[21];
			char a;
			int i=0,k=0;
			for(i=0;i<8;i++)
			{
				a=getch();
				if(a==13)
				{
					break;
				}
				else if(a==8)
				{
					printf("\b");
					printf(" ");
					i-=2;
					k=1;
				}
				else{
					if(k==1)
					{
						printf("\b");
					}
					printf("*");
					c[i]=a;
					k=0;
				}
			}
			c[i]='\0';
			scanf("%s",c);
			FILE* f=fopen("customer.txt","r");
			while(feof(f)==0)
			{
				fscanf(f,"%s",d);
				if(strcmp(c,d)==0)
				{
					printf("\t\tVERIFICATION COMPLETED\n");
					return 1;
				}
			}
			fclose(f);
			printf("\xcd\xcd\xcd\xcd Invalid Credentials...Attempts left: %d \xcd\xcd\xcd\xcd\n",x);
			x--;
		}
		printf("NO ATTEMPTS LEFT\n");
	}
	else{
		int x=2;
		while(x>=1)
		{
			printf("ENTER YOUR NAME_ID:  ");
			char c[21],d[21];
			char a;
			int i=0,k=0;
			for(i=0;i<21;i++)
			{
				a=getch();
				if(a==13)
				{
					break;
				}
				else if(a==8)
				{
					printf("\b");
					printf(" ");
					i-=2;
					k=1;
				}
				else{
					if(k==1)
					{
						printf("\b");
					}
					printf("*");
					c[i]=a;
					k=0;
				}
			}
			c[i]='\0';
			FILE* f=fopen("customer.txt","r");
			while(feof(f)==0)
			{
				fscanf(f,"%s",d);
				if(strcmp(c,d)==0)
				{
					printf("\t\tVERIFICATION COMPLETE\n\n");
					printf("Press any key to proceed...");
					getch();
					system("cls");
					return 1;
				}
			}
			fclose(f);
			printf("\xcd\xcd\xcd\xcd Invalid Credentials...Attempts left: %d \xcd\xcd\xcd\xcd\n",x);
			x--;
		}
		printf("NO ATTEMPTS LEFT\n");
	}
	return 0;
}

void existing_cust()  //EXISTING CUSTOMER.
{
	printf("\xcd\xcd\xcd\xcd 1.Verify through Customer_Id\t2.Verify through Name_Id \xcd\xcd\xcd\xcd\n");
	int c;
	scanf("%ld",&c);
	switch(c)
	{
		case 1:if(verify_cust_id(c)==0)
				{
					return;
				}
				break;
		case 2:if(verify_cust_id(c)==0)
				{
					return;		
				}		
				break;
	}
	printf("Enter your Name:  ");
	char p[21];
	scanf("%s",p);
	while(1)
	{
		int c;
		printf("\xcd\xcd\xcd\xcd 1.Books_Available\t2.Book_Borrow\t3.Outstanding_fine\t4.Return_Back \xcd\xcd\xcd\xcd\n\n");
		scanf("%d",&c);
		switch(c)
		{
			case 1:
					system("cls");
					printf("\xcd\xcd\xcd\xcd DISPLAYING THE LIST \xcd\xcd\xcd\xcd\n\n");
					Book_Available();
					break;
			case 2:	system("cls");
					borrow_book(p);
					break;
			case 3:system("cls");
					outstanding_fine(p);
					break;		
			default:return;		
		}
	}
}

void Book_Available()	//LIST OF BOOKS.
{
	FILE* f=fopen("book.txt","r");
	while(feof(f)==0)
	{
		long int x=ftell(f);
		int n=3;
		while(n>0)
		{
			char* q=(char*)malloc(sizeof(char)*100);
			fscanf(f,"%s",q);
			n--;
			free(q);
		}
		int s;
		fscanf(f,"%d",&s);
		if(s>9)
		{
			fseek(f,x,SEEK_SET);
			lib b;
			fscanf(f,"%s%s%d%d ",b.title,b.author,&(b.id),&(b.stock));
			printf("Book_Title: %s\n",b.title);
			printf("Book_Author: %s\n",b.author);
			printf("Book_Id: %d\n",b.id);
			printf("Book_Stock: %d\n",b.stock);
			printf("\n\n");
		}
	}
	fclose(f);
	printf("\nPress any key to proceed...");
	getch();
	system("cls");
}

void update_files(nd* t)
{
	FILE* f=NULL;
	while(f==NULL)
	{
		f=fopen("user.txt","a");
	}
	fprintf(f,"%s %lld %s %d %s ",(t->d).name,(t->d).phn_no,(t->d).dob,(t->d).borrowing,(t->d).fines);
	fclose(f);
}

void borrow_book(char* p)	//BOOK BORROW.
{
	char b[50];
	printf("Enter the book name: ");
	scanf("%s",b);
	FILE* f=fopen("book.txt","r+");
	while(feof(f)==0)
	{
		char s[50];
		fscanf(f,"%s",s);
		if(strcmp(s,b)==0)
		{
		    int n=2,m;
			while(n>0)
			{
			    char d[20];
			    fscanf(f,"%s",d);
			    n=n-1;
			}
			long int x=ftell(f);
			fscanf(f,"%d",&m);
			if(m>9)
			{
			    printf("\xcd\xcd\xcd\xcd BOOK available \xcd\xcd\xcd\xcd\n\n");
			    fseek(f,x,SEEK_SET);
			    m=m-1;
			    fprintf(f," %d",m);
			    FILE* fp=fopen("Borrow.txt","a+");
			    bd by;
			    strcpy(by.user_name,p);
			    if( update_user_data(by.user_name)){
			        strcpy(by.book_name,s);
			        printf("Enter the date of borrowing (DD/MM/YYY):  ");
			        scanf("%s",by.date_of_borrowing);
			        fprintf(fp," %s %s %s",by.user_name,by.book_name,by.date_of_borrowing);
			    }
			    else{
			        printf("\xcd\xcd\xcd\xcd USER NOT FOUND \xcd\xcd\xcd\xcd\n\n");
			    }
			    fclose(fp);
			    fclose(f);
			    printf("\xcd\xcd\xcd\xcd BOOK BORROWED \xcd\xcd\xcd\xcd\n\n");
			    printf("NOTE: BOOK SHALL BE RENEWED OR RETURNED WITHIN 15 DAYS FROM THE DATE OF BORROWING\n\n");
			    printf("\nPress any key to proceed...");
				getch();
				system("cls");
				return;
			}
			else{
			    printf("\xcd\xcd\xcd\xcd BOOK OUT OF STOCK \xcd\xcd\xcd\xcd\n");
			    fclose(f);
			    printf("\nPress any key to proceed...");
				getch();
				system("cls");
			    return;
			}
		}
	}
	printf("\xcd\xcd\xcd\xcd BOOK NOT AVAILABLE \xcd\xcd\xcd\xcd\n");
	printf("\nPress any key to proceed...");
	getch();
	system("cls");
	fclose(f);
}

int update_user_data(char* s)
{
    FILE* f=fopen("user.txt","r+");
    char* p=(char*)malloc(sizeof(char)*21);
    while(feof(f)==0)
    {
        fscanf(f,"%s",p);
        if(strcmp(p,s)==0)
        {
            int n=2,m;
            while(n>0)
            {
                char* q=(char*)malloc(sizeof(char)*21);
                fscanf(f,"%s",q);
                free(q);
                n=n-1;
            }
            long int x=ftell(f);
            fscanf(f,"%d",&m);
            m=m+1;
            fseek(f,x,SEEK_SET);
            fprintf(f," %d",m);
            free(p);
            fclose(f);
            return 1;
        }
    }
    free(p);
    fclose(f);
    return 0;
}

void outstanding_fine(char* s)  //FINES.
{
	FILE* f=fopen("user.txt","r");
	//fseek(f,0,SEEK_SET);
	while(feof(f)==0)
	{
		char* p=(char*)malloc(sizeof(char)*21);
		fscanf(f,"%s",p);
		if(strcmp(s,p)==0)
		{
			int n=3;
			while(n>=1)
			{
				char* q=(char*)malloc(sizeof(char)*11);
				fscanf(f,"%s",q);
				free(q);
				n--;
			}
			char* r=(char*)malloc(sizeof(char)*10);
			fscanf(f,"%s",r);
			printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n");
			printf("Customer_Name:  %s\n",p);
			printf("Outstanding_Fine:  %s\n\n",r);
			free(r);
		}
		free(p);
	}
	printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	fclose(f);
}

//librarian...

void librarian()
{
	char pass[]={"lib_12"};  //library password to access the addtional feature.
	char p[21],g;
	printf("Enter the password: ");
	int j=2;
	while(j)
	{
		int i=0,f=0;
		for(i=0;i<10;i++)
		{
			g=getch();
			if(g==13)
			{
				break;
			}
			else if(g==8)
			{
				printf("\b");
				printf(" ");
				i-=2;
				f=1;
			}
			else{
				if(f==1)
				{
					printf("\b");
				}
				printf("*");
				p[i]=g;
				f=0;
			}
		}
		p[i]='\0';
		if(strcmp(p,pass)==0)
		{
			printf("\xcd\xcd\xcd\xcd VERIFICATION COMPLETED \xcd\xcd\xcd\xcd\n\n");
			printf("Press any key to proceed....");
			getch();
			system("cls");
			break;
		}
		else{
			printf("\xcd\xcd\xcd\xcd INVALID PASSWORD...TRY AGAIN \xcd\xcd\xcd\xcd\n");
			printf("\n \xcd\xcd\xcd\xcd ATTEMPTS LEFT-- %d \xcd\xcd\xcd\xcd\n\n",j);
		}
		j--;
	}
    int c;
    while(1)
    {
        printf("\xcd\xcd\xcd\xcd 1.Enter Book in record\t2.Borrowing History\t3.Fine System\t4.Customers\t5.New Customers \xcd\xcd\xcd\xcd\n");
        scanf("%d",&c);
        switch(c)
        {
            case 1:
					system("cls");
					entry();
                    break;
            case 2:	system("cls");
					borrow_history();
                    break;
            case 3:	system("cls");
					fine_management();
					break;          
            case 4:	system("cls");
					customer_data();
            		break;
            case 5:	system("cls");
					new_cust_count(first);
            		break;
            default:return;        
                    
        }
    }
    
}

void borrow_history()	//BORROW HISTORY.
{
    FILE* f=fopen("Borrow.txt","r");
    while(1)
    {
        if(feof(f)!=0)
        {
            return;
        }
        bd b;
        printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
        fscanf(f,"%s %s %s",b.user_name,b.book_name,b.date_of_borrowing);
        printf("Customer-Name:  %s\nBook-Name:  %s\nDate:  %s\n\n",b.user_name,b.book_name,b.date_of_borrowing);
        printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
    }
    printf("\nPress any key to proceed...");
	getch();
	system("cls");
    fclose(f);
}

void entry()
{
	FILE* f=fopen("book.txt","a+");
    lib book;
    printf("Enter the book Title name: ");
    scanf("%s",book.title);
    printf("Enter the author name: ");
    scanf("%s",book.author);
    printf("Enter the book ID: ");
    scanf("%d",&(book.id));
    printf("Enter the total no of copies: ");
    scanf("%d",&(book.stock));
    fprintf(f,"%s %s %d %d ",book.title,book.author,(book.id),(book.stock));
	printf("\t\xcd\xcd\xcd\xcd NEW BOOK ENTERED \xcd\xcd\xcd\xcd\n\n");
	printf("\nPress any key to proceed...");
	getch();
	system("cls");
	fclose(f);
}

void customer_data()  //CUSTOMER DATA.
{
	FILE* f=fopen("user.txt","r");
	while(feof(f)==0)
	{
		nd n;
		fscanf(f,"%s%lld%s%d%s",(n.d).name,&((n.d).phn_no),(n.d).dob,&((n.d).borrowing),(n.d).fines);
		printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
		printf("Customer_Name:  %s\n",(n.d).name);
		printf("Customer_Phn_No:  %lld\n",(n.d).phn_no);
		printf("Customer_DOB:  %s\n",(n.d).dob);
		printf("No of Books Borrowed:  %d\n",(n.d).borrowing);
		printf("Outsatnding Fine:  %s\n",(n.d).fines);
	}
	printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	printf("\nPress any key to proceed...");
	getch();
	system("cls");
}

void new_cust_count(nd* h) 	//NEW CUSTOMER LIST.
{
	nd* t=h;
	int c=0;
	while(t!=NULL)
	{
		printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n");
		printf("Customer_Name: %s\n",(t->d).name);
		printf("Customer_Phn-No: %lld\n",(t->d).phn_no);
		printf("Customer_DOB: %s\n\n",(t->d).dob);
		t=t->link;
		c++;
	}
	printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
	printf("New_Customer Count: %d\n",c);
	printf("\nPress any key to proceed...");
	getch();
	system("cls");
}

void fine_history(FILE* f)  //FINE HISTORY.
{
	//FILE* f=fopen("user.txt","r");
	fseek(f,0,SEEK_SET);
	while(feof(f)==0)
	{
		char* p=(char*)malloc(sizeof(char)*21);
		fscanf(f,"%s",p);
		int n=3;
		while(n>=1)
		{
			char* q=(char*)malloc(sizeof(char)*11);
			fscanf(f,"%s ",q);
			free(q);
			n--;
		}
		char* r=(char*)malloc(sizeof(char)*10);
		fscanf(f,"%s",r);
		printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n");
		printf("Customer_Name:  %s\n",p);
		printf("Outstanding_Fine:  %s\n\n",r);
		free(r);
		free(p);
	}
	printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
}

void fine_management()
{
	int c;
	FILE* f=fopen("user.txt","r+");
	while(1)
	{
		printf("\xcd\xcd\xcd\xcd 1.Fine_History\t2.Add_Fine\t3.Return_Back \xcd\xcd\xcd\xcd\n\n");
		scanf("%d",&c);
		switch(c)
		{
			case 1:system("cls");
					fine_history(f);
					break;
			case 2:system("cls");
					add_fine(f);	
					break;
			default:return;			
		}
	}
}

void add_fine(FILE* f)
{
	printf("Enter the Customer_Id:  ");
	char* p=(char*)malloc(sizeof(char)*21);
	scanf("%s",p);
	fseek(f,0,SEEK_SET);
	while(feof(f)==0)
	{
		char* s=(char*)malloc(sizeof(char)*21);
		fscanf(f,"%s",s);
		if(strcmp(p,s)==0)
		{
			int n=3;
			while(n>=1)
			{
				char* q=(char*)malloc(sizeof(char)*11);
				fscanf(f,"%s",q);
				free(q);
				n--;
			}
			long int x=ftell(f);
			char* r=(char*)malloc(sizeof(char)*11);
			fscanf(f,"%s",r);
			int m=atoi(r);
			m=m+100;
			fseek(f,x,SEEK_SET);
			fprintf(f," %d",m);
			printf("Fine Added\n\n");
			free(p);
			free(r);
			free(s);
			return;
		}
		free(s);
	}
	free(p);
	printf("\xcd\xcd\xcd\xcd CUSTOMER NOT FOUND \xcd\xcd\xcd\xcd\n\n");
}
