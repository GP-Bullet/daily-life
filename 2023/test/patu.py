# -*- coding:utf8 -*-
import requests
import re
from urllib import parse
import os


class ImageSpider(object):
    def __init__(self):
        self.url = 'https://image.baidu.com/search/flip?tn=baiduimage&ie=utf-8&word={}{}'
        self.headers = {'User-Agent':'Mozilla/4.0'}
        self.word_parse = ''
        self.i = 1  #添加计数 

    # 获取图片递归函数
    def getimage(self,url,word):
        #使用 requests模块得到响应对象
        res= requests.get(url,headers=self.headers,proxies=None)
        # 更改编码格式
        res.encoding="utf-8"
        # 得到html网页
        html=res.text
        print(html)
        #正则解析
        pattern = re.compile('"hoverURL":"(.*?)"',re.S)
        img_link_list = pattern.findall(html)
        #存储图片的url链接 
        print(img_link_list)

        # 创建目录，用于保存图片
        directory = '/home/gp-bullet/Desktop/weixing/weixing'.format(word)
        # 如果目录不存在则创建新目录
        if not os.path.exists(directory):
            os.makedirs(directory)
        
        for img_link in img_link_list:
            filename = '{}{}_{}.jpg'.format(directory, word, self.i)
            self.save_image(img_link,filename)
            self.i += 1
            # 每页只能下载60张图片，这里可以直接跳出，或者按需要的数量更改
            if self.i == 4000:
                 print(self.i)
                 return
            # 也可以改成翻页下载的形式：
            # self.url = 'https://image.baidu.com/search/flip?tn=baiduimage&ie=utf-8&word={}{}'
            # 格式化地址：url = self.url.format(word_parse,'&pn=40')  #这里的pn=20*n
            if  self.i % 60 == 0:
                pn = (int)(self.i / 60 * 20)
                pagepn = '&pn=' + str(pn)
                urlnew = self.url.format(self.word_parse,pagepn)
                print(urlnew)
                self.getimage(urlnew,word)

    # 保存图片
    def save_image(self,img_link,filename):
        html = requests.get(url=img_link,headers=self.headers).content
        with open(filename,'wb') as f:
            f.write(html)
        print(filename,'下载成功')

    # 执行函数 
    def run(self):
        word = input("您想要搜索下载的图片关键词？")
        self.word_parse = parse.quote(word)
        url = self.url.format(self.word_parse,'&pn=0')
        print(url)
        self.getimage(url,word)

if __name__ == '__main__':
    spiderer = ImageSpider()
    spiderer.run()