#include "include.h"

#define MAX_CHAR 1000

bool shell_exit = false;
int line_num = 0;

#include "history.h"
#include "directory.h"

int set_config(const char * file_name){
	FILE * fp;

	int rc = 0;
	struct stat stat_buf;

	if(0 == (rc = stat (file_name, &stat_buf))){
		fp = fopen(file_name, "r");

		if(NULL == fp){
			printf("Error opening file %s: %s \n", file_name, strerror(errno));
			return errno;
		}

		char str[MAX_CHAR];
		while(fgets(str, MAX_CHAR, fp) != NULL){
			//do something
		}
		fclose(fp);
		return 0;
	}
	else{
		printf("Failed to locate config.sh: %s \n", strerror(errno));
		return rc;
	}
}

int is_not_empty(char * str){
	char * p = str;

	while(*p != '\0'){
		if (!isspace(*p)){
			return 0;
		}
		p++;
	}
	return 1;
}

char * read_line(){
	size_t size = 0;
	char * input_buffer = NULL;

    size_t rc = getline(&input_buffer, &size, stdin);

//    printf("%zu characters were read.\n",rc);
//    printf("You typed: '%s'\n", input_buffer);

	if( -1 == rc){
		printf("Failed to read line: %s\n", strerror(errno));
		return NULL;
	}

	if(0 == is_not_empty(input_buffer)){
		line_num++;
		if(use_history){
			//enqueue(history_queue, input_buffer);
		}
		printf("hi\n");
		return input_buffer;
	}
	return NULL;
}

void parse_and_execute_line(char * input_buffer){
	//get rid of  leading white space

	while(isspace(*input_buffer)) input_buffer++;

	if (0 == strcmp(input_buffer, "exit\n")){
		shell_exit = true;
		printf ("exiting . . .\n");
		return;
	}
	else if (0 == strcmp(input_buffer, "history\n") && use_history){
		//print_queue(history_queue);
	}
	else if (0 == strncmp(input_buffer, "ls", 2)){
		printf("ls");
	}
	else if (0 == strncmp(input_buffer, "cd", 2)){
		printf("ls");
	}
	else if (0 == strncmp(input_buffer, "pwd", 3)){
		printf("%s\n", cwd);
	}
	else{
		//parse and get arguments
		//ignore if invalid command
		printf("hi2\n");
	}
}

void shell_loop(){
	char * input_buffer = NULL;
	cwd = get_pwd();

	//history_queue = create_queue(50);

	if(NULL == history_queue){
		use_history = false;
	}
	else{
		use_history = true;
	}

	while(!shell_exit){
		printf("# ");

		input_buffer = read_line();

		if( NULL != input_buffer){
			parse_and_execute_line(input_buffer);
		}
//		else{
//			printf("Empty line\n");
//		}

		free(input_buffer);
		input_buffer = NULL;
	}
	//cleanup_queue(history_queue);
}

int main(int argc, char *argv[]){

	if (0 != set_config("config.txt")){
		printf("Using default configurations.\n");
	}

	shell_exit = false;
	shell_loop();
	return 0;
}
