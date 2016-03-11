function rho=dispersionCoefficient(C)
% Calculate the dispersion Coefficient
% This function is used by function "chooseBestk"
% Yifeng Li, May 26, 2011

rho=sum(sum(4*(C-1/2).^2))/(size(C,1)^2);
end