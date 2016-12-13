# Optimización del Kernel

En esta tarea se optimizo el kernel para que funcione `correctamente` en la 
tarjeta de desarrollo Intel Galileo Gen2.

El proceso por el cual se paso al intentar tener un kernel que ademas de ocupar
menos espacio, arrancara de una manera mas rapida fue dificil ya que en el proceso
me di cuenta que el kernel que estaba usando en las practicas anteriores que aunque
podia arrancar la plataforma no funcionaba del todo bien, sobre todo porque la
tarjeta necesita drivers especificos los cuales no estan presentes en esa version
de kernel la cual es `4.8.6`.

Me tarde varios dias investigando, modificando mi kernel, compilandolo y corriendolo
en la tarjeta para llegar a la conclusion de que como no existian los parches y por lo 
tanto los drivers que necesitaba, tenia que usar una version del kernel en el cual esos
problemas ya fueron solucionados por esa razon cambie a la version de kernel `3.14.28`

Sobre todo tuve problemas con el driver de un dispositivo PCAL9555A, el cual es usado
para poder acceder a los GPIOs. Por lo tanto en el directorio `/sys/class/gpio/` no
se encontraban los chips que mapeaban los GPIOs, que son esenciales para poder hacer
funcionar el proyecto en el cual se trabajo en los modulos anteriores. Ese driver fue
agregado como un parche para el kernel mencionado anteriormente entre otros para que
el kernel tenga lo necesario para reconocer el hardware.

Al kernel que se uso para ser optimizado se le modificaron varias cosas, entre ellas
se le cambio el memory allocator, de SLUB a SLOB esto debido a que es recomendado en
sistemas embebidos y ademas en los resultados de este articulo: 
https://www.researchgate.net/publication/273634549_An_Experimental_Comparison_Analysis_of_Kernel-level_Memory_Allocators

Que aunque la comparacion se hizo sobre los memory allocators al nivel de kernel y 
sobre una maquina con muchos recursos se considera util la informacion.

Ya que no se necesita que el kernel tenga capacidad de comunicarse mediante el cable
de red, se desactivaron esos drivers asi como los drivers de wifi. para que el kernel
generado ocupe menos espacio y tenga menos modulos que cargar. 

Tambien se le quitaron los modulos de sonido ya que no se consideran necesarios para
la aplicacion a presentar.

el kernel nuevo se compilo de la misma manera que se compilo el kernel `4.8.6`

```bash
make bzImage modules -j4
```

Pero ahora ademas de la compilacion e instalacion del kernel, se instalaron los modulos con el
siguiente comando.

```bash
make INSTALL_MOD_PATH=/mount/directory/of/the/FS/partition modules_install
```

Esto para poder levantar correctamente los modulos necesarios.

El archivo `config` contiene el archivo de configuracion del kernel generado.
