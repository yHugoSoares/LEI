import sys
from itertools import product

def preproc(s):
    return "".join(c.upper() for c in s if c.isalpha())

def vigenere_dec(message, key):
    result = []
    for i, c in enumerate(message):
        shift = ord(key[i % len(key)]) - ord('A')
        result.append(chr((ord(c) - ord('A') - shift) % 26 + ord('A')))
    return "".join(result)

# Portuguese letter frequency order
PT_FREQ = "AEOSRIDMNTCULPVGBFHQJXZWKY"

def best_shift_for_slice(slice_text):
    """Return the 4 most likely shifts based on frequency analysis."""
    counts = [0] * 26
    for c in slice_text:
        counts[ord(c) - ord('A')] += 1
    most_common = sorted(range(26), key=lambda i: counts[i], reverse=True)
    # Map the most frequent ciphertext letter to the most frequent PT letters
    candidates = []
    for pt_rank, ct_idx in enumerate(most_common[:4]):
        for pt_letter in PT_FREQ[:6]:
            shift = (ct_idx - (ord(pt_letter) - ord('A'))) % 26
            if shift not in candidates:
                candidates.append(shift)
    return candidates[:6]

def main():
    if len(sys.argv) < 4:
        print("Usage: python3 vigenere_attack.py <key_len> <ciphertext> <word1> [word2 ...]")
        sys.exit(1)

    key_len = int(sys.argv[1])
    ciphertext = preproc(sys.argv[2])
    words = [w.upper() for w in sys.argv[3:]]

    slices = [ciphertext[i::key_len] for i in range(key_len)]
    candidates_per_pos = [best_shift_for_slice(s) for s in slices]

    for combo in product(*candidates_per_pos):
        key = "".join(chr(s + ord('A')) for s in combo)
        plaintext = vigenere_dec(ciphertext, key)
        if any(w in plaintext for w in words):
            print(key)
            print(plaintext)
            return

if __name__ == "__main__":
    main()
