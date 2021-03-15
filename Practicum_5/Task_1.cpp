#include <iostream>
#include <conio.h>
#include <easyx.h>
#include <graphics.h>
#include <cmath>
#include <time.h>

using namespace std;
double f1(double x){
    return exp(x)+2;
}

double f2(double x){
    return -1/x;
}

double f3(double x){
    return -2*(x+1)/3;
}

double test1fun1(double x){
	return sin(x);
}

double test1fun2(double x){
	return cos(x);
}

double test2fun1(double x){
	return x;
}

double test2fun2(double x){
	return x*x;
}

double test3fun1(double x){
	return 1/x;
}

double test3fun2(double x){
	return x*x*x;
}

double root(double (*f)(double f_p), double (*g)(double g_p), double a, double b, double eps1, int count,int number){
	double c=(a+b)/2;
    if(c-a<eps1||b-c<eps1) {if(number==0) return c; else{cout<<number<<" root-number iteration: "<<count<<endl; return c;} }
    if((f(a)-g(a))*(f(c)-g(c))>0) return root(f,g,c,b,eps1,count+1,number);
    else if((f(a)-g(a))*(f(c)-g(c))<0) return root(f,g,a,c,eps1,count+1,number);
    else {if(number==0) return c; else{cout<<number<<" root-number iteration: "<<count<<endl; return c;} }
}

double integral(double (*f)(double f_p), double a, double b, double eps2, int number){
    int n=10,n_2=20,i=2,j=1,i_2n=1;
    double h_n=(b-a)/n,h_2n=h_n/2;
    double f0=f(a),fn=f(b);
    double SumEven=0,SumOdd=0,SumAdd=0,Interg_n=0,Interg_2n=0;
    while(i<n){
        SumEven+=f(a+i*h_n);
        i+=2;
    }
    while(j<n){
        SumOdd+=f(a+j*h_n);
        j+=2;
    }
    while(i_2n<n_2){
        SumAdd+=f(a+i_2n*h_2n);
        i_2n+=2;
    }
    Interg_n=h_n/3*(f0+fn+2*SumEven+4*SumOdd);
    double innerpoint=SumEven+SumOdd+SumAdd;
    Interg_2n=h_2n/3*(f0+fn+2*SumEven+2*SumOdd+4*SumAdd);

    while(1/15*fabs(Interg_n-Interg_2n)>eps2){
        Interg_n=Interg_2n;
        h_2n/=2;n_2*=2;SumAdd=0;i_2n=1;
        while(i_2n<n_2){
            SumAdd+=f(a+i_2n*h_2n);
            i_2n+=2;
        }
        Interg_2n=h_2n/3*(f0+fn+2*innerpoint+4*SumAdd);
        innerpoint+=SumAdd;
    }
	if(number!=0) cout<<number<<" integral-number of n: "<<n_2<<endl;

    return Interg_2n;
}

int main()
{
	clock_t start,finish;
	start=clock();
	double root1=root(f1,f3,-5.0,-3.0,0.0000166,1,1);
	finish=clock();
	double totaltime1=(double)(finish-start)/CLOCKS_PER_SEC;
	
	start=clock();
    double root2=root(f2,f3,-3.0,-1.0,0.0000166,1,2);
	finish=clock();
	double totaltime2=(double)(finish-start)/CLOCKS_PER_SEC;

    start=clock();
	double root3=root(f1,f2,-1.0,-0.2,0.0000166,1,3);
	finish=clock();
	double totaltime3=(double)(finish-start)/CLOCKS_PER_SEC;

	cout<<"root1RunTime ="<<totaltime1<<"s"<<endl;
	cout<<"root2RunTime ="<<totaltime2<<"s"<<endl;
	cout<<"root3RunTime ="<<totaltime3<<"s"<<endl;

	start=clock();
	double int1=integral(f1,root1,root3,0.0000166,1);
	finish=clock();
	totaltime1=(double)(finish-start)/CLOCKS_PER_SEC;

	start=clock();
	double int2=integral(f2,root2,root3,0.0000166,2);
	finish=clock();
	totaltime2=(double)(finish-start)/CLOCKS_PER_SEC;
	
	start=clock();
	double int3=integral(f3,root1,root2,0.0000166,3);
	finish=clock();
	totaltime3=(double)(finish-start)/CLOCKS_PER_SEC;

	cout<<"int1RunTime ="<<totaltime1<<"s"<<endl;
	cout<<"int2RunTime ="<<totaltime2<<"s"<<endl;
	cout<<"int3RunTime ="<<totaltime3<<"s"<<endl;
	cout<<endl;

	double Area=int1-int2-int3;

	cout<<"1-st root: "<<root1<<endl;
	cout<<"2-nd root: "<<root2<<endl;
	cout<<"3-rd root: "<<root3<<endl;
	cout<<"Area: "<<Area<<endl;
	cout<<endl;

	start=clock();
	double totaltime;
	double testroot1=root(test1fun1,test1fun2,0,1.5,0.0000166,1,0);
	finish=clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"testroot1RunTime ="<<totaltime<<"s"<<endl;

	start=clock();
	double testroot2=root(test2fun1,test2fun2,0,2,0.0000166,1,0);
	finish=clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"testroot2RunTime ="<<totaltime<<"s"<<endl;

	start=clock();
	double testroot3=root(test3fun1,test3fun2,0,2,0.0000166,1,0);
	finish=clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"testroot3RunTime ="<<totaltime<<"s"<<endl;

	start=clock();
	double integral1=integral(test1fun2,0,1,0.0000166,0);
	finish=clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"testintegral1RunTime ="<<totaltime<<"s"<<endl;

	start=clock();
	double integral2=integral(test2fun2,0,1,0.0000166,0);
	finish=clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"testintegral2RunTime ="<<totaltime<<"s"<<endl;

	start=clock();
	double integral3=integral(test3fun1,1,2,0.0000166,0);
	finish=clock();
	totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"testintegral3RunTime ="<<totaltime<<"s"<<endl;

	cout<<endl;
	cout<<"1-st testroot: "<<testroot1<<endl;
	cout<<"2-nd testroot: "<<testroot2<<endl;
	cout<<"3-rd testroot: "<<testroot3<<endl;
	cout<<"1-st testintegral: "<<integral1<<endl;
	cout<<"2-nd testintegral: "<<integral2<<endl;
	cout<<"3-rd testintegral: "<<integral3<<endl;
	cout<<endl;
	cout<<"Type anything to continue..."<<endl;
	_getch();

	initgraph(900,600);	// create graph area
	setbkcolor(WHITE);
	cleardevice();
	for(int i=100;i<=699;i++)
		for(int j=100;j<=500;j++){
			double pointx=0.01*i-7;
			double pointy=(-0.01)*j+5;
			if(pointy<f1(pointx) && pointy>f2(pointx) && pointy>f3(pointx)) putpixel(i,j,YELLOW);
		}
	setlinecolor(BLACK);
	line(50,500,850,500);
	setlinecolor(GREEN);
	double last=(-100)*f1(0.01*100-7)+500;
	putpixel(100,last,GREEN);
	for(i=101;i<=800;i++){
		double current=(-100)*f1(0.01*i-7)+500;
		putpixel(i,current,GREEN);
		line(i-1,last,i,current);
		last=current;
	}
	setlinecolor(BLUE);
	last=(-100)*f2(0.01*100-7)+500;
	putpixel(100,last,BLUE);
	for(i=101;i<=800;i++){
		double current=(-100)*f2(0.01*i-7)+500;
		putpixel(i,current,BLUE);
		line(i-1,last,i,current);
		last=current;
	}
	setlinecolor(BLACK);
	line(700,10,700,590);
	setlinecolor(RED);
	last=(-100)*f3(0.01*100-7)+500;
	putpixel(100,last,RED);
	for(i=101;i<=800;i++){
		double current=(-100)*f3(0.01*i-7)+500;
		putpixel(i,current,RED);
		line(i-1,last,i,current);
		last=current;
	}

	settextcolor(BLACK);
	outtextxy(100*root1+700,(-100)*f1(root1)+500-20,"root1: -4.02679");
	outtextxy(100*root2+700+20,(-100)*f2(root2)+500-5,"root2: -1.82281");
	outtextxy(100*root3+700+10,(-100)*f2(root3)+500,"root3: -0.371777");
	outtextxy(100*(-2.5)+700+10,350,"area: 3.56367");
	settextcolor(RED);
	outtextxy(100,140,"f3=-2(x+1)/3");
	settextcolor(GREEN);
	outtextxy(100,310,"f1=exp(x)+2");
	settextcolor(BLUE);
	outtextxy(100,460,"f2=-1/x");

	saveimage("graph.jpg");

	_getch();				
	closegraph();

	return 0;
}