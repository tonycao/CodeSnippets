function [Y,numIter,tElapsed]=kernelnmfruletest(X,outTrain)
% map the test/unknown samples into the kernel-NMF feature space
% This function does not work because of technically difficulty.
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

error('The kernelnmfruletest function does not work because of technically difficulty.');
tStart=tic;
optionDefault.kernel='rbf';
optionDefault.param=[];
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

Ak=outTrain.factors{1};
A=outTrain.factors{2};
k=outTrain.facts;

Ap=(abs(Ak)+Ak)./2;
An=(abs(Ak)-Ak)./2;
[r,c]=size(X); % c is # of samples, r is # of features
inx=kmeans(X',k); % k-mean clustering, get idx=[1,1,2,2,1,3,3,1,2,3]
H=(inx*ones(1,k)-ones(c,1)*cumsum(ones(1,k)))==0; % obtain logical matrix [1,0,0;1,0,0;0,1,0;0,1,0;1,0,0;0,0,1;...]
G=H+0.2;
W=A;
XfitPrevious=Inf;
for i=1:option.iter
    ApW=Ap*W;
    AnW=An*W;
    GWt=G*W';
    G=G.*sqrt((ApW + GWt*AnW)./(AnW + GWt*ApW));
%     G(G<eps)=0;
    G=max(G,eps);
    Y=G';
    if mod(i,10)==0 || i==option.iter
        if option.dis
            disp(['Iterating >>>>>> ', num2str(i),'th']);
        end
        XfitThis=Ak*A*Y;
        fitRes=norm(XfitPrevious-XfitThis,'fro');
        XfitPrevious=XfitThis;
        curRes=norm(Ak-XfitThis,'fro');
        if option.tof>=fitRes || option.residual>=curRes || i==option.iter
            s=sprintf('Mutiple update rules based KernelNMF successes! \n # of iterations is %0.0d. \n The final residual is %0.4d.',i,curRes);
            disp(s);
            numIter=i;
            finalResidual=curRes;
            break;
        end
    end
end
tElapsed=toc(tStart);
end
