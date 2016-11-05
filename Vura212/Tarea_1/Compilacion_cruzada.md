COMPILACIÓN CRUZADA

++¿Cómo conseguir un compilador cruzado?

+Un compilador cruzado es un compilador capaz de crear código ejecutable para otra plataforma a aquella
+en la que se ejecuta. Esta herramienta es útil cuando quiere compilarse código para una plataforma a la que
+no tiene acceso, o cuando es incómodo o imposible compilar como en los sistemas embebidos.

+*Host: es la máquina, arquitectura o plataforma, que se usa para compilar el codigo
+*Target: es la maquina, arquitrectura o plataforma, que será pretendido para correr el codigo

+En el proceso de compilación 'usual' las plataformas del host y el targetson iguales.
+  Por ejemplo; se usa una PC para compilar un código para en la misma PC. 
+En una compilación cruzada el host y el target con plataformas diferentes, por ejemplo;
+  quisieras compilar un programa en tu PC que tambien corra en una Raspberry pi.
+
+Compilación cruzada es el proceso que permite compilar un código que supusestamente correra en el target y
+ hacer que mientras trabaje en la arquitectura del host. Por ejemplo, se podria querer compilar un programa
+ para la raspberry (arquietctuta del target) en la laptop (arquitectuta del host).
+
+*Qué se necesita?
+Basicamente se necesitan 2 cosas:
+1.- Un tool-chain corriendo en el host, apuntando a la arquitectura del target.
+2.- El archivo del sistema del target ("sysroot").
+
+el toolchain puede ser logrado de diferentes maneras. La más fácil es indudablemente encontrar un
+ paquete .deb o .rpm para instalar en el sistema host. Por ejemplo, esto es posible cuando la arquitectura
+ del target es la raspberry y el host es tu laptop. Si un paquete binario no está disponible se necesita hacer
+ un toolchain personalizado desde scratch. En este caso, herramientas como Crosstool -ng podrían ayudar.
+El sysroot es una copia del file system de la plataforma del target. Actualmente no se necesita una copite
+ entera de del file system en el host; folder como /usr y /lib son suficientes.
+Es buena idea guardar todo en una simple lugar, se sugiere crear un folder  (por ejemplo x-compile) y
+ almacenar el toolchain y el sysroot aqui. 

++ ¿Cómo configurar el kernel para que soporte la plataforma de Hardware deseada?

+Para iniciar tomaremos como ejemplo una arquitectura ARM.
+-Bash$ y bash# son entradas de shell, no comandos
+-Host significa la máquina donde se construirá el kernel
+-Target significa la máquina para la cual se construirá el kernel.

+1.- Decidir donde contruir ek kernel
+Primeramente se necesita decidir conde construir el kernel, un buen lugar para hacerlo en en el directorio
+ $HOME. Evitese hacer la construcción del kernel en /usr/src/linux.

+2.- Decidir una versión de kernel.
+Muchas personas deciden el kernel más actual y estable. Para ayudar a identificar un kernel en particular,
+ la forma de identificarlos se muestra a continuación:

+para cualquier kernel X.Y.Z.,
+X - es el número de la versión.
+Y - aqui se muestra: indicador estable de numeros.
+    viejos numeros indican el desarrollo o la beta que pueden ser menos estable.
+Z - Este es el nivel de parche del kernel.

+Para este ejemplo usaremos el kernel ARM 2.6.6.
+Bajo el arbol del kernel ARM, puedes encontrar un sufijo para el numero de versión del kernel:
+ -rmkN o -vrsN donde N es el número del parche actual. Por ejemplo: 2.4.26-vrs1. Esto indica la versión +principal
+ del parche del kernel ARM que podría ser aplicado. 
+Algunos parche contiene el sufijo -np, esto  significa que contienen más parches que su antecesor. 
+ Esto significa que 2.4.21.rmk2-np1 esta basado en 2.4.21-rmk2 que esta basado en el kernel 2.4.21. 
+ Entonces para obtener la fuente del kernel para 2.4.21-rmk2-np1 se necesitaria la linea principal de la 
+ fuente del kernel, el parche 2.4.21-rmk2 y el parche 2.4.21-rmk2-np1.
+Si se necesitan parches extras para el mantenimiento, se tiene que ser cuidadoso al elegir un kernel.

+3.- Descargar la fuente principal del kernel
+ Se necesita buscar el parche para la arquitectura, en el caso de la Raspberry sería para una arquitectura ARM.
+ A continuación buscamos un kernel de kernel.org.
+Una vez que se ha seleccionado el kernel estable descatgamos los archivo linux y sus parches:
+ linux-4.8.6.tar.xz
+ linux-4.8.6.tar.sign
+ patch-4.8.5-6.xz
+ patch-4.8.6.xz

+ Estos serán almacenados en el directorio $HOME.

+4.- Desempaquetando la fuente del kernel
+ Para desempaquetar usaremos:
+ cd /home
+ tar Jvxf linux-4.8.6.tar.xz
+Esto creará una carpeta llamada linux-4.8.6. Accesaremos a esta carpeta y ejecutaremos el comando
+
+make
+
+A continuación en la ventana que sale daremos guardar y salir.
+Para hacer la compilación cruzada se instalará el sidg programa:

+sudo apt-get install gcc-arm-linux-gnueabi make ncurses-dev

+Al terminar el proceso se debe usarse el sig comando 

+make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2709_defconfig

+y para cargar modulos se usa el comando

+make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs

++¿COMO ARRANCAR EL NUEVO KERNEL?
+Los modulos del kernel deben estar instalados dentro del directorio /lib/modules/x.y.z del systema del target.
+Para instalarlo debemos escribir el sig comando

+make modules_install INSTALL_MOD_PATH=$TARGETDIR

+el kernel estará disponible en $HOME/arch/arm/boot/zImage y la informacion simbolica del kernel en $HOME/linux+/System.map.
+En caso de falla deberá revisar /var/log/messages o /var/log/dmesg y en casos extremos reconfigurar y recompilar el kernel.

++Referencias:
+https://www.raspberrypi.org/documentation/linux/kernel/building.md
+http://gumstix.org/basic-cross-compilation.html
+https://www.alexisabarca.com/2013/05/compilar-kernel-para-raspberry-pi/
