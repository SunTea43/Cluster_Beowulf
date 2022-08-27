#define __USE_MINGW_ANSI_STDIO 1
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include <time.h>
#include<float.h>

#ifdef LDBL_DECIMAL_DIG
  #define OP_DBL_Digs (LDBL_DECIMAL_DI)
#else  
  #ifdef DECIMAL_DIG
    #define OP_DBL_Digs (DECIMAL_DIG)
  #else  
    #define OP_DBL_Digs (LDBL_DIG + 100)
  #endif
#endif

/*CONSTANTS*/
struct timespec inicio, fin;

/*Functions*/
void sampleStart();
void sampleEnd();

int main(){
    long int i, n = 10e6; //10e6 90e6
    long double sum = 0.0, term, pi, p;
	printf("Calculating PI with a serie of %ld ", n);
    
	sampleStart();
    
    /* Applying Leibniz Formula */    
    for(i = 0; i< n; i++) {
    	
        //p = ((i*100)/n);
        //printf("Progress: %.0f %%", p);
        term = pow(-1, i) / (2 * i + 1);
        sum += term;
        //system("cls");
    }
    
	pi = 4 * sum;
	sampleEnd();
	
    printf("\nPI = %.*Lf\n", OP_DBL_Digs, pi);

    return 0;
}


/* -------------------------------------Functions ------------------------------------*/
/**
 * @brief: Get the init time
 */
void sampleStart(){
	clock_gettime(CLOCK_MONOTONIC, &inicio);
}

/**
 * 	@brief: Get the end time
 */
void sampleEnd(){
	clock_gettime(CLOCK_MONOTONIC, &fin);
	double totalTime;
	
	totalTime = (fin.tv_sec - inicio.tv_sec) * 1e9;
	totalTime = (totalTime + (fin.tv_nsec - inicio.tv_nsec)) * 1e-9;
	
	printf("\n%f\n\n", totalTime);
}

