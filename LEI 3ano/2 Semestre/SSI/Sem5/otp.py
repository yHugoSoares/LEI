import sys
import os

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 otp.py <setup|enc|dec> ...")
        sys.exit(1)

    mode = sys.argv[1].lower()

    if mode == "setup":
        if len(sys.argv) != 4:
            print("Usage: python3 otp.py setup <num_bytes> <key_file>")
            sys.exit(1)
        n = int(sys.argv[2])
        key_file = sys.argv[3]
        key = os.urandom(n)
        with open(key_file, "wb") as f:
            f.write(key)

    elif mode == "enc":
        if len(sys.argv) != 4:
            print("Usage: python3 otp.py enc <plaintext_file> <key_file>")
            sys.exit(1)
        msg_file = sys.argv[2]
        key_file = sys.argv[3]
        with open(msg_file, "rb") as f:
            message = f.read()
        with open(key_file, "rb") as f:
            key = f.read()
        if len(key) < len(message):
            print("Error: key is shorter than the message")
            sys.exit(1)
        ciphertext = bytes(m ^ k for m, k in zip(message, key))
        with open(msg_file + ".enc", "wb") as f:
            f.write(ciphertext)

    elif mode == "dec":
        if len(sys.argv) != 4:
            print("Usage: python3 otp.py dec <ciphertext_file> <key_file>")
            sys.exit(1)
        ct_file = sys.argv[2]
        key_file = sys.argv[3]
        with open(ct_file, "rb") as f:
            ciphertext = f.read()
        with open(key_file, "rb") as f:
            key = f.read()
        plaintext = bytes(c ^ k for c, k in zip(ciphertext, key))
        with open(ct_file + ".dec", "wb") as f:
            f.write(plaintext)

    else:
        print("Error: mode must be setup, enc, or dec")
        sys.exit(1)

if __name__ == "__main__":
    main()
