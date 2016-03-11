function [p,dist]=purity(indCluster,classes)

numSample=numel(classes);
uniClass=unique(classes);
numClass=numel(uniClass);
uniCluster=unique(indCluster);
numCluster=numel(uniCluster);
dist=zeros(numCluster,numClass);
for i=1:numCluster
    curClu=(indCluster==(uniCluster(i)));
    for j=1:numClass
        curCla=(classes==uniClass(j));
        dist(i,j)=sum(curClu&curCla);
    end
end
p=sum(max(dist,[],2))/numSample;
end