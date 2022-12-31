#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/display/cfb.h>
#include "cfb_font_magic5.h"

#define LOG_LEVEL LOG_LEVEL_DBG
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER( terminal_app, LOG_LEVEL_DBG);

void main(void)
{
  const struct device *dev;

  dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
  if (!device_is_ready(dev)) {
    LOG_ERR("Device %s not ready\n", dev->name);
    return;
  }
  
  if (display_set_pixel_format(dev, PIXEL_FORMAT_MONO10) != 0) {
    LOG_ERR("Failed to set required pixel format\n");
    return;
  }
  LOG_INF("Initialized %s\n", dev->name);
  
  if (cfb_framebuffer_init(dev)) {
    LOG_ERR("Framebuffer initialization failed!\n");
    return;
  }
  cfb_framebuffer_set_font(dev, 0);	      
  //cfb_framebuffer_invert(dev);
  cfb_framebuffer_clear(dev, true);
  display_blanking_off(dev);
  cfb_framebuffer_finalize(dev);
  
}

