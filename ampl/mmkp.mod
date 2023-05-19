param nc;
param nn;
param nr;

# Sets
set C := 1..nc; # Classes
set N := 1..nn; # Items
set R := 1..nr; # Resources

# Parameters
param q{R};     # Resource capacity
param v{C,N};  # Value of each item in each class
param w{C,N,R};  # Weight of each item in each class and resource

# Variables
var x{C,N} binary;   # Whether each item in each class is selected

# Objective
maximize z: sum{c in C, n in N} v[c,n]*x[c,n];

# Constraints
s.t. capacity_constraint{r in R}:
  sum{c in C, n in N} w[c,n,r]*x[c,n] <= q[r];

s.t. class_constraint{c in C}:
  sum{n in N} x[c,n] = 1;