import requests
import os
import re

def download_images(keyword, pages):
    # 创建一个文件夹来存放图片
    path = "./" + keyword
    if not os.path.exists(path):
        os.mkdir(path)

    # 定义一个变量来记录图片的总数
    count = 0

    # 定义一个集合来存储已经下载过的图片的链接
    downloaded = set()

    # 循环每一页的链接
    for i in range(1, pages + 1):
        # 拼接搜索链接，注意替换空格为加号
        url = "https://cn.bing.com/images/async?q=" + keyword.replace(" ", "+") + "&first=" + str(i) + "&count=35&relp=35&scenario=ImageBasicHover&datsrc=N_I&layout=ColumnBased&mmasync=1"
        # 发送请求并获取响应内容
        response = requests.get(url)
        html = response.text

        # 使用正则表达式匹配图片的链接，注意转义引号和括号
        img_urls = re.findall(r"murl&quot;:&quot;(.*?)&quot;", html)

        # 循环每张图片的链接
        for img_url in img_urls:
            # 判断是否已经下载过这个链接，如果没有就执行下载操作，并将链接加入集合；如果有就跳过这个链接，不重复下载。
            if img_url not in downloaded:
                downloaded.add(img_url)
                try:
                    # 发送请求并获取图片的二进制数据，注意禁用代理服务器
                    img_data = requests.get(img_url, proxies=None).content

                    # 生成图片的文件名，并保存到指定路径下，注意使用wb模式打开文件
                    count += 1
                    filename = path + "/" + keyword + str(count) + ".jpg"
                    with open(filename, "wb") as f:
                        f.write(img_data)

                    print("成功下载第{}张图片：{}".format(count, img_url))
                except Exception as e:
                    print("下载第{}张图片失败：{}".format(count, e))
            else:
                print("跳过重复的图片：{}".format(img_url))

# 调用函数，传入关键词和页数（每页35张）
download_images("卫星", 100)