/*
	A test to Sync CD algorithm
	JingChang Liu
	2017 04 15
*/

#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<mpi.h>
#include<time.h>
#include<stdlib.h>

#define M 20 // M �����޺� || �Ż���������
#define N 3 // ���õ�processes ����Ŀ
#define mu 100 // ����
#define s 20 // ���delay
#define Max_iter 100 // ����������
#define eta 0.01 // Prox����

double par_f(double); // return f ƫ��
double prox_l1(double); //���� l1-norm proxֵ

int main()
{
	int argc;
	char **argv;

	int process_num, process_rank; //������Ŀ��rank
	int k = 0; // ��������
	double U[M] = { 0 }; //���յĸ���ֵ

	// Generate x
	double x[M];
	srand(unsigned(time(0)));
	for (int i = 0; i < M; i++)
	{
		x[i] = (double)rand() / RAND_MAX + 10;
		printf("%f ", x[i]);
	}
	printf("\n\n\n");

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

	/*	��������
	worker 1: 0 ~ n-1
	worker 2: n ~ 2n-1

	worker N-1: (N-2)n ~ (N-1)n-1
	worker N: (N-1)n ~ M
	*/
	int n, start, stop;
	n = M / (N - 1);

	start = (process_rank - 1) * n;

	if (process_rank != (N - 1))
		stop = start + n - 1;
	else
		stop = M;

	while (k < Max_iter)
	{
		MPI_Request recv_req;

		// Master
		if (process_rank == 0)
		{
			// �� Workers �㲥 x ��ֵ
			MPI_Bcast(x, M, MPI_DOUBLE, 0, MPI_COMM_WORLD);

			// Recv from workers
			for(int )
		}
	}

}

// ���� f ���� x ��ƫ��
double par_f(double x)
{
	return mu * (x - 1) / (1 + mu * (x - 1) * (x - 1));
}

// f = ||.||_1, �� f �� prox ֵ eta: ����ֵ
double prox_l1(double x)
{
	return fmax(0, x - eta) - fmax(0, -x - eta);
}