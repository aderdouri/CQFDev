V <- function(x) 
{
  ( 3*( exp(-x)+exp(-2*x)+exp(-3*x)+exp(-4*x)+exp(-5*x) )+100*exp(-5*x) -90 )
}

try(uniroot(V, c(0, 1)))

dV <- function(x) 
{
  -( 3*( -exp(-x) -2*exp(-2*x)-3*exp(-3*x)-4*exp(-4*x)-5*exp(-5*x) )-5*100*exp(-5*x) )/90
}
dV(0.05191071)

d2V <- function(x) 
{
  ( 3*( exp(-x) +4*exp(-2*x)+9*exp(-3*x)+16*exp(-4*x)+25*exp(-5*x) )+25*100*exp(-5*x) )/90
}
d2V(0.05191071)



n<-c(1:100)
n
x<-rnorm(100,3,0.5)
x
s<-cumsum(x)
s
plot(s/n,xlab="n",ylim=c(2,4),type="l")
s/n
