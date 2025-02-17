// Standard library headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Third-party library headers
#include <glib.h>
#include <ncurses.h>

// Project headers
#include "defs.h"
#include "utils.h"
#include "output.h"
#include "database.h"
#include "interpreter.h"
#include "input_validation.h"

#define OFFSET 2
#define MIN_LINES 30
#define MIN_COLS 200
#define Q1_DESC "Query 1: Retrieves the top N artists by discography size."
#define Q2_DESC "Query 2: Retrieves the top N largest artists by discography size for a given country."
#define Q3_DESC "Query 3: Retrieves the popularity of music genres within a given age interval."
#define Q4_DESC "Query 4: Retrieves the most frequent top10 artist within a given date interval."
#define Q5_DESC "Query 5: Retrieves the top N recommended users for a given user."
#define Q6_DESC "Query 6: Retrieves the listening statistics for a given user in a given year."
#define DESCRIPTIONS { Q1_DESC, Q2_DESC, Q3_DESC, Q4_DESC, Q5_DESC, Q6_DESC, NULL };

void print_query_description(WINDOW *win, int line, int index) {
    char *description[] = DESCRIPTIONS;
    mvwprintw(win, line, 0, "%s", description[index]);
}

int selector(WINDOW *selector_win, int line, char **options, int num_options, int type_query) {

    keypad(selector_win, TRUE);
    int highlight = 0;

    while (1) {

        if (type_query) {
            wclear(selector_win);
            wrefresh(selector_win);
        }

        int j = 0;

        for (int i = 0; i < num_options; i++) {
            if (i == highlight) {
                wattron(selector_win, A_REVERSE | A_BOLD);
            }
            mvwprintw(selector_win, line, j, "%s", options[i]);
            j += strlen(options[i]) + 1;
            if (i == highlight) {
                wattroff(selector_win, A_REVERSE | A_BOLD);
                if (type_query) {
                    print_query_description(selector_win, line + 1, i);
                } 
            }
        }

        wrefresh(selector_win);

        int ch = wgetch(selector_win);
        switch (ch) {
            case KEY_LEFT:
                highlight = highlight == 0 ? num_options - 1 : highlight - 1; // Move left
                break;
            case KEY_RIGHT:
                highlight = highlight == num_options - 1 ? 0 : highlight + 1; // Move right
                break;
            case '\n': // Enter key pressed
                goto end;
            default:
                break;
        }
    }

    end:
    keypad(selector_win, FALSE);
    return highlight;
}

void do_interpreter(Database database, int min_y, int max_y, int max_x) {
    
    char *queries[] = QUERIES;
    char *spacers[] = SPACERS_FULL;

    // Subtitles Window
    int subtitles_y = min_y + 1;
    int subtitles_x = 2;
    int subtitles_lines = 1;
    int subtitles_cols = max_x - 4;

    WINDOW *subtitles_win = newwin(subtitles_lines, subtitles_cols, subtitles_y, subtitles_x);
    wrefresh(subtitles_win);

    // Input Window
    int input_y = min_y + 2;
    int input_x = 2;
    int input_lines = max_y - input_y - 2;
    int intput_cols = 90;
    
    WINDOW *input_win = newwin(input_lines, intput_cols, input_y, input_x);
    wrefresh(input_win);

    // Output Window
    int output_y = min_y + 2;
    int output_x = intput_cols + 2;
    int output_lines = max_y - output_y - 2;
    int output_cols = max_x - intput_cols - 4;
    int output_writable_lines = output_lines - 3;

    WINDOW *output_win = newwin(output_lines, output_cols, output_y, output_x);
    wrefresh(output_win);

    // Print subtitles
    wattron(subtitles_win, A_BOLD);
    mvwprintw(subtitles_win, 0, 0, "Press 'ENTER' to select (left and right arrow keys to navigate):");
    mvwprintw(subtitles_win, 0, output_x, "Output:");
    wattroff(subtitles_win, A_BOLD);
    wrefresh(subtitles_win);
    
    int count = 0;

    while (1) {
        wclear(input_win);
        wclear(output_win);
        box(output_win, 0 , 0);
        wrefresh(input_win);
        wrefresh(output_win);

        int query = 1 + selector(input_win, 1, queries, QUERIES_NUM, 1);
        int spacer = selector(input_win, 4, spacers, SPACERS_NUM, 0);
        
        switch (query) {
            case 1:
                mvwprintw(input_win, 6, 0, "Enter user or artist ID:");
                mvwprintw(input_win, 7, 0, "(Expected format: <ID>)");
                break;
            case 2:
                mvwprintw(input_win, 6, 0, "Enter number of artists and country:");
                mvwprintw(input_win, 7, 0, "(Expected format: <N> [Country])");
                break;
            case 3:
                mvwprintw(input_win, 6, 0, "Enter age interval:");
                mvwprintw(input_win, 7, 0, "(Expected format: <min_age> <max_age>)");
                break;
            case 4:
                mvwprintw(input_win, 6, 0, "Enter user or artist ID:");
                mvwprintw(input_win, 7, 0, "(Expected format: [begin_date] [end_date])");
                break;
            case 5:
                mvwprintw(input_win, 6, 0, "Enter user ID and number of recommendations:");
                mvwprintw(input_win, 7, 0, "(Expected format: <ID> <N>)");
                break;
            case 6:
                mvwprintw(input_win, 6, 0, "Enter user ID, year and number of artists:");
                mvwprintw(input_win, 7, 0, "(Expected format: <ID> <year> [N])");
                break;
            default:
                break;
            }
        wrefresh(input_win);

        char input[BUFFER_SIZE];

        wmove(input_win, 8, 0);
        curs_set(1);
        echo();
        wgetstr(input_win, input);
        noecho();
        curs_set(0);

        if (!validate_input(query, input)) {
            mvwprintw(input_win, 10, 0, "Invalid input!");
            mvwprintw(input_win, 11, 0, "Press 'ENTER' to try a new query or 'Q' to quit...");
            wrefresh(input_win);
            loop1:
            curs_set(1);
            int ch = wgetch(input_win);
            curs_set(0);
            if (ch == 'q' || ch == 'Q') {
                goto end;
            } else if (ch == '\n') {
                continue;
            } else {
                goto loop1;
            }
            continue;
        }

        Output output = init_output();
        interactive_interpreter(query, spacer, input, database, &output);
        write_output_to_terminal(output, output_win, output_writable_lines);

        mvwprintw(input_win, 10, 0, "Press 'S' to save output or 'D' to discard...");
        wrefresh(input_win);

        char output_file_path[BUFFER_SIZE];
        snprintf(output_file_path, BUFFER_SIZE, "resultados/command%d_output.txt", count);
        char ch = '\0';

        loop2:
        curs_set(1);
        ch = wgetch(input_win);
        curs_set(0);

        if ((ch == 's' || ch == 'S')) {  
            write_output_to_file(output, output_file_path);
            mvwprintw(input_win, 11, 0, "Output saved as command%d_output.txt...", count);
            wrefresh(input_win);
            count++;
        } else if (ch == 'd' || ch == 'D') {
            mvwprintw(input_win, 11, 0, "Output discarded...");
            wrefresh(input_win);
        } else {
            goto loop2;
        }
        free_output(output);

        mvwprintw(input_win, 13, 0, "Press 'ENTER' to continue or 'Q' to quit...");
        wrefresh(input_win);

        loop3:
        curs_set(1);
        ch = wgetch(input_win);
        curs_set(0);

        if (ch == '\n') {
            continue;
        } else if (ch == 'q' || ch == 'Q') {
            goto end;
        } else {
            goto loop3;
        }
    }

    end:
    wclear(input_win);
    wclear(output_win);
    wclear(subtitles_win);
    wrefresh(input_win);
    wrefresh(output_win);
    wrefresh(subtitles_win);
    delwin(input_win);
    delwin(output_win);
    delwin(subtitles_win);
}

void do_load(Database *database, int min_y, int max_x) {
    // Window Dimensions
    int lines = 10;
    int cols = max_x-4;
    int y = min_y + 1;
    int x = 2;

    // Window
    WINDOW *load_win = newwin(lines, cols, y, x);
    wrefresh(load_win);

    char dataset_folder_path[BUFFER_SIZE];
    mvwprintw(load_win, 0, 0, "Enter dataset folder path or press 'ENTER' for default path: (%s)", DEFAULT_DATASET_FOLDER_PATH);
    wmove(load_win, 1, 0);
    wrefresh(load_win);

    // Get dataset folder path
    get_input:
    curs_set(1);
    echo();
    wgetnstr(load_win, dataset_folder_path, BUFFER_SIZE);
    noecho();
    curs_set(0);

    if (strlen(dataset_folder_path) == 0) {
        strcpy(dataset_folder_path, DEFAULT_DATASET_FOLDER_PATH);
    } else if (!validate_directory(dataset_folder_path)) {
        wclear(load_win);
        mvwprintw(load_win, 0, 0, "Invalid path or files not found! Please enter a new path or press 'ENTER' for default path: (%s)", DEFAULT_DATASET_FOLDER_PATH);
        wmove(load_win, 1, 0);
        wrefresh(load_win);
        goto get_input;
    }

    wattron(load_win, A_BLINK);
    mvwprintw(load_win, 2, 0, "Loading database...");
    wrefresh(load_win);
    wattroff(load_win, A_BLINK);

    // Load database
    *database = load_database(dataset_folder_path);

    mvwprintw(load_win, 2, 0, "Loading database...");
    mvwprintw(load_win, 3, 0, "Database loaded!");
    mvwprintw(load_win, 4, 0, "Press 'ENTER' to continue...");
    wrefresh(load_win);

    loop:
    char ch = wgetch(load_win);
    if (ch != '\n') goto loop;

    // Delete window
    wclear(load_win);
    wrefresh(load_win);
    delwin(load_win);
}

WINDOW *draw_title_win(char *title, int max_x) {
    // Window Dimensions
    int lines = 3;
    int cols = 2 + strlen(title);
    int y = 0;
    int x = (max_x / 2) - (cols / 2);

    // Window
    WINDOW *title_win = newwin(lines, cols, y, x);
    box(title_win, 0, 0);
    wrefresh(title_win);

    // Print title
    wattron(title_win, A_REVERSE | A_BOLD);
    mvwprintw(title_win, 1, 1, "%s", title);
    wattroff(title_win, A_REVERSE | A_BOLD);
    wrefresh(title_win);

    return title_win;
}

void do_interface() {
    initscr();              // Initialize ncurses
    cbreak();               // Disable line buffering
    noecho();               // Don't echo user input
    curs_set(0);            // Hide cursor
    nodelay(stdscr, TRUE);  // Don't wait for input
    refresh();              // Need to draw the root window
                            // without this, the children windows never draw

    // Get the size of the terminal
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // If the terminal is too small, exit
    if (max_y < MIN_LINES || max_x < MIN_COLS) {
        endwin();
        printf("Terminal too small. Minimum size: %dx%d\n", MIN_COLS, MIN_LINES);
        return;
    }

    // Borders
    box(stdscr, 0, 0);
    refresh();

    // Title
    WINDOW *title_win = draw_title_win(" STREAMING DATABASE ", max_x);

    // Title height
    int min_y = 3;

    // Load database
    Database database = NULL;
    do_load(&database, min_y, max_x);

    // Interpreter
    do_interpreter(database, min_y, max_y, max_x);

    // Free database
    mvprintw(max_y/2, max_x/2 - 26, "Program will terminate once the database is freed...");
    refresh();
    free_database(database);

    // Delete windows and terminate interface
    delwin(title_win);
    endwin();
}
