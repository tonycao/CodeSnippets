%% icm script

origimg = double(imread('original.jpg'));
covar   = 100;
noiseimg = blur_image(origimg, covar);

% denoising
max_diff = 200;
weight_diff = 0.02;
iterations = 10;
denoisedimg = restore_image(noiseimg, covar, max_diff, weight_diff, iterations);

figure, 
subplot(1,3,1); imshow(origimg,[]);
subplot(1,3,2); imshow(noiseimg,[]);
subplot(1,3,3); imshow(denoisedimg,[]);