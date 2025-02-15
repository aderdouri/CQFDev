#
# Date: Sunday, Jun 17, 2015
# File name: Module_5_Exam.R
# Version: 1 
# Author: Abderrazak DERDOURI
# Subject: CQF Exam module 5
#
# Description: Q1 and Q2
#  
#
# Notes:
# Revision History:
#

# 
# This function resolve for SigmaV and V0
# d1=x[1], d2=x[2], x[3]=SigmaV, x[4]=V0
#

require(nleqslv)
NMfun<-function(x, E0, sigmaE, r, T, D) 
{
  y <- rep(NA, length(x))  
  y[1] <- E0-x[4]*pnorm(x[1])+D*exp(-r*T)*pnorm(x[2])
  y[2] <- sigmaE*E0-pnorm(x[1])*x[3]*x[4]
  y[3] <- x[1]-(1/(x[3]*sqrt(T)))*(log(x[4]/D)+(r+0.5*(x[3])^2)*T)
  y[4] <- x[2]-x[1]+x[3]*sqrt(T)
  return(y)
}

##
## Q1.(a)
##
sigmaE=0.6
E0=6
r=0.03
T=1
D=10

xstart <- c(0, 0, 0.05, 12)
NMfun(xstart, E0, sigmaE, r, T, D)
(nleqslv(xstart, NMfun, E0=E0, sigmaE=sigmaE, r=r, T=T, D=D))$x

##
## Q1.(b)
##
sigmaE=0.1
iter = 1;
sigmaV<- numeric(6)
V<- numeric(6)
while(sigmaE <= 0.6) 
{
  xstart <- c(0, 0, 0.05, 12)
  NMfun(xstart, E0, sigmaE, r, T, D)
  cat("sigmaE = ", sigmaE, "\n")
  print('(d1, d2, sigmaV, V0)');
  y=(nleqslv(xstart, NMfun, E0=E0, sigmaE=sigmaE, r=r, T=T, D=D))$x
  sigmaV[iter] = y[3]
  V[iter] = y[4]
  sigmaE <- sigmaE + 0.1;  
  iter <- iter + 1;
}
100*sigmaV
V
sigmaE <- c(0.1, 0.2, 0.3, 0.4, 0.5, 0.6)
plot(sigmaE, sigmaV, type="l", col="red")


(1-pnorm(1.9440731))

##
## Q1.(c)
##
h1 <- function(K, r, T, sigma_v, V0)
{
  (log(K/(V0*exp(r*T)))+ (0.5*sigma_v^2)*T)/(sigma_v*sqrt(T))
}

h2 <- function(K, r, T, sigma_v, V0)
{
  h1(K, r, T, sigma_v, V0)-sigma_v*sqrt(T)
}

PD <- function(K, r, T, sigma_v, V0)
{
  pnorm(h1(K, r, T, sigma_v, V0)) + exp(2*(r-sigma_v^2/2)*log(K/V0)*1/sigma_v^2)*pnorm(h2(K, r, T, sigma_v, V0))
}
100*PD(10, 0.03, 1, 0.233, 15.6838492)


h1(10, 0.03, 1, 0.233, 15.684)
h2(10, 0.03, 1, 0.233, 15.684)

h1(60, 0.05, 4, 0.2, 100)
h2(60, 0.05, 4, 0.2, 100)
pnorm(h1(60, 0.05, 4, 0.2, 100))
pnorm(h2(60, 0.05, 4, 0.2, 100))


##
## Q2
##

f <- function(alpha)
{
  integrand <- function(x)
  {
    x/(exp(x)-1)
  }
  0.4 - 1 + 4/alpha*( (1/alpha)*integrate(integrand, 0, alpha)$value + alpha/2 -1)
}

uniroot(f, c(-10000, 10000))$root


#
# N(d): risk neutral exercice probability
#
d2 <- function(S, E, r, sigma, t, T)
{
  return ( (log(S/E) +(r-sigma^2/2)*(T-t))/(sigma*sqrt(T-t)) )
}

d2(110, 120, 0.0, 0.2, 0, 0.5)
d2(110, 120, 0.0, 0.4, 0, 0.5)


pnorm(d2(110, 120, 0.0, 0.2, 0, 0.5))
pnorm(d2(110, 120, 0.0, 0.4, 0, 0.5))

C <- function (alpha, u1, u2)
{
  return (1/alpha*( log(1+ ((exp(alpha*u1)-1)*(exp(alpha*u2)-1))/(exp(alpha)-1)) ) )
}



##
## Q3
##

curve(f(0.0320792, x), from=1, to=70, add=FALSE, col="red", lwd=2, xlab="x", ylab="lamda*exp(-lamda*x)")
par(new=TRUE)
curve(f(0.0208705, x), from=1, to=70, add=TRUE, col="blue", lwd=2, xlab="x", ylab="lamda*exp(-lamda*x)")
par(new=TRUE)
curve(f(0.0257853, x), from=1, to=70, add=TRUE, col="black", lwd=2, xlab="x", ylab="lamda*exp(-lamda*x)")
par(new=TRUE)
curve(f(0.031825, x), from=1, to=70, add=TRUE, col="orange", lwd=2, xlab="x", ylab="lamda*exp(-lamda*x)")
par(new=TRUE)
curve(f(0.0387927, x), from=1, to=70, add=TRUE, col="yellow", lwd=2, xlab="x", ylab="lamda*exp(-lamda*x)")
par(new=TRUE)
curve(f(0.0301785, x), from=1, to=70, add=TRUE, col="gray", lwd=2, xlab="x", ylab="lamda*exp(-lamda*x)")
par(new=TRUE)
curve(f(0.0320792, x), from=1, to=70, add=TRUE, col="gray", lwd=2, xlab="x", ylab="lamda*exp(-lamda*x)")

legend( x="right", legend=c("lamda=0.0320792"
                            , "lamda=0.0208705"
                            ,"lamda=0.0257853"
                            , "lamda=0.031825"
                            , "lamda=0.0387927"
                            ,"lamda=0.0301785"
                            ,"lamda=0.0320792"),
        col=c("red","blue", "black","orange", "yellow", "gray"), lwd=1, lty=c(1,2), pch=c(15,17))


x<-seq(1:7)
P0.7<-c(0.983607, 0.950086, 0.910189, 0.863093, 0.808658, 0.768967, 0.728774)
P0.6<-c(0.987654, 0.962252, 0.931751, 0.895392, 0.852895, 0.821316, 0.788989)
P0.5<-c(0.990099, 0.969649, 0.944966, 0.915366, 0.880536, 0.85436, 0.827388)

plot(x, P0.5, type="l", col="black", lwd=2, xlab="year", ylab="Survival Probability")
par(new=TRUE)
plot(x, P0.6, type="l", col="red", lwd=2, xlab="year", ylab="Survival Probability")
par(new=TRUE)
plot(x, P0.7, type="l", col="blue", lwd=2, xlab="year", ylab="Survival Probability")

legend( x="right", legend=c("RR=0.5", "RR=0.6","RR=0.7")
        , col=c("black","red", "blue"), lwd=1, lty=c(1,2), pch=c(15,17))


