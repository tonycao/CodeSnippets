% Interactive Graph cuts Segmentation Algorithm
% Towards Medical Image Analysis course
% By Ravindra Gadde, Raghu Yalamanchili

% Interactive Graph cut segmentation using max flow algorithm as described
% in Y. Boykov, M. Jolly, "Interactive Graph Cuts for Optimal Boundary and
% Region Segmentation of Objects in N-D Images", ICCV, 2001.
clear all;
close all;
clc;
K=10; % Large constant
sigma=1;% Similarity variance
lambda=10^12;% Terminal Constant
c=10^8;% Similarity Constant
%mex maxflowmex.cpp maxflow-v3.0/graph.cpp maxflow-v3.0/maxflow.cpp % Mex

im = imread('abdomen.jpg'); % Read image
im = imnoise(im,'gaussian');

m = double(rgb2gray(im));
[height,width] = size(m);

disp('building graph');

N = height*width;

% construct graph
% Calculate weighted graph
E = edges4connected(height,width);
V = c*exp(-abs(m(E(:,1))-m(E(:,2))))./(2*sigma^2);
A = sparse(E(:,1),E(:,2),V,N,N,4*N);
  load 'ground_abdomen.mat' % Comment this part to manually select seeds
% Uncomment this part to manually select seeds
% imshow(m,[]);
% disp('select foreground pixels');
% [x,y] = ginput(50);
% fg(:,1)=ceil(y);
% fg(:,2)=ceil(x);
% % calcualate Terminal weights
% close all;
% imshow(m,[]);
% disp('select background pixels');
% [x1,y1] = ginput(50);
% bg(:,1)=ceil(y1);
% bg(:,2)=ceil(x1);
T = calc_weights(m,fg,bg,K,lambda); 


%Max flow Algorithm
disp('calculating maximum flow');

[flow,labels] = maxflow(A,T);
labels = reshape(labels,[height width]);
for i = 1: height
    for j = 1: width
        if(labels(i,j)==0)
            im_segment(i,j)=im(i,j);
            
        else
            im_segment(i,j)=0;
            
            
        end
    end
end
imagesc(labels); title('labels');
imshow(uint8(im_segment),[]);

