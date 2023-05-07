#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
typedef struct student
{
    long int IDno;
    char name[20];
    struct subject
    {
        int scode;
        char sname[20];
        int grade;
    } sub[3];
    int total;
    float average;
} student;
void create()
{
    FILE *fp;

    student *s;
    int n, i, j;
    printf("How many Students: ");
    scanf("%d", &n);
    s = (student*)calloc(n, sizeof(student));
    fp = fopen("studentdata.txt", "w");
    for(i = 0; i < n; i++)
    {
        s[i].total = 0;
        s[i].average = 0;
        printf("Enter the Student ID: ");
        scanf("%ld", &s[i]);
        fflush(stdin);
        printf("Enter Name: ");
        scanf("%[^\n]s", s[i].name);
        for(j = 0; j < 3; j++)
        {
            printf("Enter the grade in Subject%d: ", j + 1);
            scanf("%d", &s[i].sub[j].grade);
            s[i].total += s[i].sub[j].grade;
        }
        s[i].average = s[i].total / 3.0;
        fwrite(&s[i], sizeof(student),1,fp);
    }
    fclose(fp);
}
void display()
{
    student s1;
    FILE *fp;
    int j;
    fp = fopen("studentdata.txt","r");
    while(fread(&s1, sizeof(student),1,fp))
    {
        printf("\n%-5ld\t%-20s\t",s1.IDno,s1.name);
        for(j = 0; j<3; j++)
        {
            printf("\t%4d",s1.sub[j].grade);
        }
        printf("\t%7.2f",s1.average);
    }
    fclose(fp);
}
void deleterec() {
    student s1;
    FILE *fp, *fp1;
    int j, ID,result = 0;
    fp = fopen("studentdata.txt","r");
    fp1 = fopen("temprecord.txt", "w");
    printf("Enter the Student Id to Delete: ");
    scanf("%d", &ID);
    while(fread(&s1, sizeof(student),1,fp))
    {
        if(s1.IDno == ID)
        {
            result = 1;

        }else{
        fwrite(&s1, sizeof(student), 1, fp1);
        }
    }
    fclose(fp);
    fclose(fp1);
    if(result  == 1)
    {

        fp1 = fopen("temprecord.txt", "r");
        fp = fopen("studentdata.txt", "w");
        printf("Deleted Successfuly");
        while(fread(&s1, sizeof(student), 1, fp1))
        {
            fwrite(&s1, sizeof(student), 1, fp);
        }
        fclose(fp);
        fclose(fp1);

    }
    else
    {
        printf("Student ID does Not Exist!\n");
    }

}
void search()
{
    student s1;
    FILE *fp;
    int j, ID,result;
    fp = fopen("studentdata.txt","r");
    printf("Enter the Student Id to search: ");
    scanf("%d", &ID);
    printf("\n---------------------------------------------------------------------------------\n");
    printf("   ID              Name                          Math\t Eng\t Sci\t  GPA");
    printf("\n---------------------------------------------------------------------------------\n");
    while(fread(&s1, sizeof(student),1,fp))
    {
        if(s1.IDno == ID)
        {
            result = 1;
            printf("\n%-5d\t%-20s\t",s1.IDno,s1.name);
            for(j = 0; j<3; j++)
            {
                printf("\t%4d",s1.sub[j].grade);
            }
            printf("\t%7.2f",s1.average);
        }
    }
    if(result != 1)
    {
        printf("Student ID does Not Exist!\n");
    }
    fclose(fp);
}
void update()
{
    student s1;
    FILE *fp, *fp1;
    int j, ID,result = 0;
    fp = fopen("studentdata.txt","r");
    fp1 = fopen("temprecord.txt", "w");
    printf("Enter the Student Id to Update: ");
    scanf("%d", &ID);
    while(fread(&s1, sizeof(student),1,fp))
    {
        if(s1.IDno == ID)
        {
            s1.total = 0;
            result = 1;
            fflush(stdin);
            printf("Enter New Name of the student: ");
            scanf("%[^\n]s", s1.name);
            for(j = 0; j < 3; j++)
            {
                printf("Enter the New grade in Subject%d: ", j + 1);
                scanf("%d", &s1.sub[j].grade);
                s1.total += s1.sub[j].grade;
            }
            s1.average = s1.total / 3.0;
        }
        fwrite(&s1, sizeof(student), 1, fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(result  == 1)
    {

        fp1 = fopen("temprecord.txt", "r");
        fp = fopen("studentdata.txt", "w");

        while(fread(&s1, sizeof(student), 1, fp1))
        {
            fwrite(&s1, sizeof(student), 1, fp);
        }
        fclose(fp);
        fclose(fp1);

    }
    else
    {
        printf("Student ID does Not Exist!\n");
    }

}
int main()
{
    int choice;
    do
    {

        printf("\n[1]ADD A STUDENT RECORD\n");
        printf("[2]DISPLAY ALL STUDENT RECORD\n");
        printf("[3]DELETE A STUDENT RECORD\n");
        printf("[4]SEARCH A STUDENT RECORD\n");
        printf("[5]UPDATEA STUDENT RECORd\n");
        printf("[0]EXIT\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        system("cls");
        switch(choice)
        {
        case 1:
            create();
            break;
        case 2:
            printf("\n=================================Students Data===========================================\n");
            printf("---------------------------------------------------------------------------------\n");
            printf("   ID              Name                          Math\t Eng\t Sci\t  GPA");
            printf("\n---------------------------------------------------------------------------------\n");
            display();
            printf("\n\n======================================End================================================\n");
            sleep(3);
            break;
        case 3:
            deleterec();
            break;
        case 4:
            search();
            printf("\n=========================End=============================\n");
            break;
        case 5:
            update();
            break;
        case 0:
            printf("Exiting the program");
            break;
        default:
            printf("Invalid Choice!, Please Try Agian!");
            sleep(2);

        }
    }
    while(choice != 0);

    return 0;
}
