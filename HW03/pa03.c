#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "pa03.h"
#define RANGE 10000

void cleanup(FILE * fpin, FILE * fpout)
{
	fclose (fpin);
	fclose (fpout);
}

double * * allocateMemory(int nrow, int ncol)
{
	double * * data = NULL;
	data = malloc(sizeof(double*) * nrow);
	if (!data) {
		free(data);
		return NULL;
	}
	for (int i = 0; i < nrow; i++) {
		data[i] = malloc(sizeof(double) * ncol);
		if (!data[i]) {
			for (int j = 0; j <= i; j++) {
				free(data[i]);
			}
			free(data);
			return NULL;
		}
	}
	return data;
}

void releaseMemory(double * * data, int nrow)
{
	if (data) {
		for (int i = 0; i < nrow; i++) {
			if (data[i]) {
				free(data[i]);
			}
		}
		free(data);
	}
}

bool readData(FILE * fpin, double * * data, int nval, int dim)
{
	int niter, diter;
	for (niter = 0; niter < nval; niter ++)
	{
		for (diter = 0; diter < dim; diter ++)
		{
			if (fscanf(fpin, "%lf", & data[niter][diter]) == 0)
			{
				return false;
			}
		}
	}
	return true;
}

// write the output centroids to the file
// check for all the NULL before calling this function, it does not check
void writeCentroids(FILE * fpout, double * * centroid, int kval, int dim){
	int kiter,diter;
	for (kiter = 0; kiter < kval; kiter ++)
	{
		for (diter = 0; diter < dim; diter ++)
		{
			//write to the file
			fprintf(fpout, "%lf ", centroid[kiter][diter]);
		}
		fprintf(fpout, "\n");
	}
}

//initilize function is to initilize the values for centroid
void initialize(double * * centroid, int kval, int dim)
{
	int kiter, diter;
	for (kiter = 0; kiter < kval; kiter ++)
	{
		for (diter = 0; diter < dim; diter ++)
		{
			int randval = - RANGE + (rand() % (2 * RANGE));
			centroid[kiter][diter] = randval;
		}
	}
}

int main(int argc, char * * argv)
{
	// argv[1]: name of input file
	// argv[2]: value of k
	// argv[3]: name of output file
	// argv[4]: (optional) seed for random numbers, use time if absent

	if (argc < 4)
	{
		fprintf(stderr, "argc is %d, not 4\n", argc);
		return EXIT_FAILURE;
	}
	FILE * fpin = fopen(argv[1], "r");
	if (fpin == NULL)
	{
		fprintf(stderr, "fopen %s fail\n", argv[1]);
		return EXIT_FAILURE;
	}
	int kval = (int) strtol(argv[2], NULL, 10);
	// convert long to in
	if (kval <= 0)
	{
		fprintf(stderr, "kval is %d, must be positive\n", kval);
		return EXIT_FAILURE;
	}
	FILE * fpout = fopen(argv[3], "w");
	if (fpout == NULL)
	{
		fclose (fpin);
		// was open successfully and needs to be closed
		fprintf(stderr, "fopen %s fail\n", argv[3]);
		return EXIT_FAILURE;
	}

	if (argc == 5)
	{
		int randseed = (int) strtol(argv[4], NULL, 10);
		if (randseed == -1)
		{
			srand(time(NULL));
		}
		else
		{
			srand(randseed);
		}
	}

	int nval;
	fscanf(fpin, "%d", & nval);
	if (nval < kval)
	{
		fprintf(stderr, "nval= %d must be greater than kval = %d\n",
				nval, kval);
		cleanup(fpin, fpout);
		return EXIT_FAILURE;
	}
	int dim;
	fscanf(fpin, "%d", & dim);
	if (dim < 2)
	{
		fprintf(stderr, "nval= %d must be greater than kval = %d\n",
				nval, kval);
		cleanup(fpin, fpout);
		return EXIT_FAILURE;

	}

	// allocate memory for the data points
	double * * datapoint = allocateMemory(nval, dim);
	if (datapoint == NULL)
	{
		cleanup(fpin, fpout);
		return EXIT_FAILURE;
	}
	// allocate memory for the centroid
	double * * centroid = allocateMemory(kval, dim);
	if (centroid == NULL)
	{
		cleanup(fpin, fpout);
		return EXIT_FAILURE;
	}

	// read the data from the file
	if (readData(fpin, datapoint, nval, dim) == false)
	{
		cleanup(fpin, fpout);
		return EXIT_FAILURE;
	}

	// initialize centroids within [-RANGE, RANGE] of every dimension
	initialize(centroid, kval, dim);

	//allocate memory for cluster
	int * cluster;
	cluster = malloc(sizeof(*cluster)*nval);
	if(cluster == NULL)
	{
		cleanup(fpin, fpout);
		return EXIT_FAILURE;
	}
	// initilize cluster values
	for(int niter = 0; niter < nval; niter++)
	{
		cluster[niter] = -1;
	}

	//now we will run our kmean algorithm
	kmean(kval, nval, dim, datapoint, centroid, cluster);


	//print all the centroids into a file
	writeCentroids(fpout, centroid, kval, dim);

	//free all the allocated spaces
	releaseMemory(datapoint, nval);
	releaseMemory(centroid, kval);
	free(cluster);
	//close all the files
	cleanup(fpin, fpout);
	return EXIT_SUCCESS;
}

void kmean(int kval, int nval, int dim, double * * data, double * * centroid,
		int * cluster)
{
	double diff = 1;
#ifdef DEBUG
	for (int i = 0; i < kval; i++) {
		memcpy(centroid[i], data[i], sizeof(double) * dim);
	} 
#endif
	double *newC = malloc(sizeof(double) * dim);
	for(int i = 0; i < dim; i++) {
		newC[i] = 0;
	}

	while (diff > 0) {
		diff = 0;
		for (int i = 0; i < nval; i++) {
			cluster[i] = closestCentroid(kval, dim, data[i], centroid);
		}
		for (int i = 0; i < kval; i++) {
			int counter = 0;
			for (int j = 0; j < dim; j++) {
				newC[j] = 0;
			}
			//==================start the loop=====================
			for (int j = 0; j < nval; j++) {
				if (cluster[j] == i) {
					counter++;
					for (int k = 0; k < dim; k++) {
						newC[k] += data[j][k];
					}
				}
			}
			for (int j = 0; j < dim; j++) {
				if (counter == 0) {
					counter = 1;
				}
				newC[j] /= counter;
			}
			diff += distance2(newC, centroid[i], dim);
			memcpy(centroid[i], newC, sizeof(double) * dim);
		}
	}
	free(newC);
}
