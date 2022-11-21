## 第8章 绘图



本章简介：

* 界面上的各个组件都是通过绘图而得到的。

* Qt的二维绘图基本功能是通过QPainter在绘制设备上绘图实现的，通过绘制一些点、线、面等基本图形组成自己需要的图形，得到的图形是不可交互操作的图形。
  * 绘图设备包括：
    * QWidget
    * QPixmap
* Qt还提供了Graphics View框架，使用QGraphicsView、QGraphicsScense、QGraphicsItem类来绘制图形，在一个场景中可以绘制大量图件，且每个图件都是可选择、可交互的。

本章先介绍QPainter绘图的原理，再介绍Graphics View架构

### 8.1 QPainter基本绘图

#### 8.1.1 QPainter绘图系统

##### 1. QPainter与QPaintDevice

Qt的绘图系统使用户可以在屏幕或打印设备上用相同的API绘图，绘图系统基于三个类：

* QPainter

  QPainter用来进行绘图操作的类

* QPaintDevice

  一个可以使用QPainter进行绘图的抽象的二维界面

  一般的绘图设备包括QWidget、QPixmap、QImage等，这些设备为QPainter提供一个"画布"

* QPaintEngine

  给QPainter提供在不同设备上绘图的接口

  QPaintEngine类由QPainter和QPaintDevice内部使用，应用程序一般无需和QPaintEngine打交道，除非要创建自己的设备类型。

##### 2. paintEvent事件和绘图区

要在设备上绘图，只需要重新实现`paintEvent`事件并在上面编写响应代码。创建一个QPainter对象获取绘图设备的接口，然后就可以在绘图设备的"画布"上绘图了。

在`paintEvent()`事件里绘图的基本程序结构是：

```c++
void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);	//创建与绘图设备关联的QPainter对象
    ...//painter在设备的窗口上画图
}
```

QWidget的绘图区就是其窗口内部区域

![image-20221121091004788](qt5.9 C++开发指南.assets/image-20221121091004788.png)

QWidget的内部绘图区的坐标系统如图8-1所示

* 坐标系统的单位是像素
* 左上角坐标为(0,0)，向右是X轴正方向，向下是Y轴正方向
* 绘图区的宽度和高度分别由`QWidget::width()`和`QWidget::height()`函数获取。
* 这个坐标系统是QWidget绘图区的局部物理坐标，称为视口（viewport）坐标，相应的还有逻辑坐标，称为窗口（window）坐标

##### 3. QPainter绘图的主要属性





























