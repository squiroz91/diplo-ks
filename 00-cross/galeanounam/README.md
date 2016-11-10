Compilación cruzada
===================


La compilación de código fuente que, realizada bajo una arquitectura determinada genera código ejecutable para una arquitectura diferente se denomina **compilación cruzada**. Para realizar este tipo de compilación es necesario contar con una serie de programas y librerías que establezcan un ambiente propicio para llevar a cabo esta tarea. Este ambiente se llama *entorno de compilación cruzada*.

En el proceso de la compilación cruzada podemos definir dos tipos de sistemas: el sistema *huesped* y el sistema *objetivo*. El sistema huesped es donde se realiza la compilación del sistema y el objetivo es donde se va a ejecutar el código.

####Sistema huesped
La implementación de un entorno de compilación cruzada nos brinda la posibilidad de aprovechar los recursos que disponemos en una computadora tipo PC. El sistema huesped donde se ha llevado a la compilación cruzada tiene las siguientes características:
- Procesador: intel Atom a 1.6 GHz
- RAM: 1.5 GB
- Disco Duro: 160 GB
- OS: Peppermint OS 6

####Sistema objetivo####
El dispositivo donde vivirá el kernel será una Raspberry Pi 3 con las siguientes características:
- Procesador: Chipset Broadcom BCM2387. 1,2 GHz de cuatro núcleos ARM Cortex-A53.
- GPU. Dual Core VideoCore IV ® Multimedia Co-procesador. ...
- RAM: 1GB LPDDR2.
- Ethernet socket Ethernet 10/100 BaseT. 802.11 b / g / n LAN inalámbrica y Bluetooth 4.1 (Classic Bluetooth y LE)

####Componentes toolchain
Los componentes necesarios para implementar el entorno de compilación cruzada consisten básicamente en tres elementos:
- Compilador C: compilador de C básico.
- Libreria C: implementa las llamadas al sistema mediante API's.
- Binutils:  conjunto de programas para compilación, enlazado, ensamblado y depuraciónde código.

####Compilación del kernel
El archivo donde se configura el kernel para la plataforma deseada es **.config**. Este archivo lo podemos conseguir desde un raspbian en ejecución.

Con el archivo copiado en la raíz del directorio donde se extrajo el kernel. Ejecutamos, para cargar la configuración existente.

``
make ARCH=arm CROSS_COMPILE=/usr/bin/arm-linux-gnueabi- oldconfig
``

Configurando paquetes con menuconfig

`
make ARCH=arm CROSS_COMPILE=/usr/bin/arm-linux-gnueabi- menuconfig
`

Ejecutamos el comando

`
make ARCH=arm CROSS_COMPILE=/usr/bin/arm-linux-gnueabi- -k
` 
