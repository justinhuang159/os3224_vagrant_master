#include "types.h"
#include "stat.h"
#include "user.h"

int total_wait = 0, total_run = 0, total_tat = 0;

int
main(void)
{
   int i, pid;
   for(i = 0; i < 20; i++)
   {
      pid = fork();
      if(pid == 0) {
         if(i % 2 == 0) {
            int j, k, total = 0;
            for(j = 0; j < 10000; j++) {
               for(k = 0; k < 10000; k++) {
                  total = j + k - j - k + total;
               }
               //yield();
            }
         }
         else {
            int j, k, total = 0;
            for(j = 0; j < 5000; j++) {
               for(k = 0; k < 5000; k++) {
                  total = j - j + k - k + total;
               }
            }
         }
         exit();
      }
      else if(pid == -1) {
         printf(2, "Fork Failed!\n");
         break;
      }
   }

   int wt = 0, rt = 0, iot = 0, stat = 0, count = 0;
   while(wait_stat(&wt, &rt, &iot, &stat) != -1) {
      total_wait += wt;
      total_run += rt;
      total_tat += (wt + rt + iot);
      printf(0, "Child pid %d has wait=%d, run=%d, tat=%d\n", stat, wt, rt, wt + rt + iot);
      count++;
   }
   printf(0, "Parent Finished...\n");
   printf(0, "Avg. Wait Time = %d\n", total_wait / 20);
   printf(0, "Avg. Run Time  = %d\n", total_run / 20);
   printf(0, "Avg. TAT Time  = %d\n", total_tat / 20);
   exit();
}
