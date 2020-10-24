/*
* This code is based on the work from:
*   Cesar Augusto Garcia Perez
*   COW ASCII taken from: http://www.chris.com/ascii/index.php?art=animals/cows
*
* Edits and modifications have been done by me: Alejandro MDC
* the original code can be reviewed in the mutex_milk.c file
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

/*
*   Defines shell coloring
*/
#define RED      "\x1b[31m"
#define GREEN    "\x1b[32m"
#define PURPLE   "\x1b[35m"
#define BWHITE   "\x1b[1;97m"
#define RESET    "\x1b[0m"

pthread_mutex_t mutex;                          /* mutex instance               */
int stock = 1000;                                 /* amount of elements in stock  */
int cashier = 5;                                /* number of cashiers to use    */

int lower = 1, upper = 200;

void sellmilk(intptr_t *t_id){
    intptr_t t_id2 = (intptr_t) t_id;
   //sell a random number of milk from 1-200 bottles
   // every seller can have up to 5 customers
    srand(time(0));
    int customers, milkSale;
    customers = lrand48() % 6;   //creates 0 to 5 customers
    //we need to use lrand48 instead of the usual srand as srand if not THREAD SAFE and will give the same value of customers to the threads!
    //however it does not solve all isues, every program run seems to have the same random distrubution of customers 
    printf("This seller has found %d customers!", customers);

    int customerCount=0;
    while(customerCount != customers && stock != -1)
    {
   	 milkSale = (rand() % (upper - lower + 1))+lower;
  	 printf("\n This sale's  planned units: %d", milkSale);
    //rand sale done
    //now verify if it is doable
  	  if(milkSale <= stock){
		    //sale is doable
	   	 stock-= milkSale;
	  	 printf("\n The planned amount was sold!");
	    }
	  else{
		  if(milkSale > stock){
			  printf(  "\nThe planned amount can not be sold, instead, current  customer will get all remaining units\n");
			 stock = -1;
		//this flag lets us know no more milk will be available for sale to other threads and/or customers!
		  }
	  }
	  customerCount++;
    }
    if(stock == -1){
	    printf("\nAll milk has been sold for today!\n");
    }
    printf(PURPLE "Thread %zd Finished!\n" RESET, t_id2);
}

/*
*   Calls sellmilk(), and activate/desactivate mutex whenever there is someone selling
*/
void *threadfunc(void *i){
    intptr_t t_id = (intptr_t) i;
    printf(">>Inside thread %zd\n", t_id);
    
    printf(">>" BWHITE "%zd " RESET "Trying to access!\n", t_id);
    pthread_mutex_lock(&mutex);
    printf(RED "BLOCK BY %zd\n" RESET, t_id);
    if(stock > 0){
        sellmilk((intptr_t *)t_id);
        printf(GREEN "UNBLOCK BY %zd\n" RESET, t_id);
        printf("\t\t\t STOCK-> %d\n", stock);
        pthread_mutex_unlock(&mutex);
       
    }else{
        pthread_mutex_unlock(&mutex);
        printf(GREEN "UNBLOCK BY %zd\n" RESET, t_id);
        pthread_exit(NULL);
    }
}

int main(void){
    pthread_mutex_init(&mutex, NULL);                               /* Initialize mutex with no attr, see more in man pthread_mutex_destoy */
    printf(">>Mutex created at &->%p\n", (void *) &mutex);
    printf("\t\t\t STOCK-> %d\n", stock);
    pthread_t thread[cashier];                                      /* Creates array of cashiers                                            */

    int i;
    
    /*
    *   Create the threads up to cashier
    */
    for(i = 0; i < cashier; i++){
        pthread_create(&thread[i], NULL, threadfunc, (void *) (intptr_t) (i+1));
    }
    
    /*
    *   Main() waits for threads to be completed
    */
    for(i = 0; i < cashier; i++){
        pthread_join(thread[i], NULL);
    }

    printf("\n Thanks for buying LonLon Ranch Milk!\n");

    printf("\n"
"            /~~~~~\\        /~~~~~\\ \n"
"           |    (~'        ~~~)   | \n"
"            \\    \\__________/    / \n"
"            /~::::::::         ~\\ \n"
" /~~~~~~~-_| ::::::::             |_-~~~~~~~\\ \n"
"\\ ======= /|  ::A::;      A     :|\\ ====== / \n"
" ~-_____-~ |  _----------------_::| ~-____-~ \n"
"           |/~                  ~\\| \n"
"           /                      \\ \n" 
"          (        ()    ()        ) \n"
"           `\\                   ./' \n"
"             ~-_______________-~     \n"
"                   /~~~~\\           \n"
"                  |      |           \n"
"                  |      |           \n"
"                 (________)          \n"
"                  by jurci              \n");
}
