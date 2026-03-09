import re
import sys


def tokenize(line):
  line_num = 1
  recognized = []
  errors = []
  for mtch in re.finditer(r"(?P<CREATE>CREATE)|(?P<TABLE>TABLE)|(?P<INSERT>INSERT)|(?P<INTO>INTO)|(?P<VALUES>VALUES)|(?P<SELECT>SELECT)|(?P<FROM>FROM)|(?P<WHERE>WHERE)|(?P<PRIMARY>PRIMARY)|(?P<KEY>KEY)|(?P<INTEGER>INTEGER)|(?P<TEXT>TEXT)|(?P<LPAREN>\()|(?P<RPAREN>\))|(?P<COMMA>,)|(?P<SEMICOLON>;)|(?P<GT>>)|(?P<EQ>=)|(?P<STR>'[^']*')|(?P<INT>\d+)|(?P<IDEN>[A-Za-z_][A-Za-z0-9_]*)|(?P<IGNORE>[ \t]+)|(?P<NEWLINE>\n)|(?P<UNKNOWN>.)", line):
    for k, v in mtch.groupdict().items():
      if v is not None:
        token = (k, v, line_num, mtch.start())
        break

    if token[0] == "NEWLINE":
      line_num += token[1].count("\n")
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

