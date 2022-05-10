from PIL import Image                            #导入PIL模块
                                                     #提供了对整幅图像进行处理的功能
                                                     #又支持对图像中单个像素点进行操作
def to_square(img_name):                          #定义函数裁剪图片为正方形
    img=Image.open(img_name)                     #打开图片文件
    width,height=img.size                        #[size函数坐标轴是以屏幕左上角为原点
                                                     #x轴向右递增，y轴像下递增]
                                                     #size属性同样返回一个字典，{‘height’:30,‘width’:30}
                                                     #height以y轴，width以x轴
                                                     #获取图片大小参数
    if width>height:                             #比较长宽数值大小确定图形为横板或者竖版
        minvalue=height                          #将较小一方赋值为minvalue（最小值）
        x,y=(width-minvalue)//2,0                #确定裁剪坐标
    else:
        minvalue=width
        x,y=0,(height-minvalue)//2
    return img.crop((x,y,minvalue+x,minvalue+y)) #x,y为左上坐标点
                                                     #minval+x，minval+y为右下坐标点
                                                     #将图片从中间裁剪为正方形
def to_zoom(oldimg,width,height):                #定义函数调整图片大小
    return oldimg.resize((width,height),Image.ANTIALIAS)
                                                 #ANTIALIAS函数-提高图片质量(抗锯齿)
img_list=[]                                      #创建空列表存放修改（裁剪缩放）过的图片
for i in range(9):
    img_list.append(to_zoom(to_square(str(i)+'.png'), 400, 400))
                                                 #[str(i)+'.png']为图片名称，读取图片
                                                     #to_square()函数裁剪图片
                                                     #to_zoom()函数缩放图片
                                                     #.append将图片存放到列表中
newimg=Image.new('RGBA',(400*3,400*3))         #创建一个新图像
                                                     #（400*3，400*3）为图片大小
                                                     #.new函数有三个变量
                                                     #.new(mode,size,color=0)
                                                     #1  1位像素，黑白图像，存成8位像素
                                                     #L  8位像素，黑白
                                                     #p  9位像素，使用调色板映射到任何其他模式
                                                     #RGB  3*8位像素，真彩
                                                     #RGBA  4*8位像素，真彩+透明通道
                                                     #CMYK  4*8位像素，印刷四色模式或彩色印刷模式
                                                     #YCbCr  3*8位像素，色彩视频格式
                                                     #I  32位整型像素
                                                     #F  33位浮点型像素
                                                     #size默认先width后height
                                                     #color不输入默认等于零（黑色）
for i in range(3):                               #双重循环嵌套（类似九九乘法表）
    for j in range(3):                               #i确定行，j确定列
        newimg.paste(img_list[i*3+j],(j*400,i*400))#.paste函数粘贴列表中图像到新建图片中
                                                         #（j*400，i*400）为被粘贴图像左上角坐标
 newimg.save (u'九宫格句子.png')                    #将新建图片保存，格式为png
                                                     #名称为‘九宫格句子’，u为中文输出前缀。
                                                     #输出英文名可删去
import matplotlib.pyplot as plt                   #plt函数用于显示图片
import matplotlib.image as mpimg                  #mpimg函数用于读取图片
                                                      #读取后格式为array
                                                      #array（数组）形式能更高效进行运算
'''import numpy as np'''                          #NumPy(Numerical Python) 是 Python 语言的一个扩展程序库
                                                      #支持大量的维度数组与矩阵运算
                                                      #此外也针对数组运算提供大量的数学函数库
                                                      #通俗说就是更简单的计算方法
lena=mpimg.imread(u'九宫格句子.png')               #读取文件‘九宫格句子’，赋值为lena
lena.shape#(512,512,3)'''                            #.shape函数用于（查看矩阵）或（数组的维度）
                                                      #可注释掉
plt.imshow(lena)                                  #plt.imshow()函数将数据转换为图像
plt.axis('off')                                   #不显示坐标轴
 plt.show                                           #显示图片