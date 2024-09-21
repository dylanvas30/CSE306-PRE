#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

bool use_header = true;

int count_records(char* filename){
  FILE *fp = fopen(filename, "r");
  if (!fp) {
        perror("File opening failed");
        return -1;  // Error handling for file not found
    }

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
  if (!file) {
        perror("File opening failed");
        return -1;  // Error handling for file not found
    }

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
  if (!file) {
        perror("File opening failed");
        return -1;  // Error handling for file not found
    }
  char line[1024];
  double min = DBL_MAX;
  int count = 0;

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
      count++;
    }
  }
  fclose(file);
  if (count == 0) {
        printf("Error: No valid numeric data found in field %d\n", fields);
        return -1;
    }
  return min;
} 

// max function

double maxFunc(char* fileName, int fields){
  FILE *file = fopen(fileName, "r");
  if (!file) {
        perror("File opening failed");
        return -1;  // Error handling for file not found
    }
  char line[1024];
  double max = -DBL_MAX;
  int count = 0;

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
      count++;
    }
  }
  fclose(file);
  if (count == 0) {
        printf("Error: No valid numeric data found in field %d\n", fields);
        return -1;
    }
  return max;
}

// mean function

double meanFunc(char* fileName, int fields) {
    FILE *fp = fopen(fileName, "r");
    if (!fp) {
        perror("File opening failed");
        return -1;  // Error handling for file not found
    }

    char line[1024];
    double tsum = 0.0;
    int count = 0;

    while (fgets(line, sizeof(line), fp)) {
        char* token = strtok(line, ",");
        for (int i = 0; i < fields - 1 && token != NULL; i++) {
            token = strtok(NULL, ",");
        }
        if (token) {
            double value = atof(token);
            tsum += value;
            count++;
        }
    }
    
    fclose(fp);

    if (count == 0) {
        printf("Error: No valid numeric data found in field %d\n", fields);
        return -1;
    }
    //printf("mean is:\n");

    return tsum/count;
}

// records field value function

void recordsFunc(char* fileName, int fields, const char* value) {
    FILE *fp = fopen(fileName, "r");
    if (!fp) {
        perror("File opening failed");
        return;  // Error handling for file not found
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        char* token = strtok(line, ",");
        for (int i = 0; i < fields - 1 && token != NULL; i++) {
            token = strtok(NULL, ",");
        }
        if (token && strcmp(token, value) == 0) {
            // Print record with matching value
            printf("%s", line);
        }
    }
    
    fclose(fp);
}

int main(int argc, char* argv[]) {

  printf("argument 1: %s\n", argv[1]);
  printf("argument 2: %s\n", argv[2]);

  //First, handle the case where  the user specifies certain flags
  int num_arguments = argc - 1;

  char* filename = argv[num_arguments];
  printf("%s\n", filename);
  printf("%d\n",num_arguments != 1);
  char* flag = argv[1];
  if (strcmp(flag, "-mean") == 0) {
      int fields = atoi(argv[2]);
      double mean = meanFunc(filename, fields);
      printf("mean value in field %d: %.2f\n", fields, mean);
  } else if (strcmp(flag, "-records") == 0) {
      int fields = atoi(argv[2]);
      char* value = argv[3];
      recordsFunc(filename, fields, value);
  }
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
  } else if (strcmp(flag, "-mean") == 0) {
      int fields = atoi(argv[2]);
      double mean = meanFunc(filename, fields);
      printf("mean value in field %d: %.2f\n", fields, mean);
  } else if (strcmp(flag, "-records") == 0) {
      int fields = atoi(argv[2]);
      char* value = argv[3];
      recordsFunc(filename, fields, value);
  }else {
    printf("You must specify a file name and parameters");
  }

  return 0;
}
