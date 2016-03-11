function perf=perform(testClassPredicted,testClass,c)
% Analyze the performance of classification
% For binary-class problem, the class labels should be 0 and 1.
% For m-class problem, the class labels should be 0,1,2,3,...,m-1.
% Usage:
% perf=perform(testClassPredicted,testClass,c)
% testClassPredicted: vector, predicted class labels of testing samples. 
% testClass: vector, the real class labels of testing.
% c: the number of classes.
% perf: row vector, 
%      if c==2: perf=[PPV,NPV,Spec.,Sen., Acc., and BAcc]
%      if c>2: perf=[Acc1,Acc1,Acc2,Acc3,...,Acc,Bacc].
% Contact Information:
% Yifeng Li
% University of Windsor
% li11112c@uwindsor.ca; yifeng.li.cn@gmail.com
% Oct. 24, 2009

if c<=4
    perf=zeros(1,6);
else
    perf=zeros(1,c+2);
end
tfnum=isnumeric(testClass);
if ~tfnum
    error('The elements must be numeric: 0,1,...');
end
n=numel(testClass);

if c==2 % binary classes
TP=0;
TN=0;
FP=0;
FN=0;
for i=1:n
    if ~isnan(testClassPredicted(i))
        if testClassPredicted(i)==1
            if testClass(i)==1 % positive
                TP=TP+1;
            else
                FP=FP+1;
            end
        else
            if testClass(i)==0 % negtive
                TN=TN+1;
            else
                FN=FN+1;
            end
            
        end
    end
end
perf=zeros(1,6);
perf(1,1)=TP/(TP+FP); %PPV
perf(1,2)=TN/(TN+FN); %NPV
perf(1,3)=TN/(TN+FP); %Spec.
perf(1,4)=TP/(TP+FN); %Sen.
perf(1,5)=(TP+TN)/n; %Accuracy
perf(1,6)=nanmean([perf(1,3);perf(1,4)]); % BACC
end

if c>=3 % multiple class
    for i=1:n
        if testClassPredicted(i)==testClass(i)
            for ci=1:c
                if testClass(i)==ci-1
                    perf(1,ci)= perf(1,ci)+1;
                end
            end
        end 
    end
    perf(1,c+1)=sum(perf(1:c)); % acc
    % get acc0,acc1,...
    for ci=1:c
        numci=sum(testClass==ci-1);
        perf(1,ci)=perf(1,ci)/numci;
    end
    perf(1,c+1)=perf(1,c+1)/n; %acc
    perf(1,c+2)=nanmean(perf(1:c)); % bacc
end
       
    
end