import csv
import re

### Exercise 1.1
# Portuguese postal codes: four digits, a hyphen, then three digits
postal_code_pattern = r'\d{4}-\d{3}'

### Exercise 1.2
# Phone numbers: exactly 9 digits preceded by an optional country code of 1 to 3 digits between parenthesis
phone_pattern = r'(\(\d{1,3}\))?\d{9}'

# Read and test CSV data
csv_file = 'exemplo.csv'

try:
    with open(csv_file, 'r', encoding='utf-8') as file:
        reader = csv.DictReader(file)
        
        print("=== Exercise 1.1: Portuguese Postal Codes ===")
        for row in reader:
            postal_code = row['postal-code'].strip()
            if re.fullmatch(postal_code_pattern, postal_code):
                print(f"✓ ID {row['id']}: '{postal_code}' is valid")
            else:
                print(f"✗ ID {row['id']}: '{postal_code}' is NOT valid")
        
        print("\n=== Exercise 1.2: Phone Numbers ===")
        file.seek(0)
        next(reader)  # Skip header
        reader = csv.DictReader(file)
        
        for row in reader:
            phone = row['phone-number'].strip()
            if re.fullmatch(phone_pattern, phone):
                print(f"✓ ID {row['id']}: '{phone}' is valid")
            else:
                print(f"✗ ID {row['id']}: '{phone}' is NOT valid")
                
except FileNotFoundError:
    print(f"File '{csv_file}' not found.")
except Exception as e:
    print(f"Error: {e}")