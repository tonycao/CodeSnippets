function [en,dist]=entropyCluster(indCluster,classes)

numSample=numel(classes);
uniClass=unique(classes);
numClass=numel(uniClass);
uniCluster=unique(indCluster);
numCluster=numel(uniCluster);
dist=zeros(numCluster,numClass);
logn=zeros(numCluster,numClass);
for i=1:numCluster
    curClu=(indCluster==(uniCluster(i)));
    numCurClu=sum(curClu);
    for j=1:numClass
        curCla=(classes==uniClass(j));
        curCluCla=curClu&curCla;
        numCurCluCla=sum(curCluCla);
        if numCurCluCla==0
            continue;
        end
        dist(i,j)=numCurCluCla;
        logn(i,j)=numCurCluCla*log2(numCurCluCla/numCurClu);
    end
end
en=-1/(numSample*log2(numClass))*sum(sum(logn));
end