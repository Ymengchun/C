#include <stdio.h>
#include <stdbool.h>
#define MAXPROCESS 50
#define MAXRESOURSE 100

int Available[MAXRESOURSE];
int Max[MAXPROCESS][MAXPROCESS];
int Allocation[MAXPROCESS][MAXPROCESS];
int Need[MAXPROCESS][MAXPROCESS];
int Request[MAXPROCESS][MAXPROCESS];
int Finish[MAXPROCESS];
int p[MAXPROCESS];
int m, n;	 // m个进程，n个资源

void Init();
int Safe();
void Banker();

int main(void){
	Init();
	Safe();
	Banker();
} 

void Init(){
	int i, j;
	printf("请输入进程的数目：\n");
	scanf("%d", &m);
	printf("请输入资源的种类：\n");
	scanf("%d", &n);
	
	printf("请输入每个进程所需的资源数，按照 %dx%d 矩阵输入\n", m, n);
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			scanf("%d", &Max[i][j]);
		}
	}
	
	printf("请输入每个进程已分配到的资源数，也按照 %dx%d 矩阵输入\n", m, n);
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++){
			scanf("%d", &Allocation[i][j]);
			Need[i][j] = Max[i][j] - Allocation[i][j];
			if(Need[i][j] < 0){
				printf("您输入的第 %d 个进程拥有的第 %d 个资源数错误，请重新输入：\n", i+1, j+1);
				j--;
				continue;
			}
		}
	}
	
	printf("请输入各个资源现有的数目：\n");
	
	for(i = 0; i < n; i++){
		scanf("&d", &Available[i]);
	}
	
}

int Safe(){
	int i, j, k, l;
	int Work[MAXRESOURSE];
	for(i = 0; i < n; i++){
		Work[i] = Available[i];
	}
	
	for(i = 0; i < m; i++){
		Finish[i] = false;
	}
	
	for(i = 0; i < m; i++){
		if(Finish[i] = true)
			continue;
		else{
			for(j = 0; j < n; j++){
				if(Need[i][j] > Work[j]){
					break;
				}
			}
			if(j == n){
				Finish[i] = true;
				for(k = 0; k < n; k++){
					Work[k] += Allocation[i][k];
				}
				p[l++] = i;
				i = -1;
			}
			else{
				continue;
			}
		}
		
		if(l == m){
			printf("系统是安全的\n");
			printf("安全序列：\n");
			for(i = 0; i < l; i++){
				printf("%d", p[i]);
				if(i != l-1){
					printf("-->");
				}
			}
			return true;
		}
	}
	printf("系统不是安全的\n");
	return false;	
}

/* 银行家算法 */ 
void Banker(){
	int i, cusneed;
	char again;
	while(1){
		printf("请输入申请资源的进程号(注：第一个进程号为0)\n");
		scanf("%d", &cusneed);
		
		for(i = 0; i < n; i++){
			scanf("%d", &Request[cusneed][i]);
		}
		
		for(i = 0; i < n; i++){
			if(Request[cusneed][i] > Need[cusneed][i]){
				printf("您输入的请求数超过进程的需求量！请重新输入！\n");
				continue;
			}	
			
			if(Request[cusneed][i] > Available[i]){
				printf("您输入的请求数超过系统拥有的资源数！请重新输入！\n");
				continue;
			}	
		}
	
		for(i = 0; i < n; i++){
			Available[i] -= Request[cusneed][i];
			Allocation[cusneed][i] += Request[cusneed][i];
			Need[cusneed][i] -= Request[cusneed][i];
		}
		
		if(Safe()){
			printf("同意分配请求！\n");
		}
		
		else{
			printf("您的请求被拒绝！\n");
			for(i = 0; i < n; i++){
				Available[i] -= Request[cusneed][i];
				Allocation[cusneed][i] += Request[cusneed][i];
				Need[cusneed][i] -= Request[cusneed][i];
			}
		}
		
		for(i = 0; i < m; i++){
			Finish[i] = false; 
		}
		
		printf("您还想再次请求分配吗？是请按 y/Y，否请按其他键\n");
		scanf("%c", &again);
		
		if(again == 'y' || again == 'Y'){
			continue;
		}
		
		break;
	}
}
