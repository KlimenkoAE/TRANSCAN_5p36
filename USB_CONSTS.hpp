#pragma once
/* коды запросов */
#define GET_STATUS_DEVICE      0x8000
#define GET_STATUS_INTERF      0x8100
#define GET_STATUS_ENDPNT      0x8200
#define CLEAR_FEATURE_DEVICE   0x0001
#define CLEAR_FEATURE_INTERF   0x0101
#define CLEAR_FEATURE_ENDPNT   0x0201
#define SET_FEATURE_DEVICE     0x0003
#define SET_FEATURE_INTERF     0x0103
#define SET_FEATURE_ENDPNT     0x0203
#define SET_ADDRESS            0x0005
#define GET_DESCRIPTOR_DEVICE  0x8006
#define GET_DESCRIPTOR_INTERF  0x8106
#define GET_DESCRIPTOR_ENDPNT  0x8206
#define SET_DESCRIPTOR         0x0007
#define GET_CONFIGURATION      0x8008
#define SET_CONFIGURATION      0x0009
#define GET_INTERFACE          0x810A
#define SET_INTERFACE          0x010B
#define SYNCH_FRAME            0x820C
#define GET_REPORT             0xA101
#define SET_IDLE               0x210A
//
#define FEAT_ENDPOINT_HALT        0x0000
#define FEAT_DEVICE_REMOTE_WAKEUP 0x0001
#define FEAT_TEST_MODE            0x0002
//

/* Типы дескрипторов */
#define DESC_TYPE_DEVICE                0x01
#define DESC_TYPE_CONFIGURATION         0x02
#define DESC_TYPE_STRING                0x03
#define DESC_TYPE_INTERFACE             0x04
#define DESC_TYPE_ENDPOINT              0x05
#define DESC_TYPE_DEVICE_QUALIFIER 0x06
#define DESC_TYPE_OTHER_SPEED_CONFIGURATION 0x07
#define DESC_TYPE_INTERFACE_POWER1 0x08

#define DESC_TYPE_HID                   0x21
#define DESC_TYPE_REPORT                0x22



/* Аттрибуты устройства */
#define USB_CONFIG_BUSPOWERED     0x80
#define USB_CONFIG_SELFPOWERED    0x40
#define USB_CONFIG_REMOTEWAKEUP   0x20
/* Типы конечных точек  */
#define EP_CONTROL              0x00
#define EP_ISOCHRONOUS          0x01
#define EP_BULK                 0x02
#define EP_INTERRUPT            0x03
/*device status*/


// CDC Class Requests
#define USB_CDC_SET_LINE_CODING          0x2120
#define USB_CDC_GET_LINE_CODING          0xA121
#define USB_CDC_SET_CONTROL_LINE_STATE   0x2122



//IOCTL

#define VC_READ_BUFFER_8 0xC0D0
#define VC_WRITE_BUFFER_8 0x40D1

 

#define EP_IN(n) (0x8##n)
#define EP_OUT(n) (0x0##n)





