#include <stdio.h>
#include "structs.h"
#include <time.h>

long long getCurrentRawTime()
{

  time_t rawtime;
  struct tm *info;

  time(&rawtime); // Get current calendar time
  /*  info = localtime(&rawtime); // Convert to local time struct tm

   printf("Current local date and time: %s", asctime(info));

   // Using strftime for custom formatting
   char buffer[80];
   strftime(buffer, sizeof(buffer), "Today is %A, %B %d, %Y. The time is %H:%M:%S.", info);
   printf("%s\n", buffer); */
  return (long long)rawtime;
}