#define START_BLK_ADDR  (45)
#define SD_BLOCK_CNT    (32)
#define DDR_ADDR        (0x23E00000)

extern void led1(void);
extern void led2(void);
extern void led3(void);
extern void led_blink(void);

typedef unsigned int bool;

// 通道号：0，或者2
// 开始扇区号：45
// 读取扇区个数：32
// 读取后放入内存地址：0x23E00000
// with_init：0
typedef bool(*pCopySDMMCtoMem)(int, unsigned int, unsigned short, unsigned int*, bool);
typedef void (*pFunc)(void);

// 从SD卡第45扇区开始，复制32个扇区内容到DDR的0x23E00000，然后跳转到23E00000去执行
void copy_2_ddr(void)
{
    pCopySDMMCtoMem pCopy2ddr = (pCopySDMMCtoMem)(*(unsigned int *)0xD0037F98);
    pFunc pBl2Main = (pFunc)DDR_ADDR;

    // 第一步，读取SD卡扇区到DDR中
    (*pCopy2ddr)(2, START_BLK_ADDR, SD_BLOCK_CNT, (unsigned int *)DDR_ADDR, 0);
    // 第二步，跳转到DDR中的BL2去执行
    (*pBl2Main)();
}