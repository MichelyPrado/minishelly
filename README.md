<div align="center" >
  <img src="./imgs/MiniShelly-logo.png" alt="Libft" width="175" height="175">
  <h1>&#128679; MiniShelly</h1>
  <p>Interpretador de linha de comando em Construção</p>
</div>

***

[![TESTS CHECK](https://github.com/ThreeDP/minishelly/actions/workflows/tests.yml/badge.svg)](https://github.com/ThreeDP/minishelly/actions/workflows/tests.yml/badge.svg)
[![NORM CHECK](https://github.com/ThreeDP/minishelly/actions/workflows/norm.yml/badge.svg)](https://github.com/ThreeDP/get_next_line/actions/workflows/norm.yml)

# Sobre 
> O projeto Minishell da Escola 42 é uma tarefa que desafia os estudantes a criar um interpretador de linha de comando básico em linguagem C. O objetivo é implementar uma série de funções que permitam a execução de comandos internos (builtins) e externos, como em um shell real. Além disso, é necessário implementar recursos como redirecionamento de entrada e saída, pipes, expansão de variáveis e tratamento de sinais. O projeto tem como finalidade aprimorar habilidades em programação em linguagem C, gerenciamento de memória e trabalho com processos no sistema operacional Unix/Linux.

# Funções
> Aqui temos algumas das funções que já estão implementadas no MiniShelly.

- [x] Builtins
  - [x] echo -n
  - [x] env
  - [x] unset
  - [x] export
  - [x] pwd
  - [x] cd
  - [x] exit
- [ ] Exec commands
  - [x] run command
  - [ ] pipe
  - [ ] operator &&
  - [ ] operator ||
  - [ ] operator >
  - [ ] operator <
  - [ ] operator >>
  - [ ] operator <<
  - [ ] operator *
- [ ] Signals
  - [ ] ctrl-C
  - [ ] ctrl-D
  - [ ] ctrl-\
- [ ] String parser
  - [ ] expand environ var
  - [ ] expand $? exit code
  - [x] single quote
  - [x] double quote
  - [x] token creation
- [x] Sys config
  - [x] prompt history
  - [x] prompt wait if there was no closing quote

# Run
> Execute os seguintes comandos dentro da pasta srcs para compilar o programa e começar a utilizar.

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

# Testing
> Para executar os testes execute os comandos dentro da pasta tests.

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