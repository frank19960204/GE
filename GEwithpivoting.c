#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


float linearsystem[5][5] = {{1.0/1.0,1.0/2.0,1.0/3.0,1.0/4.0,1.0/5.0},
						  	{1.0/2.0,1.0/3.0,1.0/4.0,1.0/5.0,1.0/6.0},
						  	{1.0/3.0,1.0/4.0,1.0/5.0,1.0/6.0,1.0/7.0},
						  	{1.0/4.0,1.0/5.0,1.0/6.0,1.0/7.0,1.0/8.0},
						  	{1.0/5.0,1.0/6.0,1.0/7.0,1.0/8.0,1.0/9.0}};
float coef[5] = {137.0/60.0,29.0/20.0,153.0/140.0,743.0/840.0,1879.0/2520.0};
float answer[5] = {0.0,0.0,0.0,0.0,0.0};

void swap(int a,int b){
	float temp;
	for(int i = 0;i<5;i++){ 
 		temp = linearsystem[a][i];
 		linearsystem[a][i] = linearsystem[b][i];
 		linearsystem[b][i] = temp;
 	}
 	temp = coef[a];
 	coef[a] = coef[b];
 	coef[b] = temp;
}

void pivoting(int a){
	int biggest = a;
	for(int i = a;i<5;i++){
		if(linearsystem[i][a]>=0 || linearsystem[biggest][a]>=0){
			if(linearsystem[i][a]>linearsystem[biggest][a]){
				biggest = i;
			}
		}
		else{
			if(linearsystem[i][a]<linearsystem[biggest][a]){
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
				printf("%f ",linearsystem[k][j]);
			}
			printf("| %f \n",coef[k]);	
		}
		printf("-----------------------------------------------------------------------\n");
		for(int j = i+1;j<5;j++){
			float alpha =  linearsystem[j][i]/linearsystem[i][i]; //alpha is first nonzero number divided by pivot
			for(int k = i+1;k<5;k++){
				linearsystem[j][k] -= linearsystem[i][k] * alpha;	
			}
			coef[j] -= coef[i] * alpha;
		}
	}
}

void backward(){
	for(int i = 4;i>=0;i--){
		for(int j = 4;j>i;j--){
			coef[i] -= linearsystem[i][j]*answer[i+1];
		}
		answer[i] = coef[i]/linearsystem[i][i];	

	}
}



int main(){
	forward();
	backward();
	float diff = 0.0;
	for(int i = 0;i<5;i++){
		printf("x%d:%f\n",i,answer[i]);
	}
	for(int i = 0;i<5;i++){
		diff += ((1.0 - answer[i]) * (1.0 - answer[i]));
	}
	diff = sqrtf(diff);
	printf("2-norm of difference: %f\n\n",diff);
}




