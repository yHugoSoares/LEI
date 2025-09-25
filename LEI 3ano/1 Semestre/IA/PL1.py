# Simple command-line menu application
def main_menu():
    while True:
        print("\n--- Main Menu ---")
        print("1. Option 1")
        print("2. Option 2")
        print("3. Exit")
        choice = input("Select an option: ")

        if choice == "1":
            print("You selected Option 1.")
        elif choice == "2":
            print("You selected Option 2.")
        elif choice == "3":
            print("Exiting...")
            break
        else:
            print("Invalid option. Please try again.")


def joinStrings(str1, str2):
    return str1 + str2

class Aluno:
    def __init__(self, nome, numero, idade):
        self.nome = nome
        self.numero = numero
        self.idade = idade

    def get_nome(self):
        return self.nome
    
    def get_numero(self):
        return self.numero
    
    def get_idade(self):
        return self.idade
    
    def set_nome(self, nome):
        self.nome = nome

    def set_numero(self, numero):
        self.numero = numero

    def set_idade(self, idade):
        self.idade = idade

    def equals(self, other):
        return self.numero == other.numero
    
    def older(self, other):
        return self.idade > other.idade

    def __str__(self):
        return f"Nome: {self.nome}, Número: {self.numero}, Idade: {self.idade}"
        



if __name__ == "__main__":
    # main_menu()
    str1 = "Hello, "
    str2 = "world!"
    print(joinStrings(str1, str2))
    aluno1 = Aluno("Erica", 123, 21)
    aluno2 = Aluno("Bob", 456, 22)
    aluno1rep = Aluno("Erica", 123, 21)
    
    print(aluno1.__str__())
    print(aluno2.__str__())

    print("Are they the same student?", aluno1.equals(aluno2))
    print("Are aluno1 and aluno1rep the same student?", aluno1.equals(aluno1rep))
    print("Is aluno1 older than aluno2?", aluno1.older(aluno2))

    