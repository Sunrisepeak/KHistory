# KHistory: 案件检测工具的构建和调试



## 环境要求&构建工具

### Linux

**ubuntu**

```bash
sudo add-apt-repository ppa:xmake-io/xmake
sudo apt-get update
sudo apt-get install g++ gdb xmake make mesa-common-dev git -y
```

### Windows

> 需要分别安装如下环境

**VS(Visual Studio)和对应C++环境**

> 其中社区版本是免费的

- 微软商店中安装
- 官网: https://visualstudio.microsoft.com/

**安装git**

- 官网: https://git-scm.com/download/win
- [安装视频](https://www.bilibili.com/video/BV1tg4y1w78v/?spm_id_from=333.999.0.0&vd_source=eac75885a69b523024571c4df766896f)

**安装xmake**

> 使用PowerShell安装xmake

```bash
Invoke-Expression (Invoke-Webrequest 'https://xmake.io/psget.text' -UseBasicParsing).Content
```



## 获取KHistory源码

> 在控制台或windows命令行使用git获取工具源代码

```bash
git clone --recursive git@github.com:Sunrisepeak/KHistory.git
```

或

```bash
git clone --recursive https://github.com/Sunrisepeak/KHistory.git
```



## 编译 & 运行

> 进入KHistory根目录, 进行编译&运行

```bash
cd KHistory
xmake
xmake r
```



## 调试

```bash
xmake f -m debug
xmake r -d
```



## 相关视频
