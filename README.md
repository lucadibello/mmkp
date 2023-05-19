# MMKP - Multiple-Choice Multidimensional Knapsack Problem<!-- omit in toc -->

## Table of contents<!-- omit in toc -->

- [1. Problem description](#1-problem-description)
- [2. Mathematical representation](#2-mathematical-representation)
  - [2.1. Sets / Domains](#21-sets--domains)
  - [2.2. Data](#22-data)
  - [2.3. Mathematical model](#23-mathematical-model)
  - [2.4. Input data format](#24-input-data-format)
- [3. Developed algorithms \& solvers](#3-developed-algorithms--solvers)
  - [3.1. AMPL solver (exact)](#31-ampl-solver-exact)
  - [3.2. Greedy algorithm (heuristic)](#32-greedy-algorithm-heuristic)
  - [3.3. Local search algorithm (heuristic)](#33-local-search-algorithm-heuristic)
  - [3.4. Simulated annealing algorithm (metaheuristic)](#34-simulated-annealing-algorithm-metaheuristic)
- [4. Testing instances](#4-testing-instances)
- [5. Academic papers](#5-academic-papers)
- [6. Utility scripts](#6-utility-scripts)
  - [6.1. Start MMKP](#61-start-mmkp)
  - [6.2. Start verifier](#62-start-verifier)
  - [6.3. Runner](#63-runner)
- [7. Authors](#7-authors)

## 1. Problem description

This is an implementation of the Multiple-Choice Multidimensional Knapsack Problem using C++. The MMKP involves selecting items from a given set, where each item has multiple attributes or dimensions. The goal is to maximize the total value of the selected items while respecting the capacity constraints of the knapsack.

The problem can be defined as follows:

- We are given a set of items, each with its own set of attributes or dimensions.
- Each item has a value and a weight associated with it.
- The knapsack has a limited capacity in terms of weight and possibly other constraints.
- The goal is to select a subset of items that maximizes the total value while ensuring that the selected items do not exceed the knapsack's capacity.

## 2. Mathematical representation

### 2.1. Sets / Domains

- $N$: Sets of items divided in
- $J = (J_1, J_2, ..., J_n)$: $n$ disjoint classes
- $C = (C^1, C^2, ..., C^m)$: Resource vector of size $m$ (constrained multidimensional capacity of the knapsack)

### 2.2. Data

- $n$: Number of classes
- $m$: Number of resources
- $r_i = |J_i|$: Number of items in each class
- $v_{i,j}$: Value of item $j \in \{1..r_i\}$ for class $i \in \{1..n\}$
- $w^k_{i,j}$: Weight of item $j \in \{1..r_i\}$ for class $i \in \{1..n\}$, for the resource $k \in \{1..m\}$

### 2.3. Mathematical model

$$
\begin{align*}
    z & = \min \sum_{i=1}^n \sum_{j=1}^{r_i} v_{i,j} * x_{i,j} \\
    subject\ to & \sum_{i=1}^n \sum_{j=1}^{r_i} w^k_{i,j} * x_{i,j} \leq C^k & \forall k \in \{1..m\} \\
    & \sum_{j=1}^{r_i} x_{i,j} = 1 & \forall i \in \{1..n\} \\
    & x_{i,j} \in \{0,1\}
\end{align*}
$$

### 2.4. Input data format

```latex
N M 
Q1 Q2 Q3 ... QM
I1
V1 W111 W112 W113 .. W11M
V2 W121 W122 W123 .. W12M
...
VJ WJ1 WJ2 WJ3 .. WIJM
```

Where:

- $N$ = Number of classes
- $M$ = Number of resources
- $Q_m$ = Capacity of the m-th resource $\forall m \in \{1..M\}$
- $I_n$ = Number of items on the n-th class $\forall n \in \{1..N\}$
- $V_ij$ = Value of the item j on the i-th class $\forall i \in \{1..N\}, \forall j \in \{1..I_i\}$
- $W_ijm$ = Weight of the item j on the i-th class for the m-th resource $\forall i \in \{1..N\}, \forall j \in \{1..I_i\}, \forall m \in \{1..M\}$

## 3. Developed algorithms & solvers

### 3.1. AMPL solver (exact)

We have developed an AMPL solver using [CPLEX](https://www.ibm.com/products/ilog-cplex-optimization-studio/cplex-optimizer) to provide an exact solution for the MMKP (Multiple-Choice Multidimensional Knapsack Problem). By formulating the problem as a mathematical model and utilizing the power of CPLEX, we can obtain the optimal solution. However, it is important to note that since the problem is NP-hard, computing the solution may take a considerable amount of time.

For convenience, we have made the AMPL mathematical model available in the ./src/ampl directory, consisting of the mmkp.mod and mmkp.run files. These files contain the formulation of the problem and the instructions for running the solver. Additionally, to facilitate the process and eliminate the need to install AMPL, we have provided a Jupyter Notebook that allows you to execute the model and visualize the results directly.

You can access the Jupyter Notebook by following this link: [MMKP.ipynb](./ampl/mmkp.ipynb)

> Please note that the free CPLEX license provided by AMPL has a limitation of solving instances with up to 500 variables and constraints. If you are dealing with larger problem instances, it will be necessary to obtain a license by purchasing it from the appropriate sources.

### 3.2. Greedy algorithm (heuristic)

The solution is an alternative to the well-known MMKP relaxation solution. It works as follows:

- **Class sorting**: In this step, the algorithm sorts the classes based on the average weight divided by the remaining knapsack capacity for each resource. The class ratio formula used is:

$$
\begin{align*}
    ratio_{class} = \sum_{c=1}^m \frac{\sum_{n=1}^N w^c_{i,n}}{C^c} \forall i \in n
\end{align*}
$$

> Notice: somehow GitHub does not render the formula correctly, please refer to the [PDF](./docs/MMKP_Greedy.pdf) for the correct formula.

This sorting enables prioritizing the classes that have a higher average weight relative to the remaining capacity.

- **Item sorting**: Once the classes are sorted, the algorithm proceeds to sort the items within each class. The sorting is based on the value, weight, and the remaining knapsack capacity. The item ratio formula used is:

$$
\begin{align*}
    ratio_{item} = \sum_{j=1}^{r_i} \sum_{k=1}^{m} \frac{w^k_{i,j}}{C^k} \forall i \in n
\end{align*}
$$

This ratio considers the weight of the item in each resource and the corresponding remaining capacity, allowing for the selection of items that contribute significantly to the overall value.

By employing the Greedy Algorithm, the MMKP can be solved efficiently. However, it is important to note that this approach may not always yield the optimal solution but provides a good approximation given the time constraints. The Greedy Algorithm offers a practical heuristic for tackling the MMKP and can be a valuable tool in situations where an exact solution is not required or feasible within the given time frame.

### 3.3. Local search algorithm (heuristic)

Our local search algorithm for MMKP addresses the challenges of a large search space and potential local optima. It employs a 2-OPT random double item swap as the neighborhood function. Starting with a random solution, the algorithm iteratively improves it by applying the neighborhood function.

The random double item swap for two different classes consistently yields the best results. However, the algorithm has no predefined stop condition, and it continues searching until a SIGINT signal is received.

The initial solution is generated using the greedy algorithm discussed earlier. This heuristic approach provides a reasonable starting point for subsequent iterative improvements.

By employing this local search algorithm, we overcome the challenges of the MMKP search space and local optima. The 2-OPT random double item swap and iterative improvement process enhance the solution quality, allowing us to find optimal or near-optimal solutions to the problem.

> Since the algorithm continues searching until a SIGINT signal is received, we strongly suggest running the algorithm using the script provided in [this section](#6-utility-scripts) to set a time limit.

### 3.4. Simulated annealing algorithm (metaheuristic)

The local search algorithm has a drawback of getting stuck in local optima, as it only accepts better solutions. This limitation restricts the exploration of potentially better solutions that could represent the global optima. To overcome this issue, we have implemented a simulated annealing algorithm, which takes a probabilistic approach by accepting worse solutions to escape local optima and explore a broader range of potential solutions.

The neighborhood generation in the simulated annealing algorithm utilizes the same 2-OPT random-swap neighborhood function discussed in the local search algorithm.

The Neighborhood is generate using the same 2-OPT random-swap Neighborhood function discussed in the Local Search algorithm.

The algorithm incorporates two crucial parameters:

1. The first parameter is the *temperature* ($C$), which controls the acceptance probability of worse solutions. Initially, the temperature is set to a high value, and it gradually decreases as the algorithm progresses. The temperature value influences the extent to which the algorithm explores the search space, including potentially suboptimal solutions.

2. The second parameter is the *reduction rate* or *cooling rate* ($L$), which determines the rate at which the temperature decreases during the annealing process. Choosing an appropriate cooling rate is vital for the success of the algorithm and must be determined through experimentation and fine-tuning.

The probability of accepting a worse solution is calculated using the following formula:

$$
\begin{align*}
    P & = e^{\frac{z_{new} - z_{opt}}{C}} \\
    \textit{where} \\
    z_{new} & = \textit{new neighbor solution value} \\
    z_{opt} & = \textit{current optimal solution value}
\end{align*}
$$

By incorporating simulated annealing as a metaheuristic, we mitigate the limitations of the local search algorithm and enable exploration of a wider range of solution space. The acceptance of worse solutions in a controlled manner allows the algorithm to escape local optima and potentially converge towards the global optima.

It is worth noting that the effectiveness of the simulated annealing algorithm depends on appropriately setting the temperature and cooling rate parameters, which may require experimentation and adjustment for optimal performance.

> Since the algorithm continues searching until a SIGINT signal is received, we strongly suggest running the algorithm using the script provided in [this section](#6-utility-scripts) to set a time limit.

## 4. Testing instances

To evaluate the performance of the algorithms, we have prepared two sets of instances for testing purposes. The first set consists of standard instances, which includes 261 instances. You can access these instances [here](./data/standard/). The second set comprises larger instances, with a total of 25 instances, and you can find them [here](./data/large/).

For reference and comparison, we have compiled the best known solutions for both sets of instances in the file [solutions.csv](./data/solutions.csv). This file provides the benchmark solutions against which the algorithm results can be measured.

By utilizing these testing instances, you can assess the effectiveness and efficiency of the algorithms in solving the MMKP. The standard set provides a diverse range of instances, while the large set offers more challenging scenarios. Referencing the best known solutions enables you to evaluate the quality of the algorithm outputs and compare them with the optimal or near-optimal solutions.

## 5. Academic papers

- [The multiple-choice multidimensional knapsack problem - Greedy implementation](./docs/MMKP_Greedy.pdf)

- [The multiple-choice multidimensional knapsack problem - Local search implementation](./docs/MMKP_LocalSearch.pdf)

- [The multiple-choice multidimensional knapsack problem - Metaheuristic implementation](./docs/MMKP_Metaheuristic.pdf)

## 6. Utility scripts

> Notice: Be careful, you have to build `mmkp` and `verifier` before running the scripts and the compiled executables must be in the default directory `./cmake-build-debug/`.

### 6.1. Start MMKP

`start-mmkp` is a script that runs the algorithm for a single instance and saves the results in a file named `<instance_name>.txt.out`. The script creates also a file named `<instance_name>.txt.time` with the time spent to compute the solution.

```bash
./start-mmkp.sh <instance> <seconds> [-v]
```

With the `-v` option the script prints the program output to the standard output, by default the output is redirected to avoid cluttering the terminal. 

### 6.2. Start verifier

`start-verifier` is a script that verifies the solution of a single instance. The script verifies that the solution is feasible and that has not exceeded the time limit (by default is 60s).

```bash
./start-verifier.sh <instance>
```

### 6.3. Runner

`runner` is a script that runs the algorithm for all the instances (standard and large) and check the results against the optimal solutions. The script verifies that the solution is feasible and that has not exceeded the time limit (by default is 60s).

This script embeds the `start-mmkp` and `start-verifier` scripts.

```bash
bash runner.sh <seconds> [--skip-compute] [--only-standard]
```

With the `--skip-compute` option the script does not run the algorithm, it only verifies the results. With the `--only-standard` option the script runs the algorithm only for the standard instances, by default it runs the algorithm for both standard and large instances.
In the other hand, with the `--skip-compute` option the script does not run the algorithm, it only verifies the results for the instances that have already been computed.

If you combine the `--skip-compute` and `--only-standard` options, the script verifies the results for the standard instances only. 

## 7. Authors

- Luca Di Bello <luca.dibello@student.supsi.ch>
- Mattia Dell'Oca <mattia.delloca@student.supsi.ch>
- Manuele Nolli <manuele.nolli@student.supsi.ch>