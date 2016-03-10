/*
 *
 *	TO IMPLEMENT THE KOHONEN SOM
 *
 */

#include "ksom.hpp"

//--the weight matrix, assumed to be randomly initialised
float weight_matrix[NUMBER_OF_OUTPUT_NODES][INPUT_VECTOR_DIMENSION];
int repeated_usage_threshold[NUMBER_OF_OUTPUT_NODES] = {0};

//--the actual training vectors
float training_vectors[NUMBER_OF_TRAINING_VECTORS][INPUT_VECTOR_DIMENSION];

float matching[NUMBER_OF_OUTPUT_NODES];

void train_one_iteration(const float &learning_rate, const int &neighbourhood_radius){

 	for(int training_vector_iterator=0;training_vector_iterator<NUMBER_OF_TRAINING_VECTORS; ++training_vector_iterator){

 		//--calculate matching
 		memset(matching, 0, sizeof(float)*NUMBER_OF_OUTPUT_NODES);
 		for(int output_node_iterator=0; output_node_iterator<NUMBER_OF_OUTPUT_NODES; ++output_node_iterator)

 			for(int vector_dimension_iterator=0; vector_dimension_iterator<INPUT_VECTOR_DIMENSION;++vector_dimension_iterator)

 				matching[output_node_iterator] += pow( training_vectors[training_vector_iterator][vector_dimension_iterator] - weight_matrix[output_node_iterator][vector_dimension_iterator]  ,2);

 		//--find best matching
 		std::vector<int> lowest_matching_indices(1,0); float lowest_matching = matching[0];
 		for(int _i=0;_i<NUMBER_OF_OUTPUT_NODES;++_i)
 			if(matching[_i] > lowest_matching)
 				continue;
 			else if(matching[_i] == lowest_matching)
 				lowest_matching_indices.push_back(_i);
 			else{
 				lowest_matching = matching[_i];
 				lowest_matching_indices.clear();
 				lowest_matching_indices.push_back(_i);
 			}

 		int winning_node;
 		//--in case of multiple best matching
 		if(lowest_matching_indices.size() > 1){
 			int lowest_threshold = repeated_usage_threshold[lowest_matching_indices[0]];	winning_node = lowest_matching_indices[0];

 			for(std::vector<int>::iterator it = lowest_matching_indices.begin(); it != lowest_matching_indices.end(); ++it)
 				if(repeated_usage_threshold[*it] < lowest_threshold){
 					lowest_threshold = repeated_usage_threshold[*it];
 					winning_node = *it;
 				}else{}

 		}else	winning_node = lowest_matching_indices[0];

 		//--winning node found
 		adjust_weights_winner_neighbours(winning_node , learning_rate , neighbourhood_radius, training_vector_iterator);
 		++repeated_usage_threshold[winning_node];
 	}
 	return;
 }


 void adjust_weights_winner_neighbours(const int &winning_node , const float &learning_rate, const int &neighbourhood_radius, const int &training_vector_index){

 	for(int vector_dimension_iterator = 0 ;vector_dimension_iterator < INPUT_VECTOR_DIMENSION ; ++vector_dimension_iterator){
 		weight_matrix[winning_node][vector_dimension_iterator] += learning_rate * (training_vectors[training_vector_index][vector_dimension_iterator] - weight_matrix[winning_node][vector_dimension_iterator]);

 		//--adjusting neighbours
 		for(int currnode, neighbour_rad = 1;neighbour_rad <=neighbourhood_radius; ++neighbour_rad){
 			currnode = winning_node+neighbour_rad;
 			float cur_learning_rate = learning_rate/(2<<neighbour_rad);

 			if(cur_learning_rate < minimum_learning_rate)
 				break;else{}

 			weight_matrix[currnode][vector_dimension_iterator] += cur_learning_rate * (training_vectors[training_vector_index][vector_dimension_iterator] - weight_matrix[currnode][vector_dimension_iterator]);

 			currnode = winning_node - neighbour_rad;
 			if(currnode < 0)	continue;
 			else{}
 			weight_matrix[currnode][vector_dimension_iterator] += cur_learning_rate * (training_vectors[training_vector_index][vector_dimension_iterator] - weight_matrix[currnode][vector_dimension_iterator]);
 		}
 	}
 }

void init_ksom_to_zero(){
    for(int i=0; i<NUMBER_OF_OUTPUT_NODES; ++i)
        for(int j=0;j<INPUT_VECTOR_DIMENSION; ++j)
            weight_matrix[i][j] = 0.0f;
}

int find_winner(const float ip_vector[]){
	memset(matching, 0, sizeof(float)*NUMBER_OF_OUTPUT_NODES);

	for(int i=0;i<NUMBER_OF_OUTPUT_NODES;++i)
		for(int j=0;j<INPUT_VECTOR_DIMENSION;++j)
			matching[i] += pow( ip_vector[j]-weight_matrix[i][j] , 2);

	float lowest_matching = matching[0]; int lowest_matching_index = 0;

	for(int i=1;i<NUMBER_OF_OUTPUT_NODES;++i)
		if(matching[i] < lowest_matching){
			lowest_matching_index = i;
			lowest_matching = matching[i];
		}else{}

	return lowest_matching_index;
}

int load_weight_matrix(){
	std::ifstream fin("wtmatrix_trained.txt");
	if(!fin)	return -1; else{}

	for(int i=0;i<NUMBER_OF_OUTPUT_NODES;++i)
		for(int j=0;j<INPUT_VECTOR_DIMENSION;++j)
			fin>>weight_matrix[i][j];

	return 0;
}

void print_weight_matrix(){
	std::cout<<"\nWeight matrix\n";
	for(int i=0;i<NUMBER_OF_OUTPUT_NODES;std::cout<<std::endl,++i)
		for(int j=0;j<INPUT_VECTOR_DIMENSION;++j)
			std::cout<<weight_matrix[i][j]<<" ";

	return;
}
