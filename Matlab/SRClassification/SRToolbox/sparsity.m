function s=sparsity(Y)
% Calculate the sparsity of a matrix
% Y: matrix
% s: scalar, the sparsity of Y
% Contact Information:
% Yifeng Li
% University of Windsor
% li11112c@uwindsor.ca; yifeng.li.cn@gmail.com
% May 26, 2011

s=sum(sum(Y<=0.0001))/(size(Y,1)*size(Y,2));
end