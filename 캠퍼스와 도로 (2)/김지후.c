//#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#define MAX 10001

short Dijkstra(short);
short choose(short[], short[]);
short Test(short,short);
short isNeedTest(short, short);

short map[500][500];
short N, M;
short *needTest, Answer[500], distance[500];

int main(void)
{	
	short i,j,start,end,far;
	short T, test_case,acount,tcount;
	//FILE * input;
	setbuf(stdout, NULL);
	//input=fopen("input.txt", "r");
	//fscanf(input,"%hd",&T);
	scanf("%hd",&T);
	for (test_case = 0; test_case < T; test_case++)
	{	
		acount = 0;
		//matrix 초기화
		//fscanf(input,"%hd %hd", &N, &M);
		scanf("%hd %hd", &N, &M);
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
				map[i][j] = MAX;
		}
		for (i = 0; i < M; i++)
		{
			//fscanf(input,"%hd %hd %hd", &start, &end, &far);
			scanf("%hd %hd %hd", &start, &end, &far);
			if (map[start-1][end-1] > far)
			{
				map[start-1][end-1] = far;
				map[end-1][start-1] = far;
			}
		}
		// 모든 경우 출발점 다익스트라
		for (start = 0; start < N; start++)
		{
			tcount = Dijkstra(start);
			//테스트
			for (end = 0; end < tcount; end++)
			{	
				if (isNeedTest(needTest[end],acount)==1)
				{
					if (Test(needTest[end], start) ==1)
					{
						if (acount == 0)
							Answer[acount++] = needTest[end];
						else
						{
							for (i = 0; i < acount; i++)
							{
								if (Answer[i] > needTest[end]) {
									for (j = acount; j >i; j--)
										Answer[j] = Answer[j - 1];
									Answer[i] = needTest[end];
									acount++;
									break;
								}
							}
						}
					}
				}
			}

		}

		printf("Case #%d\n", test_case + 1);
		printf("%d ", acount);
		for (i = 0; i < acount; i++)
			printf("%d ", Answer[i] + 1);
		printf("\n");
		free(needTest);
	}

	return 0;
}

short Test(short testCase, short startPoint) {
	short *tdistance;
	short *unvisit,i,u,w;
	short tmap[500][500];
	unvisit = (short*)malloc(sizeof(short)*N);
	tdistance = (short*)malloc(sizeof(short)*N);
	for (i = 0; i < N; i++)
	{
		for (u = 0; u < N; u++)
		{
			if (u == testCase || i == testCase)
				tmap[i][u] = MAX;
			else
				tmap[i][u] = map[i][u]; 
		}
		unvisit[i] = 0;
	}
	for(i=0; i<N; i++)
		tdistance[i] = tmap[startPoint][i];
	unvisit[startPoint] = 1;
	tdistance[startPoint] = 0;
	tdistance[testCase] = MAX;

	//찾아 보자
	for (i = 0; i < N - 1; i++)
	{
		u = choose(tdistance, unvisit);
		unvisit[u] = 1;
		if (u == -1)
			continue;
		for (w = 0; w < N; w++)
		{
			//middle 판별
			if (unvisit[w] == 0) {
				if (tdistance[u] + tmap[u][w] < tdistance[w])
					tdistance[w] = tdistance[u] + tmap[u][w];
			}
		}
	}
	u = 0;
	//길이가 같거나 짧은게 있나?
	for (i = 0; i < N; i++)
	{
		if (distance[i] < tdistance[i] && i!=startPoint&&i!=testCase)
		{
			u = 1;
			break;
		}
	}

	//free(tdistance);
	//free(unvisit);
	return u;
}

short Dijkstra(short startPoint) {
	short *unvisit;
	short i, u, w, count = 0,flag;
	needTest = (short*)malloc(sizeof(short)*N);
	unvisit = (short*)malloc(sizeof(short)*N);
	//초기화
	for (i = 0; i < N; i++)
	{
		distance[i] = map[startPoint][i];
		unvisit[i] = 0;
	}
	unvisit[startPoint] = 1;
	distance[startPoint] = 0;

	//찾아 보자
	for (i = 0; i < N - 1; i++)
	{
		u = choose(distance, unvisit);
		unvisit[u] = 1;
		flag = 0;
		for (w = 0; w < N; w++)
		{	
			//middle 판별
			if (unvisit[w] == 0 && distance[u] + map[u][w] < distance[w])
			{
				distance[w] = distance[u] + map[u][w];
				if (flag==0)
				{
					flag = 1;
					needTest[count] =u;
					count++;
				}
			}
		}
	}
	//free(unvisit);
	return count;
}

short choose(short dista[], short found[]) {
	short i,result=-1;
	short min = MAX;

	for (i = 0; i < N; i++)
	{
		if (dista[i] < min && found[i] == 0)
		{
			min = dista[i];
			result = i;
		}
	}
	return result;
}

short isNeedTest(short testCase,short anwercase) {
	int i;
	for (i = 0; i < anwercase; i++)
	{
		if (testCase == Answer[i])
			return 0;
	}
	return 1;
}
