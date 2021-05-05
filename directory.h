#include "include.h"

char * cwd;

void shell_ls(){

}

void shell_cd(){

}

char * get_pwd(){
	char * pwd;
	if (NULL != getcwd(pwd, MAX_CHAR*5)){
		return pwd;
	}
	return strerror(errno);
}
