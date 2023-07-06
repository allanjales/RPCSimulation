# Versão mínima do CMAKE
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Nome da simulação
project(RPCSimulation)

# Pacotes necessários. UI_All para user interface e VIS_ALL para visualização
find_package(Geant4 REQUIRED ui_all vis_all)

# Usar os includes do Geant4
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# Compila os sources do projeto
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Cria executável a partir do arquivo principal
add_executable(RPCSimulation RPCSimulation.cc ${sources} ${headers})

# Linka libraries para o executável
target_link_libraries(RPCSimulation ${Geant4_LIBRARIES})

# Copia todos os arquivos de macro para o diretório da build
file(GLOB MACRO_FILES "*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

# Copia todos os arquivos de macro dados para o diretório da build
file(GLOB DATA_FILES "*.dat")
file(COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})

# O projeto depende do executável
add_custom_target(Simulation DEPENDS RPCSimulation)