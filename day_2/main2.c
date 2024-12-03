#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 64

const char* input_path = "./input.txt";

int is_number(char c) {
    return c > 47 && c < 58;
}

char* int_array_to_str(int* numbers, const int size) {
    char* str = (char*)malloc(BUFFER_SIZE * sizeof(char));
    memset(str, 0, BUFFER_SIZE * sizeof(char));
    int str_index = 0;

    char current[BUFFER_SIZE];
    for (int i = 0; i < size; i++) {
        sprintf(current, "%d", numbers[i]);
        int current_index = 0;
        while(current[current_index] != '\0') {
            str[str_index] = current[current_index];
            str_index++;
            current_index++;
        }

        str[str_index] = ' ';
        str_index++;
    }

    str[str_index] = '\0';
    return str;
}

int get_number_count(const char* line, const int size) {
    int space_count = 0;
    for (int i = 0; i < size; i++) {
        if (line[i] == '\n' || line[i] == '\0') {
            break;
        }

        if (line[i] == ' ' && is_number(line[i + 1])) {
            space_count++;
        }
    }

    return space_count + 1;
}

int is_safe(int* numbers, const int size) {
    char* numbers_str = int_array_to_str(numbers, size);
    free(numbers_str);

    int previous_number = 0;
    int is_decreasing = 1, is_increasing = 1, is_valid = 1;

    for (int i = 0; i < size; i++) {
        if (i == 0) {
            previous_number = numbers[i];
                continue;
        }

        int diff = numbers[i] - previous_number;
        if (abs(diff) > 3 || abs(diff) < 1) {
            return 0;
        }

        if (diff > 0) {
            is_decreasing = 0;
        }

        if (diff < 0) {
            is_increasing = 0;
        }
        
        if (is_decreasing == is_increasing) {
            return 0;
        }

        previous_number = numbers[i];
    }
    
    printf("\tSafe!\n");
    return 1;
}

int is_safe_with_removed(int* numbers, const int size) {
    int new_numbers[size - 1];
    int skipped = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (j == i) {
                skipped = 1;
                continue;
            }

            new_numbers[j - skipped] = numbers[j];
        }

        if (is_safe(new_numbers, size - 1)) {
            return 1;
        }

        skipped = 0;
    }

    return 0;
}

int main() {
    FILE* file = fopen(input_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error occurred when opening the input file."); 
        return 1;
    }

    int safe_reports = 0;
    char line_buffer[BUFFER_SIZE];
    char number_buffer[BUFFER_SIZE];

    while(fgets(line_buffer, BUFFER_SIZE, file)) {
        int number_count = get_number_count(line_buffer, BUFFER_SIZE);
        int numbers_index = 0;
        int numbers[number_count];
        int current_number_index = 0;
        char current_number_buffer[BUFFER_SIZE] = {0};

        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (is_number(line_buffer[i])) {
                current_number_buffer[current_number_index] = line_buffer[i];
                current_number_index++;
                continue;
            }

            if (line_buffer[i] == ' ' || line_buffer[i] == '\n') {
                current_number_buffer[current_number_index] = '\0';
                numbers[numbers_index] = atoi(current_number_buffer);
                numbers_index++;
                current_number_index = 0;

                if (line_buffer[i] == '\n') {
                    break;
                }
                continue;
            }
        }

        if (is_safe_with_removed(numbers, number_count)) {
            safe_reports++;
        }
    }

    fclose(file);

    printf("Safe reports: %d\n", safe_reports);
    return 0;
}
