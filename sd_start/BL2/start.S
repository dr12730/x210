/*
 * 文件名：  start.S
 * 作者：	朱老师
 * 描述：	演示SD卡的分散加载
 */

#define IRQ_STACK	0xD0037F80

.global _start					// 把_start链接属性改为外部，这样其他文件就可以看见_start了
_start:

	ldr pc, =main
	
// 汇编最后的这个死循环不能丢
	b .
	

.global IRQ_handle	
IRQ_handle:
	ldr sp, =IRQ_STACK
	sub lr, lr, #4
	stmfd sp!, {r0-r12, lr}
	bl irq_handler
	ldmfd sp!, {r0-r12, pc}^
