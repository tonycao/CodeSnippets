function w=SW(K,trainClass)
% compute the expected distance of an image from the mass center of a class
% K: kernel matrix
% trainClass: column vector, the class labels of the samples

uniCls=unique(trainClass);
numCl=numel(uniCls);
w=0;
for i=1:numCl
   ind=(trainClass==uniCls(i));
   numCurCl=sum(ind);
   w=w + (1/numCurCl * sum(diag(K(ind,ind)))) - (1/numCurCl^2 * sum(sum(K(ind,ind))));
end
w=w/numCl;
end
