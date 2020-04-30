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