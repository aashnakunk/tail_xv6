#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUF_SIZE 1024

void printlines(int fd, char *filename, int numLines);

int main(int argc, char *argv[]) {
    int i=0;
    int fd = 0;
    int numberofLines=10; //if no argument is specified tail will print the last 10 lines
    char *filename = "";

    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            char *arg = argv[i];

            if (*arg == '-') {
                // We're now looking at the -NUM argument in 'tail -NUM FILE'
                arg++;  //ignore the - and move past it
                numberofLines = atoi(arg); //extract the NUM value into numberofLines
            } else {
                //we've reached the third argument, FILE, in 'tail -NUM FILE'
                filename = arg;
                fd = open(filename, O_RDONLY);

                if (fd < 0) {
                    printf(1, "tail cannot open %s\n", filename);
                    //handling the error when the file cannot be opened
                    exit();
                }
            }
        }
    }

    printlines(fd, filename, numberofLines);
    close(fd);
    exit();
}

void printlines(int fd, char *filename, int numLines) {
    int i=0;
    char buffer[BUF_SIZE];
    int bytesRead_buffer, totalLines = 0, lineCount = 0;

    // Creating a temporary file which stores the input file contents
    //we're doing this due to the offset limitation of the read function
    int temporaryFile = open("temporary file", O_CREATE | O_RDWR);

    while ((bytesRead_buffer = read(fd, buffer, sizeof(buffer))) > 0) {
        write(temporaryFile, buffer, bytesRead_buffer); //writes input file contents to this temporary file 'temporaryFILE'

        for(i = 0; i < bytesRead_buffer; i++) {
            if (buffer[i] == '\n') {
                totalLines++; //counts the number of total lines in the file
            }
        }
    }

    close(temporaryFile);

    if (bytesRead_buffer < 0) {
        printf(1, "tail: read error\n");
        //Handling the error when the file can't be read
        exit();
    }

    // Now, we open this temporary file which has the contents of the input file
    //We then read its contents
    temporaryFile = open("temporary file", O_RDONLY);

    while ((bytesRead_buffer = read(temporaryFile, buffer, sizeof(buffer))) > 0) {
        for (i = 0; i < bytesRead_buffer; i++) {
            if (lineCount >= (totalLines - numLines) || totalLines < numLines) {
                //the last NUM lines of FILE are extracted, w.r.t. 'tail -NUM FILE'
                printf(1, "%c", buffer[i]);
                //print the buffer, i.e., the last NUM lines
            } else if (buffer[i] == '\n') {
                lineCount++; //maintaining spaced lines by counting them too
            }
        }
    }

    close(temporaryFile);

    // Delete the temporary file
    unlink("temporary file");
}
