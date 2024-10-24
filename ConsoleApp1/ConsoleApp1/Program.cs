using System.Diagnostics;

static double scalar_multiplication(double[] A, double[] B)
{
    double x = 0;
    for (int i = 0; i < A.Length; i++)
    {
        x += A[i] * B[i];
    }
    return x;
}
static double[] get_row(double[,] A, int lengths, int index)
{
    double[] vec = new double[lengths];
    for (int i = 0; i < lengths; i++)
    {
        vec[i] = A[index, i];
    }
    return vec;
}
static double[] get_column(double[,] A, int lengths, int index)
{
    double[] vec = new double[lengths];
    for (int i = 0; i < lengths; i++)
    {
        vec[i] = A[i, index];
    }
    return vec;
}
int[] threads = [2, 4, 8, 16, 20];
int[] lengths = [1000, 2000, 5000];
double[,] A = new double[10000, 10000];
double[,] B = new double[10000, 10000];
Random random = new Random();

for (int i = 0; i < 10000; i++)
{
    for (int j = 0; j < 10000; j++)
    {
        A[i, j] = (random.NextDouble() * (7.2 - 2.5)) + 2.5;
        B[i, j] = (random.NextDouble() * (7.2 - 2.5)) + 2.5;
    }
}

foreach (int thread in threads)
{
    var parallelOptions = new ParallelOptions
    {
        MaxDegreeOfParallelism = thread
    };
    foreach (int n in lengths)

    {
        Stopwatch sw = new Stopwatch();
        sw.Start();
        for (int i = 0; i < n; i++)
        {

            Parallel.For(0, n, parallelOptions, (j, state) =>
            {
                scalar_multiplication(get_row(A, n, i), get_row(B, n, i));
            });


        }
        sw.Stop();
        Console.WriteLine("По строкам Размерность матрицы={0}, Число потоков={1}, Время={2}", n, thread, sw.ElapsedMilliseconds);
        Stopwatch sw_2 = new Stopwatch();
        sw_2.Start();
        for (int i = 0; i < n; i++)
        {
            Parallel.For(0, n, parallelOptions, (j, state) =>
            {
                scalar_multiplication(get_column(A, n, i), get_row(B, n, i));
            });

        }
        sw_2.Stop();
        Console.WriteLine("По столбцам Размерность матрицы={0}, Число потоков={1}, Время={2}", n, thread, sw_2.ElapsedMilliseconds);
    }
}
