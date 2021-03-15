#include <iostream>
#include <conio.h>
#include <easyx.h>
#include <graphics.h>
#include <cmath>
#include <time.h>
using namespace std;
#define N 10

double ifzn(double x[], double y[], double z[], double y0){
	int n=0;
	double h=1.0/N;
	y[0]=y0;
	z[0]=-1;
	while(n<N){
		z[n+1]=z[n]-h*sinh(x[n])*z[n]-h*x[n]*y[n]-h*x[n];
		y[n+1]=y[n]+h*z[n];
		n++;
	}
	return z[n]-1;
}

int main()
{
	double x[N+1]={0},y[N+1]={0},z[N+1]={0};
	double h=1.0/N; 
	double eps=0.0001;
	int n=1; 
	double lambda=-50;
	double lambda2=-50+10;
	y[0]=lambda;
	x[0]=0; z[0]=-1; 

	while(n<=N) {x[n]=n*h; n++;}//x0=0 < x1=0.01 <...< x99=0.99 < x100=1
	//compute first 2 values and define direction of growth
	double ifzn1=ifzn(x,y,z,lambda);
	double ifzn2=ifzn(x,y,z,lambda2);
	printf("ifzn1: %f\n",ifzn1);
	printf("ifzn2: %f\n",ifzn2);

	double left,right;
	int direction;
	if(ifzn1*ifzn2<0) {left=lambda;right=lambda+10;}
	else{
		if(ifzn1<ifzn2 && ifzn2<0) {direction=1; left=lambda2;}
		else if(ifzn1>ifzn2 && ifzn2>0) {direction=2; left=lambda2;}
		else if(ifzn2<ifzn1 && ifzn1<0) {direction=-1; right=lambda;}
		else if(ifzn1<ifzn2 && ifzn1>0) {direction=-2; right=lambda;}
		double f1=ifzn1,f2=ifzn2;
		printf("direction: %d\n",direction);
		//find left and right
		while((f1*f2)>0) {
			if(direction==1) {lambda+=10; f1=ifzn(x,y,z,lambda); right=lambda;}
			if(direction==2) {lambda+=10; f1=ifzn(x,y,z,lambda); right=lambda;}
			if(direction==-1) {lambda-=10; f2=ifzn(x,y,z,lambda); left=lambda;}
			if(direction==-1) {lambda-=10; f2=ifzn(x,y,z,lambda); left=lambda;}
		}
	}

	printf("left=%f, right=%f\n",left,right);
	printf("iteration lambda z[n]-1\n");
	//binary search
	int count=1;
	double mid;
	while(right-left>eps) {
		mid=(right+left)/2;
		if(ifzn(x,y,z,mid)*ifzn(x,y,z,left)>0) left=mid;
		else if(ifzn(x,y,z,mid)*ifzn(x,y,z,left)<0) right=mid;
		else {lambda=mid;break;}
		printf("%d %f %f\n",count,mid,ifzn(x,y,z,mid));
		count++;
	}
	lambda=mid;

	//calculate with this lambda 
	printf("y[0]: %f\n",y[0]);
	while(n<N){
		z[n+1]=z[n]-h*sinh(x[n])*z[n]-h*x[n]*y[n]-h*x[n];
		y[n+1]=y[n]+h*z[n];
		n++;
	}
	printf("y[0]: %f\n",y[0]);
	
	printf("shooting method yn\n");
	int j=0;
	for(j; j<=N; j++)
		printf("%f ",y[j]);
	printf("\n");
	double y_1_copy[101];
	for(j=0;j<=N;j++)
		y_1_copy[j]=y[j];

	printf("shooting method zn\n");
	j=0;
	for(j; j<=N; j++)
		printf("%f ",z[j]);
	printf("\n");
	printf("\n");

	//for(j=1;j<=100;j++) printf("%d %f %f\n",j,-10+0.1*j,ifzn(x,y,z,-10+0.1*j));


	//linear interpolation
	double linear_1=ifzn(x,y,z,-20.0);
	double linear_2=ifzn(x,y,z,-10.0);
	double lambda_linear=(10.0)*(linear_1-2*linear_2)/(linear_2-linear_1);

	printf("linear_1 linear_2: %f %f\n",linear_1,linear_2);
	printf("lambda_linear: %f\n",lambda_linear);
	n=0; y[0]=lambda;
	while(n<N){
		z[n+1]=z[n]-h*sinh(x[n])*z[n]-h*x[n]*y[n]-h*x[n];
		y[n+1]=y[n]+h*z[n];
		n++;
	}
	
	printf("linear method yn\n");
	j=0;
	for(j; j<=N; j++)
		printf("%f ",y[j]);
	printf("\n");
	printf("linear method zn\n");
	j=0;
	for(j; j<=N; j++)
		printf("%f ",z[j]);
	printf("\n");

	//cube spline interpolation - shooting method - 1
	n=N;
	double coffi[N+1][4];//0-a 1-b 2-c 3-d
	coffi[0][2]=0;//c[0]=0 in spline
	coffi[n][2]=0;//c[n]=0 in spline

	double p[N];//catching method - p 
	double q[N];//catching method - q
	double f[N];//catching method - f
	for(int i=1;i<N;i++) f[i]=(6.0/(h*h))*(y_1_copy[i-1]-2*y_1_copy[i]+y_1_copy[i+1]);
	//in catching method: a0=0,cn=0,a2=...=an-1=1, b1=...=bn-1=-4, c1=...=cn-2=1
	//direct path
	p[1]=-1.0/4;
	for(i=2;i<=n-1;i++) p[i]=1.0/(-4-p[i-1]);
	q[1]=-f[1]/(-4.0);
	for(i=1;i<=n-1;i++) q[i]=(q[i-1]-f[i])/(-4-p[i-1]);
	coffi[n-1][2]=(q[n-2]-f[n-1])/(-4-p[n-2]);//c[n-1]
	//inverse path
	for(i=n-2;i>=1;i--) coffi[i][2]=p[i]*coffi[i+1][2]+q[i];//c[n-2...1]
	//other coffi
	for(i=1;i<=n;i++) coffi[i][3]=(coffi[i][2]-coffi[i-1][2])/h;//d[1...n]
	for(i=1;i<=n;i++) coffi[i][1]=(1.0/2)*h*coffi[i][2]-(1.0/6)*h*h*coffi[i][3]+(y_1_copy[i]-y_1_copy[i-1])/h;//b[1...n]
	for(i=1;i<=n;i++) coffi[i][0]=y_1_copy[i];//a[1...n]
	printf("coffi\n");
	for(i=1;i<=n;i++) printf("%d %f %f %f %f\n",i,coffi[i][0],coffi[i][1],coffi[i][2],coffi[i][3]);
	printf("\n");


	//cube spline interpolation - linear interpolation - 2
	n=N;
	double coffi2[N+1][4];//0-a 1-b 2-c 3-d
	coffi2[0][2]=0;//c[0]=0 in spline
	coffi2[n][2]=0;//c[n]=0 in spline

	for(i=1;i<N;i++) f[i]=(6.0/(h*h))*(y[i-1]-2*y[i]+y[i+1]);
	//in catching method: a0=0,cn=0,a2=...=an-1=1, b1=...=bn-1=-4, c1=...=cn-2=1
	//direct path
	p[1]=-1.0/4;
	for(i=2;i<=n-1;i++) p[i]=1/(-4-p[i-1]);
	q[1]=-f[1]/(-4.0);
	for(i=1;i<=n-1;i++) q[i]=(q[i-1]-f[i])/(-4-p[i-1]);
	coffi2[n-1][2]=(q[n-2]-f[n-1])/(-4-p[n-2]);//c[n-1]
	//inverse path
	for(i=n-2;i>=1;i--) coffi2[i][2]=p[i]*coffi2[i+1][2]+q[i];//c[n-2...1]
	//other coffi
	for(i=1;i<=n;i++) coffi2[i][3]=(coffi2[i][2]-coffi2[i-1][2])/h;//d[1...n]
	for(i=1;i<=n;i++) coffi2[i][1]=1.0/2*h*coffi2[i][2]-1.0/6*h*h*coffi2[i][3]+(y[i]-y[i-1])/h;//b[1...n]
	for(i=1;i<=n;i++) coffi2[i][0]=y[i];//a[1...n]
	printf("coffi2\n");
	for(i=1;i<=n;i++) printf("%d %f %f %f %f\n",i,coffi2[i][0],coffi2[i][1],coffi2[i][2],coffi2[i][3]);
	printf("\n");

	//for(i=0;i<=N;i++) printf("x[%d] y_1_copy[%d] %f %f\n",i,i,x[i],y_1_copy[i]);

	//cube spline fitting - shooting method - 3
	n=N;
	double coffi_fit1_y[N-2][4]={0};
	double coffi_fit_x[N-2][4]={0};
	double coffi_fit_x_fir_end[2][4]={0};//the first and end polynomial - x
	double coffi_fit1_y_fir_end[2][4]={0};//the first and end polynomial - y
	//P=wo+w1t+w2t^2+w3t^3
	//P=(y(t),x(t))^T,w0=(a0,b0)^T,w1=(a1,b1)^T,w2=(a2,b2)^T,w3=(a3,b3)^T,t\in[0,1]
	//0-w0,1-w1,2-w2,3-w3
	//PP1=2P0-P1 PP2=2Pn-Pn-1
	
		//fit1 - start
		coffi_fit1_y_fir_end[0][0]=(1.0/6)*((2*y_1_copy[0]-y_1_copy[1])+4*y_1_copy[0]+y_1_copy[1]);//1/6(PP1-4P0+P1)
		coffi_fit1_y_fir_end[0][1]=(-1.0/2)*((2*y_1_copy[0]-y_1_copy[1])-y_1_copy[1]);//-1/2(PP1-P1)
		coffi_fit1_y_fir_end[0][2]=(1.0/2)*((2*y_1_copy[0]-y_1_copy[1])-2*y_1_copy[0]+y_1_copy[1]);//1/2(PP1-2P0+P1)
		coffi_fit1_y_fir_end[0][3]=(-1.0/6)*((2*y_1_copy[0]-y_1_copy[1])-3*y_1_copy[0]+3*y_1_copy[1]-y_1_copy[2]);//-1/6(PP1-3P0+3P1-P2)
		//fit1 - end
		coffi_fit1_y_fir_end[1][0]=(1.0/6)*(y_1_copy[n-2]+4*y_1_copy[n-1]+y_1_copy[n]); 
		coffi_fit1_y_fir_end[1][1]=(-1.0/2)*(y_1_copy[n-2]-y_1_copy[n]);
		coffi_fit1_y_fir_end[1][2]=(1.0/2)*(y_1_copy[n-2]-2*y_1_copy[n-1]+y_1_copy[n]);
		coffi_fit1_y_fir_end[1][3]=(-1.0/6)*(y_1_copy[n-2]-3*y_1_copy[n-1]+3*y_1_copy[n]-(2*y_1_copy[n]-y_1_copy[n-1]));
		//x - start
		coffi_fit_x_fir_end[0][0]=(1.0/6)*((2*x[0]-x[1])+4*x[0]+x[1]); 
		coffi_fit_x_fir_end[0][1]=(-1.0/2)*((2*x[0]-x[1])-x[1]);
		coffi_fit_x_fir_end[0][2]=(1.0/2)*((2*x[0]-x[1])-2*x[0]+x[1]);
		coffi_fit_x_fir_end[0][3]=(-1.0/6)*((2*x[0]-x[1])-3*x[0]+3*x[1]-x[2]);
		//x - end
		coffi_fit_x_fir_end[1][0]=(1.0/6)*(x[n-2]+4*x[n-1]+x[n]); 
		coffi_fit_x_fir_end[1][1]=(-1.0/2)*(x[n-2]-x[n]);
		coffi_fit_x_fir_end[1][2]=(1.0/2)*(x[n-2]-2*x[n-1]+x[n]);
		coffi_fit_x_fir_end[1][3]=(-1.0/6)*(x[n-2]-3*x[n-1]+3*x[n]-(2*x[n]-x[n-1]));
	for(i=0;i<=N-3;i++){
		coffi_fit1_y[i][0]=(1.0/6)*(y_1_copy[i]+4*y_1_copy[i+1]+y_1_copy[i+2]); 
		coffi_fit1_y[i][1]=(-1.0/2)*(y_1_copy[i]-y_1_copy[i+2]);
		coffi_fit1_y[i][2]=(1.0/2)*(y_1_copy[i]-2*y_1_copy[i+1]+y_1_copy[i+2]);
		coffi_fit1_y[i][3]=(-1.0/6)*(y_1_copy[i]-3*y_1_copy[i+1]+3*y_1_copy[i+2]-y_1_copy[i+3]);
		coffi_fit_x[i][0]=(1.0/6)*(x[i]+4*x[i+1]+x[i+2]); 
		coffi_fit_x[i][1]=(-1.0/2)*(x[i]-x[i+2]);
		coffi_fit_x[i][2]=(1.0/2)*(x[i]-2*x[i+1]+x[i+2]);
		coffi_fit_x[i][3]=(-1.0/6)*(x[i]-3*x[i+1]+3*x[i+2]-x[i+3]);
	}
	printf("coffi_fit1\n");
	for(i=0;i<=N-3;i++) 
		printf("%d %f %f %f %f  %f %f %f %f\n",
		i,coffi_fit1_y[i][0],coffi_fit1_y[i][1],coffi_fit1_y[i][2],coffi_fit1_y[i][3],
		coffi_fit_x[i][0],coffi_fit_x[i][1],coffi_fit_x[i][2],coffi_fit_x[i][3]);
	printf("\n");


	printf("coffi_fit_x_fir_end\n");
	for(i=0;i<=1;i++)
		printf("%d %f %f %f %f\n",i,coffi_fit_x_fir_end[i][0],coffi_fit_x_fir_end[i][1],coffi_fit_x_fir_end[i][2],coffi_fit_x_fir_end[i][3]);
	printf("\n");
/*
	for(i=0;i<=1;i++)
		for(float j=0;j<=1;j+=0.01){
			//P=w0+w1t+w2t^2+w3t^3
			double valuex=coffi_fit_x_fir_end[i][0]+coffi_fit_x_fir_end[i][1]*j
				+coffi_fit_x_fir_end[i][2]*j*j+coffi_fit_x_fir_end[i][3]*j*j*j;
			double valuey=coffi_fit1_y_fir_end[i][0]+coffi_fit1_y_fir_end[i][1]*j
				+coffi_fit1_y_fir_end[i][2]*j*j+coffi_fit1_y_fir_end[i][3]*j*j*j;
			printf("%f %f %f\n",j,valuex,valuey);
			//double pixelx=100+700*valuex;
			//double pixely=-800*valuey-3900;
			//putpixel(pixelx,pixely,GREEN);
		}
*/

	//cube spline fitting - linear interpolation - 4
	n=N;
	double coffi_fit2_y[N-2][4];
	double coffi_fit2_y_fir_end[2][4];//the first and end polynomial
	//P=wo+w1t+w2t^2+w3t^3
	//0-w0,1-w1,2-w2,3-w3

		//fit1 - start
		coffi_fit2_y_fir_end[0][0]=(1.0/6)*((2*y[0]-y[1])+4*y[0]+y[1]);//1/6(PP1-4P0+P1)
		coffi_fit2_y_fir_end[0][1]=(-1.0/2)*((2*y[0]-y[1])-y[1]);//-1/2(PP1-P1)
		coffi_fit2_y_fir_end[0][2]=(1.0/2)*((2*y[0]-y[1])-2*y[0]+y[1]);//1/2(PP1-2P0+P1)
		coffi_fit2_y_fir_end[0][3]=(-1.0/6)*((2*y[0]-y[1])-3*y[0]+3*y[1]-y[2]);//-1/6(PP1-3P0+3P1-P2)
		//fit1 - end
		coffi_fit2_y_fir_end[1][0]=(1.0/6)*(y[n-2]+4*y[n-1]+y[n]); 
		coffi_fit2_y_fir_end[1][1]=(-1.0/2)*(y[n-2]-y[n]);
		coffi_fit2_y_fir_end[1][2]=(1.0/2)*(y[n-2]-2*y[n-1]+y[n]);
		coffi_fit2_y_fir_end[1][3]=(-1.0/6)*(y[n-2]-3*y[n-1]+3*y[n]-(2*y[n]-y[n-1]));

	for(i=0;i<=N-3;i++){
		coffi_fit2_y[i][0]=(1.0/6)*(y[i]+4*y[i+1]+y[i+2]);
		coffi_fit2_y[i][1]=(-1.0/2)*(y[i]-y[i+2]);
		coffi_fit2_y[i][2]=(1.0/2)*(y[i]-2*y[i+1]+y[i+2]);
		coffi_fit2_y[i][3]=(-1.0/6)*(y[i]-3*y[i+1]+3*y[i+2]-y[i+3]);
	}
	printf("coffi_fit2\n");
	for(i=0;i<=N-3;i++) 
		printf("%d %f %f %f %f  %f %f %f %f\n",
		i,coffi_fit2_y[i][0],coffi_fit2_y[i][1],coffi_fit2_y[i][2],coffi_fit2_y[i][3],
		coffi_fit_x[i][0],coffi_fit_x[i][1],coffi_fit_x[i][2],coffi_fit_x[i][3]);
	printf("\n");
	printf("coffi_fit1_y_fir_end\n");
	for(i=0;i<=1;i++)
		printf("%d %f %f %f %f\n",i,coffi_fit1_y_fir_end[i][0],coffi_fit1_y_fir_end[i][1],coffi_fit1_y_fir_end[i][2],coffi_fit1_y_fir_end[i][3]);
	printf("coffi_fit2_y_fir_end\n");
	for(i=0;i<=1;i++)
		printf("%d %f %f %f %f\n",i,coffi_fit2_y_fir_end[i][0],coffi_fit2_y_fir_end[i][1],coffi_fit2_y_fir_end[i][2],coffi_fit2_y_fir_end[i][3]);
	printf("\n");
	printf("\n");

	cout<<"Type anything to continue..."<<endl;
	_getch();

	//-----------GRAPH 1------12-------//

	initgraph(900,600);	// create graph area
	//x:100-800, y:100-500
	setbkcolor(WHITE);
	cleardevice();

	//print points of function created by cube spline interpolation - shooting method - 1
	//S_i(x)=ai+bi(x-xi)+ci/2(x-xi)^2+di/6(x-xi)^3
	int cycle=1;
	int num=1;
	int segment=(800-100)/N+1;
	for(i=100;i<=800;i++){
		if(cycle==segment) {num++;cycle=1;}
		if(i==800) {num--;}
		double valuex=(i-100)/700.0;
		//S_i(x)=ai+bi(x-xi)+ci/2(x-xi)^2+di/6(x-xi)^3
		double valuey=coffi[num][0]+coffi[num][1]*(valuex-x[num])
			+coffi[num][2]/2*(valuex-x[num])*(valuex-x[num])
			+coffi[num][3]/6*(valuex-x[num])*(valuex-x[num])*(valuex-x[num]);
		double pixelx=100+700*valuex;
		double pixely=-800*valuey-3900;
		cycle++;
		//printf("%d %d %f %f %f %f\n",i,num,valuex,valuey,pixelx,pixely);
		putpixel(pixelx,pixely,BROWN);
	}

	//print points of function created by cube spline interpolation - linear interpolation - 2
	cycle=1;
	num=1;
	for(i=100;i<=800;i++){
		if(cycle==segment) {num++;cycle=1;}
		if(i==800) {num--;}
		double valuex=(i-100)/700.0;
		//S_i(x)=ai+bi(x-xi)+ci/2(x-xi)^2+di/6(x-xi)^3
		double valuey=coffi2[num][0]+coffi2[num][1]*(valuex-x[num])
			+coffi2[num][2]/2*(valuex-x[num])*(valuex-x[num])
			+coffi2[num][3]/6*(valuex-x[num])*(valuex-x[num])*(valuex-x[num]);
		double pixelx=100+700*valuex;
		double pixely=-800*valuey-3900;
		cycle++;
		//printf("%d %d %f %f %f %f\n",i,num,valuex,valuey,pixelx,pixely);
		putpixel(pixelx,pixely,GREEN);
	}

	for(i=0;i<=N;i++){
		double valuex=i*h;
		double valuey=y_1_copy[i];
		double pixelx=100+700*valuex;
		double pixely=-800*valuey-3900;
		//putpixel(pixelx,pixely,BLUE);
		settextcolor(BLACK);
		outtextxy(pixelx,pixely-10,".");
	}
	for(i=0;i<=N;i++){
		double valuex=i*h;
		double valuey=y[i];
		double pixelx=100+700*valuex;
		double pixely=-800*valuey-3900;
		//putpixel(pixelx,pixely,MAGENTA);
		settextcolor(BLACK);
		outtextxy(pixelx,pixely-10,".");
	}

	setlinecolor(BLACK);
	line(50,100,850,100);
	line(100,50,100,500);

	settextcolor(BLACK);
	outtextxy(100,100,"0");
	outtextxy(275,100,"0.25");
	outtextxy(450,100,"0.5");
	outtextxy(625,100,"0.75");
	outtextxy(800,100,"-5");
	outtextxy(100,200,"-5.125");
	outtextxy(100,300,"-5.25");
	outtextxy(100,400,"-5.375");
	outtextxy(100,500,"-5.5");

	outtextxy(350,50,"cube spline interpolation for 2 methods");
	for(j=700;j<=730;j++) putpixel(j,200,BROWN);
	outtextxy(750,190,"shooting method");
	for(j=700;j<=730;j++) putpixel(j,230,GREEN);
	outtextxy(750,220,"linear interpolation");

	saveimage("graph1.jpg");

	_getch();				
	closegraph();

	//-----------GRAPH 2----13---------//

	initgraph(900,600);	// create graph area
	//x:100-800, y:100-500
	setbkcolor(WHITE);
	cleardevice();
	
	//print points of function created by cube spline interpolation - shooting method - 1
	//S_i(x)=ai+bi(x-xi)+ci/2(x-xi)^2+di/6(x-xi)^3
	cycle=1;
	num=1;
	for(i=100;i<=800;i++){
		if(cycle==segment) {num++;cycle=1;}
		if(i==800) {num--;}
		double valuex=(i-100)/700.0;
		//S_i(x)=ai+bi(x-xi)+ci/2(x-xi)^2+di/6(x-xi)^3
		double valuey=coffi[num][0]+coffi[num][1]*(valuex-x[num])
			+coffi[num][2]/2*(valuex-x[num])*(valuex-x[num])
			+coffi[num][3]/6*(valuex-x[num])*(valuex-x[num])*(valuex-x[num]);
		double pixelx=100+700*valuex;
		double pixely=-800*valuey-3900;
		cycle++;
		putpixel(pixelx,pixely,BROWN);
	}

	//print points of function created by cube spline interpolation fitting - shooting method - 3
	//first draw the first and end graph
	for(i=0;i<=1;i++)
		for(float j=0;j<=1;j+=0.01){
			//P=w0+w1t+w2t^2+w3t^3
			double valuex=coffi_fit_x_fir_end[i][0]+coffi_fit_x_fir_end[i][1]*j
				+coffi_fit_x_fir_end[i][2]*j*j+coffi_fit_x_fir_end[i][3]*j*j*j;
			double valuey=coffi_fit1_y_fir_end[i][0]+coffi_fit1_y_fir_end[i][1]*j
				+coffi_fit1_y_fir_end[i][2]*j*j+coffi_fit1_y_fir_end[i][3]*j*j*j;
			double pixelx=100+700*valuex;
			double pixely=-800*valuey-3900;
			putpixel(pixelx,pixely,GREEN);
		}
	//then the rest parts
	for(i=0;i<=N-3;i++){
		for(float j=0;j<=1;j+=0.01){
			//P=w0+w1t+w2t^2+w3t^3
			double valuex=coffi_fit_x[i][0]+coffi_fit_x[i][1]*j+coffi_fit_x[i][2]*j*j+coffi_fit_x[i][3]*j*j*j;
			double valuey=coffi_fit1_y[i][0]+coffi_fit1_y[i][1]*j+coffi_fit1_y[i][2]*j*j+coffi_fit1_y[i][3]*j*j*j;
			double pixelx=100+700*valuex;
			double pixely=-800*valuey-3900;
			putpixel(pixelx,pixely,GREEN);
		}
	}

	for(i=0;i<=N;i++){
		double valuex=i*h;
		double valuey=y_1_copy[i];
		double pixelx=100+700*valuex;
		double pixely=-800*valuey-3900;
		//putpixel(pixelx,pixely,BLUE);
		settextcolor(BLACK);
		outtextxy(pixelx,pixely-10,".");
	}

	setlinecolor(BLACK);
	line(50,100,850,100);
	line(100,50,100,500);

	settextcolor(BLACK);
	outtextxy(100,100,"0");
	outtextxy(275,100,"0.25");
	outtextxy(450,100,"0.5");
	outtextxy(625,100,"0.75");
	outtextxy(800,100,"1");
	outtextxy(800,100,"-5");
	outtextxy(100,200,"-5.125");
	outtextxy(100,300,"-5.25");
	outtextxy(100,400,"-5.375");
	outtextxy(100,500,"-5.5");

	outtextxy(350,50,"interpolation and fitting of shooting method");
	for(j=700;j<=730;j++) putpixel(j,200,BROWN);
	outtextxy(750,190,"interpolation");
	for(j=700;j<=730;j++) putpixel(j,230,GREEN);
	outtextxy(750,220,"fitting");

	saveimage("graph2.jpg");

	_getch();				
	closegraph();

	//-----------GRAPH 3----24---------//

	initgraph(900,600);	// create graph area
	//x:100-800, y:100-500
	setbkcolor(WHITE);
	cleardevice();

	//print points of function created by cube spline interpolation - linear interpolation - 2 
	cycle=1;
	num=1;
	for(i=100;i<=800;i++){
		if(cycle==segment) {num++;cycle=1;}
		if(i==800) {num--;}
		double valuex=(i-100)/700.0;
		//S_i(x)=ai+bi(x-xi)+ci/2(x-xi)^2+di/6(x-xi)^3
		double valuey=coffi2[num][0]+coffi2[num][1]*(valuex-x[num])
			+coffi2[num][2]/2*(valuex-x[num])*(valuex-x[num])
			+coffi2[num][3]/6*(valuex-x[num])*(valuex-x[num])*(valuex-x[num]);
		double pixelx=100+700*valuex;
		double pixely=-800*valuey-3900;
		cycle++;
		putpixel(pixelx,pixely,BROWN);
	}

	//print points of function created by cube spline fitting - linear interpolation - 4
	//first draw the first and end graph
	for(i=0;i<=1;i++)
		for(float j=0;j<=1;j+=0.01){
			//P=w0+w1t+w2t^2+w3t^3
			double valuex=coffi_fit_x_fir_end[i][0]+coffi_fit_x_fir_end[i][1]*j
				+coffi_fit_x_fir_end[i][2]*j*j+coffi_fit_x_fir_end[i][3]*j*j*j;
			double valuey=coffi_fit2_y_fir_end[i][0]+coffi_fit2_y_fir_end[i][1]*j
				+coffi_fit2_y_fir_end[i][2]*j*j+coffi_fit2_y_fir_end[i][3]*j*j*j;
			double pixelx=100+700*valuex;
			double pixely=-800*valuey-3900;
			putpixel(pixelx,pixely,GREEN);
		}
	//then the rest parts
	for(i=0;i<=N-3;i++){
		for(float j=0;j<=1;j+=0.01){
			//P=w0+w1t+w2t^2+w3t^3
			double valuex=coffi_fit_x[i][0]+coffi_fit_x[i][1]*j+coffi_fit_x[i][2]*j*j+coffi_fit_x[i][3]*j*j*j;
			double valuey=coffi_fit2_y[i][0]+coffi_fit2_y[i][1]*j+coffi_fit2_y[i][2]*j*j+coffi_fit2_y[i][3]*j*j*j;
			double pixelx=100+700*valuex;
			double pixely=-800*valuey-3900;
			putpixel(pixelx,pixely,GREEN);
		}
	}

	for(i=0;i<=N;i++){
		double valuex=i*h;
		double valuey=y[i];
		double pixelx=100+700*valuex;
		double pixely=-800*valuey-3900;
		//putpixel(pixelx,pixely,MAGENTA);
		settextcolor(BLACK);
		outtextxy(pixelx,pixely-10,".");
	}

	setlinecolor(BLACK);
	line(50,100,850,100);
	line(100,50,100,500);

	settextcolor(BLACK);
	outtextxy(100,100,"0");
	outtextxy(275,100,"0.25");
	outtextxy(450,100,"0.5");
	outtextxy(625,100,"0.75");
	outtextxy(800,100,"1");
	outtextxy(800,100,"-5");
	outtextxy(100,200,"-5.125");
	outtextxy(100,300,"-5.25");
	outtextxy(100,400,"-5.375");
	outtextxy(100,500,"-5.5");

	outtextxy(350,50,"interpolation and fitting of linear interpolation");
	for(j=700;j<=730;j++) putpixel(j,200,BROWN);
	outtextxy(750,190,"interpolation");
	for(j=700;j<=730;j++) putpixel(j,230,GREEN);
	outtextxy(750,220,"fitting");

	saveimage("graph3.jpg");

	_getch();				
	closegraph();

	//-----------GRAPH 4----34---------//

	initgraph(900,600);	// create graph area
	//x:100-800, y:100-500
	setbkcolor(WHITE);
	cleardevice();

	//print points of function created by cube spline interpolation fitting - shooting method - 3
	//first draw the first and end graph
	for(i=0;i<=1;i++)
		for(float j=0;j<=1;j+=0.01){
			//P=w0+w1t+w2t^2+w3t^3
			double valuex=coffi_fit_x_fir_end[i][0]+coffi_fit_x_fir_end[i][1]*j
				+coffi_fit_x_fir_end[i][2]*j*j+coffi_fit_x_fir_end[i][3]*j*j*j;
			double valuey=coffi_fit1_y_fir_end[i][0]+coffi_fit1_y_fir_end[i][1]*j
				+coffi_fit1_y_fir_end[i][2]*j*j+coffi_fit1_y_fir_end[i][3]*j*j*j;
			double pixelx=100+700*valuex;
			double pixely=-800*valuey-3900;
			putpixel(pixelx,pixely,BROWN);
		}
	//then the rest parts
	for(i=0;i<=N-3;i++){
		for(float j=0;j<=1;j+=0.01){
			//P=w0+w1t+w2t^2+w3t^3
			double valuex=coffi_fit_x[i][0]+coffi_fit_x[i][1]*j+coffi_fit_x[i][2]*j*j+coffi_fit_x[i][3]*j*j*j;
			double valuey=coffi_fit1_y[i][0]+coffi_fit1_y[i][1]*j+coffi_fit1_y[i][2]*j*j+coffi_fit1_y[i][3]*j*j*j;
			double pixelx=100+700*valuex;
			double pixely=-800*valuey-3900;
			putpixel(pixelx,pixely,BROWN);
		}
	}
/*
	//print points of function created by cube spline fitting - linear interpolation - 4
	//first draw the first and end graph
	for(i=0;i<=1;i++)
		for(float j=0;j<=1;j+=0.01){
			//P=w0+w1t+w2t^2+w3t^3
			double valuex=coffi_fit_x_fir_end[i][0]+coffi_fit_x_fir_end[i][1]*j
				+coffi_fit_x_fir_end[i][2]*j*j+coffi_fit_x_fir_end[i][3]*j*j*j;
			double valuey=coffi_fit2_y_fir_end[i][0]+coffi_fit2_y_fir_end[i][1]*j
				+coffi_fit2_y_fir_end[i][2]*j*j+coffi_fit2_y_fir_end[i][3]*j*j*j;
			double pixelx=100+700*valuex;
			double pixely=-800*valuey-3900;
			putpixel(pixelx,pixely,GREEN);
		}
	//then the rest parts
	for(i=0;i<=N-3;i++){
		for(float j=0;j<=1;j+=0.01){
			//P=w0+w1t+w2t^2+w3t^3
			double valuex=coffi_fit_x[i][0]+coffi_fit_x[i][1]*j+coffi_fit_x[i][2]*j*j+coffi_fit_x[i][3]*j*j*j;
			double valuey=coffi_fit2_y[i][0]+coffi_fit2_y[i][1]*j+coffi_fit2_y[i][2]*j*j+coffi_fit2_y[i][3]*j*j*j;
			double pixelx=100+700*valuex;
			double pixely=-800*valuey-3900;
			putpixel(pixelx,pixely,GREEN);
		}
	}
*/

	for(i=0;i<=N;i++){
		double valuex=i*h;
		double valuey=y_1_copy[i];
		double pixelx=100+700*valuex;
		double pixely=-800*valuey-3900;
		//putpixel(pixelx,pixely,BLUE);
		settextcolor(BLACK);
		outtextxy(pixelx,pixely-10,".");
	}
	for(i=0;i<=N;i++){
		double valuex=i*h;
		double valuey=y[i];
		double pixelx=100+700*valuex;
		double pixely=-800*valuey-3900;
		//putpixel(pixelx,pixely,MAGENTA);
		settextcolor(BLACK);
		outtextxy(pixelx,pixely-10,".");
	}

	setlinecolor(BLACK);
	line(50,100,850,100);
	line(100,50,100,500);

	settextcolor(BLACK);
	outtextxy(100,100,"0");
	outtextxy(275,100,"0.25");
	outtextxy(450,100,"0.5");
	outtextxy(625,100,"0.75");
	outtextxy(800,100,"1");
	outtextxy(800,100,"-5");
	outtextxy(100,200,"-5.125");
	outtextxy(100,300,"-5.25");
	outtextxy(100,400,"-5.375");
	outtextxy(100,500,"-5.5");

	outtextxy(350,50,"cube spline fitting for 2 methods");
	for(j=700;j<=730;j++) putpixel(j,200,BROWN);
	outtextxy(750,190,"shooting method");
	for(j=700;j<=730;j++) putpixel(j,230,GREEN);
	outtextxy(750,220,"linear interpolation");

	saveimage("graph4.jpg");

	_getch();				
	closegraph();

	return 0;
}