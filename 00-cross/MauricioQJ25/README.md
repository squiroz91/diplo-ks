Compilacion Cruzada para Raspberry Pi 3

  Nombre: Mauricio Quijada Jiménez

  El kernel o núcleo de linux se puede definir como el corazón de este sistemaoperativo. Es el encargado de que el software y el hardware de tu ordenador puedan trabajar juntos.


  El kernel se puede compilar en el embebido, sin embargo esto llevaría bastante tiempo, por lo que se compila en la pc. Al proceso de compilar para otra arquitectura se le conoce como compilación cruzada.

  Primero necesitamos un compilar, en mi caso estoy usando Ubuntu 14.04 e instalé el compilador de la siguiente manera.

sudo apt-get install gcc-arm-linux-gnueabi

   El siguiente paso es conseguir el codigo fuente del kernel de Linux, lo podemos hacer en la siguiente página *www.kernel.org* 
 
wget http://www.kernel.org/pub/linux/kernel/v3.0/linux-3.2.tar.bz2

   despues se descomprime 

tar xjf linux-3.2.tar.bz2
   
   y configuramos la arquitectura para la cual se compilará y el compilador a usar de la siguiente manera

export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabi-

   ingresamos a la carpeta
cd linux-3.2

   y se crea el archivo de configuracion (Este lo podemos exportar de una imagen de linux en ejecución en: /proc/config.gz, si este no aparece se usa "sudo modprobe configs", para visualizarlo).
   En mi caso generé el archivo de la siguiente manera

make vexpress_defconfig

   Y finalmente para compilar...

make all

   y esperamos por unos 20 o 30 minutos.

Tambien se actualizar la configuración antes de compilar de la siguiente manera:

make ARCH=arm CROSS_COMPILE=${CCPREFIX} oldconfig

y si se desea agregar o quitar características y módulos al kernel se ingresa al menú configuración

make ARCH=arm CROSS_COMPILE=${CCPREFIX} menuconfig

y para compilar los modulos

make ARCH=arm CROSS_COMPILE=${CCPREFIX} modules

-----------------------------------------------------------

Para pasar el nuevo kernel compilado a la tarjeta SD, primero se monta la tarjeta

mkdir mnt/fat32
mkdir mnt/ext4
sudo mount /dev/sdb1 mnt/fat32
sudo mount /dev/sdb2 mnt/ext4

   Despues se instalan los modulos

sudo make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
INSTALL_MOD_PATH=mnt/ext4 modules_install

   y Finalmente se copian a la tarjeta y se prueba en la Raspberry

sudo cp mnt/fat32/$KERNEL.img mnt/fat32/$KERNEL-backup.img
sudo scripts/mkknlimg arch/arm/boot/zImage mnt/fat32/$KERNEL.img
sudo cp arch/arm/boot/dts/`*.dtb mnt/fat32/
sudo cp arch/arm/boot/dts/overlays/*.dtb* mnt/fat32/overlays/
sudo cp arch/arm/boot/dts/overlays/README mnt/fat32/overlays/
sudo umount mnt/fat32
sudo umount mnt/ext4


Se consultaron las siquientes fuentes

https://www.raspberrypi.org/documentation/linux/kernel/building.md
https://balau82.wordpress.com/2012/03/31/compile-linux-kernel-3-2-for-arm-and-emulate-with-qemu/
https://www.alexisabarca.com/2013/05/compilar-kernel-para-raspberry-pi/
https://www.kernel.org/


