#!/usr/bin/env python3
"""Clean a CSV file with Python's standard library; writes a new output file."""
import argparse
import csv
import sys
from pathlib import Path


def clean_csv(source: Path, destination: Path) -> tuple[int, int, int]:
    if not source.is_file():
        raise FileNotFoundError(f"Input file does not exist: {source}")
    if source.resolve() == destination.resolve():
        raise ValueError("Output must be a different file; the original is never overwritten.")
    kept, removed_blank, removed_duplicate = 0, 0, 0
    seen = set()
    destination.parent.mkdir(parents=True, exist_ok=True)
    with source.open("r", encoding="utf-8-sig", newline="") as input_file, \
         destination.open("w", encoding="utf-8", newline="") as output_file:
        reader = csv.reader(input_file)
        writer = csv.writer(output_file)
        for row in reader:
            row = [cell.strip() for cell in row]
            if not row or all(not cell for cell in row):
                removed_blank += 1
                continue
            # Case-sensitive exact row deduplication after trimming whitespace.
            signature = tuple(row)
            if signature in seen:
                removed_duplicate += 1
                continue
            seen.add(signature)
            writer.writerow(row)
            kept += 1
    return kept, removed_blank, removed_duplicate


def main():
    parser = argparse.ArgumentParser(
        description="Trim CSV cell whitespace, remove blank rows and exact duplicate rows.")
    parser.add_argument("input", type=Path, help="source CSV (will not be modified)")
    parser.add_argument("-o", "--output", type=Path, help="output CSV (default: INPUT.cleaned.csv)")
    args = parser.parse_args()
    output = args.output or args.input.with_name(args.input.stem + ".cleaned" + args.input.suffix)
    try:
        kept, blanks, duplicates = clean_csv(args.input, output)
    except (OSError, csv.Error, ValueError) as exc:
        print(f"Error: {exc}", file=sys.stderr)
        return 1
    print(f"Cleaned file: {output}")
    print(f"Rows written: {kept}")
    print(f"Blank rows removed: {blanks}")
    print(f"Duplicate rows removed: {duplicates}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
