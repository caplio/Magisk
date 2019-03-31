#include <magisk.h>
#include <magiskpolicy.h>

static const char magiskrc[] =
"\n\n"

"on early-init\n"
"    write " EARLYINIT " 1\n"
"    wait " EARLYINITDONE "\n"
"    rm " EARLYINITDONE "\n"
"\n"

"on post-fs-data\n"
"    start logd\n"
"    load_persist_props\n"
"    rm " UNBLOCKFILE "\n"
"    start %s\n"
"    wait " UNBLOCKFILE " 10\n"
"    rm " UNBLOCKFILE "\n"
"\n"

"service %s /sbin/magisk --post-fs-data\n"
"    user root\n"
"    seclabel u:r:" SEPOL_PROC_DOMAIN ":s0\n"
"    oneshot\n"
"\n"

"service %s /sbin/magisk --service\n"
"    class late_start\n"
"    user root\n"
"    seclabel u:r:" SEPOL_PROC_DOMAIN ":s0\n"
"    oneshot\n"
"\n"
  
"on init\n"
"    chmod 666 /dev/diag\n"
"on post-fs-data\n"
"    # Modem logging collection\n"
"    mkdir /data/vendor/radio 0777 radio radio\n"
"    mkdir /data/vendor/radio/diag_logs 0777 system system\n"
"    # WLAN logging collection\n"
"    mkdir /data/vendor/wifi 0777 system system\n"
"    mkdir /data/vendor/wifi/cnss_diag 0777 system system\n"
"\n"

"on property:sys.usb.config=diag,serial_cdev,rmnet,adb && property:sys.usb.configfs=1\n"
"    start adbd\n"
"    start port-bridge\n"
"\n"

"on property:sys.usb.ffs.ready=1 && property:sys.usb.config=diag,serial_cdev,rmnet,adb && property:sys.usb.configfs=1\n"
"    write /config/usb_gadget/g1/configs/b.1/strings/0x409/configuration Default composition\n"
"    rm /config/usb_gadget/g1/configs/b.1/f1\n"
"    rm /config/usb_gadget/g1/configs/b.1/f2\n"
"    rm /config/usb_gadget/g1/configs/b.1/f3\n"
"    rm /config/usb_gadget/g1/configs/b.1/f4\n"
"    rm /config/usb_gadget/g1/configs/b.1/f5\n"
"    rm /config/usb_gadget/g1/configs/b.1/f6\n"
"    rm /config/usb_gadget/g1/configs/b.1/f7\n"
"    rm /config/usb_gadget/g1/configs/b.1/f8\n"
"    write /config/usb_gadget/g1/idVendor 0x05C6\n"
"    write /config/usb_gadget/g1/idProduct 0x9091\n"
"    symlink /config/usb_gadget/g1/functions/diag.diag /config/usb_gadget/g1/configs/b.1/f1\n"
"    symlink /config/usb_gadget/g1/functions/cser.dun.0 /config/usb_gadget/g1/configs/b.1/f2\n"
"    symlink /config/usb_gadget/g1/functions/${sys.usb.rmnet.func.name}.rmnet /config/usb_gadget/g1/configs/b.1/f3\n"
"    symlink /config/usb_gadget/g1/functions/ffs.adb /config/usb_gadget/g1/configs/b.1/f4\n"
"    write /config/usb_gadget/g1/UDC ${sys.usb.controller}\n"
"    setprop sys.usb.state ${sys.usb.config} \n"
"\n"
  
#if 0
"on property:sys.boot_completed=1\n"
"    start magisk_bc\n"
"\n"

"service magisk_bc /sbin/magisk --boot-complete\n"
"    user root\n"
"    seclabel u:r:"SEPOL_PROC_DOMAIN":s0\n"
"    oneshot\n"
;
#endif
;
