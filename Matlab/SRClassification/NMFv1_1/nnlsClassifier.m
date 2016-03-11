function [testClassPredicted,sparsity]=nnlsClassifier(trainSet,trainClass,testSet,testClass,option)
% NNLS Classifier: testSet=trainSet*Y, s.t. Y>=0.
% Usage:
% [testClassPredicted,sparsity]=nnlsClassifier(trainSet,trainClass,[],testClass)
% [testClassPredicted,sparsity]=nnlsClassifier(trainSet,trainClass,testSet,testClass)
% [testClassPredicted,sparsity]=nnlsClassifier(trainSet,trainClass,testSet,testClass,option)
% trainSet, matrix, the training set with samples in columns and features in rows.
% trainClass: column vector of numbers or string, the class labels of the traning set.
% testSet: matrix, the test set.
% testClass: column vector of numbers or string, the class labels of the
% test/unknown set. It is actually unused in this function, thus, set it [].
% option: struct, the options to configue this function:
% option.method, string, the optimization algorithm used to solve the NNLS problem. It could be
%     'nnls': used the NNLS algorithm (default);
%     'seminmfupdaterule': use the update rules based algorithm;
%     'sparsennls': used NNLS algorithm with sparse constraint.
% option.predicter: the method to find the class label of a test sample according to Y. It could be
%     'max': the same class label with the training sample with the maximum coefficient (default);
%     'kvote': select k training samples with the k largest coefficients, and decide the class labels by majority voting.
% option.k: scalar, only for option.predicter='kvote'. The default is 1.
% testClassPredicted: column vector, the predicted class labels of the test/unknown samples.
% sparsity: scalar, the sparsity of the coefficient matrix Y.
% References:
%  [1]\bibitem{nips2011}
%     Y. Li, and A. Nogm,
%     ``Non-neagtive least squares classifier,''
%     {\it Advances in Neural Information Processing Systems},
%     submitted. 
%     Available at \url{http://cs.uwindsor.ca/~li11112c/doc/nips2011.pdf}
% Contact Information:
% Yifeng Li
% University of Windsor
% li11112c@uwindsor.ca; yifeng.li.cn@gmail.com
% May 23, 2011

optionDefault.method='nnls';
optionDefault.predicter='max';
optionDefault.k=1;
if nargin<5
    option=optionDefault;
else
    option=mergeOption(option,optionDefault);
end
% if tensor data
if size(trainSet,3)>1
    trainSet=matrizicing(trainSet,3);
    testSet=matrizicing(testSet,3);
    trainSet=trainSet';
    testSet=testSet';
end
switch option.method
    case 'nnls'
        Y=fcnnls(trainSet,testSet);
        sparsity=sum(sum(Y<=0.00001))/(size(Y,1)*size(Y,2));
    case 'sparsennls'
        optionDefault.beta=0.1;
        optionDefault.eta=max(max(trainSet))^2;
        option=mergeOption(option,optionDefault);
        outTrain.factors{1}=trainSet;
        outTrain.option=option;
        Y=sparsenmfnnlstest(testSet,outTrain);
        sparsity=sum(sum(Y<=0.00001))/(size(Y,1)*size(Y,2));
    case 'seminmfupdaterule'
%         optionDefault.iter=1000;
%         option=mergeOption(option,optionDefault);
        option.dis=0;
        outTrain.factors{1}=trainSet;
        outTrain.option=option;
        Y=seminmfruletest(testSet,outTrain);
        sparsity=sum(sum(Y<=0.00001))/(size(Y,1)*size(Y,2));
end

switch option.predicter
    case  'max'
        [val,ind]=max(Y,[],1);
        testClassPredicted=trainClass(ind);
    case 'kvote'
        for s=1:size(Y,2)
            [sortedCoeff,ind] = getBestScores(Y(:,s),option.k);
            predicted(s,:)=trainClass(ind);
        end
        testClassPredicted=vote(predicted);
end

    
end