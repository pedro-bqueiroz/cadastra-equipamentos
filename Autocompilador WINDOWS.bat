:: É necessário já ter o GCC instalado e no PATH. A implementação de um 'autocompilador' para pessoas que não têm tanto conhecimento sobre tecnologia será revista no futuro, e pretendo que seja possível apenas clicar duas vezes neste arquivo.
gcc -c cadastra_equipamentos.c
gcc cadastra_equipamentos.o cadastra-equipamentos.c -o Cadastra-Equipamentos.exe
start Cadastra-Equipamentos.exe
pause