# LED Control Release Notes

## **v0.2.1**

* Fix button debouncing time error in button driver.
* Remove checking active field in cb_read and cb_write function.

## **v0.2.0**

* Change from turn on/off led to blink led.
* Remove Apps folder and app module, call directly system function in main.c.
* Remove no use modules (sys_prot).

## **v0.1.0**

* Change to new sending/receiving method between modules (sys_data_mng).
* Add active state field in BSP LED structures.
