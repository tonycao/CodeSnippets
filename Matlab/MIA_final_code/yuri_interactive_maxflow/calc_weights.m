function T=calc_weights(im,fg,bg,K,lambda)
% im-> input image
% fg-> foreground pixel locations in row matrixes Mx2
% bg-> background pixel locations in row matrixes Nx2
[height,width] = size(im);
N=height*width;
T=zeros(N,2);
fgx=fg(:,1);% Foreground or object pixels
fgy=fg(:,2);
bgx=bg(:,1);% Background pixels
bgy=bg(:,2);
for i = 1:size(fgx,1)
    obj_pixels(i)=im(fgx(i),fgy(i));% Extract values of foreground pixels
end

for i = 1:size(bgx,1)
    bkg_pixels(i)=im(bgx(i),bgy(i));% Extract values of Background pixels
end

n_obj=hist(obj_pixels,0:255);% Form Histogram
n_obj=n_obj./max(n_obj);% Calculate probability of object pixels

n_bkg=hist(bkg_pixels,0:255);
n_bkg=n_bkg./max(n_bkg);% Calculate probability of background pixels
count=1;
% S terminal(Object)
for i = 1 : width
    for j = 1 : height
        if(size(find(fgx==j),1)&&size(find(fgy==i),1))% Check for foreground pixels
            T(count,1)=K;
        else if(size(find(bgx==j),1)&&size(find(bgy==i),1))% Check for background pixels
                T(count,1)=0;
            else
                 T(count,1)=-lambda*log(n_bkg(im(j,i)+1)); % Else
            end
        end

        count=count+1;
    end
end


count=1;
% T terminal(Background)
for i = 1 : width
    for j = 1 : height
        if(size(find(fgx==j),1)&&size(find(fgy==i),1))
            T(count,2)=0;
        else if(size(find(bgx==j),1)&&size(find(bgy==i),1))
                T(count,2)=K;
            else
                 T(count,2)=-lambda*log(n_obj(im(j,i)+1));
            end
        end

        count=count+1;
    end
end



T=sparse(T);
end