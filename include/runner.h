enum E_Type {
	E_FORK,
	E_TIMEOUT_KILL,
};

typedef struct _runner_error_code {
	enum E_Type type;
	int exit_code;
} runner_error_code;

runner_error_code
runner (char* target_path, char* input_path, char *output_path);

