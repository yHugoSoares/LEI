import operator
from functools import reduce

import ply.lex as lex


# Notebook helper compatibility.
def cleanLexGlobals():
    return None


def _token_list(lexer_obj, text):
    lexer_obj.input(text)
    return [(tok.type, tok.value, tok.lineno, tok.lexpos) for tok in lexer_obj]


# -------------------------
# Exercise 2.1
# -------------------------
def tokenize_parenthesis(text):
    class Spec:
        tokens = ("LPAREN", "RPAREN")
        t_LPAREN = r"\("
        t_RPAREN = r"\)"
        t_ignore = " \t"

        def t_newline(self, t):
            r"\n+"
            t.lexer.lineno += len(t.value)

        def t_error(self, t):
            print(f"Illegal character: {t.value[0]}")
            t.lexer.skip(1)

    lexer_obj = lex.lex(module=Spec())
    return _token_list(lexer_obj, text)


# -------------------------
# Exercise 2.2
# -------------------------
def tokenize_bintree(text):
    class Spec:
        tokens = ("VAL",)
        literals = ("(", ")")
        t_VAL = r"\d+"
        t_ignore = " \t"

        def t_newline(self, t):
            r"\n+"
            t.lexer.lineno += len(t.value)

        def t_error(self, t):
            print(f"Illegal character: {t.value[0]}")
            t.lexer.skip(1)

    lexer_obj = lex.lex(module=Spec())
    return _token_list(lexer_obj, text)


# -------------------------
# Exercise 2.3
# -------------------------
def tokenize_proplogic(text):
    class Spec:
        tokens = ("VAR", "TRUE", "FALSE", "IMPLIES", "AND", "OR", "NOT", "IDEN")
        literals = ("(", ")", ",", ";")

        reserved = {"var": "VAR", "True": "TRUE", "False": "FALSE"}

        t_IMPLIES = r"=>"
        t_AND = r"/\\"
        t_OR = r"\\/"
        t_NOT = r"!"
        t_ignore = " \t"

        def t_IDEN(self, t):
            r"[A-Za-z][A-Za-z0-9_]*"
            t.type = self.reserved.get(t.value, "IDEN")
            return t

        def t_newline(self, t):
            r"\n+"
            t.lexer.lineno += len(t.value)

        def t_error(self, t):
            print(f"Illegal character: {t.value[0]}")
            t.lexer.skip(1)

    lexer_obj = lex.lex(module=Spec())
    return _token_list(lexer_obj, text)


# -------------------------
# Exercise 2.4
# -------------------------
def tokenize_sql(text):
    class Spec:
        tokens = (
            "CREATE",
            "TABLE",
            "INSERT",
            "INTO",
            "VALUES",
            "SELECT",
            "FROM",
            "WHERE",
            "PRIMARY",
            "KEY",
            "INTEGER",
            "TEXT",
            "GT",
            "INT",
            "STR",
            "IDEN",
        )
        literals = ("(", ")", ",", ";")

        reserved = {
            "CREATE": "CREATE",
            "TABLE": "TABLE",
            "INSERT": "INSERT",
            "INTO": "INTO",
            "VALUES": "VALUES",
            "SELECT": "SELECT",
            "FROM": "FROM",
            "WHERE": "WHERE",
            "PRIMARY": "PRIMARY",
            "KEY": "KEY",
            "INTEGER": "INTEGER",
            "TEXT": "TEXT",
        }

        t_GT = r">"
        t_ignore = " \t"

        def t_STR(self, t):
            r"'[^']*'"
            t.value = t.value[1:-1]
            return t

        def t_INT(self, t):
            r"\d+"
            t.value = int(t.value)
            return t

        def t_IDEN(self, t):
            r"[A-Za-z_][A-Za-z0-9_]*"
            t.type = self.reserved.get(t.value.upper(), "IDEN")
            return t

        def t_newline(self, t):
            r"\n+"
            t.lexer.lineno += len(t.value)

        def t_error(self, t):
            print(f"Illegal character: {t.value[0]}")
            t.lexer.skip(1)

    lexer_obj = lex.lex(module=Spec())
    return _token_list(lexer_obj, text)


# -------------------------
# Exercise 3.1
# -------------------------
def tokenize_json_generic(text):
    class Spec:
        tokens = ("STR", "FLOAT", "INT", "TRUE", "FALSE", "NULL")
        literals = ("{", "}", "[", "]", ":", ",")

        t_TRUE = r"true"
        t_FALSE = r"false"
        t_NULL = r"null"
        t_ignore = " \t"

        def t_STR(self, t):
            r'"([^"\\]|\\.)*"'
            t.value = t.value[1:-1]
            return t

        def t_FLOAT(self, t):
            r"-?(?:0|[1-9]\d*)\.\d+(?:[eE][+-]?\d+)?"
            t.value = float(t.value)
            return t

        def t_INT(self, t):
            r"-?(?:0|[1-9]\d*)"
            t.value = int(t.value)
            return t

        def t_newline(self, t):
            r"\n+"
            t.lexer.lineno += len(t.value)

        def t_error(self, t):
            print(f"Illegal character: {t.value[0]}")
            t.lexer.skip(1)

    lexer_obj = lex.lex(module=Spec())
    return _token_list(lexer_obj, text)


# -------------------------
# Exercise 3.2
# -------------------------
def tokenize_json_dsl(text):
    class Spec:
        tokens = (
            "TITLE",
            "YEAR",
            "CAST",
            "GENRES",
            "STR",
            "FLOAT",
            "INT",
            "TRUE",
            "FALSE",
            "NULL",
        )
        literals = ("{", "}", "[", "]", ":", ",")

        t_TITLE = r'"title"'
        t_YEAR = r'"year"'
        t_CAST = r'"cast"'
        t_GENRES = r'"genres"'
        t_TRUE = r"true"
        t_FALSE = r"false"
        t_NULL = r"null"
        t_ignore = " \t"

        def t_STR(self, t):
            r'"([^"\\]|\\.)*"'
            t.value = t.value[1:-1]
            return t

        def t_FLOAT(self, t):
            r"-?(?:0|[1-9]\d*)\.\d+(?:[eE][+-]?\d+)?"
            t.value = float(t.value)
            return t

        def t_INT(self, t):
            r"-?(?:0|[1-9]\d*)"
            t.value = int(t.value)
            return t

        def t_newline(self, t):
            r"\n+"
            t.lexer.lineno += len(t.value)

        def t_error(self, t):
            print(f"Illegal character: {t.value[0]}")
            t.lexer.skip(1)

    lexer_obj = lex.lex(module=Spec())
    return _token_list(lexer_obj, text)


# -------------------------
# Exercise 4.1
# -------------------------
def tokenize_calc(text):
    class Spec:
        states = (
            ("ASK", "exclusive"),
            ("ASSIGN_EQ", "exclusive"),
            ("EXPR", "exclusive"),
            ("DONE", "exclusive"),
        )

        tokens = (
            "EXCLAMATION",
            "QUESTION",
            "STAR",
            "EQ",
            "IDEN",
            "INT",
            "ADD",
            "SUB",
            "MUL",
            "DIV",
            "LPAREN",
            "RPAREN",
        )

        t_ignore = " \t"
        t_EXCLAMATION = r"!"
        t_QUESTION = r"\?"
        t_STAR = r"\*"

        def t_EXCLAMATION(self, t):
            r"!"
            t.lexer.begin("EXPR")
            return t

        def t_QUESTION(self, t):
            r"\?"
            t.lexer.begin("ASK")
            return t

        def t_STAR(self, t):
            r"\*"
            t.lexer.begin("DONE")
            return t

        def t_IDEN(self, t):
            r"[A-Za-z][A-Za-z0-9_]*"
            t.lexer.begin("ASSIGN_EQ")
            return t

        t_ASK_ignore = " \t"

        def t_ASK_IDEN(self, t):
            r"[A-Za-z][A-Za-z0-9_]*"
            t.type = "IDEN"
            t.lexer.begin("DONE")
            return t

        def t_ASK_error(self, t):
            print(f"Illegal character: {t.value[0]}")
            t.lexer.skip(1)

        t_ASSIGN_EQ_ignore = " \t"

        def t_ASSIGN_EQ_EQ(self, t):
            r"="
            t.type = "EQ"
            t.lexer.begin("EXPR")
            return t

        def t_ASSIGN_EQ_error(self, t):
            print(f"Illegal character: {t.value[0]}")
            t.lexer.skip(1)

        t_EXPR_ignore = " \t"
        t_EXPR_ADD = r"\+"
        t_EXPR_SUB = r"-"
        t_EXPR_MUL = r"\*"
        t_EXPR_DIV = r"/"
        t_EXPR_LPAREN = r"\("
        t_EXPR_RPAREN = r"\)"

        def t_EXPR_INT(self, t):
            r"\d+"
            t.type = "INT"
            t.value = int(t.value)
            return t

        def t_EXPR_IDEN(self, t):
            r"[A-Za-z][A-Za-z0-9_]*"
            t.type = "IDEN"
            return t

        def t_EXPR_error(self, t):
            print(f"Illegal character: {t.value[0]}")
            t.lexer.skip(1)

        t_DONE_ignore = " \t"

        def t_DONE_error(self, t):
            print(f"Illegal character: {t.value[0]}")
            t.lexer.skip(1)

        def t_ANY_newline(self, t):
            r"\n+"
            t.lexer.lineno += len(t.value)

        def t_error(self, t):
            print(f"Illegal character: {t.value[0]}")
            t.lexer.skip(1)

    lexer_obj = lex.lex(module=Spec())
    return _token_list(lexer_obj, text)


# -------------------------
# Exercise 4.2
# -------------------------
def process_calculator():
    env = {}

    def eval_expr(expr_text):
        safe_globals = {"__builtins__": None}
        return eval(expr_text, safe_globals, env)

    while True:
        try:
            cmd = input("calc> ").strip()
        except EOFError:
            break

        if not cmd:
            continue

        if cmd == "#":
            break

        if cmd == "*":
            for name in sorted(env):
                print(f"{name} = {env[name]}")
            continue

        if cmd.startswith("?"):
            name = cmd[1:].strip()
            if not name.isidentifier():
                print("Invalid variable name")
                continue
            try:
                env[name] = float(input(f"{name}? "))
            except ValueError:
                print("Invalid number")
            continue

        if cmd.startswith("!"):
            expr = cmd[1:].strip()
            try:
                print(eval_expr(expr))
            except Exception as exc:
                print(f"Error: {exc}")
            continue

        if "=" in cmd:
            lhs, rhs = cmd.split("=", 1)
            name = lhs.strip()
            if not name.isidentifier():
                print("Invalid assignment")
                continue
            try:
                env[name] = eval_expr(rhs.strip())
            except Exception as exc:
                print(f"Error: {exc}")
            continue

        print("Unknown command")


# -------------------------
# Exercise 5
# -------------------------
def sumOnOff(text):
    class Spec:
        states = (("OFF", "exclusive"),)
        tokens = ("INT", "ON", "OFF", "EQ")

        t_ignore = " \t\n\r"

        def t_ON(self, t):
            r"[Oo][Nn]"
            return t

        def t_OFF(self, t):
            r"[Oo][Ff][Ff]"
            t.lexer.begin("OFF")
            return t

        def t_EQ(self, t):
            r"="
            return t

        def t_INT(self, t):
            r"\d+"
            t.value = int(t.value)
            return t

        def t_error(self, t):
            t.lexer.skip(1)

        t_OFF_ignore = " \t\n\r"

        def t_OFF_ON(self, t):
            r"[Oo][Nn]"
            t.type = "ON"
            t.lexer.begin("INITIAL")
            return t

        def t_OFF_EQ(self, t):
            r"="
            t.type = "EQ"
            return t

        def t_OFF_INT(self, t):
            r"\d+"
            return None

        def t_OFF_OFF(self, t):
            r"[Oo][Ff][Ff]"
            return None

        def t_OFF_error(self, t):
            t.lexer.skip(1)

    lexer_obj = lex.lex(module=Spec())
    lexer_obj.input(text)

    total = 0
    for token in lexer_obj:
        if token.type == "INT":
            total += token.value
        elif token.type == "EQ":
            print(total)


# -------------------------
# Exercise 6
# -------------------------
def remove_comments(input_text):
    class Spec:
        states = (("comment", "exclusive"),)
        tokens = ("TEXT",)

        def t_COMMENT_START(self, t):
            r"/\*"
            t.lexer.comment_depth = 1
            t.lexer.begin("comment")

        def t_TEXT(self, t):
            r"[^/]+"
            return t

        def t_SLASH(self, t):
            r"/"
            t.type = "TEXT"
            return t

        def t_newline(self, t):
            r"\n+"
            t.lexer.lineno += len(t.value)
            t.type = "TEXT"
            return t

        def t_error(self, t):
            t.lexer.skip(1)

        def t_comment_COMMENT_START(self, t):
            r"/\*"
            t.lexer.comment_depth += 1

        def t_comment_COMMENT_END(self, t):
            r"\*/"
            t.lexer.comment_depth -= 1
            if t.lexer.comment_depth == 0:
                t.lexer.begin("INITIAL")

        def t_comment_newline(self, t):
            r"\n+"
            t.lexer.lineno += len(t.value)

        def t_comment_TEXT(self, t):
            r"[^/*\n]+|[/*]"
            return None

        def t_comment_error(self, t):
            t.lexer.skip(1)

    lexer_obj = lex.lex(module=Spec())
    lexer_obj.input(input_text)
    return "".join(tok.value for tok in lexer_obj)


if __name__ == "__main__":
    pass
