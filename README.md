<p><em><span style="font-weight: 400;">El programa permite al usuario realizar funciones con su archivo de canciones, poder clasificar su m&uacute;sica y ordenar respecto a sus gustos. Adem&aacute;s de agregar canciones nuevas y eliminarlas de la lista.</span></em></p>
A pesar de que la opción de importar canciones es la quinta en la lista, es lo primero que se debe hacer al ejecutar el programa pues cualquier otra función no se ejecutará. Se recomienda importar el archivo Canciones.csv pues se sabe que existe. 
<ul>
<li aria-level="1">
<h2><strong>&iquest;C&oacute;mo compilar y correr el programa?</strong></h2>
</li>
</ul>
<p><span style="font-weight: 400;">Para compilar el programa se deber&aacute; seguir los siguientes pasos:</span></p>
<ol>
<li><span style="font-weight: 400;"> Descargar el archivo .zip</span></li>
<li><span style="font-weight: 400;"> Descomprimir en carpeta de preferencia</span></li>
<li><span style="font-weight: 400;"> Hacer click derecho + shift en la carpeta y abrir &ldquo;PowerShell&rdquo;</span></li>
<li><span style="font-weight: 400;"> Escribir el siguiente comando para</span><strong> compilar</strong><span style="font-weight: 400;"> un .exe</span></li>
</ol>
<blockquote>
<p><em><strong>gcc *.c -o ejecutable.exe</strong></em></p>
</blockquote>
<ol start="5">
<li><span style="font-weight: 400;"> Escribir el siguiente comando para </span><strong>correr</strong><span style="font-weight: 400;"> el .exe generado</span></li>
</ol>
<blockquote>
<p><em><strong>ejecutable.exe</strong></em></p>
</blockquote>
<p>&nbsp;</p>
<ul>
<li aria-level="1">
<h2><strong>Comentarios sobre el programa y sus funciones</strong></h2>
</li>
</ul>
<p><span style="font-weight: 400;">El programa corre sin problemas en todas sus funciones, sin embargo hay consideraciones que se deben tomar en cuenta.</span></p>
<p>&nbsp;</p>
<p><span style="font-weight: 400;">La funci&oacute;n Buscar_art funciona correctamente, aunque para mejorar y que sea de manera m&aacute;s efectiva o eficiente ser&iacute;a con la creaci&oacute;n de un struct la cual almacene la cantidad de canciones que est&eacute;n en el texto que pertenezcan al mismo artista.</span></p>
<p>&nbsp;</p>
<p><span style="font-weight: 400;">La funci&oacute;n leer_agregar_main, al leer una canci&oacute;n que exist&iacute;a anteriormente no se actualiza la informaci&oacute;n sobre los g&eacute;neros.</span></p>
<p><span style="font-weight: 400;">Por ejemplo, si uno intenta volver a ingresar una canci&oacute;n que ya existe en la lista y se agregan m&aacute;s g&eacute;neros que los originales, estos no se actualizar&aacute;n.</span></p>
<p><span style="font-weight: 400;">Una posible soluci&oacute;n es la eliminaci&oacute;n de la canci&oacute;n le&iacute;da para ser guardada nuevamente con la informaci&oacute;n que corresponda.</span></p>
<p>&nbsp;</p>
<p><span style="font-weight: 400;">Otra posible mejora al programa es la implementaci&oacute;n de alguna funci&oacute;n, o modificaci&oacute;n de aquellas ya existentes, que recorra las listas y g&eacute;neros con tal de eliminar aquellas listas que posean 0 datos</span></p>
<p>&nbsp;</p>
<p><span style="font-weight: 400;">Puede que existan funciones redundantes. Explorar la posibilidad de dise&ntilde;o de funciones m&aacute;s generales que permitan su reutilizaci&oacute;n independiente del tipo de dato que ingrese. Especialmente conveniente considerando la similitud entre los structs usados a lo largo del programa.</span></p>
<ul>
<li aria-level="1">
<h2><strong>Coevaluaci&oacute;n</strong></h2>
</li>
</ul>
<p><span style="font-weight: 400;">Este punto consiste en una lista de cualidades positivas y por mejorar de cada integrante, las cuales se deber&aacute;n tener en cuenta para mejorar el trabajo en equipo en un futuro.</span></p>
<p><span style="color: #0000ff;"><span style="color: #0000ff;"><span style="color: #0000ff;"><span style="font-weight: 400;">[ + ] = Positivo</span></span></span></span></p>
<p><span style="font-weight: 400; color: #ff0000;">[ ! ] = Por mejorar.</span></p>
<p>&nbsp;</p>
<p><strong>Antonia Acevedo:</strong></p>
<p><span style="font-weight: 400; color: #ff0000;">AA[ ! ] Me hubiera gustado tiempo para mejorar la funci&oacute;n Buscar_art</span></p>
<p><span style="color: #0000ff;"><span style="font-weight: 400;">FB[ + ] Proactiva y emp&aacute;tica.</span></span></p>
<p><span style="color: #0000ff;"><span style="font-weight: 400;">AM[ + ] Muestra inter&eacute;s en el trabajo grupal, uno de los miembros m&aacute;s activos.</span></span></p>
<p><span style="color: #0000ff;"><span style="font-weight: 400;">JM[ + ] Buen desempe&ntilde;o y productividad a la hora de trabajar, preocupada por el buen funcionamiento del equipo.</span></span></p>
<p><strong>Felipe Bechan:</strong></p>
<p><span style="color: #0000ff;"><span style="font-weight: 400;">AA[ + ] Buen desempe&ntilde;o a la hora de realizar el main y aportar con ayuda cuando se necesitaba</span></span></p>
<p><span style="font-weight: 400; color: #ff0000;">FB[ ! ] Mejorar comunicaci&oacute;n con el equipo de trabajo</span></p>
<p><span style="color: #0000ff;"><span style="font-weight: 400;">AM[ + ] Buen dise&ntilde;o del men&uacute; principal</span></span></p>
<p><span style="color: #0000ff;"><span style="font-weight: 400;">JM[ + ]Aporta un buen dise&ntilde;o del men&uacute;, con claridad y orden.</span></span></p>
<p><strong>Alexandra Mendoza:</strong><span style="font-weight: 400;">&nbsp;</span></p>
<p><span style="color: #0000ff;"><span style="font-weight: 400;">AA[ + ] Dio orden al trabajo adem&aacute;s de apoyar positivamente y con la disposici&oacute;n de ayudar a todo, junto con enriquecer el c&oacute;digo.</span></span></p>
<p><span style="color: #0000ff;"><span style="font-weight: 400;">FB[ + ] L&iacute;der de grupo, proactiva, autocr&iacute;tica, emp&aacute;tica, dispuesta a ayudar a sus compa&ntilde;eros. Excelente desempe&ntilde;o&nbsp;</span></span></p>
<p><span style="color: #0000ff;"><span style="font-weight: 400;">AM[ + ] Falta de atenci&oacute;n a algunos detalles, buen desempe&ntilde;o general.</span></span></p>
<p><span style="color: #0000ff;"><span style="font-weight: 400;">JM [ + ] Excelente gu&iacute;a de grupo,adem&aacute;s de su disposici&oacute;n y entendimiento a la hora de ayudar a sus compa&ntilde;eros.</span></span></p>
<p><strong>Jorge Morgado:</strong></p>
<p><span style="color: #0000ff;"><span style="font-weight: 400;">AA[ + ] Buen desempe&ntilde;o adem&aacute;s de aportar con funciones y ayuda al resto de integrantes.</span></span></p>
<p><span style="color: #0000ff;"><span style="font-weight: 400;">FB[ + ] Buen desempe&ntilde;o en tareas asignadas, ordenado.</span></span></p>
<p><span style="color: #0000ff;"><span style="font-weight: 400;">AM[ + ] Buen dise&ntilde;o inicial de los struct, recomendar&iacute;a un poco m&aacute;s de atenci&oacute;n</span></span><span style="color: #0000ff;"><span style="font-weight: 400;"> la hora de escribir nombres de funciones y variables</span></span></p>
<p><span style="font-weight: 400; color: #ff0000;">JM[ ! ]Por Mejorar la utilizaci&oacute;n de las herramientas de trabajo.</span></p>
<p><br /><br /></p>