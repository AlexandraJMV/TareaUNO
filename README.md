Importacion funcional.

Eliminar cancion semi funcional

**>Problemas**:

  Si cualquiera de los campos con los cales se busca la  cancion (Nombre, Artista o anyo) presenta un espacio antes
  o despues, no se detectara como la misma (A pesar que se perciba como tal). 
  De igual forma la busqueda es extremadamente sensible a Mayusculas y minusculas.

  *Soluciones*   
  
                 Funcion  que elimine espacios antes y despues de cadenas cuando se  ingrese cualquier cadena,
                 tanto al importar canciones como al realizar busquedas.
                 
                 Cadena auxiliar dentro del struct de canciones (o un auxiliar temporal al buscar) completamente en mayusculas/minusculas. 
                 Esto permitira una comparacion de cadenas sin que nos importe  tanto el detalle, agilizando la busqueda.
  
  Las funciones Eliminar cancion y agregar cancion deberian ser totalmente funcionales.
  
  Importar canciones ES totalmente funcional, ARREGLADA la  lectura erronea de la primera cancion (a traves del uso de 3 fgetchar)

  Compilar o usar algun IDE para testear, cualquier  problmea  con mis funciones me informan.
  
  ***OBSERVACIONES PARA FUTUROS REFINAMIENTOS***  
  
    > Borrar listas de reproduccion que tengan 0 canciones
    > Borrar generos que tengan 0 canciones
    > La cancion  YOU BELONG WITH ME de Taylor Swift se guarda mal.
  
