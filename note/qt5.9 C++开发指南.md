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

QPainter主要的三个属性：

* pen(QPen对象)

  用于控制线条的颜色、宽度、线型等

* brush(QBrush对象)

  用于设置一个区域的填充特性，可以设置填充颜色、填充方式、渐变特性等，还可以采用图片做材质填充。

* font(QFont对象)

  用于绘制文字时，设置文字的字体样式、大小等属性

> 使用这3个属性基本就控制了绘图的基本特点，当然还有一些其他的功能结合使用，比如叠加模式、旋转和缩放等功能。

##### 4. 创建实例

实例`samp8_1`演示:使用`paintEvent()`事件来绘制一个矩形

```c++
QPainter painter(this);
painter.setRenderHint(QPainter::Antialiasing);		// 反走样
painter.setRenderHint(QPainter::TextAntialiasing);	// 抗锯齿

int w = this->width();
int h = this->height();
QRect rect(w/4, h/4, w/2, h/2);	// 要绘制的矩形框

// 设置画笔
QPen pen;
pen.setWidth(3);	//线宽
pen.setColor(Qt::red);	//线颜色
pen.setStyle(Qt::SolidLine);	//线的类型，实线或虚线等
pen.setCapStyle(Qt::FlatCap);	//线的端点样式
pen.setJoinStyle(Qt::BevelJoin);	//线的连接点样式
painter.setPen(pen);

// 设置画刷
QBrush brush;
brush.setColor(Qt::yellow);	// 画刷颜色
brush.setStyle(Qt::SolidPattern);	// 画刷填充样式
painter.setBrush(brush);

painter.drawRect(rect);	// 绘制图形
```

#### 8.1.2 QPen的主要功能

QPen用于绘图时，对线条进行设置。

主要包括：

* 线宽
* 颜色
* 线型 等

`表8-1`是 QPen 类的主要接口函数

> 通常一个设置函数都有一个对应的读取函数。
>
> 如 setColor() 用于设置画笔颜色，对应的读取画笔颜色的函数为 color()

![image-20230419230207300](qt5.9 C++开发指南.assets/image-20230419230207300.png)

除了线条颜色和宽度的设置，QPen影响线条的另外3个主要属性：

* 线条样式（style）
* 端点样式（capStyle）
* 连接样式（joinStyle）

**1. 线条样式**

`setStyle(Qt::PenStyle style)`

Qt 定义的几种线条样式：

<img src="qt5.9 C++开发指南.assets/image-20230419230626740.png" alt="image-20230419230626740" style="zoom:50%;" />

也可以自定义线条样式（需要用到 `setDashOffset()`和`setDashPattern()`函数）

**2. 线条端点样式**

`setCapStyle(Qt::PenCapStyle style)`

Qt dinginess的几种线条端点样式：

![image-20230419231016706](qt5.9 C++开发指南.assets/image-20230419231016706.png)

**3. 线条连接样式**

`setJoinStyle(Qt::PenJoinStyle style)`

Qt 定义的几种线条连接样式：

![image-20230419231149946](qt5.9 C++开发指南.assets/image-20230419231149946.png)

#### 8.1.3 QBrush的主要功能

QBrush 定义了 QPainter 绘图时的填充特性，包括：

* 填充颜色
* 填充样式
* 材质填充时的材质图片等

主要函数见`表 8-2`

![image-20230419232845334](qt5.9 C++开发指南.assets/image-20230419232845334.png)

**设置画刷样式**

`setStyle(Qt::BrushStyle style)` 用于设置画刷样式。

参数是`Qt::BrushStyle`枚举，该枚举类型典型的几种取值见 `表8-3`

![image-20230419233308267](qt5.9 C++开发指南.assets/image-20230419233308267.png)

渐变填充需要使用专门的类作为Brush赋值给QPainter。

下面是`Qt::BrushStyle` 几种样式填充

<img src="qt5.9 C++开发指南.assets/image-20230419233450781.png" alt="image-20230419233450781" style="zoom:50%;" />

实例：`samp8_1`

用材质图片填充一个矩形

```c++
QPainter painter(this);
painter.setRenderHint(QPainter::Antialiasing);	// 反走样
painter.setRenderHint(QPainter::TextAntialiasing);	// 抗锯齿

int w = this->width();
int h = this->height();
QRect rect(w/4, h/4, w/2, h/2);	//要绘制的矩形

QPen pen;
pen.setWidth(3);	// 线宽
pen.setColor(Qt::red);	// 线颜色
pen.setStyle(Qt::SolidLine);		// 线的类型
pen.setCapStyle(Qt::FlatCap);		// 线的端点样式
pen.setJoinStyle(Qt::BevelJoin);	// 线的连接点样式
painter.setPen(pen);

// 设置画刷
QPixmap texturePixmap(":images/images/texture.jpg");

QBrush brush;
brush.setStyle(Qt::TexturePattern); // 设置填充样式
brush.setTexture(texturePixmap); // 设置材质图片
painter.setBrush(brush);

painter.drawRect(rect);	// 绘制图形
```

#### 8.1.4 渐变填充

<font color=red>使用渐变填充需要用渐变类的对象作为Painter的brush。</font>

**有3个实现渐变填充的类：**

* `QLinearGradient`：线性渐变。指定一个起点及其颜色，终点及其颜色，还可以指定中间的某个颜色点的颜色。起点至终点之间的颜色会线性插值计算，得到线性渐变的填充颜色。
* `QRadialGradient`：有简单辐射渐变和扩展辐射渐变两种方式。简单辐射渐变是在一个圆内的一个焦点和一个端点之间生成渐变颜色，扩展辐射渐变是在一个焦点圆和一个中心圆之间生成渐变色。
* `QConicalGradient`：圆锥型渐变，围绕一个中心点逆时针生成渐变颜色。

![image-20230421202321105](qt5.9 C++开发指南.assets/image-20230421202321105.png)

**设置延展方式**

用`QGradient`类的`setSpread(QGradient::Spread methodd)`函数设置延展方式。

3种延展方式的效果：

* `PadSpread` 模式是用结束点的颜色填充外部区域，这是缺省的方式。
* `RepeatSpread` 模式是重复使用渐变方式填充外部区域。
* `ReflectSpread` 是反射式重复使用渐变方式填充外部区域。

> `setSpread()` 对圆锥形渐变不起作用

 ![image-20230421203158900](qt5.9 C++开发指南.assets/image-20230421203158900.png)

**实例：渐变效果绘图**

<img src="qt5.9 C++开发指南.assets/image-20230421221316120.png" alt="image-20230421221316120" style="zoom:33%;" />

```c++
QPainter painter(this);
int w = this->width();
int h = this->height();
QRect rect(w/4, h/4, w/2, h/2);	// 中间区域矩形框
// 径向渐变
QRadialGradient radialGrad(w/2, h/2, qMax(w/8, h/8), w/2, h/2);
radialGrad.setColorAt(0, Qt::green);
radialGrad.setColorAt(1, Qt::blue);
radialGrad.setSpread(QGradient::ReflectSpread);
painter.setBrush(radialGrad);

// 绘图
painter.drawRect(this->rect());
```

上面代码定义`QRadialGradient`对象时，使用的构造函数原先是：

```c++
QRadialGradient(qreal cx,  qreal cy, qreal radius, qreal fx, qreal fy)
```

* `(cx,cy)`是辐射填充的中心点，程序中设置为`(w/2, h/2)`，也就是Widget窗口的中心
* radius 是辐射填充区的半径，程序中设置为`qMax(w/8, h/8)`
* `(fx, fy)`是焦点坐标，程序中设置为(w/2, h/2)

#### 8.1.5 QPainter绘制基本图形元件

TODO：待完成

### 8.2 坐标系统和坐标变换

#### 8.2.1 坐标变换函数

![image-20221121091004788](qt5.9 C++开发指南.assets/image-20221121091004788.png)

* QPainter在窗口上绘图的默认坐标系统如图8-1所示，这是绘图设备的<font color=red>物理坐标</font>
* 为了绘图的方便，QPainter提供了一些坐标变换的功能，通过平移、旋转等坐标变换，得到一个<font color=red>逻辑坐标系统</font>

<font color=red>坐标变换函数</font>见表8-5：

![image-20221122143433764](qt5.9 C++开发指南.assets/image-20221122143433764.png)

* 常用的坐标变换是平移、旋转和缩放
* 使用世界坐标变换矩阵也可以实现这些变换功能，但是需要单独定义一个QTransform类的变量，对于QPainter来说，简单的坐标变换使用QPainter自由的坐标变换函数就足够了。

##### 1. 坐标平移

坐标平移函数`void tanslate(qreal dx, qreal dy)`

* 将坐标系统水平方向平移dx个单位，垂直方向移动dy个单位，在缺少的坐标系统中，单位就是像素。
* 如果是从原始状态平移(dx,dy)，那么平移后的坐标原点就移到了(dx,dy)

举例：假设一个绘图窗口的宽度为300像素，高度为200像素，则其坐标系统如图8-10左所示，若执行平移函数`translate(150,100)`，则坐标系统水平向右平移150像素，平移后的坐标系统如图8-10右所示，坐标原点在窗口的中心，而左上角的坐标变为(-150,-100)，右下角的坐标变为(150,100)。。

![image-20221122164516812](qt5.9 C++开发指南.assets/image-20221122164516812.png)

##### 2. 坐标旋转

坐标旋转`void rotate(qreal angle)`

* 将坐标系统绕坐标原点顺时针旋转angle角度，单位是度。
* angle为正 顺时针旋转，为负 逆时针旋转

示例：如上图所示，在图8-10右的基础上，若执行`rotate(90)`，则得到图8-11所示的坐标系统。在8-11的新坐标系下，窗口左上角的坐标变成了(-100,150)，而右下角的坐标变成了(100, -150)

> 注：旋转之后并不会改变窗口矩形的实际大小，只是改变了坐标轴的方向。

##### 3. 缩放

缩放函数`void scale(qreal sx, qreal sy)`

sx,sy分别为横向和纵向缩放比例，比例大于1是放大，小于1是缩小。

##### 4. 状态保持与恢复

进行坐标变换时，QPainter内部实际上有一个坐标变换矩形

* `save()`：保存当前坐标状态
* `restore()`：恢复上次保存的坐标状态

这两个函数必须配对使用，操作的是同一个堆栈对象。

* `resetTransform()`：复位所有坐标变换操作，恢复原始的坐标系统。

#### 8.2.2 坐标变换绘图示例

##### 1. 绘制3个五角星的程序

![image-20230422125751338](qt5.9 C++开发指南.assets/image-20230422125751338.png)

实例：`samp8_2`

```c++
void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);	//创建painter对象

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    //生成五角星的5个顶点，假设原点在五角星中心
    qreal r = 100;	// 半径
    const qreal Pi = 3.14159;
    qreal deg = Pi*72/180;	// 角度转成弧度：将72度转成弧度

    QPoint points[5] = {
        QPoint(r, 0),
        QPoint(r*qCos(deg), -r*qSin(deg)),
        QPoint(r*qCos(2*deg), -r*qSin(2*deg)),
        QPoint(r*qCos(3*deg), -r*qSin(3*deg)),
        QPoint(r*qCos(4*deg), -r*qSin(4*deg)),
    };

    // 设置字体
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);

    // 设置画笔
    QPen penLine;
    penLine.setWidth(2); // 线宽
    penLine.setColor(Qt::blue);	// 划线颜色
    penLine.setStyle(Qt::SolidLine); // 线的类型
    penLine.setCapStyle(Qt::FlatCap); // 线端点样式
    penLine.setJoinStyle(Qt::BevelJoin); // 线的连接点样式
    painter.setPen(penLine);

    // 设置画刷
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern); // 画刷填充样式
    painter.setBrush(brush);

    // 设计绘制五角星的PainterPath，以便重复使用
    QPainterPath starPath;
    starPath.moveTo(points[0]);
    starPath.lineTo(points[2]);
    starPath.lineTo(points[4]);
    starPath.lineTo(points[1]);
    starPath.lineTo(points[3]);
    starPath.closeSubpath();	// 闭合路径，最后一个点与第一个点相连

    starPath.addText(points[0], font, "0");
    starPath.addText(points[1], font, "1");
    starPath.addText(points[2], font, "2");
    starPath.addText(points[3], font, "3");
    starPath.addText(points[4], font, "4");

    // 绘图
    painter.save();	// 保存坐标状态
    painter.translate(100, 120); // 平移
    painter.drawPath(starPath); // 画星星
    painter.drawText(0, 0, "S1");

    painter.restore(); // 恢复上一次坐标状态

    painter.translate(300, 120); // 平移
    painter.scale(0.8, 0.8); // 缩放
    painter.rotate(90); // 顺时针旋转
    painter.drawPath(starPath); // 画星星
    painter.drawText(0, 0, "S2");

    painter.resetTransform(); // 复位所有坐标变换
    painter.translate(500, 120); // 平移
    painter.rotate(-145); // 逆时针旋转
    painter.drawPath(starPath); // 画星星
    painter.drawText(0, 0, "S3");
}
```



##### 2. 绘制五角星的PainterPath的定义

略

#### 8.2.3 视口和窗口

##### 1. 视口和窗口的定义与原理

绘图设备的物理坐标是基本的坐标系，通过QPainter的平移等变换得到更容易操作的逻辑坐标。

为了实现更方便的坐标，QPainter还提供了视口（Viewport）和窗口（Window）坐标系，通过QPainter内部的坐标变换矩阵自动转换为绘图设备的物理坐标。

* 视口

  * 表示绘图设备的任意一个矩形区域的物理坐标，可以只选取物理坐标的一个矩形区域用于绘图。
  * 默认情况下，视口等于绘图设备的整个矩形区。

* 窗口

  * <font color=red>与视口是同一个矩形</font>，只不过是用逻辑坐标定义的坐标系。

  * 窗口可以直接定义矩形区的逻辑坐标范围。

图8-13是对视口和窗口的图示说明

![image-20221122172224678](qt5.9 C++开发指南.assets/image-20221122172224678.png)

* 图8-13左图中的矩形框代表绘制设备的物理大小和坐标范围，宽度为300像素，高度为200像素

* 取其中间的一个正方形区域作为视口，灰色的正方形就是视口，绘制设备的物理坐标中，视口的左上角坐标为(50,0)，右下角坐标为(250,200)。
  * 定义此视口，使用`painter.setViewport(50,0,200,200)`
  * 表示从绘制设备物理坐标系统的起点(50,0)开始，取宽度为200、高度为200的一个矩形区域作为视口。
* 对于图8-13左图的视口所表示的正方形区域，定义一个窗口（图8-13右图），窗口坐标的中心在正方形中心，并设置正方形的逻辑边长为100。
  * 定义此窗口，使用`painter.setWindow(-50,-50,100,100)`
  * 它表示对应于视口的矩形区域，其窗口左上角的逻辑坐标是(-50,-50)，窗口宽度为100，高度为100。
  * 这里设置的窗口还是一个正方形，使得从视口到窗口变换时，长和宽的变化比例是相同的。实际可以任意指定窗口的逻辑坐标范围，长和宽的变化比例不相同也是可以的。

##### 2. 视口和窗口的使用实例

<font color=red>使用窗口坐标的优点：</font>

只需要按照窗口定义来绘图，而不用管实际的物理坐标范围的大小。

例如：在一个固定边长100的正方形窗口内绘图，当实际绘图设备大小变换时，绘制的图形会自动变换大小。这样，就可以将绘图功能与绘图设备隔离开来，使绘图功能适用于不同大小、不同类型的设备。

示例：`samp8_3`演示了使用视口和窗口的方法。

<img src="assets/image-20230423154034160.png" alt="image-20230423154034160" style="zoom:50%;" />

```c++
void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    int w = width();
    int h = height();
    int side = qMin(w, h); // 取长和宽的小值

    QRect rect((w-side)/2, (h-side)/2, side, side);  // viewport 矩形区
    painter.drawRect(rect);  // viewport大小

    painter.setViewport(rect);	// 设置 viewport
    painter.setWindow(-100, -100, 200, 200);  // 设置窗口大小，逻辑坐标

    // 设置画笔
    QPen pen;
    pen.setWidth(1); // 线宽
    pen.setColor(Qt::red); // 划线颜色
    pen.setStyle(Qt::SolidLine); // 线的类型
    pen.setCapStyle(Qt::FlatCap); // 线端点样式
    pen.setJoinStyle(Qt::BevelJoin); // 线的连接点样式
    painter.setPen(pen);

    // 线性渐变
    QLinearGradient linearGrad(0, 0, 100, 0); // 从左到右
    linearGrad.setColorAt(0, Qt::yellow); // 起点颜色
    linearGrad.setColorAt(1, Qt::green); // 终点颜色
    linearGrad.setSpread(QGradient::PadSpread);  // 扩展方式
    painter.setBrush(linearGrad);

    painter.drawEllipse(QPoint(50, 0), 50, 50);
}
```

#### 8.2.4 绘图叠加的效果

只是添加不同的填充和叠加效果，先略过。

### 8.3 Graphics View绘图架构

#### 8.3.1 场景、视图与图形项

QPainter绘图：

* 需要在绘图设备的`paintEvent()`事件里编写绘图程序，实现整个绘图过程
* 这种方法绘制的图形是位图
* 这种方法适合用于绘制复杂性不高的固定图形
* 不能实现图件的选择、编辑、拖放等功能。

Graphics View绘图架构：

* 绘制复杂的可交互图像
* 一种基于图形项（Graphics Item）的模型/视图模式
* 使用该架构可以绘制复杂的、有几万个基本图形元件的图形，并且每个图形元件是可选择、可拖放和修改的，类似于矢量绘图软件的绘图功能。

![image-20221124085902485](qt5.9 C++开发指南.assets/image-20221124085902485.png)

Graphics View架构主要由3个部分组成：

* 场景（Scene）

  场景是不可见的，是一个抽象的管理图形项的容器，可以向场景添加图形项、获取场景中的某个图形项等。场景主要具有如下一些功能：

  * 提供管理大量图形项的快速接口

  * 将事件传播给每个图形项

  * 管理每个图形项的状态，如选择状态、焦点状态等

  * 管理未经变换的渲染功能，主要用于打印

  * 其他：

    * 背景层和前景层

      通常由QBrush指定，也可以通过实现`drawBackground()`和`drawForeground()`函数来实现自定义的背景和前景，实现一些特殊效果。

* 视图（View）

  用于显示场景中的内容，可以为一个场景设置几个视图，用于对同一个数据集提供不同的视口。

  * 视图接受键盘和鼠标输入并转换为场景事件，并进行坐标转换后传送给可视场景。

* 图形项（Graphics Item）

  一些基本的图形元件，图形项的基类是QGraphicsItem。Qt提供了一些基本的图形项，如绘制椭圆的QGraphicsEllipseItem、绘制矩形的QGraphicsRectItem等。

  QGraphicsItem支持如下的一些操作：

  * 支持鼠标事件响应，包括鼠标按下、移动、释放、双击，还有鼠标的停留、滚轮、快捷菜单等事件
  * 支持键盘输入、按键事件
  * 支持拖放操作
  * 支持组合，可以是父子项关系组合，也可以是通过QGraphicsItemGroup类进行组合。
  * 支持碰撞检测

三者的关系：场景是图形项的容器，可以在场景上绘制很多图形项，每个图形项就是一个对象，视图是显示场景的一部分区域的视口，一个场景可以有多个视图，一个视图显示场景的部分区域或全部区域，或从不同角度观察场景。

#### 8.3.2 Graphics View的系统坐标

![image-20221128084802431](qt5.9 C++开发指南.assets/image-20221128084802431.png)

Graphics View系统有3个坐标系：

* 图形项坐标（Item Coordinates）

  * <font color=red>图形项坐标是局部的逻辑坐标</font>，一般以图件的中心为原点(0,0)，也是各种坐标变换的中心。
  * 图形项的鼠标事件的坐标是用局部坐标表示的，创建自定义图形项，绘制图形项时只需考虑其局部坐标，QGraphicsScene和QGraphicsView会自动进行坐标转换。
  * 一个图形项的位置是其中心点在父坐标系统中的坐标，对于没有父图形项的图形项，其父对象就是场景，图形项的位置就是在场景中的坐标。
  * 如果一个图形项还是其他图形项的父项，父项进行坐标变换时，子项也做同样的坐标变换。
  * QGraphicsItem大多数函数都是在其局部坐标系上操作的，例如图形项的边界矩形`QGraphicsItem::boundingRect()`是用局部坐标给出的，但是`QGraphicsItem::post()`是仅有的几个例外，返回的是图形项在父项坐标系中的坐标，如果是顶层图形项，就是在场景中的坐标。

* 场景坐标（Scene Coordinates）

  * <font color=red>场景的坐标等价于QPainter的逻辑坐标</font>，一般以场景的中心为原点

  * 场景是所有图形项的基础坐标，描述了每个顶层图形项的位置。

  * 创建场景时可以定义场景矩形区域的坐标范围，如`scene=new QGraphicsScene(-400, -300, 800, 600)`

    这样定义的scene是左上角坐标为(-400,-300)，宽度为800，高度为600的矩形区域，单位是像素。

  * 每个图形项在场景里都有一个位置坐标 `QGraphicsItem::scenePos()`给出

  * 图形项的边界矩形 `QGraphicsItem::sceneBoundingRect()`函数给出，边界矩形可以使`QGraphicsScene`知道场景的哪个区域发生了变化，场景发生变化会发射`QGraphicsScene::changed()`信号，参数是一个场景的矩形列表，表示发生变化的矩形区。

* 视图坐标（View Coordinates）

  * <font color=red>视图坐标与设备坐标相同（窗口界面widget的物理坐标），是物理坐标</font>，缺省以左上角为原点，单位是像素，视图坐标只与widget或视口有关，而与观察的场景无关。
  * <font color=red>所有的鼠标、拖放事件的坐标首先是由视图坐标定义的，然后用户需要将这些坐标映射为场景坐标，以便和图形项交互。</font>

**坐标映射**

坐标映射：在场景操作图形项时，进行场景到图形项、图形项到图形项，或视图到场景之间的坐标变换时比较有用的。

例如，在QGraphicsView的视口上单击鼠标时，通过函数`QGraphicsView::mapToScene()`可以将视图坐标映射为场景坐标，然后用`QGraphicsScene::itemAt()`获取场景中鼠标光标处的图形项。

#### 8.3.3 Graphics View相关的类

##### 1. QGraphics View类的主要接口函数

QGraphics View的视口坐标等于显示设备的物理坐标，但也可以对QGraphicsView的坐标进行平移、旋转、缩放等变换。

主要的函数：

![image-20221128190438069](qt5.9 C++开发指南.assets/image-20221128190438069.png)

##### 2. QGraphicsScene类的主要接口函数

QGraphicsScene的主要接口函数：

![image-20221128190550233](qt5.9 C++开发指南.assets/image-20221128190550233.png)

##### 3. 图形项

QGraphicsItem是所有图形项的基类，用户也可以从QGraphicsItem继承定义自己的图形项。

图形项的类的继承关系如下图：

![image-20221128190725661](qt5.9 C++开发指南.assets/image-20221128190725661.png)

QGraphicsItem类提供的图形项操作的函数

![image-20221128190805682](qt5.9 C++开发指南.assets/image-20221128190805682.png)

#### 8.3.4 Graphics View程序基本结构和功能实现

实例samp8_4，主要功能包括以下几点：

* 工作区是一个从QGraphicsView继承的自定义类QWGraphicsView，作为绘图的视图组件
* 创建一个QGraphicsScene场景，场景的大小就是途中的实线矩形框的大小
* 改变窗口大小，当视图大于场景时，矩形框总是居于图形视图的中央；当视图小于场景时，在视图窗口自动出现卷滚条。
* 蓝色椭圆正好处于场景的中间，红色圆形位于场景的右下角。当图形项位置不在场景的矩形框中时，图形项也是可以显示的。
* 当鼠标在窗口上移动时，会在状态栏显示当前光标位置的视图坐标和场景坐标，在某个图形项上单击鼠标时，还会显示在图形项中的局部坐标。

这个实例演示视图、场景和绘图项3个坐标系的关系，已经它们之间的坐标转换。



<img src="qt5.9 C++开发指南.assets/image-20221128191317945.png" alt="image-20221128191317945" style="zoom: 67%;" />

#### 8.3.5 Graphics View绘图程序

samp8_5：一个基于Graphics View结构的简单绘图程序，通过这个实例可以发现Graphics View图形编程更多功能的使用方法。

运行界面如下图所示：

![image-20221128192610151](qt5.9 C++开发指南.assets/image-20221128192610151.png)

其他：略



## 第9章 Qt Charts

Qt Charts可以方便地绘制常见的折线图、柱状图、饼图等图表。

本章主要介绍：

* Qt Charts的基本特点和功能
* 以画折线图为例详细说明Qt Charts各主要部件的操作方法
* 介绍各种常用图标的绘图方法
* 介绍鼠标操作图形缩放等功能的实现

> Qt 5.7以前只有商业版才有Qt Charts，5.7以后社区版本也包含了Qt Charts

### 9.1 Qt Charts概述

#### 9.1.1 Qt Charts模块

Qt Charts模块是一组易于使用的图标组件，它基于Qt的Graphics View架构，其核心组件是QChartView和QChart。

* QChartView用于显示图表的视图，其父类是QGraphicsView

* QChart的继承关系：

  ![image-20221128194402466](qt5.9 C++开发指南.assets/image-20221128194402466.png)

  * QChart是一种图形项。
  * QPolarChart是用于绘制极坐标图的图表类。

* 在项目中使用Qt Charts模块：

  * 在配置文件（.pro文件）中增加下面的一行语句

    ```c++
    Qt += charts
    ```

  * 在需要使用QtCharts的类的头文件或源程序文件中，使用包含语句

    ```c++
    #include <QtCharts>
    using namespace QtCharts;
    ```

    也可以使用宏定义

    ```c++
    #include <QtCharts>
    Qt_CHARTS_USE_NAMESPACE
    ```

#### 9.1.2 一个简单的QChart绘图程序

## 第12章 自定义插件和库

当UI设计器提供的界面组件不满足设计需求时，可以从QWidget基础自定义界面组件。

两种使用自定义界面组件的方法：

* 提升法（promotion）：
  * 提升法用于界面可视化设计时不够直观，不能在界面上即刻显示自定义组件的效果。
* 为UI设计器设计自定义界面组件的Widget插件
  * 直接按照到UI设计器的组件面板里，如同Qt自带的界面设计组件一样使用
  * 在设计时就能看到组件的实际显示效果，只是编译和运行时需要使用到插件的动态链接库（Windows平台上）

本章介绍：

* 这两种自定义Widget组件的设计和使用方法
* Qt编写和使用静态链接库和共享库（Windows平台上就是动态链接库）的方法

### 12.1 自定义Widget组件

所有界面组件的基类时QWidget，要设计自定义的界面组件，可以从QWidget继承一个自定义的类，重定义其paintEvent()事件，利用Qt的绘图功能绘制组件外观，并实现需要的其他功能。

实例：设计一个电池电量显示组件，用于电池使用或充电时显示其电量。

<img src="qt5.9 C++开发指南.assets/image-20230424223332528.png" alt="image-20230424223332528" style="zoom:50%;" />





## 第14章 网络编程

Qt网络模块提供了用于编写 TCP/IP 客户端和服务器端程序的各种类。如：

* 用于TCP通信的QTcpSocket和QTcpServer
* 用于UDP通信的QUdpSocket
* 用于实现HTTP、FTP等普通网络协议的高级类，如QNetworkRequest、QNetworkReply和QNetworkAccessManager
* 用于网络代理、网络承载管理的类
* 基于安全套接字层（Secure Sockets Layer，SSL）协议的安全网络通信的类

本章主要介绍：

* 基本的TCP和UDP网络通信类的使用
* 基于HTTP的网络下载管理的实现

要在程序中使用Qt网络模块，添加配置：

`Qt += network`

### 14.1 主机信息查询

#### 14.1.1 QHostInfo和QNetworkInterface类

QHostInfo和QNetworkInterface类可以用于查询主机的MAC地址或IP地址。

QHostInfo类主要的功能函数：

![image-20230426221423586](qt5.9 C++开发指南.assets/image-20230426221423586.png)

QNetworkInterface类的主要功能函数：

![image-20230426221540446](qt5.9 C++开发指南.assets/image-20230426221540446.png)

**实例：演示这两个类的主要功能**

`samp14_1`：创建一个窗口基于QDialog的应用程序，如下图所示

![image-20230426221806677](qt5.9 C++开发指南.assets/image-20230426221806677.png)

#### 14.1.2 QHostInfo的使用

##### 1. 显示本机地址信息

```c++
void Dialog::on_btnGetHostInfo_clicked()
{
    // QHostInfo获取主机信息
    QString hostName = QHostInfo::localHostName();	//本地主机名
    ui->plainTextEdit->appendPlainText("本地主机名：" + hostName + "\n");

    QHostInfo hostInfo = QHostInfo::fromName(hostName);

    QList<QHostAddress> addList = hostInfo.addresses();	// IP地址列表
    for(int i=0;i<addList.count(); i++){
        QHostAddress aHost = addList.at(i);	//每一项是一个QHostAddress
        bool show = ui->chkOnlyIPv4->isChecked();	//是否只显示IPv4
        if(show)
            show = (QAbstractSocket::IPv4Protocol == aHost.protocol()); //协议类型是否为IPv4
        else
            show = true;
        if(show){
            ui->plainTextEdit->appendPlainText("协议：" + protocolName(aHost.protocol())); //协议类型
            ui->plainTextEdit->appendPlainText("本机IP地址：" + aHost.toString()); //IP地址
            ui->plainTextEdit->appendPlainText("");
        }
    }
}
```

* `QHostInfo::localHostName()`获取主机名hostName，然后再使用主机名作为参数，用`QHostInfo::fromName(hostName)`获取主机的信息 hostInfo

* `QHostInfo`的方法`addresses()`返回主机的IP地址列表

  `QList<QHostAddress> addList = hostInfo.addresses()`

  `QHostAddress`类提供了一个IP地址的信息，包括IPv4地址和IPv6地址

  * `protocol()`返回`QAbstractSocket::NetworkLayerProtol`类型变量，表示当前IP地址的协议类型。

    ![image-20230505233845303](qt5.9 C++开发指南.assets/image-20230505233845303.png)

  * `toString()`返回IP地址的字符串

* 自定义了一个函数`protocolName()`，用以返回协议类型对应的名称

  ```c++
  QString Dialog::protocolName(QAbstractSocket::NetworkLayerProtocol protocol)
  {
      switch (protocol) {
          case QAbstractSocket::IPv4Protocol:
              return "IPv4 Protocol";
          case QAbstractSocket::IPv6Protocol:
              return "IPv6 Protocol";
          case QAbstractSocket::AnyIPProtocol:
              return "Any IP Protocol";
          default:
              return "Unknow Network Layer Protocol";
      }
  }
  ```

##### 2. 查找主机地址信息

QHostInfo的静态函数`lookupHost()`可以根据主机名、域名或IP地址查找主机的地址信息，`lookupHost()`函数原型如下：

```c++
int QHostInfo::lookupHost(const QString &name, QObject *receiver, const char *member)
```

* name：是表示主机名的字符串，可以是一个主机名、一个域名、或者是一个IP地址
* receiver和member指定一个响应槽函数的接收者和槽函数名称。

`lookupHost()`以异步的方式查找主机地址。

```c++
// 查找主机信息
void Dialog::on_btnLookup_clicked()
{
    QString hostname = ui->editHost->text();
    QHostInfo::lookupHost(hostname, this, SLOT(lookedUp(QHostInfo)));

}

//查找主机信息的槽函数
void Dialog::lookedUp(const QHostInfo &host)
{
    if (host.error() != QHostInfo::NoError) {
          ui->plainTextEdit->appendPlainText("Lookup failed:" + host.errorString());
          return;
      }
    QList<QHostAddress> addList = host.addresses();
    for(int i = 0; i < addList.count(); i++){
        QHostAddress aHost = addList.at(i);
        bool show = ui->chkOnlyIPv4->isChecked(); //是否只显示IPv4
        if(show)
            show = (QAbstractSocket::IPv4Protocol == aHost.protocol()); // 协议类型是否为IPVk4
        else
            show = true;
        if(show){
            ui->plainTextEdit->appendPlainText("协议：" + protocolName(aHost.protocol())); //协议类型
            ui->plainTextEdit->appendPlainText("本机IP地址：" + aHost.toString());	// IP地址
            ui->plainTextEdit->appendPlainText("");
        }
    }
}
```





## 扩展

### 1. 反走样与抗锯齿

```c++
    painter.setRenderHint(QPainter::Antialiasing);	// 开启反走样功能
    painter.setRenderHint(QPainter::TextAntialiasing); // 开启抗锯齿功能
```

反走样（Anti-Aliasing，简称AA）是处理渲染失真问题的手段，通常会与锯齿联系密切，因此也被称为“抗锯齿”。
在计算机图形学中，走样是指在显示器上绘制非水平且非垂直的直线或多边形边界时，或多或少会呈现锯齿状或台阶状外观。反走样技术是一种通过对图像进行处理来减少锯齿现象的技术。









