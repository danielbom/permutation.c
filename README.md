# Iterative Permutation

Trying to solve the [Einstein Problem](https://www.ahapuzzles.com/logic/zebra/einsteins-puzzle/) years ago, I came to the problem of multiple permutations. I searched in Stack Overflow something to help me and I found this [question](https://stackoverflow.com/questions/3862191/permutation-generator-on-c), where I share the [solution v0](./v0/Perm.h) there.

The [version v1](./v1/permutation.h) is the result of a refactoring. I simplified the interface to handle the permutations using incomplete type (void *).

When I rewrite the solution to the Einstein Problem using the new interface of Permutation, I feel curious about the results (in time and development experience) of passing functions as arguments ([einstein-problem-functions.c](./v1/einstein-problem-functions.c)), using only macros ([einstein-problem-macros.c](./v1/einstein-problem-macros.c)), keeping it simple ([einstein-problem-pure.c](./v1/einstein-problem-pure.c)), or making hybrid solution ([einstein-problem-merge.c](./v1/einstein-problem-merge.c)).

The solution **v2** is only a refactoring of the solution **v1** where I extract the common behavior of [einstein-problem](./v2/einstein-problem.h) and the [main](./v2/einstein-problem-main.h).

# Running

To compile and run, look at the scripts "./run.sh" in each folder, but a simple way is:

```bash
# Choose only one version to compile
gcc v0/einstein.c -o einstein

# "-D=TIME_IT" is optional
gcc v1/einstein-problem-functions.c -o einstein -D=TIME_IT
gcc v1/einstein-problem-macros.c -o einstein -D=TIME_IT
gcc v1/einstein-problem-merge.c -o einstein -D=TIME_IT
gcc v1/einstein-problem-pure.c -o einstein -D=TIME_IT

gcc v2/einstein-problem-functions.c -o einstein -D=TIME_IT
gcc v2/einstein-problem-macros.c -o einstein -D=TIME_IT
gcc v2/einstein-problem-merge.c -o einstein -D=TIME_IT
gcc v2/einstein-problem-pure.c -o einstein -D=TIME_IT

# Execute
./einstein
```
