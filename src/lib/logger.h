#define LOG_PRINT(...) log_print("",0,__VA_ARGS__ )

void write_log( char* msg, unsigned long value );

void write_log_sign( char* msg, long long value );

void write_log_msg( char* msg );
