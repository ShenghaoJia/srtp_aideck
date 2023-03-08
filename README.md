# 快速开始
用JTAG连接AIDeck，然后在quickstart目录下运行
```shell
sudo docker run --rm -it -v $PWD:/module/data/ --device /dev/ttyUSB0 --privileged -P bitcraze/aideck /bin/bash -c 'export GAPY_OPENOCD_CABLE=interface/ftdi/olimex-arm-usb-tiny-h.cfg; source /gap_sdk/configs/ai_deck.sh; cd /module/data/;  make clean all run'
```
编译结束之后，会开始输出摄像头的识别结果。快速开始中使用的是01的拳头巴掌识别，你可以在摄像头前做出巴掌和拳头的手势，然后观察输出结果。


# 如何训练模型

## 下载数据集
可以从 [gesture_dataset](https://seunetsi.feishu.cn/file/boxcn8cqHQ8nvUAeXXJRvJkdBth) 下载数据集，下载之后将 data.npz 文件放到train文件夹下

## 清空原有模型
为了保证训练的正常进行，我们建议先将我们留在项目中的旧模型文件删掉，你可以将工作目录切至 train ，然后运行
```shell
rm -f ./model/model.h5
rm -f ./model/model.tflite
```

## 使用新数据集进行训练
在train目录运行
```shell
sudo docker run --rm -it -v $PWD:/module/data/ --device /dev/ttyUSB0 --privileged -P bitcraze/aideck /bin/bash -c 'export GAPY_OPENOCD_CABLE=interface/ftdi/olimex-arm-usb-tiny-h.cfg; source /gap_sdk/configs/ai_deck.sh; cd /module/data/;  make clean all run platform=gvsoc'
```

这一步不需要连接无人机，整个过程会在docker的虚拟容器 `platform=gvsoc` 中进行，如果一切正常的话，你会看到模型的训练过程，并且在训练结束后会识别 samples 文件夹中的图片，0代表识别为巴掌，1代表识别为拳头。

## 查看模型文件是否正常生成
如果一切正常的话，在model文件夹下会生成新的model.h5和model.tflite文件，并且在BUILD_MODEL_SQ8BIT文件夹下会有modelKernels.h、modelKernels.c和model_L3_Flash_Const.dat三个c语言模型文件。


# 如何在AIDeck上运行模型
## 将模型文件拷贝至运行目录
模型训练完成后，将 train/BUILD_MODEL_SQ8BIT/modelKernels.h、train/BUILD_MODEL_SQ8BIT/modelKernels.c 和 train/BUILD_MODEL_SQ8BIT/model_L3_Flash_Const.dat 复制到 run/BUILD_MODEL_SQ8BIT 下(如果run/BUILD_MODEL_SQ8BIT已经有旧的模型文件，需要先将其删除)

## 在AIDeck上运行
将AIDeck连接至电脑，确保摄像头和GAP8芯片可用，然后在run目录下运行
```shell
sudo docker run --rm -it -v $PWD:/module/data/ --device /dev/ttyUSB0 --privileged -P bitcraze/aideck /bin/bash -c 'export GAPY_OPENOCD_CABLE=interface/ftdi/olimex-arm-usb-tiny-h.cfg; source /gap_sdk/configs/ai_deck.sh; cd /module/data/;  make clean all run'
```

## 在无人机上查看结果
结果已经通过UART不断输入无人机，可以在无人机上进行接收和查看

## 将程序烧录至AIDeck上
在模型文件拷贝至run/BUILD_MODEL_SQ8BIT后，可以在run目录下运行
```shell
sudo docker run --rm -it -v $PWD:/module/data/ --device /dev/ttyUSB0 --privileged -P bitcraze/aideck /bin/bash -c 'export GAPY_OPENOCD_CABLE=interface/ftdi/olimex-arm-usb-tiny-h.cfg; source /gap_sdk/configs/ai_deck.sh; cd /module/data/;  make clean all image flash'
```

# 无人机固件如何烧录
## 获取完整的crazyflie固件
你可以从 [这里](https://github.com/bitcraze/crazyflie-firmware) 下载到crazyflie的无人机固件

## 将我们的固件放入完成固件中
我们提供的固件代码需要放入到完整的固件进行编译，将我们项目中的firmware文件夹拷贝至完整固件的example文件夹下(即example/firmware)，然后在firmware文件夹中运行
```shell
make
```
编译完成后，使用
```shell
make cload
```
进行烧录。

***注意***：烧录完成后无人机会自动起飞，请注意安全！

# 使用自己的数据集运行
## 准备自己的数据集
你只需要准备图片即可，要求324*244大小，分成若干个类别并放入不同的文件夹中，例如\
|- workdir\
|&emsp;- class0\
|&emsp;&emsp;- image1.jpg\
|&emsp;&emsp;- image2.jpg\
|&emsp;&emsp;...\
|&emsp;- class1\
|&emsp;&emsp;- ...

## 数据集打包
我们的项目需要指定格式的数据集，你可以使用我们提供的打包脚本 [package.py](https://github.com/ShenghaoJia/rawGestureDataset/tree/main/dataProcess) ,将代码中的 dataset 替换为你的数据集根目录，将classNum替换为你的数据类别数。运行package.py后会生成data.npz，使用其进行训练即可。

## 文件修改
需要修改一些文件，包括 train/model/train.py，train/model/save_samples.py，train/common.mk，train/Makefile，train/model/nntool_script，train/model.c，以定制自己的神经网络
