#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define U32_T unsigned int

//U32_T ex_period[] = {2, 10, 15};
U32_T ex_period[] = {2, 4, 5};
//U32_T ex_period[] = {10, 2, 15, 5};
U32_T ex_wcet[] = {1, 1, 2};

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

int main(void)
{
    U32_T size = sizeof(ex_period)/sizeof(U32_T);
    U32_T sorted_ex_period[size];
    U32_T task_priority[size];
    U32_T i = 0, j = 0, k = 0, l = 0;
    U32_T task_completed[size];
    U32_T curr_high_prio_task = 0;
    U32_T time_elapsed[size];
    U32_T lcm_period = 0;
    U32_T time = 0;

#if 0
    printf("Original Period:\n");
    for (i = 0; i < size; i++)
        printf("%d\t", ex_period[i]);
    printf("\n");
#endif

    for (i = 0; i < size; i++)
        *(sorted_ex_period+i) = *(ex_period+i);

    sort(sorted_ex_period);

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

    lcm_period = lcm(ex_period, size);

    while(time < lcm_period)
    {
        for (k = 0; k < size; k++)
        {
            if (time % ex_period[k] == 0)
                task_completed[curr_high_prio_task] = 0;
        }
        time++;
    }

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (task_priority[j] == i)
            {
                curr_high_prio_task = task_priority[j];
                printf("High Priority Task is %d\n", curr_high_prio_task);
            }
        }

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
                printf("Task %d executed succesfully\n", curr_high_prio_task);
                task_completed[curr_high_prio_task] = 1; /* Indicating completion of task */
                time_elapsed[curr_high_prio_task] += ex_wcet[curr_high_prio_task];

                for (l = 0; l < size; l++)
                {
                    if (l != curr_high_prio_task)
                    {
                        time_elapsed[l] += ex_wcet[l];
                    }
                }
            }
        }

        printf("Time Elapsed:\n");
        for (k = 0; k < size; k++)
            printf("%d\t", time_elapsed[k]);
        printf("\n");
    }

    return 0;
}
