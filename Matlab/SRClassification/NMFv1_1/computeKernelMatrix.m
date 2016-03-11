function K=computeKernelMatrix(A,B,option)
% A: matrix, each column is a sample
% B: matrix, each column is a sample
% option: struct, include files:
% option.kernel
% option.param
% Yifeng Li, September 03, 2011
% yifeng.li.cn@gmail.com

if nargin<3
    option=[];
end
optionDefault.kernel='rbf';
optionDefault.param=[];
option=mergeOption(option,optionDefault);
switch option.kernel
    case 'rbf'
        if isempty(option.param)
            option.param=1; % sigma
        end
%     sigma=param(1);
%     kfun= @kernelRBF; % my rbf kernel
    kfun=@kernelRBF; % fast rbf kernel from official matla
    case 'polynomial'
        if isempty(option.param)
            option.param=[1;0;2];
        end
%     Gamma=param(1);
%     Coefficient=param(2);
%     Degree=param(3);
    kfun= @kernelPoly;
    case 'linear'
        if any(any(isnan(A))) % any(any(isnan([A,B]))) % missing values
            kfun=@innerProduct;
        else
           kfun= @kernelLinear; % no missing values
        end
    case 'sigmoid'
        if isempty(option.param)
            option.param=[1;0];
        end
%         alpha=param(1);
%         beta=param(2);
        kfun=@kernelSigmoid;
    case 'ds' % dynamical systems kernel
%         kfun=@dynamicSystems_kernel;%(D1,D2,param), param=[numR,numC,rank,lambda]
        kfun=@dynamicSystems_kernel2;%(D1,D2,param), param=[rank,lambda]
    otherwise
        eval(['kfunc=@',option.kernel,';']);
end

K=feval(kfun,A,B,option.param); % kernel matrix
end