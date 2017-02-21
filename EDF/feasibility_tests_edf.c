#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* A simple check to see if the CPU utilization factor is upper bounded by optimal utilization 
** factor (Ub=1), U <= 1, serves as a necessary and sufficient condition for schedulibilty.
** But this is under the assumption that relative deadline is the same as period. For cases
** where relative deadline is less than the period, */

#define TRUE 1
#define FALSE 0
#define U32_T unsigned int
//#define RUN_PROCESSOR_UTIL_TEST 1
//#define RUN_WORST_CASE_RESP_TIME_FEASIBILITY_TEST 1
//#define RUN_TIMING_ANALYSIS_TEST 1

#if defined EX0
// U - CPU utilization factor
// U=0.7333 
U32_T ex_period[] = {2, 10, 15};
U32_T ex_wcet[] = {1, 1, 2};
#elif defined EX1
// U=0.9857
U32_T ex_period[] = {2, 5, 7};
U32_T ex_wcet[] = {1, 1, 2};
#elif defined EX2 
// U=0.9967
U32_T ex_period[] = {2, 5, 7, 13};
U32_T ex_wcet[] = {1, 1, 1, 2};
#elif defined EX3
// U=0.93
U32_T ex_period[] = {3, 5, 15};
U32_T ex_wcet[] = {1, 2, 3};
#elif defined EX4
// U=1.0
U32_T ex_period[] = {2, 4, 16};
U32_T ex_wcet[] = {1, 1, 4};
#elif defined EX5
//U=1.0 
U32_T ex_period[] = {2, 5, 10};
U32_T ex_wcet[] = {1, 2, 1};
#elif defined EX6
//U=1.106 
U32_T ex_period[] = {2, 3, 7, 15};
U32_T ex_wcet[] = {1, 1, 1, 2};
#elif defined EX7
// U=1.0
U32_T ex_period[] = {3, 5, 15};
U32_T ex_wcet[] = {1, 2, 4};
#elif defined EX8
//U=0.9967 
U32_T ex_period[] = {2, 5, 7, 13};
U32_T ex_wcet[] = {1, 2, 1, 2};
#endif

U32_T size = sizeof(ex_period)/sizeof(U32_T);
U32_T task_priority[10];
U32_T task_completed[10];
U32_T curr_high_prio_task = 0;
U32_T time_elapsed[10];
U32_T exec_time_elapsed[10];
U32_T time = 0;

/* EDF Utilization bound schedulibilty test */
int edf_util_bound_sched_test(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);
/* EDF Processor Demand Analysis Test */
int edf_processor_demand_analysis(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);
/*EDF Timing Analysis Test */
int edf_timing_analysis_sched_feasibility_test(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);

void sort(U32_T *array);
int gcd(int a, int b);
int lcm(unsigned int *a, int n);
void Assign_Priorities(void);

int main(void)
{ 
    int i;
    U32_T numServices;
    float cpu_utility = 0.0;

    numServices = sizeof(ex_period)/sizeof(U32_T);
    
    for (i = 0; i < numServices; i++)
    {
        printf("C%d=%d, T%d=%d; ", i, ex_wcet[i], i, ex_period[i]);
        cpu_utility += (float)ex_wcet[i]/(float)ex_period[i];
    }
    
    printf("U = %4.2f\n", cpu_utility);

#ifdef RUN_PROCESSOR_UTIL_TEST
    printf("******** EDF Utility Bound Analysis ********\n");
    
    if(edf_util_bound_sched_test(numServices, ex_period, ex_wcet, ex_period) == TRUE)
        printf("FEASIBLE\n");
    else
    {
        printf("EDF Utility Test is infeasible. Going for Processor Demand Analysis N&S Test\n");
        if(edf_processor_demand_analysis(numServices, ex_period, ex_wcet, ex_period) == TRUE)
            printf("FEASIBLE\n");
        else
            printf("INFEASIBLE\n");
    }

    printf("******** EDF Utility Bound Analysis ********\n");
#endif

#ifdef RUN_WORST_CASE_RESP_TIME_FEASIBILITY_TEST 

    printf("******** EDF Feasibility Analysis (Worst-Case Task Response Time) ********\n");

    if(edf_processor_demand_analysis(numServices, ex_period, ex_wcet, ex_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("******** EDF Feasibility Analysis (Worst-Case Task Response Time) ********\n");
#endif

#ifdef RUN_TIMING_ANALYSIS_TEST
    printf("************ EDF Timing Analysis ************\n");
    
    if(edf_timing_analysis_sched_feasibility_test(numServices, ex_period, ex_wcet, ex_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
    
    printf("************ EDF Timing Analysis ************\n");
#endif
}

int edf_util_bound_sched_test(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[])
{

    int i, j;
    float cpu_util_factor = 0;
    
    int set_feasible = TRUE; /* assume feasible until we find otherwise */

    for (i=0; i < numServices; i++)
    {
        cpu_util_factor += (float)wcet[i]/(float)period[i]; 
    }

    if (cpu_util_factor > 1.0)
    {
        set_feasible = FALSE;
    }

    return set_feasible;
}

int edf_processor_demand_analysis(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[])
{
    int i, j;
    U32_T an, anext; /* time durations over which the processor demand is analysed */

    int set_feasible=TRUE; /* assume service set is feasible until proven otherwise */

    for (i = 0; i < numServices; i++)
    {
        an = 0; anext = 0;

        for (j = 0; j <= i; j++)
        {
            an += wcet[j];
        }

        //printf("i=%d, an=%d\n", i, an);

        anext = wcet[i];

        for (j = 0; j < i; j++)
            anext += (floor(((double)an - (double)deadline[j])/((double)period[j])) + 1) * wcet[j];
    
        //printf("an = %d, anext = %d\n", an, anext);
        if (anext > an)
        {
            set_feasible=FALSE;
            break;
        }
        else
            an = anext;

        //printf("an=%d, anext=%d\n", an, anext);
        
    }

    return set_feasible;
 }

int edf_timing_analysis_sched_feasibility_test(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[])
{
   /* Function is implemented taking the following things into consideration 
   ** 1. Critical Instant - All processes arrive at the same instant
   ** 2. Deadline is the same as period 
   */

    U32_T sorted_ex_period[size];
    U32_T i = 0, j = 0, k = 0, l = 0;
    U32_T lcm_period = 0;

    int set_feasible = TRUE; /* Assume service set is feasible until proven otherwise */

    for (i = 0; i < size; i++)
    {
        task_completed[i] = 0; /* indicates false */
        time_elapsed[i] = 0;
    }

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
#ifdef DEBUG_PRINT
                printf("Service %d repeat\n", k);
#endif
                if (*(exec_time_elapsed+k) != 0)
                {
                    set_feasible = FALSE;
                }
                else
                {
                    task_completed[k] = 0;
                    *(exec_time_elapsed+k) = *(ex_wcet+k);
                    time_elapsed[k] = 0;
                }
            }

        }

        Assign_Priorities();

        if (task_completed[curr_high_prio_task] == 0)
        {
#ifdef DEBUG_PRINT
            printf("Task %d, Deadline = %d, Time Elapsed = %d\n", 
                    curr_high_prio_task, ex_period[curr_high_prio_task], time_elapsed[curr_high_prio_task]);
#endif
            if ((time_elapsed[curr_high_prio_task] > ex_period[curr_high_prio_task]) || 
                    (ex_wcet[curr_high_prio_task] > (ex_period[curr_high_prio_task] - time_elapsed[curr_high_prio_task])))
            {
                printf("Task %d missed deadline, Deadline = %d, Time Elapsed = %d\n", 
                        curr_high_prio_task, ex_period[curr_high_prio_task], time_elapsed[curr_high_prio_task]);
                set_feasible = FALSE;
            }
            else
            {
#ifdef DEBUG_PRINT
                printf("Executing Task %d\n", curr_high_prio_task);
#endif                
                exec_time_elapsed[curr_high_prio_task] -= 1;
                
                if (exec_time_elapsed[curr_high_prio_task] == 0)
                {
#ifdef DEBUG_PRINT
                    printf("Task %d executed succesfully\n", curr_high_prio_task);
#endif
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

#ifdef DEBUG_PRINT
        printf("Time Elapsed:\n");
        for (k = 0; k < size; k++)
            printf("%d\t", time_elapsed[k]);
        printf("\n");
#endif
        time++;

#ifdef DEBUG_PRINT
        printf("Time Elapsed: %d\n", time);
#endif
    }

    return set_feasible;
}

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

int gcd(int a, int b) 
{
      if (b == 0) return a;
        return gcd(b, a%b);
}

int lcm(unsigned int *a, int n)
{
    int res = 1, i;
    for (i = 0; i < n; i++) 
    {
        res *= (*(a+i)/gcd(res, *(a+i)));
    }
    return res;
}

void Assign_Priorities(void)
{
    U32_T time_diff[size];
    U32_T sorted_time_diff[size];
    U32_T i = 0, j = 0;
    U32_T lowest_priority = size-1;

    for (i = 0; i < size; i++)
    {
        if (task_completed[i] == 1)
            time_diff[i] = 100; /* Some big number to ensure that this service gets lowest priority */
        else
            time_diff[i] = ex_period[i] - time_elapsed[i];    
    }

    for (i = 0; i < size; i++)
        *(sorted_time_diff+i) = *(time_diff+i);

    sort(sorted_time_diff);

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (time_diff[i] == 100)
                task_priority[i] = lowest_priority;
            else
            {
                if (time_diff[i] == sorted_time_diff[j])
                {
                    task_priority[i] = j;
                    if (j == 0)
                    {
                        curr_high_prio_task = i;
                    }
                }
            }
        }
    }

#ifdef DEBUG_PRINT
   printf("High Priority Task is %d\n", curr_high_prio_task);
#endif
}
