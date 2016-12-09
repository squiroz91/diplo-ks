#Tunning del kernel de linux para Beaglebone

##¿Cómo configurar el kernel para que soporte la plataforma Beaglebone Black?
Para compilar el kernel de linux para beaglebone y sus módulos se necesita agregar la varaible de ambiente:
__export PATH=<sdk path>/linux-devkit/sysroot/x86_64-arago-linux/usr/bin:$PATH__

####Limpiar las fuentes del kernel
#####Antes de compilar el kernel de linux una buena práctica es asegurarse que las fuentes están limpias y no existen remanentes de builds anteriores.
#####Para hacer esto se ejecuta el siguiente comando:
#####__make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean__


##¿Qué pasos el proceso de compilación para generar el código objeto final?
####Configuración del kernel
#####Antes de compilar el kernel es necesario hacer una configuración para seleccionar cuales componentes formaran partel del kernel compilado, cuales serán compilados
como módulis y cuales quedaran fuera

#####_Configuraciones por omisión_
#####La manera más fácil de hacer la compilación es utilizando los parámetros default y luego hacer el tailoring correspodiente, para esto en el kernel escribimos:
######__make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- <defconfig>__

#####**Ajustando la configuración**
######Cuando se necesita ajustar la configuración del kernel la mánera más fácil de hacerla es utilizando la funcionalidad construida en la configuración del kernel.
######Las dos posibilidades más populares son:
######menuconfig; como la utilidad de configuración de ncurses
######Para invocarla se realiza lo siguiente:
######__make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- <config type>__
######Para el menuconfig el comando sería:
######__make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig__
######Al finalizar una ventana de configuración se abre en donde se seleccionan los componentes del kernel que se incorporarán en el build. Al salir de la configuración los cambio son guardados en un archivo en la raiz del árbol de kernel llamdo .config

####Compilando las fuentes
#####Compilando el kernell




##¿Qué opciones se activaron/desactivaron más sobresalientes para el Hardware y por qué?

