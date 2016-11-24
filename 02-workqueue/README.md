# Creación de una Cola de Trabajo

El objetivo es crear una cola de Trabajo en Espacio de Kernel simple, y cuyo
funcionamiento pueda verse reflejado usando `printk()`.

La tarea debe de cumplir los siguientes aspectos.


* Escrita, documentada y entregada en **C**.
* Debe de ser un módulo de kernel cargable.
* Debe de ser una cola de trabajo (*workqueue*).
* Debe de ser construíble usando **GNU Make**, presentando un `Makefile`.
* Comprobar su ejecución correcta a través de un screenshot.

El código de cola de trabajo se considera independiente de máquina, por lo que
puede crearse en x86_64. Tendrá mejor calificación si usan las herramientas
de compilación cruzada y logra ejecutarse en su plataforma de hardware
embebido.

Se descartarán trabajos que estén fuera de esta carpeta, que su
configuración local de Git no esté completa, y/o que la subcarpeta no tenga
su nombre de usuario.

Fecha máxima de entrega: `2016-11-18T23:59:59-06:00`

