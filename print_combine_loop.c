#include <sys/ioctl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <ctype.h>

#define SLEEP_DELAY 20000

int get_window_width(){
	struct winsize size;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
        return 80; 
    }
	//unsigned short size.ws_row
	//unsigned short size.ws_col
	int len = (int)(size.ws_col - 1);
	return len > 0 ? len : 80;;
}

char* get_filled_row(char filler,int len){
	char* array = (char*)malloc(len*sizeof(char));
	if (array == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
	memset(array,filler,len);
	array[len-1] = '\0';
	return array;
}

char get_offset_char(char ori,int offset){
	
	char* array = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	int arr_len = (int)strlen(array);
	char ret = ' ';
	for (int i=0;i<arr_len;i++){
		if (array[i]!=ori) continue;
		int char_pos = i + offset;
		while (char_pos>=arr_len) char_pos -= arr_len;
		while (char_pos < 0) char_pos += (arr_len-1);
		ret = array[char_pos];
		break;
	}
	return ret;
}

void printloop_2(char* original, int target_pos){
	int len = get_window_width();
	int orig_len = (int)strlen(original);
	if (target_pos >= orig_len || target_pos >= len) return;
	
	for (int i = len; i >= target_pos; i--){
		char* array=get_filled_row('-',len);
		int copy_len = target_pos < orig_len ? target_pos : orig_len;
		if (copy_len > len - 1) copy_len = len - 1;
		memcpy(array, original, copy_len);
		
		char append = get_offset_char(original[target_pos],(i-target_pos));
		if (!isprint(append)) append = ' ';
		array[i] = append;
		
		printf("%s\r", array);
        fflush(stdout);
        usleep(SLEEP_DELAY);
		free(array);
	}
}

void printloop_1(char* ori){
	int ori_len = (int)strlen(ori);
	for (int i=0;i<ori_len;i++){
		printloop_2(ori,i);
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }
	char* ori = argv[1];
    int ori_len = strlen(ori);
	
	
	printloop_1(ori);
	printf("\n");
    return 0;
}
