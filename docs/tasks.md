# Runner Game

1. Crear personaje (rectágulo) y escenario: debe tener parte frontal (en la que el personaje corre) y fondo.
2. Hacer que el escenario se mueva a una velocidad constante:
  * El fondo se mueve más lento que la parte frontal.
  * El personaje se queda en una posición fija, no se mueve.
3. Hacer que el personaje pueda saltar y agacharse, además asignar botones para que pueda protegerse y pegar.
4. Agregar obstáculos en el piso (piedras, gradas y agujeros)
  * Generación aleatoria de mapa.
  * Colisiones.
5. Agregar paredes (pueden romperse) y obstáculos estáticos que necesiten que el personaje se deslice (que se agache).
6. Agregar monedas que el personaje recoja cada vez que pase sobre ellas.
  * También agregar un power-up que le otorga al personaje la habilidad de bloquear.
  * El power-up es de un solo uso.
  * El personaje puede tener a lo mucho 3 power-ups.
7. Agregar bolas de fuego con movimiento horizontal.
  * Pueden bloquearse si se tiene un power-up disponible
  * También el personaje puede esquivarlas, saltando o deslizándose
8. Agregar texturas y sprites:
  * Textura para el fondo debe tener cierta continuidad, porque se mueve
  * El piso tiene una única textura. Las gradas que están conectadas a este existienden esta textura
  * El sprite del personaje debe mostrar:
    - Cuando corre.
    - Cuando salta.
    - Cuando se desliza.
    - Cuando golpea.
    - Cuando se protege.
9. Agregar sonidos:
  * El personaje salta.
  * El personaje recoge monedas y power-ups.
  * El personaje se desliza.
  * El personaje rompe una pared.
  * El personaje se proteje.
  * El personaje choca contra un obstáculo.
    - Choca contra pared.
    - Choca contra bola de fuego.
  * Música de fondo.
10. Mostrar Puntuación y cantidad de powerups
11. Mostrar cuánto le falta para terminar el nivel
12. Agregar dos obstáculos más
  * Un item que hace que todo se vuelva más lento y los saltos más largos, dificultando la jugabilidad.
  * ...


### Adicionales:

1. Pueden haber gradas, cuando el personaje llegue a cierta altura, la cámara se mueve hacia arriba.
  * La camara vuelve a su posición original cuando el personaje vuelve al "piso".
2. Agregar partes del mapa en el que solo hallan plataformas
  * Adicionalmente bolas de fuego aparecen y se mueven desde el lado derecho
  * Combinar esto con el punto **1.**
