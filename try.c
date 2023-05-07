#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>

int main(){
     FILE *fpt;
    int result = 0;
    char username[20], password[20], iuser[20], ipass[20];
    printf("[1]Register\n[2]Log in\n");
    int sel;
    printf("Enter Your Choice: ");
    scanf("%d", &sel);

    switch(sel){
case 1:

    fpt = fopen("Usernamepassword.txt","a+");
    if(fpt == NULL){
        perror("No file detected!");
        exit(1);
    }
    printf("Enter Username: ");
    scanf("%s", iuser);
    printf("Enter Password: ");
    scanf("%s", ipass);
    while(fscanf(fpt,"%s %s", username, password) != EOF){
        if(strcmp(iuser, username) == 0){
            result = 1;
        }
    }
    if (result == 1){

        printf("Register in Failed, Username Already Taken!");
        exit(1);
    }else{
        fprintf(fpt,"\n%s %s", &iuser, &ipass);
        printf("Registered Successfully!");
    }
    break;
    case 2:

    fpt = fopen("Usernamepassword.txt","r");
    if(fpt == NULL){
        perror("No file detected!");
        exit(1);
    }
    printf("Enter Username: ");
    scanf("%s", iuser);
    printf("Enter Password: ");
    scanf("%s", ipass);
    while((fscanf(fpt,"%s %s", username, password)) != EOF){
        if(strcmp(iuser, username) == 0 && strcmp(ipass,password) == 0){
            result = 1;
        }
    }
    if (result == 1){
        printf("Logged in Successfully");
    }else{
        printf("Invalid Username or Password!");
        exit(1);
    }
    break;
    default:
        printf("\nInvalid Choice, Please Try Again!\n");
        sleep(2);

        return main();


    }
 fclose(fpt);
return 0;
}
