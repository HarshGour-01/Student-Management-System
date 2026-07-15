#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Students Management System 
struct Student
{
    int id ;
    char name[50];
    int age ;
    float marks ;
};

// Function Prototypes 
void addStudent()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");
    
    if (fp == NULL)
    {
        printf("File cannot be opened!\n");
        return;
    }
    printf("\n----- Add Student -----\n");
    printf("Enter Student ID : ");
    scanf("%d", &s.id);

    printf("Enter Student Name : ");
    scanf(" %[^\n]", s.name);    // star

    printf("Enter Age : ");
    scanf("%d", &s.age);

    printf("Enter Marks : ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);

    printf("\nStudent Added Successfully!\n");   
}

void viewStudents()
{
    FILE *fp ;
    struct Student s;

    fp = fopen("students.dat", "rb");
    
    if (fp == NULL)
    {
        printf("\nNO Records Found!\n");
        return;
    }

printf("\n=====================================================\n");
printf("ID\tName\t\tAge\tMarks\n");
printf("=======================================================\n");

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        printf("%d\t%-15s\t%d\t%.2f\n", s.id, s.name, s.age, s.marks);                   
    }
    fclose(fp);
}

void searchStudent()
{
    FILE *fp ;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }
    printf("\nEnter Student ID to Search : ");
    scanf("%d", &id);

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.id == id)
        {
            printf("\n===== Student Found =====\n");
            printf("ID  : %d\n", s.id);
            printf("Name    : %s\n", s.name);
            printf("Age    : %d\n", s.age);
            printf("Marks   : %.2f\n", s.marks);

            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        printf("\nStudent Not Found!\n");
    }
    fclose(fp);
}

void updateStudent()
{
    FILE *fp;
    struct Student s;
    int id, found = 0;
    fp = fopen("students.dat", "rb+");
    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Student ID to Update : ");
    scanf("%d", &id);

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.id == id)
        {
            printf("\nEnter New Name : ");
            scanf(" %[^\n]", s.name);

            printf("Enter New age : ");
            scanf("%d", &s.age);
            
            printf("Enter New Marks : ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(struct Student), SEEK_CUR);
            fwrite(&s,sizeof(struct Student), 1, fp);
            printf("\nStudent Updated Successfully!\n");
            
            found = 1;
            break;
        }
    }
    if (found == 0)
    {
        printf("\nStudent Not Found!\n");
    }
    fclose(fp);
}

void deleteStudent()
{
    FILE *fp, *temp;
    struct Student s;
    int id, found = 0;

    fp = fopen("students.dat","rb");
    
    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    printf("\nEnter Student ID to Delete : ");
    scanf("%d", &id);

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if(s.id == id)
        {
            found = 1;
            continue;
        }

        fwrite(&s, sizeof(struct Student), 1, temp);  
    }

    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");
    
    if (found)
    printf("\nStudent Deleted Successfully!\n");
    else 
    printf("\nStudent Not Found!\n");
}

int main()
{
    int choice;
    
    while (1)
    {

printf("\n==================================================\n");
printf("     STUDENT MANAGEMENT SYSTEM\n");
printf("====================================================\n");
        
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("\nEnter Your Choice : ");
        scanf("%d", &choice);
        
        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                viewStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4: 
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;
            
            case 6:
                printf("\nThank You!\n");
                exit(0);
        
        default:
            printf("\nInvalid Choice!");
        }

    }
    return 0;
}