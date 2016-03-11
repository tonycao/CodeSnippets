function [ind,clusters,clusterClasses,order]=getClusters(Y,X,classes)
% X, matrix, data, each column is a sample
% Y, matrix, coefficient matrix, obtained through NMF: X=AY
% classes: ,column vector, class labels of the samples in X
% Yifeng Li
% May 03, 2011

if nargin<3
    classes=[];
end
if nargin<2
   X=[]; 
end

ind=[];
clusters=[];
clusterClasses=[];
order=[];

[numCluster,numSample]=size(Y);
[C,in]=max(Y,[],1);
ind=false(numCluster,numSample);
% indicator matrix
for i=1:numSample
    ind(in(i),i)=true;
end
if isempty(X)&& isempty(classes)
    return;
end
% for each cluster, obtain the samples and class labels
if ~isempty(X)
    clusters=cell(1,numCluster);
    for j=1:numCluster
        clusters{j}=X(:,ind(j,:));
    end
end
if ~isempty(classes)
    clusterClasses=cell(1,numCluster);
    for j=1:numCluster
        clusterClasses{j}=classes(ind(j,:));
    end
end
numorder=(1:numSample)';
order=cell(1,numCluster);
for j=1:numCluster
   order{j}=numorder(ind(j,:));
end
end