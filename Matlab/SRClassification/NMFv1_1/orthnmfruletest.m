function [Y,numIter,tElapsed]=orthnmfruletest(X,outTrain)
% map the test/unknown samples into the orth-NMF feature space
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
optionDefault.orthogonal=[1,1];
optionDefault.iter=200;
optionDefault.dis=1;
optionDefault.residual=1e-4;
optionDefault.tof=1e-4;
if isfield(outTrain,'optionTr')
    option=outTrain.optionTr;
else
    option=[];
end
option=mergeOption(option,optionDefault);

A=outTrain.factors{1};
S=outTrain.factors{2};
k=outTrain.facts;

[r,c]=size(X); % c is # of samples, r is # of features
[inx]=kmeans(X',k); % k-mean clustering, get idx=[1,1,2,2,1,3,3,1,2,3]
Y=(inx*ones(1,k)-ones(c,1)*cumsum(ones(1,k)))==0; % obtain logical matrix [1,0,0;1,0,0;0,1,0;0,1,0;1,0,0;0,0,1;...]
Y=Y'+0.2;

XfitPrevious=Inf;
for i=1:option.iter
    if option.orthogonal(2)==1
        Y=Y.*((S'*A'*X)./(S'*A'*X*(Y'*Y)));
    else
        Y=Y.*((A'*X)./(A'*A*Y));
    end
    Y=max(Y,eps);    
    if mod(i,10)==0 || i==option.iter
        if option.dis
            disp(['Iterating >>>>>> ', num2str(i),'th']);
        end
        XfitThis=A*S*Y;
        fitRes=norm(XfitPrevious-XfitThis,'fro');
        XfitPrevious=XfitThis;
        curRes=norm(X-XfitThis,'fro');
        if option.tof>=fitRes || option.residual>=curRes || i==option.iter
            s=sprintf('Multiple rule based orthNMF successes! \n # of iterations is %0.0d. \n The final residual is %0.4d.',i,curRes);
            disp(s);
            numIter=i;
            finalResidual=curRes;
            break;
        end
    end
end
tElapsed=toc(tStart);
end
