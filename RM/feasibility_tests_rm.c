#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define U32_T unsigned int

// U - CPU utilization factor
// U=0.7333 
U32_T ex0_period[] = {2, 10, 15};
U32_T ex0_wcet[] = {1, 1, 2};

// U=0.9857
U32_T ex1_period[] = {2, 5, 7};
U32_T ex1_wcet[] = {1, 1, 2};

// U=0.9967
U32_T ex2_period[] = {2, 5, 7, 13};
U32_T ex2_wcet[] = {1, 1, 1, 2};

// U=0.93
U32_T ex3_period[] = {3, 5, 15};
U32_T ex3_wcet[] = {1, 2, 3};

// U=1.0
U32_T ex4_period[] = {2, 4, 16};
U32_T ex4_wcet[] = {1, 1, 4};

//U=1.0 
U32_T ex5_period[] = {2, 5, 10};
U32_T ex5_wcet[] = {1, 2, 1};

//U=0.9967 
U32_T ex6_period[] = {2, 5, 7, 13};
U32_T ex6_wcet[] = {1, 1, 1, 2};

// U=1.0
U32_T ex7_period[] = {3, 5, 15};
U32_T ex7_wcet[] = {1, 2, 4};

//U=0.9967 
U32_T ex8_period[] = {2, 5, 7, 13};
U32_T ex8_wcet[] = {1, 2, 1, 2};

int completion_time_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);
int scheduling_point_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);
int rm_least_upper_bound_sched_test(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);

int main(void)
{ 
    int i;
    U32_T numServices;

    printf("******** Rate Monotonic Schedulibilty Test ********\n");
    printf("Rate Monotonic Upper Bound is a sufficient and not necessary test, \n"); 
    printf("so if a process set fails the test, it may still meet its deadlines \n\n");        
    printf("Ex-0 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=10, T3=15; T=D)\n",
            ((1.0/2.0) + (1.0/10.0) + (2.0/15.0)));
    
    numServices = sizeof(ex0_period)/sizeof(U32_T);
    
    if(rm_least_upper_bound_sched_test(numServices, ex0_period, ex0_wcet, ex0_period) == TRUE)
        printf("FEASIBLE\n");
    else
    {
        printf("RM LUB Test is infeasible. Going for N&S RM Test\n");
        if ((completion_time_feasibility(numServices, ex0_period, ex0_wcet, ex0_period) == TRUE) || 
                scheduling_point_feasibility(numServices, ex0_period, ex0_wcet, ex0_period) == TRUE)
            printf("FEASIBLE\n");
        else
            printf("INFEASIBLE\n");
    }

    printf("Ex-1 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=5, T3=7; T=D)\n", 
            ((1.0/2.0) + (1.0/5.0) + (2.0/7.0)));
    
    numServices = sizeof(ex1_period)/sizeof(U32_T);
    
    if(rm_least_upper_bound_sched_test(numServices, ex1_period, ex1_wcet, ex1_period) == TRUE)
        printf("FEASIBLE\n");
    else
    {
        printf("RM LUB Test is infeasible. Going for N&S RM Test\n");
        if ((completion_time_feasibility(numServices, ex1_period, ex1_wcet, ex1_period) == TRUE) || 
                scheduling_point_feasibility(numServices, ex1_period, ex1_wcet, ex1_period) == TRUE)
            printf("FEASIBLE\n");
        else
            printf("INFEASIBLE\n");
    }

    printf("Ex-2 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D)\n",
            ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
    
    numServices = sizeof(ex2_period)/sizeof(U32_T);
    
    if(rm_least_upper_bound_sched_test(numServices, ex2_period, ex2_wcet, ex2_period) == TRUE)
        printf("FEASIBLE\n");
    else
    {
        printf("RM LUB Test is infeasible. Going for N&S RM Test\n");
        if ((completion_time_feasibility(numServices, ex2_period, ex2_wcet, ex2_period) == TRUE) || 
                scheduling_point_feasibility(numServices, ex2_period, ex2_wcet, ex2_period) == TRUE)
            printf("FEASIBLE\n");
        else
            printf("INFEASIBLE\n");
    }

    printf("Ex-3 U=%4.2f (C1=1, C2=2, C3=3; T1=3, T2=5, T3=15; T=D)\n",
            ((1.0/3.0) + (2.0/5.0) + (3.0/15.0)));
    
    numServices = sizeof(ex3_period)/sizeof(U32_T);
    
    if(rm_least_upper_bound_sched_test(numServices, ex3_period, ex3_wcet, ex3_period) == TRUE)
        printf("FEASIBLE\n");
    else
    {
        printf("RM LUB Test is infeasible. Going for N&S RM Test\n");
        if ((completion_time_feasibility(numServices, ex3_period, ex3_wcet, ex3_period) == TRUE) || 
                scheduling_point_feasibility(numServices, ex3_period, ex3_wcet, ex3_period) == TRUE)
            printf("FEASIBLE\n");
        else
            printf("INFEASIBLE\n");
    }

    printf("Ex-4 U=%4.2f (C1=1, C2=1, C3=4; T1=2, T2=4, T3=16; T=D)\n",
            ((1.0/2.0) + (1.0/4.0) + (4.0/16.0)));
    
    numServices = sizeof(ex4_period)/sizeof(U32_T);
    
    if(rm_least_upper_bound_sched_test(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE)
        printf("FEASIBLE\n");
    else
    {
        printf("RM LUB Test is infeasible. Going for N&S RM Test\n");
        if ((completion_time_feasibility(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE) || 
                scheduling_point_feasibility(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE)
            printf("FEASIBLE\n");
        else
            printf("INFEASIBLE\n");
    }

    printf("Ex-5 U=%4.2f (C1=1, C2=2, C3=1; T1=2, T2=5, T3=10; T=D)\n",
            ((1.0/2.0) + (2.0/5.0) + (1.0/10.0)));
    
    numServices = sizeof(ex4_period)/sizeof(U32_T);
    
    if(rm_least_upper_bound_sched_test(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE)
        printf("FEASIBLE\n");
    else
    {
        printf("RM LUB Test is infeasible. Going for N&S RM Test\n");
        if ((completion_time_feasibility(numServices, ex5_period, ex5_wcet, ex5_period) == TRUE) || 
                scheduling_point_feasibility(numServices, ex5_period, ex5_wcet, ex5_period) == TRUE)
            printf("FEASIBLE\n");
        else
            printf("INFEASIBLE\n");
    }

    printf("Ex-6 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D)\n",
            ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
    
    numServices = sizeof(ex6_period)/sizeof(U32_T);
    
    if(rm_least_upper_bound_sched_test(numServices, ex6_period, ex6_wcet, ex6_period) == TRUE)
        printf("FEASIBLE\n");
    else
    {
        printf("RM LUB Test is infeasible. Going for N&S RM Test\n");
        if ((completion_time_feasibility(numServices, ex6_period, ex6_wcet, ex6_period) == TRUE) || 
                scheduling_point_feasibility(numServices, ex6_period, ex6_wcet, ex6_period) == TRUE)
            printf("FEASIBLE\n");
        else
            printf("INFEASIBLE\n");
    }
    
    printf("Ex-7 U=%4.2f (C1=1, C2=2, C3=4; T1=3, T2=5, T3=15; T=D)\n",
            ((1.0/3.0) + (2.0/5.0) + (4.0/15.0)));
    
    numServices = sizeof(ex7_period)/sizeof(U32_T);
    
    if(rm_least_upper_bound_sched_test(numServices, ex7_period, ex7_wcet, ex7_period) == TRUE)
        printf("FEASIBLE\n");
    else
    {
        printf("RM LUB Test is infeasible. Going for N&S RM Test\n");
        if ((completion_time_feasibility(numServices, ex7_period, ex7_wcet, ex7_period) == TRUE) || 
                scheduling_point_feasibility(numServices, ex7_period, ex7_wcet, ex7_period) == TRUE)
            printf("FEASIBLE\n");
        else
            printf("INFEASIBLE\n");
    }
    
    printf("Ex-8 U=%4.2f (C1=1, C2=2, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D)\n",
            ((1.0/2.0) + (2.0/5.0) + (1.0/7.0) + (2.0/13.0)));
    
    numServices = sizeof(ex8_period)/sizeof(U32_T);
    
    if(rm_least_upper_bound_sched_test(numServices, ex8_period, ex8_wcet, ex8_period) == TRUE)
        printf("FEASIBLE\n");
    else
    {
        printf("RM LUB Test is infeasible. Going for N&S RM Test\n");
        if ((completion_time_feasibility(numServices, ex8_period, ex8_wcet, ex8_period) == TRUE) || 
                scheduling_point_feasibility(numServices, ex8_period, ex8_wcet, ex8_period) == TRUE)
            printf("FEASIBLE\n");
        else
            printf("INFEASIBLE\n");
    }
    
    printf("******** Rate Monotonic Schedulibilty Test ********\n");

#if 0
    printf("******** Completion Test Feasibility Example ********\n");

    printf("Ex-0 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=10, T3=15; T=D)\n: ",
            ((1.0/2.0) + (1.0/10.0) + (2.0/15.0)));
    
    numServices = sizeof(ex0_period)/sizeof(U32_T);
    
    if(completion_time_feasibility(numServices, ex0_period, ex0_wcet, ex0_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-1 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=5, T3=7; T=D)\n: ", 
            ((1.0/2.0) + (1.0/5.0) + (1.0/7.0)));
    
    numServices = sizeof(ex1_period)/sizeof(U32_T);
    
    if(completion_time_feasibility(numServices, ex1_period, ex1_wcet, ex1_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-2 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D)\n: ",
            ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
    
    numServices = sizeof(ex2_period)/sizeof(U32_T);
    
    if(completion_time_feasibility(numServices, ex2_period, ex2_wcet, ex2_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    
    printf("Ex-3 U=%4.2f (C1=1, C2=2, C3=3; T1=3, T2=5, T3=15; T=D)\n: ",
            ((1.0/3.0) + (2.0/5.0) + (3.0/15.0)));
    
    numServices = sizeof(ex3_period)/sizeof(U32_T);
    
    if(completion_time_feasibility(numServices, ex3_period, ex3_wcet, ex3_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-4 U=%4.2f (C1=1, C2=1, C3=4; T1=2, T2=4, T3=16; T=D)\n: ",
            ((1.0/2.0) + (1.0/4.0) + (4.0/16.0)));
    
    numServices = sizeof(ex4_period)/sizeof(U32_T);
    
    if(completion_time_feasibility(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("******** Completion Test Feasibility Example ********\n");
    
    printf("\n\n");
    printf("******** Scheduling Point Feasibility Example ********\n");

    printf("Ex-0 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=10, T3=15; T=D)\n: ",
            ((1.0/2.0) + (1.0/10.0) + (2.0/15.0)));
    
    numServices = sizeof(ex0_period)/sizeof(U32_T);
    
    if(scheduling_point_feasibility(numServices, ex0_period, ex0_wcet, ex0_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-1 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=5, T3=7; T=D)\n: ", 
            ((1.0/2.0) + (1.0/5.0) + (1.0/7.0)));
    
    numServices = sizeof(ex1_period)/sizeof(U32_T);
    
    if(scheduling_point_feasibility(numServices, ex1_period, ex1_wcet, ex1_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-2 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D)\n: ",
            ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
    
    numServices = sizeof(ex2_period)/sizeof(U32_T);
    
    if(scheduling_point_feasibility(numServices, ex2_period, ex2_wcet, ex2_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-3 U=%4.2f (C1=1, C2=2, C3=3; T1=3, T2=5, T3=15; T=D)\n: ",
            ((1.0/3.0) + (2.0/5.0) + (3.0/15.0)));
    
    numServices = sizeof(ex3_period)/sizeof(U32_T);
    
    if(scheduling_point_feasibility(numServices, ex3_period, ex3_wcet, ex3_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-4 U=%4.2f (C1=1, C2=1, C3=4; T1=2, T2=4, T3=16; T=D)\n: ",
            ((1.0/2.0) + (1.0/4.0) + (4.0/16.0)));
    
    numServices = sizeof(ex4_period)/sizeof(U32_T);
    
    if(scheduling_point_feasibility(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("******** Scheduling Point Feasibility Example ********\n");
#endif

}

int completion_time_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[])
{
    int i, j;
    U32_T an, anext;

    /* We are given numServices tasks ordered in decreasing order of priorities */

    int set_feasible=TRUE; /* assume service set is feasible until proven otherwise */

    for (i=0; i < numServices; i++)
    {
        an=0; anext=0;

        /* The workload posed to task j by i higher priority tasks over a period [0,t] is 
        ** wi(t) = sum(j=1,i) (wcet[j] * ceil(t/period[j])) */
        /* A task is schedulable if wi <= di (the deadline) where wi(t) = t (process completes
        ** its execution at exactly time t). */

        for (j=0; j <= i; j++)
        {
            an+=wcet[j]; // an will be the time until which the total cumulative demand on n tasks is computed
        }
        /* an is equivalent to t0 where t0 is the sum of execution times, t1 = w1(t0) and so on */

        //printf("i=%d, an=%d\n", i, an);

        while(1)
        {
            anext=wcet[i];

            /* ceil(((double)an)/((double)period[j]))*wcet[j] will be wi(t) term */
            for (j=0; j < i; j++)
                anext += ceil(((double)an)/((double)period[j]))*wcet[j];

            /* Wait until wi(t) becomes equal to t */
            if (anext == an)
                break;
            else
                an=anext;

            //printf("an=%d, anext=%d\n", an, anext);
        }
        
        if (an > deadline[i])
        {
            set_feasible=FALSE;
        }
    }

    return set_feasible;
}

int scheduling_point_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[])
{
    int rc = TRUE, i, j, k, l, status, temp;

    for (i=0; i < numServices; i++) // iterate from highest to lowest priority
    {
        status=0;

        for (k=0; k<=i; k++) 
        {
            /* Identifying the kth service whose l periods must be analysed */
            for (l = 1; l <= (floor((double)period[i]/(double)period[k])); l++)
            {
                temp = 0;
                /* l - the number of periods of kth service that must be analysed */
                for (j = 0; j <= i; j++) 
                {
                    /* time required by jth service to execute within l periods of kth service */
                    temp += wcet[j] * ceil((double)l*(double)period[k]/(double)period[j]);
                }

                if (temp <= (l*period[k]))
                {
                    /* temp, which is sum of time required by jth service, if smaller than l
                    ** periods of sevice k, then service set is feasible */
                    status=1;
                    break;
                }
            }

            if (status) break;
        }

        if (!status) rc=FALSE;
    }

    return rc;
}

int rm_least_upper_bound_sched_test(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[])
{

    int i, j;
    float cpu_util_factor = 0.0;
    float rm_upper_bound = 0.0;
    float temp = 0.0;

    int set_feasible = TRUE; /* assume feasible until we find otherwise */

    temp = pow((double)2, (double)1/numServices);    
    
    rm_upper_bound = numServices * (temp - 1);

    for (i=0; i < numServices; i++)
    {
        cpu_util_factor += (float)wcet[i]/(float)period[i]; 
    }

    //printf("CPU Util Factor = %3.2f, Upper Bound: %3.2f\n", cpu_util_factor, rm_upper_bound);
    
    if (cpu_util_factor > rm_upper_bound)
    {
        set_feasible = FALSE;
    }

    return set_feasible;
}
