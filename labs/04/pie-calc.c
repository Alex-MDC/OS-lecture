  #include <stdlib.h>
  #include <stdio.h>
  #include <math.h>
  #include <string.h>
 #include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <time.h>
  
//use 10k as pointsmax
  #define POINTSMAX 10000
  #define STDIN 0
  #define STDOUT 1
//case working
//rand working making different every iteration
//

 double pointar[POINTSMAX][2];

 typedef struct s_rangeP {
	 int min;
	 int max;
	 int result;   //will store # of points in circle
 } rangeP;

 //range[0] holds rangeMin, range[1] holds rangeMax
 void *calcpoints(void *rangePoints){

	double xp,yp,distance;
	rangeP *range=(rangeP *)rangePoints;
	int circlep=0;
	int j = range->min;
	 for(j=j-1; j < range->max; j++)
	 {
		 xp=pointar[j][0];
		 yp=pointar[j][1];
		 distance = (xp*xp) + (yp*yp);
		 if(distance <=1){
			 circlep++;
		 }
	 }
	 range->result =circlep;
	 pthread_exit(NULL);
 }

 int main(void) {

	 //2 in second value so we can store x and y coordinates
	// double pointar[POINTSMAX][2];
	 char args[20];
	 int option;
	 printf("Choose how many threads (type): one, two, four, eight, sixt\n");
	 read(STDIN, args,20);
	 if(strcmp(args,"one\n") == 0)
		 option =1;
	 if(strcmp(args,"two\n") ==0)
		 option =2;
	 if(strcmp(args,"four\n") ==0)
		 option =4;
	 if(strcmp(args,"eight\n") ==0)
		 option = 8;
	 if(strcmp(args,"sixt\n") ==0)
		 option = 16;

	 int circle_count =0;
	 int square_count =0;
	 //generate random numbers between 0 and 1
	 double xcord, ycord,rcord;
	 int points = POINTSMAX;
	 double distance, pi;

	 srand(time(0));
	// xcord = ((double) rand() / (RAND_MAX));
	// printf("random x %f created \n ", xcord);
	
	int j;
	int k;
	for( j=0; j<points;j++)
	{
		for( k=0;k<2; k++)
		{
			rcord = ((double) rand()/(RAND_MAX));
			pointar[j][k]= rcord;
		}

	}
	//done building coords
	

	//range struct 
	rangeP range;
	rangeP rangef[16];
	pthread_t threads[16];
	int circlepoints;
	circlepoints=0;
	clock_t t;
	double time_taken;
	int maxR, minR;
	 switch(option)
	{
	case(1):
	       	printf("1 thread  chosen \n");
		//do with one thread
		t = clock();
		pthread_t tid;
		range.max = points;
		range.min = 1;
		int rc;
		
		rc = pthread_create(&tid, NULL,calcpoints,(void *)&range);
		pthread_join(tid, NULL);
		//calc pi
		t = clock()-t;
		time_taken = ((double)t)/CLOCKS_PER_SEC; //seconds
		circlepoints = range.result;
		//get result from modified struct
		pi =(4*circlepoints) /((double) points);
		printf("The value of pi is %f \n",pi);
		printf("Time taken in seconds was: %f \n", time_taken);

	 break;

	case(2):
	 	printf("two threads chosen \n");
		t = clock();
		pthread_t tidOne;
		pthread_t tidTwo;
		rangeP rangeTwo;
		//range1
		range.max= points/2;
		range.min=1;
		//range2
		rangeTwo.max=points;
		rangeTwo.min=points/2 +1;
		//start threads
		pthread_create(&tidOne,NULL,calcpoints,(void *)&range);
		pthread_join(tidOne,NULL);
		circlepoints = range.result;
		pthread_create(&tidTwo,NULL,calcpoints,(void *)&rangeTwo);
		pthread_join(tidTwo,NULL);
		t = clock() -t;
		circlepoints += rangeTwo.result;
		pi=  (4*circlepoints)/((double)points);
		printf("The value of pi is %f\n",pi);
		time_taken = ((double)t)/CLOCKS_PER_SEC;
		printf("time taken %f \n", time_taken);

		break;

	case(4):
		printf("four threads chosen\n");
	
		//a rang per each of the threads
		//2500 pointsp/thread
		maxR=0;
		// fill "from the bottom up" the ranges per thread
		for(j=0;j<4;j++){
			minR = maxR +1;
			rangef[j].min= minR;
			maxR += 2500;
			rangef[j].max= maxR;
		}
		t= clock();
		for(j=0;j<4;j++){
			pthread_create(&threads[j],NULL,calcpoints,(void *)&rangef[j]);
			pthread_join(threads[j], NULL);
			circlepoints+=rangef[j].result;
		}
	       	t = clock() -t;
		pi=  (4*circlepoints)/((double)points);
                printf("The value of pi is %f\n",pi);
                time_taken = ((double)t)/CLOCKS_PER_SEC;
                printf("time taken %f \n", time_taken);

		break;

	case(8):
		printf("eight  threads chosen\n");
                //1250 pointsp/thread
                maxR=0;
                // fill "from the bottom up" the ranges per thread
                for(j=0;j<8;j++){
                        minR = maxR +1;
                        rangef[j].min= minR;
                        maxR += 1250;
                        rangef[j].max= maxR;
                }
                t= clock();
		for(j=0;j<8;j++){
                        pthread_create(&threads[j],NULL,calcpoints,(void *)&rangef[j]);
                        pthread_join(threads[j], NULL);
                        circlepoints+=rangef[j].result;
                }
                t = clock() -t;
                pi=  (4*circlepoints)/((double)points);
                printf("The value of pi is %f\n",pi);
                time_taken = ((double)t)/CLOCKS_PER_SEC;
                printf("time taken %f \n", time_taken);

		break;

	case(16):
		 printf("sixteen threads chosen\n");
       //         rangeP rangef[16];
                //a range per each of the threads
      //          pthread_t threads[16];
                //625  pointsp/thread
                maxR=0;
                // fill "from the bottom up" the ranges per thread
                for(j=0;j<16;j++){
                        minR = maxR +1;
                        rangef[j].min= minR;
                        maxR += 625;
                        rangef[j].max= maxR;
                }
                t= clock();
                for(j=0;j<16;j++){
                        pthread_create(&threads[j],NULL,calcpoints,(void *)&rangef[j]);
                        pthread_join(threads[j], NULL);
                        circlepoints+=rangef[j].result;
                }
                t = clock() -t;
                pi=  (4*circlepoints)/((double)points);
                printf("The value of pi is %f\n",pi);
                time_taken = ((double)t)/CLOCKS_PER_SEC;
                printf("time taken %f \n", time_taken);

		break;
	default:
		printf("Invalid option\n");

	}

	 pthread_exit(NULL);
	 return 0;
 }
