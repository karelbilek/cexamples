: Co dělá myDD?

- myDD vezme buď STDIN, nebo soubor, co dostane v options -i nebo --fin
- myDD buď načítá po 512byte blocích, nebo po tolika, co dostane v -n
- myDD zapíše buď do STDOUT, nebo tam, co dostane v -o nebo --fout
- myDD přepisuje, když má option -r nebo --rewrite


- fprintf(stderr, "OMG") vypise chybu, potrebuje 