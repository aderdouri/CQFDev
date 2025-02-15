# Date: Saturday, March 18, 2015
# File name: Abderrazak_DERDOURI_Module.R
# Version: 1 
# Author: Abderrazak DERDOURI
# Course: CQF
# Description: Exam.pdf
#	


##
## Module 2 Exam
##

rm(list=ls())   # removes all objects in memory

R = matrix( 
  # the data elements 
  c(1 ,0.2 ,0.5, 0.3 ,0.2 ,1 ,0.7 ,0.4 ,0.5 ,0.7 ,1 ,0.9 ,0.3 ,0.4 ,0.9 ,1),
  nrow=4,              # number of rows 
  ncol=4,              # number of columns 
  byrow = TRUE)        # fill matrix by rows 

S = matrix( 
  # the data elements 
  c(0.07, 0, 0, 0, 0, 0.12, 0, 0, 0, 0, 0.18 ,0, 0, 0, 0, 0.26),
  nrow=4,              # number of rows 
  ncol=4,              # number of columns 
  byrow = TRUE)        # fill matrix by rows 

r=0.03
m=0.1

mu=matrix(
  # the data elements
  c(0.04, 0.08, 0.12, 0.15),
  nrow=4,              # number of rows 
  ncol=1,              # number of columns 
  byrow = TRUE)        # fill matrix by rows 

(Sigma = S%*%R%*%S)

(gamma=(m-r)/(t(mu-r)%*%(solve(Sigma))%*%(mu-r)) )

( w = ((m-r)*solve(Sigma)%*%(mu-r))/ (t(mu-r)%*%solve(Sigma)%*%(mu-r))[1] )


##
## Standard deviation
##
( sigma_p = sqrt(t(w)%*%Sigma%*%w) )


##
##Tangency portfolio
##

Id=matrix(
  c(1, 1, 1, 1),
  nrow=4,              # number of rows 
  ncol=1,              # number of columns 
  byrow = TRUE)        # fill matrix by rows

Id

(A = t(Id)%*%solve(Sigma)%*%Id)
(B = t(mu)%*%solve(Sigma)%*%Id)
(C = t(mu)%*%solve(Sigma)%*%mu)
(DELTA=A*C-B*B)

(wt=solve(Sigma)%*%(mu-r*Id)/drop(B-A*r))

( sigma_t = sqrt(t(wt)%*%Sigma%*%wt) )
(mu_t=r+sigma_t*sqrt(C-2*r*B+r*r*A))
(slope_CML=(mu_t-r)/sigma_t)

##
## VAR
##


(Factor=qnorm(0.99))
(VAR = t(wt)%*%mu + sqrt(t(wt)%*%Sigma%*%wt)*Factor)

(Factor=qt(0.99, 30))
(VAR = t(wt)%*%mu + sqrt(t(wt)%*%Sigma%*%wt)*Factor)

