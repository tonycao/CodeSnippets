function [Y,numIter,tElapsed]=nmfnnlstest(X,outTrain)
% map the test/unknown samples into the NMF feature space
% X: matrix, test/unknown set, each column is a sample, each row is a feature.
% outTrain: struct, related options in the training step.
% outTrain.factors: column vector of cell of length 2, contain the matrix factors obtained by NMF
% optTrain.facts: scalar, the number of new features.
% outTrain.optionTr: struct, the option input into the training step. The default is [].
% Y: matrix, the test samples in the feature space.
% numIter: scalar, number of iterations.
% tElapsed: scalar, the computing consumed.
% Contact Information:
% Yifeng Li
% University of Windsor
% li11112c@uwindsor.ca; yifeng.li.cn@gmail.com
% May 03, 2011


tStart=tic;
A=outTrain.factors{1};
% option=outTrain.option;
Y=kfcnnls(A,X);
numIter=1;
tElapsed=toc(tStart);
end