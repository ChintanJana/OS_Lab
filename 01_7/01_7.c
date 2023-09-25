/* 
   TEAM NUMBER - 1
   MEMBERS -
   ANANYA BHOWMICK       002111001016
   ARIJIT SAHA           002111001118
   ROHEENA PAL           002111001096
   CHINTAN JANA          002111001115

   ASSIGNMENT DETAILS - 
   ASSIGNMENT NUMBER 7
   Consider a main process which creates three threads Th1, Th2, and Th3. The main process also creates two random quantities (X, Y), both less than 10. These two values will be placed by the main process in the shared memory (One variant of IPC Primitive) that is accessible by all the three threads Th1, Th2 and Th3. The shared memory will be created by the main process also.
   For each pair of values (X,Y), it is required that some computations will be done by various threads. The thread Th1 will compute A (X*Y) and the thread Th2 will compute B (X*Y)/2). Similarly, Th3 computes C (X+Y), Th2 again computes D ((X*Y)/(X+Y)), and finally Th1 computes E ((X+Y)(X-Y)). All these values are kept in the shared memory in a tabular fashion as shown below.
   The number of (X,Y) pairs will be taken as an argument from the CLI. It is the responsibility of the main process to populate required numbers of (X,Y)s in the shared memory. The program will only exit when all A,B,C etc. are computed for all given (X,Y) values. Before exiting, all (X,Y)s, As, Bs etc. should be displayed.
   INPUT - N, number of random pairs
   OUTPUT FORMAT - 
   Pairs(X,Y) | A | B | C | D | E
   ——————————————————————————
   (1, 2) | 2 | 1 | 3 | .66 | -3
   ——————————————————————————
   (4, 1) | 4 | 2 | 5 | .8 | 15
   ………

   COMPILATION COMMAND -
   gcc -o 01_7 01_7.c -lpthread
   ./01_7 10

   OUTPUT - 
   Pairs(X,Y)      |A      |B      |C      |D      |E
   --------------------------------------------------------
   Pairs(2, 8)     |16.00  |8.00   |10.00  |1.00   |-60.00
   Pairs(1, 8)     |8.00   |4.00   |9.00   |0.00   |-63.00
   Pairs(6, 8)     |48.00  |24.00  |14.00  |3.00   |-28.00
   Pairs(2, 4)     |8.00   |4.00   |6.00   |1.00   |-12.00
   Pairs(7, 2)     |14.00  |7.00   |9.00   |1.00   |45.00
   Pairs(6, 5)     |30.00  |15.00  |11.00  |2.00   |11.00
   Pairs(6, 8)     |48.00  |24.00  |14.00  |3.00   |-28.00
   Pairs(6, 5)     |30.00  |15.00  |11.00  |2.00   |11.00
   Pairs(7, 1)     |7.00   |3.50   |8.00   |0.00   |48.00
   Pairs(8, 2)     |16.00  |8.00   |10.00  |1.00   |60.00

   Shared memory Segment shmid=9
   uid=1000        gid=1000        cuid=1000       cgid=1000
   mode=0666       access_perms=0666
   bytes=480       lpid=278        cpid=278        nattch=1
   att_time=Fri Sep 15 23:00:55 2023
   det_time=Not set
   change_time=Fri Sep 15 23:00:55 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define NUM_THREADS 3

// defining the structure for shared memory
struct SharedMemory {
		int x;      // X value
		int y;      // Y value
		double A;   // result of X * Y
		double B;   // result of (X * Y) / 2
		double C;   // result of X + Y
		double D;   // result of (X * Y) / (X + Y)
		double E;   // result of (X + Y)(X - Y)
};

// shared memory data structure
struct SharedMemory *shm;

// decalring the total number of pairs
int numPairs;

// Barrier for synchronization
pthread_barrier_t barrier;

// thread 1 computes A (X * Y) and E ((X + Y)(X - Y))
void *thread1() {
		for(int i = 0; i < numPairs; i++){
				pthread_barrier_wait(&barrier);
				shm[i].A = shm[i].x * shm[i].y;
				shm[i].E = (shm[i].x + shm[i].y) * (shm[i].x - shm[i].y);
		}
}

// thread 2 computes B (X * Y) / 2 and D ((X * Y) / (X + Y))
void *thread2() {
		for(int i = 0; i < numPairs; i++){
				pthread_barrier_wait(&barrier);
				shm[i].B = (shm[i].x * shm[i].y) / 2.0;
				shm[i].D = (shm[i].x * shm[i].y) / (shm[i].x + shm[i].y);
		}
}

// thread 3 computes C (X + Y)
void *thread3() {
		for(int i = 0; i < numPairs; i++){
				pthread_barrier_wait(&barrier);
				shm[i].C = shm[i].x + shm[i].y;
		}
}


int main(int argc, char *argv[]) {
		// checking if the correct number of arguments is provided
		if (argc != 2) {
				printf("Usage: %s <number_of_pairs>\n", argv[0]);
				exit(1);
		}

		numPairs = atoi(argv[1]); // to get the number of pairs from the command line argument

		if (numPairs == 0) {
				fprintf(stderr, "Error: Invalid argument :: numPairs must be positive\n");
				exit(EXIT_FAILURE);
		}

		key_t key = ftok("shmfile", 65); // generating a unique key for the shared memory

		// creating a shared memory segment
		int shmid = shmget(key, numPairs * sizeof(struct SharedMemory), IPC_CREAT | 0666);
		if(shmid == -1){
				perror("shmget");
				exit(1);
		}

		// to attach shared memory
		shm = (struct SharedMemory *)shmat(shmid, NULL, 0);
		if(shm == (struct SharedMemory *)(-1)){
				perror("shmat");
				exit(1);
		}

		pthread_barrier_init(&barrier, NULL, 4); // initializing barrier

		pthread_t threads[NUM_THREADS];

		// creating threads to compute values for X * Y, (X * Y) / 2, and X + Y
		pthread_create(&threads[0], NULL, thread1, NULL);
		pthread_create(&threads[1], NULL, thread2, NULL);
		pthread_create(&threads[2], NULL, thread3, NULL);

		for(int i = 0; i < numPairs; i++){
				// generating random X and Y values
				shm[i].x = rand() % 9 + 1;
				shm[i].y = rand() % 9 + 1;
				pthread_barrier_wait(&barrier);
		}

		// waiting for all threads to complete
		for(int j = 0; j < NUM_THREADS; j++){
				pthread_join(threads[j], NULL);
		}

		pthread_barrier_destroy(&barrier); // destroying the barrier

		// displaying the computed results
		printf("Pairs(X,Y)\t|A\t|B\t|C\t|D\t|E\n");
		printf("--------------------------------------------------------\n");
		for(int i = 0; i < numPairs; i++){
				printf("Pairs(%d, %d) \t|%.2lf\t|%.2lf\t|%.2lf\t|%.2lf\t|%.2lf\n", shm[i].x, shm[i].y, shm[i].A, shm[i].B, shm[i].C, shm[i].D, shm[i].E);
		}

		// creating command for ipcs system call
		char command[100];
		sprintf(command, "ipcs --id %d -m -l", shmid);

		// calling ipcs command to display shared memory stats
		int err = system(command);
		if(err != 0){
				perror("system");
				exit(1);
		}

		// detaching and removing shared memory
		shmdt(shm);
		shmctl(shmid, IPC_RMID, NULL);

		return 0;
}
