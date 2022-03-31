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
                 
  
 ***RECORDATORIO***
 EN AGREGAR, CUANDO LA LISTA SE CAMBIA PARA UNA CANCION, ME FALTA ELIMINAR LA CANCION DE LA LISTA ANTERIOR.
