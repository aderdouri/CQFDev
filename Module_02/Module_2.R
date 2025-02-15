#
# Date: Saturday, March 18, 2015
# File name: Abderrazak_DERDOURI_Module.R
# Version: 1 
# Author: Abderrazak DERDOURI
# Course: CQF
#
# Description: Exam.pdf
#  
#	

#
#1. Analysis of table tennis appeal
#

R = matrix( 
  c(1 ,0.8 ,0.5, 0.4 ,0.8 ,1 ,0.7 ,0.5 ,0.5 ,0.7 ,1 ,0.8 ,0.4 ,0.5 ,0.8 ,1), # the data elements 
  nrow=4,              # number of rows 
  ncol=4,              # number of columns 
  byrow = TRUE)        # fill matrix by rows 

R

S = matrix( 
  c(0.07, 0, 0, 0, 0, 0.12, 0, 0, 0, 0, 0.3 ,0, 0, 0, 0, 0.6), # the data elements 
  nrow=4,              # number of rows 
  ncol=4,              # number of columns 
  byrow = TRUE)        # fill matrix by rows 

(Sigma = S%*%R%*%S)

det(Sigma)
solve(Sigma)


##
## Module 2 Exam
##

rm(list=ls())   # removes all objects in memory

R = matrix( 
  c(1 ,0.2 ,0.5, 0.3 ,0.2 ,1 ,0.7 ,0.4 ,0.5 ,0.7 ,1 ,0.9 ,0.3 ,0.4 ,0.9 ,1), # the data elements 
  nrow=4,              # number of rows 
  ncol=4,              # number of columns 
  byrow = TRUE)        # fill matrix by rows 

R

S = matrix( 
  c(0.07, 0, 0, 0, 0, 0.12, 0, 0, 0, 0, 0.18 ,0, 0, 0, 0, 0.26), # the data elements 
  nrow=4,              # number of rows 
  ncol=4,              # number of columns 
  byrow = TRUE)        # fill matrix by rows 

S

(Sigma = S%*%R%*%S)

det(Sigma)
solve(Sigma)

r=0.03
mu=matrix(
  c(0.04, 0.08, 0.12, 0.15),
  nrow=4,              # number of rows 
  ncol=1,              # number of columns 
  byrow = TRUE)        # fill matrix by rows 

mu
m=0.1
gamma=(m-r)/(t(mu-r)%*%(solve(Sigma))%*%(mu-r))


( w = ((m-r)*solve(Sigma)%*%(mu-r))/ (t(mu-r)%*%solve(Sigma)%*%(mu-r))[1] )

##
## Standard deviation
##
( sigma_p = sqrt(t(w)%*%Sigma%*%w) )

Id=matrix(
  c(1, 1, 1, 1),
  nrow=4,              # number of rows 
  ncol=1,              # number of columns 
  byrow = TRUE)        # fill matrix by rows 


(A = t(Id)%*%Sigma_1%*%Id)
(B = t(mu)%*%Sigma_1%*%Id)
(C = t(mu)%*%Sigma_1%*%mu)

#
#tangency portfolio
#

(wt=Sigma_1%*%(mu-r*Id))

(wt=Sigma_1%*%(mu-r*Id)/drop(B-A*r))

( sigma_t = sqrt(t(wt)%*%Sigma%*%wt) )

(Factor=qnorm(0.99))

(VAR = t(wt)%*%mu + sqrt(t(wt)%*%Sigma%*%wt)*Factor)

(Factor=qnorm(0.99, 30))
(VAR = t(wt)%*%mu + sqrt(t(wt)%*%Sigma%*%wt)*Factor)

install.packages("evir")


library(fGarch)
library(rugarch)




rm(list=ls(all=TRUE)) 

library(fGarch) 
library(rugarch) 
library(evir)
data(bmw,package="evir") 

garch1 = garchFit(~arma(1,0)+garch(1,1),data=bmw,cond.dist="norm") 
options(digits=3) 
summary(garch1) 
options(digits=10) 




require("quantmod")
sp500 <- new.env()
getSymbols("^GSPC", env = sp500, src = "yahoo",
           from = as.Date("1988-01-02"), to = as.Date("2013-12-31"))

GSPC <- sp500$GSPC
GSPC1 <- get("GSPC", envir = sp500)
GSPC2 <- with(sp500, GSPC)
head(GSPC2)
dim(GSPC2)
