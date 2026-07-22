<p align="center">
  <strong>Operating Systems</strong>
</p>

This repository contains two projects developed for the **Operating Systems** course at the Federal University of São Paulo, implemented in C. The first project simulates the page replacement algorithm with aging (Aging), modeling RAM and swap memory behavior with multiple processes. The second project implements a simplified command-line shell with support for process execution and basic commands.

## Objective

- Understand and simulate page replacement algorithms in virtual memory.
- Implement the Aging algorithm for selecting the victim page during replacement.
- Develop a simplified command-line shell, understanding the process execution cycle in Unix-like operating systems.
- Explore system calls (syscalls) for process creation and management.

## Technologies Used

- **Language:** C (C99/ANSI standard)
- **Compiler:** gcc
- **Operating System:** Linux
- **Libraries:** `stdio.h`, `stdlib.h`, `stdbool.h`, `time.h`, `sys/time.h`, `unistd.h`

## Project Structure

```bash
SO/
├── Paginação/            # Page replacement simulator
│   ├── prgrm.c           # Entry point — initializes memory and runs the simulation
│   ├── const.h           # Simulation constants, parameters, and types
│   ├── process.h         # Creation and execution of simulated processes
│   ├── page.h            # Operations on pages (get, set, swap)
│   ├── memory.h          # RAM and swap memory management
│   ├── aging.h           # Aging algorithm for victim page selection
│   └── data/             # Simulation output data
└── SHELL/
    ├── cmd_final.c        # Simplified shell implementation
    └── cmd_final          # Compiled executable
```

## Project 1 — Page Replacement Simulator with Aging

### Description

Simulates a virtual memory system with **100 processes**, each having pages distributed between RAM and a swap area. In each cycle, processes attempt to access their pages with a controlled probability (parameter `CHANCE`). In case of a **page miss**, the system chooses a victim page for replacement using the **Aging** algorithm (if enabled) or random selection.

The simulation records the number of page misses over time and prints the results in the terminal.

### Configurable Parameters (`const.h`)

| Parameter | Default Value | Description |
|-----------|---------------|-------------|
| `N_PRCS` | 100 | Number of simulated processes |
| `RAM_SIZE` | 1000 | RAM size in pages |
| `N_PGS` | calculated | Pages per process |
| `N_SW_PGS` | 2 | Swap pages per process |
| `UNIVERSE` | 10000 | Probability universe |
| `CHANCE` | 9900 (99%) | Page access probability |
| `N_CICLES` | 100000 | Total simulation cycles |
| `CICLES` | 10 | Result printing interval |
| `ENABLE` | 0 | Enable Aging (`1`) or Random (`0`) |

### Aging Algorithm

The Aging algorithm uses a **reference bit register** (`shftr`, typically 8 bits) for each page:
- In each cycle, the bit is shifted to the right (aging).
- If the page was accessed, the most significant bit is set (`AGE_RFRSH`).
- The page with the lowest value in the register (least recently accessed) is chosen as the victim.

### Source Code Files

- **`const.h`:** Defines all simulation parameters, data structures (`prcs`, `pg`, `mm`), and includes necessary libraries.
- **`process.h`:** Implements process creation (`crtPrcss`), execution of an access cycle (`runPrcss`), and page miss handling (`pageMiss`).
- **`memory.h`:** Implements memory creation (`crtMem`) and page swapping between RAM and swap (`swap`).
- **`aging.h`:** Implements the page replacement victim selection algorithm using aging (`choosePg`).
- **`page.h`:** Page read and write operations (`getPg`, `setPg`).

## Project 2 — Simplified Shell

### Description

Implements a C-based **command-line shell** that accepts and executes user commands. The shell manages the creation of child processes via `fork()` and program execution with `exec()`, following the standard cycle of a Unix command interpreter.

## How to Run the Project

### Page Replacement Simulator

```bash
git clone https://github.com/g-reale/SO.git
cd SO/Paginação

# Compile
gcc -o pr prgrm.c

# Execute
./pr
```

The output displays the configuration parameters and, every 10 cycles, the accumulated number of page misses:

```
CONST AMOUNTS: N_PAGES X, N_SW_PGS X, N_RAM_PGS X, N_PRCS 100, ...
0       0
10      42
20      89
...
```

### Simplified Shell

```bash
cd SO/SHELL

# Compile
gcc -o cmd_final cmd_final.c

# Execute
./cmd_final
```

## Environment Setup

- **gcc** installed
- Operating System: Linux

```bash
# Verify gcc version
gcc --version
```

## Workflow — Page Replacement

1. RAM and swap memories are created and initialized.
2. 100 processes are created, with their pages distributed between RAM and swap.
3. In each cycle, each process tries to access its pages with a probability of `CHANCE/UNIVERSE`.
4. In case of a page miss, a victim page is selected (Aging or random) and replaced.
5. Every `CICLES` cycles, the total number of page misses is printed.
6. The aging bit for each RAM page is updated at the end of each cycle.

## Notes

- To enable the Aging algorithm (instead of random selection), change `ENABLE` to `1` in `const.h` and recompile.
- The two projects are independent of each other.
- The page replacement simulator does not have a graphical interface; all output is text-based.

---

<p align="center">
  <strong>Sistemas Operacionais</strong>
</p>

Este repositório contém dois projetos desenvolvidos na disciplina de **Sistemas Operacionais** realizada na Universidade Federal de São Paulo, implementados em linguagem C. O primeiro simula o algoritmo de substituição de páginas com envelhecimento (Aging), modelando o comportamento de memória RAM e swap com múltiplos processos. O segundo implementa um shell simplificado em linha de comando com suporte a execução de processos e comandos básicos.

## Objetivo

- Compreender e simular o funcionamento de algoritmos de substituição de páginas em memória virtual.
- Implementar o algoritmo de Aging para escolha da página vítima na substituição.
- Desenvolver um shell de linha de comando simplificado, entendendo o ciclo de execução de processos em sistemas operacionais Unix-like.
- Explorar chamadas de sistema (syscalls) para criação e gerenciamento de processos.

## Tecnologias Utilizadas

- **Linguagem:** C (padrão C99/ANSI)
- **Compilador:** gcc
- **Sistema operacional:** Linux
- **Bibliotecas:** `stdio.h`, `stdlib.h`, `stdbool.h`, `time.h`, `sys/time.h`, `unistd.h`

## Estrutura do Projeto

```bash
SO/
├── Paginação/            # Simulador de substituição de páginas
│   ├── prgrm.c           # Ponto de entrada — inicializa memória e executa a simulação
│   ├── const.h           # Constantes, parâmetros e tipos da simulação
│   ├── process.h         # Criação e execução de processos simulados
│   ├── page.h            # Operações sobre páginas (get, set, swap)
│   ├── memory.h          # Gerenciamento da memória RAM e swap
│   ├── aging.h           # Algoritmo de Aging para escolha de página vítima
│   └── data/             # Dados de saída da simulação
└── SHELL/
    ├── cmd_final.c        # Implementação do shell simplificado
    └── cmd_final          # Executável compilado
```

## Projeto 1 — Simulador de Paginação com Aging

### Descrição

Simula um sistema de memória virtual com **100 processos**, cada um possuindo páginas distribuídas entre RAM e área de swap. A cada ciclo, os processos tentam acessar suas páginas com probabilidade controlada (parâmetro `CHANCE`). Em caso de **page miss**, o sistema escolhe uma página vítima para substituição utilizando o algoritmo de **Aging** (se habilitado) ou seleção aleatória.

A simulação registra o número de page misses ao longo do tempo e imprime os resultados no terminal.

### Parâmetros Configuráveis (`const.h`)

| Parâmetro | Valor padrão | Descrição |
|-----------|--------------|-----------|
| `N_PRCS` | 100 | Número de processos simulados |
| `RAM_SIZE` | 1000 | Tamanho da RAM em páginas |
| `N_PGS` | calculado | Páginas por processo |
| `N_SW_PGS` | 2 | Páginas no swap por processo |
| `UNIVERSE` | 10000 | Universo de probabilidade |
| `CHANCE` | 9900 (99%) | Probabilidade de acesso à página |
| `N_CICLES` | 100000 | Total de ciclos da simulação |
| `CICLES` | 10 | Intervalo de impressão de resultados |
| `ENABLE` | 0 | Habilita Aging (`1`) ou aleatório (`0`) |

### Algoritmo de Aging

O algoritmo de Aging usa um **registrador de bit de referência** (`shftr`, tipicamente 8 bits) para cada página:
- A cada ciclo, o bit é deslocado à direita (aging).
- Se a página foi acessada, o bit mais significativo é setado (`AGE_RFRSH`).
- A página com menor valor no registrador (menos acessada recentemente) é escolhida como vítima.

### Códigos-fonte

- **`const.h`:** Define todos os parâmetros da simulação, as estruturas de dados (`prcs`, `pg`, `mm`) e inclui as bibliotecas necessárias.
- **`process.h`:** Implementa a criação de processos (`crtPrcss`), a execução de um ciclo de acesso (`runPrcss`) e o tratamento de page miss (`pageMiss`).
- **`memory.h`:** Implementa criação da memória (`crtMem`) e a troca de páginas entre RAM e swap (`swap`).
- **`aging.h`:** Implementa o algoritmo de escolha de página vítima por envelhecimento (`choosePg`).
- **`page.h`:** Operações de leitura e escrita de páginas (`getPg`, `setPg`).

## Projeto 2 — Shell Simplificado

### Descrição

Implementa um **shell de linha de comando** em C que aceita e executa comandos do usuário. O shell gerencia criação de processos filho via `fork()` e execução de programas com `exec()`, seguindo o ciclo padrão de um interpretador de comandos Unix.

## Como Executar o Projeto

### Simulador de Paginação

```bash
git clone https://github.com/g-reale/SO.git
cd SO/Paginação

# Compilar
gcc -o pr prgrm.c

# Executar
./pr
```

A saída exibe os parâmetros de configuração e, a cada 10 ciclos, o número acumulado de page misses:

```
CONST AMOUNTS: N_PAGES X, N_SW_PGS X, N_RAM_PGS X, N_PRCS 100, ...
0       0
10      42
20      89
...
```

### Shell Simplificado

```bash
cd SO/SHELL

# Compilar
gcc -o cmd_final cmd_final.c

# Executar
./cmd_final
```

## Configuração do Ambiente

- **gcc** instalado
- Sistema operacional: Linux

```bash
# Verificar gcc
gcc --version
```

## Fluxo de Funcionamento — Paginação

1. A memória RAM e o swap são criados e inicializados.
2. 100 processos são criados, com suas páginas distribuídas entre RAM e swap.
3. A cada ciclo, cada processo tenta acessar suas páginas com probabilidade `CHANCE/UNIVERSE`.
4. Em caso de page miss, uma página vítima é selecionada (Aging ou aleatório) e substituída.
5. A cada `CICLES` ciclos, o número total de page misses é impresso.
6. O bit de envelhecimento de cada página da RAM é atualizado ao final de cada ciclo.

## Observações

- Para habilitar o algoritmo de Aging (em vez da seleção aleatória), altere `ENABLE` para `1` em `const.h` e recompile.
- Os dois projetos são independentes entre si.
- O simulador de paginação não possui interface gráfica; toda a saída é via terminal.
