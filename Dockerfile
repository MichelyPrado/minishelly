FROM ubuntu:latest

RUN apt-get update && apt-get install -y build-essential
RUN apt-get install libcmocka-dev -y
RUN apt-get install -y libreadline-dev
RUN apt-get install vim -y
RUN apt-get install make -y
RUN apt-get install valgrind -y
RUN apt-get install python3 -y
RUN apt-get install python3-venv python3-pip -y
RUN python3 -m pip install --upgrade pip setuptools
RUN python3 -m pip install norminette
ADD . /minishelly
WORKDIR /minishelly/tests

CMD ["make"]