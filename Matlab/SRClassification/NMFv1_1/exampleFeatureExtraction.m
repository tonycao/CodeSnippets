% This is an example of how to extract features using NMF
clear

% load data
% % suppose the current folder is the one containing the NMF toolbox
load('.\data\ALLAML.mat','classes012','D');
classes=classes012;
clear('classes012');
kfold=4;
ind=crossvalind('Kfold',classes,kfold);
indTest=(ind==1);
trainSet=D(:,~indTest);
testSet=D(:,indTest);
trainClass=classes(~indTest);
testClass=classes(indTest);
% feature extraction
feMethod='nmf';
optionFE.facts=3;
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
classPerformKNN=perform(testClassPredicted,testClass,numel(unique([trainClass;testClass])));

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
classPerformSVM=perform(testClassPredicted,testClass,numel(unique([trainClass;testClass])));







