% This is an example of how to extract features using NMF
clear

% load data
% % suppose the current folder is the one containing the NMF toolbox
load('.\data\ALLAML.mat','classes012','D');
classes=classes012;
clear('classes012');

% unit l_2 norm normalization
D=normc(D);

kfold=4;
ind=crossvalind('Kfold',classes,kfold);
indTest=(ind==1);
trainSet=D(:,~indTest);
testSet=D(:,indTest);
trainClass=classes(~indTest);
testClass=classes(indTest);
% feature extraction
feMethod='knmf-l1nnls'; % 'knmf-l1nnls'
optionFE.facts=3;
optionFE.option.kernel='rbf';
optionFE.option.param=2^0;
optionFE.option.lambda=0.1;
[trainExtr,outTrain]=featureExtractionTrain(trainSet,trainClass,feMethod,optionFE);
[testExtr,outTest]=featureExtrationTest(trainSet,testSet,outTrain);

trainSet=trainExtr;
testSet=testExtr;
% classification
disp('KNN classifier:');
tic;
testClassPredicted=knnclassify(testSet',trainSet',trainClass,1);
tElapsedKNN=toc;
% classPerformKNN includes the accuracies of class 0, class 1, class 2, and total accuracy, and balanced accuracy
classPerformKNN=perform(testClassPredicted,testClass,numel(unique([trainClass;testClass])))

disp('SVM classifier:');
% normalization
[trainSet,trainSetMean,trainSetSTD]=normmean0std1(trainSet');
trainSet=trainSet';
testSet=normmean0std1(testSet',trainSetMean,trainSetSTD);
testSet=testSet';
tic;
model=svmtrain(trainClass,trainSet','-s 0 -t 2 -b 1');
testClassPredicted = svmpredict(testClass, testSet', model,'-b 1');
tElapsedSVM=toc;
% classPerformSVM includes the accuracies of class 0, class 1, class 2, and total accuracy, and balanced accuracy
classPerformSVM=perform(testClassPredicted,testClass,numel(unique([trainClass;testClass])))
%% tensor data
load('.\data\InfBetaTensorComplete.mat','classes','D');

% If you need to normalize your tensor data, please use either unit l_2 norm normalization or n-way normalization (but not both) 
% % l_2 norm normalization
% numR=size(D,1);
% numC=size(D,2);
% D=matrizicing(D,3);
% D=D';
% D=normc(D);
% numP=size(D,2); % number of pages
% D=unmatrizicing(D,3,[numR,numC,numP]);

kfold=4;
ind=crossvalind('Kfold',classes,kfold);
indTest=(ind==1);
trainSet=D(:,:,~indTest);
testSet=D(:,:,indTest);
trainClass=classes(~indTest);
testClass=classes(indTest);

% n-way normalization
% Note: You need to install Dr. Rasmus Bro's The N-way toolbox for MATLAB in order
% to use nprocess function. Download it from here http://www.models.life.ku.dk/nwaytoolbox
Cent=[0,0,1];
Scal=[1,1,0];
[trainSet,Means,Scales]=nprocess(trainSet,Cent,Scal);
[testSet,Means,Scales]=nprocess(testSet,Cent,Scal,Means,Scales,1);

% feature extraction
feMethod='knmf-l1nnls'; % try also 'knmf-nnls'
optionFE.option.kernel='ds';
optionFE.option.param=[1 5];
optionFE.option.lambda=0.1;
optionFE.facts=5;
[trainExtr,outTrain]=featureExtractionTrain(trainSet,trainClass,feMethod,optionFE);
[testExtr,outTest]=featureExtrationTest(trainSet,testSet,outTrain);
trainSet=trainExtr;
testSet=testExtr;

% classification
disp('KNN classifier:');
tic;
testClassPredicted=knnclassify(testSet',trainSet',trainClass,1);
tElapsedKNN=toc;
% classPerformKNN includes the accuracies of class 0, class 1, class 2, and total accuracy, and balanced accuracy
classPerformKNN=perform(testClassPredicted,testClass,numel(unique([trainClass;testClass])))

disp('SVM classifier:');
% normalization
[trainSet,trainSetMean,trainSetSTD]=normmean0std1(trainSet');
trainSet=trainSet';
testSet=normmean0std1(testSet',trainSetMean,trainSetSTD);
testSet=testSet';
tic;
model=svmtrain(trainClass,trainSet','-s 0 -t 2 -b 1');
testClassPredicted = svmpredict(testClass, testSet', model,'-b 1');
tElapsedSVM=toc;
% classPerformSVM includes the accuracies of class 0, class 1, class 2, and total accuracy, and balanced accuracy
classPerformSVM=perform(testClassPredicted,testClass,numel(unique([trainClass;testClass])))







