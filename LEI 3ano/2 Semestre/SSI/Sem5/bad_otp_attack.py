import sys
import random

def try_decrypt(ciphertext, seed):
    random.seed(seed)
    key = random.randbytes(len(ciphertext))
    try:
        return bytes(c ^ k for c, k in zip(ciphertext, key)).decode("utf-8", errors="replace")
    except Exception:
        return None

def main():
    if len(sys.argv) < 4:
        print("Usage: python3 bad_otp_attack.py <key_size> <ciphertext_file> <word1> [word2 ...]")
        sys.exit(1)

    key_size = int(sys.argv[1])
    ct_file = sys.argv[2]
    words = sys.argv[3:]

    with open(ct_file, "rb") as f:
        ciphertext = f.read()

    # Try all 2^16 possible seeds
    for seed_int in range(2**16):
        seed = seed_int.to_bytes(2, "big")
        random.seed(seed)
        key = random.randbytes(key_size)
        try:
            plaintext = bytes(c ^ k for c, k in zip(ciphertext, key)).decode("utf-8", errors="replace")
        except Exception:
            continue
        if any(w in plaintext for w in words):
            print(plaintext)
            return

if __name__ == "__main__":
    main()
