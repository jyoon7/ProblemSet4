#include <stdio.h>

char pixels[200];
char compressed[200];

int read(void);
int  write(void);
void decode(void);

int main(){
  if(read() == 1) return 1;
  decode();
  if(write() == 1) return 1;

  return 0;
}

int read(void){
  FILE *readFile;
  readFile = fopen("compressed.txt", "r");

  if(readFile == NULL){
    printf("File cannot be opened or does not exist.\n");
    return 1; //Return error
  }

  // Copy the content of file to array
  int count = 0;
  char c;
  while((c = fgetc(readFile)) != EOF){
    compressed[count++] = c;
  }

  compressed[count] = '\0';

  //Close opened file
  if(readFile) fclose(readFile);
  return 0;
}

int write(void){
  FILE *writeFile;
  writeFile = fopen("pixelsDecompressed.txt", "w");

  if(writeFile == NULL){
    printf("File cannot be opened or does not exist.\n");
    return 1; //Return error
  }

  char c;
  int i = 0;
  while((c = pixels[i++]) != '\0'){
    fputc(c, writeFile);
  }

  if(writeFile) fclose(writeFile);
  return 0;
}

void decode(void){
  int x = 0; // Goes through compressed array
  int z = 0; // goes through pixels arraw
  int digit = 1; // Counts number of pixels per row
  int length; // Counts number of times pixel is repeated in the array
  char color = '1'; 
    
    length = compressed[x] - '0';
    
    for(int y = 0; y < 109; y++){
      if((digit % 10) == 0){ // count for line break
        pixels[z++] = '\n';
        digit++;
      }
      else if (length <= 0){ // Change pixel color
        if (color == '1'){   
          color = '0';
        }
        else if (color == '0'){
          color = '1';
        }
        x++;
        length = compressed[x] - '0';
      }
      else if (length != 0) // Copy each pixel into the pixel array
      {
        pixels[z++] = color;
        digit++;
        length = length - 1;
      }
    }
}
      
      
      
    
