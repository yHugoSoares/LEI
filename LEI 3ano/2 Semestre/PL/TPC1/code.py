import re

def processar_tpc_com_detalhes(nome_ficheiro):
    try:
        with open(nome_ficheiro, 'r', encoding='utf-8') as f:
            # Tokenização por caracteres de espaçamento
            tokens = f.read().split()
    except FileNotFoundError:
        print(f"Erro: O ficheiro '{nome_ficheiro}' não foi encontrado.")
        return

    # Listas para guardar as matches
    matches_min_num = []
    matches_mais_mais = []

    # Regex para o segundo critério: +alfa-numérico+
    pattern_mais = re.compile(r'^\+[a-zA-Z0-9]+\+$')

    for t in tokens:
        # 1. Começa com minúscula e termina com número
        if len(t) >= 2 and t[0].islower() and t[-1].isdigit():
            matches_min_num.append(t)
        
        # 2. Começa e acaba em '+' com alfa-numéricos no meio
        if pattern_mais.match(t):
            matches_mais_mais.append(t)

    # Impressão dos Resultados
    print(f"{'='*50}")
    print(f"RESULTADOS PARA: {nome_ficheiro}")
    print(f"{'='*50}\n")

    print(f"1. Tokens que começam com minúscula e terminam com número ({len(matches_min_num)}):")
    if matches_min_num:
        print(f"   Matches: {matches_min_num}")
    else:
        print("   Nenhuma match encontrada.")
    
    print("\n" + "-"*50 + "\n")

    print(f"2. Tokens entre '+' com conteúdo alfa-numérico ({len(matches_mais_mais)}):")
    if matches_mais_mais:
        print(f"   Matches: {matches_mais_mais}")
    else:
        print("   Nenhuma match encontrada.")
    print(f"\n{'='*50}")

# Execução
processar_tpc_com_detalhes('tpc1.txt')
