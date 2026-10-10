/*
 * Household Budget Tracker (C)
 * Stores entries in expenses.csv in the current directory.
 * Build: gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o budget
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILE_NAME "expenses.csv"
#define LINE_SIZE 256

static int read_line(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (!fgets(buffer, (int)size, stdin)) return 0;
    buffer[strcspn(buffer, "\r\n")] = '\0';
    return 1;
}
static int valid_date(const char *s) {
    return strlen(s) == 10 && isdigit((unsigned char)s[0]) &&
        isdigit((unsigned char)s[1]) && isdigit((unsigned char)s[2]) &&
        isdigit((unsigned char)s[3]) && s[4] == '-' &&
        isdigit((unsigned char)s[5]) && isdigit((unsigned char)s[6]) &&
        s[7] == '-' && isdigit((unsigned char)s[8]) &&
        isdigit((unsigned char)s[9]);
}
static void add_expense(void) {
    char date[32], category[60], note[100], amount_text[64], *end;
    double amount;
    if (!read_line("Date (YYYY-MM-DD): ", date, sizeof date) || !valid_date(date)) {
        puts("Please enter the date in YYYY-MM-DD format."); return;
    }
    if (!read_line("Category (food/transport/bills/etc.): ", category, sizeof category) ||
        !read_line("Short note (no commas): ", note, sizeof note) ||
        !read_line("Amount: ", amount_text, sizeof amount_text)) return;
    amount = strtod(amount_text, &end);
    while (isspace((unsigned char)*end)) ++end;
    if (end == amount_text || *end != '\0' || amount <= 0) {
        puts("Amount must be a positive number."); return;
    }
    if (strchr(category, ',') || strchr(note, ',')) {
        puts("Please do not use commas in category or note (CSV format)."); return;
    }
    FILE *fp = fopen(FILE_NAME, "a");
    if (!fp) { perror("Could not open expense file"); return; }
    if (fprintf(fp, "%s,%.2f,%s,%s\n", date, amount, category, note) < 0) {
        perror("Could not save expense"); fclose(fp); return;
    }
    if (fclose(fp) != 0) { perror("Could not finish saving"); return; }
    puts("Expense saved.");
}
static void show_summary(void) {
    FILE *fp = fopen(FILE_NAME, "r");
    char line[LINE_SIZE], date[32], category[60], note[100], extra;
    double amount, total = 0.0;
    unsigned count = 0;
    if (!fp) { puts("No expenses yet. Add your first expense."); return; }
    while (fgets(line, sizeof line, fp)) {
        if (sscanf(line, "%31[^,],%lf,%59[^,],%99[^\n]%c",
                   date, &amount, category, note, &extra) >= 4 &&
            amount >= 0.0) { total += amount; ++count; }
    }
    fclose(fp);
    printf("\n--- Household spending summary ---\nEntries: %u\nTotal recorded: %.2f\n", count, total);
    puts("Tip: review expenses by category in a spreadsheet if you want a deeper breakdown.");
}
int main(void) {
    char choice[16];
    for (;;) {
        puts("\n=== Household Budget Tracker ===\n1. Add expense\n2. Show summary\n3. Exit");
        if (!read_line("Choose: ", choice, sizeof choice)) break;
        if (strcmp(choice, "1") == 0) add_expense();
        else if (strcmp(choice, "2") == 0) show_summary();
        else if (strcmp(choice, "3") == 0) break;
        else puts("Choose 1, 2, or 3.");
    }
    return EXIT_SUCCESS;
}
