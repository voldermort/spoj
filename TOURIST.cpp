#include <cstdio>
#include <set>
#include <map>
#include <algorithm>
#include <memory.h>
using namespace std;

template<class T> void checkmax(T &a,T b){if(b>a) a=b;}

char m[128][128];
char q[100*100*100*4];

short d[100][100][100][100];

int main() {
	//freopen("input.txt","r",stdin);

	int t;
	scanf("%d", &t);
	while(t--){
		int R,C;
		scanf("%d%d", &C, &R);
		gets(m[0]);
		for(int r=0;r<R;r++)gets(m[r]);

		int qh=0, qt=0;
		q[qt++]=0;
		q[qt++]=0;
		q[qt++]=0;
		q[qt++]=0;

		d[0][0][0][0] = (m[0][0]=='*') + 1;

		int dr1[] = {0, 1, 0, 1};
		int dc1[] = {1, 0, 1, 0};
		int dr2[] = {0, 1, 1, 0};
		int dc2[] = {1, 0, 0, 1};

		short res = 0;

		while(qh<qt){
			int r1=q[qh++];
			int c1=q[qh++];
			int r2=q[qh++];
			int c2=q[qh++];			
			short cur_d = d[r1][c1][r2][c2];
			if(r1==R-1 && c1==C-1 && r2==R-1 && c2==C-1) res = cur_d;
			d[r1][c1][r2][c2]=0;

			for(int i=0; i<4; i++){
				int nr1=r1+dr1[i];
				int nc1=c1+dc1[i];
				int nr2=r2+dr2[i];
				int nc2=c2+dc2[i];

				if(nc1<=nc2 && nr1<R && nc1<C && nr2<R && nc2<C && m[nr1][nc1]!='#' && m[nr2][nc2]!='#'){
					if(d[nr1][nc1][nr2][nc2] == 0){
						q[qt++]=nr1;
						q[qt++]=nc1;
						q[qt++]=nr2;
						q[qt++]=nc2;
					}

					checkmax(d[nr1][nc1][nr2][nc2], (short)(cur_d + (m[nr1][nc1]=='*') + (m[nr2][nc2]=='*' && (nr1!=nr2||nc1!=nc2))));
				}
			}
		}

		printf("%d\n", res - 1);
	}
}
