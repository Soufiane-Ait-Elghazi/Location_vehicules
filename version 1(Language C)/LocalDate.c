#include <stdio.h>
#include <time.h>
#include "Common_functions.h"
#include "LocalDate.h"
 date_local LocalDate(){

    date_local x;

    struct tm* local;
    time_t t = time(NULL);

    // Get the localtime
    local = localtime(&t);

    x.a=local->tm_year+1900;
    x.m=local->tm_mon+1;
    x.j=local->tm_mday;

    return x;

 }
