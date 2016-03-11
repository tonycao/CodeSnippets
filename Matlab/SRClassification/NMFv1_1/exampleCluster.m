
clear

% load data
% suppose the current folder is the one containing the NMF toolbox
load('.\data\ALLAML.mat','classes012','D');
classes=classes012;
clear('classes012');
k=3;
% Directly call a NMF algorithm to obtain the factor matrices.
[A,Y]=nmfnnls(D,k);
% Then clustering. 
indCluster1=NMFCluster(Y);

% Call the NMF interface. The default is nmfnnls algorithm.
[A,Y]=nmf(D,k);
% Then clustering.
indCluster2=NMFCluster(Y);

% Call the NMF interface. Specify an algorithm.
option.algorithm='nmfnnls';
[A,Y]=nmf(D,k,option);
% Then clustering.
indCluster3=NMFCluster(Y);

% Call the NMF interface. Specify an algorithm.
option.algorithm='sparsenmfnnls';
[A,Y]=nmf(D,k,option);
% Then clustering.
indCluster4=NMFCluster(Y);

% Directly call NMFCluster function. NMF optimization is done inside. The
% default algorithm is nmfnnls.
indCluster5=NMFCluster(D,k);

% % Directly call NMFCluster function. NMF optimization is done inside.
% Specify an algorithm.
option.algorithm='convexnmfrule';
indCluster6=NMFCluster(D,k,option);




