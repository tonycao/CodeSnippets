function [indCluster,numIter,tElapsed,finalResidual]=NMFCluster(X,k,option)
% NMF based clustering
% Usage:
% [indCluster,numIter,tElapsed,finalResidual]=NMFCluster(X) % in this case, X is coefficient matrix obtained by a NMF outside this function
% [indCluster,numIter,tElapsed,finalResidual]=NMFCluster(X,k)
% [indCluster,numIter,tElapsed,finalResidual]=NMFCluster(X,k,option)
% X: matrix, the data to cluster, each column is a sample/data point
% k: the number of clusters
% option: struct, the same as the option in the nmf function, type "help nmf" for more informtion
% indCluster: the cluster label of each sample, i.e. indCluster=[2;2;1;1;3;2;1;1;2;3];
% numIter: scalar, the number of iterations.
% tElapsed: scalar, the computing time used.
% finalResidual: scalar, the fitting residual.
% Contact Information:
% Yifeng Li
% University of Windsor
% li11112c@uwindsor.ca; yifeng.li.cn@gmail.com
% May 21, 2011

callNMF=true;
if nargin==2
    option=[];
    callNMF=true;
end
if nargin==1
    Y=X; % X is coefficient matrix
    callNMF=false;
end
if callNMF
   [A,Y,numIter,tElapsed,finalResidual]=nmf(X,k,option); 
end
[C,indCluster]=max(Y,[],1);
indCluster=indCluster';
end