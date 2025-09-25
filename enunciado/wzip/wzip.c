#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("wzip: file1 [file2 ...]\n");
    exit(1);
  }

  int current_count = 0;
  char current_char = '\0';
  char character;
  int first_char = 1;

  for (int i = 1; i < argc; i++)
  {
    FILE *file_pointer = fopen(argv[i], "r");
    if (file_pointer == NULL)
    {
      printf("wzip: cannot open file\n");
      exit(1);
    }

    while ((character = fgetc(file_pointer)) != EOF)
    {
      if (first_char)
      {
        current_char = character;
        current_count = 1;
        first_char = 0;
      }
      else if (character == current_char)
      {
        current_count++;
      }
      else
      {
        fwrite(&current_count, sizeof(int), 1, stdout);
        fwrite(&current_char, sizeof(char), 1, stdout);

        current_char = character;
        current_count = 1;
      }
    }

    fclose(file_pointer);
  }

  if (!first_char)
  {
    fwrite(&current_count, sizeof(int), 1, stdout);
    fwrite(&current_char, sizeof(char), 1, stdout);
  }

  return 0;
}