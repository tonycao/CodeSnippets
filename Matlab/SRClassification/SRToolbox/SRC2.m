function [testClassPredicted, sparsity,OtherOuptput] = SRC2(trainSet, trainClass, testSet, option)
% SRC2 for overcomplete data
% trainSet: matrix, each column is a training sample
% trainClass: column vector, the class labels for training samples
% testSet: matrix, the test samples
% option, struct, with fields:
% option.lambda: scalar, the parameter to optimization algorithm l1_ls, the
% default is 0.1.
% option.predicter: string, the rule to interpret the sparse code, it can be
% 'subspace' (default),'max','kvote'.
% testClassPredicted: column vectors, the predicted class labels of
% testing samples.
% sparsity: scalar, the sparsity of the sparse coefficient matrix.
% Yifeng Li
% note: each sample has to be normalized to unit l2 norm

% % normalization to length 1
% trainSet=normc(trainSet);
% testSet=normc(testSet);

% optionDefault.p=4;
optionDefault.lambda=0.1;
optionDefault.predicter='subspace';
option=mergeOption(option,optionDefault);
% trainSet=downsample(trainSet,option.p);
% testSet=downsample(testSet,option.p);

% training step, obtain sparse coefficients in columns of Y
Y=zeros(size(trainSet,2),size(testSet,2));
for i=1:size(testSet,2)
    Y(:,i)= l1_ls(trainSet, testSet(:,i), option.lambda); %http://www.stanford.edu/~body/l1_ls
end

% calculate sparsity
sparsity=sum(sum(abs(Y)<=0.0001))/(size(Y,1)*size(Y,2));

% predict step
switch option.predicter
    case  'max'
        [val,ind]=max(Y,[],1);
        testClassPredicted=trainClass(ind);
        OtherOuptput=[];
    case 'kvote'
        for s=1:size(Y,2)
            [sortedCoeff,ind] = getBestScores(Y(:,s),option.k);
            predicted(s,:)=trainClass(ind);
        end
        testClassPredicted=vote(predicted);
        OtherOuptput=[];
    case 'subspace'
        [testClassPredicted,residuals]=subspace(Y,testSet,trainSet,trainClass);
        OtherOuptput=residuals;
end
end
