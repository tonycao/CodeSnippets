function b=SB(K, trainClass)
% compte the averaged distance between all class centroids

% centroid
uniCls=unique(trainClass);
numCl=numel(uniCls);
overAll=sum(sum(K));
b=0;
for i=1:numCl-1
    indi=(trainClass==uniCls(i));
    numi=sum(indi);
   for j=i+1:numCl
       indj=(trainClass==uniCls(j));
       numj=sum(indj);
    b=b+1/(numi^2) * sum(sum(K(indi,indi))) - 1/(numi*numj) * 2*sum(sum(K(indi,indj))) + 1/(numj^2) * sum(sum(K(indj,indj)));   
   end
end
b=2/(numCl^2-numCl);
end