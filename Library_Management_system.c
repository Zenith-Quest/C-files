#include<stdio.h>
#include<conio.h>
#include<time.h>
#include <stdlib.h> 
#include <string.h> 

struct books{
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
}b;

struct student{
    int id;
    char Name[50];
    char bookName[50];
    char date[12];
}s;

FILE *fp;

void addbook();
void booklist();
void del();
void isbook();
void isbooklist();
void displayb();

int main(){

    int ch;

    while(1){
        system("cls");
        printf("<== Library Management System ==>\n");
        printf("1.Add Book\n");
        printf("2.Available Books List\n");
        printf("3.Remove Book\n");
        printf("4.Issue Book\n");
        printf("5.Issued Book List\n");
        printf("6.Display Books\n");
        printf("0.Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch(ch){
        case 0:
            exit(0);

        case 1:
            addbook();
            break;

        case 2:
            booklist();
            break;

        case 3:
            del();
            break;

        case 4:
           isbook();
            break;

        case 5:
            isbooklist();
            break;
        case 6:
        	displayb();
        	break;
        default:
            printf("Invalid Choice...\n\n");

        }
        
    }
	printf("Press Any Key To Continue...");
    getchar();
    return 0;
}
void displayb(){
	char c;
    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date\n");
    
    fp = fopen("books.txt", "r");
    while(fscanf(fp,"%d %[^\t] %[^\t] %s",&b.id,b.bookName,b.authorName,b.date)!=EOF){
    	printf("%-10d %-30s %-20s %s\n\n",b.id,b.bookName,b.authorName,b.date);
	}
	fclose(fp);
	getch();
}

void addbook(){
	int a;
	char mydate[12];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(mydate,"%02d/%02d/%02d",tm.tm_mday, tm.tm_mon +1,tm.tm_year+1900);
	strcpy(b.date,mydate);
	fp = fopen("books.txt", "a");
top:	
	
    printf("Enter book id: ");
    scanf("%d", &b.id);

    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bookName);

    printf("Enter author name: ");
    fflush(stdin);
    gets(b.authorName);
    
    fprintf(fp,"%d\t%s\t%s\t%s\n", b.id, b.bookName, b.authorName, b.date);
    
    printf("Book Added Successfully");
    
    printf("Do you want to add more books? \n1.Yes\n2.No\n");
    scanf("%d",&a);
    if(a==1){
    	goto top;
	}
	else
    	fclose(fp);

    
}

void booklist() {
    struct books c;
    FILE *fs = fopen("issued_book.txt", "r");
    FILE *fb = fopen("booklist.txt", "w");
    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book ID", "Book Name", "Author", "Date");

    fp = fopen("books.txt", "r");

    while (fscanf(fp, "%d %[^\t] %[^\t] %s", &b.id, b.bookName, b.authorName, b.date) != EOF) {
        int isIssued = 0;
        rewind(fs); // Reset issued_book.txt to the beginning

        while (fscanf(fs, "%d %[^\t] %[^\t] %s", &c.id, c.bookName, c.authorName, c.date) != EOF) {
            if (c.id == b.id) {
                isIssued = 1;
                break;
            }
        }

        if (!isIssued) {
            fprintf(fb, "%d\t%s\t%s\t%s\n", b.id, b.bookName, b.authorName, b.date);
        }
    }

    fclose(fs);
    fclose(fp);
    fclose(fb);

    fb = fopen("booklist.txt", "r");
    rewind(fb);

    while (fscanf(fb, "%d %[^\t] %[^\t] %s", &b.id, b.bookName, b.authorName, b.date) != EOF) {
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fb);
    getch();
}


void del(){
	FILE *ft ;
	ft = fopen("temp.txt","a");
	
	char c,n[50],a[50],d[12];
	
	int id,id1;
	printf("<== Choose the id of the book to remove ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date\n");	
    
	fp = fopen("books.txt", "r");
	
    while(fscanf(fp,"%d %[^\t] %[^\t] %s",&b.id,b.bookName,b.authorName,b.date)!=EOF){
    	printf("%-10d %-30s %-20s %s\n\n",b.id,b.bookName,b.authorName,b.date);
	}
	fclose(fp);
	fp = fopen("books.txt","r");
	
	printf("\bEnter the id of the book you want to remove==>");
	scanf("%d",&id1);
	while (fscanf(fp, "%d %[^\t] %[^\t] %s", &b.id, b.bookName, b.authorName, b.date) != EOF) {
    if (id1 != b.id) {
        fprintf(ft,"%d\t%s\t%s\t%s\n", b.id, b.bookName, b.authorName, b.date);
    }
    
}fclose(fp);
fclose(ft);
	remove("books.txt");
    rename("temp.txt", "books.txt");
	printf("<==Deleted sucessfully==>\n");
	printf("<==press any character to go to menue==> ");
	getch();
	
}
void isbook(){
	FILE *fs = fopen("issued_book.txt","a");
	
	char mydate[12];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(mydate,"%02d/%02d/%02d",tm.tm_mday, tm.tm_mon +1,tm.tm_year+1900);
	strcpy(s.date,mydate);
	
	
	fp = fopen("booklist.txt", "r");
    while(fscanf(fp,"%d %[^\t] %[^\t] %s",&b.id,b.bookName,b.authorName,b.date)!=EOF){
    	printf("%-10s30s %-20s %s\n\n",b.id,b.bookName,b.authorName,b.date);
	}
	fclose(fp);
	
	printf("Enter the book you want to issue==>");
	scanf("%d",&s.id);
	printf("Enter your name: ");
    fflush(stdin);
    gets(s.Name);
    
    FILE *fb = fopen("booklist.txt", "r");
    while(fscanf(fp,"%d %[^\t] %[^\t] %s",&b.id,b.bookName,b.authorName,b.date)!=EOF){
    	if(b.id == s.id){
    		strcpy(s.bookName,b.bookName);
		}
	}
	fprintf(fs,"\n%d\t%s\t%s\t%s\n", s.id, s.Name, s.bookName , s.date);
	
	printf("<==The book is issued sucessfully==>");
	fclose(fs);
	fclose(fp);
	
}

void isbooklist(){
FILE *fs = fopen("issued_book.txt","r"); 
	printf("<== Issued Book List ==>\n\n");
	printf("%-10s %-30s %-20s %s\n\n", "Book id", "Student Name", "Book Name", "Date\n");
	while(fscanf(fs,"%d %[^\t] %[^\t] %s",&s.id,s.Name,s.bookName,s.date)!=EOF){
    	printf("%-10d %-30s %-20s %s\n\n",s.id,s.Name,s.bookName,s.date);
	}
	getch();      
	fclose(fs);
	 
}
	 
	           
	                      