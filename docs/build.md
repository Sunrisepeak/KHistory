# KHistory: 案件检测工具的构建和调试

## 环境要求&构建工具

### Linux

**ubuntu**

```bash
sudo add-apt-repository ppa:xmake-io/xmake
sudo apt-get install g++ gdb xmake git -y
```



### Windows

> 需要分别安装如下环境

- VS(Visual Studio)和对应C++环境
- git
- xmake



## 获取KHistory源码

> 在控制台或windows命令行使用git获取工具源代码

```bash
git clone --recursive git@github.com:Sunrisepeak/KHistory.git
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

