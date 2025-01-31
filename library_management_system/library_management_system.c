/**
 * the intention is to create a library management system , functionalities offered 
 * books catalog - list of books with a unique id stored in the file book.csv
 * membership - store the member detail such as (name,ph.no,membership type,report,no.of.books taken,book id's) in the file user.csv
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

#define ID_MAX 4
#define PH_MAX 11
#define NAME_MAX 50
#define MAX_LINE 1000
#define MAX_LEN 100

struct members {
    int id;
    char name[NAME_MAX];
    char phone[PH_MAX];
};

typedef struct members membership;

void home();
void menu();
void member_details();
void add_member();
void get_books();
int is_duplicate(char *name);

// Function pointer array
void (*functions[])() = {home, menu, member_details, get_books, add_member};

int main() {
    functions[0]();
    return 0;
}

void home() {   
    short user_option;
    printf("WELCOME TO THE LMS \n1. LOOK AT THE CATALOGUE\n2. SHOW MEMBER DETAILS\n3. ORDER BOOKS\n4. QUIT\n");
    printf("Enter your choice: ");
    scanf("%hd", &user_option);
    switch(user_option) {
        case 1: functions[1](); break;
        case 2: functions[2](); break;
        case 3: functions[3](); break;
        case 4: exit(0);
        default: fprintf(stderr, "Invalid input... Program Colsed!\n"); break;
    }
}

void menu() {
    FILE *fp = fopen("book.csv", "r");
    if (!fp) {
        perror("Error opening books file");
        return;
    }

    char line[MAX_LINE];
      // Print each book entry    
        printf("\n📖 LIBRARY CATALOG 📖\n\n");
            while (fgets(line, sizeof(line), fp)) {
                  printf("%s", line); 
            }

    fclose(fp);

    char opt;
    printf("\nPress 'o' to order books, 'b' to return to home, 'q' to quit: ");
    getchar();
    scanf("%c", &opt);
    opt = tolower(opt);
        switch(opt) {
            case 'o': functions[3](); break;
            case 'b': functions[0](); break;
            case 'q': exit(0);
            default: fprintf(stderr, "Invalid option...S\n"); exit(0);
        }
}

void member_details() {  
    char filename[] = "user.csv"; 
    char temp_user[NAME_MAX];

    FILE *fp = fopen(filename, "r");

    if (!fp) {
        perror("Error opening file");
        return;
    }

    printf("Enter your username: ");
    scanf("%s", temp_user);

    char line[MAX_LINE];
    int found = 0;
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, temp_user) != NULL) {
                printf("\nWelcome Back, %s!\nYour details: %s\n", temp_user, line);
                found = 1;
                break;
            }
        }

    if (!found) {
        fprintf(stderr, "User not found!\n");
    }

    fclose(fp);

    char opt;
    printf("\nPress 'a' to add a new member, 'q' to quit: ");
    getchar();
    
    scanf("%c", &opt);
    opt = tolower(opt);     
        switch(opt) {
            case 'a': functions[4](); break;
            case 'q': exit(0); break;
            default: printf("Invalid choice...SS\n"); break;
        }
}

void add_member() {   
    membership member_data;
    FILE *fp = fopen("user.csv", "a+");
    if (!fp) {
        fprintf(stderr, "File access failed...\n");
        exit(EXIT_FAILURE);
    }

    printf("\nWELCOME! Please fill in your details:\n");
    printf("Enter your name: ");
    scanf(" %[^\n]", member_data.name);

    if (strlen(member_data.name) < 3) {
        fprintf(stderr, "The username must consist of at least 3 characters.\n");
        fclose(fp);
        return;
    }

    if (is_duplicate(member_data.name) == -1) {
        fprintf(stderr, "Username already exists.\n");
        fclose(fp);
        return;
    }

    printf("Enter your mobile number: ");
    scanf("%s", member_data.phone);

    srand(time(NULL));
    member_data.id = rand() % 9000 + 1000; 

    printf("Your user ID: %4d\n", member_data.id);
    fprintf(fp, "%d,%s,%s\n", member_data.id, member_data.name, member_data.phone);
    
    fclose(fp);
}

int is_duplicate(char *name) {  
    FILE *fp = fopen("user.csv", "r");
    if (!fp) {
        fprintf(stderr, "Error: Could not open file\n");
        return 1;
    }

    char line[MAX_LINE];
       
       // finds for duplicate entry 
        while (fgets(line, sizeof(line), fp)) { 
            if (strstr(line, name) != NULL) {    //if duplicate found  
                fclose(fp);
                return -1;    
            }
        }

    fclose(fp);
    return 0;  // No duplicate found
}

void get_books() {
    FILE *fp = fopen("book.csv", "r");
    if (!fp) {
        perror("Error opening book catalog");
        return;
    }

    char line[MAX_LINE];
    printf("\n📚 Available Books 📚\n");
        while (fgets(line, sizeof(line), fp)) {
            printf("%s", line);
        }
    fclose(fp);

    char book_choice[MAX_LEN];
    printf("\nEnter the book title to order: ");
    getchar();
    
    fgets(book_choice, sizeof(book_choice), stdin);
    book_choice[strcspn(book_choice, "\n")] = 0;  // Remove newline character

    FILE *order_fp = fopen("orders.csv", "a");
        if (!order_fp) {
            perror("Error accessing order file");
            return;
        }

    fprintf(order_fp, "%s\n", book_choice);
    fclose(order_fp);

    printf("Book \"%s\" ordered successfully!\n", book_choice);
}
