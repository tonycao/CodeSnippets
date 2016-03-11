function range=searchkernelRange(trainSet,trainClass,option)
% model selection
% only for rbf kernel
% Yifeng Li
% Nov 01, 2011

if nargin<3
   option=[]; 
end
optionDefault.range=5:30;
optionDefault.epsilon=1e-4;
option=mergeOption(option,optionDefault);
numTr=size(trainSet,2);
numP=numel(option.range);
M=nan(numP,1);
for i=1:numP
    option.param=2^option.range(i);
    K=computeKernelMatrix(trainSet,trainSet,option);
    sumK=sum(sum(K));
    if sumK<=(1+option.epsilon)*numTr || sumK>=(1-option.epsilon)*numTr*numTr
        continue;
    end
    M(i)=1;
end
range=option.range(~isnan(M));
end
