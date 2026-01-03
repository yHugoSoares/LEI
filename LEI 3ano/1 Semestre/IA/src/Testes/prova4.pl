estudante(joao).

inscrito(Nome, Disciplina) :-
    estudante(Nome).

inscrito(joao, ia).

nota(Nome, Disciplina, Nota) :-
    inscrito(Nome, Disciplina).

nota(joao, ia, 15).

distincao(Nome) :-
    nota(Nome, ia, Nota),
    Nota >= 14.

desporto(Nome) :-
    estudante(Nome).

professor_leciona(Nome, Disciplina)


% ==================== Grupo 4 ====================
/*
Pacientes: | ID_P | Nome    | Idade | Diagnóstico | 
           | 1 | Ana Silva. | 45    | Diabetes | 
           | 2 | Carlos Dias| 62    | Hipertensão | 
           | 3 |Maria Santos|  38   | Asma |
           | 4 | João Costa | 71    | Cardiopatia |
           | 5 | Rita Neves | 55 | Diabetes |

Medicamentos:   | ID_M | Nome    | Indicação   | Preço | 
                | 1 | Metformina | Diabetes    | 8,50€ |
                | 2 | Lisinopril | Hipertensão | 5,20€ |
                | 3 | Salbutamol | Asma        | 12,30€|
                | 4 | Atenolol   | Cardiopatia | 6,75€ |
                | 5 | Fluticasona| Asma        | 15,80€|

Prescrições:    | ID_P | ID_M | Data       | Dosagem | 
                | 1    | 1    | 15/11/2024 | Diária |
                | 2    | 2    | 20/10/2024 | 2×dia |
                | 3    | 3    | 01/12/2024 | 3×dia |
                | 4    | 4    | 05/12/2024 | 2×dia |
                | 5    | 1    | 12/11/2024 | Diária |
                | 3    | 5    | 08/12/2024 | 1×dia 
*/

paciente(1, 'Ana Silva', 45, 'Diabetes').
paciente(2, 'Carlos Dias', 62, 'Hipertensão').
paciente(3, 'Maria Santos', 38, 'Asma').
paciente(4, 'João Costa', 71, 'Cardiopatia').
paciente(5, 'Rita Neves', 55, 'Diabetes').

medicamento(1, 'Metformina', 'Diabetes', 8.50).
medicamento(2, 'Lisinopril', 'Hipertensão', 5.20).
medicamento(3, 'Salbutamol', 'Asma', 12.30).
medicamento(4, 'Atenolol', 'Cardiopatia', 6.75).
medicamento(5, 'Fluticasona', 'Asma', 15.80).

prescricao(1, 1, '15/11/2024', 'Diária').
prescricao(2, 2, '20/10/2024', '2×dia').
prescricao(3, 3, '01/12/2024', '3×dia').
prescricao(4, 4, '05/12/2024', '2×dia').
prescricao(5, 1, '12/11/2024', 'Diária').
prescricao(3, 5, '08/12/2024', '1×dia').


% I. Quantos pacientes têm cada diagnóstico?
conta_pacientes_diagnostico(Diagnostico, Total) :-
    findall(ID, paciente(ID, _, _, Diagnostico), Lista),
    length(Lista, Total).

% II. Quais são os medicamentos com preço superior a 10€?
medicacao_cara(Nome, Preco) :-
    medicamento(_, Nome, _, Preco),
    Preco > 10.0.


% III. Que pacientes com idade superior a 60 anos têm asma e qual medicamento tomam?
paciente_idoso_asma(NomePaciente, Medicamento) :-
    paciente(Id_P, NomePaciente, Idade, 'Asma'),
    Idade > 60.