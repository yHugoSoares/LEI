import sys

def preproc(s):
    return "".join(c.upper() for c in s if c.isalpha())

def cesar_dec(message, shift):
    return "".join(chr((ord(c) - ord('A') - shift) % 26 + ord('A')) for c in message)

def main():
    if len(sys.argv) < 3:
        print("Usage: python3 cesar_attack.py <ciphertext> <word1> [word2 ...]")
        sys.exit(1)

    ciphertext = preproc(sys.argv[1])
    words = [w.upper() for w in sys.argv[2:]]

    for shift in range(26):
        plaintext = cesar_dec(ciphertext, shift)
        if any(w in plaintext for w in words):
            key = chr(shift + ord('A'))
            print(key)
            print(plaintext)
            return

if __name__ == "__main__":
    main()
