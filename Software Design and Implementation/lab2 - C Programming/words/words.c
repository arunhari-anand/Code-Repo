/*
* words.c     Arun Anand     July 9, 2017
*
* This program takes as its arguments (i) nothing (ii) a set of filenames or
* (iii) a hyphen in order to provide a listing of all the words in the file (in
* in the case of ii) or in stdin (in the case of i and iii)
* One word is printed per line
*
* method void readfile(const int argc, const char *argv[]) rotates through
* the files provided and prints the words in them sequentially, and calls
* readScreen in the sequence when a hyphen is encountered
*
* method void readscreen() reads from stdin and prints all the words inputted
* One word is printed per line.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <ctype.h>



int status = 0; //the return status of the program

/*
* This method rotates through the files provided and prints the words in them
* sequentially, and calls readScreen in the sequence when a hyphen is encountered
* Its arguments are passed to it from the main method. argc is the number of
* command line arguments, and argv is  an array that contains pointers to those
* arguments.
* If a file cannot be opened it returns 1, and if there is an error in the file
* it returns 2
* This method does not return anything
*/
void readfile(const int argc, const char *argv[]);

/*
* this method reads from stdin and prints all the words inputted
* One word is printed per line.
* It takes no arguments and returns nothing
*/
void readscreen();


/*
* the main method checks the number of arguments and either calls readFile or
* readScreen based on this number.
*/
int main(const int argc, const char *argv[])
{

  if (argc==1){
    readscreen();
  }

  else if (argc>1){

    readfile(argc, argv);
  }

  return status;
}

/*
* This method rotates through the files provided and prints the words in them
* sequentially, and calls readScreen in the sequence when a hyphen is encountered
* Its arguments are passed to it from the main method. argc is the number of
* command line arguments, and argv is  an array that contains pointers to those
* arguments.
* If a file cannot be opened it returns 1, and if there is an error in the file
* it returns 2
* This method does not return anything
*/
void readfile(const int argc, const char *argv[])
{
  FILE *fp;
  char ch;
  //rotates through all the files provided
  for (int i = 1; i < argc; i++){

    //if a hypen is provided, then input comes from stdin
    if (*(argv[i]) == '-'){
      printf("%s", "\n");
      readscreen();
    }

    else{
      fp = fopen(argv[i], "r");

      //tests if the file opens
      if (fp == NULL){
        fprintf(stderr, "File cannot be opened!\n");
        status = 1;
        return;
      }

      bool already_newLine = false;
      //keeps track of whether a newline has already been added

      //reads characters until the end of the file
      while (!feof(fp)){

        //checks if there is an error in the file
        if (ferror(fp) != 0){
          fprintf(stderr, "Error in file!\n");
          status = 2;
          return;
        }

        ch = fgetc(fp);

        //alphabetical characters are outputted to the screen
        if (isalpha(ch)){
          printf("%c", ch);
          already_newLine = false;
        }
        //space and punctuation are converted into newlines if a newline hasnt
        //already been added
        else if (!already_newLine && (ispunct(ch) || isspace(ch))){
          putchar('\n');
          already_newLine = true;
        }
      }
      fclose(fp);

    }
  }
}

/*
* this method reads from stdin and prints all the words inputted
* One word is printed per line.
* It takes no arguments and returns nothing
*/
void readscreen()
{
  char next_character;
  bool already_newLine = false;

  //keep reading from stdin until EOF
  //uses the same procedure outlined in readFile
  while (scanf("%c", &next_character) == 1){
    if (isalpha(next_character)){
      printf("%c", next_character);
      already_newLine = false;
    }
    else if (!already_newLine && (ispunct(next_character) || isspace(next_character))){
      putchar('\n');
      already_newLine= true;
    }
  }
}
