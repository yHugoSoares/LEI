import sys

def preproc(s):
    l = []
    for c in s:
        if c.isalpha():
            l.append(c.upper())
    return "".join(l)

def cesar_enc(message, shift):
    result = []
    for c in message:
        result.append(chr((ord(c) - ord('A') + shift) % 26 + ord('A')))
    return "".join(result)

def cesar_dec(message, shift):
    return cesar_enc(message, -shift)

def main():
    if len(sys.argv) != 4:
        print("Usage: python3 cesar.py <enc|dec> <KEY> <message>")
        sys.exit(1)

    operation = sys.argv[1].lower()
    key = sys.argv[2].upper()
    message = sys.argv[3]

    if operation not in ("enc", "dec"):
        print("Error: operation must be 'enc' or 'dec'")
        sys.exit(1)

    if len(key) != 1 or not key.isalpha():
        print("Error: key must be a single letter (A-Z)")
        sys.exit(1)

    shift = ord(key) - ord('A')
    processed = preproc(message)

    if operation == "enc":
        print(cesar_enc(processed, shift))
    else:
        print(cesar_dec(processed, shift))

if __name__ == "__main__":
    main()
