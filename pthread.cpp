#include "asg2.h"
#include <stdio.h>
#include <pthread.h>


int n_thd; // number of threads
int size_local; 


typedef struct {
    //TODO: specify your arguments for threads
    int index;
    int total_thds;
    //TODO END
} Args;


void* worker(void* args) {
    //TODO: procedure in each threads
    // the code following is not necessary, you can replace it.
    
    Args* my_arg = (Args*) args;
    int index_thds = my_arg->index;
    int total_thds = my_arg->total_thds; // can just read n_thds

    Point* p_local = data;
    //int nofcl = 0;

    p_local = p_local + index_thds*Y_RESN; //beginning position
    //nofcl = nofcl + index_thds*Y_RESN;

    //chose spcific row by index of thread(eg.3 thread: row 0 1 2 0 1 2)
    for(int i = index_thds; i<X_RESN; i=i+n_thd){
        for(int j=0; j<Y_RESN; j++){
            compute(p_local);
            // printf("P%d: i,j=%d,%d; X=%d, Y=%d, color=%lf\n",
            // index_thds,i,j, p_local->x, p_local->y, p_local->color);
            p_local++;
            //nofcl++;
        }
        p_local = p_local + (n_thd-1)*Y_RESN; // jump to next sepcific row
        // because already move one row by p++, only need to jump n_thds-1 row
    }


    //TODO END

}


int main(int argc, char *argv[]) {

	if ( argc == 5 ) {
		X_RESN = atoi(argv[1]);
		Y_RESN = atoi(argv[2]);
		max_iteration = atoi(argv[3]);
        n_thd = atoi(argv[4]);
	} else {
		X_RESN = 1000;
		Y_RESN = 1000;
		max_iteration = 100;
        n_thd = 4;
	}

    #ifdef GUI
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Pthread");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, X_RESN, 0, Y_RESN);
	glutDisplayFunc(plot);
    #endif

    /* computation part begin */
    t1 = std::chrono::high_resolution_clock::now();

    initData();
    size_local = total_size/n_thd;
    printf("\n====== Pthread START ======\n\n");
    printf("X,Y=%d,%d; Total,Local,Np; %d = %d * %d\n\n", X_RESN,Y_RESN,total_size,size_local,n_thd);

    //TODO: assign jobs
        pthread_t thds[n_thd]; // thread pool
        Args args[n_thd]; // arguments for all threads
        for (int thd = 0; thd < n_thd; thd++){
            args[thd].index = thd; // index of threads
            args[thd].total_thds = n_thd; // total number of threads
        }
        for (int thd = 0; thd < n_thd; thd++) pthread_create(&thds[thd], NULL, worker, &args[thd]);
        for (int thd = 0; thd < n_thd; thd++) pthread_join(thds[thd], NULL);
    //TODO END

    t2 = std::chrono::high_resolution_clock::now();  
    time_span = t2 - t1;
    /* computation part end */

    printf("\nStudent ID: 117010332\n"); // replace it with your student id
    printf("Name: XU Jiale\n"); // replace it with your name
    printf("Assignment 2 Pthread\n");
    printf("Run Time: %f seconds\n", time_span.count());
    printf("Problem Size: %d * %d, %d\n", X_RESN, Y_RESN, max_iteration);
    printf("Thread Number: %d\n\n", n_thd);

    #ifdef GUI
	glutMainLoop();
    #endif

	return 0;
}
