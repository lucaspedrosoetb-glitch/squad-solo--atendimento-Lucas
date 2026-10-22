# Sistema de Atendimento — Hospital Campo Real

Triagem digital de pacientes implementada em C++ com **três estruturas de dados lineares construídas manualmente** (sem STL): Fila, Pilha e Lista Encadeada.

**Integrantes:** Lucas Pedroso
**Disciplina:** PSC II — Engenharia de Software — Campo Real (Prof. Giovane Galvão)

## Estruturas utilizadas

| Requisito | Estrutura | Função no sistema |
|-----------|-----------|-------------------|
| R1 | Fila (FIFO) | Pacientes aguardando atendimento: entram por trás, saem pela frente |
| R2 | Pilha (LIFO) | Histórico de atendimentos concluídos; o último fica no topo |
| R3 | Lista encadeada | Médicos de plantão em ordem de disponibilidade; após atender, voltam ao final da lista |
| R4 | Relatório | Imprime o histórico do topo à base, sem destruir os dados (usa pilha auxiliar) |

Todas as estruturas usam a struct `No` fornecida. Todo `new` possui o `delete` correspondente (verificado com AddressSanitizer).

## Como compilar

Requer `g++` com suporte a C++17.

```bash
g++ -std=c++17 -Wall -o atendimento atendimento_template.cpp
```

O código compila sem warnings.

## Como executar

```bash
./atendimento
```

No Windows (PowerShell/CMD): `atendimento.exe`

## Exemplo de saída

```text
╔═══════════════════════════════════════════════════╗
║  Sistema de Atendimento — Squad ________________  ║
╚═══════════════════════════════════════════════════╝

Médicos disponíveis: Dra. Ana Lima -> Dr. Bruno Costa -> Dra. Carla Ramos

Pacientes chegando:
Próximo a ser atendido: Eduardo (urgencia=3)
Total na fila: 4

Simulação de atendimentos:
  [1] Dra. Ana Lima atende Eduardo (urgencia=3)
  [2] Dr. Bruno Costa atende Fernanda (urgencia=1)
  [3] Dra. Carla Ramos atende Gabriel (urgencia=2)
  [4] Dra. Ana Lima atende Helena (urgencia=1)

Médicos disponíveis ao final: Dr. Bruno Costa -> Dra. Carla Ramos -> Dra. Ana Lima

Último atendimento registrado (peek): Dra. Ana Lima → Helena (urgencia=1)

=== Relatório de Atendimentos ===
  1. Dra. Ana Lima → Helena (urgencia=1)
  2. Dra. Carla Ramos → Gabriel (urgencia=2)
  3. Dr. Bruno Costa → Fernanda (urgencia=1)
  4. Dra. Ana Lima → Eduardo (urgencia=3)

Topo após o relatório (deve ser igual ao peek): Dra. Ana Lima → Helena (urgencia=1)
```

## Regras do projeto atendidas

- Nenhuma classe da STL (apenas `<iostream>` e `<string>`).
- Sem vazamento de memória.
- Compilação sem warnings com `-Wall`.
- Um commit por requisito (R1, R2, R3, R4).
