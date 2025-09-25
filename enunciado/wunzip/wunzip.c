#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }
    
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "rb");  // esto para abrir en modo binario
        
        if (file == NULL) {
            printf("wunzip: cannot open file\n");
            return 1;
        }
        
        int count;
        char character;
        
        // Leer pares contador, caracter hasta el final del archivo
        while (fread(&count, sizeof(int), 1, file) == 1 && 
               fread(&character, sizeof(char), 1, file) == 1) {
            
            // se imprime el caracter count veces
            for (int j = 0; j < count; j++) {
                printf("%c", character);
            }
        }
        
        fclose(file);
    }
    
    return 0;
}