#include <stdio.h>
#include <stdlib.h>

const char* input_path = "./input.txt";
const int line_buffer_size = 64;

int main() {
    FILE* file = fopen(input_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error occurred when opening the input file."); 
        return 1;
    }

    int safe_reports = 0, previous_number = 0, number_buffer_index = 0;
    int is_increasing = 1, is_decreasing = 1, is_first = 1, is_valid = 1;
    char line_buffer[line_buffer_size];
    char number_buffer[line_buffer_size];

    while(fgets(line_buffer, line_buffer_size, file)) {
        for(int i = 0; i < line_buffer_size; i++) {

            if (line_buffer[i] == ' ' || line_buffer[i] == '\n' || line_buffer[i] == '\0') {
                if (is_first == 1) {
                    previous_number = atoi(number_buffer);
                    number_buffer_index = 0;
                    is_first = 0;
                    continue;
                }
                
                int current_number = atoi(number_buffer);
                int difference = abs(current_number - previous_number);
                
                if (current_number > previous_number) {
                    is_decreasing = 0;
                }

                if (current_number < previous_number) {
                    is_increasing = 0;
                }

                if (difference > 3 || difference < 1) {
                    is_valid = 0;
                }

                previous_number = current_number;
                number_buffer_index = 0;

                if (line_buffer[i] == '\n' || line_buffer[i] == '\0') {
                    break;
                }

                continue;
            } 
            
            number_buffer[number_buffer_index] = line_buffer[i];
            number_buffer[number_buffer_index + 1] = '\0';
            number_buffer_index++;
        }

        if (is_valid && abs(is_increasing - is_decreasing) == 1) {
            safe_reports++;
        }

        is_increasing = 1;
        is_decreasing = 1;
        is_first = 1;
        is_valid = 1;
        number_buffer_index = 0;
    }

    fclose(file);

    printf("Safe reports: %d\n", safe_reports);
    return 0;
}
