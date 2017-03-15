
/* Function that generates a random
   matrix with dimension d
*/
matrix *genrandMatrix(int d) {
	//time_t t;
	//srand(time(NULL));

	matrix *m = (matrix *) malloc(sizeof(matrix));
	m->row = 0;
	m->col = 0;
	m->d = d;

}