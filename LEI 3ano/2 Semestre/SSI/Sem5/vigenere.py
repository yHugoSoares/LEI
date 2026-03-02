import sys

def preproc(s):
    return "".join(c.upper() for c in s if c.isalpha())

def vigenere_enc(message, key):
    result = []
    key = preproc(key)
    for i, c in enumerate(message):
        shift = ord(key[i % len(key)]) - ord('A')
        result.append(chr((ord(c) - ord('A') + shift) % 26 + ord('A')))
    return "".join(result)

def vigenere_dec(message, key):
    result = []
    key = preproc(key)
    for i, c in enumerate(message):
        shift = ord(key[i % len(key)]) - ord('A')
        result.append(chr((ord(c) - ord('A') - shift) % 26 + ord('A')))
    return "".join(result)

def main():
    if len(sys.argv) != 4:
        print("Usage: python3 vigenere.py <enc|dec> <KEY> <message>")
        sys.exit(1)

    operation = sys.argv[1].lower()
    key = sys.argv[2].upper()
    message = preproc(sys.argv[3])

    if operation == "enc":
        print(vigenere_enc(message, key))
    elif operation == "dec":
        print(vigenere_dec(message, key))
    else:
        print("Error: operation must be 'enc' or 'dec'")
        sys.exit(1)

if __name__ == "__main__":
    main()
