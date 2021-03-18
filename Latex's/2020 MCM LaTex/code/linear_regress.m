Y = hairdryerS2(:,[6]); % Extract observed value y
% Extract observed value x
x123456 = [hairdryerS2(:,[2:5]),hairdryerS2(:,[7:8])]; 
% Y = microwaveS1(:,[6]);
% x123456 = [microwaveS1(:,[2:5]),microwaveS1(:,[7:8])];
% Y = percifierS1(:,[6]);
%x123456 = [percifierS1(:,[2:5]),percifierS1(:,[7:8])];
Size = size(x123456)
% Construct data matrix of multiple linear regression analysis
X=[ones(Size(1),1),x123456] 
% Calculate regression coefficients and stats values
[beta,betarint,r,rint,st] = regress(Y,X) 
q = sum(r.^2) % Sum of squared residuals
ybar = mean(Y) % Average value of observed y and estimated value of y
yhat = X * beta
u = sum((yhat-ybar).^2) % sum of square
m = 6 % number of variables and samples
n = length(Y)
F = u/m/(q/(n-m-1)) % stats value F
% Quantiles,if fw1<F<fw2 then model is not allowed
fw1 = finv(0.025,m,n-m-1) 
fw2 = finv(0.975,m,n-m-1)
c = diag(inv(X'*X)) % Calculate c_jj and stats value t
t = beta./sqrt(c)/sqrt(q/(n-m-1))
% Quantiles,if t_i<tfw<t_j then t_0...t_i can be abandoned
tfw = tinv(0.975,n-m-1) 
rcoplot(r,rint)
title("Plot Of Residuals")
xlabel("Products")
ylabel("Residuals")