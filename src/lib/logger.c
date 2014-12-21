#include <stdio.h>
#include <time.h>

#include "globals.h"

void write_log( char* msg, unsigned long value ) {

    FILE *fp;
    char logfile[100];
    sprintf(logfile, "cntp_log_%d.log", globals.src_node);
    time_t logtime;
    struct tm *logtm;

    logtime = time( NULL );
    logtm = localtime( &logtime );

    fp = fopen( logfile, "a" );

    if ( fp ) {
        fprintf(fp,"%04d-%02d-%02d %02d:%02d:%02d - %s : %lu \n", 1900 + logtm->tm_year, logtm->tm_mon + 1,
                logtm->tm_mday, logtm->tm_hour, logtm->tm_min, logtm->tm_sec ,
                msg, value );
        fclose(fp);

    } else {
        printf( "Error opening logfile %s\n", logfile );
    }
}

void write_log_sign( char* msg, long long value ) {

    FILE *fp;
    char logfile[100];
    sprintf(logfile, "cntp_log_%d.log", globals.src_node);
    time_t logtime;
    struct tm *logtm;

    logtime = time( NULL );
    logtm = localtime( &logtime );

    fp = fopen( logfile, "a" );

    if ( fp ) {
        fprintf(fp,"%04d-%02d-%02d %02d:%02d:%02d - %s : %lld \n", 1900 + logtm->tm_year, logtm->tm_mon + 1,
                logtm->tm_mday, logtm->tm_hour, logtm->tm_min, logtm->tm_sec ,
                msg, value );
        fclose(fp);

    } else {
        printf( "Error opening logfile %s\n", logfile );
    }
}

void write_log_msg( char* msg ) {

    FILE *fp;
    char logfile[100];
    sprintf(logfile, "cntp_log_%d.log", globals.src_node);
    time_t logtime;
    struct tm *logtm;

    logtime = time( NULL );
    logtm = localtime( &logtime );

    fp = fopen( logfile, "a" );

    if ( fp ) {
        fprintf(fp,"%04d-%02d-%02d %02d:%02d:%02d - %s\n", 1900 + logtm->tm_year, logtm->tm_mon + 1,
                logtm->tm_mday, logtm->tm_hour, logtm->tm_min, logtm->tm_sec ,
                msg);
        fclose(fp);

    } else {
        printf( "Error opening logfile %s\n", logfile );
    }
}


