function k=kernelLinear(x,y,param)
% linear kernel
% Usage:
% k=kernelLinear(x,y)
% x,y: column vectors, or matrices.
% param: []
% k, scalar or matrix, the kernel values

k=x'*y;
end