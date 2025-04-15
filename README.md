# ncmppGui

一个用C++编写的极速ncm转换工具。

从v1.2开始支持多线程解密。

多线程命令行版本见[Majjcom/ncmpp](https://github.com/Majjcom/ncmpp)。

## 使用方法

- 下载[Release](https://github.com/Majjcom/ncmppGui/releases/latest)中的软件包
- 使用压缩软件解压
- 运行`bin`目录下的`ncmppGui.exe`（此处失败，请安装同一目录下的`vc_redist.x64.exe`）
- 选择输出路径
- 拖入`ncm`文件
- 点击转换即可

## 注意

本工具解密的歌曲文件可能会吞掉音乐的封面等元数据，可以使用工具`musictag`来补全音乐元数据。

`musictag`作者博客：[https://www.cnblogs.com/vinlxc/p/11347744.html](https://www.cnblogs.com/vinlxc/p/11347744.html)

开源docker网页版：[https://github.com/xhongc/music-tag-web](https://github.com/xhongc/music-tag-web)

## ✨✨Github访问慢的请看这里！！！✨✨

- 国内蓝奏云下载：

  - [Majjcom/ncmppGui](https://majjcom.lanzouy.com/b01x26kxg)

  - 密码：dr4s

## 😊😊现在，安卓设备也可以使用啦😃😃

下载Release中的APK包，安装使用。

使用方法与PC端基本一致。

**注意，部分较新的安卓系统可能出现无法找到文件的问题，需要在设置中打开“管理所有文件”权限。**

## 构建环境

Windows 11 23H2

GUI: Qt 5.15.14

kit: msvc2022_x64