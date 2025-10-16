#include <bits/stdc++.h>

using namespace std;

namespace jumpmelon
{
	typedef long long big;

	const int MAXM = 22, MAXS = 500000, P = 232792561, G = 71;
	bool IsPrime[MAXM + 1], IsPP[MAXM + 1];
	int m, A[MAXM][MAXM], P0[MAXM], C[MAXM], Fa[MAXM], V[MAXM], VV[MAXM];
	int T[MAXM][MAXM], IT[MAXM][MAXM], M[MAXM][MAXM << 1], F[MAXS];
	int Y[MAXM], YY[MAXM];

	int inv(int x) { return x == 1 ? 1 : int(big(P - P / x) * inv(P % x) % P); }

	int find(int x)
	{
		if (Fa[x] != x)
			Fa[x] = find(Fa[x]);
		return Fa[x];
	}

	int qpow(int x, big n)
	{
		int s = 1;
		while (n)
		{
			if (n & 1)
				s = int((big)s * x % P);
			x = int((big)x * x % P);
			n >>= 1;
		}
		return s;
	}

	void Gauss()
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < m; j++)
				M[i][j] = T[i][j];
			M[i][m + i] = 1;
		}
		for (int i = 0; i < m; i++)
		{
			if (!M[i][i])
			{
				for (int j = i + 1; j < m; j++)
					if (M[j][i])
					{
						for (int k = 0; k < (m << 1); k++)
							swap(M[i][k], M[j][k]);
						break;
					}
			}
			for (int j = 0; j < m; j++)
				if (i != j)
				{
					int t = M[j][i];
					for (int k = 0; k < (m << 1); k++)
						M[j][k] = int(((big)M[j][k] * M[i][i] + big(P - M[i][k]) * t) % P);
				}
		}
		for (int i = 0; i < m; i++)
		{
			int v = inv(M[i][i]);
			for (int j = 0; j < m; j++)
				IT[i][j] = int((big)M[i][m + j] * v % P);
		}
	}

	void init()
	{
		memset(IsPrime + 1, 1, sizeof(bool[m]));
		for (int i = 2; i <= m; i++)
			if (IsPrime[i])
			{
				for (int j = i << 1; j <= m; j += i)
					IsPrime[j] = 0;
				for (int j = i; j <= m; j *= i)
					IsPP[j] = 1;
			}
		for (int i = 0; i < m; i++)
			for (P0[i] = i, C[i] = 1; A[P0[i]][i] != i; P0[i] = A[P0[i]][i])
				C[i]++;
		for (int i = 0; i < m; i++)
			Fa[i] = i;
		for (int s = 0; s < m; s++)
			if (P0[s] == s)
			{
				int c = 0;
				V[c++] = s;
				T[s][s] = 1;
				while (1)
				{
					int b = -1;
					for (int i = 0; i < m; i++)
						if (P0[i] == s && IsPP[C[i]] && (b == -1 || C[i] > C[b]))
						{
							bool fl = 1;
							for (int t = A[i][i]; t != i; t = A[t][i])
								if (find(t) == find(i))
								{
									fl = 0;
									break;
								}
							if (fl)
								b = i;
						}
					if (b == -1)
						break;
					for (int i = 0; i < m; i++)
						if (P0[i] == s)
							Fa[find(i)] = find(A[i][b]);
					int cc = c;
					memcpy(VV, V, sizeof(int[cc]));
					c = 0;
					for (int i = 0; i < cc; i++)
						for (int j = 0, t = VV[i]; j < C[b]; j++, t = A[t][b])
						{
							for (int k = 0; k < cc; k++)
								for (int w = 0, tt = VV[k]; w < C[b]; w++, tt = A[tt][b])
									T[t][tt] = int((big)T[VV[i]][VV[k]] * qpow(G, (P - 1) / C[b] * (j * w % C[b])) % P);
							V[c++] = t;
						}
				}
				for (int i = 0; i < c; i++)
					for (int j = 0; j < m; j++)
						if (P0[A[j][s]] == s)
							T[V[i]][j] = T[V[i]][A[j][s]];
			}
		Gauss();
	}

	void FWT(const int TT[MAXM][MAXM], int *X, int n)
	{
		for (int l = 1; l < n; l *= m)
			for (int i = 0; i < n; i += l * m)
				for (int j = 0; j < l; j++)
				{
					for (int k = 0; k < m; k++)
						Y[k] = X[l * k + i + j];
					memset(YY, 0, sizeof(int[m]));
					for (int x = 0; x < m; x++)
						for (int y = 0; y < m; y++)
							YY[x] = int((YY[x] + (big)Y[y] * TT[x][y]) % P);
					for (int k = 0; k < m; k++)
						X[l * k + i + j] = YY[k];
				}
	}

	void work()
	{
		int n, s = 1;
		big k;
		scanf("%d%d%lld", &n, &m, &k);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &A[i][j]);
		init();
		for (int i = 0; i < n; i++)
			s *= m;
		for (int i = 0; i < s; i++)
			scanf("%d", &F[i]);
		FWT(T, F, s);
		for (int i = 0; i < s; i++)
			F[i] = qpow(F[i], k + 1);
		FWT(IT, F, s);
		for (int i = 0; i < s; i++)
			printf("%d\n", F[i]);
	}
}

int main()
{
	jumpmelon::work();
	return 0;
}
