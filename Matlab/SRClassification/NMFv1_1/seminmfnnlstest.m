function [Y,numIter,tElapsed]=seminmfnnlstest(X,outTrain)
% SemiNMF based on NNLS: X=AY, s.t. Y>0;
% X, dataset, matrix, each column is a sample, each row is a feature, each column of X is a sample
% k, number of clusters
% option: struct:
% option.iter, max number of interations
% option.dis, boolen scalar, false: (not display information) or true
% (display).
% option.residual, if the ||X-XfitThis||<=option.residual, halt.
% option.tof, if ||XfitPrevious-XfitThis||<=option.tof, halt.
% Yifeng Li, May 01, 2011
% yifeng.li.cn@gmail.com

tStart=tic;
A=outTrain.factors{1};
% option=outTrain.option;
Y=fcnnls(A,X);
numIter=1;
tElapsed=toc(tStart);
end
