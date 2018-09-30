# Map reader

Se usará un archivo que contenga los siguientes atributos por cada obstáculo a dibujar:  
`TIME OBSTACLE_TYPE LEFT BOTTOM WIDTH HEIGHT`  
Si el obstáculo ya tiene un tamaño (W x H) definido:  
`TIME OBSTACLE_TYPE LEFT BOTTOM `

Donde:  
* `TIME`: indica en qué momento se dibujará el obstáculo.
* `OBSTACLE_TYPE`: el tipo del obstáculo.
* El resto son la posición y tamaño del obstáculo.

`TIME` se multiplicará por el tiempo que el obstáculo se demora en desplazarse un cuadrado (`UNIT_WIDTH`), que se calcula de la siguiente forma:  

`T = U_w / Vx`  

Donde:
* `U_w`: `UNIT_WIDTH`.
* `Vx`: velocidad del obstáculo.

De esta forma los obstáculos pueden ubicarse en el grid de manera sencilla.

## Aún más fácil

`OBSTACLE_TYPE LEFT BOTTOM WIDTH HEIGHT`  
Si el obstáculo ya tiene un tamaño (W x H) definido:  
`OBSTACLE_TYPE LEFT BOTTOM `

