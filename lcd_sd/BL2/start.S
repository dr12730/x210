/*
 * 文件名：	led.s	
 * 作者：	朱老师
 * 描述：	演示串口通讯
 */


.global _start					// 把_start链接属性改为外部，这样其他文件就可以看见_start了
_start:

	ldr pc, =main
	
// 汇编最后的这个死循环不能丢
	b .
	