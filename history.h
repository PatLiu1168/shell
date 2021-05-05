#include "include.h"
/*history uses a queue implementation*/

bool use_history = false;
struct queue * history_queue;

struct queue{
	size_t max_capacity;
	int front, rear, size;
	char (*array)[100]; //should be an array of n arrays of 100 chars
	int * line_num_array;
};

struct queue * create_queue(size_t max){
	struct queue * temp_queue = (struct queue *)malloc(sizeof(struct queue));

    if(NULL == temp_queue){
        printf("Memory could not be allocated for history");
        return false;
    }

	temp_queue->max_capacity = max;
	temp_queue->size = 0;
	temp_queue->front = 0;
	temp_queue->rear = max-1;

	temp_queue->array = malloc(max * (sizeof(char))*100);
	temp_queue->line_num_array = (int*)malloc(max * (sizeof(int)));

    return temp_queue;
}

bool is_full(struct queue * temp_queue){
	return (temp_queue->size == temp_queue->max_capacity);
}

bool is_empty(struct queue * temp_queue){
	return (temp_queue->size == 0);
}

void enqueue(struct queue * temp_queue, int num, char * str){
	if (is_empty(temp_queue)){
		strcpy(temp_queue->array[temp_queue->front], str);
		temp_queue->line_num_array[temp_queue->front] = num;
		(temp_queue->size)++;
	}
	else if (is_full(temp_queue)){
		temp_queue->rear = temp_queue->front;
		(temp_queue->front)++;
		strcpy(temp_queue->array[temp_queue->rear], str);
		temp_queue->line_num_array[temp_queue->rear] = num;
	}
	else{
		strcpy(temp_queue->array[temp_queue->size], str);
		temp_queue->line_num_array[temp_queue->size] = num;
		(temp_queue->size)++;
	}
}

void print_queue(struct queue * temp_queue){
	if (temp_queue->front < temp_queue->rear){
		for (int i = temp_queue->front; i < temp_queue->size; i++ ){
			printf("%i %s", temp_queue->line_num_array[i], temp_queue->array[i]);
		}
	}
	else if (temp_queue->front > temp_queue->rear){
		for (int i = temp_queue->front; i < temp_queue->max_capacity; i++ ){
			printf("%i %s", temp_queue->line_num_array[i], temp_queue->array[i]);
		}
		for (int i = 0; i <= temp_queue->rear ; i++){
			printf("%i %s", temp_queue->line_num_array[i], temp_queue->array[i]);
		}
	}
}



