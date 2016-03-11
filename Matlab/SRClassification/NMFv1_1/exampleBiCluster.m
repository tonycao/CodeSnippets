% This is an example of how to use the "biCluster" finction and how to draw
% the heatmap after biclustering.

clear

% load data 
% suppose the current folder is the one containing the NMF toolbox
load('.\data\ALLAML.mat','classes012','D');
classes=classes012;
clear('classes012');
k=3; % number of cluster

option.propertyName='threshold';
option.propertyValue=0.9;
option.algorithm='nmfnnls';
[ACluster,YCluster,indACluster,indYCluster,Xout,Aout,Yout,numIter,tElapsed,finalResidual]=biCluster(D,k,option);

option.colormap=redbluecmap;
option.standardize=true;
NMFBicHeatMap(Xout,Aout,Yout,indACluster,indYCluster,k,option);
