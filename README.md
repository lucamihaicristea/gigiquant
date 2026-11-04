# GigiQuant — Portfolio Manager

This project was developed for the **Proiectarea Algoritmilor* course at the **Facultatea de Automatica si Calculatoare** (National University of Science and Technology POLITEHNICA Bucharest).

The primary goal of the application is to implement efficient algorithms to solve quantitative finance problems, including performance metrics calculation, arbitrage detection, portfolio optimization, and probabilistic price modeling.

---

## Features & Core Functionality

- **Sharpe Ratio Calculation:** Evaluates risk-adjusted returns for financial assets and portfolios.
- **Arbitrage Opportunity Detection:** Identifies execution paths for arbitrage opportunities across exchange rates.
- **Portfolio Optimization:** Determines optimal asset allocation based on defined constraints.
- **Stock Price Probability Modeling:** Predicts price distributions over a given time horizon.

---

## Data Structures & Algorithms Used

To ensure computational efficiency, the project incorporates:
- **Graphs (Directed Graphs):** Used for modeling exchange pairs and pathfinding.
- **Binary Trees & Custom Structs:** For structured data manipulation and fast lookups.
- **LinkedLists, Stacks & Queues:** Core primitives for data flow and internal state management.

---

## Repository Structure

```text
├── src/
│   ├── interviuri.h      # Main header file (data structures & function prototypes)
│   ├── functii.c         # Core algorithm implementations
│   └── test.c            # Driver code / main entry point
├── in/                   # Input datasets for evaluation
├── ref/                  # Reference outputs for validation
├── Makefile              # Build automation script
└── config.json           # Test runner configurations
```

---

## Getting Started

### Prerequisites

The project is built for Linux environments. On Windows, use **WSL** (Windows Subsystem for Linux).

Install the required verification tools:
```bash
sudo apt update && sudo apt install valgrind cppcheck -y
```
### Building and Running Tests
1. Clone the repository:
```bash
git clone [https://github.com/lucamihaicristea/gigiquant.git](https://github.com/lucamihaicristea/gigiquant.git)
cd gigiquant
```

2. Make the checker executable and run it:
```bash
chmod +x ./checker
./checker
```
