/*****************************************************************************/
/*
*	filename:log.c
*	about:
*		C code template main file
*		
*	attention:
*
*	history:
*		2024/11/03:K.Yamada :create this file
*/
/*****************************************************************************/
/*****************************************************************************/
/*                         include headerfile                                */
/*****************************************************************************/
#include <log.h>

/*****************************************************************************/
/*                               define macro                                */
/*****************************************************************************/
/*none*/

/*****************************************************************************/
/*                         define variable (global)                          */
/*****************************************************************************/
char log_time_txt[256];

/*****************************************************************************/
/*                         define structure (global)                         */
/*****************************************************************************/
/*none*/

/*****************************************************************************/
/*                         define type (global)                              */
/*****************************************************************************/
/*none*/

/*****************************************************************************/
/*                                 define function                           */
/*****************************************************************************/
/*
*	function name:test_function
*	about:
*		log test function
*
*	out	char* 				:pointer variable to real time string(log_time_txt)
*/
char* LOG_TIME()
{
    struct timeval tv;
    struct tm *tm_info;
    // 現在時刻を取得（秒とミリ秒）
    gettimeofday(&tv, NULL);

    // 秒部分をlocaltimeで変換
    tm_info = localtime(&tv.tv_sec);

	strftime(log_time_txt, sizeof(log_time_txt), "%Y/%m/%d %H:%M:%S", tm_info);

    // 変数 num を文字列に変換して結合
    char num_str[32];
    sprintf(num_str, ".%03ld", tv.tv_usec / 1000);  // 数値を文字列に変換

    // str に num_str を追加
    strcat(log_time_txt, num_str);

	return log_time_txt;
}

/*
*	function name:test_function
*	about:
*		log test function
*
*	out	int 				:error code
*/
int setup_write_log(const char *filename){
	int ret = 0;
    long size = get_file_size(filename);

	for (int i = 0; i < 5; i++)
	{
		if (size != -1) {
			// printf("File size: %ld bytes\n", size);
			return -1;
		}else if (LOG_FILE_MAX_SIZE * 1000000 < size)
		{
			remove_first_line(filename);
		}
	}
	
	return ret;
}

/*
*	function name:test_function
*	about:
*		log test function
*
*	out	int 				:error code
*/
long get_file_size(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Failed to open file");
        return -1;
    }

    // ファイルの終端にシーク
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Failed to seek file");
        fclose(file);
        return -1;
    }

    // 現在の位置（ファイルサイズ）を取得
    long size = ftell(file);
    if (size == -1) {
        perror("Failed to tell file size");
    }

    fclose(file);
    return size;
}

/*
*	function name:test_function
*	about:
*		log test function
*
*	out	int 				:error code
*/
void remove_first_line(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    // 一時ファイルを作成
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Failed to create temp file");
        fclose(file);
        return;
    }

    char buffer[1024];
    int is_first_line = 1;

    // 元のファイルから行を読み込み、一時ファイルに書き込む
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (is_first_line) {
            is_first_line = 0; // 最初の行をスキップ
        } else {
            fputs(buffer, temp); // 2行目以降を一時ファイルに書き込む
        }
    }

    fclose(file);
    fclose(temp);

    // 元のファイルを削除し、一時ファイルをリネーム
    if (remove(filename) != 0) {
        perror("Failed to remove original file");
        return;
    }
    if (rename("temp.txt", filename) != 0) {
        perror("Failed to rename temp file");
        return;
    }

    printf("First line removed successfully.\n");
}

/*
*	function name:test_function
*	about:
*		log test function
*
*	out	int 				:error code
*/
int test_function(void)
{
	FILE *fp;
	fp = fopen("file_never_exist", "r");
	if(fp == NULL) {
		ERRORMSG("%s", strerror(errno));
		return -1;
	}
	fclose(fp);
	return 0;
}
