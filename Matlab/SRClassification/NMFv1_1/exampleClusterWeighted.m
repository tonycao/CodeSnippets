% This is an example of how to use weighted NMF on data with missing values.

clear

% load data
% suppose the current folder is the one containing the NMF toolbox
load('.\data\ALLAML.mat','classes012','D');
classes=classes012;
clear('classes012');

% simulate missing values
D(rand(size(D))<0.05)=NaN;
k=3; % number of cluster
% Directly call the weighted NMF algorithm to obtain the factor matrices.
[A,Y]=wnmfrule(D,k);
% Then clustering. 
indCluster1=NMFCluster(Y);

% Or, can the "nmf" function
option.algorithm='wnmfrule';
[A,Y]=nmf(D,k,option);
% Then clustering. 
indCluster2=NMFCluster(Y);

