#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* input_path = "./input.txt";
const char* word = "XMAS";
const char* word_backwards = "SAMX";
const int word_length = 4;

char* get_2d_pointer(char* text, const int width, const int height, const int pos_x, const int pos_y) {
    return text + pos_y * width * sizeof(char) + pos_x * sizeof(char);
}

int get_file_lines_count(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error when opening the file");
        return -1;
    }

    const int buffer_size = 512;
    int count = 0;
    char buffer[buffer_size];
    while(fgets(buffer, buffer_size, file)) {
        count++;
    }

    fclose(file);
    return count;
}

int get_file_line_length(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error when opening the file");
        return -1;
    }

    const int buffer_size = 256;
    char buffer[buffer_size];

    if (!fgets(buffer, buffer_size, file)) {
        fclose(file);
        return 0;
    }

    for (int i = 0; 1; i++) {
        if (buffer[i] == '\n' || buffer[i] == '\0' || buffer[i] == '\r') {
            printf("First line: %s", buffer);
            fclose(file);
            return i;
        }
    }
}


int scan_horizontal(char* text, const int width, const int height, const int pos_x, const int pos_y) {
    if (pos_x > width - word_length) {
        return 0;
    }

    char* start = get_2d_pointer(text, width, height, pos_x, pos_y);
    if (memcmp(word, start,word_length) == 0) {
        // printf("Detected horizontal XMAS at X=%d, Y=%d\n", pos_x, pos_y);
        return 1;
    }

    return 0;
}

int scan_horizontal_backwards(char* text, const int width, const int height, const int pos_x, const int pos_y) {
    const char* word_backwards = "SAMX";
    
    if (pos_x < word_length - 1) {
        return 0;
    }

    char* start = get_2d_pointer(text, width, height, pos_x, pos_y) - (word_length - 1);

    if (memcmp(word_backwards, start, word_length) == 0) {
        // printf("Detected horizontal XMAS backwards at X=%d, Y=%d\n", pos_x, pos_y);
        return 1;
    }

    return 0;
}

int scan_vertical(char* text, const int width, const int height, const int pos_x, const int pos_y) {
    if (pos_y > word_length - 1) {
        return 0;
    }

    char* start = get_2d_pointer(text, width, height, pos_x, pos_y);
    for (int i = 0; i < word_length; i++) {
        char* current = start + i * width * sizeof(char);
        if (*current != word[i]) {
            return 0;
        }
    }
    
    // printf("Detected vertical XMAS at X=%d, Y=%d\n", pos_x, pos_y);
    return 1;
}

int scan_vertical_backwards(char* text, const int width, const int height, const int pos_x, const int pos_y) {
    if (pos_y < word_length - 1) {
        return 0;
    }

    char* start = get_2d_pointer(text, width, height, pos_x, pos_y);
    for (int i = 0; i < word_length; i++) {
        char* current = start - i * width * sizeof(char);
        if (*current != word[i]) {
            return 0;
        }
    }
    
    // printf("Detected vertical XMAS backwards at X=%d, Y=%d\n", pos_x, pos_y);
    return 1;
}

int scan_diagonal_right(char* text, const int width, const int height, const int pos_x, const int pos_y) {
    if (pos_y > height - word_length) {
        return 0;
    }

    if (pos_x > width - word_length) {
        return 0;
    }

    char* start = get_2d_pointer(text, width, height, pos_x, pos_y);
    for (int i = 0; i < word_length; i++) {
        char* current = start + i * width * sizeof(char) + i * sizeof(char);
        if (*current != word[i]) {
            return 0;
        }
    }
    
    // printf("Detected diagonal right XMAS at X=%d, Y=%d\n", pos_x, pos_y);
    return 1;
}

int scan_diagonal_right_backwards(char* text, const int width, const int height, const int pos_x, const int pos_y) {
    if (pos_y > height - word_length) {
        return 0;
    }

    if (pos_x > width - word_length) {
        return 0;
    }

    char* start = get_2d_pointer(text, width, height, pos_x, pos_y);
    for (int i = 0; i < word_length; i++) {
        char* current = start + i * width * sizeof(char) + i * sizeof(char);
        if (*current != word_backwards[i]) {
            return 0;
        }
    }
    
    // printf("Detected diagonal right backwards XMAS at X=%d, Y=%d\n", pos_x, pos_y);
    return 1;
}

int scan_diagonal_left(char* text, const int width, const int height, const int pos_x, const int pos_y) {
    if (pos_y > height - word_length) {
        return 0;
    }

    if (pos_x < word_length - 1) {
        return 0;
    }

    char* start = get_2d_pointer(text, width, height, pos_x, pos_y);
    for (int i = 0; i < word_length; i++) {
        char* current = start + i * width * sizeof(char) - i * sizeof(char);
        if (*current != word[i]) {
            return 0;
        }
    }
    
    // printf("Detected diagonal left XMAS at X=%d, Y=%d\n", pos_x, pos_y);
    return 1;
}

int scan_diagonal_left_backwards(char* text, const int width, const int height, const int pos_x, const int pos_y) {
    if (pos_y > height - word_length) {
        return 0;
    }

    if (pos_x < word_length - 1) {
        return 0;
    }

    char* start = get_2d_pointer(text, width, height, pos_x, pos_y);
    for (int i = 0; i < word_length; i++) {
        char* current = start + i * width * sizeof(char) - i * sizeof(char);
        if (*current != word_backwards[i]) {
            return 0;
        }
    }
    
    // printf("Detected diagonal left backwards XMAS at X=%d, Y=%d\n", pos_x, pos_y);
    return 1;
}

int scan_xmas(char* text, const int width, const int height, const int pos_x, const int pos_y) {
    int scans = 0;
    scans += scan_horizontal(text, width, height, pos_x, pos_y);
    scans += scan_horizontal_backwards(text, width, height, pos_x, pos_y);
    
    scans += scan_vertical(text, width, height, pos_x, pos_y);
    scans += scan_vertical_backwards(text, width, height, pos_x, pos_y);

    scans += scan_diagonal_right(text, width, height, pos_x, pos_y);
    scans += scan_diagonal_right_backwards(text, width, height, pos_x, pos_y);

    scans += scan_diagonal_left(text, width, height, pos_x, pos_y);
    scans += scan_diagonal_left_backwards(text, width, height, pos_x, pos_y);
    return scans;
}

int main() {
    int width = get_file_line_length(input_path), height = get_file_lines_count(input_path);
    printf("Width: %d, Height: %d\n", width, height);
    FILE* file = fopen(input_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Error when opening the file");
        return 1;
    }

    char* buffer = (char*)malloc(width * height * sizeof(char));
    char line_buffer[width * 2];
    for (int i = 0; fgets(line_buffer, width * 2, file); i++) {
        memcpy(buffer + i * width, line_buffer, width);
    }

    char* current = buffer;
    for (int i = 0; i < width * height; i++) {
        printf("%c", *current);
        current++;
    }

    int xmas_count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            xmas_count += scan_xmas(buffer, width, height, j, i);
        }
    }

    free(buffer);
    fclose(file);
    printf("XMAS was found %d times!\n", xmas_count);
    return 0;
}
