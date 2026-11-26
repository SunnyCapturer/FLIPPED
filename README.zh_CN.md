> **FLIPPED 是早期的截图工具。** [官网](https://flipped.xmuli.tech/zh-cn/) · [源码](https://github.com/SunnyCapturer/FLIPPED) · [SnipArc 下载](https://sniparc.mosuzo.com/zh-cn/download)

<div align="center">
  <p>
      <h1>
      <a href="https://github.com/SunnyCapturer/FLIPPED">
          <img src="snapshot/Flipped.svg"  alt="FLIPPED" />
      </a>
      <br/>
      FLIPPED
    </h1>
    <br/>
    <h4>漂亮且简易的跨平台截图贴图的软件</h4>
  </p>
  <p align="right"><br><a href="README.md">English</a> | <a href="README.zh_CN.md">简体中文</a></p>
</div>


[TOC]

<br>

> **开发经验：** [如何开发一款截图软件呢？](https://sunny.xmuli.tech/article/how_develop_it.html)



ps：希望此项目的源码对你有参考价值，该项目的的 <font color=#D0087E size=4 face="幼圆">**⭐Star** </font>也会有收获。

<br>

## 特性

- 贴图（钉图）
- 多屏截图，延时截图，自定义截图
- 智能识别窗口矩形（Windows & Linux）
- 矩形、椭圆、箭头、画笔、马赛克、文本、序号
- 撤销、重做（多级）、保存、取消、拷贝到剪切板
- 截图框样式三套，且主题色提供自定义；屏幕十字线样式自定义
- 国际化：英文、简体中文、繁体中文；字体和字号自定义

<br>

旧版本的二进制下载：[old releases](https://github.com/SunnyCapturer/FlippedPages/releases)



## 运行预览

### 视频演示

- [P1] [FLIPPED-MACOS 运行演示](https://www.bilibili.com/video/BV1rX4y1D7EZ?p=1)
- [P2] [FLIPPED-WINDOWS 运行演示](https://www.bilibili.com/video/BV1rX4y1D7EZ?p=2)
- [P3] [FLIPPED-MACOS_WINDOWS_LINUX 运行演示](https://www.bilibili.com/video/BV1rX4y1D7EZ?p=3)

<br>

### 截图演示

**MACOS**

<img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2022/202303121457071.jpg" width="100%"/>

<img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2022/202303121524707.jpg" width="100%"/>

**WINDOWS**

<img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2022/202303121616530.jpg" width="100%"/>

<img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2022/202303121524281.jpg" width="100%"/>

**LINUX**

<img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2022/202303121447431.jpg" width="100%"/>

<br>

<font color=#D0087E size=4 face="幼圆"> **其它：** 更多截图效果可 → [在此](.\snapshot) 预览 </font>

<br>

## 快捷键

| 按键                                                         | 描述                   | 模式 |
| ------------------------------------------------------------ | ---------------------- | ---- |
| <kbd>←</kbd>, <kbd>↓</kbd>, <kbd>↑</kbd>, <kbd>→</kbd> ( <kbd>A</kbd>, <kbd>S</kbd>, <kbd>W</kbd>, <kbd>D</kbd> ) | 移动选中框位置 1 像素  | 局部 |
| <kbd>Ctrl</kbd> + <kbd>←</kbd>, <kbd>↓</kbd>, <kbd>↑</kbd>, <kbd>→</kbd> | 扩展选中框尺寸 1 像素  | 局部 |
| <kbd>Alt</kbd> + <kbd>←</kbd>, <kbd>↓</kbd>, <kbd>↑</kbd>, <kbd>→</kbd> | 收缩选中框尺寸 1 像素  | 局部 |
| <kbd>Shift</kbd> + <kbd>←</kbd>, <kbd>↓</kbd>, <kbd>↑</kbd>, <kbd>→</kbd> | 移动选中框位置 10 像素 | 局部 |
| <kbd>Shift</kbd> + <kbd>Ctrl</kbd> + <kbd>←</kbd>, <kbd>↓</kbd>, <kbd>↑</kbd>, <kbd>→</kbd> | 扩展选中框尺寸 10 像素 | 局部 |
| <kbd>Shift</kbd> + <kbd>Alt</kbd> + <kbd>←</kbd>, <kbd>↓</kbd>, <kbd>↑</kbd>, <kbd>→</kbd> | 收缩选中框尺寸 01 像素 | 局部 |
| <kbd>Esc</kbd>                                               | 退出                   | 局部 |
|                                                              |                        |      |
| <kbd>Ctrl</kbd> + <kbd>Shift</kbd>  + <kbd>A</kbd>           | 窗口智能截图           | 全局 |
| <kbd>Ctrl</kbd> + <kbd>Shift</kbd>  + <kbd>L</kbd>           | 延时截图               | 全局 |
| <kbd>Ctrl</kbd> + <kbd>Shift</kbd>  + <kbd>S</kbd>           | 全屏截图               | 全局 |

<br>

## 编译

### 依赖

- Qt >= 5.15.2
- CMake >= 3.16
- MSVC >= 2019 | MinGW >=  8.1.0 | GCC >= 9.4 | Clang >= 12.0

​	备注: 这是已经成功编译的一些版本，在更低的版本未经过测试。

<br>

### Windows

- **工具链:** Windows 10 & Qt 5.15.2 & CMake 3.24.1 & MSVC 2019 ( or MinGW 8.1.0)

- **编译步骤:**

  ```bash
  # ******************** MSVC 2019 ********************
  #『Step1』
  # x86:
  # 添加 "C:\Qt\5.15.2\msvc2019\bin" 到 path 后，终端执行 echo %PATH% 使其立即生效
  "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvarsall.bat" x86
  cmake -G "Visual Studio 16 2019" -A Win32 ..
  devenv Flipped.sln /Build "Release|Win32"
  
  # x64:
  # 添加 "C:\Qt\5.15.2\msvc2019_64\bin" 到 path 后，终端执行 echo %PATH% 使其立即生效
  "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvarsall.bat" x64
  cmake -G "Visual Studio 16 2019" -A x64 ..
  devenv Flipped.sln /Build "Release|x64"
  
  #『Step2』
  Visual Studio 2019 open `Flipped.sln`
  
  #『Step3』
  windeployqt  bin/Flipped.exe --no-translations
  
  # ******************** MinGW 8.1.0 ********************
  QtCreator opens the `CMakeLists.txt` file in the root directory of the source code
  ```

<br>

### MacOS / Linux

- **工具链:** 

  - **MacOS:** MacOS 10.15 & Qt 5.15.2 & CMake 3.24 & Clang 12.0
  - **Linux:** Ubuntu 20.04 & Qt 5.15.2 & CMake 3.24 & GCC 9.4

- **编译步骤:**

  ```bash
  git clone --recursive https://github.com/SunnyCapturer/FLIPPED.git
  cd Flipped
  mkdir build & cd build
  cmake ..
  make -j16
  ```

<br>

## 作者

[![alt text](https://img.shields.io/badge/QQ-%E5%81%95%E8%87%A7-brightgreen)](https://sighttp.qq.com/authd?IDKEY=31f3ef7312b39e2c8dc822ae2f4c3b3118e1a6f31cc83373) : 直接和我聊天~           |    [![alt text](https://img.shields.io/badge/GitHub-XMuli-brightgreen)](https://github.com/XMuli) : 查看我的主页

[![alt text](https://img.shields.io/badge/Blog-%E5%81%95%E8%87%A7%E7%9A%84%E5%B0%8F%E7%AB%99-ff69b4)](https://ifmet.cn/) : 好奇我的小窝    |    [![alt text](https://img.shields.io/badge/Blog-国内镜像-ff69b4)](https://blog.csdn.net/qq_33154343) ：浏览量 100W+

<br>

## 贡献者

若是帮助到了你，或者觉得有用，<font color=#FE7207  size=4 face="幼圆">可以点击该项目的的 <font color=#D0087E size=4 face="幼圆">**⭐Star** </font>和<font color=#D0087E size=4 face="幼圆">**🍴 Fork**</font> 的两个图标，方便抬手之间，表示点个赞，手有余香，</font>其次才是一份冰的肥宅快乐水。

<br>

<details>
    <summary> <b>当然也可以赠与一杯冰阔落[捐赠/打赏  ← 点击展开二维码]</b></summary>
  <p> - 若是此项目帮助到了你，或者觉得有用，或是想帮助此项目的发展，你也能够邀请我喝一杯杯肥仔快乐水。 - </p>
  <pre><img src="https://fastly.jsdelivr.net/gh/XMuli/xmuliPic@pic/2022/202302282339037.png" width="80%"/></pre>
</details>
<br>

## 反馈 & 贡献

非常欢迎你的加入！对于此软件有任何缺陷、建议、功能想法、都可 [提一个 Issue](https://github.com/SunnyCapturer/FLIPPED/issues) ；或者帮助此项目的完善，提交一个 Pull Request。

请遵循 [Contributor Covenant](http://contributor-covenant.org/version/1/3/0/) 行为规范。

<br>

## 版本下载

<font color=#D0087E>→ 离线安装包下载 [Releases](https://github.com/SunnyCapturer/FLIPPED/releases) ；</font>

<font color=#D0087E>→ **反馈 BUG/SUGGEST，技术交流等，和最新 Sunny 版本安装包获取，在QQ群:[418103279 ](https://qm.qq.com/cgi-bin/qm/qr?k=jsD03QzMohGZm0TqYAFh3BvKOpCGlTcT&jump_from=webapi&authKey=DMUwiCQ6ta95PoH8JmtZ+Jz9y7Ozg3yinEsxmm92rNXZRVeMPD7NRgjU+dmUI8Xu)** </font>

<br>

## 系列地址

[QtExamples](https://github.com/XMuli/QtExamples)     欢迎 `star` ⭐ 和 `fork` 🍴这个系列的 `C++ / QT / DTK` 学习，附学习由浅入深的目录

[ExCMake](https://github.com/XMuli/ExCMake)          欢迎 `star` ⭐ 和 `fork` 🍴这个系列的 `CMake` 学习，附学习由浅入深的目录

