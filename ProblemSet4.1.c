#include <stdio.h>

char pixels[200]; // Store the pixel information from "pixels.txt"
char compressed[200]; // Store the compressed pixel information

int read(void);
int  write(void);
void encode(void);

int main(){
  if(read() == 1) return 1;
  encode();
  if(write() == 1) return 1;

  return 0;
}

int read(void){
  FILE *readFile;
  readFile = fopen("pixels.txt", "r");

  if(readFile == NULL){
    printf("File cannot be opened or does not exist.\n");
    return 1; //Return error
  }

  // Copy the content of file to array
  int count = 0;
  char c;
  while((c = fgetc(readFile)) != EOF){
    pixels[count++] = c;
  }

  pixels[count] = '\0';

  //Close opened file
  if(readFile) fclose(readFile);
  return 0;
}

int write(void){
  FILE *writeFile;
  writeFile = fopen("compressed.txt", "w");

  if(writeFile == NULL){
    printf("File cannot be opened or does not exist.\n");
    return 1; //Return error
  }

  char c;
  int i = 0;
  while((c = compressed[i++]) != '\0'){
    fputc(c, writeFile);
  }

  if(writeFile) fclose(writeFile);
  return 0;
}

void encode(void){
  int z = 0;
  char length = 1;
  for(int x = 0; pixels[x] != '\0'; x++){
    if (pixels[x+1] == '\n'){  
      if (pixels[x] == pixels[x+2]){
        length++;
        x = x + 2;
      }
      else if (pixels[x] != pixels[x+2]){
        compressed[z++] = '0' + length;
        length = 1;
        x = x + 2;
      }
    }
    if (pixels[x+1] != '\n'){
      if (pixels[x] == pixels[x+1]){
        length++;
      }
      else if (pixels[x] != pixels[x+1]){
        compressed[z++] = '0' + length;
        length = 1;
      }
    }
  }
}