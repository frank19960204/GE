#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


double linearsystem1[5][5] = {{1.0/1.0,1.0/2.0,1.0/3.0,1.0/4.0,1.0/5.0},
						  	{1.0/2.0,1.0/3.0,1.0/4.0,1.0/5.0,1.0/6.0},
						  	{1.0/3.0,1.0/4.0,1.0/5.0,1.0/6.0,1.0/7.0},
						  	{1.0/4.0,1.0/5.0,1.0/6.0,1.0/7.0,1.0/8.0},
						  	{1.0/5.0,1.0/6.0,1.0/7.0,1.0/8.0,1.0/9.0}};
double linearsystem2[5][5] = {{1.0,2.0,3.0,4.0,5.0},
						  	  {200.0,1.0,1.0,2.0,3.0},
						  	  {1.0,2.0,1000.0,1.0,1.0},
						  	  {1.0,1.0,1.0,1.0,1.0},
						  	  {5.0,6.0,7.0,8.0,9.0}};
double coef1[5] = {137.0/60.0,29.0/20.0,153.0/140.0,743.0/840.0,1879.0/2520.0};
double coef2[5] = {15.0,207.0,1005.0,5.0,35.0};
double answer[5] = {0.0,0.0,0.0,0.0,0.0};

void swap(int a,int b){
	double temp;
	for(int i = 0;i<5;i++){ 
 		temp = linearsystem2[a][i];
 		linearsystem2[a][i] = linearsystem2[b][i];
 		linearsystem2[b][i] = temp;
 	}
 	temp = coef2[a];
 	coef2[a] = coef2[b];
 	coef2[b] = temp;
}

void pivoting(int a){
	int biggest = a;
	for(int i = a;i<5;i++){
		if(linearsystem2[i][a]>=0 || linearsystem2[biggest][a]>=0){
			if(linearsystem2[i][a]>linearsystem2[biggest][a]){
				biggest = i;
			}
		}
		else{
			if(linearsystem2[i][a]<linearsystem2[biggest][a]){
				biggest = i;
			}
		}
	}
	if(biggest != a){
		swap(biggest,a);
	}
}

void forward(){
	//swap(0,1);
	
	for(int i = 0;i<4;i++){
		pivoting(i);
		for(int k = 0;k<5;k++){
			for(int j = 0;j<5;j++){
				printf("%lf ",linearsystem2[k][j]);
			}
			printf("| %lf \n",coef2[k]);	
		}
		printf("-----------------------------------------------------------------------\n");
		for(int j = i+1;j<5;j++){
			double alpha =  linearsystem2[j][i]/linearsystem2[i][i]; //alpha is first nonzero number divided by pivot
			for(int k = i+1;k<5;k++){
				linearsystem2[j][k] -= linearsystem2[i][k] * alpha;	
			}
			coef2[j] -= coef2[i] * alpha;
		}
	}
}

void backward(){
	for(int i = 4;i>=0;i--){
		for(int j = 4;j>i;j--){
			coef2[i] -= linearsystem2[i][j]*answer[i+1];
		}
		answer[i] = coef2[i]/linearsystem2[i][i];	

	}
}



int main(){
	forward();
	backward();
	double diff = 0.0;
	for(int i = 0;i<5;i++){
		printf("x%d:%lf\n",i,answer[i]);
	}
	for(int i = 0;i<5;i++){
		diff += ((1.0 - answer[i]) * (1.0 - answer[i]));
	}
	diff = sqrt(diff);
	printf("2-norm of difference: %lf\n\n",diff);
}




