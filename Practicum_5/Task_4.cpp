#include<stdio.h>
#include<stdlib.h>
#include<easyx.h>
#include<math.h>
#include<conio.h>
#define N1 5
#define N2 5
#define l1 1.0
#define l2 1.0
#define pi 3.1415926535
//#define dim (N1-1)*(N2-1)
//#define chi 100

const int dim = (N1 - 1) * (N2 - 1);
double chi = 100;

double h1 = l1 / N1; double h2 = l2 / N2;
double Delta = 4 / (h1 * h1) + 4 / (h2 * h2);
double delta = (4 / (h1 * h1)) * sin((pi * h1) / (2 * l1)) * sin((pi * h1) / (2 * l1)) 
			 + (4 / (h2 * h2)) * sin((pi * h2) / (2 * l2)) * sin((pi * h2) / (2 * l2));
double v = 2 / sqrt(Delta * delta);
double y[dim + 1];
double f[dim + 1];

int Trans(int i, int j) { return (N1 - 1) * (N2 - 1) - (j - 1) * (N2 - 1) - (i - 1); }
//int invTransi(int k) { int i; if (k % (N1 - 1) == 0) i = 1; else i = N2 - k % (N2 - 1); return i; }
//int invTransj(int k) { int j; if (k % (N1 - 1) == 0) j = N1 - k / (N2 - 1); else j = N1 - 1 - k / (N2 - 1); return j; }
int Index(int i, int j) { return (i - 1) * (dim+1) + (j - 1); }
//y_ij ----Trans----> j  - the j-th variable

double pointwise(double x1[], double x2[]) {
	double res = 0;
	for (int i = 1; i <= dim; i++) {
		res += x1[i] * x2[i];
	}
	return res;
}

double norm(double x[]) {
	double tmp = 0;
	for (int i = 1; i <= dim; i++) {
		tmp += (x[i] * x[i]);
	}
	return sqrt(tmp);
}

void CLAU() {
	double* A1 = (double*)malloc(sizeof(double) * ((dim + 1) * (dim + 1)));
	//double A1[(dim + 1) * (dim + 1)];
	double* E_vA1 = (double*)malloc(sizeof(double) * ((dim + 1) * (dim + 1)));
	double* E_vA2 = (double*)malloc(sizeof(double) * ((dim + 1) * (dim + 1)));
	//double E_vA1_inv[(dim + 1) * (dim + 1)];
	double* E_vA1_inv = (double*)malloc(sizeof(double) * ((dim + 1) * (dim + 1)));
	
	double* A = (double*)malloc(sizeof(double) * ((dim + 1) * (dim + 1)));
	double* B= (double*)malloc(sizeof(double) * ((dim + 1) * (dim + 1)));
	double* B_inv = (double*)malloc(sizeof(double) * ((dim + 1) * (dim + 1)));
	//double A[(dim + 1) * (dim + 1)];
	//double B[(dim + 1) * (dim + 1)];
	//double B_inv[(dim + 1) * (dim + 1)];
	
	//init f
	for (int i = N2-1; i >= 1; i--) {
		for (int j = 1; j <= N1-1; j++) {
			if (( (i * h1 - 0.5) * (i * h1 - 0.5) + (j * h2 - 0.5) * (j * h2 - 0.5)) > 0.125) f[Trans(i, j)] = 1;
			else f[Trans(i, j)] = 1.0 / chi;
			//f[Index(i, j)] = 1;
		}
	}

	printf("-------f-------\n");
	for (int i = N2-1; i >= 1; i--) {
		for (int j = 1; j <= N1 - 1; j++)
			printf("%d %.3f ", Trans(i, j), f[Trans(i, j)]);
		printf("\n");
	}
	printf("----------------\n");
	
	//init y
	for (int i = 0; i <= dim; i++) y[i] = 0.0;
	// 1/h_1^2 y_i+1,j + 1/h_1h_2 y_i,j+1 - (1/h_1^2 + 1/h_1h_2) y_i,j

	//A1
	for (int i = 1; i <= dim; i++)
		for (int j = 1; j <= dim; j++)
			A1[Index(i, j)] = 0;
	int counteq = 1;
	for (int j = N1 - 1; j >= 1; j--) {
		for (int i = N2 - 1; i >= 1; i--) {
			//printf("%d %d %d %d %d %d\n", counteq, i, j, Trans(i + 1, j), Trans(i, j + 1), Trans(i, j));
			if (i + 1 <= N1 - 1) A1[Index(counteq, Trans(i + 1, j))] = 1.0 / (h1 * h1);
			//else A1[Index(counteq, Trans(i + 1, j))] = 0;
			if (j + 1 <= N2 - 1) A1[Index(counteq, Trans(i, j + 1))] = 1.0 / (h1 * h2);
			//else A1[Index(counteq, Trans(i, j + 1))] = 0;
			A1[Index(counteq, Trans(i, j))] = (-1.0) / (h1 * h1) + (-1.0) / (h1 * h2);
			counteq++;
		}
	}
	printf("-------A1-------\n");
	for (int i = 1; i<=dim ; i++) {
		for (int j = 1; j <= dim; j++)
			printf("%.4f ", A1[Index(i, j)]);
		printf("\n");
	}

	//E_vA1 = E + v*A1
	for (int i = 1; i <= dim; i++)
		for (int j = 1; j <= dim; j++) {
			if (i != j) E_vA1[Index(i, j)] = v * A1[Index(i, j)];
			else E_vA1[Index(i, j)] = 1 + v * A1[Index(i, j)];
		}
	
	printf("-------E_vA1-------\n");
	for (int i = 1; i <= dim; i++) {
		for (int j = 1; j <= dim; j++)
			printf("%.4f ", E_vA1[Index(i, j)]);
		printf("\n");
	}
	
	//E_vA2=E_vA1^T
	for (int i = 1; i <= dim; i++)
		for (int j = 1; j <= dim; j++)
			E_vA2[Index(i, j)] = E_vA1[Index(j, i)];
	printf("-------E_vA2-------\n");
	for (int i = 1; i <= dim; i++) {
		for (int j = 1; j <= dim; j++)
			printf("%.4f ", E_vA2[Index(i, j)]);
		printf("\n");
	}
	
	
	//A=A1+A2
	for (int i = 1; i <= dim; i++) {
		for (int j = 1; j <= dim; j++) {
			if (i > j) A[Index(i, j)] = A1[Index(i, j)];
			else if (i < j) A[Index(i, j)] = A1[Index(j, i)];
			else A[Index(i, j)] = 2 * A1[Index(i, j)];
		}
	}
	free(A1);
	printf("-------A-------\n");
	for (int i = 1; i <= dim; i++) {
		for (int j = 1; j <= dim; j++)
			printf("%.4f ", A[Index(i, j)]);
		printf("\n");
	}
	
	
	//find B^-1
	for (int i = 1; i <= dim; i++)
		for (int j = 1; j <= dim; j++) {
			if (i != j) E_vA1_inv[Index(i, j)] = 0;
			else E_vA1_inv[Index(i, j)] = 1;
		}
	
	//double E_vA1_copy[(dim + 1) * (dim + 1)];
	double* E_vA1_copy = (double*)malloc(sizeof(double) * ((dim + 1) * (dim + 1)));
	for (int i = 1; i <= dim; i++)
		for (int j = 1; j <= dim; j++) {
			E_vA1_copy[Index(i, j)] = E_vA1[Index(i, j)];
		}
	//E_vA1^-1 - gauss method
	for (int j = 1; j <= dim; j++) {
		for (int i = dim; i >= j+1; i--) {
			double Relation = E_vA1_copy[Index(i, j)] / E_vA1_copy[Index(j, j)];
			for (int k = j; k <= dim; k++) 	E_vA1_copy[Index(i, k)] -= E_vA1_copy[Index(j, k)] * Relation;
			for (int k = 1; k <= dim; k++)	E_vA1_inv[Index(i, k)] -= E_vA1_inv[Index(j, k)] * Relation;
		}
	}

	for (int i = 1; i <= dim; i++)
		for (int j = 1; j <= dim; j++)
			E_vA1_inv[Index(i, j)] /= E_vA1_copy[Index(i,i)];
	printf("-------E_vA1_inv-------\n");
	for (int i = 1; i <= dim; i++) {
		for (int j = 1; j <= dim; j++)
			printf("%.4f ", E_vA1_inv[Index(i, j)]);
		printf("\n");
	}
	
	free(E_vA1_copy);

	//B^-1=[(E+vA1)^-1] * [(E+vA1)^-1]^T
	for (int i = 1; i <= dim; i++)
		for (int j = 1; j <= dim; j++) {
			double tmp = 0.0;
			for (int k = 1; k <= dim; k++) {
				tmp += E_vA1_inv[Index(i, k)] * E_vA1_inv[Index(j, k)];
			}
			B_inv[Index(i, j)] = tmp;
		}
	free(E_vA1_inv);
	printf("-------B_inv-------\n");
	for (int i = 1; i <= dim; i++) {
		for (int j = 1; j <= dim; j++)
			printf("%.4f ", B_inv[Index(i, j)]);
		printf("\n");
	}
	
	
	//B=(E+vA1)^T*(E+vA1)
	for (int i = 1; i <= dim; i++)
		for (int j = 1; j <= dim; j++) {
			double tmp = 0;
			for (int k = 1; k <= dim; k++) {
				tmp += E_vA1[Index(k, i)] * E_vA1[Index(k, j)];
			}
			B[Index(i, j)] = tmp;
		}
	printf("-------B-------\n");
	for (int i = 1; i <= dim; i++) {
		for (int j = 1; j <= dim; j++)
			printf("%.4f ", B[Index(i, j)]);
		printf("\n");
	}
	
	/*
	printf("-------B*B_inv-------\n");
	for (int i = 1; i <= dim; i++) {
		for (int j = 1; j <= dim; j++) {
			double tmp = 0;
			for (int k = 1; k <= dim; k++)
				tmp += B[Index(i, k)] * B_inv[Index(k, j)];
			printf("%.4f ", tmp);
		}
		printf("\n");
	}
	*/
	
	double* v = (double*)malloc( sizeof(double) * (dim + 1) );
	double* r = (double*)malloc(sizeof(double) * (dim + 1));
	double* A_v = (double*)malloc(sizeof(double) * (dim + 1));
	double tao;

	//double tao = 2.0 / (delta / (2.0 * (1.0 + sqrt(delta / Delta))) + delta / (4.0 * sqrt(delta / Delta)));
	//printf("tao: %f\n", tao);
	//printf("tao/4: %f\n", tao / 4);
	//printf("v: %f\n", v);

	double* ytmp = (double*)malloc(sizeof(double) * (dim + 1));
	double* phi = (double*)malloc(sizeof(double) * (dim + 1));

	double norm1 = norm(y);
	double norm2;
	int count = 0;
	while(1) {
		
		//r_n=Ay_n-f
		for (int i = 1; i <= dim; i++) {
			double tmp = 0;
			for (int k = 1; k <= dim; k++)
				tmp += A[Index(i, k)] * y[k];
			//printf("%d tmp:%f\n", i, tmp);
			r[i] = tmp - f[i];
		}
		//v_n=B^-1*r_n
		for (int i = 1; i <= dim; i++) {
			double tmp = 0;
			for (int k = 1; k <= dim; k++)
				tmp += B_inv[Index(i, k)] * r[k];
			v[i] = tmp;
		}
		//Av_n
		for (int i = 1; i <= dim; i++) {
			double tmp = 0;
			for (int k = 1; k <= dim; k++)
				tmp += A[Index(i, k)] * v[k];
			A_v[i] = tmp;
		}

		//printf("------r v A_v------------\n");
		//for (int i = 1; i <= dim; i++) printf("%f ", r[i]); printf("\n");
		//for (int i = 1; i <= dim; i++) printf("%f ", v[i]); printf("\n");
		//for (int i = 1; i <= dim; i++) printf("%f ", A_v[i]); printf("\n");
		//tao
		tao = pointwise(v, r) / pointwise(v, A_v);
		//printf("(v,r) = %f\n", pointwise(v, r));
		//printf("(v,A_v) = %f\n", pointwise(v, A_v));
		//printf("-------tao norm---count = %d----\n", count);
		//printf("tao: %.30f\n", tao);
		
		//phi=(B-tao_n+1*A)y_n+tao_n+1*f
		for (int i = 1; i <= dim; i++) {
			double tmp = 0;
			for (int k = 1; k <= dim; k++)
				tmp += (B[Index(i, k)] - tao * A[Index(i, k)]) * y[k];
			phi[i] = tmp + tao * f[i];
		}

		//tmp - up triangle matrix
		for (int i = dim; i >= 1; i--) {
			double sum = 0;
			for (int j = dim; j > i; j--) {
				sum += E_vA2[Index(i, j)] * ytmp[j];
			}
			ytmp[i] = (phi[i] - sum) / E_vA2[Index(i, i)];
			//y[i] = (ytmp[i] - sum) / E_vA2[Index(i, i)];
		}

		//y - down triangle matrix
		for (int i = 1; i <= dim; i++) {
			double sum = 0;
			for (int j = 1; j < i; j++)
				sum += E_vA1[Index(i, j)] * y[j];
			//ytmp[i] = (phi[i] - sum) / E_vA1[Index(i, i)];
			y[i] = (ytmp[i] - sum) / E_vA1[Index(i, i)];
		}

		norm2 = norm(y);
		/*
		printf("norm = %f\n", norm2);
		printf("norm2-norm1 = %f\n", fabs(norm2 - norm1));
		printf("-------y---count = %d----\n", count);
		for (int i = N2 - 1; i >= 1; i--) {
			for (int j = 1; j <= N1 - 1; j++)
				printf("%.4f ", y[Trans(i, j)]);
			printf("\n");
		}
		printf("\n");
		*/
		//if(count%100==0) 
			printf("count = %d fabs(norm2-norm1)= %f\n", count, fabs(norm2 - norm1));
		if (count != 1 && fabs(norm2 - norm1) <= 0.001) {
			printf("count = %d fabs(norm2-norm1)= %f\n", count, fabs(norm2 - norm1));
			break;
		}
		//chi=0.1 -> 5-0.0005 10-0.0005
		//chi=100 -> 5-0.0005 10-0.0005
		count++;
		norm1 = norm2;
	}

	free(A);
	free(B);
	free(B_inv);
	free(E_vA1);
	free(E_vA2);
	free(v);
	free(r);
	free(A_v);
	free(phi);
	free(ytmp);
}

double ColorTrans(float a, float b, float val) { //down - up bounds and value
	return (b - val) / (b - a) * 256;
	//blue (0,0,255) red (255,0,0)
}

int main() {
	printf("h1: %.4f l1: %.4f h2: %.4f l2: %.4f", h1, l1, h2, l2);
	printf("\nDelta: %f delta: %f v: %f\n", Delta,delta,v);
	CLAU();

	printf("-------y----------\n");
	for (int i = N2 - 1; i >= 1; i--) {
		for (int j = 1; j <= N1 - 1; j++)
			printf("%.4f ", y[Trans(i, j)]);
		printf("\n");
	}
	printf("\n");
	
	initgraph(900, 600);	// create graph area
	//x:300-600, y:150-450
	setbkcolor(WHITE);
	cleardevice();

	
	for (int i = 0; i <= N2; i++) {
		for (int j = 0; j <= N1; j++) {
			double valuex = i * h1;
			double valuey = j * h2;
			double pixelx = 300 + 300 * valuex;
			double pixely = 450 - 300 * valuey;
			if (i != 0 && j != 0 && i != N2 && j != N1) setfillcolor(HSLtoRGB(ColorTrans(0, 1, y[Trans(i, j)]), 0.5, 0.5));
			else setfillcolor(HSLtoRGB(ColorTrans(0, 1, 0.0), 0.5, 0.5));
			//chi=100 -> 0-0.1
			//chi=0.1 -> -0.05-0.15
			solidcircle(pixelx, pixely, 1.5 * 300 * h1 / 2);
		}
	}

	setlinecolor(BLACK);
	line(50, 450, 850, 450);
	line(300, 50, 300, 500);

	settextcolor(BLACK);
	TCHAR S1[] = _T("1.0");
	outtextxy(600, 450, S1);
	TCHAR S2[] = _T("0.0");
	outtextxy(300, 450, S2);
	TCHAR S3[] = _T("1.0");
	outtextxy(300, 150, S3);

	//TCHAR img[] = _T("chi_100_n_30_eps_0.01.jpg");
	//saveimage(img);
	_getch();
	closegraph();
	
	return 0;
}