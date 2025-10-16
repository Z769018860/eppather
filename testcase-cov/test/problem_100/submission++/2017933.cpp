#include <cstdio>
#include <vector>

const int mod = 1e9 + 7;

struct Matrix
{
	std::vector < std::vector < int > > vec;
	
	Matrix(int n, int m)
	{
		vec.resize(n);
		for (auto &i : vec)
			i.resize(m);
	}
	Matrix(std::vector < std::vector < int > > a) {
		vec = a;
	}
	
	Matrix operator * (const Matrix& a) const
	{
		Matrix b(vec.size(), a.vec[0].size());
		int i, j, k, temp;
		for (i = 0; i < vec.size(); i++)
			for (k = 0; k < vec[0].size(); k++)
			{
				for (j = 0, temp = vec[i][k]; j + 7 < a.vec[0].size(); j += 8)
				{
					b.vec[i][j] += 1ll * temp * a.vec[k][j] % mod;
					b.vec[i][j + 1] += 1ll * temp * a.vec[k][j + 1] % mod;
					b.vec[i][j + 2] += 1ll * temp * a.vec[k][j + 2] % mod;
					b.vec[i][j + 3] += 1ll * temp * a.vec[k][j + 3] % mod;
					b.vec[i][j + 4] += 1ll * temp * a.vec[k][j + 4] % mod;
					b.vec[i][j + 5] += 1ll * temp * a.vec[k][j + 5] % mod;
					b.vec[i][j + 6] += 1ll * temp * a.vec[k][j + 6] % mod;
					b.vec[i][j + 7] += 1ll * temp * a.vec[k][j + 7] % mod;
					
					b.vec[i][j] = (b.vec[i][j] % mod + mod) % mod;
					b.vec[i][j + 1] = (b.vec[i][j + 1] % mod + mod) % mod;
					b.vec[i][j + 2] = (b.vec[i][j + 2] % mod + mod) % mod;
					b.vec[i][j + 3] = (b.vec[i][j + 3] % mod + mod) % mod;
					b.vec[i][j + 4] = (b.vec[i][j + 4] % mod + mod) % mod;
					b.vec[i][j + 5] = (b.vec[i][j + 5] % mod + mod) % mod;
					b.vec[i][j + 6] = (b.vec[i][j + 6] % mod + mod) % mod;
					b.vec[i][j + 7] = (b.vec[i][j + 7] % mod + mod) % mod;
				}
			    while (j < a.vec[0].size())
			    {
					b.vec[i][j] += 1ll * temp * a.vec[k][j] % mod;
					b.vec[i][j] = (b.vec[i][j] % mod + mod) % mod;	
					j++;
			    }
			}
		return b;
	}
	
	void print()
	{
		for (auto i : vec)
		{
			for (auto j : i)
				printf("%d ", j);
			printf("\n");
		}
	}
};

int read()
{
    int res(0), ch(getchar()), f = 1;
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        res = res * 10 + ch - '0';
        ch = getchar();
    }
    return res * f;
}

int main()
{
	int n, m, p, i, j;
	scanf("%d %d %d", &n, &p, &m);
	Matrix A(n, p), B(p, m);
	for (i = 0; i < n; i++)
		for (j = 0; j < p; j++)
			A.vec[i][j] = read();
	for (i = 0; i < B.vec.size(); i++)
		for (j = 0; j < B.vec[0].size(); j++)
			B.vec[i][j] = read();
	Matrix C = A * B;
	C.print();
	return 0;
}