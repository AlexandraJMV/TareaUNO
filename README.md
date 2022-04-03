**>Problemas**:

  Arreglado el tema de sensibilidad a mayusculas, minusculas y espacios a traves de la implementacion de la funcion 
  formato, que copia la cadena en otra sin espacios y con todos sus caracteres en mayuscula. 
  
  Las funciones Eliminar cancion y agregar cancion deberian ser totalmente funcionales.
  
  Importar canciones es totalmente funcional, ARREGLADA la lectura erronea de la primera cancion (a traves del uso de 3 fgetchar)

  La funcion ue se encargar de agregar canciones, si lee una cancion que ya existe (En cuanto a nombre, artista y anyo)
  y generos NUEVOS, no le asigna estos nuevos generos a la cancion.
  Lo mejor seria sobreescribir la cancion (Eliminar y volver a agregar)

  **Como ejecutar:**
    >Descargar archivos del programa,  puede almacenarlos en una carpeta o en el escritorio, siempre y cuando todos
    se guarden en un mismo lugar.

    >En el simbolodel sistema acceder a la direccion en donde se encuentran los archivvos del programa
    Por ejemplo:
                cd Desktop/
                cd Carpeta-Tarea/ <-- Aqui estan los archivos.
    
    > Finalmente se escribe
                gcc *.c -o nombre_del_ejecutable.exe
    y se ejecuta el programa. :)
    
  ***OBSERVACIONES PARA FUTUROS REFINAMIENTOS***  
  
    > Borrar listas de reproduccion que tengan 0 canciones
    > Borrar generos que tengan 0 canciones
    > La cancion  YOU BELONG WITH ME de Taylor Swift se guarda mal.