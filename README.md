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

Notice: Be careful, you have to build `mmkp` and `verifier` before running the scripts and the resultants executables must be in the default directory `./cmake-build-debug/`.

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

## Research papers

- https://www.sciencedirect.com/science/article/abs/pii/S0305048317305777