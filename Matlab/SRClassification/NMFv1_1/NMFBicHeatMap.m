function NMFBicHeatMap(Xout,Aout,Yout,indACluster,indYCluster,k,option)
% Draw the heatmap for the result of biclustering
% Usuage:
% NMFBicHeatMap(Xout,Aout,Yout,indACluster,indYCluster,k)
% NMFBicHeatMap(Xout,Aout,Yout,indACluster,indYCluster,k,option)
% Xout: matrix, the same as the output "Xout" of function "biCluster".
% Aout: matrix, the same as the output "Aout" of function "biCluster".
% Yout: matrix, the same as the output "Yout" of function "biCluster".
% indACluster: column vector, the same as the output "indACluster" of function "biCluster".
% indYCluster: column vector, the same as the output "indYCluster" of function "biCluster".
% k: scalar, number of clusters
% option: struct, options
% option.standardize: boolen, if standardize the matrices of Xout, Aout, and Yout. The default is true;
% option.colormap: M-by-3 matrix of RGB values, 
%      or Name of or handle to a function that returns a colormap, such as
%      redgreencmap or redbluecmap. The default is redbluecmap;
% option.colorbar: boolen, if show the colorbar in the figure. The default is true;
% option.saveFormat: string, the format of the graph to saved. It could be
%     'eps' (default), 'png', 'jpeg', and 'pdf'.
% See function "biCluster" for more information.
% Contact Information:
% Yifeng Li
% University of Windsor
% li11112c@uwindsor.ca; yifeng.li.cn@gmail.com
% May 25, 2011

if nargin<7
    option=[];
end
optionDefault.standardize=true;
optionDefault.colormap=redbluecmap;
optionDefault.colorbar=true;
optionDefault.saveFormat='eps';
% optionDefault.sampleID=1:k;
% optionDefault.featureID=flipud(indACluster(:));
option=mergeOption(option,optionDefault);

%rb=redbluecmap(11);
W=isnan(Xout);
if any(W)
    Xout(W)=0;
end
XoutFlipud=flipud(Xout);
AoutFlipud=flipud(Aout);
YoutFlipud=flipud(Yout);
indAClusterFlip=flipud(indACluster(:));


if option.standardize
    h1=HeatMap(XoutFlipud,'Symmetric',false,'Standardize','row','Colormap', option.colormap,'RowLabels',indAClusterFlip,'ColumnLabels',indYCluster);
    h2=HeatMap(AoutFlipud,'Symmetric',false,'Standardize','row','Colormap', option.colormap,'RowLabels',indAClusterFlip,'ColumnLabels',[1:k]);
    h3=HeatMap(YoutFlipud,'Symmetric',false,'Standardize','column','Colormap', option.colormap,'RowLabels',[k:-1:1],'ColumnLabels',indYCluster);
else
    h1=HeatMap(XoutFlipud,'Symmetric',false,'Colormap', option.colormap,'RowLabels',indAClusterFlip,'ColumnLabels',indYCluster);
    h2=HeatMap(AoutFlipud,'Symmetric',false,'Colormap', option.colormap,'RowLabels',indAClusterFlip,'ColumnLabels',[1:k]);
    h3=HeatMap(YoutFlipud,'Symmetric',false,'Colormap', option.colormap,'RowLabels',[k:-1:1],'ColumnLabels',indYCluster);
end
scrsz = get(0,'ScreenSize');
figWidth=0.9*scrsz(3);
figHeight=0.95*scrsz(4);
hFig=figure('Name','HeatMap for NMF',...
'NumberTitle','on',...
'Visible','on',...
'OuterPosition',[0 0 figWidth figHeight],...
'MenuBar','figure',...
'ToolBar','figure',...
'PaperPositionMode','auto');%,...
%'PaperOrientation','landscape',...
%'PaperType','tabloid');
set(hFig,'DefaultAxesUnits','pixels',...
    'DefaultAxesXLim',[1,300],...
    'DefaultAxesYLim',[1,300],...
    'DefaultAxesXGrid','off',...
    'DefaultAxesYGrid','off'); 

%set(hFig,'Units','pixels');
set(0,'CurrentFigure',hFig);
plot(h1,hFig);
plot(h2,hFig);
plot(h3,hFig);
cs=get(hFig,'Children');
left=0.05;
bottom=0.1;
width=0.3;
height=0.8;
set(cs(2),'Position',[left+0.6,bottom+0.4,width,width-0.05]); % [left,bottom,width,height]
if optionDefault.colorbar
    colorbar('peer',cs(2),'location','EastOutside');
end
set(cs(4),'Position',[left+0.35,bottom,width-0.05,height]);
if optionDefault.colorbar
    colorbar('peer',cs(4),'location','EastOutside');
end
set(cs(6),'Position',[left,bottom,width,height]);
if optionDefault.colorbar
    colorbar('peer',cs(6),'location','EastOutside');
end

switch option.saveFormat
    case 'eps'
        format='-depsc2';
    case 'png'
        format='-dpng';
    case 'jpeg'
        format='-djpg';
    case 'pdf'
        format='-dpdf';
end

folder='./savedHeatMap';
subfolder=datestr(now,'yyyy_mmm_dd_HH_MM_SS');
saveDir=[folder,'/',subfolder];
mkdir(saveDir);
saveFileName=['NMFBicHeatMap','.',option.saveFormat];
saveFileNameDir=[saveDir,'/',saveFileName];
print(hFig,format,'-r300',saveFileNameDir);
end

