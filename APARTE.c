
// CODIGOS PARA TESTEAR

    /*
    // TEST IMPRESION DE INFORMACIONPOR GENERO
        generoC * test = (generoC *) firstList(gl_canciones->generos);
        int contador = 1;
        while (test != NULL)
        {
            printf("%d - %s\n\n", contador, test->NomGenero);
            cancion * test2 = (cancion *) firstList(test->canciones);
            int cont2 = 1;
            while(test2 != NULL)
            {
                printf("%d - %s\n",cont2, test2->nombre);
                test2 = (cancion *) nextList(test->canciones);
                cont2++;
            }
            printf("\n");
            contador++;
            test = (generoC *) nextList(gl_canciones->generos);
        }
    // TEST IMPRESION DE CANCIONES
    cancion * test = (cancion *) firstList(gl_canciones->canciones);
    while (test != NULL)
    {
        printf("%s\n\n", test->nombre);
        test = (cancion *) nextList(gl_canciones->canciones);
    }

    //TEST IMPRESION DE  LISTAS
    listaC * test = (listaC *) firstList(gl_canciones->listasExistentes);
    while (test != NULL)
    {
        printf("%s, cantidad de canciones = %d", test->NomLista, test->cantidadCan);

        cancion * test2= (cancion*)  firstList(test->canciones);
        int cont = 1;
        while (test2 != NULL){
            printf("%d.  %s, %s, %d\n",  cont, test2->nombre, test2->artista, test2->anyo);
            test2 = (cancion *) nextList(test->canciones);
            cont++;
        }
        printf("\n\n");
        test = (listaC *) nextList(gl_canciones->listasExistentes);
    }

    //TEST  INFO DE  GENEROS

    cancion * test = firstList(gl_canciones->canciones);
    test = nextList(gl_canciones->canciones);
    printf("test = %s\n\n", test->nombre);

    generoC * gen = firstList(test->generos);
    while(gen != NULL)
    {
        printf("nombre  genero : %s\n ", gen->NomGenero);
        gen = (generoC *) nextList(test->generos);
    }
        // TEST IMPRESION DE INFORMACIONPOR GENERO
        generoC * test = (generoC *) firstList(gl_canciones->generos);
        int contador = 1;
        while (test != NULL)
        {
            printf("%d - %s\n\n", contador, test->NomGenero);
            cancion * test2 = (cancion *) firstList(test->canciones);
            int cont2 = 1;
            while(test2 != NULL)
            {
                printf("%d - %s\n",cont2, test2->nombre);
                test2 = (cancion *) nextList(test->canciones);
                cont2++;
            }
            printf("\n");
            contador++;
            test = (generoC *) nextList(gl_canciones->generos);
        }*/

