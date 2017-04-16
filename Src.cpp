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

#define M 20 // M 个有限和 || 优化变量个数
#define N 3 // 调用的processes 的数目
#define mu 100 // 参数
#define s 20 // 最大delay
#define Max_iter 100 // 最大迭代次数
#define eta 0.01 // Prox步长

double par_f(double); // return f 偏导
double prox_l1(double); //计算 l1-norm prox值

int main()
{
	int argc;
	char **argv;

	int process_num, process_rank; //进程数目，rank
	int k = 0; // 迭代次数
	double U[M] = { 0 }; //接收的更新值

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

	/*	划分数据
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
			// 向 Workers 广播 x 的值
			MPI_Bcast(x, M, MPI_DOUBLE, 0, MPI_COMM_WORLD);

			// Recv from workers
			for(int )
		}
	}

}

// 计算 f 关于 x 的偏导
double par_f(double x)
{
	return mu * (x - 1) / (1 + mu * (x - 1) * (x - 1));
}

// f = ||.||_1, 求 f 的 prox 值 eta: 参数值
double prox_l1(double x)
{
	return fmax(0, x - eta) - fmax(0, -x - eta);
}