#include <stdio.h>
#include <stdlib.h>

const char* input_path = "./input.txt";

int get_line_count(const char* path) {
    FILE* file = fopen(path, "r");
    const int buffer_size = 32;
    char line_content[buffer_size];
    int line_count = 0;

    while(fgets(line_content, buffer_size, file)) {
        line_count++;
    }
    
    fclose(file);
    return line_count;
}

void get_left_right_values(const char* line, int length, int* left, int* right) {
    char buffer_left[length];
    char buffer_right[length];
    int buffer_index = 0;
    int is_right = 0;
    
    for (int i = 0; i < length; i++) {
        if (line[i] == '\0' || line[i] == '\n') {
            break;
        }
        if (line[i] < 48 || line[i] > 57) {
            is_right = 1;
            buffer_index = 0;
            continue;
        }
        
        if (is_right == 1) {
            buffer_right[buffer_index] = line[i];
        } else {
            buffer_left[buffer_index] = line[i];
        }

        buffer_index++;
    }

    *left = atoi(buffer_left);
    *right = atoi(buffer_right);
}

void sort(int* array, const int size) {
    int swapped = 0;
    for (int i = 0; i < size; i++) {
        swapped = 0;
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = 1;
            }
        }

        if (swapped == 0) {
            return;
        }
    }
}

int get_occurrances(const int* array, const int size, const int value) {
   int result = 0;
   
   for(int i = 0; i < size; i++) {
       if (array[i] == value) {
           result++;
       }
   }

   return result;
}

int main() {
    int line_count = get_line_count(input_path);
    
    const int buffer_size = 32;
    char line_content[buffer_size];
    FILE* file = fopen(input_path, "r");
    
    int left[line_count];
    int right[line_count];

    for(int i = 0; i < line_count; i++) {
        if (!fgets(line_content, buffer_size, file)) {
            fprintf(stderr, "Error when reading a file");
            return 1;
        }

        int left_val, right_val;
        get_left_right_values(line_content, buffer_size, &left_val, &right_val);
        left[i] = left_val;
        right[i] = right_val;
    }

    sort(left, line_count);
    sort(right, line_count);

    int result = 0;
    for (int i = 0; i < line_count; i++) {
        result += abs(left[i] - right[i]);
    }

    printf("The result is: %d\n", result);

    // Part 2
    int score = 0;
    for (int i = 0; i < line_count; i++) {
        int occurrances = get_occurrances(right, line_count, left[i]);
        score += occurrances * left[i];
    }

    printf("Similarity score: %d\n", score);
    return 0;
}
