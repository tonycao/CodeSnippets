function [gammaOptimal,KOptimal,scoreMax]=modelSelectionGammaK(D,classes,option)
% Grid Search
% usuages:
%[gammaOptimal,KOptimal,accMax]=modelSelectionGammaK(D,classes,option);
%[gammaOptimal,KOptimal,accMax]=modelSelectionGammaK(D,[],option);
%[gammaOptimal,KOptimal,accMax]=modelSelectionGammaK(D);
% Yifeng Li, Nov 01, 2011

numSample=size(D,2);
optionDefault.KRange=2:round(sqrt(numSample));
optionDefault.gammaRange=0:10; % exponent of 2
optionDefault.modSelMethod='dispersionCoefficient';
optionDefault.rerun=30;
optionDefault.algorithm='nmfnnls';
optionDefault.optionnmf=[];
if nargin<3
   option=[];
else
    option=mergeOption(option,optionDefault);
end
if nargin<2
   classes=[]; 
end

numKRange=numel(option.KRange);
numGammaRange=numel(option.gammaRange);
numG=numGammaRange;
ifKernel=true;
if numGammaRange==0
    numG=1;
    ifKernel=false;
end

scores=zeros(numG,numKRange);
for j=1:numG
    if ifKernel
        option.optionnmf.param=2^option.gammaRange(j);
    else
        option.optionnmf.param=[];
    end
    for i=1:numKRange
        switch option.modSelMethod
            case 'dispersionCoefficient'
                C=zeros(numSample,numSample);
                for r=1:option.rerun
                    [~,Y]=nmf(D,option.KRange(i),option);
                    ind=getClusters(Y); % get the indicator matrix
                    C=C+getRelationMatrix(ind);
                end
                C=C./option.rerun;
                scores(j,i)=dispersionCoefficient(C);
            case 'purityEntropyRatio'
                if isempty(classes)
                    error('purityEntropyRatio needs the class information! can not be empty');
                end
                ratio=0;
                for r=1:option.rerun
                    [~,Y]=nmf(D,optionKRange(i),option);
                    ind=NMFCluster(Y); % get the indicator matrix
                    ratio=ratio+purity(ind,classes)/entropyCluster(ind,classes);
                end
                ratio=ratio/option.rerun;
                scores(j,i)=ratio;
            otherwise
                error('Please choose the correct model selection measure');
        end
    end
end

[scoresRow,indsRow]=max(scores,[],1);
[scoreMax,indCol]=max(scoresRow);
indRow=indsRow(indCol);
gammaOptimal=2^(option.gammaRange(indRow));
KOptimal=option.KRange(indCol);
end
