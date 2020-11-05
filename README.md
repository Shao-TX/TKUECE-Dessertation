# TKUECE-Dissertation : Design of three-dimensional shape simulation device combined with tactile feedback

此裝置使用許多以3D列印製作的柱體和螺桿，利用外框將柱體固定，在以馬達轉動以達成將柱體上下移動的效果。我們使用Raspberry Pi作為I2C的Master對Arduino發送資料，使柱體上升或者下降，可以依此功能將柱體上升成指定形狀，和使用者互動、給予回饋。

## Hardware

### Components

|Name|Quentity|Value|
|:---:|:----:|:----:|
|[Capacitor](https://reurl.cc/OqekoD)|6|10uF|
|[TTMotor](https://reurl.cc/EzaZDv)|36|6mm , 1:25|
|[Limit Switch](https://reurl.cc/v18gXe)|36|2A , 125V|
|[Arduino Nano v3.1](https://reurl.cc/Xk9l90)|6|~|
|[Raspberry Pi 4](https://reurl.cc/GrlbRG)|1|~|

### PCB
![PCB](hardware\PCB\Image\PCB_Image.jpg)

### Device Appearance

## Software

### Run the code :

1. Python
2. C

### UI design:

1. Pyqt5
![](software\Pyqt5\Image\Pyqt.png)

## Reference
[ShapeShifting](http://shape.stanford.edu/research/shapeShift/)