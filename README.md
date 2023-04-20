# mmkp

Multiple-choice multidimensional knapsack problem implementation

## Data format

```text
N M 
Q1 Q2 Q3 ... QM
I
V1 W11 W12 W13 .. W1M
V2 W21 W22 W23 .. W2M
...
VI WI1 WI2 WI3 .. WIM

N = Number of classes 
M = Number of resources
Q1 .. QM = Capacity of i-th resource


N classes definition follow:
  I = Number of items on the j-th class
  I items definition follow:
    V1 = Value of the item
    W11 .. W1M = Weight of the item for i-th resource
```

## Scripts

### Start MMKP

`start-mmkp` is a script that runs the algorithm for a single instance and saves the results in a file named `<instance_name>.txt.out`. The script creates also a file named `<instance_name>.txt.time` with the time spent to compute the solution.

```bash
bash start-mmkp <instance>
```

### Start verifier

`start-verifier` is a script that verifies the solution of a single instance. The script verifies that the solution is feasible and that has not exceeded the time limit (by default is 60s).

```bash
bash start-verifier <instance>
```

### Runner

`runner` is a script that runs the algorithm for all the instances (standard and large) and check the results against the optimal solutions. The script verifies that the solution is feasible and that has not exceeded the time limit (by default is 60s).

This script embeds the `start-mmkp` and `start-verifier` scripts.

```bash
bash runner.sh [--skip-compute] [--only-standard]
```

## Research papers

- https://www.sciencedirect.com/science/article/abs/pii/S0305048317305777