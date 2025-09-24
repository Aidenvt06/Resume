#include <stdio.h>
#include <string.h>

//XOR algorithm. Takes in a message, key, and length, and preforms the XOR operation on the message. Usable for both encryption and decryption.
void xor (char msg [], char key [], char output[], int length){
    int keyLength = strlen(key);

    for (int i = 0; i < length; i++){
        output[i] = msg[i] ^ key[i % keyLength]; //if and when the key runs out before the message does, the index i gets mod by keyLength to keep it within it's bounds. 
    }
    output[length] = '\0';
}

int main(int argc, char** argv){
    if (argc != 4){
        printf("Invalid number of arguments, should be 3. \n");
            return 1;
    }
    char output[1000];
    char msg[1000];
    char *mode = argv[1];
    char *key = argv[2];
    char *filename = argv[3];
    
    if ((strcmp(mode, "enc") != 0) && (strcmp(mode, "dec") != 0)) {
        printf("Invalid mode entered. Expected 'enc' to encode or 'dec' to decode"); //ensures that the mode entered is either enc or dec
        return 1;
    }
    
    //decryption mode
    if (strcmp(mode, "dec") == 0){
            FILE *fp = fopen(filename, "rb");
        if (!fp) {
            printf("Error: Could not open file for reading\n"); //makes sure the file was opened
            return 1;
        }
        
        int msgLength;
        fread(&msgLength, sizeof(int), 1, fp);
        fread(msg, sizeof(char), msgLength, fp); // read encrypted message
        fclose(fp);

        xor(msg, key, output, msgLength); //decrypts message
        printf("%s\n", output); 
    }

    //encryption mode
    if (strcmp(mode, "enc") == 0){
        printf("Enter a message:\n");
        scanf("%999[^\n]", msg);  // read up to 999 characters until newline

        int msgLength = strlen(msg);

        xor(msg, key, output, msgLength);

        FILE *fp = fopen(filename, "wb");
        if (!fp) {
            printf("Error: Could not open file for writing\n"); //also checks if the file was opened
            return 1;
        }

        fwrite(&msgLength, sizeof(int), 1, fp);      // write length
        fwrite(output, sizeof(char), msgLength, fp); // write encrypted mesage
        fclose(fp);
    }

}
