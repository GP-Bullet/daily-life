# 导入相关模块
import requests
import re
import os

# 定义爬取图片的函数
def crawl_baidu_images(keyword, path, num):
    # 拼接百度图片搜索的网址
    url = "https://image.baidu.com/search/flip?tn=baiduimage&ie=utf-8&word=" + keyword + "&pn="
    # 创建保存图片的文件夹
    if not os.path.exists(path):
        os.mkdir(path)
    # 循环爬取每一页的图片链接
    count = 0
    for i in range(0, num, 20):
        # 获取网页源代码
        html = requests.get(url + str(i)).text
        # 用正则表达式匹配图片链接
        pic_urls = re.findall('"objURL":"(.*?)",', html, re.S)
        # 循环下载每一张图片到指定路径
        for pic_url in pic_urls:
            try:
                pic = requests.get(pic_url, timeout=10)
                count += 1
                filename = path + "/" + keyword + str(count) + ".jpg"
                with open(filename, "wb") as f:
                    f.write(pic.content)
                    print("成功下载一张图片：" + filename)
            except Exception as e:
                print("下载失败：" + pic_url)

# 调用函数，输入关键词、路径和数量（必须是20的倍数）
crawl_baidu_images("宇宙陨石", "/home/biu/Desktop/weixing", 1000)