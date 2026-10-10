#!/usr/bin/env python3
"""Local pantry tracker: standard-library only, stores data in pantry.json."""
import json
from datetime import date, datetime
from pathlib import Path

DATA_FILE = Path(__file__).with_name("pantry.json")


def load_items():
    try:
        data = json.loads(DATA_FILE.read_text(encoding="utf-8"))
        return data if isinstance(data, list) else []
    except FileNotFoundError:
        return []
    except (json.JSONDecodeError, OSError) as exc:
        print(f"Could not read pantry data: {exc}")
        return []


def save_items(items):
    temp = DATA_FILE.with_suffix(".tmp")
    temp.write_text(json.dumps(items, indent=2, ensure_ascii=False), encoding="utf-8")
    temp.replace(DATA_FILE)


def ask_date(prompt):
    while True:
        raw = input(prompt).strip()
        try:
            return date.fromisoformat(raw).isoformat()
        except ValueError:
            print("Use a real date in YYYY-MM-DD format.")


def add_item(items):
    name = input("Item name: ").strip()
    if not name:
        print("Name cannot be empty.")
        return
    while True:
        raw = input("Quantity (e.g. 2 packs): ").strip()
        if raw:
            break
        print("Quantity cannot be empty.")
    expiry = ask_date("Best-before/expiry date (YYYY-MM-DD): ")
    items.append({"id": max((x.get("id", 0) for x in items), default=0) + 1,
                  "name": name, "quantity": raw, "expiry": expiry})
    save_items(items)
    print(f"Saved {name}.")


def list_items(items):
    if not items:
        print("Pantry is empty. Add an item to get started.")
        return
    today = date.today()
    for item in sorted(items, key=lambda x: x.get("expiry", "9999-12-31")):
        try:
            expiry = date.fromisoformat(item["expiry"])
            days = (expiry - today).days
            if days < 0:
                status = f"PAST DATE by {-days} day(s)"
            elif days == 0:
                status = "DATE IS TODAY"
            elif days <= 3:
                status = f"USE SOON — {days} day(s) left"
            else:
                status = f"{days} day(s) left"
        except (KeyError, ValueError, TypeError):
            status = "CHECK DATE"
        print(f"#{item.get('id', '?')}  {item.get('name', 'Unknown')} "
              f"({item.get('quantity', 'quantity unknown')}) — {item.get('expiry', '?')} [{status}]")


def remove_item(items):
    list_items(items)
    if not items:
        return
    raw = input("ID to remove (blank to cancel): ").strip()
    if not raw:
        return
    try:
        item_id = int(raw)
    except ValueError:
        print("Enter a numeric ID.")
        return
    remaining = [item for item in items if item.get("id") != item_id]
    if len(remaining) == len(items):
        print("No item found with that ID.")
        return
    save_items(remaining)
    print("Item removed.")


def main():
    items = load_items()
    while True:
        print("\n=== PantryPal: Waste Less ===\n1. Add pantry item\n2. List items and dates"
              "\n3. Remove item\n4. Exit")
        choice = input("Choose: ").strip()
        if choice == "1":
            add_item(items)
            items = load_items()
        elif choice == "2":
            list_items(items)
        elif choice == "3":
            remove_item(items)
            items = load_items()
        elif choice == "4":
            print("Goodbye — check your pantry before shopping.")
            break
        else:
            print("Choose 1, 2, 3, or 4.")


if __name__ == "__main__":
    main()
