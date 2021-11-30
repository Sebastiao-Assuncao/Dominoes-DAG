# Dominoes Sequence Fall

Given a specific sequence of dominoes (assume it is a DAG) represented by:

- 1 line containing 2 integers: the number n of tiles (n>=2) and the number of dependencies m to be described (m>=0)

- m lines containing 2 integers x and y indicating that if tile x falls, then tile y also falls.

Return two integers k and l, where k is the minimum number of interventions needed to guarantee that all dominoes fall e l is the size of the largest sequence of falling dominoes.
