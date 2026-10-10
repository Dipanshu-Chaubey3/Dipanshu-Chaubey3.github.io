# CleanSheet — CSV Cleanup Tool (Python)

A practical data-cleaning utility for messy spreadsheets exported as CSV files. It trims whitespace from cells, removes completely blank rows, and removes exact duplicate rows after trimming.

## Run
```bash
python csv_cleaner.py messy_data.csv
python csv_cleaner.py messy_data.csv --output clean_data.csv
```

The original file is never overwritten. By default, output is saved as `INPUT.cleaned.csv`.

## Concepts practised
Python's `csv`, `argparse`, `pathlib`, exception handling, tuples/sets and file safety.

## Limitations
Deduplication is exact and case-sensitive across the entire row; it does not infer that different spellings represent the same person or product. Review the output before using it for business decisions.
