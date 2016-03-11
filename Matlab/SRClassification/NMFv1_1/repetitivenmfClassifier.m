function [testClassPredicted]=repetitivenmfClassifier(trainSet,trainClass,testSet,testClass,option)
% Repetitive NMF classifier.
% Usage:
% [testClassPredicted,sparsity]=repetitivenmfClassifier(trainSet,trainClass,[],testClass)
% [testClassPredicted,sparsity]=repetitivenmfClassifier(trainSet,trainClass,testSet,testClass)
% [testClassPredicted,sparsity]=repetitivenmfClassifier(trainSet,trainClass,testSet,testClass,option)
% trainSet, matrix, the training set with samples in columns and features in rows.
% trainClass: column vector of numbers or string, the class labels of the traning set.
% testSet: matrix, the test set.
% testClass: column vector of numbers or string, the class labels of the
% test/unknown set. It is actually unused in this function, thus, set it [].
% option: struct, the options to configue this function:
% option.facts: scalar, the number of clusters. The default is the number of classes;
% option.Ys: matrix, the coefficient matrix Y produced outside this function. The default is [];
% option.repetitive, scalar, the number of calling NMF clustering;
% testClassPredicted: column vector, the predicted class labels of the test/unknown samples.
% References:
%  [1]\bibitem{LiTCBB2011} 
%     Y. Li,  
%     ``Non-negative matrix factorization classifier,''
%     {\it IEEE/ACM Transactions on Computational Biology and Bioinformatics}, 
%     submitted, 2011. 
%     Available at \url{http://cs.uwindsor.ca/~li11112c/doc/tcbb2011.pdf}
% Contact Information:
% Yifeng Li
% University of Windsor
% li11112c@uwindsor.ca; yifeng.li.cn@gmail.com
% May 23, 2011


optionDefault.facts=numel(unique([trainClass;testClass]));
optionDefault.Ys={};
optionDefault.repetitive=9;
option=mergeOption(option,optionDefault);


% if tensor data
if size(trainSet,3)>1
    trainSet=matrizicing(trainSet,3);
    testSet=matrizicing(testSet,3);
    trainSet=trainSet';
    testSet=testSet';
end
% clustering based sample selection
if isempty(option.Ys)
    for r=1:option.repetitive
        if any([trainSet,testSet]<0)
            [A,Y]=seminmfnnls([trainSet,testSet],option.facts);
        else
            [A,Y]=nmfnnls([trainSet,testSet],option.facts);
        end
        option.Ys{r}=Y;
    end
    clear('A','Y');
end
testClassPredicted=repmat(testClass(:),1,option.repetitive);
for r=1:option.repetitive
    optionnmf.facts=option.facts;
    if ~isempty(option.Ys)
        optionnmf.Y=option.Ys{r};
    else
        optionnmf.Y=[];
    end
    testClassPredicted(:,r)=nmfClassifier(trainSet,trainClass,testSet,testClass,optionnmf);
end
testClassPredicted=vote(testClassPredicted);
end