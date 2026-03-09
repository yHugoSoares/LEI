import sys
import json


def generate(token_file):
    with open(token_file, "r", encoding="utf-8") as f:
        token_dict = json.load(f)

    if not isinstance(token_dict, dict):
        print(
            "Invalid token file format: expected a JSON object mapping "
            "TOKEN_NAME -> regex pattern."
        )
        print(
            "Hint: pass a token specification file such as "
            "tokens_parenthesis.json, not an input dataset like cinema.json."
        )
        return

    bad_values = [k for k, v in token_dict.items() if not isinstance(v, str)]
    if bad_values:
        print(
            "Invalid token file format: all token patterns must be strings. "
            f"Invalid entries: {', '.join(bad_values)}"
        )
        return

    if "UNKNOWN" in token_dict:
        print("Reserved token name UNKNOWN")
        return

    regex = (
        "|".join(f"(?P<{token}>{pattern})" for token, pattern in token_dict.items())
    ) + "|(?P<UNKNOWN>.)"

    code = f'''import re
import sys


def tokenize(line):
  line_num = 1
  recognized = []
  errors = []
  for mtch in re.finditer(r"{regex}", line):
    for k, v in mtch.groupdict().items():
      if v is not None:
        token = (k, v, line_num, mtch.start())
        break

    if token[0] == "NEWLINE":
      line_num += token[1].count("\\n")
    elif token[0] == "UNKNOWN":
      errors.append(token)
    elif token[0] != "IGNORE":
      recognized.append(token)
  return recognized, errors


def main():
  toks, errs = tokenize(sys.stdin.read())
  for err in errs:
    print("Invalid symbol:", err)
  for tok in toks:
    print(tok)


if __name__ == "__main__":
  main()
'''
    print(code)


def main():
    if len(sys.argv) < 2:
        print("Usage: python generator.py <filename>")
        sys.exit(1)

    filename = sys.argv[1]
    generate(filename)


if __name__ == "__main__":
    main()
