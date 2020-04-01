
## CS415 Project 2 -- Ari Encarnacion, Vincent Valenzuela

This project implements a program used for a conceptual rental agency. The user inputs a list of clients in the format of `<starting date> <end date> <payment offered for rental period>`. The program will then create a DAG of all clients in which all edges are connected between a client whose end date is less than or equal to another client's start date.

#### Input

Input **must** be in the format:

start1 end1 payment1

for example:

```
10 40 100
50 80 200
70 60 23
```

Input files **must not** have extra spaces after payment nor new line extra characters at the end of the file.

#### Output

The program will output a file named `out<inputfile>.txt` where `<inputfile>`  is the name of the file a user choses to input.


#### Implementation

The program parses a client file and creates a DAG. The DAG is represented in an **adjacency matrix** (extra credit not implemented). An array of all connnected nodes is generated using a topological sort of the DAG. The longest (highest cost) path is then calculated using that array.