##** _Compilación cruzada_**

La compilación cruzada es la creación de binarios que van a correr en otra plataforma. Sin embargo hay que hacer una diferencia entre la plataforma en donde se hace la compilación y la plataforma _cliente_ o _host_, en donde se ejecutarán los binarios.

###Opciones de compilación

--build=_build_

El sistema en el cual se hace la compilación

--host=_host_

El sistema en el cual se ejecutarán los binarios

Cuando la opcion __--host__ es utilizada, la opción _configure_ buscará la suite adecuada para hacer la compilación cruzada. Las herramientas de compilación cruzada usan por default prefijos para seleccionar la arquitectura objetivo a compilar. Ejemplo de opciones de compilación cruzada para MinGW32, con binarios llamados i586-minGW32msvc-gcc-i586-mingw32msvc-ld,i586-mingw32msvc-as, etc.

Ejemplo de sintaxis de compilación cruzada:


