# Tarea 1: Compilación cruzada del kernel de linux en raspberry

## 1. ¿Cómo conseguir un compilador cruzado?
El compilador cruzado usado es el de Linaro GCC. El grupo Linaro provee un conjunto 
de herramientas de software que permiten realizar desarrollo sobre la arquitectura ARM 

[página principal](http://www.linaro.org).

Podemos manejar dos opciones:

1. Descargar el compilador de repositorio proporcionado por Raspberry:

[página del repositorio]https://github.com/raspberrypi/tools

Este repositorio contiene el compilador de Linaro con el modelo del procesador ARM 
usado en el sistema embebido

2. Construir el compilador de Linaro GCC manualmente:

Para esto se usa el software crosstool-NG que se descarga del repositorio:

[página del repositorio]https://github.com/crosstool-ng/crosstool-ng.git

## 2. ¿Cómo configurar el kernel para que soporte la plataforma de Hardware deseada?

Cuando descargamos el codigo del kernel de linux, tenemos dentro de las opciones del
Makefile la opcion ARCH, la cual se usa en la compilación cruzada para especificar
la arquitectura deseada. También se especifican las opciones del hardware mediante 
el menu de configuración, obteniendo el archivo .config.

También se puede obtener estas opciones de confguración del sitio de Raspberry. Para
el caso de la tarjeta Raspberry Pi 3 el archivo de configuracion es bcm2709_defconfig.
Entonces la ejecución del makefile es:

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2709_defconfig

## 3. ¿Qué pasos hace el proceso de compilación para generar el código objeto final?

Después de configurar las opciones para la arquitectura del procesador y su hardware
especifico, se procede a realizar la compilación del kernel para generar una imagen
`zimage`. En este proceso se usa primero el preprocesador, después el compilador para 
generar código objeto (ensamblador) y posteriormente el enlazador para unir las librerias.

Entonces la ejecución del makefile es:

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs 

El kernel de Raspberry usa árboles de dispositivos (DT - Device Tree) para admnistrar
los recursos y la carga de módulos. un DT es una descripción del hardware en un sistema, 
esto incluye el modelo del procesador, su configuración de memoria y los periféricos. Los
DT son escritos en forma textual en archivos .dts (DTS-Device Tree Source). Los módulos dtbs
contienen el formato compilado binario de los archiovs dts, donde se encuentra la información 
del hardware del sistema embebido y también son generados con la compilación cruzada.

## 4. ¿Cómo arrancar el nuevo kernel?

Una forma es copiar el kernel en la memoria SD donde se tiene instalada la imagen de Linux
que estamos usando en la Raspberry.

Insertamos la memoria SD a la PC e identificamos las particiones de boot y root. 
En la partición de root se instalan los módulos generados:

sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=mnt/ext4 modules_install

y en la partición de boot se copia la imagen generada del kernel `zimage`

Finalmente se copian los archivos dtbs.

## 5. Pruebas

En mi caso tenia una imagen mínima (image-core-minimal) generada con el proyecto Yocto con la version de kernel 4.4.23,
la cual no tenia instalada el driver para manejar el convertidor USB-serial de FTDI. Después de compilar
el kernel, se actualizó a la versión 4.4.28-v7+ y agregó ese driver faltante.

¡Si funciono la actualización del kernel en la imagen mínima generada con Yocto en la RaspberryPi 3!

