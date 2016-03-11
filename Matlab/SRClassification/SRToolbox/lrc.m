function [testClassPredicted,otherOutput]=lrc(trainSet,trainClass,testSet,testClass,option)
% linear regression classifier
% trainSet, matrix, each column is a training sample
% trainClass: column vector, the class labels for the training samples
% testSet: matrix, each column is a new or testing sample
% testClass; column vector, the class labels for the testing samples, can
% be [], if unknown.
% option, struct, reserved for future use.
% Yifeng Li, August 04, 2010

% optionDefault.p=16;
% option=mergeOption(option,optionDefault);
% % trainSet=downsample(trainSet,option.p);
% testSet=downsample(testSet,option.p);

utrCl=unique(trainClass);
numCl=numel(utrCl);
numTest=size(testSet,2);
testClassPredicted=zeros(numTest,1);
residuals=[];
for s=1:numTest
    testSets=testSet(:,s);
    residual=zeros(numCl,1);
    for i=1:numCl
        ind=(trainClass==utrCl(i));
        trainSeti=trainSet(:,ind);
        beta=pinv(trainSeti)*testSets;
        residual(i)=matrixNorm(testSets-trainSeti*beta);
    end
    residuals=[residuals;residual];
    [val,resInd]=min(residual);
    testClassPredicted(s)=utrCl(resInd);
end
otherOutput=residuals;
end