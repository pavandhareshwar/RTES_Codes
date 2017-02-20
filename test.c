#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define U32_T unsigned int

U32_T ex_period[] = {2, 5, 10};
U32_T ex_wcet[] = {1, 2, 1};


U32_T size = sizeof(ex_period)/sizeof(U32_T);
U32_T task_priority[3];
U32_T task_completed[3];
U32_T curr_high_prio_task = 0;
U32_T time_elapsed[3];
U32_T exec_time_elapsed[3];
U32_T time = 0;

void sort(U32_T *array)
{
    int i, j, a;
    int n = sizeof(ex_period)/sizeof(U32_T);

    for (i = 0; i < n; ++i)
    {
        for (j = i + 1; j < n; ++j)
        {
            if (*(array+i) > *(array+j))
            {
                a =  *(array+i);
                *(array+i) = *(array+j);
                *(array+j) = a;
            }
        }
    }
}

int gcd(int a, int b) {
      if (b == 0) return a;
        return gcd(b, a%b);
}

int lcm(unsigned int *a, int n) {
    int res = 1, i;
    for (i = 0; i < n; i++) 
    {
        res *= (*(a+i)/gcd(res, *(a+i)));
    }
    return res;
}

#if 1
void Assign_Priorities(void)
{
     int i = 0, j = 0;
     U32_T time_diff[size];
     U32_T sorted_time_diff[size];
     U32_T lowest_priority = size;

     for (i = 0; i < size; i++)
     {
        if (task_completed[i] == 1)
            time_diff[i] = 100; /* Some big number to ensure that this service gets lowest priority */
        else
            time_diff[i] = ex_period[i] - time_elapsed[i];    
     }

     for (i = 0; i < size; i++)
         *(sorted_time_diff+i) = *(time_diff+i);

     sort(time_diff);

     for (i = 0; i < size; i++)
     {
         for (j = 0; j < size; j++)
         {
             if (time_diff[i] == sorted_time_diff[j])
             {
                 task_priority[i] = j;
             }
         }
     }

   
     printf("Laxity: ");
     for (i = 0; i < size; i++)
       printf("%d\t", *(sorted_time_diff+i));
    printf("\n");
    
    curr_high_prio_task = task_priority[0];
    //printf("High Priority Task is %d\n", curr_high_prio_task);

}
#else
void Assign_Priorities(void)
{
    U32_T sorted_ex_period[size];
    U32_T i = 0, j = 0;

    for (i = 0; i < size; i++)
    {
        if (task_completed[i] == 1)
            *(sorted_ex_period+i) = 100;
        else
            *(sorted_ex_period+i) = *(ex_period+i);
    }

    sort(sorted_ex_period);

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (ex_period[j] == sorted_ex_period[i])
            {
                task_priority[i] = j;
            }
        }
    }

   curr_high_prio_task = task_priority[0];
   printf("High Priority Task is %d\n", curr_high_prio_task);

}
#endif

int main(void)
{
    U32_T sorted_ex_period[size];
    U32_T i = 0, j = 0, k = 0, l = 0;
    U32_T lcm_period = 0;

#if 0
    printf("Original Period:\n");
    for (i = 0; i < size; i++)
        printf("%d\t", ex_period[i]);
    printf("\n");

    for (i = 0; i < size; i++)
        *(sorted_ex_period+i) = *(ex_period+i);

    sort(sorted_ex_period);
#endif

#if 0
    printf("Sorted Period:\n");
    for (i = 0; i < size; i++)
        printf("%d\t", *(sorted_ex_period+i));
    printf("\n");

    for (i = 0; i < size; i++)
        *(sorted_ex_wcet+i) = *(ex_wcet+i);
    
    sort(sorted_ex_wcet);

    printf("Sorted Exec Time:\n");
    for (i = 0; i < size; i++)
        printf("%d\t", *(sorted_ex_wcet+i));
    printf("\n");
#endif

#if 0
   for (i = 0; i < size; i++)
   {
       for (j = 0; j < size; j++)
       {
           if (ex_period[i] == sorted_ex_period[j])
           {
               task_priority[i] = j;
           }
       }
   }
#endif
   
#if 0
   printf("Assigned Priorities:\n");
   for (i = 0; i < size; i++)
       printf("%d\t", task_priority[i]);
   printf("\n");

#endif
   for (i = 0; i < size; i++)
   {
       task_completed[i] = 0; /* indicates false */
        time_elapsed[i] = 0;
   }

#if 0
   printf("Task Completion Status:\n");
   for (i = 0; i < size; i++)
       printf("%d\t", task_completed[i]);
   printf("\n");

   printf("Time Elapsed:\n");
   for (i = 0; i < size; i++)
       printf("%d\t", time_elapsed[i]);
   printf("\n");
#endif

    for (i = 0; i < size; i++)
        *(exec_time_elapsed+i) = *(ex_wcet+i);

    lcm_period = lcm(ex_period, size);

    printf("LCM Period: %d\n", lcm_period);
        
    while(time < lcm_period)
    {
        for (k = 0; k < size; k++)
        {
            if (time % ex_period[k] == 0)
            {
                printf("Service %d repeat\n", k);
                task_completed[k] = 0;
                *(exec_time_elapsed+k) = *(ex_wcet+k);
            }

        }

        Assign_Priorities();

        if (task_completed[curr_high_prio_task] == 0)
        {
            printf("Task %d, Deadline = %d, Time Elapsed = %d\n", 
                    curr_high_prio_task, ex_period[curr_high_prio_task], time_elapsed[curr_high_prio_task]);
            if ((time_elapsed[curr_high_prio_task] > ex_period[curr_high_prio_task]) || 
                    (ex_wcet[curr_high_prio_task] > (ex_period[curr_high_prio_task] - time_elapsed[curr_high_prio_task])))
            {
                printf("Task %d missed deadline, Deadline = %d, Time Elapsed = %d\n", 
                        curr_high_prio_task, ex_period[curr_high_prio_task], time_elapsed[curr_high_prio_task]);
            }
            else
            {
                printf("Executing Task %d\n", curr_high_prio_task);
                
                exec_time_elapsed[curr_high_prio_task] -= 1;
                
                if (exec_time_elapsed[curr_high_prio_task] == 0)
                {
                    printf("Task %d executed succesfully\n", curr_high_prio_task);
                    task_completed[curr_high_prio_task] = 1; /* Indicating completion of task */
                
                    if (time_elapsed[curr_high_prio_task] != 0)
                        time_elapsed[curr_high_prio_task] = 0;

                }
                
                //time += ex_wcet[curr_high_prio_task] - 1;

                for (l = 0; l < size; l++)
                {
                    if (l != curr_high_prio_task)
                    {
                        if (task_completed[l] == 0)
                        {
                            //time_elapsed[l] += ex_wcet[curr_high_prio_task];
                            time_elapsed[l] += 1;
                        }
                    }
                }
            }
        }

        printf("Time Elapsed:\n");
        for (k = 0; k < size; k++)
            printf("%d\t", time_elapsed[k]);
        printf("\n");

        time++;

        printf("Time Elapsed: %d\n", time);
    }

    return 0;
}
