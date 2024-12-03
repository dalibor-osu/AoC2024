#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 12

const char* input_path = "./input.txt";

int is_number(char c) {
    return c > 47 && c < 58; 
}

void shift(char* buffer, const int buffer_size) {
    for (int i = 1; i < buffer_size; i++) {
        buffer[i - 1] = buffer[i];
    }

    buffer[buffer_size - 1] = '\0';
}

void init(FILE* file, char* buffer, const int buffer_size) {
    for (int i = 1; i < buffer_size; i++) {
        buffer[i] = fgetc(file);
    }
}

int advance_window(FILE* file, char* buffer, const int buffer_size) {
    shift(buffer, buffer_size);
    char next_char = (char) fgetc(file);
    buffer[buffer_size - 1] = next_char;
    if (next_char == EOF || next_char < 32) {
        char end[buffer_size];
        memset(end, -1, buffer_size * sizeof(char));
        if (memcmp(buffer, end, buffer_size * sizeof(char)) == 0) {
            return 0;
        }
        return 1;
    } else {
        return 1;
    }
}

int starts_correctly(char* text) {
    const char* start = "mul(";
    for (int i = 0; i < 4; i++) {
        if (text[i] != start[i]) {
            return 0;
        }
    }

    return 1;
}

int try_get_numbers(char* text, int* first, int* second) {
    const int first_start = 4;
    const int max_length = 3;
    int second_start = 0;
    char first_buffer[4] = {0};
    char second_buffer[4] = {0};
    int first_end;

    for (int i = first_start; i < first_start + max_length + 1; i++) {
        first_end = i;

        if (i == first_start + max_length && text[i] != ',') {
            return 0;
        }

        if (is_number(text[i])) {
            first_buffer[i - first_start] = text[i];
            continue;
        }

        if (first_end <= first_start) {
            return 0;
        }

        break;
    }

    if (text[first_end] != ',') {
        return 0;
    }

    second_start = first_end + 1;

    for (int i = second_start; i < second_start + max_length + 1; i++) {
        if (i == second_start + max_length && text[i] != ')') {
            return 0;
        }

        if (is_number(text[i])) {
            second_buffer[i - second_start] = text[i];
            continue;
        }

        if (text[i] == ')' && i > second_start) {
            break;
        }

        return 0;
    }

    *first = atoi(first_buffer);
    *second = atoi(second_buffer);
    return 1;
}

int is_do(char* text) {
    const char* do_text = "do()";
    for (int i = 0; i < 4; i++) {
        if (do_text[i] != text[i]) {
            return 0;
        }
    }

    return 1;
}

int is_dont(char* text) {
    const char* dont_text = "don't()";
    for (int i = 0; i < 7; i++) {
        if (dont_text[i] != text[i]) {
            return 0;
        }
    }

    return 1;
}

int main() {
    FILE* file = fopen(input_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open the file");
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int result = 0;
    int first, second;

    init(file, buffer, BUFFER_SIZE);

    int enabled = 1;
    while(advance_window(file, buffer, BUFFER_SIZE)) {
        if (is_do(buffer)) {
            enabled = 1;
            continue;
        }

        if (is_dont(buffer)) {
            enabled = 0;
            continue;
        }

        if (enabled == 0) {
            continue;
        }

        if (!starts_correctly(buffer)) {
            continue;
        }

        if (!try_get_numbers(buffer, &first, &second)) {
            continue;
        }

        result += first * second;
    }

    fclose(file);
    printf("Result: %d\n", result);
    return 1;
}
