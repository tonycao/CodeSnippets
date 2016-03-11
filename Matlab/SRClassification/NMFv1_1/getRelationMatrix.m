function C=getRelationMatrix(ind)
% ind, logical matrix
% C, numerical matrix
% Yifeng Li
% May 04, 2011

[numCluster,numSample]=size(ind);
C=zeros(numSample,numSample);
for c=1:numCluster
    C(ind(c,:),ind(c,:))=1;
end
end