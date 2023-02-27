# train 文件夹用于训练，训练完成后将 train/BUILD_MODEL_SQ8BIT/modelKernels.h、train/BUILD_MODEL_SQ8BIT/modelKernels.c和train/BUILD_MODEL_SQ8BIT/model_L3_Flash_Const.dat 复制到 run/BUILD_MODEL_SQ8BIT 下

# run 用于在真机上运行代码，可以跳过训练阶段，直接使用训练好的模型运行

# firmware是固件代码，代码在 firmware/src/hello_aideck.c 中

# run/BUILD_MODEL_SQ8BIT 中的模型文件就是我们最后版本的模型
