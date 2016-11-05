##**_Compilación cruzada_**

La compilación cruzada es la creación de binarios que van a correr en otra plataforma. Sin embargo hay que hacer una diferencia entre la plataforma en donde se hace la compilación y la plataforma _cliente_ o _host_, en donde se ejecutarán los binarios.

###¿Cómo conseguir un compilador cruzado?
Se necesitan instalar paquetes como g++, make y gawk

Para empezar se necesita tener:
C Cross compiler
C++ cross compiler
Cross-Assembler
Cross-linker


####Opciones de compilación (configurar el kernel para un hardware específico)

--build=_build_

El sistema en el cual se hace la compilación

--host=_host_

El sistema en el cual se ejecutarán los binarios

Cuando la opcion __--host__ es utilizada, la opción _configure_ buscará la suite adecuada para hacer la compilación cruzada. Las herramientas de compilación cruzada usan por default prefijos para seleccionar la arquitectura objetivo a compilar. Ejemplo de opciones de compilación cruzada para MinGW32, con binarios llamados i586-minGW32msvc-gcc-i586-mingw32msvc-ld,i586-mingw32msvc-as, etc.

###¿Cómo configurar el kernel para que soporte la plataforma de software deseado?
Extraer los fuentes

**Crear links simbólicos en el desde el directorio GCC**
Los links que se generan son:
$ ln -s ../mpfr-3.1.2 mpfr
$ ln -s ../gmp-6.0.0 gmp
$ ln -s ../mpc-1.0.2 mpc
$ ln -s ../isl-0.12.2 isl
$ ln -s ../cloog-0.18.1 cloog

Definir el directorio de instalación:
Ejemplo: /opt/cross
Definir la variable de ambiente:
$ export PATH=/opt/cross/bin:$PATH

####Configurar Binutils
$ mkdir build-binutils
$ cd build-binutils
$ ../binutils-2.24/configure --prefix=/opt/cross --target=aarch64-linux --disable-multilib
$ make -j4
$ make install
$ cd ..

Para el ejemplo se definió la arquitectura aarch64-linux

#####Headers del kernel
Aqui se installan los headers del kernel en /opt/cross/aarch64-linux/include , con lo cual se harpa posible que el sistema utiliza el toolchain para hacer llamadas al kernel Aarch

$ cd linux-3.17.2
$ make ARCH=arm64 INSTALL_HDR_PATH=/opt/cross/aarch64-linux headers_install
$ cd ..

####Configuración
__make config__
Opciones de compilación en modo texto (demasiado tardado)

__make menuconfig__
Programa tipo gráfico. Utilizarlo si no se tiene la ventana X windows funcionando

__make xconfig__
Configuración en modo gráfico

Ejemplo de sintaxis de compilación cruzada:

~/felix/ ./configure --build i686-pc-linux-gnu --host i586-mingw32msvc
...
...
...

~/felix # make

--target=_target_

Esta opción se refiere al sistema que será creado

Por ejemplo cuando se instala el compilado, se puede utilizar la opcion --target=_target_ para especificar un compilador específico de GCC

###¿Qué pasos hace el proceso de compilación para generar el código objeto final?

**Configurar los compiladores c/c++**
Invocación de compiladores
$ mkdir -p build-gcc
$ cd build-gcc
$ ../gcc-4.9.2/configure --prefix=/opt/cross --target=aarch64-linux --enable-languages=c,c++ --disable-multilib
$ make -j4 all-gcc
$ make install-gcc
$ cd ..

**Libreria C y archivos de inicio**
$ mkdir -p build-glibc
$ cd build-glibc
$ ../glibc-2.20/configure --prefix=/opt/cross/aarch64-linux --build=$MACHTYPE --host=aarch64-linux --target=aarch64-linux --with-headers=/opt/cross/aarch64-linux/include --disable-multilib libc_cv_forced_unwind=yes
$ make install-bootstrap-headers=yes install-headers
$ make -j4 csu/subdir_lib
$ install csu/crt1.o csu/crti.o csu/crtn.o /opt/cross/aarch64-linux/lib
$ aarch64-linux-gcc -nostdlib -nostartfiles -shared -x c /dev/null -o /opt/cross/aarch64-linux/lib/libc.so
$ touch /opt/cross/aarch64-linux/include/gnu/stubs.h
$ cd ..

**Librerias de apoyo**
$ cd build-gcc
$ make -j4 all-target-libgcc
$ make install-target-libgcc
$ cd ..

**Libreria C standard**
$ cd build-glibc
$ make -j4
$ make install
$ cd ..

***Libreria C++ standard**
$ cd build-gcc
$ make -j4
$ make install
$ cd .

###¿Cómo arrancar el nuevo kernel?

-Reiniciar la máquina
-En el menu seleccionar el kernel compilador

Instalando el Kernel

El proceso consta de dos partes

a) Instalar el kernel perse
b) Instalar los módulos compilados

###Pasos para instalar el kernel

Los archivos ejecutables deben estar en el directorio /boot
se debe copiar el archivo bzimage en /boot


Cuando la compilación haya finalizado, reiniciar la computadora
En el boot loadar escoger nuevo>kernel
Revisar los mensajes de carga, si hay algún error
En caso de que el arranque falle (intentar con el kernel anterior)
En caso de éxito, verificar que todo funciona (incluyendo red, tarjeta de sonido, módem, etc)
###Instalar módulos del kernel
Los módulos a ser añadidos se ubicaránen /lib/modules/<version>
Es recomendable hacer una versión de respaldo en caso de falla

###Problemas comunes en el arranque
El proceso de arranque registra todo en /var/log/messages o /var/log/dmesg
Algunas veces el problema radica en la configuración del kernel, se debe reconfigurar, y recompilar desde el inicio



[Referencia 1](http://www.haifux.org/lectures/88-sil/kernel-compilation.html)
[Referencia 2](https://www.gnu.org/software/automake/manual/html_node/Cross_002dCompilation.html)
[Referencia 3](http://www.tldp.org/HOWTO/html_single/Module-HOWTO/)
[Referencia 4](http://preshing.com/20141119/how-to-build-a-gcc-cross-compiler/)
