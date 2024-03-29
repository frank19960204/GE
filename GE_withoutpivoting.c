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

void forward(){
	for(int i = 0;i<4;i++){
		for(int j = i+1;j<5;j++){
			//printf("(%d,%d)=%f\n",j,i,);
			//printf("(%d,%d)=%f\n",i,i,linearsystem[i][i]);
			double alpha =  linearsystem2[j][i]/linearsystem2[i][i]; //alpha is first nonzero number divided by pivot
			//printf("alpha:%f\n",alpha);
			for(int k = i+1;k<5;k++){
				linearsystem2[j][k] -= linearsystem2[i][k] * alpha;	
			}
			coef2[j] -= coef2[i] * alpha;
			//printf("coef[%d]:%f",j,coef[j]);
		}
		for(int x = 0;x<5;x++){
			for(int y = 0;y<5;y++){
				printf("%lf ",linearsystem2[x][y]);
			}
			printf("| %lf\n",coef2[x]);
		}
		printf("--------------------------------\n");
		
	}
}

void backward(){
	for(int i = 4;i>=0;i--){
		for(int j = 4;j>i;j--){
			//printf("gp\n");
			coef2[i] -= linearsystem2[i][j]*answer[i+1];
		}
		//printf("coef[%d]:%f\n",i,coef[4]);
		answer[i] = coef2[i]/linearsystem2[i][i];	

	}
}

void swap(int a,int b){
	double temp;
	for(int i = 0;i<5;i++){ 
 		temp = linearsystem2[a][i];
 		linearsystem2[a][i] = linearsystem2[b][i];
 		linearsystem2[b][i] = temp;
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




