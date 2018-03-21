## Kohonen Self-Organising Map C++ Module

This [repository](https://github.com/sandeepsukumaran/KSOM) contains the C++ code for a [Kohonen Self-Organising map](https://en.wikipedia.org/wiki/Self-organizing_map), developed for use with a face recognition project done during my final year of bachelor's at College of Engineering Trivandrum.

### Files
There are two files in this repository: the cpp code file and the header file used for declarations.

### Using the module
To train the KSOM, the parameters of the network can be set in the _.hpp_ file. Initialisation of the KSOM weight matrix to non-zero values can be achieved by using the _load_weight_matrix_ function. Training iterations are run one at a time by specifying the learning rate and neighbourhood radius for the iteration. Additional functions have to be written for the same.

### Some details of the implementation used
The simple training algorithm used can be found on [Wikipedia](https://en.wikipedia.org/wiki/Self-organizing_map#Algorithm). Distance of neighbours from BMU is taken to be 1.
