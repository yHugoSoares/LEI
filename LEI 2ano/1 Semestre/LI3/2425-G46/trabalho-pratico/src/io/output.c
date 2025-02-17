// Standard library headers
#include <stdio.h>

// Third-party library headers
#include <glib.h>
#include <ncurses.h>

// Project headers
#include "output.h"
#include "utils.h"

#include <glib.h>
#include <stdio.h>

typedef struct output {
    GPtrArray *lines;  // Using GPtrArray for better type safety and convenience
} *Output;

Output init_output() {
    Output output = g_new(struct output, 1);
    output->lines = g_ptr_array_new_with_free_func(g_free);  // Automatically frees strings
    return output;
}

void free_output(Output output) {
    if (output) {
        g_ptr_array_free(output->lines, TRUE);
        g_free(output);
    }
}

void add_line_to_output(Output output, char **tokens, char *spacer) {
    char* line;
    if (tokens == NULL || spacer == NULL) {
        line = g_strdup("");
    } else {
        line = g_strjoinv(spacer, tokens);
    }
    g_ptr_array_add(output->lines, line);
}

void write_output_to_file(Output output, char *output_file_path) {

    FILE* file = fopen(output_file_path, "w");

    for (guint i = 0; i < output->lines->len; i++) {
        fprintf(file, "%s\n", (char*)g_ptr_array_index(output->lines, i));
    }

    fclose(file);
}

void write_output_to_terminal(Output output, WINDOW *output_win, int max_lines) {

    int i;
    for (i = 0; i < max_lines && i < output->lines->len; i++) {
        if (i < 9) {
            mvwprintw(output_win, i+1, 2, "0%d | %s", i+1, (char*)g_ptr_array_index(output->lines, i));
        } else {
            mvwprintw(output_win, i+1, 2, "%d | %s", i+1, (char*)g_ptr_array_index(output->lines, i));
        }
    }
    if (i == max_lines) {
        mvwprintw(output_win, max_lines+1, 2, "Output truncated to the first %d lines (use batch mode for complete output)", max_lines);
    }
    wrefresh(output_win);
}
