#include<stdio.h>
#include<math.h>

int main(void) {
	int t, N;
	int solve(int);
	setbuf(stdout, NULL);
	scanf("%d", &t);
	for (int test_case = 0; test_case < t; test_case++) {
		scanf("%d", &N);
		printf("Case #%d\n", test_case + 1);
		printf("%d\n", solve(N));
	}
	return 0;
}

int solve(int N) {
	int digit2=N, digit3=N,b,basis,answer;
/*
    for(basis=2;basis<=N;basis++){
        long temp=basis;
        for(i=2;i<=N;i++){
            if(temp>N)
            break;
            	if (N % (int)((temp*basis - 1) / (basis - 1)) == 0 && N / (int)((temp*basis - 1) / (basis - 1))<basis) {
    			    return N;
				break;
            }
        }
    }   --> for(basis<=N) -> overflow
        N = 1000000007�� ��� ��� for���� ���µ� if���� �ɸ��� ���� -> time limit
        for���� N�� ��� ���ϱ�?
        3�ڸ� �� �̻��� ��� b^2 + b^1 + b^0 --> b^2 b�� ��ƮN�� ������ N���� ũ�Ƿ�
        ��ƮN������ ������ �ٲٰ� ����Ͽ� ���� ���� ��쿡��
        2�ڸ� ��츦 ���� ������ָ� ��(�ڸ����� Ŭ���� b�� �۱� ������)
*/
	// i==3�̻��� ��� N = (b^i + b^i-1 + .... + b^1 + b^0)k
	for (basis = 2; basis <= (int)sqrt(N); basis++) {
		long temp = basis*basis;
		for (int i = 3; i <= (int)sqrt(N); i++) {
			if (temp>N)
				break;
			if (N % (int)((temp*basis - 1) / (basis - 1)) == 0 && N / (int)((temp*basis - 1) / (basis - 1))<basis) {
				digit3 = basis;
				basis = N;
				break;
			}
			temp *= basis;
		}
	}
	if (basis == (int)sqrt(N)+1) {     // if�� ��� x -> �� x
		digit3 = N - 1;
	
	// i==2�� ��� N = (b^1 + b^0)k       k�� Ŭ���� b�� ����
	for (int k = (int)sqrt(N); k >= 2; k--) {
		if (N%k == 0) {
			b = N / k - 1;
			if (b > k) {
				digit2 = b;
				break;
			}
		}
	}
	}
	if(digit2<digit3)
	digit3=digit2;

    //��� k>=2, i>=3�̹Ƿ�  N=1,2,3�� ��� for���� ���ư��� �����Ƿ� ���� ���� ����
	if (N == 1) digit3 = 2;
	if (N == 2) digit3 = 3;
	if (N == 3) digit3 = 2;

	return digit3;
}
