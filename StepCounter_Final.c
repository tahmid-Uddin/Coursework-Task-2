#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

                    }



// Complete the main function


int main() {
    char option;
    int buffer_size = 500;
    char line[buffer_size];
    char filename[100];
    int number_of_records = 0;
    FITNESS_DATA file_data[1000];
    FILE *input;

    while (1) {
        printf("A:Specify the filename to be imported\n");
        printf("B:Display the total number of records in the file\n");
        printf("C:Find the date and time of the timeslot with the fewest steps\n");
        printf("D:Find the date and time of the timeslot with the largest number of steps\n");
        printf("E:Find the mean step count of all the records in the file\n");
        printf("F:Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q:Exit\n");
        printf("\nChoose an option: ");

        option = getchar();
        while (getchar() != '\n');

        if (option == 'A' | option == 'a') {
            
            // Reads the user inputted name of file
            printf("Input filename: ");
            fgets(line, buffer_size, stdin);
            sscanf(line, " %s ", filename);

            // Attempts to open it
            input = fopen(filename, "r");
            if (!input)
            {
                printf("Error: could not open file\n");
                return 1;
            }

            // Finds the number of records in the file
            while (fgets(line, buffer_size, input)) 
            {
                number_of_records++;
            }

            // Resets the file pointer to the start of the file
            rewind(input);

            char steps[10];
            int stepsint;
            int i = 0;
            
            // Stores file data to array
            while (fgets(line, buffer_size, input)) 
            {
                tokeniseRecord(line, ",", file_data[i].date, file_data[i].time, steps);
                stepsint = atoi(steps);
                file_data[i].steps = stepsint;
                i++;
            }

        }

        else if ((option == 'B' | option == 'b') && input) {
            
            printf("Total records: %d\n", number_of_records);

        }

        else if ((option == 'C' | option == 'c') && input) {
            int fewest_steps = file_data[0].steps;
            int fewest_steps_index;

            for (int i = 1; i < number_of_records; i++) {
                if (file_data[i].steps < fewest_steps) {
                    fewest_steps = file_data[i].steps;
                    fewest_steps_index = i;
                }
            }

            printf("Fewest Steps: %s %s\n", file_data[fewest_steps_index].date, file_data[fewest_steps_index].time);

        }

        else if ((option == 'D' | option == 'd') && input) {
            int largest_steps = file_data[0].steps;
            int largest_steps_index;
            
            for (int i = 1; i < number_of_records; i++) {
                if (file_data[i].steps > largest_steps) {
                    largest_steps = file_data[i].steps;
                    largest_steps_index = i;
                }
            }

            printf("Largest Steps: %s %s\n", file_data[largest_steps_index].date, file_data[largest_steps_index].time);
            
        }

        else if ((option == 'E' | option == 'e') && input) {
            int steps_sum = 0;
            char str[100];

            for (int i = 0; i < number_of_records; i++) {
                steps_sum = steps_sum + file_data[i].steps;
            }

            int mean = round(steps_sum / number_of_records);
            
            printf("Mean step count: %d\n", mean);
        }

        else if ((option == 'F' | option == 'f') && input) {
            int start; int end; int run = 0; 0; 0;
            int longest_period_start;
            int longest_period_end;

            for (int i = 0; i < number_of_records; i++) {
                if (file_data[i].steps > 500) {
                    end = i;
                    if (run == 0) {
                        start = i;
                        run = 1;
                    }  
                }

                if (((file_data[i].steps < 500) & (run == 1)) || (i == number_of_records - 1)) {
                    run = 0;
                    if ((end - start) > (longest_period_end - longest_period_start)) {
                        longest_period_start = start;
                        longest_period_end = end; 
                    }
                }
            }

            printf("Longest period start: %s %s\n", file_data[longest_period_start].date, file_data[longest_period_start].time);
            printf("Longest period end: %s %s\n", file_data[longest_period_end].date, file_data[longest_period_end].time);
        }

        else if (option == 'Q' | option == 'q') {
            if (input) {
                fclose(input);
            }
            return 0;
        }

        else {
            printf("Invalid choice\n");
        }
        
        printf("\n\n");
    }
}









