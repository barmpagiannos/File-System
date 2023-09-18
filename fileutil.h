#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

/////////////////////////////
// Updated Version        //
/////////////////////////////

FILE *fptr;
int count = 0;

// This function inserts a One-Time Password (OTP).
int insert_OTP();

// This function generates a random OTP and saves it to "otp.txt" file.
void create_OTP();

// This function deletes the OTP file.
void delete_OTP(); // This function will never be used directly. It is intended exclusively for use within insert_OTP().

// This function creates a new file.
void create();

// This function writes content to an existing file or creates a new one if it doesn't exist.
void write();

// This function reads content from an existing file.
void read();

// This function clears the content of an existing file.
void clear();

// This function deletes an existing file.
void fdelete();

// This function checks if a file with the specified name exists.
int check_existence(char filename[]);

// This function counts the number of registered users.
void counter();

// This is a variation of the write() function with slight differences.
void write_users(); // It is good that read() works fine, so I don't need a read_users().

// All operations work flawlessly in this function.
void counter(){ // This function counts the registered users.
    fptr = fopen("counter.txt", "r"); // It opens it to read.
    fscanf(fptr, "%d", &count); // It reads the variable 'count', even if it's zero.
    fclose(fptr); // It closes the folder.
    count++; // It increments it by one.
    fptr = fopen("counter.txt", "w"); // Now it opens it to write.
    fprintf(fptr, "%d", count); // It writes it.
    fclose(fptr); // It closes it.
}

// This function generates a random OTP.
void create_OTP(){
    time_t t;
    srand((unsigned) time(&t));

    char otp[7]; // I make it 7 to include the '\0'.

    for(int i = 0; i < 6; i++){
        otp[i] = (rand()%(57-48))+48; // I want ASCII characters for numbers from 0 to 9.
    }

    // I won't use create() because it has a special implementation for user use. That's why I'll do it manually.
    fptr = fopen("otp.txt", "w"); // It creates an empty file with the name "otp.txt".
    fprintf(fptr, "%s", otp);
    fclose(fptr);
}

// This function prompts the user for an OTP and verifies it.
int insert_OTP(){

    char password[7]; // I make it 7 to include the '\0'.
    char content[7]; // I make it 7 to include the '\0'.

    fptr = fopen("otp.txt", "r"); // I don't need to check if the folder "otp.txt" exists because it's obviously there when this function is called.
                                  // After the create_OTP is called, which creates the "otp.txt" and writes a random OTP.

    int i = 0;

    while(1){
        if(i == 6){
            break;
        }
        content[i] = fgetc(fptr); // It reads character by character the OTP from the "otp.txt" folder.
        i++;
    }
    fclose(fptr);

    while(1){ // This while loop will run indefinitely, accepting inputs from the user until the correct OTP is entered.
        printf("\nGive password: ");
        scanf("%s", password);

        if(strcmp(password, content) == 0){ // As soon as this happens, the "otp.txt" folder will be deleted and the entire function will terminate.
            delete_OTP();
            return 1; // Access accepted!
        }
    }
}

// This function deletes the OTP file.
void delete_OTP(){
    int ret = remove("otp.txt");
}

// This function creates a new file.
void create(){
    char filename[50];
    printf("Enter file's name: ");
    scanf("%s", filename);
    fptr = fopen(strcat(filename, ".txt"), "w"); // It creates an empty file with the name "filename".
    fclose(fptr); // It closes the file.
}

// This function writes content to an existing file or creates a new one if it doesn't exist.
void write(){ // It will write to an already existing folder. If it doesn't exist, it will create it.

    char filename[50];

    printf("Enter the file's name you want to write to: ");
    scanf("%s", filename);

    // Consume the newline character left in the input buffer. ChatGPT solved this problem!
    getchar();

    if(check_existence(filename) == 1){ // I need to check if this folder exists.
        // If it exists, then you can write to it.
        fptr = fopen(filename, "a"); // Now I use just 'filename' and not strcat, because strcat was used before,
                                     // with the call to check_existence, so '.txt' was already added.
        char content[100];

        printf("Enter the content you want to write to the file: ");
        fgets(content, sizeof(content), stdin);
        fprintf(fptr, "%s", content);

        fclose(fptr);
    }else{
        printf("The file doesn't exist.\n");
    }
}

// This function reads content from an existing file.
void read(){

    char filename[50];

    printf("\nEnter the file's name you want to read from: ");
    scanf("%s", filename);
  
    char content[1000];

    if(check_existence(filename) == 1){ // I need to check if this folder exists.
        // If it exists, then, if you enter the correct OTP, you will be able to read it.

        create_OTP();
        int test = insert_OTP();

        if(test == 1){ // If you enter the correct OTP, it will be readable.
            fptr = fopen(filename, "r"); // Now I use just 'filename' and not strcat, because strcat was used just before,
                                         // with the call to check_existence, so '.txt' was already added.
            printf("\n"); // This is for aesthetic reasons.
            while(fgets(content, sizeof(content), fptr)){
                printf("%s", content);
            }
            fclose(fptr);
        }else if(test == 0){ // If you don't enter the correct OTP, it won't be readable.
            printf("Wrong OTP.\n");
            fclose(fptr);
        }
    }else{
        printf("The file doesn't exist.\n");
    }
}

// This function clears the content of an existing file.
void clear(){

    char filename[50];

    printf("\nEnter the file's name you want to clear: ");
    scanf("%s", filename);

    if(check_existence(filename) == 1){ // I need to check if this folder exists.
        // If it exists, you will receive an OTP.

        create_OTP();
        int test = insert_OTP();

        if(test == 1){ // If you enter the correct OTP, it will be cleared.
            fptr = fopen(filename, "w"); // Clear it. Now I use just 'filename' and not strcat, because strcat was used just before,
                                         // with the call to check_existence, so '.txt' was already added.
            printf("\nFile cleared.\n");
            fclose(fptr);

            // When strcmp() is called inside the if, 'filename' already has the .txt extension, so
            if(strcmp(filename, "users.txt") == 0){ // If the folder you want to clear is "users.txt",
                                                    // then the counter folder "counter.txt" will also be cleared.
                fptr = fopen("counter.txt", "w"); // I add the .txt extension because it wasn't added earlier, like in the users folder.
                fclose(fptr);
            }

        }else if(test == 0){ // If you don't enter the correct OTP, it won't be cleared.
            printf("Wrong OTP.\n");
            fclose(fptr);
        }
    }else{
        printf("The file doesn't exist.\n");
    }
}

// This function deletes an existing file.
void fdelete(){

    char filename[50];

    printf("Enter the file's name you want to delete: ");
    scanf("%s", filename);

    if(check_existence(filename) == 1){ // I need to check if this folder exists.
        // If it exists, you will receive an OTP.

        create_OTP();
        int test = insert_OTP();

        if(test == 1){ // If you enter the correct OTP, it will be deleted.
           int ret = remove(filename);
            if(ret == 0) {
                printf("File deleted successfully.\n");
            }
            if(strcmp(filename, "users.txt") == 0){ // If the folder you want to delete is "users.txt",
                                         // then "counter.txt" will also be deleted, so when you want to recreate it, it won't already exist.
                int ret = remove("counter.txt");
            }


        }else if(test == 0){ // If you don't enter the correct OTP, it won't be cleared.
            printf("Wrong OTP.\n");
            fclose(fptr);
            delete_OTP();
        }
    }else{
        printf("The file doesn't exist.\n");
    }
}

// This function checks if a file with the specified name exists.
int check_existence(char filename[]){ // It returns true if it exists, otherwise it doesn't exist.

    fptr = fopen(strcat(filename, ".txt"), "r");

    if(fptr != NULL){
        fclose(fptr);
        return 1;
    }else{
        fclose(fptr);
        return 0;
    }
}

// This function writes user information to an existing file or creates a new one if it doesn't exist.
void write_users(){ // It will write to an already existing folder. If it doesn't exist, it will create it.

    counter(); // It will call this only to ensure that the user numbering inside the "users.txt" folder is correct.

    fptr = fopen("users.txt", "a"); // Now I use just 'filename' and not strcat, because strcat was used before, so '.txt' was already added.

    char username[50];
    char password[50];

    printf("Enter the username: ");
    scanf("%s", username);

    printf("Enter the password: ");
    scanf("%s", password);

    fprintf(fptr, "%d. %s     %s\n", count, username, password); // 5 tabs between username and password.

    fclose(fptr);
}
