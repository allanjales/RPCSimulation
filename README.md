# Simulação de uma RPC 

Antes de tudo, crie uma pasta chamada `build`:
~~~sh
mkdir build
cd build
~~~

Para compilar o código e gerar os executáveis:
~~~sh
cmake ..
make
~~~

Para rodar o código:
~~~sh
./RPCSimulation
~~~

Para rodar com tudo:
~~~sh
./RPCSimulation run.mac
~~~

Para rodar com tudo e salvar num arquivo log.txt:
~~~sh
./RPCSimulation run.mac | tee log.txt
~~~

## Nota

Os arquivos aqui foram testados com o GEANT4 v11.02.02