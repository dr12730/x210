# x210 嵌入式系统的练习代码
- uart：实现终端的printf输出

- key_interrupt：实现外部按键中断的响应

- timer：实现定时器、看门狗、RTC时钟的中断响应

  - 其中宏 `WDT_INT`，`WDT_RESET` 和 `PWM_TIMER` 是三个实验的宏开关，每次只可打开其中一个

- sd_start：通过SD卡分散加载BL1和BL2
  - 在目录中执行`make clean`, `make`, 
  - 把 SD 卡插入 PC 端后执行`./write2sd` 
  - 再把 SD 卡插入 x210 的SD2卡槽
  - 第6 pin 脚打到左边，从SD卡启动
  - 按下POWER键即可
  - 按下 RESET 键关机

- nand 和 SD 卡：
  - 初始化
  - 读、写、擦除操作

- ADC 模数转换

- lcd

  - lcd_usb：USB 下载的 LCD 版本

    ```bash
    sudo insmod seculk.ko
    make
    sudo dnw usb_lcd.bin
    ```

  - lcd_sd： SD卡启动的 LCD 版本

    ```bash
    make
    ./write2sd
    ```



### 如何解决 Invalid module format 问题？

```bash
wilson@ubuntu:/mnt/hgfs/share_directory/adc$ sudo insmod ~/x210/dnw/src/driver/secbulk.ko
insmod: ERROR: could not insert module /home/wilson/x210/dnw/src/driver/secbulk.ko: Invalid module format
```

这是由于 linux 内核升级造成的，到 `dnw` 目录下执行 `make clean` 后再执行 `make` 即可

