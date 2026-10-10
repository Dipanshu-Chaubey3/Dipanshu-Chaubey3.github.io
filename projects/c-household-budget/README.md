# Household Budget Tracker (C)

A terminal-based expense logger for tracking everyday household spending. Entries are appended to a local `expenses.csv` file and a summary shows the total recorded amount.

## Build and run
```bash
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o budget
./budget
```
On Windows, run `budget.exe` after compiling.

## Features
- Add dated expenses with a category and short note.
- Validate date shape and positive numeric amounts.
- Persist entries in a local CSV file.
- Review total recorded spending.

## Limitations
This is a learning prototype: date validation checks the format, not whether the date exists; notes/categories cannot contain commas; the summary is a grand total rather than a monthly/category report. Back up `expenses.csv` because it contains your local records.

## Concepts practised
C file I/O, strings, parsing, input validation, loops and functions.
