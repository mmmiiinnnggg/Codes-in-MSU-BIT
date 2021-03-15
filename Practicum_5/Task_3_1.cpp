#include<stdio.h>
#include<stdlib.h>
#include<easyx.h>
#include<math.h>
#include<conio.h>
#define lambda 1.0
#define a 0.0
#define b 1.0
#define N 100
double h = (b - a) / (N * (1.0));

double* x = (double*)malloc(sizeof(double) * (N + 1));
double* s = (double*)malloc(sizeof(double) * (N + 1));
double* u = (double*)malloc(sizeof(double) * (N + 1));

double K_1(double x, double s) { return x - s; }
double K_2(double x, double s) { return fabs(x - s); }
double f_1(double x) { return 3.0 / 2 - x; } // u=1
double f_2(double x) { return x / 2 + 1 / 3.0; } //u=x
double f_3(double x) { return x * x - 1 / 3.0 * x + 1 / 4.0; } //u=x^2
double f_4(double x) { return 3 - 2 * x; } // u=2
double f_5(double x) { return x * x * x; }


void CLAY(double (*K)(double x, double s), double (*f_)(double x)) {
	double** LU;
	LU = (double**)malloc(sizeof(double*) * (N + 1));
	for (int i = 0; i <= N; i++) LU[i] = (double*)malloc(sizeof(double) * (N + 1));
	double* y = (double*)malloc(sizeof(double) * (N + 1));
	//u(x)-lambda*int_{0}^{1} K(x,s)u(s)ds=f(x)
	//discreted：u(xi)-lambda*sum_{k=0}^{N} ck*K(xi,sk)uk=fi, i=0...N
	//Simpson numerical intergral
	//I=h/3(F0+4F1+2F2+4F3+..+4Fn-3+2Fn-2+4Fn-1+Fn)
	//here： c0=1,c1=4,c2=2,c3=4,...,cn-3=4,cn-2=2,cn-1=4,cn=1
	// =>
	//ui-lambda(c0*K(xi,s0)u0 + c1*K(xi,s1)u1 +...+ ci*K(xi,si)ui +...+ cN*K(xi,sN)uN )
	double h = (b - a) / (N * (1.0));
	int i, j;
	for (i = 0; i <= N; i++) x[i] = a + i * h;
	for (i = 0; i <= N; i++) s[i] = a + i * h;
	double c[N + 1];
	c[0] = h / 3; c[N] = h / 3;
	for (i = 1; i < N; i++) { if (i % 2 == 1) c[i] = (4.0) * (h / 3); else c[i] = (2.0) * (h / 3); }

	double coffi[N + 1][N + 1];
	double f[N + 1];
	for (i = 0; i <= N; i++) f[i] = f_(x[i]);

	int k;
	for (i = 0; i <= N; i++) {
		for (k = 0; k <= N; k++) {
			if (k == i) coffi[i][k] = 1 - lambda * c[k] * K(x[i], s[k]);
			if (k != i) coffi[i][k] = (-lambda) * c[k] * K(x[i], s[k]);
		}
	}

	printf("h=%f\n", h);
	printf("coffi\n");
	for (i = 0; i <= N; i++) {
		for (j = 0; j <= N; j++)
			printf("%f ", coffi[i][j]);
		printf("\n");
	}
	printf("\n");
	//CLAY by LU decompositon
	for (j = 0; j <= N - 1; j++) {
		for (i = j + 1; i <= N; i++) {
			LU[i][j] = coffi[i][j] / coffi[j][j];
			for (k = j; k <= N; k++)
				coffi[i][k] -= LU[i][j] * coffi[j][k];
		}
	}
	for (i = 0; i <= N; i++)
		for (j = i; j <= N; j++)
			LU[i][j] = coffi[i][j];

	//solve
	for (i = 0; i <= N; i++) {
		double tmp = 0;
		for (j = 0; j < i; j++)
			tmp += LU[i][j] * y[j];
		y[i] = f[i] - tmp;
	}
	for (i = N; i >= 0; i--) {
		double tmp = 0;
		for (j = i + 1; j <= N; j++)
			tmp += LU[i][j] * u[j];
		u[i] = (y[i] - tmp) / LU[i][i];
	}

	printf("print LU\n");
	for (int i = 0; i <= N; i++) {
		for (int j = 0; j <= N; j++)
			printf("%f ", LU[i][j]);
		printf("\n");
	}

	for (int i = 0; i <= N; i++) free(LU[i]); free(LU); free(y); free(s);

	for (int i = 0; i <= N; i++)
		printf("y[%d]=%f\n", i, y[i]);
	for (int i = 0; i <= N; i++)
		printf("u[%d]=%f\n", i, u[i]);
}

void interpolation() {

	//------------cube spline interpolation------------//
	int n = N;
	double coffi[N + 1][4];//0-a 1-b 2-c 3-d
	coffi[0][2] = 0;//c[0]=0 in spline
	coffi[n][2] = 0;//c[n]=0 in spline

	double p[N];//catching method - p 
	double q[N];//catching method - q
	double f[N];//catching method - f
	for (int i = 1; i < N; i++) f[i] = (6.0 / (h * h)) * (u[i - 1] - 2 * u[i] + u[i + 1]);
	//in catching method: a0=0,cn=0,a2=...=an-1=1, b1=...=bn-1=-4, c1=...=cn-2=1
	//direct path
	p[1] = -1.0 / 4;
	for (int i = 2; i <= n - 1; i++) p[i] = 1.0 / (-4 - p[i - 1]);
	q[1] = -f[1] / (-4.0);
	for (int i = 1; i <= n - 1; i++) q[i] = (q[i - 1] - f[i]) / (-4 - p[i - 1]);
	coffi[n - 1][2] = (q[n - 2] - f[n - 1]) / (-4 - p[n - 2]);//c[n-1]
	//inverse path
	for (int i = n - 2; i >= 1; i--) coffi[i][2] = p[i] * coffi[i + 1][2] + q[i];//c[n-2...1]
	//other coffi
	for (int i = 1; i <= n; i++) coffi[i][3] = (coffi[i][2] - coffi[i - 1][2]) / h;//d[1...n]
	for (int i = 1; i <= n; i++) coffi[i][1] = (1.0 / 2) * h * coffi[i][2] - (1.0 / 6) * h * h * coffi[i][3] + (u[i] - u[i - 1]) / h;//b[1...n]
	for (int i = 1; i <= n; i++) coffi[i][0] = u[i];//a[1...n]
	printf("coffi\n");
	for (int i = 1; i <= n; i++) printf("%d %f %f %f %f\n", i, coffi[i][0], coffi[i][1], coffi[i][2], coffi[i][3]);
	printf("\n");

	//-----------GRAPH-----------//
	//print points of function created by cube spline interpolation 
	//S_i(x)=ai+bi(x-xi)+ci/2(x-xi)^2+di/6(x-xi)^3
	int cycle = 1;
	int num = 1;
	int segment = (800 - 100) / N + 1;
	for (int i = 100; i <= 800; i++) {
		if (cycle == segment) { num++; cycle = 1; }
		if (i == 800) { num--; }
		double valuex = a +( b - a) * (i - 100) / 700.0;
		//S_i(x)=ai+bi(x-xi)+ci/2(x-xi)^2+di/6(x-xi)^3
		double valuey = coffi[num][0] + coffi[num][1] * (valuex - x[num])
			+ coffi[num][2] / 2 * (valuex - x[num]) * (valuex - x[num])
			+ coffi[num][3] / 6 * (valuex - x[num]) * (valuex - x[num]) * (valuex - x[num]);
		double pixelx = 100 + 700 * valuex;
		double pixely = -200 * valuey + 500;
		cycle++;
		//printf("%d %d %f %f %f %f\n",i,num,valuex,valuey,pixelx,pixely);
		putpixel(pixelx, pixely, LIGHTBLUE);
	}
}

void approximation() {
	//-----------cube spline fitting---------------//
	int n = N;
	double coffi_fit1_y[N - 2][4] = { 0 };
	double coffi_fit_x[N - 2][4] = { 0 };
	double coffi_fit_x_fir_end[2][4] = { 0 };//the first and end polynomial - x
	double coffi_fit1_y_fir_end[2][4] = { 0 };//the first and end polynomial - y
	//P=wo+w1t+w2t^2+w3t^3
	//P=(y(t),x(t))^T,w0=(a0,b0)^T,w1=(a1,b1)^T,w2=(a2,b2)^T,w3=(a3,b3)^T,t\in[0,1]
	//0-w0,1-w1,2-w2,3-w3
	//PP1=2P0-P1 PP2=2Pn-Pn-1

		//fit1 - start
	coffi_fit1_y_fir_end[0][0] = (1.0 / 6) * ((2 * u[0] - u[1]) + 4 * u[0] + u[1]);//1/6(PP1-4P0+P1)
	coffi_fit1_y_fir_end[0][1] = (-1.0 / 2) * ((2 * u[0] - u[1]) - u[1]);//-1/2(PP1-P1)
	coffi_fit1_y_fir_end[0][2] = (1.0 / 2) * ((2 * u[0] - u[1]) - 2 * u[0] + u[1]);//1/2(PP1-2P0+P1)
	coffi_fit1_y_fir_end[0][3] = (-1.0 / 6) * ((2 * u[0] - u[1]) - 3 * u[0] + 3 * u[1] - u[2]);//-1/6(PP1-3P0+3P1-P2)
	//fit1 - end
	coffi_fit1_y_fir_end[1][0] = (1.0 / 6) * (u[n - 2] + 4 * u[n - 1] + u[n]);
	coffi_fit1_y_fir_end[1][1] = (-1.0 / 2) * (u[n - 2] - u[n]);
	coffi_fit1_y_fir_end[1][2] = (1.0 / 2) * (u[n - 2] - 2 * u[n - 1] + u[n]);
	coffi_fit1_y_fir_end[1][3] = (-1.0 / 6) * (u[n - 2] - 3 * u[n - 1] + 3 * u[n] - (2 * u[n] - u[n - 1]));
	//x - start
	coffi_fit_x_fir_end[0][0] = (1.0 / 6) * ((2 * x[0] - x[1]) + 4 * x[0] + x[1]);
	coffi_fit_x_fir_end[0][1] = (-1.0 / 2) * ((2 * x[0] - x[1]) - x[1]);
	coffi_fit_x_fir_end[0][2] = (1.0 / 2) * ((2 * x[0] - x[1]) - 2 * x[0] + x[1]);
	coffi_fit_x_fir_end[0][3] = (-1.0 / 6) * ((2 * x[0] - x[1]) - 3 * x[0] + 3 * x[1] - x[2]);
	//x - end
	coffi_fit_x_fir_end[1][0] = (1.0 / 6) * (x[n - 2] + 4 * x[n - 1] + x[n]);
	coffi_fit_x_fir_end[1][1] = (-1.0 / 2) * (x[n - 2] - x[n]);
	coffi_fit_x_fir_end[1][2] = (1.0 / 2) * (x[n - 2] - 2 * x[n - 1] + x[n]);
	coffi_fit_x_fir_end[1][3] = (-1.0 / 6) * (x[n - 2] - 3 * x[n - 1] + 3 * x[n] - (2 * x[n] - x[n - 1]));
	for (int i = 0; i <= N - 3; i++) {
		coffi_fit1_y[i][0] = (1.0 / 6) * (u[i] + 4 * u[i + 1] + u[i + 2]);
		coffi_fit1_y[i][1] = (-1.0 / 2) * (u[i] - u[i + 2]);
		coffi_fit1_y[i][2] = (1.0 / 2) * (u[i] - 2 * u[i + 1] + u[i + 2]);
		coffi_fit1_y[i][3] = (-1.0 / 6) * (u[i] - 3 * u[i + 1] + 3 * u[i + 2] - u[i + 3]);
		coffi_fit_x[i][0] = (1.0 / 6) * (x[i] + 4 * x[i + 1] + x[i + 2]);
		coffi_fit_x[i][1] = (-1.0 / 2) * (x[i] - x[i + 2]);
		coffi_fit_x[i][2] = (1.0 / 2) * (x[i] - 2 * x[i + 1] + x[i + 2]);
		coffi_fit_x[i][3] = (-1.0 / 6) * (x[i] - 3 * x[i + 1] + 3 * x[i + 2] - x[i + 3]);
	}
	printf("coffi_fit1\n");
	for (int i = 0; i <= N - 3; i++)
		printf("%d %f %f %f %f  %f %f %f %f\n",
			i, coffi_fit1_y[i][0], coffi_fit1_y[i][1], coffi_fit1_y[i][2], coffi_fit1_y[i][3],
			coffi_fit_x[i][0], coffi_fit_x[i][1], coffi_fit_x[i][2], coffi_fit_x[i][3]);
	printf("\n");


	printf("coffi_fit_x_fir_end\n");
	for (int i = 0; i <= 1; i++)
		printf("%d %f %f %f %f\n", i, coffi_fit_x_fir_end[i][0], coffi_fit_x_fir_end[i][1], coffi_fit_x_fir_end[i][2], coffi_fit_x_fir_end[i][3]);
	printf("\n");

	//----------GRAPH----------//
	//print points of function created by cube spline interpolation fitting - shooting method - 3
	//first draw the first and end graph
	for (int i = 0; i <= 1; i++)
		for (float j = 0; j <= 1; j += 0.01) {
			//P=w0+w1t+w2t^2+w3t^3
			double valuex = coffi_fit_x_fir_end[i][0] + coffi_fit_x_fir_end[i][1] * j
				+ coffi_fit_x_fir_end[i][2] * j * j + coffi_fit_x_fir_end[i][3] * j * j * j;
			double valuey = coffi_fit1_y_fir_end[i][0] + coffi_fit1_y_fir_end[i][1] * j
				+ coffi_fit1_y_fir_end[i][2] * j * j + coffi_fit1_y_fir_end[i][3] * j * j * j;
			double pixelx = 100 + 700 * valuex;
			double pixely = -200 * valuey + 500;
			putpixel(pixelx, pixely, GREEN);
		}
	//then the rest parts
	for (int i = 0; i <= N - 3; i++) {
		for (float j = 0; j <= 1; j += 0.01) {
			//P=w0+w1t+w2t^2+w3t^3
			double valuex = coffi_fit_x[i][0] + coffi_fit_x[i][1] * j + coffi_fit_x[i][2] * j * j + coffi_fit_x[i][3] * j * j * j;
			double valuey = coffi_fit1_y[i][0] + coffi_fit1_y[i][1] * j + coffi_fit1_y[i][2] * j * j + coffi_fit1_y[i][3] * j * j * j;
			double pixelx = 100 + 700 * valuex;
			double pixely = -200 * valuey + 500;
			putpixel(pixelx, pixely, GREEN);
		}
	}
}

double transX(double RealX_1, double RealX_2, double PixelX_1, double PixelX_2, double valuex) {
	return (PixelX_2 - PixelX_1) / (RealX_2 - RealX_1) * valuex + 
		(RealX_2 * PixelX_1 - RealX_1 * PixelX_2) / (RealX_2 - RealX_1);
}

double transY(double RealY_1, double RealY_2, double PixelY_1, double PixelY_2, double valuey) {
	return (PixelY_2 - PixelY_1) / (RealY_2 - RealY_1) * valuey +
		(RealY_2 * PixelY_1 - RealY_1 * PixelY_2) / (RealY_2 - RealY_1);
}


int main() {
	CLAY(K_1, f_4);

	initgraph(900, 600);	// create graph area
	//x:100-800, y:100-500
	setbkcolor(WHITE);
	cleardevice();

	interpolation();
	approximation();

	setfillcolor(BLACK);

	for (int i = 0; i <= N; i++) {
		double valuex = a + i * h;
		double valuey = u[i];
		double pixelx = 100 + 700 * valuex;
		double pixely = -200 * valuey + 500;
		fillcircle(pixelx, pixely, 2);
		//settextcolor(BLACK);
		//outtextxy(pixelx, pixely - 10, ".");
	}
	
	setlinecolor(BLACK);
	line(50, 500, 850, 500);
	line(100, 50, 100, 600);
	//outtextxy(y,x,s);
	settextcolor(BLACK);
	TCHAR s = _T('0.0');
	outtextxy(100, 500, s);

	TCHAR S1[] = _T("1.0");
	outtextxy(100, 300, S1);
	TCHAR S2[] = _T("2.0");
	outtextxy(100, 100, S2);

	TCHAR S3[] = _T("0.5");
	outtextxy(450, 500, S3);
	TCHAR S4[] = _T("1.0");
	outtextxy(800, 500, S4);
	/*
	outtextxy(350, 50, "interpolation and fitting of shooting method");
	for (int j = 700; j <= 730; j++) putpixel(j, 200, BROWN);
	outtextxy(750, 190, "interpolation");
	for (int j = 700; j <= 730; j++) putpixel(j, 230, GREEN);
	outtextxy(750, 220, "fitting");

	
	*/
	TCHAR S7[] = _T("12.jpg");
	saveimage(S7);
	_getch();
	closegraph();

	free(x);  free(u);
	return 0;
}

