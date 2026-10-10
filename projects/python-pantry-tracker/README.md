# PantryPal — Food Expiry & Pantry Tracker (Python)

A small local command-line tool to help a household remember what food it has and which items may need using soon. It uses only the Python standard library.

## Run
```bash
python pantry_tracker.py
```

## Features
- Add food name, quantity and best-before/expiry date.
- Sort pantry items by date.
- Highlight items past their date, due today, or due within three days.
- Remove items by ID.
- Save data locally to `pantry.json`.

## Responsible use
This is a reminder tool, not a food-safety authority. A date alone cannot determine whether food is safe; follow product storage instructions and local food-safety guidance. The data file is stored beside the script, so keep a backup if needed.

## Concepts practised
Python functions, JSON persistence, date arithmetic, exception handling, sorting and CLI design.
