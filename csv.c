#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

bool use_header = true;

int count_records(char* filename){
  FILE *fp = fopen(filename, "r");

  int line_count = 0;
  char line[1024];

  while (fgets(line, sizeof(line), fp)) {
    line_count++;
  }

  fclose(fp);

  if (use_header==false){
    line_count = line_count - 1;
  }
  return line_count;

}

int fields_first_row(char* filename) {
  printf("function called\n");
  FILE *file = fopen(filename, "r");

  char temp[1024];
  if (fgets(temp, sizeof(temp), file) == NULL) {
    perror("Error reading file");
    fclose(file);
    return -1;
  }
  //printf("function called 1");
  fclose(file);
  printf("function called 2\n");
  int field_count = 1;
  for (int i = 0; temp[i] != '\0'; i++) {
    if (temp[i] == ',') {
      field_count++;
    }
  }

  printf("%d", field_count);
  return 0;
}
//-------------------------------------------------------------------------------------------------------

//  minimum vfunction

double minFunc(char* fileName, int fields){

  FILE *file = fopen(fileName, "r");
  char line[1024];
  double min = DBL_MAX;

  while(fgets(line,sizeof(line),file)){
    char* token = strtok(line, ",");
    for(int i = 0; i<fields-1 && token != NULL; i++){
      token = strtok(NULL, ",");
    }
    if(token){
      double value = atof(token);
      if(value <min){
	min=value;
      }
    }
  }
  fclose(file);
  return min;
} 

// max function

double maxFunc(char* fileName, int fields){
  FILE *file = fopen(fileName, "r");
  char line[1024];
  double max = -DBL_MAX;

  while (fgets(line,sizeof(line),file)){
    char* token = strtok(line, ",");
    for(int i=0; i<fields-1 && token != NULL; i++){
      token = strtok(NULL, ",");
    }
    if(token){
      double value = atof(token);
      if(value>max){
	max = value;
      }
    }
  }
  fclose(file);
  return max;
}

int main(int argc, char* argv[]) {

  printf("argument 1: %s\n", argv[1]);
  printf("argument 2: %s\n", argv[2]);

  //First, handle the case where  the user specifies certain flags
  int num_arguments = argc - 1;

  char* filename = argv[num_arguments];
  printf("%s\n", filename);
  printf("%d\n",num_arguments != 1);
  if (num_arguments !=  1){
    printf("\n");
    //printf("%s",argv[1]);
    if (strcmp(argv[1],"-f") ==0){
      int count = fields_first_row(filename);
    } else if (strcmp(argv[1], "-h")==0){
      use_header = false;
    }
    if(strcmp(argv[1], "-r" )==0 || strcmp(argv[2], "-r")==0){
      //display number of data records in file, keeping in mind that the first line may or may not count
      int num_records = count_records(filename);
      printf("%d", num_records);
    }
    if(strcmp(argv[1],"-min")==0){
	int fields = atoi(argv[2]);
	double min = minFunc(filename, fields);
	printf("min value %d: %.2f", fields, min);
      }
    if(strcmp(argv[1], "-max")==0){
      int fields = atoi(argv[2]);
      double max = maxFunc(filename, fields);
      printf("max val %d: %.2f", fields , max); 
    }
  } else {
    printf("You must specify a file name and parameters");
  }

  return 0;
}
