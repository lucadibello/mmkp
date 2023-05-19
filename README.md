# MMKP - Multiple-Choice Multidimensional Knapsack Problem

This is an implementation of the Multiple-Choice Multidimensional Knapsack Problem using C++. The MMKP involves selecting items from a given set, where each item has multiple attributes or dimensions. The goal is to maximize the total value of the selected items while respecting the capacity constraints of the knapsack.

The problem can be defined as follows:

- We are given a set of items, each with its own set of attributes or dimensions.
- Each item has a value and a weight associated with it.
- The knapsack has a limited capacity in terms of weight and possibly other constraints.
- The goal is to select a subset of items that maximizes the total value while ensuring that the selected items do not exceed the knapsack's capacity.

## Mathematical representation

### Sets / Domains

- $N$: Sets of items divided in
- $J = (J_1, J_2, ..., J_n)$: $n$ disjoint classes
- $C = (C^1, C^2, ..., C^m)$: Resource vector of size $m$ (constrained multidimensional capacity of the knapsack)

### Data

- $n$: Number of classes
- $m$: Number of resources
- $r_i = |J_i|$: Number of items in each class
- $v_{i,j}$: Value of item $j \in \{1..r_i\}$ for class $i \in \{1..n\}$
- $w^k_{i,j}$: Weight of item $j \in \{1..r_i\}$ for class $i \in \{1..n\}$, for the resource $k \in \{1..m\}$

### Mathematical model

$$
\begin{align*}
    z & = \min \sum_{i=1}^n \sum_{j=1}^{r_i} v_{i,j} * x_{i,j} \\
    subject\ to & \sum_{i=1}^n \sum_{j=1}^{r_i} w^k_{i,j} * x_{i,j} \leq C^k & \forall k \in \{1..m\} \\
    & \sum_{j=1}^{r_i} x_{i,j} = 1 & \forall i \in \{1..n\} \\
    & x_{i,j} \in \{0,1\}
\end{align*}
$$

### Input data format

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

## Developed algorithms & solvers

### AMPL solver (exact)

We have developed an AMPL solver using [CPLEX](https://www.ibm.com/products/ilog-cplex-optimization-studio/cplex-optimizer) to provide an exact solution for the MMKP (Multiple-Choice Multidimensional Knapsack Problem). By formulating the problem as a mathematical model and utilizing the power of CPLEX, we can obtain the optimal solution. However, it is important to note that since the problem is NP-hard, computing the solution may take a considerable amount of time.

For convenience, we have made the AMPL mathematical model available in the ./src/ampl directory, consisting of the mmkp.mod and mmkp.run files. These files contain the formulation of the problem and the instructions for running the solver. Additionally, to facilitate the process and eliminate the need to install AMPL, we have provided a Jupyter Notebook that allows you to execute the model and visualize the results directly.

You can access the Jupyter Notebook by following this link: [MMKP.ipynb](./ampl/mmkp.ipynb)

> Please note that the free CPLEX license provided by AMPL has a limitation of solving instances with up to 500 variables and constraints. If you are dealing with larger problem instances, it will be necessary to obtain a license by purchasing it from the appropriate sources.

### Greedy algorithm (heuristic)

The greedy algorithm starts with an empty knapsack and iteratively selects items based on their individual value-to-weight ratios. At each step, it selects the item with the highest ratio until the knapsack's capacity is reached. This approach provides a fast and reasonable solution, but it may not always yield the optimal solution.

### Local search algorithm (heuristic)

### Simulated annealing algorithm (metaheuristic)




## Academic papers

* [The multiple-choice multidimensional knapsack problem - Greedy implementation](./docs/MMKP_Greedy.pdf)

* [The multiple-choice multidimensional knapsack problem - Local search implementation](./docs/MMKP_LocalSearch.pdf)

* [The multiple-choice multidimensional knapsack problem - Metaheuristic implementation](./docs/MMKP_Metaheuristic.pdf)

## Additional tools

- AMPL solver:
- Bash utility scripts

## Scripts

> Notice: Be careful, you have to build `mmkp` and `verifier` before running the scripts and the compiled executables must be in the default directory `./cmake-build-debug/`.

### Start MMKP

`start-mmkp` is a script that runs the algorithm for a single instance and saves the results in a file named `<instance_name>.txt.out`. The script creates also a file named `<instance_name>.txt.time` with the time spent to compute the solution.

```bash
./start-mmkp.sh <instance> <seconds> [-v]
```

With the `-v` option the script prints the program output to the standard output, by default the output is redirected to avoid cluttering the terminal. 

### Start verifier

`start-verifier` is a script that verifies the solution of a single instance. The script verifies that the solution is feasible and that has not exceeded the time limit (by default is 60s).

```bash
./start-verifier.sh <instance>
```

### Runner

`runner` is a script that runs the algorithm for all the instances (standard and large) and check the results against the optimal solutions. The script verifies that the solution is feasible and that has not exceeded the time limit (by default is 60s).

This script embeds the `start-mmkp` and `start-verifier` scripts.

```bash
bash runner.sh <seconds> [--skip-compute] [--only-standard]
```

With the `--skip-compute` option the script does not run the algorithm, it only verifies the results. With the `--only-standard` option the script runs the algorithm only for the standard instances, by default it runs the algorithm for both standard and large instances.
In the other hand, with the `--skip-compute` option the script does not run the algorithm, it only verifies the results for the instances that have already been computed.

If you combine the `--skip-compute` and `--only-standard` options, the script verifies the results for the standard instances only. 

## Authors

- Luca Di Bello <luca.dibello@student.supsi.ch>
- Mattia Dell'Oca <mattia.delloca@student.supsi.ch>
- Manuele Nolli <manuele.nolli@student.supsi.ch>