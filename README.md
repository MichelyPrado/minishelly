<div align="center" >
  <img src="./imgs/MiniShelly-logo.png" alt="Libft" width="175" height="175">
</div>

***

[![TESTS CHECK](https://github.com/ThreeDP/minishelly/actions/workflows/tests.yml/badge.svg)](https://github.com/ThreeDP/minishelly/actions/workflows/tests.yml/badge.svg)
[![NORM CHECK](https://github.com/ThreeDP/minishelly/actions/workflows/norm.yml/badge.svg)](https://github.com/ThreeDP/get_next_line/actions/workflows/norm.yml)

# 🐚 Sobre 


https://github.com/ThreeDP/minishelly/assets/37334813/26f3ea0b-0879-400e-ac61-54111c149b91


Este projeto consiste em uma replica do bash, desenvolvida em linguagem C utilizando a metodologia XP com TDD. O projeto foi realizado em dupla e conta com diversas funcionalidades que tornam a experiência de uso semelhante ao bash original.

## O que é um bash?

O Bash é um interpretador de comandos de texto que funciona como uma interface entre o usuário e o sistema operacional. Ele permite a execução de comandos, scripts e programas de forma interativa ou automatizada. O Bash é uma ferramenta essencial para administradores de sistemas e desenvolvedores, pois facilita a execução de tarefas complexas e repetitivas.

## Impacto do Projeto

O desenvolvimento dessa replica do bash em C teve um impacto significativo em nosso aprendizado e habilidades como engenheiros de software. Através desse projeto, adquirimos conhecimento em linguagem C, metodologia XP, TDD e diversas funcionalidades do bash. Além disso, a prática de trabalhar em dupla nos permitiu aprimorar nossas habilidades de colaboração e comunicação.

# Habilidades Adquiridas

- Trabalho em equipe: desenvolvemos o projeto em dupla, o que exigiu comunicação eficaz, colaboração constante e empatia ao entender as dificuldades do outro.
- Resolução de problemas: enfrentamos desafios durante o desenvolvimento do projeto e encontramos soluções criativas para superá-los.
- Linguagem C: aprofundamos nosso conhecimento em C ao implementar as funcionalidades do interpretador de comandos.
- Metodologia XP com TDD: Utilizamos a metodologia XP (Extreme Programming) com TDD (Test-Driven Development) para desenvolver o projeto, o que nos ajudou a garantir a qualidade do código e a facilitar a manutenção e evolução do software.

# Funções Desenvolvidas
> O minishelly possui a implementação das seguintes funções de um interpretador de comandos bash.

- [x] Builtins
  - [x] echo -n
  - [x] env
  - [x] unset
  - [x] export
  - [x] pwd
  - [x] cd
  - [x] exit
- [X] Exec commands
  - [x] pipe
  - [X] operator >
  - [X] operator <
  - [X] operator >>
  - [X] operator <<
- [X] Signals
  - [X] ctrl-C
  - [X] ctrl-D
  - [X] ctrl-\
- [x] String parser
  - [x] expand environ var
  - [x] expand $? exit code
  - [x] single quote
  - [x] double quote
  - [x] token creation
- [x] Sys config
  - [x] prompt history
  - [x] prompt wait if there was no closing quote

# Compilar o minishelly
> Execute os seguintes comandos dentro da pasta srcs para compilar o programa e começar a utilizar.


https://github.com/ThreeDP/minishelly/assets/37334813/af6157fd-35e9-4436-ac7b-dceb2d76a8cc


**Dependências necessárias**
- biblioteca readline.
- sistema operacional unix.

```bash
sudo apt install libreadline-dev
```

**Compilação:**
```bash
make
```

**Limpar objetos, executável e recompilar:**
```bash
make re
```

**Limpar objetos:**
```bash
make re
```

**Limpar objetos e executável:**
```bash
make re
```

# Para executar os testes unitários
> Para executar os testes execute os comandos dentro da pasta tests.

**Dependências necessárias**
- valgrind.
- sistema operacional unix.

```bash
sudo apt install valgrind
```

**Executar todos os testes:**
```bash
make
```
> Todos os comandos anteriores de exclusão de arquivos realizão a mesma ação dentro da pasta de testes.

### Unit test
> Para executar um teste especifico execute o seguinte padrão de comando.

```bash
make run-test TEST_NAME=<test_obj_dir>/<test_name>
```



