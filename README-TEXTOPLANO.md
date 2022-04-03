
A pesar de que la opción de importar canciones es la quinta en la lista, es lo primero que se debe hacer al ejecutar el programa pues cualquier otra función no se ejecutará. Se recomienda importar el archivo Canciones.csv pues se sabe que existe. 
		
El programa permite al usuario realizar funciones con su archivo de canciones, poder clasificar su música y ordenar respecto a sus gustos. Además de agregar canciones nuevas y eliminarlas de la lista.
¿Cómo compilar y correr el programa?
Para compilar el programa se deberá seguir los siguientes pasos:
1. Descargar el archivo .zip
2. Descomprimir en carpeta de preferencia
3. Hacer click derecho + shift en la carpeta y abrir “PowerShell”
4. Escribir el siguiente comando para compilar un .exe
gcc *.c -o ejecutable.exe
5. Escribir el siguiente comando para correr el .exe generado
	ejecutable.exe

Comentarios sobre el programa y sus funciones
El programa corre sin problemas en todas sus funciones, sin embargo hay consideraciones que se deben tomar en cuenta.

La función Buscar_art funciona correctamente, aunque para mejorar y que sea de manera más efectiva o eficiente sería con la creación de un struct la cual almacene la cantidad de canciones que estén en el texto que pertenezcan al mismo artista.

La función leer_agregar_main, al leer una canción que existía anteriormente no se actualiza la información sobre los géneros.
Por ejemplo, si uno intenta volver a ingresar una canción que ya existe en la lista y se agregan más géneros que los originales, estos no se actualizarán.
Una posible solución es la eliminación de la canción leída para ser guardada nuevamente con la información que corresponda.

Otra posible mejora al programa es la implementación de alguna función, o modificación de aquellas ya existentes, que recorra las listas y géneros con tal de eliminar aquellas listas que posean 0 datos

Puede que existan funciones redundantes. Explorar la posibilidad de diseño de funciones más generales que permitan su reutilización independiente del tipo de dato que ingrese. Especialmente conveniente considerando la similitud entre los structs usados a lo largo del programa.











Coevaluación
Este punto consiste en una lista de cualidades positivas y por mejorar de cada integrante, las cuales se deberán tener en cuenta para mejorar el trabajo en equipo en un futuro.

[ + ] = Positivo
[ ! ] = Por mejorar.

Antonia Acevedo:
AA[ ! ] Me hubiera gustado tiempo para mejorar la función Buscar_art
FB[ + ] Proactiva y empática.
AM[ + ] Muestra interés en el trabajo grupal, uno de los miembros más activos.
JM[ + ] Buen desempeño y productividad a la hora de trabajar, preocupada por el buen funcionamiento del equipo.
Felipe Bechan:
AA[ + ] Buen desempeño a la hora de realizar el main y aportar con ayuda cuando se necesitaba
FB[ ! ] Mejorar comunicación con el equipo de trabajo
AM[ + ] Buen diseño del menú principal
JM[ + ]Aporta un buen diseño del menú, con claridad y orden.
Alexandra Mendoza: 
AA[ + ] Dio orden al trabajo además de apoyar positivamente y con la disposición de ayudar a todo, junto con enriquecer el código.
FB[ + ] Líder de grupo, proactiva, autocrítica, empática, dispuesta a ayudar a sus compañeros. Excelente desempeño 
AM[ + ] Falta de atención a algunos detalles, buen desempeño general.
JM [ + ] Excelente guía de grupo,además de su disposición y entendimiento a la hora de ayudar a sus compañeros.

Jorge Morgado:
AA[ + ] Buen desempeño además de aportar con funciones y ayuda al resto de integrantes.
	FB[ + ] Buen desempeño en tareas asignadas, ordenado.
	AM[ + ] Buen diseño inicial de los struct, recomendaría un poco más de atención
            la hora de escribir nombres de funciones y variables
	JM[ ! ]Por Mejorar la utilización de las herramientas de trabajo.

	
