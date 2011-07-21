#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

template<class T> void checkmax(T &a,T b){if(b>a) a=b;}

char a[1001];
char b[1001];
short dp0[1001][1001];
short dp1[2][1001];
short lmatch[2][1001];

int main() {
	//freopen("input.txt","r",stdin);

	while(true)
	{
		int K;
		scanf("%d\n",&K);
		if(!K)break;
		gets(a);
		gets(b);
		int l1=strlen(a),l2=strlen(b);
		/*
		dp[i][j][0] denotes the length of LCS which follows the constraint that each 
		segment of LCS except the last one is of length>=K and the last segment of it 
		can be of any length>=0 but it should end at index i,j of two string 'a' and 'b' 
		respectively.

		dp[i][j][1] denotes the length of LCS which strictly follows the constraint
		given by problem that each segment of it will be of length>=K
		*/
		int z=1;
		memset(dp1[0], 0, sizeof(dp1[0]));
		memset(lmatch[0], 0, sizeof(lmatch[0]));
		for(int i=0;i<l1;i++,z^=1) for(int j=0;j<l2;j++)
		{
			dp0[i + 1][j + 1] = dp1[z][j + 1] = max(dp1[z^1][j + 1], dp1[z][j]);

			if (a[i]==b[j])
			{
				checkmax(dp0[i + 1][j + 1], (short) (1 + dp0[i][j]));

				lmatch[z][j+1] = 1 + lmatch[z^1][j];

				if (lmatch[z][j+1] >= K)
					checkmax(dp1[z][j + 1], (short) (K + dp0[i + 1 - K][j + 1 - K]));
			} else {
				lmatch[z][j+1] = 0;
			}
		}
		printf("%d\n", dp1[z^1][l2]);
	}
	return 0;
}
