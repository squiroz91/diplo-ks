##**_Compilación cruzada_**

La compilación cruzada es la creación de binarios que van a correr en otra plataforma. Sin embargo hay que hacer una diferencia entre la plataforma en donde se hace la compilación y la plataforma _cliente_ o _host_, en donde se ejecutarán los binarios.

###Opciones de compilación (configurar el kernel para un hardware específico)

--build=_build_

El sistema en el cual se hace la compilación

--host=_host_

El sistema en el cual se ejecutarán los binarios

Cuando la opcion __--host__ es utilizada, la opción _configure_ buscará la suite adecuada para hacer la compilación cruzada. Las herramientas de compilación cruzada usan por default prefijos para seleccionar la arquitectura objetivo a compilar. Ejemplo de opciones de compilación cruzada para MinGW32, con binarios llamados i586-minGW32msvc-gcc-i586-mingw32msvc-ld,i586-mingw32msvc-as, etc.

Ejemplo de sintaxis de compilación cruzada:

~/felix/ ./configure --build i686-pc-linux-gnu --host i586-mingw32msvc
...
...
...

~/felix # make

--target=_target_

Esta opción se refiere al sistema que será creado

Por ejemplo cuando se instala el compilado, se puede utilizar la opcion --target=_target_ para especificar un compilador específico de GCC

##¿Cómo arrancar el kernel?
Cuando la compilación haya finalizado, reiniciar la computadora
En el boot loadar escoger nuevo>kernel
Revisar los mensajes de carga, si hay algún error
En caso de que el arranque falle (intentar con el kernel anterior)
En caso de éxito

[Referencia 1](www.haifux.org/lectures/88-sil/kernel-compilation.html)
[Referencia 2](https://www.gnu.org/software/automake/manual/html_node/Cross_002dCompilation.html)