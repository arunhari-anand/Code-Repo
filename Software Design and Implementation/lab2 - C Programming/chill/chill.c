/*
* chill.c     Arun Anand     July 9, 2017
*
* This program contains a main method that accepts 0, 1 or 2 command-line
* arguments in order to calculate and display a formatted table that provides
* windchill values with respect to temperature and wind Velocity values
*
* 0 arguments - all variables are held free
* 1 argument - this argument will be assumed to be a temperature
* 2 arguments- will be assumed to be the temperature and wind Velocity
* The main method will handle all the print statements
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/*
* main method that accepts 0, 1 or 2 command-line
* arguments in order to calculate and display a formatted table that provides
* windchill values with respect to temperature and wind Velocity values
*/
int main(const int argc, const char *argv[])
{

//If there are more than 2 arguments then the program will terminate
//with an error status of 1
  if (argc > 3){
    fprintf(stderr, "Usage: chill.c <Temperature> <Velocity>\n");
    fprintf(stderr, "Only zero, one, or two arguments are permitted!");
    return 1;
  }
 //if there are less than 3 arguments then the header of the table is printed here
  printf("%*s %*s %*s %*s %*s\n", 5, "Temp", 4, " ", 4, "Wind", 4, " ", 5, "Chill" );
  printf("%*s %*s %*s %*s %*s\n", 5, "____", 4, " ", 4, "____", 4, " ", 5, "_____" );

  // this if-block handles the case where there are no arguments
  // a nested-for loop is used here to print the table
  //the format specifier ""%*.1lf" is used to print a column of the specified
  //width, with the floats rounded to 1 decimal place.

  if (argc == 1){
    int maxlen = 5;
    for(double temp = -10; temp <= 40; temp+=5){
      for(double wind = 5; wind <= 15; wind+=5){
        double wind_chill = 35.74 + 0.6215*(temp) - 35.75*(pow(wind, 0.16)) + 0.4275*temp*(pow(wind, 0.16));
        printf("%*.1lf %*s %*.1lf %*s %*.1lf\n", 5, temp, 4, " ", 4, wind, 4, " ", 5, wind_chill );
      }
      printf("\n");
    }
  }

  //this if-block handles the case where a temperature is given
  //it checks if the argument is numerical (else returns 2) and if the temperature
  //is between -99 and 50 exclusive. Else it returns 3
  else if (argc == 2){
    double temp;
    if (sscanf(argv[1],"%lf",&temp) != 1){
      fprintf(stderr, "Argument must be numerical!");
      return 2;
    }
    if (temp >= 50){
      fprintf(stderr, "Temperature must be less than 50 degrees Fahrenheit");
      return 3;
    }
    else if (temp <= -99){
      fprintf(stderr, "Temperature must be greater than -99 degrees Fahrenheit");
      return 3;
    }
    int maxlen = 5;
    for(double wind = 5; wind <= 15; wind+=5){
      double wind_chill = 35.74 + 0.6215*(temp) - 35.75*(pow(wind, 0.16)) + 0.4275*temp*(pow(wind, 0.16));
      printf("%*.1lf %*s %*.1lf %*s %*.1lf\n", 5, temp, 4, " ", 4, wind, 4, " ", 5, wind_chill );
    }
  }

  //this if-block handles the case where a temperature and wind velocity
  //are given
  //it checks if the arguments are numerical (else returns 2) and if the temperature
  //is between -99 and 50 exclusive. Else it returns 3.
  //Also checks if wind velocity is atleast 0.5, else returns 4
  else if (argc == 3){
    double temp, wind;
    if (sscanf(argv[1],"%lf",&temp) != 1 || (sscanf(argv[2],"%lf",&wind) != 1)){
      fprintf(stderr, "Arguments must be numerical!");
      return 2;
    }
    if (temp >= 50){
      fprintf(stderr, "Temperature must be less than 50 degrees Fahrenheit");
      return 3;
    }
    else if (temp <= -99){
      fprintf(stderr, "Temperature must be greater than -99 degrees Fahrenheit");
      return 3;
    }
    if (wind < 0.5){
      fprintf(stderr, "Wind speed must be greater than or equal to 0.5 MPH");
      return 4;
    }
    int maxlen = 5;
    double wind_chill = 35.74 + 0.6215*(temp) - 35.75*(pow(wind, 0.16)) + 0.4275*temp*(pow(wind, 0.16));
    printf("%*.1lf %*s %*.1lf %*s %*.1lf\n", 5, temp, 4, " ", 4, wind, 4, " ", 5, wind_chill );
  }
  return 0;
}
