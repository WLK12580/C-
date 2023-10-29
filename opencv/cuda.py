import cv2
print(cv2.getBuildInformation())

import cv2
frame=cv2.imread('OIP-C.jpg')

#上传到gpu进行处理
gpu_frame=cv2.cuda_GpuMat()
gpu_frame.upload(frame)
print(gpu_frame.cudaPtr())

#resize
gpu_resframe=cv2.cuda.resize(gpu_frame,(1024,512))
cpu_resfram=gpu_resframe.download()
print(cpu_resfram.shape)