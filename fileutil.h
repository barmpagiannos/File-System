#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

/////////////////////////////
// Επικαιροποιημένη έκδοση //
/////////////////////////////

FILE *fptr;
int count = 0;

int insert_OTP();
void create_OTP();
void delete_OTP(); // Αυτή η συνάρτηση δεν θα χρησιμοποιείται ποτέ αυτούσια. Προορίζεται αποκλειστικά για χρήση μέσα στην insert_OTP();

void create();
void write();
void read();
void clear();
void fdelete();
int check_existence(char filename[]);

void counter();

void write_users(); // Η write() αλλά λίγο παραλλαγμένη.
                    // Το καλό είναι ότι η read() είναι μια χαρά, οπότε δεν χρειάζομαι μια read_users().

// Όλα λειτουργούν ρολόι σε αυτήν τη συνάρτηση.
void counter(){ // Αυτή η συνάρτηση μετράει τους εγγεγραμένους χρήστες.
    fptr = fopen("counter.txt", "r"); // Το ανοίγει για να το διαβάσει.
    fscanf(fptr, "%d", &count); // Διαβάζει τη μεταβλητή counter, ακόμα κι αν αυτή είναι μηδέν.
    fclose(fptr); // Κλείνει τον φάκελο.
    count++; // Το ανεβάζει κατά ένα.
    fptr = fopen("counter.txt", "w"); // Τώρα το ανοίγει για να το γράψει.
    fprintf(fptr, "%d", count); // Το γράφει.
    fclose(fptr); // Το κλείνει.
}

void create_OTP(){
    time_t t;
    srand((unsigned) time(&t));

    char otp[7]; // Το βάζω 7 για να μπει και το \0.

    for(int i = 0; i < 6; i++){
        otp[i] = (rand()%(57-48))+48; // Θέλω ASCII χαρακτήρες για αριθμούς από το 0 έως το 9.
    }
    // Δεν θα χρησιμοποιήσω την create() διότι αυτή έχει ειδική υλοποίηση για χρήση από τον χρήστη. Γι' αυτό θα το κάνω manually.
    fptr = fopen("otp.txt", "w"); // It creates an empty file with name otp.txt.
    fprintf(fptr, "%s", otp);
    fclose(fptr);
}

int insert_OTP(){

    char password[7]; // Το βάζω 7 για να μπει και το \0.
    char content[7]; // Το βάζω 7 για να μπει και το \0.

    fptr = fopen("otp.txt", "r"); // Δεν χρειάζεται να ελέγξω αν υπάρχει ο φάκελος otp.txt διότι κατά την κλήση αυτής της συνάρτησης προφανώς και θα υπάρχει.
                                  // Αφού προηγουμένως θα έχει κληθεί η create_OTP, η οποία φτιάχνει τον otp.txt και του γράφει έναν τυχαίο OTP.

    int i = 0;

    while(1){
        if(i == 6){
            break;
        }
        content[i] = fgetc(fptr); // Διαβάζει χαρακτήρα - χαρακτήρα τον OTP από τον φάκελο "otp.txt".
        i++;
    }
    fclose(fptr);

    while(1){ // Αυτή η while θα τρέχει διαρκώς δεχόμενη εισόδους από τον χρήστη μέχρι να εισαχθεί ο σωστός OTP.
        printf("\nGive password: ");
        scanf("%s", password);

        if(strcmp(password, content) == 0){ // Μόλις γίνει αυτό, θα διαγράφεται ο φάκελος otp.txt και θα τερματίζεται η ολόκληρη η συνάρτηση.
            delete_OTP();
            return 1; // Access accepted!
        }
    }
}

void delete_OTP(){
    int ret = remove("otp.txt");
}

void create(){
    char filename[50];
    printf("Enter file's name: ");
    scanf("%s", filename);
    fptr = fopen(strcat(filename, ".txt"), "w"); // It creates an empty file with name "filename".
    fclose(fptr); // It closes the file.
}

void write(){ // Θα γράφει σε ήδη υπάρχοντα φάκελο. Αν δεν υπάρχει θα τον δημιουργεί.

    char filename[50];

    printf("Enter the file's name you want to write to: ");
    scanf("%s", filename);

    // Consume the newline character left in the input buffer. ChatGPT solved this problem!
    getchar();

    if(check_existence(filename) == 1){ // Θα πρέπει να γίνεται ο έλεγχος αν υπάρχει αυτός ο φάκελος.
        // Αν υπάρχει, τότε θα γράφεις.
        fptr = fopen(filename, "a"); // Τώρα βάζω σκέτο filename και όχι strcat, διότι το strcat μπήκε πριν, οπότε το .txt μπήκε ήδη.
        char content[100];

        printf("Enter the content you want to write to the file: ");
        fgets(content, sizeof(content), stdin);
        fprintf(fptr, "%s", content);

        fclose(fptr);
    }else{
        printf("The file doesn't exist.\n");
    }
}

void read(){

    char filename[50];

    printf("\nEnter the file's name you want to read from: ");
    scanf("%s", filename);

    char content[1000];

    if(check_existence(filename) == 1){ // Θα πρέπει να γίνεται ο έλεγχος αν υπάρχει αυτός ο φάκελος.
        // Αν υπάρχει, τότε, αν βάλεις τον σωστό OTP, θα τον διαβάζεις.

        create_OTP();
        int test = insert_OTP();

        if(test == 1){ // Αν βάλεις σωστό κωδικό OTP, τότε θα διαβάζεται.
            fptr = fopen(filename, "r"); // Τώρα βάζω σκέτο filename και όχι strcat, διότι το strcat μπήκε μόλις πριν,
                                         // με την κλήση της check_existence, οπότε το .txt μπήκε ήδη.
            printf("\n"); // Μπαίνει για καλλωπιστικούς λόγους.
            while(fgets(content, sizeof(content), fptr)){
                printf("%s", content);
            }
            fclose(fptr);
        }else if(test == 0){ // Αν δεν βάλεις σωστό κωδικό OTP, τότε δεν θα διαβάζεται.
            printf("Wrong OTP.\n");
            fclose(fptr);
        }
    }else{
        printf("The file doesn't exist.\n");
    }
}

void clear(){

    char filename[50];

    printf("\nEnter the file's name you want to clear: ");
    scanf("%s", filename);

    if(check_existence(filename) == 1){ // Θα πρέπει να γίνεται ο έλεγχος αν υπάρχει αυτός ο φάκελος.
        // Αν υπάρχει, τότε θα λαμβάνεις κωδικό OTP.
        create_OTP();
        int test = insert_OTP();

        if(test == 1){ // Αν βάλεις σωστό κωδικό OTP, τότε θα καθαρίζεται.
            fptr = fopen(filename, "w"); // Καθάρισε. Τώρα βάζω σκέτο filename και όχι strcat, διότι το strcat μπήκε μόλις πριν,
                                         // με την κλήση της check_existence, οπότε το .txt μπήκε ήδη.
            printf("\nFile cleared.\n");
            fclose(fptr);

            // Κατά την κλήση της strcmp() μέσα στην if το filename είναι ΗΔΗ με κατάληξη .txt, οπότε
            if(strcmp(filename, "users.txt") == 0){ // Αν ο φάκελος τον οποίο θες να καθαρίσεις είναι ο "users.txt",
                                                    // τότε θα καθαρίζεται και ο φάκελος καταμέτρησης "counter.txt".
                fptr = fopen("counter.txt", "w"); // Βάζω την κατάληξη .txt διότι δεν μπήκε από πουθενά πιο πριν, όπως στον φάκελο users.
                fclose(fptr);
            }

        }else if(test == 0){ // Αν δεν βάλεις σωστό κωδικό OTP, τότε δεν θα καθαρίζεται.
            printf("Wrong OTP.\n");
            fclose(fptr);
        }
    }else{
        printf("The file doesn't exist.\n");
    }
}

void fdelete(){

    char filename[50];

    printf("Enter the file's name you want to delete: ");
    scanf("%s", filename);

    if(check_existence(filename) == 1){ // Θα πρέπει να γίνεται ο έλεγχος αν υπάρχει αυτός ο φάκελος.
        // Αν υπάρχει, τότε θα λαμβάνεις κωδικό OTP.
        create_OTP();
        int test = insert_OTP();

        if(test == 1){ // Αν βάλεις σωστό κωδικό OTP, τότε θα καθαρίζεται.
           int ret = remove(filename);
            if(ret == 0) {
                printf("File deleted successfully.\n");
            }
            if(strcmp(filename, "users.txt") == 0){ // Αν ο φάκελος τον οποίο θέλεις να διαγράψεις είναι ο "users.txt",
                                         // τότε θα διαγράφεται και ο "counter.txt", ώστε όταν θελήσεις να τον ξαναφτιάξεις να μην υπάρχει ήδη.
                int ret = remove("counter.txt");
            }


        }else if(test == 0){ // Αν δεν βάλεις σωστό κωδικό OTP, τότε δεν θα καθαρίζεται.
            printf("Wrong OTP.\n");
            fclose(fptr);
            delete_OTP();
        }
    }else{
        printf("The file doesn't exist.\n");
    }
}

int check_existence(char filename[]){ // Επιστρέφει true αν υπάρχει, αλλιώς δεν υπάρχει.

    fptr = fopen(strcat(filename, ".txt"), "r");

    if(fptr != NULL){
        fclose(fptr);
        return 1;
    }else{
        fclose(fptr);
        return 0;
    }
}

void write_users(){ // Θα γράφει σε ήδη υπάρχοντα φάκελο. Αν δεν υπάρχει θα τον δημιουργεί.

    counter(); // Θα καλεί αυτήν μόνο και μόνο για να είναι σωστή η αρίθμηση των χρηστών μέσα στον φάκελο "users.txt".

    fptr = fopen("users.txt", "a"); // Τώρα βάζω σκέτο filename και όχι strcat, διότι το strcat μπήκε πριν, οπότε το .txt μπήκε ήδη.

    char username[50];
    char password[50];

    printf("Enter the username: ");
    scanf("%s", username);

    printf("Enter the password: ");
    scanf("%s", password);

    fprintf(fptr, "%d. %s     %s\n", count, username, password); // 5 tabs between username and password.

    fclose(fptr);
}


