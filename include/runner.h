/* runner_error_code->type list */
#define E_FORK 0x01
#define E_TIMEOUT_KILL 0x02
#define E_CANNOT_KILL 0x04
//#define E_WAITPID 0x08

typedef struct struct_runner_error_code* runner_error_code;
typedef struct struct_runner_error_code {
	int incomplete; // 0: everything complete, 1: has some error
	int type;
	int exit_code;
} struct_runner_error_code;

runner_error_code
runner (char* target_path, char* input_path, char *output_path);

