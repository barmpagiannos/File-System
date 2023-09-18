# File-System
A C program that allows users to process text files on their computers.

The user can create, write, read, clear and delete files on demand.

All functions are already made in the header file. The only thing you have to do is to fill the main() function as you wish.

The only function you need are: void create();
                                void write();
                                void read();
                                void clear();
                                void fdelete();
                                void write_users();

Let's see what each of those function does.

1. create(): Asks you to put a name to the file you want to create. It creates the file and closes it.
2. write(): Asks you to which file you want to write content. It then asks you to enter some content to be written to the file. If you enter a filename that doesn't exists, it pops up an error.
3. read(): Asks you from which file you want to read the content. It then creates and "otp.txt" file for your OTP, because you can't read a file without permission. If you enter the correct OTP, the "otp.txt" file is being deleted and the content of the file appears to the screen.
4. clear(): Asks you which file you want to clear. Then, same as read() function, it asks you for an OTP password. You should input the correct password. Only then the file is cleared.
5. fdelete(): Asks you which file you want to delete. Then the same thing with the OTP password happens.
6. write_users(): A very specific function. It initially creates a file called "users.txt" and then asks you to input some usernames and passwords. It works like a mini database for the program users.

