function [Y,numIter,tElapsed]=seminmfruletest(X,outTrain)
% SemiNMF based on update rules: X=AY, s.t. Y>0;
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
optionDefault.iter=1000;
optionDefault.dis=1;
optionDefault.residual=1e-4;
optionDefault.tof=1e-4;

A=outTrain.factors{1};
if isfield(outTrain,'option')
    option=outTrain.option;
else
    option=[];
end
option=mergeOption(option,optionDefault);

Y=A\X;
Y(Y<0)=0;
Apn=A'*X;
Ap=(abs(Apn)+Apn)./2;
An=(abs(Apn)-Apn)./2;
Bpn=A'*A;
Bp=(abs(Bpn)+Bpn)./2;
Bn=(abs(Bpn)-Bpn)./2;
XfitPrevious=Inf;
for i=1:option.iter
    Y=Y.*sqrt((Ap + Bn*Y)./(An + Bp*Y));
    if mod(i,10)==0 || i==option.iter
        if option.dis
            disp(['Iterating >>>>>> ', num2str(i),'th']);
        end
        XfitThis=A*Y;
        fitRes=matrixNorm(XfitPrevious-XfitThis);
        XfitPrevious=XfitThis;
        curRes=matrixNorm(X-XfitThis);
        if option.tof>=fitRes || option.residual>=curRes || i==option.iter
            disp(['Mutiple update rules based on SemiNMF successes!, # of iterations is ',num2str(i),'. The final residual is ',num2str(curRes)]);
            numIter=i;
            finalResidual=curRes;
            break;
        end
    end
end
tElapsed=toc(tStart);
end
