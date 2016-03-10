#include <cmath>
#include <vector>
#include <cstring>
#include <fstream>

const int NUMBER_OF_OUTPUT_NODES = 150;
const int NUMBER_OF_TRAINING_VECTORS = 75;
const int INPUT_VECTOR_DIMENSION = 21;

const float minimum_learning_rate = 0.015625;


void adjust_weights_winner_neighbours(const int &, const float &, const int &, const int &);

void train_one_iteration(const float &, const int &);

void init_ksom();

void init_ksom_to_zero();

int find_winner(const float []);

int load_weight_matrix();

void print_weight_matrix();
