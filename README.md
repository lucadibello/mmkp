# mmkp
Multiple-choice multidimensional knapsack problem implementation


## Research papers:
- https://www.sciencedirect.com/science/article/abs/pii/S0305048317305777

## Data format
```
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
