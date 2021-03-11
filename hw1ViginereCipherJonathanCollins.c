#include <stdio.h>
#include <ctype.h>

// global variables

char textData[512];
char keyData[512];
char cipherKey[512];
char cipherText[512];
int keyCharCount = 0;
int textCharCount = 0;

//function to read in data of key and store in array
//print key
void readKeyFile(char * KeyFname) {
    char ch;
    int i;
    int idx = 0;

    FILE *file = fopen( KeyFname, "r" );

    if ( file == 0 ){
        printf( "Could not open file\n" );
        }
    else {
        printf( "File opened successfully\n" );
        while ((ch = fgetc(file)) != EOF){
            printf("%c", ch);

            if(isalpha(ch) != 0){
                keyData[idx] = tolower(ch);
                idx++;
                keyCharCount++;
            }
        }
    }

    fclose(file);
}

//function to read in data of plaintext and store in 512 array (read data in plaintext char by char in c)
//print unmodified plaintext
//function to rid of spaces and punctuation and convert to lowercase and pad with x
    //use isalpha function to determine if the char read in is letter or not
    //convert to lowercase if is aplpha using toLower() function
    // if the characters read by the file is less than 512, pad with 'x'
void readTextFile(char * textFname){
    char ch;
    int i;
    int idx = 0;

    FILE *file = fopen( textFname, "r" );

    if ( file == 0 ){
        printf( "Could not open file\n" );
        }
    else {
        printf( "File opened successfully\n" );
        while ((ch = fgetc(file)) != EOF){
            printf("%c", ch);

            if(isalpha(ch) != 0){
                textData[idx] = tolower(ch);
                idx++;
                textCharCount++;
            }
        }

        if (idx < 512){
            while(idx < 512){
                textData[idx] = 'x';
                idx++;
            }
        }

    }
    fclose(file);
}


void cipherKeyFunc(char* keyData){
    int i;
    int idx = 0;
    int count = 0;

    while (count != 512){
        for (i = 0; i < 512; i++){
            cipherKey[i] = keyData[idx];
            idx++;
            count++;
            if (idx == keyCharCount){
                idx = 0;
            }
        }
    }


}


void cipherTextFunc(char* cipherKey, char* textData){
    int i;
    int cipherCharCount = 0;
    for (i = 0; i < 512; i++){

        cipherText[i] = (((int)cipherKey[i] + (int)textData[i]) % 26 + 85);

        if ((int)cipherText[i] < 97) {
            cipherText[i] = cipherText[i] + 26;
        }



        printf("%c", cipherText[i]);
        cipherCharCount++;
        if (cipherCharCount == 80){     //print ciphertext in exactly 80 letters per row
            printf("\n");
            cipherCharCount = 0;
        }
    }

}


//MAIN
int main(int argc, char **argv) {

printf( "\ncommandline arguments including program name:\n\n");
int i;

for ( i = 0; i < argc; i++ ) {
    printf( "argument %d: %s\n", i, argv[ i ] );
}
printf( "\n");

// skip argv[0], it is the executable
char* keyFileName = argv[ 1 ];
char* TextFileName = argv[ 2 ];

printf("Vigenere Key: ");

//reads key file, prints unmodified, converts and stores in array
readKeyFile(keyFileName);

printf("\n\nPlaintext: ");

//reads text file, prints unmodified, converts and stores in array
readTextFile(TextFileName);

printf("\n\nCiphertext:\n");

//creates cipherKeyText that repeats the key until it fills the 512 array
cipherKeyFunc(keyData);

//creates cipher text by adding the ascii values of key and plaintext via mod 26 and returning the new value and prints it
cipherTextFunc(cipherKey, textData);


return 0;}




