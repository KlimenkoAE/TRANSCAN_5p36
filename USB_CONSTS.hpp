#pragma once
// коды запросов провильно перевернутые значение имеет смысл конкреиного чиса в литл ендиан  
#define GET_STATUS_DEVICE      0x0008
#define GET_STATUS_INTERF      0x0081
#define GET_STATUS_ENDPNT      0x0082
#define CLEAR_FEATURE_DEVICE   0x0100
#define CLEAR_FEATURE_INTERF   0x0101
#define CLEAR_FEATURE_ENDPNT   0x0102
#define SET_FEATURE_DEVICE     0x0300
#define SET_FEATURE_INTERF     0x0301
#define SET_FEATURE_ENDPNT     0x0302
#define SET_ADDRESS            0x0500
#define GET_DESCRIPTOR_DEVICE  0x0680
#define GET_DESCRIPTOR_INTERF  0x0681
#define GET_DESCRIPTOR_ENDPNT  0x0682
#define SET_DESCRIPTOR         0x0700
#define GET_CONFIGURATION      0x0880
#define SET_CONFIGURATION      0x0900
#define GET_INTERFACE          0x0A81
#define SET_INTERFACE          0x0B01
#define SYNCH_FRAME            0x0C82
#define GET_REPORT             0x01A1
#define SET_IDLE               0x0A21
//
#define FEAT_ENDPOINT_HALT        0x0000
#define FEAT_DEVICE_REMOTE_WAKEUP 0x0100
#define FEAT_TEST_MODE            0x0200
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
#define USB_CDC_SET_LINE_CODING          0x2021
#define USB_CDC_GET_LINE_CODING          0x21A1
#define USB_CDC_SET_CONTROL_LINE_STATE   0x2221



//IOCTL

#define VC_READ_BUFFER_8 0xC0D0
#define VC_WRITE_BUFFER_8 0x40D1

 

#define EP_IN(n) (0x8##n)
#define EP_OUT(n) (0x0##n)





