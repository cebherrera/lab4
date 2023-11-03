/*
* This include file describes the functions exported by cdcacm.c
*/
#ifndef _CDCACM_H
#define _CDCACM_H

/*
 * Definitions for functions being abstracted out
 */
void cdcacm_data_tx(usbd_device *usbd_dev, const char *data, int len);
void cdcacm_data_rx_cb(usbd_device *usbd_dev, uint8_t ep);
void setup_cdcacm(void);

#endif /* generic header protector */