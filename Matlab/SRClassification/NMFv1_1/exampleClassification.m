% This is an example of how to use the NNLS, BNNLS, NMF, and RNMF
% classifiers.
clear

% load data
% suppose the current folder is the one containing the NMF toolbox
load('.\data\ALLAML.mat','classes012','D');
classes=classes012;
clear('classes012');
kfold=3;
ind=crossvalind('Kfold',classes,kfold);
indTest=(ind==1);
trainSet=D(:,~indTest);
testSet=D(:,indTest);
trainClass=classes(~indTest);
testClass=classes(indTest);

% classification
disp('NNLS classifier...');
tic;
[testClassPredicted,sparsity]=nnlsClassifier(trainSet,trainClass,testSet,testClass);
tElapsedNNLS=toc;
% classPerformNNLS includes the accuracies of class 0, class 1, class 2, and total accuracy, and balanced accuracy
classPerformNNLS=perform(testClassPredicted,testClass,numel(unique([trainClass;testClass])));

disp('BNNLS classifier...');
tic;
testClassPredicted=bootstrapnnlsClassifier(trainSet,trainClass,testSet,testClass);
tElapsedBNNLS=toc;
classPerformBNNLS=perform(testClassPredicted,testClass,numel(unique([trainClass;testClass])));

disp('NMF classifier...');
optionnmf.facts=5; % number of clusters
[A,Y]=nmfnnls(D,optionnmf.facts); % clustering
optionnmf.Y=Y;
clear('A');
% reorder Y
Yreordered=[optionnmf.Y(:,~indTest),optionnmf.Y(:,indTest)];
optionnmf.Y=Yreordered;
tic;
[testClassPredicted]=nmfClassifier(trainSet,trainClass,testSet,testClass,optionnmf);
tElapsedNMF=toc;
classPerformNMF=perform(testClassPredicted,testClass,numel(unique([trainClass;testClass])));

disp('RNMF classifier...');
optionrnmf.facts=5;
optionrnmf.repetitive=9;
Ys=cell(optionrnmf.repetitive,1);
for r=1:optionrnmf.repetitive
    if any(any(D<0))
        [A,Yr]=seminmfnnls(D,optionrnmf.facts);
    else
        [A,Yr]=nmfnnls(D,optionrnmf.facts);
    end
    Ys{r}=Yr;
end
optionrnmf.Ys=Ys;
clear('A');
% reorder Ys
for p=1:optionrnmf.repetitive
    Yreordered=[optionrnmf.Ys{p}(:,~indTest),optionrnmf.Ys{p}(:,indTest)];
    optionrnmf.Ys{p}=Yreordered;
end
tic;
[testClassPredicted]=repetitivenmfClassifier(trainSet,trainClass,testSet,testClass,optionrnmf);
tElapsedRNMF=toc;
classPerformRNMF=perform(testClassPredicted,testClass,numel(unique([trainClass;testClass])));

disp('NNLS classifier using ''classification'' function...');
tic;
method='nnls';
[testClassPredicted,classPerform,otherOutput]=classification(trainSet,trainClass,testSet,testClass,method);
tElapsedNNLS2=otherOutput{1};
classPerformNNLS2=classPerform;

disp('SVM classifier using ''classification'' function...');
tic;
method='svm';
optionCl.normalization=1; % normalization
[testClassPredicted,classPerform,otherOutput]=classification(trainSet,trainClass,testSet,testClass,method,optionCl);
tElapsedSVM=otherOutput{1};
classPerformSVM=classPerform;

disp('KNN, SVM, NNLS, BNNLS, NMF, and RNMF classifiers using ''multiClassifiers'' function...');
tic;
methods={'knn';'svm';'nnls';'bootstrapnnls';'nmf';'rnmf'};
optionSVM.normalization=1; % normalization
optionNMF.Y=Y;
optionNMF.facts=5;
optionRNMF.Ys=Ys;
optionRNMF.facts=5;
options={[];optionSVM;[];[];optionNMF;optionRNMF};
[testClassPredicteds,classPerforms,tElapseds,OtherOutputs]=multiClassifiers(trainSet,trainClass,testSet,testClass,methods,options);
tElapsedM=tElapseds;
classPerformM=classPerforms;

fprintf('The classification performance of NNLS classifier is: \n\r');
classPerformNNLS
fprintf('The classification performance of BNNLS classifier is: \n\r');
classPerformBNNLS
fprintf('The classification performance of NMF classifier is: \n\r');
classPerformNMF
fprintf('The classification performance of RNMF classifier is: \n\r');
classPerformRNMF
fprintf('The classification performance of NNLS classifier is: \n\r');
classPerformNNLS2
fprintf('The classification performance of SVM classifier is: \n\r');
classPerformSVM
fprintf('The classification performance of KNN, SVM, NNLS, BNNLS, NMF, and RNMF classifiers are: \n\r');
classPerformM
