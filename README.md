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


   <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/codi_autocorrelacio.png>
   
   

   * Inserte una gŕafica donde, en un *subplot*, se vea con claridad la señal temporal de un segmento de
     unos 30 ms de un fonema sonoro y su periodo de pitch; y, en otro *subplot*, se vea con claridad la
	 autocorrelación de la señal y la posición del primer máximo secundario.
	 
  <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/gr%C3%A0fica_py.png> 
  
	 NOTA: es más que probable que tenga que usar Python, Octave/MATLAB u otro programa semejante para
	 hacerlo. Se valorará la utilización de la biblioteca matplotlib de Python.

   * Determine el mejor candidato para el periodo de pitch localizando el primer máximo secundario de la
     autocorrelación. Inserte a continuación el código correspondiente.


    <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/Codi_localitzacio_primer_max_secundari_autocorrelacio.png> 


   * Implemente la regla de decisión sonoro o sordo e inserte el código correspondiente.


    <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/unnvoiced.png>


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


    <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/tram_sonor_15ms.png>

      
      Gràfica tram sord


    <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/tram_sord_15ms.png>


      En la gràfica de d'alt de tot tenim la gràfica de l'autocorrelació. Amb aquesta, podem determinar un umbral de umaxnorm d'aproximadamtn 0.6. En la segona gràfica observem l'autocorrelació normalitzada. Podem determinar un umbral per l'autocorrelació normalitzada al voltant de l'1. A la tercera gràfica hi ha la potència, que podriem deterinar un umbral al voltant dels -40.
      
      - Use el estimador de pitch implementado en el programa `wavesurfer` en una señal de prueba y compare
	    su resultado con el obtenido por la mejor versión de su propio sistema.  Inserte una gráfica
		ilustrativa del resultado de ambos estimadores.
     
     A continuació observem el pitch de la senyal obtingut amb la nostra versió del sistema.


     <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/comparaci%C3%B3_pitch_rl002f0.png>


     A continuació observem el pitch de la senyal obtingut per la pròpia senyal


    <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/comparacio_pitch_rl002f0ref.png>


    Pel que fa al contorn de pitch realitzat pel wavesurfer, en els dos casos és bastant similar.


    A continuació mostrem la comparació del pitch amb el pitch de referència amb unes gràfiques on es poden observar millor els detalls:


  <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/pitch_pitchref_python.png>


		Aunque puede usar el propio Wavesurfer para obtener la representación, se valorará
	 	el uso de alternativas de mayor calidad (particularmente Python).
  
  * Optimice los parámetros de su sistema de estimación de pitch e inserte una tabla con las tasas de error
    y el *score* TOTAL proporcionados por `pitch_evaluate` en la evaluación de la base de datos 
	`pitch_db/train`..


  <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/tanxcent_sense_ampliables.png>

  

Ejercicios de ampliación
------------------------

- Usando la librería `docopt_cpp`, modifique el fichero `get_pitch.cpp` para incorporar los parámetros del
  estimador a los argumentos de la línea de comandos.
  
  Esta técnica le resultará especialmente útil para optimizar los parámetros del estimador. Recuerde que
  una parte importante de la evaluación recaerá en el resultado obtenido en la estimación de pitch en la
  base de datos.

  * Inserte un *pantallazo* en el que se vea el mensaje de ayuda del programa y un ejemplo de utilización
    con los argumentos añadidos.

  <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/missatge_help_programa.png>

  Hem afegit tres paràmetres, 'upot' és per referir-nos a l'umbral per la potència, 'umaxnorm' és l'umbral per a referir-nos al màxim de l'autocorrelació normalitzada i 'unorm' és l'umbral de l'autocorrelació normalitzada en 1. Aquests umbrals ens ajuden a l'hora de determinar si un senyal és sord o sonor i així obtenir resultats millors. El que ens facilita la detecció del pitch.
  
  Exemple utilització amb els arguments afegits:

   <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/exemple_utilitzaci%C3%B3_umbrals.png>


- Implemente las técnicas que considere oportunas para optimizar las prestaciones del sistema de estimación
  de pitch.

  Entre las posibles mejoras, puede escoger una o más de las siguientes:

  * Técnicas de preprocesado: filtrado paso bajo, diezmado, *center clipping*, etc.
  
  Center clipping

  Amb aquesta tècnica fiquem a zero els trams de la senyal que es trobin entre dos umbrals definits. Amb aquest mètode el que aconseguim és eliminar, ficar a zero els instants de temps en que la senyal té una amplitud menor. Am això aconseguim robustesa devant del soroll. A més, s'intenta eliminar els trams on no hi hagi periodicitat, i quedar-se només amb aquesta, el que fa destacar més els formants en el domini freqüencial. També mencionar que hem triat aquest mètode ja que al anul·lar aquests valors, introduim una distorció lineal, el que fa augmentar la intensitat dels harmònics d'ordre elevat, cosa que ens interesa pel mencionat anteriorment.


   <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/center_clipping.png>


  * Técnicas de postprocesado: filtro de mediana, *dynamic time warping*, etc.
  
  Filtre de mitjana

  Aquest mètode utilitza una finestra que es va movent al llarg de la senyal. Per implementar-lo, creem un nou vector on guradarem els valors de f0 un cop la senyal hagi passat pel filtre. Amb aquest la finestra, agafem la mostra actual, l'anterior i la posterior i ens quedem amb el valor mig de les tres. Aquest valor el pasem al nou vector. Per tant, ens quedem amb els valors mitjos de les tres mostres (l'actual, l'anterior i la posterior). Hem comprovat que la millor longitud per la finestra és de 3, ja que així es queda només amb una mostra anterior i una posterior, ja que si augmentavem el valor de l obteniem pitjors resultats. El filtre implementat és no recursiu, ja que no altera els valors originals, sinó que els guarda a una altre variable. La ventatje d'utilitzar aquest filtre és que el valor final de f0 és un valor real de la senyal i no un promig.


  <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/filtre_de_mitjana.png>

  
  A continuació mostrem el tant per cent que ens queda si realitzem el filtre de mitjana amb una l=5, en comptes de l=3

  Amb l=5
  
  <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/tantxcent_ambl%3D5.png>

  Amb l=3
  
  <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/tanxcent_amb_ampliables.png>


  Si comparem el resultat amb el que obtenim amb l=3, podem observar que detecta pitjor les trames no veu com a veu i els errors de veu són més elevats. En canvi, pel que fa a trames de veu detectades com a no veu, no varia. Tot i això, els dos primer paràmetres fan que tinguem un MSE d'errors fins més elevat amb l=5. Per tant, descartem aquesta l i ens quedem amb la l=3, on tenim uns erros lleugerament menors i obtenim millors resultats.
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


  <img src=https://github.com/isibardaji/P3/blob/bardaji-cot/img/tanxcent_amb_ampliables.png>


  Podem observar una gran millora amb els processos aplicats de center clipping i filtre de mediana respecte al resultat sense aplicar-los.

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
