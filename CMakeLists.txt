cmake_minimum_required(VERSION 3.10)

project(CalculoNumerico CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main
    main.cpp
    backend/bissecao/bissecao.cpp
    backend/newton_raphson/newton_raphson.cpp
    backend/posicao_falsa/posicao_falsa.cpp
    backend/encontrar_intervalo/encontrar_intervalo.cpp
)