import re

def processar_tpc(nome_ficheiro):
    try:
        with open(nome_ficheiro, 'r', encoding='utf-8') as f:
            # Um token é qualquer sequência delimitada por espaços ou mudanças de linha
            tokens = f.read().split()
    except FileNotFoundError:
        print(f"Erro: O ficheiro '{nome_ficheiro}' não foi encontrado.")
        return

    # 1. Tokens que começam com alfabético minúsculo e terminam com numérico
    # Exemplo: 'a1', 'b23', 'teste9'
    count1 = 0
    for t in tokens:
        if len(t) >= 2:
            if t[0].islower() and t[-1].isdigit():
                count1 += 1
    
    # 2. Tokens que começam e acabam com '+' e têm apenas alfa-numéricos entre eles
    # Exemplo: '+abc123+', '+1+', '+X+'
    # A regex abaixo garante que existe pelo menos um símbolo alfa-numérico entre os '+'
    pattern2 = re.compile(r'^\+[a-zA-Z0-9]+\+$')
    count2 = 0
    for t in tokens:
        if pattern2.match(t):
            count2 += 1

    print(f"Resultados para o ficheiro: {nome_ficheiro}")
    print(f"1. Tokens (minúscula...número): {count1}")
    print(f"2. Tokens (+alfa-numérico+): {count2}")

# Execução
processar_tpc('tpc1.txt')