function [testClassPredicteds,classPerforms,tElapseds,OtherOutputs]=multiClassifiers(trainSet,trainClass,testSet,testClass,methods,options)
% trainSet, matrix, the training set with samples in columns and features in rows.
% Usuage:
% [testClassPredicteds,classPerforms,tElapseds,OtherOutputs]=multiClassifiers(trainSet,trainClass,testSet,testClass,methods)
% [testClassPredicteds,classPerforms,tElapseds,OtherOutputs]=multiClassifiers(trainSet,trainClass,testSet,testClass,methods,options)
% trainClass: column vector of numbers or string, the class labels of the traning set.
% testSet: matrix, the test set.
% testClass: column vector of numbers or string, the class labels of the
%       test/unknown set. It is actually unused in this function, thus, set it [].
% methods: column vector of cell strings, designate which one or more classifier to use. It could be
%     'nnls': the NNLS classifier;
%     'bootstrapnnls': the Bootstrap based NNLS classifier;
%     'nmf': the NMF classifier;
%     'rnmf': the RNMF classifier;
%     'knn': the KNN classifier;
%     'svm': the SVM classifier;
%     'bayesian': the Bayesian classifier;
%%%     'kernelfda': (for future extension);
%%%    'psdkernelfda': (for future extension).
%      For example, methods={nnls;nmf;svm};
% options: column vector of cells. options{i} is the option for methods{i}. Type "help classification" for more information.
% testClassPredicteds: matrix, testClassPredicteds(:,i) are the predicted class labels by methods{i}.
% classPerforms: matrix, classPerforms(i,:) is the class performance by methods{i}.
% tElapseds: column vector; tElapseds(i) is the computing time of methods{i}.
% OtherOutputs: column vector of cell. OtherOutputs{i} is the other otherOutput of methods{i}.
% See also "classfication".
% Contact Information:
% Yifeng Li
% University of Windsor
% li11112c@uwindsor.ca; yifeng.li.cn@gmail.com
% May 18, 2011

% if tensor data
if size(trainSet,3)>1
    trainSet=matrizicing(trainSet,3);
    testSet=matrizicing(testSet,3);
    trainSet=trainSet';
    testSet=testSet';
end
numClasses=numel(unique([trainClass;testClass]));
if numClasses<=4
    numberPerfMeasure=6;
else 
    numberPerfMeasure=2+numClasses;
end
testClassPredicteds=nan(numel(testClass),numel(methods));
classPerforms=nan(numel(methods),numberPerfMeasure);
OtherOutputs=cell(numel(methods),1);
tElapseds=nan(numel(methods),1);
for m=1:numel(methods)
    method=methods{m};
    if isempty(options{m})
        option=[];
    else
        option=options{m};
    end
    [testClassPredicted,classPerform,OtherOutput]=classification(trainSet,trainClass,testSet,testClass,method,option);
    testClassPredicteds(:,m)=testClassPredicted;
    classPerforms(m,:)=classPerform;
    tElapseds(m,1)=OtherOutput{1};
    OtherOutputs{m}=OtherOutput;
end
end