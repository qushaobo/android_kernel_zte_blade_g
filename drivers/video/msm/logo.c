/* drivers/video/msm/logo.c
 *
 * Show Logo in RLE 565 format
 *
 * Copyright (C) 2008 Google Incorporated
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fb.h>
#include <linux/vt_kern.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>

#include <linux/irq.h>
#include <asm/system.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>

#define fb_width(fb)	(ALIGN((fb)->var.xres,32))
#define fb_height(fb)	((fb)->var.yres)
#define fb_size(fb)	((fb)->var.xres * (fb)->var.yres*4 )
#define CONFIG_FB_MSM_MIPI_DSI 1
static void memset16(void *_ptr, unsigned short val, unsigned count)
{
	unsigned short *ptr = _ptr;
	count >>= 1;
	while (count--)
		*ptr++ = val;
}

/* 565RLE image format: [count(2 bytes), rle(2 bytes)] */
int load_565rle_image(char *filename, bool bf_supported)
{
	struct fb_info *info;
	int fd, err = 0;
	unsigned count, max;
	unsigned short *data, *bits, *ptr;

	info = registered_fb[0];
	if (!info) {
		printk(KERN_WARNING "%s: Can not access framebuffer\n",
			__func__);
		return -ENODEV;
	}

	fd = sys_open(filename, O_RDONLY, 0);
	if (fd < 0) {
		printk(KERN_WARNING "%s: Can not open %s\n",
			__func__, filename);
		return -ENOENT;
	}
#ifdef CONFIG_FB_MSM_MIPI_DSI
	max = fb_width(info) * fb_height(info)*2;
#else
#ifdef CONFIG_ZTE_UART_USE_RGB_LCD_LVDS
	max = fb_width(info) * fb_height(info)*2;
#else
	max = fb_width(info) * fb_height(info);
#endif
#endif
	printk(KERN_WARNING "LUYA!!!!max=%d\n",max);
	count = (unsigned)sys_lseek(fd, (off_t)0, 2);
	printk(KERN_WARNING "LUYA!!!!count=%d\n",count);
	
	if (count == 0) {
		sys_close(fd);
		err = -EIO;
		goto err_logo_close_file;
	}
	sys_lseek(fd, (off_t)0, 0);
	data = kmalloc(count, GFP_KERNEL);
	if (!data) {
		printk(KERN_WARNING "%s: Can not alloc data\n", __func__);
		err = -ENOMEM;
		goto err_logo_close_file;
	}
	if ((unsigned)sys_read(fd, (char *)data, count) != count) {
		err = -EIO;
		goto err_logo_free_data;
	}
#ifdef CONFIG_FB_MSM_MIPI_DSI
	ptr = data+27;
#else
#ifdef CONFIG_ZTE_UART_USE_RGB_LCD_LVDS
	ptr = data+27;
#else
	ptr = data+35;
#endif
#endif
	bits = (unsigned short *)(info->screen_base);
	while (max > 0) {
//		unsigned n = ptr[0];
//		if (n > max)
//			break;
		memset16(bits, ptr[0], 1 << 1);
		bits += 1;
		max -= 1;
		
		ptr += 1;
//		count -= 1;
	}
	dma_cache_pre_ops(info->screen_base,fb_size(info),DMA_TO_DEVICE);
err_logo_free_data:
	kfree(data);
err_logo_close_file:
	sys_close(fd);
	return err;
}
EXPORT_SYMBOL(load_565rle_image);
