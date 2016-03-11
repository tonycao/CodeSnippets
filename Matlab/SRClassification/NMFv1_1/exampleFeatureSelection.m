% This is an example of how to extract features using NMF
clear

% load data
% % suppose the current folder is the one containing the NMF toolbox
load('.\data\ALLAML.mat','classes012','D','gene');
classes=classes012;
geneNames=gene(2:end,1);
clear('classes012','gene');
kfold=4;
ind=crossvalind('Kfold',classes,kfold);
indTest=(ind==1);
trainSet=D(:,~indTest);
testSet=D(:,indTest);
trainClass=classes(~indTest);
testClass=classes(indTest);
% feature selection
optionFS.facts=3;
mask=featureFilterNMF(trainSet,geneNames,optionFS);
trainSet=trainSet(mask,:);
testSet=testSet(mask,:);
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

disp('NNLS classifier...');
tic;
[testClassPredicted,sparsity]=nnlsClassifier(trainSet,trainClass,testSet,testClass);
tElapsedNNLS=toc;
% classPerformNNLS includes the accuracies of class 0, class 1, class 2, and total accuracy, and balanced accuracy
classPerformNNLS=perform(testClassPredicted,testClass,numel(unique([trainClass;testClass])));





