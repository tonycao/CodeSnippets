function [A,Y,numIter,tElapsed,finalResidual]=kernelnmfdecom(X,k,option)
% Kernel semi-NMF based on NNLS: phi(X)=A_phiY, s.t. Y>0. 
% Definition:
%     [Ak,A,Y,numIter,tElapsed,finalResidual]=kernelnmfrule(X,k)
%     [Ak,A,Y,numIter,tElapsed,finalResidual]=kernelnmfrule(X,k,option)
% X: matrix of mixed signs, dataset to factorize, each column is a sample, and each row is a feature.
% k: scalar, number of clusters.
% option: struct:
% option.kernel: string, kernel function. It could be
%     'linear': linear kernel, linear(x,y)=x'*y;
%     'polynomial': polynomial kernel, polynomial(x,y)=(Gamma.*(x'*y)+ Coefficient).^Degree;
%     'rbf': rdial basis function kernel (default), rbf(x,y)=exp((-(1/sigma^2)).*(|x-y|.^2);
%     'sigmoid': sigmoid kernel, sigmoid(x,y)=tanh(alpha*(x'*y) + beta).
%     yourKernelFunctionName: you can define and use you own kernel function 
% option.param: parameters of specified kernel:
%      if option.kernel='linear': option.param=[];
%      if option.kernel='polynomial': option.param is [Gamma;Coefficient;Degree], the default is [1;0;2];
%      if option.kernel='rbf': option.param is sigma, the default is 1;
%      if option.kernel='sigmoid': option.param is [alpha;beta], the default is [1;0];
%      if option.kernel use your own kernel function, option.param is the parameter of your kernel.
% option.iter: max number of interations. The default is 1000.
% option.dis: boolen scalar, It could be 
%     false: not display information,
%     true: display (default).
% option.residual: the threshold of the fitting residual to terminate. 
%     If the ||X-XfitThis||<=option.residual, then halt. The default is 1e-4.
% option.tof: if ||XfitPrevious-XfitThis||<=option.tof, then halt. The default is 1e-4.
% AtA: matrix, the kernel matrix, AtA=kernel(A,A).
% Y: matrix, the coefficient matrix.
% numIter: scalar, the number of iterations.
% tElapsed: scalar, the computing time used.
% finalResidual: scalar, the fitting residual.
% References:
% [1] \bibitem{Zhang2006}
%  D. Zhang, Z. Zhou, S. Chen,
%  ``Non-negative Matrix Factorization on Kernels,''
%  {\it LNCS},
%  vol. 4099, pp. 404-412, 2006.
% [2]\bibitem{cibcb2012}
%     Y. Li and A. Ngom,
%     ``A New Kernel Non-Negative Matrix Factorization and Its Application in Microarray Data Analysis,''
%     {\it CIBCB},
%     submited, 2012.
% Contact Information:
% Yifeng Li
% University of Windsor
% li11112c@uwindsor.ca; yifeng.li.cn@gmail.com
% Sep 27, 2011

tStart=tic;
optionDefault.kernel='rbf';
optionDefault.param=[];
optionDefault.iter=1000;
optionDefault.dis=1;
optionDefault.residual=1e-4;
optionDefault.tof=1e-4;
if nargin<3
   option=optionDefault;
else
    option=mergeOption(option,optionDefault);
end

% initialize
XtX=computeKernelMatrix(X,X,option);
[A,Y,numIter,tElapsed,finalResidual]=nmfrule(XtX,k,option);
tElapsed=toc(tStart);
end
