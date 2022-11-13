PAV - P3: estimación de pitch
=============================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 3](https://github.com/albino-pav/P3).
Siga las instrucciones de la [Práctica 2](https://github.com/albino-pav/P2) para realizar un `fork` de la
misma y distribuir copias locales (*clones*) del mismo a los distintos integrantes del grupo de prácticas.

Recuerde realizar el *pull request* al repositorio original una vez completada la práctica.

Ejercicios básicos
------------------

- Complete el código de los ficheros necesarios para realizar la estimación de pitch usando el programa
  `get_pitch`.

   * Complete el cálculo de la autocorrelación e inserte a continuación el código correspondiente.

   <img src="codi_autocorrelacio.png" align="center">

   * Inserte una gŕafica donde, en un *subplot*, se vea con claridad la señal temporal de un segmento de
     unos 30 ms de un fonema sonoro y su periodo de pitch; y, en otro *subplot*, se vea con claridad la
	 autocorrelación de la señal y la posición del primer máximo secundario.
  <img src="autocorrelaqció_rl001_16000-16600.png" align="center"> 
	 NOTA: es más que probable que tenga que usar Python, Octave/MATLAB u otro programa semejante para
	 hacerlo. Se valorará la utilización de la biblioteca matplotlib de Python.

   * Determine el mejor candidato para el periodo de pitch localizando el primer máximo secundario de la
     autocorrelación. Inserte a continuación el código correspondiente.

    <img src="Codi_localitzacio_primer_max_secundari_autocorrelacio.png" align="center"> 

   * Implemente la regla de decisión sonoro o sordo e inserte el código correspondiente.

    <img src="decisió_sonord_sord.png" align="center">

   * Puede serle útil seguir las instrucciones contenidas en el documento adjunto `código.pdf`.

- Una vez completados los puntos anteriores, dispondrá de una primera versión del estimador de pitch. El 
  resto del trabajo consiste, básicamente, en obtener las mejores prestaciones posibles con él.

  * Utilice el programa `wavesurfer` para analizar las condiciones apropiadas para determinar si un
    segmento es sonoro o sordo. 
	
	  - Inserte una gráfica con la estimación de pitch incorporada a `wavesurfer` y, junto a ella, los 
	    principales candidatos para determinar la sonoridad de la voz: el nivel de potencia de la señal
		(r[0]), la autocorrelación normalizada de uno (r1norm = r[1] / r[0]) y el valor de la
		autocorrelación en su máximo secundario (rmaxnorm = r[lag] / r[0]).

		Puede considerar, también, la conveniencia de usar la tasa de cruces por cero.

	    Recuerde configurar los paneles de datos para que el desplazamiento de ventana sea el adecuado, que
		en esta práctica es de 15 ms.

      En les següents gàfiques observem un tram de veu sonor d'una senyal de veu (prueba.wav) i un tram sord. En amdos casos, hem seleccionat un tram de 15 ms. 

      Gràfica tram sonor

    <img src="tram_sonor_15ms.png" align="center">

      
      Gràfica tram sord

    <img src="tram_sord_15ms.png" align="center">

      En la gràfica de d'alt de tot tenim la gràfica de l'autocorrelació. Amb aquesta, podem determinar un umbral de umaxnorm d'aproximadamtn 0.6. En la segona gràfica observem l'autocorrelació normalitzada. Podem determinar un umbral per l'autocorrelació normalitzada al voltant de l'1. A la tercera gràfica hi ha la potència, que podriem deterinar un umbral al voltant dels -40.
      
      - Use el estimador de pitch implementado en el programa `wavesurfer` en una señal de prueba y compare
	    su resultado con el obtenido por la mejor versión de su propio sistema.  Inserte una gráfica
		ilustrativa del resultado de ambos estimadores.
     
		Aunque puede usar el propio Wavesurfer para obtener la representación, se valorará
	 	el uso de alternativas de mayor calidad (particularmente Python).
  
  * Optimice los parámetros de su sistema de estimación de pitch e inserte una tabla con las tasas de error
    y el *score* TOTAL proporcionados por `pitch_evaluate` en la evaluación de la base de datos 
	`pitch_db/train`..

Ejercicios de ampliación
------------------------

- Usando la librería `docopt_cpp`, modifique el fichero `get_pitch.cpp` para incorporar los parámetros del
  estimador a los argumentos de la línea de comandos.
  
  Esta técnica le resultará especialmente útil para optimizar los parámetros del estimador. Recuerde que
  una parte importante de la evaluación recaerá en el resultado obtenido en la estimación de pitch en la
  base de datos.

  * Inserte un *pantallazo* en el que se vea el mensaje de ayuda del programa y un ejemplo de utilización
    con los argumentos añadidos.

  <img src="missatge_help_programa.png" align="center">

  Hem afegit tres paràmetres, 'upot' és per referir-nos a l'umbral per la potència, 'umaxnorm' és l'umbral per a referir-nos al màxim de l'autocorrelació normalitzada i 'unorm' és l'umbral de l'autocorrelació normalitzada en 1. Aquests umbrals ens ajuden a l'hora de determinar si un senyal és sord o sonor i així obtenir resultats millors. El que ens facilita la detecció del pitch.
  
  Exemple utilització amb els arguments afegits:

   <img src="exemple_utilització_umbrals.png" align="center">

- Implemente las técnicas que considere oportunas para optimizar las prestaciones del sistema de estimación
  de pitch.

  Entre las posibles mejoras, puede escoger una o más de las siguientes:

  * Técnicas de preprocesado: filtrado paso bajo, diezmado, *center clipping*, etc.
  
  Center clipping

  Amb aquesta tècnica fiquem a zero els trams de la senyal que es trobin entre els dos umbrals definits.

   <img src="center_clipping.png" align="center">

  * Técnicas de postprocesado: filtro de mediana, *dynamic time warping*, etc.
  
  Filtre de mitjana

  Creem un nou vector on guradarem els valors de f0 un cop la senyal hagi passat pel filtre. Amb aquest filtre agafem la mostra actual, l'anterior i la posterior i ens quedem amb el valor mig de les tres. Aquest valor el pasem al nou vector. Per tant, ens quedem amb els valors mitjos de les tres mostres (l'actual, l'anterior i la posterior).

  <img src="filtre_mediana.png" align="center">
  
  * Métodos alternativos a la autocorrelación: procesado cepstral, *average magnitude difference function*
    (AMDF), etc.
  * Optimización **demostrable** de los parámetros que gobiernan el estimador, en concreto, de los que
    gobiernan la decisión sonoro/sordo.
  * Cualquier otra técnica que se le pueda ocurrir o encuentre en la literatura.

  Encontrará más información acerca de estas técnicas en las [Transparencias del Curso](https://atenea.upc.edu/pluginfile.php/2908770/mod_resource/content/3/2b_PS%20Techniques.pdf)
  y en [Spoken Language Processing](https://discovery.upc.edu/iii/encore/record/C__Rb1233593?lang=cat).
  También encontrará más información en los anexos del enunciado de esta práctica.

  Incluya, a continuación, una explicación de las técnicas incorporadas al estimador. Se valorará la
  inclusión de gráficas, tablas, código o cualquier otra cosa que ayude a comprender el trabajo realizado.

  También se valorará la realización de un estudio de los parámetros involucrados. Por ejemplo, si se opta
  por implementar el filtro de mediana, se valorará el análisis de los resultados obtenidos en función de
  la longitud del filtro.
   

Evaluación *ciega* del estimador
-------------------------------

Antes de realizar el *pull request* debe asegurarse de que su repositorio contiene los ficheros necesarios
para compilar los programas correctamente ejecutando `make release`.

Con los ejecutables construidos de esta manera, los profesores de la asignatura procederán a evaluar el
estimador con la parte de test de la base de datos (desconocida para los alumnos). Una parte importante de
la nota de la práctica recaerá en el resultado de esta evaluación.
